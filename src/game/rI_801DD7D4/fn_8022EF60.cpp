#include "game/rI_801DD7D4/types.h"
extern "C" {
typedef struct C4 { u8 r, g, b, a; } C4;
void* fn_801E5640(void*, int, int);
#if TARGET_PC
FE10_PROTO ptr32<const C4> fn_8021CD58(void*);
#else
const C4* fn_8021CD58(void*);
#endif
void* fn_80081194(void*, void*);
void* fn_80079150(u32);
void fn_8021A47C(void*, u8, int);
void fn_8021B14C(void*, s8);
void fn_80253EE4(const char*, f32);
void fn_80083DC4(void*, int);
#if TARGET_PC
FE10_PROTO ptr32<void> fn_802172F8(void*);
#else
void* fn_802172F8(void*);
#endif
void fn_802167C8(void*, int, int, int, int, int, int);
void fn_80111B34(void*);
void fn_801E5448(void*, void*);
extern char lbl_80390AE8[];
extern u8 lbl_80390AB0[], lbl_8038F9A0[];
struct PS { u8 p[0x30]; s8 x30; u8 x31, x32, x33, x34; u8 p2[3]; void* x38; void* x3c; };
void* fn_80232428(void* o) {
    void* a = fn_801E5640(o, 0xe, 0);
    void* b = fn_801E5640(o, 3, 0);
    void* c = fn_801E5640(o, 0xb, 0);
    C4 col = *fn_8021CD58(a);
    PS* p = (PS*)fn_80081194(lbl_80390AB0, o);
    p->x30 = 0;
    p->x31 = col.r;
    p->x32 = col.g;
    p->x33 = col.b;
    p->x34 = col.a;
    p->x38 = b;
    p->x3c = c;
    return p;
}
struct V { virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38(int); };
struct WA { void* vt; int rc; s16 x8; u8 p[0x1e]; s16 x28; u8 p2[0x46]; u8 x70[0x28]; void* x98; int x9c; };
struct PO { u8 p[0x68]; void* x68; WA* x6c; };
void fn_8022EF60(PO* o) {
    void* a = o->x68;
    WA* w = (WA*)fn_80079150(0xa0);
    if (w) {
        a = fn_802172F8(a);
        fn_802167C8(w, 0x134, 0x66, 0x160, 0xda, 0x212, 1);
        w->vt = lbl_8038F9A0;
        fn_80111B34(w->x70);
        w->x98 = a;
        w->x9c = 0;
        ((V*)w)->v2c();
    }
    o->x6c = w;
    if (w) w->rc++;
    o->x6c->x8 = 1;
    o->x6c->x28 = 8;
    ((V*)o->x6c)->v38(0);
    fn_801E5448(o, o->x6c);
}

#pragma pool_strings on
const char* dummy1(int i) {
    switch (i) {
    case 0: return "";
    case 1: return "MJID_FSHOP";
    case 2: return "RID_BASE_SHOP_TALK_CHIP";
    case 3: return "SFX_SYS_MISS1";
    case 4: return "SFX_SYS_SELECT1";
    case 5: return "SFX_SYS_CANCEL1";
    case 6: return "SFX_SYS_MSG_OK1";
    }
    return 0;
}
void* fn_8010B228(const char*);
extern void** lbl_804CB814;
extern u8 lbl_803CAB38[];
#if TARGET_PC
FE10_PROTO int fn_80231968(void*, ptr32<const void>);
#else
int fn_80231968(void*, void*);
#endif
int fn_80060754(void*);
struct Cv { int n; struct It* a; };
Cv* fn_801059B0(void);
void* fn_80110D38(void*);
struct It { void* x0; u8 p[1]; u8 x5a : 2; u8 x5b : 1; u8 x5c : 5; };
struct Un { u8 p[0xe8]; Un* next; };
void fn_802319E8(void) {
        Un* nx;
    int off;
    void* k;
    int i;
    Un* u;
    k = fn_8010B228("IID_COIN");
    for (u = (Un*)lbl_804CB814[0]; u; u = nx) {
        nx = u->next;
        if (fn_80231968(u, k)) return;
    }
    for (u = (Un*)lbl_804CB814[0xf]; u; u = nx) {
        nx = u->next;
        if (fn_80231968(u, k)) return;
    }
    if (fn_80060754(lbl_803CAB38)) {
        i = 0;
        off = 0;
        for (; i < fn_801059B0()->n; i++) {
            It* e = (It*)((u8*)fn_801059B0()->a + off);
            if (e && e->x0 && !e->x5b && k == e->x0) {
                fn_80110D38(e);
                return;
            }
            off += 0x28;
        }
    }
}
struct W2 { u8 p[0x8]; s16 x8; s16 xa, xc, xe, x10; u8 p2[0x16]; s16 x28; };
struct P2 { u8 p[0x28]; s16 x28; u8 p2[6]; u8 x30; u8 x31; u8 x32; u8 p3[5]; struct { u8 p[0x4c]; W2* x4c[1]; }* x38; };
void fn_801E5D60(void*, W2*, s16*, int);
void fn_801E6120(void*, W2*, s16*, int);
void fn_8023126C(P2* o) {
    W2* c = o->x38->x4c[(s8)o->x31];
    switch ((s8)o->x30) {
    case 0: {
        s16 p[2];
        int y = c->xc;
        int x = c->xa;
        s16 ny = y - 0x40;
        p[0] = x;
        p[1] = y;
        c->xe = x + (s16)(c->xe - c->xa);
        c->xa = x;
        c->x10 = ny + (s16)(c->x10 - c->xc);
        c->xc = ny;
        fn_801E5D60(o, c, p, 0);
        break;
    }
    case 1: {
        s16 p[2];
        int y = c->xc;
        int x = c->xa;
        int s = y + 0x40;
        p[0] = x;
        p[1] = s;
        fn_801E6120(o, c, p, 0);
        break;
    }
    }
    o->x28 = 4;
    if (++*(s8*)&o->x31 == (s8)o->x32) {
        ++*(s8*)&o->x31;
    }
    if ((s8)o->x31 >= 5) {
        o->x28 = c->x28;
        int m = o->x30;
        if (m == 1) {
            fn_80083DC4(o, 4);
        } else {
            fn_80083DC4(o, 1);
        }
    }
}
}
