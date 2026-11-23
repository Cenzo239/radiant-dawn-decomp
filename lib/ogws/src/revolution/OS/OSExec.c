#include <revolution/ESP.h>
#include <revolution/IPC.h>
#include <revolution/OS.h>

#include <stdio.h>
#include <string.h>

#define MENU_TITLE_ID 0x0000000100000002
#define TICKET_VIEW_SIZE 0xD8

static u8 views[0xBD00] ALIGN(32);

// FE10 (SDK Nov 2006): work buffers of __OSLaunchNextFirmware
typedef struct OSExecGameTOC {
    u32 numGamePartitions; // at 0x0
    u32 partitionInfos;    // at 0x4
} OSExecGameTOC;

typedef struct OSExecPartitionInfo {
    u32 gamePartition; // at 0x0
    u32 type;          // at 0x4
} OSExecPartitionInfo;

#pragma pack(push, 4)
typedef struct OSExecTitleMeta {
    u8 head[0x184];
    u64 sysVersion; // at 0x184
    u8 rest[0x4A00 - 0x18C];
} OSExecTitleMeta;
#pragma pack(pop)

static u8 gameTocBuf[0x20] ALIGN(32);
static u8 partInfoBuf[0x20] ALIGN(32);
static u8 tmdBuf[0x4A00] ALIGN(32);
static DVDDiskID id ALIGN(32);

volatile u32 __PIRegs[0xC] : 0xCC003000;
s32 __OSCurrentTGCOffset : 0x800030F4;
static volatile BOOL Prepared;
static OSExecGameTOC* gameToc;
static OSExecPartitionInfo* partInfo;
static OSExecPartitionInfo* bootGameInfo;
static OSExecTitleMeta* tmd;
BOOL __OSInReboot;
static volatile u32 DVDLowIntType;

void __OSReturnToMenu(void);
static s32 _ES_CloseLib(s32* fd);

static s32 _ES_InitLib(s32* fd);
static s32 _ES_GetTitleId(s32* fd, u64* tidOut);
static s32 _ES_GetTicketViews(s32* fd, u64 tid, void* pViews, u32* count);
static s32 _ES_LaunchTitle(s32* fd, u64 tid, void* pViews) DECOMP_DONT_INLINE;

/* Run/Callback/__OSBootDolSimple/__OSBootDol: Petari OSExec.c (FE10 range merges both sources) */
void __OSLaunchNextFirmware(void);
static BOOL PackArgs(void* addr, s32 argc, char* argv[]) {
    s32 numArgs;
    char* bootInfo2;
    char* ptr;
    char** list;
    u32 i;

    bootInfo2 = (char*)addr;
    memset(bootInfo2, 0, 0x2000);

    if (argc == 0) {
        *(u32*)&bootInfo2[8] = 0;
    } else {
        numArgs = argc;
        ptr = bootInfo2 + 0x2000;
        while (--argc >= 0) {
            ptr -= (strlen(argv[argc]) + 1);
            strcpy(ptr, argv[argc]);
            argv[argc] = (char*)(ptr - bootInfo2);
        }

        list = (char**)(bootInfo2 + ((ptr - bootInfo2) & ~3));
        list -= numArgs + 1;

        for (i = 0; i < numArgs + 1; i++) {
            list[i] = argv[i];
        }

        *(s32*)(list - 1) = numArgs;
        *(u32*)&bootInfo2[8] = (u32)((char*)(list - 1) - bootInfo2);
    }

    return TRUE;
}


// clang-format off
static asm void Run(register void* entryPoint) {
    fralloc
    bl      ICFlashInvalidate
    sync
    isync
    mtctr    entryPoint
    bctr
    frfree
    blr
}
// clang-format on

static void Callback(s32 result, DVDCommandBlock* block) {
    Prepared = TRUE;
}


void __OSGetExecParams(OSExecParams* out) {
    if ((void*)OS_DOL_EXEC_PARAMS >= (void*)0x80000000) {
        memcpy(out, OS_DOL_EXEC_PARAMS, sizeof(OSExecParams));
    } else {
        out->WORD_0x0 = 0;
    }
}

static void callback(u32 intType) {
    DVDLowIntType = intType;
}

#define EXEC_WAIT_DVD()                                                        \
    while (!DVDLowIntType) {                                                   \
    }                                                                          \
    if (DVDLowIntType != 1) {                                                  \
        OSReport("\nsecurity error(%d) has occurred", DVDLowIntType);         \
        __OSReturnToMenu();                                                    \
    }

