#include "game/rI_801DD7D4/types.h"
#pragma auto_inline off
extern "C" {
extern char lbl_8036F03C[];
extern u8 lbl_803CA870[];
extern u8 lbl_803C8E80[];
class VS { public: virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C(); virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34(int); virtual int v38(); virtual int v3C(); virtual int v40(); virtual int v44(); virtual int v48(); };
extern VS* lbl_804CB5B8;
typedef struct Pt { s16 x, y; } Pt;
typedef struct IM { u8 pad[0xa]; s16 xa, xc; u8 pe[0x4c - 0xe]; u8 x4c, x4d, x4e; u8 p4f; s16 x50; u8 p52[0x64 - 0x52]; const char* x64; u8 x68; u8 p69[0x74 - 0x69]; void* x74; int x78; } IM;
typedef struct SC { u8 pad[0x40]; IM* x40; IM* x44; IM* x48; IM* x4c; u8 p50[0x6c - 0x50]; u8 x6c; } SC;
IM* fn_801E5640(void*, int, int);
void fn_801E5734(void*, void*);
void fn_801E459C(void*, void*, void*, int);
void fn_801E495C(void*, void*, void*, int);
void fn_801E518C(void*, void*, int, f32);
int fn_801E999C(void*, int);
int fn_801E9914(void*, int);
#if TARGET_PC
FE10_PROTO struct Slot * fn_801E9B28(void*);
#else
int fn_801E9B28(void*);
#endif
#if TARGET_PC
FE10_PROTO p32ret fn_801E7A28(void*);
#else
int fn_801E7A28(void*);
#endif
void fn_801E5954(void*);
#if TARGET_PC
FE10_PROTO void fn_801EA538(void*, p32arg);
FE10_PROTO void fn_801E6C44(p32arg, void*, p32arg);
FE10_PROTO void fn_801E6D50(p32arg, void*);
#else
void fn_801EA538(void*, int);
void fn_801E6C44(int, void*, int);
void fn_801E6D50(int, void*);
#endif
void fn_80083DC4(void*, int);
void fn_800453B4(void*, int);
void fn_8004564C(void*, void*);
void fn_800466B4(void*, void*);
#if TARGET_PC
FE10_PROTO void fn_800451D4(void*, p32arg);
FE10_PROTO int fn_801237EC(p32arg);
FE10_PROTO void fn_80126D9C(p32arg, s16);
FE10_PROTO void fn_800F39DC(p32arg);
#else
void fn_800451D4(void*, int);
int fn_801237EC(int);
void fn_80126D9C(int, s16);
void fn_800F39DC(int);
#endif
void fn_80253EE4(const char*, f32);
void fn_801F7F28(void* p, void* arg);

static inline void setCB(IM* b, void (*f)(void*, void*), int k) { b->x74 = (void*)f; b->x78 = k; }
void fn_801F7F70(SC* o) {
    IM* w = o->x4c;
    w->x4c = 0;
    setCB(w, fn_801F7F28, *(int*)lbl_803CA870);
    w->x50 = fn_801E999C(w, 0);
    {
        IM* a = fn_801E5640(o, 0x107, 0);
        if (a->xa != 0x13d) {
            s16 y = a->xc;
            Pt p;
            p.x = 0x13d;
            p.y = y;
            fn_801E459C(o, a, &p, 1);
        }
    }
    {
        IM* a = fn_801E5640(o, 0x108, 0);
        if (a->xa != 0x131) {
            s16 y = a->xc;
            Pt p;
            p.x = 0x131;
            p.y = y;
            fn_801E459C(o, a, &p, 0);
        }
    }
    fn_801E5734(o, w);
    { const char* s = lbl_8036F03C + 0x15b; IM* p = fn_801E5640(o, -0x1000, 0); if (p != NULL) { p->x64 = s; } }
}
void fn_801F84E4(SC* o) {
    switch (lbl_803CA870[0xc]) {
    case 0x81: {
        IM* w = o->x4c;
        if (fn_801E9B28(w) != 0) {
            *(int*)(lbl_803CA870 + 4) = *(int*)lbl_803CA870;
            fn_800453B4(lbl_803CA870, 4);
            lbl_803CA870[0xe] = w->x50;
            *(int*)(lbl_803CA870 + 0x1c) = w->x50;
            fn_8004564C(lbl_803CA870, o);
        }
        break;
    }
    case 0x80:
        fn_80083DC4(o, 0x1a);
        break;
    }
    { const char* s = lbl_8036F03C + 0x15b; IM* p = fn_801E5640(o, -0x1000, 0); if (p != NULL) { p->x64 = s; } }
}
void fn_801F85C0(SC* o) {
    int u;
    s16 old;
    IM* w;
    int r;
    w = o->x4c;
    old = w->x50;
    fn_800466B4(lbl_803CA870, o);
    u = *(int*)lbl_803CA870;
    ((VS*)w)->v34(u);
    fn_80126D9C(u, fn_801237EC(u));
    {
        IM* k = o->x44;
        if (*(u32*)(lbl_803C8E80 + 0x15ec) & 0x10) {
            fn_801EA538(k, u);
            fn_800F39DC(u);
        }
    }
    r = fn_801E9914(w, old);
    if ((s16)r < 0) r = fn_801E999C(w, old);
    if ((s16)r >= 0) {
        w->x50 = r;
        fn_80083DC4(o, 0x1a);
    } else {
        fn_80083DC4(o, 0x1c);
    }
}
void fn_801F86B8(SC* o) {
    IM* w = o->x4c;
    w->x4c = 0;
    w->x74 = 0;
    w->x78 = 0;
    w->x50 = fn_801E999C(w, 0);
    {
        IM* a = fn_801E5640(o, 0x107, 0);
        if (a->xa != 0x191) {
            s16 y = a->xc;
            Pt p;
            p.x = 0x191;
            p.y = y;
            fn_801E495C(o, a, &p, 1);
        }
    }
    {
        IM* a = fn_801E5640(o, 0x108, 0);
        if (a->xa != 0x185) {
            s16 y = a->xc;
            Pt p;
            p.x = 0x185;
            p.y = y;
            fn_801E495C(o, a, &p, 0);
        }
    }
    fn_801E5734(o, w);
}
void fn_801F2228(SC* o) {
    u32 cur = fn_801E7A28(o->x40);
    fn_801E5954(o);
    if (cur != fn_801E7A28(o->x40)) {
        cur = fn_801E7A28(o->x40);
        ((VS*)o->x4c)->v34(cur);
        fn_801EA538(o->x44, cur);
    }
    if (!inputBlocked()) {
        int k = lbl_804CB5B8->v48();
        if ((k & 0x400) && cur != 0) {
            fn_800451D4(lbl_803CA870, cur);
            o->x4c->x68 = 1;
            o->x4c->x4e = 0;
            fn_801E518C(o, o->x40, 1, 0.5f);
            { s16 y = o->x44->xc; Pt p; p.x = 0x17e; p.y = y; fn_801E495C(o, o->x44, &p, 1); }
            { s16 x = o->x48->xa; Pt p; p.x = x; p.y = -0x2d; fn_801E495C(o, o->x48, &p, 1); }
            fn_80083DC4(o, 6);
            fn_80253EE4(lbl_8036F03C + 0x2b, 0.0f);
        } else if ((k & 0x2000) && cur != 0) {
            fn_801E6C44(cur, o, 1);
            o->x6c = 5;
            fn_80083DC4(o, 0x2d);
        } else if ((k & 0x1000) && cur != 0) {
            fn_801E6D50(cur, o);
            o->x6c = 5;
            fn_80083DC4(o, 0x2e);
        } else if (k & 0x800) {
            fn_80083DC4(o, 0x31);
            fn_80253EE4(lbl_8036F03C + 0x3b, 0.0f);
        }
    }
}

extern char lbl_8036FBC0[];
void fn_80083B78(void*);
void fn_80204174(void* o) {
    if (!inputBlocked() && (lbl_804CB5B8->v48() & 0xc00)) {
        fn_80253EE4(lbl_8036FBC0 + 0x58, 0.0f);
        fn_80083B78(o);
    }
}
}
