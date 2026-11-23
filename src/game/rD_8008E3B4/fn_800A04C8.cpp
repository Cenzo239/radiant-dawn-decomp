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

int fn_800A04C8(void* parent, int c, int a, int b)
{
    EvProc* q;
    lbl_803E50B0.a = (s8)a;
    lbl_803E50B0.b = (s8)b;
    lbl_803E50B0.c = c;
    lbl_803E50B0.e = 1;
    if (!evAny5()) {
        return 0;
    }
    lbl_803E50B0.e = 0;
    q = (EvProc*)fn_80081194(lbl_80381BD4, parent);
    q->kind = 5;
    q->cond = fn_800A0330;
    return 1;
}

BOOL fn_800A05B0(int c, int a, int b)
{
    lbl_803E50B0.a = (s8)a;
    lbl_803E50B0.b = (s8)b;
    lbl_803E50B0.c = c;
    lbl_803E50B0.e = 1;
    return evAny5();
}

int fn_800A0644(int a, int b)
{
    lbl_803E50B0.a = (s8)a;
    lbl_803E50B0.b = (s8)b;
    lbl_803E50B0.c = 0;
    lbl_803E50B0.e = 1;
    if (evAny5()) {
        return lbl_803E50B0.c;
    }
    return -1;
}

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

char* fn_800A074C(int n)
{
    u8* p = evNth(n);
    return fn_8009D948(p, *(u16*)(p + 0x14));
}

BOOL fn_800A07B8(int n)
{
    /*P*/
    u32 h;
    int i;
    FlagTable* q;
    const char* name;
    BOOL r;
    /*E*/
    u8* p = evNth(n);
    name = fn_8009D948(p, *(u16*)(p + 0x16));
    FLAG_GET_R(r, q, name, h, i);
    return r;
}

BOOL fn_800A08F0(int n)
{
    u8* p = evNth(n);
    lbl_803E50B0.e = 1;
    fn_801D0D58(fn_800C3558(), p);
    return fn_801D0E18(fn_800C3558()) != 0;
}

#pragma push
#pragma use_lmw_stmw on

int fn_800A0BE8(u8* a, u8* b, int c, void* parent)
{
    u8* p;
    BOOL found;
    void* s;
    if (a == NULL || b == NULL) {
        return 0;
    }
    lbl_803E50B0.d = *(s16*)(a + 0x1c);
    lbl_803E50B0.d2 = *(s16*)(b + 0x1c);
    lbl_803E50B0.a = c;
    lbl_803E50B0.e = 1;
    p = fn_800C3BC8(NULL);
    while (p != NULL) {
        if ((int)p[0xc] == 0xd && fn_800A0B1C(p)) {
            found = 1;
            goto done;
        }
        p = fn_800C3BC8(p);
    }
    found = 0;
done:
    if (found) {
        EvProc* q;
        lbl_803E50B0.e = 0;
        q = (EvProc*)fn_80081194(lbl_80381BD4, parent);
        q->kind = 0xd;
        q->cond = fn_800A0B1C;
        return 1;
    }
    s = fn_801190C8(a, b, c);
    if (fn_80076F54(s)) {
        fn_8014BED4(s, parent);
        return 1;
    }
    return 0;
}

int fn_800A0D20(u8* p)
{
    /*P*/
    u32 h;
    int i;
    FlagTable* q;
    const char* name;
    BOOL r;
    /*E*/
    if (lbl_803E50B0.a >= 0 && lbl_803E50B0.a != *(s16*)(p + 0x14)) {
        return 0;
    }
    if (lbl_803E50B0.b >= 0 && lbl_803E50B0.b != *(s16*)(p + 0x16)) {
        return 0;
    }
    if (lbl_803E50B0.c != 0 && lbl_803E50B0.c != *(s16*)(p + 0x18)) {
        return 0;
    }
    name = fn_8009D948(p, *(u16*)(p + 0x1a));
    FLAG_GET_R(r, q, name, h, i);
    if (r) {
        return 0;
    }
    lbl_803E50B0.a = *(s16*)(p + 0x14);
    lbl_803E50B0.b = *(s16*)(p + 0x16);
    lbl_803E50B0.c = *(s16*)(p + 0x18);
    fn_801D0D58(fn_800C3558(), p);
    return fn_801D0E18(fn_800C3558()) != 0;
}
#pragma pop

BOOL fn_800A0ED4(int c, int a, int b)
{
    u8* p;
    lbl_803E50B0.a = (s8)a;
    lbl_803E50B0.b = (s8)b;
    lbl_803E50B0.c = c;
    lbl_803E50B0.e = 1;
    p = fn_800C3BC8(NULL);
    while (p != NULL) {
        if ((int)p[0xc] == 5 && fn_800A0D20(p)) {
            return 1;
        }
        p = fn_800C3BC8(p);
    }
    return 0;
}

