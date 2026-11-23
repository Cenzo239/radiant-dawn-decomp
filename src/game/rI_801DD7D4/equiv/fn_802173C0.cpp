#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/rlist.h"
extern "C" {
void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E720(f32);
void fn_8007E174(int, u32);
int fn_800CB0FC(f32, int);
const char* fn_800D0864(const char*);
int fn_800CA3DC(f32, const char*, int);
void fn_800CB3A8(f32, f32, int, int, int, int, int, const char*, ...);
void fn_801D8ADC(int, int, int, int);
extern u8 lbl_803E7290[];
extern char lbl_80371974[];
typedef void (RObj::*MF)(void*);
struct FnT { MF f; void* arg; };
extern MF lbl_8038F770;
extern const char* lbl_803718F0[];
static inline FnT forEach(LNode* n, LNode* e, FnT f) {
    while (n != e) {
        (n->val->*f.f)(f.arg);
        n = n->next;
    }
    return f;
}
class FB { public: int x[0x11]; virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18(int, int, const char*); virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48(); virtual int v4c(); virtual int v50(); };
#define FONT ((FB*)lbl_803E7290)
struct Ent { const char* s; u8 p[0x74]; };
struct K {
    u8 p0[0x12]; s16 a12; u8 p14[2]; s16 a16; u8 p18[6]; s16 a1e, a20; u8 p22[0x16]; u32 a38; u8 p3c[8]; LNode a44; u8 p50[4]; s16 a54; u8 p56[0x16]; u8* a6c; int a70;
    virtual void v08();
};
class KV { public: virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18(void*); virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c(); virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c(void*); virtual int v60(int); };
static inline int cen(int h, int v) { return (h - v) >> 1; }
static inline int cen2(K* o, int v) { return (o->a54 - v) >> 1; }
static inline int cen3(K* o) { int h = o->a54; return (h - FONT->v50()) >> 1; }
static inline int cen4(K* o) { int h = o->a54; return (h - fn_800CB0FC(1.0f, -1)) >> 1; }
void fn_802173C0(K* o, void* a) {
    /*P*/
    int ty2;
    int en;
    int ty;
    int ofs;
    const char** sp;
    int x;
    int y;
    u8* tbl;
    int h2;
    int h1;
    int w;
    u16 en2;
    int i;
    const char* s;
/*E*/
    ((KV*)o)->v5c(a);
    ((KV*)o)->v18(a);
    x = o->a1e;
    y = o->a20;
    w = (s16)((s16)(o->a16 - o->a12) - x * 2);
    h1 = o->a54;
    ty2 = (h1 - FONT->v50()) >> 1;
    h2 = o->a54;
    ty = (h2 - fn_800CB0FC(1.0f, -1)) >> 1;
    fn_800CA3DC(1.0f, fn_800D0864(lbl_80371974 + 0x81), -1);
    i = 0;
    sp = lbl_803718F0;
    ofs = 0;
    for (; i < 6; i++) {
        tbl = o->a6c;
        fn_8007E154();
        fn_8007E174(0, (u16)(o->a38 | 3));
        fn_8007E164();
        en = 0;
        if (o->a70 == 1 || ((KV*)o)->v60(i) != 0) en = 1;
        en2 = en ? 1 : 0;
        s = fn_800D0864(*(const char**)(tbl + ofs));
        fn_800CB3A8(1.0f, 0.0f, (s16)(x + FONT->v4c() + 4), (s16)(y + ty), en2, 1, 0, s);
        fn_8007E154();
        fn_8007E720(0.2f);
        fn_8007E164();
        fn_801D8ADC(x, (s16)(y + o->a54 - 0xc), w, 0x10);
        fn_8007E154();
        fn_8007E720(-0.1f);
        fn_8007E164();
        FONT->v18(x, (s16)y + ty2, *sp);
        sp++;
        y += o->a54;
        ofs += 0x78;
    }
    {
        FnT f;
        f.f = lbl_8038F770;
        f.arg = a;
        forEach(o->a44.next, &o->a44, f);
    }
}
}