// FE10 (SDK Nov 2006), reconstructed from the code (later version: Petari OSExec.c)
void __OSLaunchNextFirmware(void) {
    s32 result;
    void* pviews = &views;
    u32 count = 1;
    s32 fd = -1;
    struct {
        u8 tmp[4];
    } unused = {0xFF, 0xFF, 0xFF, 0};
    u8 i;
    u64 version;

    DVDLowIntType = 0;
    DVDLowClosePartition(callback);
    EXEC_WAIT_DVD();

    gameToc = (OSExecGameTOC*)gameTocBuf;
    DVDLowIntType = 0;
    DVDLowUnencryptedRead(gameToc, sizeof(gameTocBuf), 0x10000, callback);
    EXEC_WAIT_DVD();

    partInfo = (OSExecPartitionInfo*)partInfoBuf;
    DVDLowIntType = 0;
    DVDLowUnencryptedRead(partInfo, sizeof(partInfoBuf),
                          gameToc->partitionInfos, callback);
    EXEC_WAIT_DVD();

    bootGameInfo = NULL;
    for (i = 0; i < gameToc->numGamePartitions; i++) {
        if (partInfo->type == 0) {
            bootGameInfo = partInfo;
        }
        partInfo++;
    }

    DVDLowIntType = 0;
    DVDLowOpenPartition(bootGameInfo->gamePartition, NULL, 0, NULL,
                        (void*)tmdBuf, callback);
    EXEC_WAIT_DVD();

    DVDLowIntType = 0;
    DVDLowClosePartition(callback);
    EXEC_WAIT_DVD();

    tmd = (OSExecTitleMeta*)tmdBuf;
    version = tmd->sysVersion;

    result = _ES_InitLib(&fd);
    if (result != IPC_RESULT_OK) {
        OSReport("\nsecurity error(%d) has occurred", result);
        __OSHotReset();
    }

    result = _ES_GetTicketViews(&fd, version, NULL, &count);
    if (count != 1 || result != IPC_RESULT_OK) {
        OSReport("\nsecurity error(%d) has occurred", result);
        __OSHotReset();
    }

    result = _ES_GetTicketViews(&fd, version, pviews, &count);
    if (result != IPC_RESULT_OK) {
        OSReport("\nsecurity error(%d) has occurred", result);
        __OSHotReset();
    }

    result = _ES_LaunchTitle(&fd, version, pviews);
    if (result != IPC_RESULT_OK) {
        OSReport("\nsecurity error(%d) has occurred", result);
        __OSHotReset();
    }

    _ES_CloseLib(&fd);

    DVDLowInit();
    DVDLowIntType = 0;
    DVDLowReadDiskID(&id, callback);
    EXEC_WAIT_DVD();

    gameToc = (OSExecGameTOC*)gameTocBuf;
    DVDLowIntType = 0;
    DVDLowUnencryptedRead(gameToc, sizeof(gameTocBuf), 0x10000, callback);
    EXEC_WAIT_DVD();

    partInfo = (OSExecPartitionInfo*)partInfoBuf;
    DVDLowIntType = 0;
    DVDLowUnencryptedRead(partInfo, sizeof(partInfoBuf),
                          gameToc->partitionInfos, callback);
    EXEC_WAIT_DVD();

    bootGameInfo = NULL;
    for (i = 0; i < gameToc->numGamePartitions; i++) {
        if (partInfo->type == 0) {
            bootGameInfo = partInfo;
        }
        partInfo++;
    }

    DVDLowIntType = 0;
    DVDLowOpenPartition(bootGameInfo->gamePartition, NULL, 0, NULL,
                        (void*)tmdBuf, callback);
    EXEC_WAIT_DVD();
}

void __OSLaunchMenu(void) {
    // This makes me feel sick
    s32 result;
    void* pviews = &views;
    u32 count = 1;
    s32 fd = -1;
    struct {
        u8 tmp[4];
    } unused = {0xFF, 0xFF, 0xFF, 0};

    if (_ES_InitLib(&fd) != IPC_RESULT_OK) {
        return;
    }

    // Get num ticket views
    result = _ES_GetTicketViews(&fd, MENU_TITLE_ID, NULL, &count);
    if (count != 1 || result != IPC_RESULT_OK) {
        return;
    }

    // Get ticket views
    if (_ES_GetTicketViews(&fd, MENU_TITLE_ID, pviews, &count) !=
        IPC_RESULT_OK) {
        return;
    }

    // Launch title
    if (_ES_LaunchTitle(&fd, MENU_TITLE_ID, pviews) != IPC_RESULT_OK) {
        return;
    }

    while (TRUE) {
        ;
    }
}

