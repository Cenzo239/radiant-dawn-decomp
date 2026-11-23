#include <revolution/DVD.h>
#include <revolution/OS.h>
#include <revolution/PAD.h>
#include <revolution/SC.h>
#include <revolution/VI.h>

#include <string.h>

static OSShutdownFunctionQueue ShutdownFunctionQueue;

static void KillThreads(void);

void OSRegisterShutdownFunction(OSShutdownFunctionInfo* info) {
    OSShutdownFunctionInfo* it;
    OSShutdownFunctionInfo* prev;
    OSShutdownFunctionInfo* tail;

    for (it = ShutdownFunctionQueue.head; it != NULL && it->prio <= info->prio;
         it = it->next) {
        ;
    }

    if (it == NULL) {

        tail = ShutdownFunctionQueue.tail;
        if (tail == NULL) {
            ShutdownFunctionQueue.head = info;
        } else {
            ShutdownFunctionQueue.tail->next = info;
        }

        info->prev = tail;
        info->next = NULL;

        it = ShutdownFunctionQueue.head;
        ShutdownFunctionQueue.tail = info;
    } else {
        info->next = it;

        prev = it->prev;
        it->prev = info;
        info->prev = prev;

        if (prev == NULL) {
            ShutdownFunctionQueue.head = info;
        } else {
            prev->next = info;
        }
    }
}

BOOL __OSCallShutdownFunctions(u32 pass, u32 event) {
    OSShutdownFunctionInfo* iter;
    BOOL failure;
    u32 prio;

    prio = 0;
    failure = FALSE;

    for (iter = ShutdownFunctionQueue.head; iter != NULL; iter = iter->next) {
        if (failure && prio != iter->prio) {
            break;
        }

        failure |= !iter->func(pass, event);
        prio = iter->prio;
    }

    failure |= !__OSSyncSram();

    return !failure;
}

void __OSShutdownDevices(u32 event) {
    BOOL padIntr;
    BOOL osIntr;
    BOOL keepEnable;

    switch (event) {
    case OS_SD_EVENT_FATAL:
    case OS_SD_EVENT_RESTART:
    case OS_SD_EVENT_RETURN_TO_MENU:
    case OS_SD_EVENT_LAUNCH_APP:
        keepEnable = FALSE;
        break;
    case 1:
    case OS_SD_EVENT_SHUTDOWN:
    case 3:
    default:
        keepEnable = TRUE;
        break;
    }

    __OSStopAudioSystem();

    if (!keepEnable) {
        padIntr = __PADDisableRecalibration(TRUE);
    }

    while (!__OSCallShutdownFunctions(FALSE, event)) {
        ;
    }

    while (!__OSSyncSram()) {
        ;
    }

    osIntr = OSDisableInterrupts();
    __OSCallShutdownFunctions(TRUE, event);
    LCDisable();

    if (!keepEnable) {
        __PADDisableRecalibration(padIntr);
    }

    KillThreads();
}

// TODO(kiwi) There must be a better way....
static void __OSGetDiscState(u8* out) {
    u32 flags;

    if (__DVDGetCoverStatus() != DVD_COVER_CLOSED) {
        *out = 3;
    } else if (*out == 1) {
        if (!__OSGetRTCFlags(&flags) || flags == 0) {
            goto status_1;
        }

    status_2:
        *out = 2;
    } else {
        goto status_2;

    status_1:
        *out = 1;
    }
}

// FE10 (SDK Nov 2006): variant of OSReturnToMenu used by __OSBootDol (flag 2, shutdown event 1, hot reset)
void __OSReturnToMenuForError(void) {
    OSStateFlags stateFlags;

    __OSStopPlayRecord();
    __OSUnRegisterStateEvent();
    __DVDPrepareReset();

    __OSReadStateFlags(&stateFlags);
    __OSGetDiscState(&stateFlags.discState);
    stateFlags.BYTE_0x5 = 2;
    __OSClearRTCFlags();
    __OSWriteStateFlags(&stateFlags);

    OSDisableScheduler();
    __OSShutdownDevices(1);
    __OSHotReset();
}

static void KillThreads(void) {
    OSThread* iter;
    OSThread* next;

    for (iter = OS_THREAD_QUEUE.head; iter != NULL; iter = next) {
        next = iter->nextActive;

        switch (iter->state) {
        case OS_THREAD_STATE_SLEEPING:
        case OS_THREAD_STATE_READY:
            OSCancelThread(iter);
            break;
        }
    }
}