#pragma push
#pragma use_lmw_stmw on
int fn_800A0F68(u8* p)
{
    /*P*/
    u32 h;
    int i;
    const char* name;
    u8* ub;
    BOOL r;
    u8* ua;
    void* id;
    void* id4;
    void* id3;
    void* id2;
    FlagTable* q;
    char* s2;
    char* s1;
/*E*/
    name = fn_8009D948(p, *(u16*)(p + 0x1a));
    FLAG_GET_R(r, q, name, h, i);
    if (r) {
        return 0;
    }
    ua = lbl_803CA870.a;
    ub = lbl_803CA870.b;
    s1 = fn_8009D948(p, *(u16*)(p + 0x14));
    s2 = fn_8009D948(p, *(u16*)(p + 0x16));
    if (*s1 != 0 && (id = *(void**)(ua + 0xec), fn_8010B1D8(s1) != id) &&
        (*(s16*)(p + 0x18) == 0 || (*s2 != 0 && (id2 = *(void**)(ua + 0xec), fn_8010B1D8(s2) != id2)))) {
        return 0;
    }
    if (*s2 != 0 && (id3 = *(void**)(ub + 0xec), fn_8010B1D8(s2) != id3) &&
        (*(s16*)(p + 0x18) == 0 || (*s1 != 0 && (id4 = *(void**)(ub + 0xec), fn_8010B1D8(s1) != id4)))) {
        return 0;
    }
    return 1;
}
#pragma pop

#pragma push
#pragma use_lmw_stmw on
int fn_800A1274(u8* p)
{
    /*P*/
    void* x;
    void* y;
    void* b;
    u32 h;
    const char* name;
    int i;
    FlagTable* q;
    BOOL r;
    void* z;
    void* a;
    void* c;
    u8* u;
    u8* v;
/*E*/
    name = fn_8009D948(p, *(u16*)(p + 0x1c));
    FLAG_GET_R(r, q, name, h, i);
    if (r) {
        return 0;
    }
    a = NULL;
    b = NULL;
    c = NULL;
    if (fn_8009D948(p, *(u16*)(p + 0x14))) {
        a = fn_8010B1D8(fn_8009D948(p, *(u16*)(p + 0x14)));
    }
    if (fn_8009D948(p, *(u16*)(p + 0x16))) {
        b = fn_8010B1D8(fn_8009D948(p, *(u16*)(p + 0x16)));
    }
    if (fn_8009D948(p, *(u16*)(p + 0x18))) {
        c = fn_8010B1D8(fn_8009D948(p, *(u16*)(p + 0x18)));
    }
    u = lbl_803CA870.a;
    if (*(u8**)(u + 0xf8) != NULL) {
        x = *(void**)(u + 0xec);
        y = *(void**)(lbl_803CA870.b + 0xec);
        z = *(void**)(*(u8**)(u + 0xf8) + 0xec);
    } else {
        v = lbl_803CA870.b;
        if (*(u8**)(v + 0xf8) != NULL) {
            x = *(void**)(v + 0xec);
            y = *(void**)(u + 0xec);
            z = *(void**)(*(u8**)(v + 0xf8) + 0xec);
        }
    }
    if ((a == NULL || a == x) && (b == NULL || b == y) && (c == NULL || c == z)) {
        return 1;
    }
    if (*(s16*)(p + 0x1a) != 0 && (a == NULL || a == y) && (b == NULL || b == x) &&
        (c == NULL || c == z)) {
        return 1;
    }
    return 0;
}

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


BOOL fn_800A1954(int a, int b)
{
    lbl_803E50B0.a = (s8)a;
    lbl_803E50B0.e = 0;
    lbl_803E50B0.b = (s8)b;
    return evAny13();
}

#pragma push
#pragma use_lmw_stmw on
#pragma auto_inline off
int fn_800A19E4(u8* p)
{
    char* name = fn_8009D948(p, *(u16*)(p + 0x16));
    char* s;
    if (name != NULL && *name != 0) {
        if (flagHas(&lbl_803CAB38, (const char*)name)) {
            if (flagGet(&lbl_803CAB38, (const char*)name)) {
                return 0;
            }
        } else if (!fn_801D0C88(fn_800C3558(), name)) {
            return 0;
        }
    }
    s = fn_8009D948(p, *(u16*)(p + 0x14));
    if (*s != 0) {
        void* id = fn_8010B1D8(s);
        if (fn_8010B1B4(lbl_803E50B0.d) != id) {
            return 0;
        }
    }
    return 1;
}
#pragma pop

int fn_800A1BC8(u8* u, void* parent)
{
    u8* p;
    BOOL found;
    EvProc* q;
    lbl_803E50B0.e = 0;
    lbl_803E50B0.d = *(s16*)(u + 0x1c);
    p = fn_800C3BC8(NULL);
    while (p != NULL) {
        if ((int)p[0xc] == 0x14 && fn_800A19E4(p)) {
            found = 1;
            goto done;
        }
        p = fn_800C3BC8(p);
    }
    found = 0;
done:
    if (!found) {
        return 0;
    }
    lbl_803E50B0.e = 0;
    lbl_803E50B0.d = *(s16*)(u + 0x1c);
    q = (EvProc*)fn_80081194(lbl_80381BD4, parent);
    q->kind = 0x14;
    q->cond = fn_800A19E4;
    return 1;
}

}