// FE10 (SDK Nov 2006): relaunch the running title (used by OSRestart for NAND applications)
void __OSRelaunchTitle(void) {
    void* pviews;
    u32 count = 1;
    s32 fd = -1;
    u64 tid ALIGN(32);

    if (_ES_InitLib(&fd) != IPC_RESULT_OK) {
        return;
    }

    if (_ES_GetTitleId(&fd, &tid) != IPC_RESULT_OK) {
        return;
    }

    if (_ES_GetTicketViews(&fd, tid, NULL, &count) != IPC_RESULT_OK) {
        return;
    }

    pviews = OSAllocFromMEM1ArenaLo(count * TICKET_VIEW_SIZE, 32);

    if (_ES_GetTicketViews(&fd, tid, pviews, &count) != IPC_RESULT_OK) {
        return;
    }

    if (_ES_LaunchTitle(&fd, tid, pviews) != IPC_RESULT_OK) {
        return;
    }

    while (TRUE) {
        ;
    }
}

#define OSRoundUp32B(x) (((u32)(x) + 31) & ~31)

/* petari's field names for the 0x1C-byte OSExecParams (ogws names it WORD_0x0, WORD_0x4, ...) */
typedef struct ExecParams {
    BOOL valid;
    u32 restartCode;
    u32 bootDol;
    void* regionStart;
    void* regionEnd;
    BOOL argsUseDefault;
    void* argsAddr;
} ExecParams;

static OSExecParams* __OSExecParamsAddr : 0x800030F0;

static inline void __OSSetExecParams(const ExecParams* params, ExecParams* addr) {
    memcpy(addr, params, sizeof(ExecParams));
    __OSExecParamsAddr = (OSExecParams*)addr;
}

typedef struct {
    char date[16];
    u32 entry;
    u32 size;
    u32 rebootSize;
    u32 reserved2;

} ImgHeader;

static inline void ReadDisc(void* addr, s32 length, u32 offset) {
    DVDCommandBlock block;
    GXColor bg = {0, 0, 0, 0};
    GXColor fg = {255, 255, 255, 0};

    DVDReadAbsAsyncPrio(&block, addr, length, offset, NULL, 0);

    while (!(DVDGetCommandBlockStatus(&block) == DVD_STATE_IDLE)) {
        if (DVDGetCommandBlockStatus(&block) > 2 || DVDGetCommandBlockStatus(&block) < 0) {
            __OSReturnToMenu();
        }
    };
}

static u32 GetApploaderPosition(void) {
    static u32 apploaderPosition = 0;

    if (apploaderPosition) {
        return apploaderPosition;
    }

    if (__OSCurrentTGCOffset) {
        u32* tgcHeader;
        s32 apploaderOffsetInTGC;

        tgcHeader = OSAllocFromMEM1ArenaLo(64, 32);
        ReadDisc(tgcHeader, 64, (u32)(__OSCurrentTGCOffset >> 2));
        apploaderOffsetInTGC = *(s32*)((u32)tgcHeader + 56);
        apploaderPosition = (u32)((__OSCurrentTGCOffset + apploaderOffsetInTGC) >> 2);
    } else {
        apploaderPosition = (0x00002440 >> 2);
    }

    return apploaderPosition;
}

static ImgHeader* LoadApploader(void) {
    ImgHeader* header;

    header = OSAllocFromMEM1ArenaLo(sizeof(ImgHeader), 32);
    ReadDisc(header, sizeof(ImgHeader), GetApploaderPosition());
    ReadDisc((void*)0x81200000, (s32)OSRoundUp32B(header->size), GetApploaderPosition() + (u32)(sizeof(ImgHeader) >> 2));
    ICInvalidateRange((void*)0x81200000, OSRoundUp32B(header->size));

    return header;
}

typedef void (*AppInitFunc)(void (*report)(const char*, ...));
typedef BOOL (*AppGetNextFunc)(void**, u32*, u32*);
typedef void* (*AppGetEntryFunc)(void);

typedef void (*AppInterfaceFunc)(AppInitFunc*, AppGetNextFunc*, AppGetEntryFunc*);