void OSShutdownSystem(void) {
    SCIdleModeInfo idleMode;
    OSStateFlags stateFlags;
    OSIOSRev iosRev;

    memset(&idleMode, 0, sizeof(SCIdleModeInfo));
    SCInit();
    while (SCCheckStatus() == SC_STATUS_BUSY) {
        ;
    }
    SCGetIdleMode(&idleMode);

    __OSStopPlayRecord();
    __OSUnRegisterStateEvent();
    __DVDPrepareReset();
    __OSReadStateFlags(&stateFlags);

    __OSGetDiscState(&stateFlags.discState);
    if (idleMode.wc24 == TRUE) {
        stateFlags.BYTE_0x5 = 5;
    } else {
        stateFlags.BYTE_0x5 = 1;
    }

    __OSClearRTCFlags();
    __OSWriteStateFlags(&stateFlags);
    __OSGetIOSRev(&iosRev);

    if (idleMode.wc24 == TRUE) {
        OSDisableScheduler();
        __OSShutdownDevices(OS_SD_EVENT_RETURN_TO_MENU);
        OSEnableScheduler();
        __OSLaunchMenu();
    } else {
        OSDisableScheduler();
        __OSShutdownDevices(OS_SD_EVENT_SHUTDOWN);
        __OSShutdownToSBY();
    }
}

// FE10 (SDK Nov 2006): OSRestart and its NAND-title path
void __OSRelaunchTitle(void);
void __OSReboot(u32 resetCode, u32 bootDol);
BOOL __OSReadNandbootInfo(void* info);
BOOL __OSWriteNandbootInfo(void* info);

static u32 bootThisDol;

typedef struct OSNandbootInfoFE10 {
    u32 WORD_0x0;
    u32 WORD_0x4;
    u32 returnType; // at 0x8
    u32 resetCode;  // at 0xC
    u8 rest[0x1020 - 0x10];
} OSNandbootInfoFE10;

static void RestartNandTitle(u32 resetCode) DECOMP_DONT_INLINE;
static void RestartNandTitle(u32 resetCode) {
    OSNandbootInfoFE10* info;
    OSStateFlags stateFlags;

    OSSetArenaLo((void*)0x81280000);
    OSSetArenaHi((void*)0x812F0000);

    info = (OSNandbootInfoFE10*)OSAllocFromMEM1ArenaLo(
        sizeof(OSNandbootInfoFE10), 32);
    memset(info, 0, sizeof(OSNandbootInfoFE10));
    __OSReadNandbootInfo(info);
    info->returnType = 1;
    info->resetCode = resetCode | 0x80000000;
    __OSWriteNandbootInfo(info);

    if (__OSReadStateFlags(&stateFlags)) {
        stateFlags.BYTE_0x5 = 3;
        __OSWriteStateFlags(&stateFlags);
    }

    OSDisableScheduler();
    __OSShutdownDevices(4);
    OSEnableScheduler();
    __OSRelaunchTitle();
}

void OSRestart(u32 resetCode) {
    u8 appType = OSGetAppType();

    __OSStopPlayRecord();
    __OSUnRegisterStateEvent();

    if (appType == 0x81) {
        RestartNandTitle(resetCode);
    } else if (appType == 0x80) {
        OSDisableScheduler();
        __OSShutdownDevices(4);
        OSEnableScheduler();
        __OSReboot(resetCode, bootThisDol);
    }

    OSDisableScheduler();
    __OSShutdownDevices(1);
    __OSHotReset();
}

void OSReturnToMenu(void) {
    OSStateFlags stateFlags;

    __OSStopPlayRecord();
    __OSUnRegisterStateEvent();
    __DVDPrepareReset();

    __OSReadStateFlags(&stateFlags);
    __OSGetDiscState(&stateFlags.discState);
    stateFlags.BYTE_0x5 = 3;
    __OSClearRTCFlags();
    __OSWriteStateFlags(&stateFlags);

    OSDisableScheduler();
    __OSShutdownDevices(OS_SD_EVENT_RETURN_TO_MENU);
    OSEnableScheduler();

    __OSLaunchMenu();
    OSDisableScheduler();
    __VISetRGBModeImm();
    __OSHotReset();

    // clang-format off
#line 843
    OS_ERROR("OSReturnToMenu(): Falied to boot system menu.\n");
    // clang-format on
}

// FE10 (SDK Nov 2006)
void __OSReturnToMenu(void) {
    OSStateFlags stateFlags;

    __OSReadStateFlags(&stateFlags);
    stateFlags.discState = 2;
    stateFlags.BYTE_0x5 = 3;
    __OSClearRTCFlags();
    __OSWriteStateFlags(&stateFlags);

    __OSLaunchMenu();
    OSDisableScheduler();
    __VISetRGBModeImm();
    __OSHotReset();

    // clang-format off
#line 869
    OS_ERROR("__OSReturnToMenu(): Falied to boot system menu.\n");
    // clang-format on
}

u32 OSGetResetCode(void) {
    if (__OSRebootParams.WORD_0x0 != 0) {
        return __OSRebootParams.WORD_0x4 | 0x80000000;
    }

    return PI_HW_REGS[PI_RESET] >> 3;
}

void OSResetSystem(u32 arg0, u32 arg1, u32 arg2) {
#pragma unused(arg0)
#pragma unused(arg1)
#pragma unused(arg2)

    // clang-format off
#line 1020
    OS_ERROR("OSResetSystem() is obsoleted. It doesn't work any longer.\n");
    // clang-format on
}
