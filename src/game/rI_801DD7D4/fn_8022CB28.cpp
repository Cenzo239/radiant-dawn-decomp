#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/rlist.h"
#pragma auto_inline off
extern "C" {
void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E720(f32);
#if TARGET_PC
FE10_PROTO void fn_8007E174(p32arg, u32);
#else
void fn_8007E174(int, u32);
#endif
int fn_800CB0FC(f32, int);
typedef void (RObj::*MF)(void*);
struct FnT { MF f; void* arg; };
static inline FnT forEach2(LNode* n, LNode* e, FnT f) {
    while (n != e) {
        (n->val->*f.f)(f.arg);
        n = n->next;
    }
    return f;
}
const char* fn_800D0864(const char*);
int fn_800CA3DC(f32, const char*, int);
void fn_800CB278(int, int, int, const char*, ...);
void fn_801DA230(int, int, int);
void fn_801DA2C0(int, int, int);
extern const char* lbl_803904A8[];
extern char lbl_80372034[];
extern MF lbl_803904B8;
struct KVX { virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c(); virtual void v30(); virtual int v34(); virtual int v38(); virtual int v3c(); virtual void v40(); virtual int v44(); };
struct KV { virtual void v08(); virtual void v0c(); virtual KVX* v10(int, int); virtual void v14(); virtual void v18(void*); virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c(); virtual void v30(); virtual int v34(); virtual void v38(); virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c(); virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c(void*); };
struct KL { u8 p[0x40]; s16 x40, x42, x44; };
struct KB { void* vt; u8 p4[0x1a]; s16 x1e, x20; u8 p22[0x16]; u32 flags; u8 p3c[8]; LNode x44; u8 p50[0x24]; KL* x74; };
struct KX { void* vt; u8 p4[0x58]; f32 x5c; };
#define SCALE(k) fn_8007E154(); fn_8007E720(k); fn_8007E164();
#define FLAGS(o) fn_8007E154(); fn_8007E174(0, (u16)(o->flags | 3)); fn_8007E164();
void fn_8022CB28(KB* o, void* a) {
/*P*/
    int x0;
    s16 w2;
    int yo;
    const char** tp;
    int x;
    int a3;
    int col;
    int y0;
    int y1;
    int y2;
    int ly;
    int i;
    const char* s;
    s16 w;
    const char* s2;
    KX* k;
    int a0;
    int a1;
    int a2;
    int y;
/*E*/
    ((KV*)o)->v5c(a);
    ((KV*)o)->v18(a);
    x0 = o->x1e;
    ly = o->x20;
    yo = (0x20 - fn_800CB0FC(1.0f, -1)) >> 1;
    x = x0 - 0x5f;
    tp = lbl_803904A8;
    y0 = yo + 0x78;
    y1 = yo + 0x99;
    y2 = yo + 0xba;
    for (i = 0; i < 4; i++, tp++) {
        if (i < 1) {
            s = fn_800D0864(*tp);
            w = (s16)fn_800CA3DC(1.0f, s, -1);
            {
                s16 c = ((KV*)o)->v34();
                col = 0;
                if (i == c) col = 0x1d;
            }
            FLAGS(o)
            SCALE(-0.5f)
            fn_800CB278((s16)(x + ((0x5f - w) >> 1)), (s16)(ly + yo), col, lbl_80372034, s);
            SCALE(0.5f)
            ly = (s16)(ly + 0x1c);
        } else {
            s2 = fn_800D0864(*tp);
            w2 = (s16)fn_800CA3DC(1.0f, s2, -1);
            SCALE(-1.5f)
            switch (i) {
            case 1:
                ly = 0x78;
                fn_801DA230((s16)x, 0x78, 0x10);
                FLAGS(o)
                SCALE(-0.5f)
                fn_800CB278((s16)(x + ((0x66 - w2) >> 1)), (s16)y0, 1, lbl_80372034, s2);
                SCALE(0.5f)
                break;
            case 2:
                ly = 0x99;
                fn_801DA230((s16)x, 0x99, 0x10);
                FLAGS(o)
                SCALE(-0.5f)
                fn_800CB278((s16)(x + ((0x66 - w2) >> 1)), (s16)y1, 1, lbl_80372034, s2);
                SCALE(0.5f)
                break;
            case 3:
                ly = 0xba;
                fn_801DA2C0((s16)x, 0xba, 0x10);
                FLAGS(o)
                SCALE(-0.5f)
                fn_800CB278((s16)(x + ((0x66 - w2) >> 1)), (s16)y2, 6, lbl_80372034, s2);
                SCALE(0.5f)
                break;
            }
            SCALE(1.5f)
        }
    }
    k = (KX*)((KV*)o)->v10(0x81, 0);
    if (k != NULL) {
        a0 = ((KVX*)k)->v44();
        a1 = ((KVX*)k)->v3c();
        a2 = ((KVX*)k)->v38();
        a3 = (int)k->x5c;
        {
            int m = ((KVX*)k)->v34();
            KL* l = o->x74;
            l->x40 = a0 * m;
            l->x42 = a1 * m;
            l->x44 = a2 * m - a3;
        }
    }
    {
        FnT ft;
        ft.f = lbl_803904B8;
        ft.arg = a;
        forEach2(o->x44.next, &o->x44, ft);
    }
}
}