#define NEWAPPLOADER_DATE "2004/02/01"

static BOOL IsNewApploader(ImgHeader* header) {
    if (strncmp((char*)header, NEWAPPLOADER_DATE, 10) > 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

static void* LoadDol(const ExecParams* params, AppInterfaceFunc getInterface) {
    AppInitFunc appInit;
    AppGetNextFunc appGetNext;
    AppGetEntryFunc appGetEntry;
    void* addr;
    u32 length;
    u32 offset;
    ExecParams* paramsWork;

    getInterface(&appInit, &appGetNext, &appGetEntry);
    paramsWork = OSAllocFromMEM1ArenaLo(sizeof(ExecParams), 1);
    __OSSetExecParams(params, paramsWork);
    appInit(OSReport);
    OSSetArenaLo(paramsWork);

    while (appGetNext(&addr, &length, &offset)) {
        ReadDisc(addr, (s32)length, (u32)(offset >> __DVDLayoutFormat));
    }

    return appGetEntry();
}

static void StartDol(const ExecParams* params, void* entry) {
    ExecParams* paramsWork;
    paramsWork = OSAllocFromMEM1ArenaLo(sizeof(ExecParams), 1);
    __OSSetExecParams(params, paramsWork);
    __PIRegs[0x024 / 4] = 0x00000004 | 0x00000001 | 2;
    OSDisableInterrupts();
    Run(entry);
}

#define BOOT_REGION_START 0x812fdff0
#define BOOT_REGION_END 0x812fdfec

/* FE10 (SDK Nov 2006) version: no partition type, no title id argument, no disk id update */
void __OSBootDolSimple(u32 doloffset, u32 restartCode, void* regionStart, void* regionEnd, BOOL argsUseDefault, s32 argc, char* argv[]) {
    ExecParams* params;
    void* dolEntry;
    ImgHeader* header;

    OSDisableInterrupts();

    params = OSAllocFromMEM1ArenaLo(sizeof(ExecParams), 1);

    params->valid = TRUE;
    params->restartCode = restartCode;
    params->regionStart = regionStart;
    params->regionEnd = regionEnd;

    params->argsUseDefault = argsUseDefault;
    if (!argsUseDefault) {
        params->argsAddr = OSAllocFromMEM1ArenaLo(0x2000, 1);
        PackArgs(params->argsAddr, argc, argv);
    }

    DVDInit();
    DVDSetAutoInvalidation(TRUE);
    DVDResume();

    Prepared = FALSE;
    __DVDPrepareResetAsync(Callback);

    __OSMaskInterrupts(0xFFFFFFF0u /* MEM | DSP | AI | EXI | PI (petari OS_INTERRUPTMASK_*) */);
    __OSUnmaskInterrupts(0x10u /* PI_ACR */);
    OSEnableInterrupts();

    while (Prepared != TRUE) {
    }

    __OSLaunchNextFirmware();

    header = LoadApploader();

    if (IsNewApploader(header)) {
        if (doloffset == 0xffffffff) {
            doloffset = GetApploaderPosition() + ((sizeof(ImgHeader) + header->size) >> 2);
        }

        params->bootDol = doloffset;
        dolEntry = LoadDol(params, (AppInterfaceFunc)header->entry);
        StartDol(params, dolEntry);
    } else {
        *(void**)BOOT_REGION_START = regionStart;
        *(void**)BOOT_REGION_END = regionEnd;
        *(u8*)0x800030E2 = 1;

        ReadDisc((void*)0x81330000, (s32)OSRoundUp32B(header->rebootSize), (u32)(GetApploaderPosition() + ((sizeof(ImgHeader) + header->size) >> 2)));
        ICInvalidateRange((void*)0x81330000, OSRoundUp32B(header->rebootSize));
        OSDisableInterrupts();
        ICFlashInvalidate();
        Run((void*)0x81330000);
    }
}

void __OSBootDol(u32 doloffset, u32 restartCode, char* const argv[]) {
    char doloffInString[20];
    s32 argvlen;
    char** argvToPass;
    s32 i;
    void* saveStart;
    void* saveEnd;

    OSGetSaveRegion(&saveStart, &saveEnd);
    sprintf(doloffInString, "%d", doloffset);

    argvlen = 0;
    if (argv) {
        while (argv[argvlen]) {
            argvlen++;
        }
    }

    argvlen += 1;
    argvToPass = OSAllocFromMEM1ArenaLo((argvlen + 1) * sizeof(char*), 1);
    argvToPass[0] = doloffInString;

    for (i = 1; i < argvlen; i++) {
        argvToPass[i] = argv[i - 1];
    }

    __OSBootDolSimple(0xffffffff, restartCode, saveStart, saveEnd, FALSE, argvlen, argvToPass);
}

/**
 * These were actually re(?)implemented in NANDCore/OSExec according to BBA
 */

static s32 _ES_InitLib(s32* fd) {
    s32 result;

    // Had to remove fd initialization to match __OSLaunchMenu
    // *fd = -1;

    result = IPC_RESULT_OK;

    *fd = IOS_Open("/dev/es", IPC_OPEN_NONE);
    if (*fd < 0) {
        result = *fd;
    }

    return result;
}

static s32 _ES_GetTitleId(s32* fd, u64* tidOut) {
    s32 result;
    u8 tidWork[256] ALIGN(32);
    u8 vectorWork[32] ALIGN(32);
    IPCIOVector* pVectors = (IPCIOVector*)vectorWork;
    u64* pTid = (u64*)tidWork;

    // Cast is necessary
    if (*fd < 0 || tidOut == ((void*)NULL)) {
        return -0x3F9;
    }

    pVectors[0].base = pTid;
    pVectors[0].length = sizeof(u64);

    result = IOS_Ioctlv(*fd, ES_IOCTLV_GET_TITLE_ID, 0, 1, pVectors);
    if (result == IPC_RESULT_OK) {
        *tidOut = *pTid;
    }

    return result;
}

static s32 _ES_GetTicketViews(s32* fd, u64 tid, void* pViews, u32* count) {
    s32 result;
    // TODO(kiwi) Hacky solution
    u8 work[0x120] ALIGN(32);
    IPCIOVector* pVectors = (IPCIOVector*)(work + 0x0);
    u64* pTid = (u64*)(work + 0x20);
    u32* pCount = (u32*)(work + 0x40);

    // Cast is necessary
    if (*fd < 0 || count == ((void*)NULL)) {
        return -0x3F9;
    }

    if ((u32)pViews % 32 != 0) {
        return -0x3F9;
    }

    *pTid = tid;

    // NULL views ptr = get num views
    if (pViews == (void*)NULL) {
        pVectors[0].base = pTid;
        pVectors[0].length = sizeof(u64);
        pVectors[1].base = pCount;
        pVectors[1].length = sizeof(u32);

        result =
            IOS_Ioctlv(*fd, ES_IOCTLV_GET_NUM_TICKET_VIEWS, 1, 1, pVectors);
        if (result == IPC_RESULT_OK) {
            *count = *pCount;
        }

        return result;
    }

    if (*count == 0) {
        return -0x3F9;
    }

    *pCount = *count;

    pVectors[0].base = pTid;
    pVectors[0].length = sizeof(u64);
    pVectors[1].base = pCount;
    pVectors[1].length = sizeof(u32);
    pVectors[2].base = pViews;
    pVectors[2].length = *count * TICKET_VIEW_SIZE;
    return IOS_Ioctlv(*fd, ES_IOCTLV_GET_TICKET_VIEWS, 2, 1, pVectors);
}

static s32 _ES_LaunchTitle(s32* fd, u64 tid, void* pViews) {
    // TODO(kiwi) Hacky solution
    u8 tidWork[256] ALIGN(32);
    u8 vectorWork[32] ALIGN(32);
    IPCIOVector* pVectors = (IPCIOVector*)vectorWork;
    u64* pTid = (u64*)tidWork;

    if (*fd < 0) {
        return -0x3F9;
    }

    if ((u32)pViews % 32 != 0) {
        return -0x3F9;
    }

    *pTid = tid;

    pVectors[0].base = pTid;
    pVectors[0].length = sizeof(u64);
    pVectors[1].base = pViews;
    pVectors[1].length = TICKET_VIEW_SIZE;

    return IOS_IoctlvReboot(*fd, ES_IOCTLV_LAUNCH_TITLE, 2, 0, pVectors);
}

static s32 _ES_CloseLib(s32* fd) {
    s32 result = IPC_RESULT_OK;

    if (*fd >= 0 && (result = IOS_Close(*fd)) == IPC_RESULT_OK) {
        *fd = -1;
    }

    return result;
}
