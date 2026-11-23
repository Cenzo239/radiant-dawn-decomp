/* Event trigger condition for kind 0x13 entries (from round 12's near miss; names guessed).
   Same declarations as fn_800A04C8.cpp. */
#include "game/rD_8008E3B4/evflags.h"

extern "C" {

typedef struct EvFilter {
    s16 a;
    s16 b;
    s16 c;
    s16 d;
    s16 d2;
    u8 e;    /* 0xA */
} EvFilter;
extern EvFilter lbl_803E50B0;

extern u8 lbl_80381BD4[];
extern u8 lbl_80381B80[];
extern char lbl_80364B30[];
extern u8 lbl_803C8DA0[];
extern u32 lbl_804CB700;
typedef struct BattleCur {
    u8* a;      /* 0x00 */
    u8* b;      /* 0x04 */
    u8 pad8[0x18];
} BattleCur;
extern BattleCur lbl_803CA870;
#if TARGET_PC
FE10_PROTO void * fn_800C357C(void);
#else
int fn_800C357C(void);
#endif
void fn_80081A90(void* p);
int fn_800A0B1C(u8* p);
void* fn_801190C8(void* a, void* b, int c);
void* fn_80076F54(void* p);
void fn_8014BED4(void* ctx, void* p);
void* fn_8010B1D8(void* x);
struct RunBits { u32 pad : 29; u32 b4 : 1; u32 b2 : 1; u32 b1 : 1; };
u8* fn_800C3558(void);
u8* fn_800C3BC8(void* p);
void* fn_80081194(void* cls, void* parent);
char* fn_8009D948(void* p, int ofs);
int fn_800A0330(u8* p);
void fn_801D0D58(void* ctx, void* p);
int fn_801D0E18(void* ctx);
#if TARGET_PC
FE10_PROTO void fn_801D0C48(void* ctx, p32arg);
#else
void fn_801D0C48(void* ctx, int v);
#endif
int fn_801D0C88(void* ctx, void* v);
void* fn_8010B1B4(int v);

typedef int (*EvCond)(u8*);
typedef struct EvProc {
    u8 pad0[0x30];
    u8* cur;     /* 0x30 */
    int kind;    /* 0x34 */
    EvCond cond; /* 0x38 */
} EvProc;

#pragma push
#pragma use_lmw_stmw on
/* The current unit's person data; the accessor ranks id like the original. */
static inline void* curPid() { return *(void**)(lbl_803CA870.a + 0xec); }

int fn_800A15F4(u8* p)
{
    void* id;
    char* name = fn_8009D948(p, *(u16*)(p + 0x1a));
    if (name != NULL && *name != 0) {
        if (flagHas(&lbl_803CAB38, (const char*)name)) {
            if (flagGet(&lbl_803CAB38, (const char*)name)) {
                return 0;
            }
        } else if (fn_80076F54(name)) {
            fn_801D0C48(fn_800C3558(), lbl_803E50B0.a);
            fn_801D0C48(fn_800C3558(), lbl_803E50B0.b);
            if (!fn_801D0C88(fn_800C3558(), name)) {
                return 0;
            }
        } else {
            return 0;
        }
    }
    if (*(s16*)(p + 0x16) >= 0 && lbl_803E50B0.a != *(s16*)(p + 0x16)) {
        return 0;
    }
    if (*(s16*)(p + 0x18) >= 0 && lbl_803E50B0.b != *(s16*)(p + 0x18)) {
        return 0;
    }
    id = curPid();
    if (id != (void*)fn_8010B1D8(fn_8009D948(p, *(u16*)(p + 0x14)))) {
        return 0;
    }
    return 1;
}

#pragma pop
}
