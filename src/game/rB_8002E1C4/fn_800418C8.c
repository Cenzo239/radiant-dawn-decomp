#include "game/rB_8002E1C4/types.h"

typedef struct RangeState { void* unit; u32 x4; u8 pad8[0x13 - 8]; u8 x13; u8 x14; u8 pad15[0x130 - 0x15]; } RangeState;
extern RangeState lbl_803CA870;
extern char lbl_80379EF8[0x10];

char* fn_800418C8(void)
{
    return lbl_80379EF8;
}
