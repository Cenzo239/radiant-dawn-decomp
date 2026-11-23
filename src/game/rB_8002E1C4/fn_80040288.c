#include "game/rB_8002E1C4/types.h"

extern char lbl_80379ECC[0x17];
extern char lbl_804CA098[5];
void fn_801C6EAC(const char* a, const char* b, void* out);
void fn_8023F4EC(void* p);

void fn_80040288(void)
{
    u8 buf[0x68];
    fn_801C6EAC(lbl_80379ECC, lbl_804CA098, buf);
    fn_8023F4EC(buf);
}
