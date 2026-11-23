#include <revolution/WUD.h>
#include <revolution/WUD/debug_msg.h>

// Release build: the debug print of WUD is an empty vararg function
// (FE10: 0x8034553C, after WUDHidHost.c).
void WUD_DEBUGPrint(const char* pFmt, ...) {
#pragma unused(pFmt)
}
