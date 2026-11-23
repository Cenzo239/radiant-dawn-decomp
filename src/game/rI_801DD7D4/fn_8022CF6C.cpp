#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/rlist.h"
extern "C" {
void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E720(f32);
void fn_8007E7E8(int);
#if TARGET_PC
FE10_PROTO void fn_8007E174(p32arg, u32);
#else
void fn_8007E174(int, u32);
#endif
int fn_800CB0FC(f32, int);
void fn_800712E8(int, int, int);
int fn_8028DB44(int);
void fn_80216F84(void*, void*);
void fn_801E4F50(void*, void*, int);
void fn_801E2F40(void*, void*);
void fn_801E4D1C(void*, void*, int);
void fn_801E5734(void*, void*);
void fn_801E1CC0(void*, s16);
typedef void (RObj::*MF)(void*);
struct FnT { MF f; void* arg; };
extern MF lbl_803904C4;
static inline FnT forEach(LNode*& n, LNode* e, FnT f) {
    while (n != e) {
        (n->val->*f.f)(f.arg);
        n = n->next;
    }
    return f;
}
struct KB;
const char* fn_800D0864(const char*);
int fn_800CA3DC(const char*, int, f32);
void fn_800CB278(int, int, int, const char*, ...);
void fn_801DA230(int, int, int);
void fn_801DA2C0(int, int, int);
extern const char* lbl_803904A8[];
extern char lbl_80372034[];
extern MF lbl_803904B8;
struct KVX { virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c(); virtual void v30(); virtual int v34(); virtual int v38(); virtual int v3c(); virtual void v40(); virtual int v44(); virtual void v48(); virtual void v4c(); virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c(); };
struct Ctx { u8 p[0x2d]; u8 x2d, x2e; u8 p2[5]; int x34; struct { u8 p[8]; void* x8; }* x38; };
struct KV { virtual void v08(); virtual void v0c(); virtual KB* v10(int, int); virtual void v14(); virtual void v18(void*); virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c(); virtual void v30(); virtual int v34(); virtual int v38(); virtual int v3c(); };
struct KB { u8 p[0x1e]; s16 x1e, x20; u8 p2[0x22]; LNode* x44; LNode* x48; s16 p4c; u8 p3[2]; s16 x50, x52, x54; u8 p4[6]; f32 x5c; u8 p5[0x10]; int x70; void* x74; u8 p6[4]; void* x7c[2]; };
struct KL { u8 p[0x40]; s16 x40, x42, x44; };
void fn_8022CF6C(KB* o, Ctx* a) {
    ((KV*)o)->v18(a);
        int hl;
    LNode* n;
    s16 k;
    int h;
    LNode* sent;
    s16 px;
    s16 x;
    s16 y;
    s16 py;
    k = o->x54;
    {
    int i = ((KV*)o)->v34();
    x = o->x1e - 0x5f;
    y = o->x20 + 3;
    switch ((s16)i) {
    case 0: y += i * k; break;
    case 1: y = 0x78; break;
    case 2: y = 0x99; break;
    case 3: y = 0xba; break;
    }
    }
    px = o->x50;
    if (px == -0x8000 || (py = o->x52) == -0x8000 || (fn_8028DB44(px - x) <= 1 && fn_8028DB44(py - y) <= 1)) {
        o->x50 = x;
        o->x52 = y;
    } else {
        o->x50 = (px + x + 1) >> 1;
        o->x52 = (y + o->x52 + 1) >> 1;
    }
    if (((KV*)o)->v3c()) {
        hl = 0;
        int f = 0;
        int b = 0;
        if (a->x2d || a->x2e) b = 1;
        if (!b) {
            void* t;
            if (a->x34) t = a->x38->x8; else t = 0;
            if (t == o) f = 1;
        }
        if (f && o->x70 == 0) hl = 1;
        fn_8007E154();
        fn_8007E720(-2.0f);
        fn_8007E164();
        h = o->x54;
        h = (h - fn_800CB0FC(1.0f, -1)) >> 1;
        fn_800712E8(o->x50, o->x52 + h, hl);
    }
    fn_8007E154();
    fn_8007E7E8(0x80);
    fn_8007E164();
    {
        FnT ft;
        ft.f = lbl_803904C4;
        ft.arg = a;
        sent = (LNode*)&o->x44;
        forEach((n = o->x48), sent, ft);
    }
}
void fn_8022D1CC(KB* o, void* p) {
    int prev = ((KV*)o)->v34();
    fn_80216F84(o, p);
    if ((s16)prev != (s16)((KV*)o)->v34()) {
        prev = -1;
        switch ((s16)((KV*)o)->v34()) {
        case 0: prev = 0; break;
        }
        if (prev >= 0) {
            KB* c = ((KV*)o)->v10(0x81, 0);
            KB* q = (KB*)((u8*)o + prev * 4);
            if (c != q->x7c[0]) {
                if (c) fn_801E4F50(p, c, 0);
                fn_801E2F40(o, q->x7c[0]);
                fn_801E4D1C(p, q->x7c[0], 1);
                fn_801E5734(p, o);
            }
        }
    }
    {
        KB* c = ((KV*)o)->v10(0x81, 0);
        if (c) {
            int m = ((KV*)c)->v38();
            int s = (int)c->x5c;
            int h = ((KV*)c)->v34();
            fn_801E1CC0(o->x74, m * h - s);
        }
    }
}
}
