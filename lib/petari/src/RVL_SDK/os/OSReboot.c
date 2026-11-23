#include "revolution/os.h"

// FE10 (Nov 2006 SDK): no partition type hand-over yet (0x8031E010)
void __OSReboot(u32 resetCode, u32 bootDol) {
    char* argvToPass;
    OSDisableInterrupts();
    OSSetArenaLo((void*)0x81280000);
    OSSetArenaHi((void*)0x812F0000);
    argvToPass = NULL;
    __OSBootDol(bootDol, resetCode | 0x80000000, &argvToPass);
}
