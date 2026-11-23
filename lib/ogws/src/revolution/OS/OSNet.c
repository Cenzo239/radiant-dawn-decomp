#include <revolution/OS.h>

// @bug Wrong prototypes. Somebody forgot to include the header!!!
// (FE10: defined below as weak functions, never inlined)
int NWC24iPrepareShutdown() DECOMP_DONT_INLINE;
int NWC24SuspendScheduler() DECOMP_DONT_INLINE;
int NWC24iSynchronizeRtcCounter() DECOMP_DONT_INLINE;

void __OSInitNet(void) {
    s32 error;
    OSIOSRev rev;

    __OSGetIOSRev(&rev);
    if (rev.idLo <= 4 || rev.idLo == 9) {
        return;
    }

    error = NWC24iPrepareShutdown();
    if (error != 0) {
        if (error < 0) {
            OSReport("Failed to register network shutdown function. %d\n",
                     error);
        }

        error = NWC24SuspendScheduler();
        if (error < 0) {
            OSReport("Failed to suspend the WiiConnect24 scheduler. %d\n",
                     error);
        }
    }

    // @bug Wrong prototype. Somebody forgot to include the header!!!
    error = NWC24iSynchronizeRtcCounter();
    if (error != 0) {
        OSReport(
            "Failed to synchronize time with network resource managers. %d\n",
            error);
    }
}

/**
 * FE10 (SDK Nov 2006): OSNet.c carries its own small copies of the NWC24 functions it needs
 * (reconstructed from the code; later versions: Petari NWC24System.c/NWC24Schedule.c/NWC24Time.c/NWC24Ipc.c).
 */
#include <revolution/IPC.h>
#include <revolution/SC.h>

#define NWC24_ERR_FATAL (-1)
#define NWC24_ERR_INVALID_VALUE (-3)
#define NWC24_ERR_INPROGRESS (-29)
#define NWC24_ERR_INTERNAL_IPC (-42)

static s32 nwc24ShtFd = -1;
static s32 nwc24ShtRetryRest = 0;
static BOOL NWC24iIsRequestPending = FALSE;

static OSShutdownFunctionInfo ShutdownFuncInfo;

static BOOL NWC24Shutdown_(BOOL final, u32 event);
static s32 NWC24iSetRtcCounter_(u32 rtc) DECOMP_DONT_INLINE;
static s32 NWC24iRequestShutdown(u32 event, s32* result) DECOMP_DONT_INLINE;
static s32 CallbackAsyncIpc(s32 result, void* arg);

static inline s32 CheckCallingStatus(const char* user) {
    OSThread* thread = OSGetCurrentThread();
    if (thread == NULL) {
        return NWC24_ERR_FATAL;
    }

    return 0;
}

static inline s32 NWC24iOpenResourceManager_(const char* user,
                                             const char* name, s32* fd,
                                             u32 mode) {
    s32 result;

    if (fd == NULL) {
        return NWC24_ERR_INVALID_VALUE;
    }

    result = IOS_Open(name, mode);
    *fd = result;

    if (result < 0) {
        if (result == -6) {
            return NWC24_ERR_INPROGRESS;
        }

        return NWC24_ERR_INTERNAL_IPC;
    }

    return 0;
}

// Open with the descriptor in a local variable (kept in a register in FE10)
#define NWC24_OPEN_LOCAL(user, name, fd, mode, result)                         \
    fd = IOS_Open(name, mode);                                                 \
    if (fd < 0) {                                                              \
        if (fd == -6) {                                                        \
            result = NWC24_ERR_INPROGRESS;                                     \
        } else {                                                               \
            result = NWC24_ERR_INTERNAL_IPC;                                   \
        }                                                                      \
    } else {                                                                   \
        result = 0;                                                            \
    }

static inline s32 NWC24iCloseResourceManager_(const char* user, s32 fd) {
    return IOS_Close(fd) < 0 ? NWC24_ERR_INTERNAL_IPC : 0;
}

static inline s32 NWC24iIoctlResourceManager_(const char* user, s32 fd,
                                              s32 type, void* in, s32 inSize,
                                              void* out, s32 outSize) {
    return IOS_Ioctl(fd, type, in, inSize, out, outSize) < 0
               ? NWC24_ERR_INTERNAL_IPC
               : 0;
}

static inline s32 NWC24iIoctlResourceManagerAsync_(const char* user, s32 fd,
                                                   s32 type, void* in,
                                                   s32 inSize, void* out,
                                                   s32 outSize, void* arg) {
    if (IOS_IoctlAsync(fd, type, in, inSize, out, outSize, CallbackAsyncIpc,
                       arg) < 0) {
        return NWC24_ERR_INTERNAL_IPC;
    }

    NWC24iIsRequestPending = TRUE;
    return 0;
}

