#include "game/rS_8023FD30/types.h"

/* Window/menu condition handlers working on the global at lbl_803CA870. */
struct MenuState {
    s32 unit;
    u8 pad04[0x12];
    s8 s16;
    u8 pad17[0x130 - 0x17];
};

extern "C" {

extern MenuState lbl_803CA870;
extern s32 lbl_803E7320[];

#if TARGET_PC
FE10_PROTO int fn_801212C0(p32arg);
FE10_PROTO int fn_801211B0(p32arg);
#else
int fn_801212C0(s32);
int fn_801211B0(s32);
#endif
int fn_80121080(s32);
int fn_80120F50(s32);
#if TARGET_PC
FE10_PROTO int fn_80120E6C(p32arg);
FE10_PROTO int fn_80120E0C(p32arg);
FE10_PROTO int fn_80120DAC(p32arg);
FE10_PROTO int fn_80120D2C(p32arg);
FE10_PROTO int fn_80120CAC(p32arg);
FE10_PROTO int fn_80120CA0(p32arg);
FE10_PROTO void fn_8003B244(p32arg);
FE10_PROTO void fn_8003B1F0(p32arg);
FE10_PROTO void fn_8003B19C(p32arg);
FE10_PROTO void fn_8003B148(p32arg);
FE10_PROTO void fn_8003B0F4(p32arg);
#else
int fn_80120E6C(s32);
int fn_80120E0C(s32);
int fn_80120DAC(s32);
int fn_80120D2C(s32);
int fn_80120CAC(s32);
int fn_80120CA0(s32);
void fn_8003B244(s32);
void fn_8003B1F0(s32);
void fn_8003B19C(s32);
void fn_8003B148(s32);
void fn_8003B0F4(s32);
#endif
void fn_800453B4(MenuState*, u8);

#define OPEN(addr, query) \
    int fn_##addr(void) { \
        fn_800453B4(&lbl_803CA870, query(lbl_803CA870.unit)); \
        return 6; \
    }

#define COND(addr, test, act) \
    int fn_##addr(void) { \
        int r; \
        if (lbl_803CA870.s16) { \
            return 3; \
        } \
        if (test(lbl_803CA870.unit) == 0) { \
            return 3; \
        } \
        act(lbl_803CA870.unit); \
        r = 3; \
        if (lbl_803E7320[0] != 0) { \
            r = 0; \
        } \
        return r; \
    }

OPEN(8023FD30, fn_801212C0)
COND(8023FD70, fn_80120E0C, fn_8003B244)
OPEN(8023FE00, fn_801211B0)
COND(8023FE40, fn_80120DAC, fn_8003B1F0)
OPEN(8023FED0, fn_80121080)
COND(8023FF10, fn_80120D2C, fn_8003B19C)
OPEN(8023FFA0, fn_80120F50)
COND(8023FFE0, fn_80120CAC, fn_8003B148)
OPEN(80240070, fn_80120E6C)
COND(802400B0, fn_80120CA0, fn_8003B0F4)

int fn_80240140(u8* p) {
    s32* q = (s32*)(p + 0x10);
    int i = 0;
    while (*q != 0 && i < 7) {
        q++;
        i++;
    }
    return i;
}

#if TARGET_PC
FE10_PROTO int fn_80291188(p32arg, p32arg);
#else
int fn_80291188(s32, s32);
#endif

int fn_8024016C(u8* p, s32 name) {
    int found = 0;
    int i = 0;
    s32* q = (s32*)(p + 0x10);
    while (*q != 0 && i < 7) {
        if (fn_80291188(*q, name) == 0) {
            found = 1;
            break;
        }
        q++;
        i++;
    }
    return found;
}

}
