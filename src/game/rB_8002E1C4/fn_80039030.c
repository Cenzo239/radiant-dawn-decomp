#include "game/rB_8002E1C4/types.h"

extern const char lbl_80361390[0x200];
void fn_80084F0C(const char* name);

/* load "E_NoticeFrame" */
int fn_80039030(void)
{
    fn_80084F0C(lbl_80361390 + 0x1bc);
    return 0;
}