__declspec(weak) int NWC24iPrepareShutdown(void) DECOMP_DONT_INLINE;
__declspec(weak) int NWC24iPrepareShutdown(void) {
    s32 result = 0;

    ShutdownFuncInfo.func = NWC24Shutdown_;
    ShutdownFuncInfo.prio = 110;
    OSRegisterShutdownFunction(&ShutdownFuncInfo);

    if (nwc24ShtFd < 0) {
        result = NWC24iOpenResourceManager_(
            "NWC24iPrepareShutdown", "/dev/net/kd/request", &nwc24ShtFd, 1);
    }

    nwc24ShtRetryRest = 5;

    if (result == 0) {
        result = 1;
    }

    return result;
}

static inline s32 GetRTC(u32* rtc) {
    s64 time;
    u32 bias, status;

    do {
        status = SCCheckStatus();
        if (status == 2) {
            return NWC24_ERR_FATAL;
        }
    } while (status != 0);

    bias = SCGetCounterBias();
    time = OSGetTime();
    *rtc = (u32)(OS_TICKS_TO_SEC(time) - bias);
    return 0;
}

__declspec(weak) int NWC24iSynchronizeRtcCounter(void) DECOMP_DONT_INLINE;
__declspec(weak) int NWC24iSynchronizeRtcCounter(void) {
    static s64 lastSync = 0;
    u32 rtc;
    s32 result;

    if (lastSync == 0 || __OSGetSystemTime() > lastSync + OS_SEC_TO_TICKS(60)) {
        result = GetRTC(&rtc);
        if (result != 0) {
            return result;
        }

        lastSync = __OSGetSystemTime();
        return NWC24iSetRtcCounter_(rtc);
    }

    return 0;
}

__declspec(weak) int NWC24SuspendScheduler(void) DECOMP_DONT_INLINE;
__declspec(weak) int NWC24SuspendScheduler(void) {
    static u8 susResult[32] ALIGN(32);
    s32 result;
    s32 fd;
    s32 closeResult;

    result = CheckCallingStatus("NWC24SuspendScheduler");
    if (result < 0) {
        return result;
    }

    NWC24_OPEN_LOCAL("NWC24SuspendScheduler", "/dev/net/kd/request", fd, 0,
                     result);
    if (result >= 0) {
        result = NWC24iIoctlResourceManager_("NWC24SuspendScheduler", fd, 1,
                                             NULL, 0, susResult,
                                             sizeof(susResult));
        if (result >= 0) {
            result = *(s32*)susResult;
        }

        closeResult =
            NWC24iCloseResourceManager_("NWC24ResumeScheduler", fd);
        if (closeResult < 0) {
            result = closeResult;
        }
    }

    return result;
}

static s32 NWC24iRequestShutdown(u32 event, s32* result) {
    static u8 shtBuffer[32] ALIGN(32);
    static u8 shtResult[32] ALIGN(32);

    *(u32*)shtBuffer = event;
    return NWC24iIoctlResourceManagerAsync_(
        "NWC24iRequestShutdown", nwc24ShtFd, 40, shtBuffer, sizeof(shtBuffer),
        shtResult, sizeof(shtResult), result);
}

static BOOL NWC24Shutdown_(BOOL final, u32 event) {
    static BOOL shuttingdown = FALSE;
    static s32 result = 0;

    if (final) {
        return TRUE;
    }

    if (shuttingdown) {
        if (NWC24iIsRequestPending) {
            return FALSE;
        }

        if (result >= 0) {
            return TRUE;
        }

        if (nwc24ShtRetryRest > 0) {
            shuttingdown = FALSE;
            nwc24ShtRetryRest--;
        } else {
            OSReport("NWC24Shutdown_: Give up!\n");
            return TRUE;
        }
    } else if (NWC24iRequestShutdown(event, &result) >= 0) {
        shuttingdown = TRUE;
    }

    return FALSE;
}

static s32 NWC24iSetRtcCounter_(u32 rtc) {
    static u8 timeBuffer[32] ALIGN(32);
    static u8 timeResult[32] ALIGN(32);
    s32 result;
    s32 fd;
    s32 closeResult;

    result = CheckCallingStatus("NWC24iSetRtcCounter_");
    if (result < 0) {
        return result;
    }

    NWC24_OPEN_LOCAL("NWC24iSetRtcCounter_", "/dev/net/kd/time", fd, 0,
                     result);
    if (result >= 0) {
        *(u32*)timeBuffer = rtc;
        result = NWC24iIoctlResourceManager_("NWC24iSetRtcCounter_", fd, 23,
                                             timeBuffer, sizeof(timeBuffer),
                                             timeResult, sizeof(timeResult));
        if (result >= 0) {
            result = *(s32*)timeResult;
        }

        closeResult =
            NWC24iCloseResourceManager_("NWC24iSetRtcCounter_", fd);
        if (result >= 0) {
            result = closeResult;
        }
    }

    return result;
}

static s32 CallbackAsyncIpc(s32 result, void* arg) {
    if (arg != NULL) {
        *(s32*)arg = result;
    }

    NWC24iIsRequestPending = FALSE;
    return 0;
}
