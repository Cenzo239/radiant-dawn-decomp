/* EQUIVALENT (register-only, round 19): fn_800A1848 at regs level (6 words); round 12 fragment made self-contained. */
/* Event lookups: 0x800A04C8.. */
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
int fn_800C357C(void);
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
void fn_801D0C48(void* ctx, int v);
int fn_801D0C88(void* ctx, void* v);
void* fn_8010B1B4(int v);

typedef int (*EvCond)(u8*);
typedef struct EvProc {
    u8 pad0[0x30];
    u8* cur;     /* 0x30 */
    int kind;    /* 0x34 */
    EvCond cond; /* 0x38 */
} EvProc;

static inline BOOL evAny5(void)
{
    u8* p = fn_800C3BC8(NULL);
    while (p != NULL) {
        if ((int)p[0xc] == 5 && fn_800A0330(p)) {
            return 1;
        }
        p = fn_800C3BC8(p);
    }
    return 0;
}
int fn_800A04C8(void* parent, int c, int a, int b);

BOOL fn_800A05B0(int c, int a, int b);

int fn_800A0644(int a, int b);


static inline u8* evNth(int n)
{
    u8* p = fn_800C3BC8(NULL);
    int i = 0;
    while (p != NULL) {
        if ((int)p[0xc] == 0xe) {
            if (i++ == n) {
                break;
            }
        }
        p = fn_800C3BC8(p);
    }
    return p;
}
char* fn_800A074C(int n);

BOOL fn_800A07B8(int n);

BOOL fn_800A08F0(int n);


#pragma push
#pragma use_lmw_stmw on

int fn_800A0BE8(u8* a, u8* b, int c, void* parent);

int fn_800A0D20(u8* p);

#pragma pop

BOOL fn_800A0ED4(int c, int a, int b);


#pragma push
#pragma use_lmw_stmw on

int fn_800A0F68(u8* p);

#pragma pop

#pragma push
#pragma use_lmw_stmw on

int fn_800A1274(u8* p);


#pragma pop

int fn_800A15F4(u8* p);

static inline BOOL evAny13(void)
{
    u8* p = fn_800C3BC8(NULL);
    while (p != NULL) {
        if ((int)p[0xc] == 0x13 && fn_800A15F4(p)) {
            return 1;
        }
        p = fn_800C3BC8(p);
    }
    return 0;
}

static inline void evSet13(s8 a, s8 b)
{
    lbl_803E50B0.a = a;
    lbl_803E50B0.e = 0;
    lbl_803E50B0.b = b;
}

static inline void evSet13x(s8 a, s8 b)
{
    lbl_803E50B0.e = 0;
    lbl_803E50B0.a = a;
    lbl_803E50B0.b = b;
}
BOOL fn_800A1954(int a, int b);


#pragma push
#pragma use_lmw_stmw on
#pragma auto_inline off

int fn_800A19E4(u8* p);

#pragma pop

int fn_800A1BC8(u8* u, void* parent);


}

/* ---- from build/tmp/r19hpbs/frag_da1848.cpp ---- */
extern "C" {
/* fn_800A1848 (from ../fn_800A04C8.cpp): 6 of 67 words: volatile registers for the first three stores (want s8 value r6, base r7, zero r9). */
int fn_800A1848(void* parent, int a, int b)
{
    EvProc* q;
    evSet13(a, b);
    if (!evAny13()) {
        return 0;
    }
    evSet13x(a, b);
    q = (EvProc*)fn_80081194(lbl_80381BD4, parent);
    q->kind = 0x13;
    q->cond = fn_800A15F4;
    return 1;
}
}
