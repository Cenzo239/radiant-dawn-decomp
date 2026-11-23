#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/vobj.h"
#pragma auto_inline off

extern "C" {

typedef struct GXColor { u8 r, g, b, a; } GXColor;
void* fn_80085EF8(int);
void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E7E8(int);
#if TARGET_PC
FE10_PROTO void fn_8007E174(p32arg, int);
#else
void fn_8007E174(int, int);
#endif
void fn_8007E720(f32);
int fn_800CB0FC(int, f32);
#if TARGET_PC
FE10_PROTO int fn_800CA3DC(p32arg, int, f32);
FE10_PROTO int fn_800CA7A4(p32arg, int, f32);
#else
int fn_800CA3DC(int, int, f32);
int fn_800CA7A4(int, int, f32);
#endif
void fn_800712E8(int, int, int);
void fn_80072ACC(int, int, int, int, int, int, int);
GXColor* fn_800CD204(int);
void fn_80080508(GXColor*);
void fn_80080ABC(int, f32);
void fn_80080B70(int, f32);
void fn_80080B00(int, GXColor*, f32);
#if TARGET_PC
FE10_PROTO void fn_80080C24(p32arg);
#else
void fn_80080C24(int);
#endif
void fn_80080308(void);
void fn_800800D4(int);
void fn_80080330(f32, f32);
#if TARGET_PC
FE10_PROTO void fn_800D0864(p32arg);
#else
void fn_800D0864(int);
#endif
void fn_801D7CA8(int, int, int);
void fn_800453B4(void*, int);
#if TARGET_PC
FE10_PROTO void fn_80253EE4(p32arg, f32);
#else
void fn_80253EE4(int, f32);
#endif
void fn_80079210(void*);
extern char lbl_803CA870[];

typedef struct Ent { u8 pad[0x30]; s16 x; s16 y; VO0* x34; u8 pad38; u8 x39; } Ent;
typedef struct List {
    u8 pad0[0x2d];
    u8 x2d;
    u8 x2e;
    u8 pad2f[0x38 - 0x2f];
    s16 x38;
    s16 x3a;
    VO4* x3c;
    u8 ids[0x64];
    s8 n;
    u8 pada5;
    s8 sel;
} List;
class Scr : public VO4 {
public:
    u8 pad[0x24 - 8];
    u8 x24;
};

void fn_801DF814(Scr* o, List* l) {
    s16 h;
    s16 w;
    s16 x;
    s16 y;
    Ent* p;
    p = (Ent*)fn_80085EF8(l->ids[l->sel]);
    x = p->x;
    y = p->y;
    h = fn_800CB0FC(-1, 1.0f);
    w = fn_800CA3DC(p->x34->v0C(), -1, 1.0f);
    x -= w / 2;
    if (l->x38 < 0 || l->x3a < 0) {
        l->x38 = x;
        l->x3a = y;
    } else {
        l->x38 = (l->x38 + x) / 2;
        l->x3a = (l->x3a + y) / 2;
    }
    fn_8007E154();
    fn_8007E720(-1.0f);
    fn_8007E164();
    {
        int d = (s16)o->vCC() - h;
        f32 m = 0.5f * d;
        fn_800712E8(l->x38, l->x3a + m, 1);
    }
    if (o->x24 != 0) {
        int a = o->v58();
        int b = o->v5C();
        fn_8007E154();
        fn_8007E720(1.5f);
        fn_8007E164();
        fn_80072ACC(l->x38 + (w >> 1), l->x3a + ((s16)b >> 1), (s16)a, 0x18, 0x19, 0x4c, !(l->x2d || l->x2e));
        fn_8007E154();
        fn_8007E720(-1.5f);
        fn_8007E164();
    }
}

int fn_801DFCAC(void) { return 0; }

void fn_801DFCB4(u8* o) { fn_800D0864(*(int*)(o + 8)); }

typedef struct Ent2 { u8 pad[0x30]; s16 x; s16 y; u8 pad34[5]; u8 x39; } Ent2;
typedef struct L3 { u8 pad[0x3c]; VO4* x3c; } L3;

void fn_801DFCBC(VO0* o, L3* a, Ent2* b) {
    f32 x = b->x;
    f32 y = b->y;
    u8 c;
    VO4* w;
    if (b->x39 == 0) {
        c = o->v64();
    } else {
        c = 0;
    }
    w = a->x3c;
    x -= fn_800CA3DC(o->v0C(), -1, 1.0f) / 2;
    {
        int yy = (s16)w->vCC();
        y += (yy - fn_800CA7A4(o->v0C(), -1, 1.0f)) / 2;
    }
    fn_8007E154();
    fn_8007E174(0, 0x13);
    fn_8007E164();
    fn_800800D4(5);
    fn_80080330(x, y);
    {
        GXColor col = *fn_800CD204(c);
        fn_80080508(&col);
    }
    if ((u8)o->v70(1)) {
        fn_80080ABC(1, 2.0f);
    } else if ((u8)o->v70(2)) {
        fn_80080B70(1, 1.0f);
    } else if ((u8)o->v70(4)) {
        fn_80080B00(1, fn_800CD204(0x2a), 1.0f);
    }
    fn_80080C24(o->v0C());
    fn_80080308();
}

void fn_801E06A8(VO4* o) {
    o->v94();
    fn_8007E154();
    fn_8007E720(-1.0f);
    fn_8007E7E8(0x80);
    fn_8007E164();
}

int fn_801E06EC(void) { return 0x20; }
int fn_801E06F4(void) { return 0x1c; }
int fn_801E06FC(void) { return 0x1c; }
int fn_801E0704(void) { return 0; }
int fn_801E070C(void) { return 0; }

void* fn_801E0714(void* p, int del) {
    if (p != NULL && del > 0) {
        fn_80079210(p);
    }
    return p;
}

void fn_801E0754(VO0* o, L3* a, Ent2* b) {
    f32 x = b->x;
    f32 y = b->y;
    u8 c;
    VO4* w;
    if (b->x39 == 0) {
        c = o->v64();
    } else {
        c = 0;
    }
    w = a->x3c;
    x -= fn_800CA3DC(o->v0C(), 2, 1.0f) / 2;
    {
        int yy = (s16)w->vCC();
        y += (yy - fn_800CA7A4(o->v0C(), 2, 1.0f)) / 2;
    }
    fn_8007E154();
    fn_8007E174(0, 0x13);
    fn_8007E164();
    fn_800800D4(6);
    fn_80080330(x, y);
    {
        GXColor col = *fn_800CD204(c);
        fn_80080508(&col);
    }
    if ((u8)o->v70(1)) {
        fn_80080ABC(1, 2.0f);
    } else if ((u8)o->v70(2)) {
        fn_80080B70(1, 1.0f);
    } else if ((u8)o->v70(4)) {
        fn_80080B00(1, fn_800CD204(0x2a), 1.0f);
    }
    fn_80080C24(o->v0C());
    fn_80080308();
}

typedef struct St2 { u8 pad[0x38]; u8 x38; u8 x39; u8 pad3a[2]; VO4* x3c; } St2;

int fn_801E09C4(void* o, St2* a, St2* s) {
    if (s->x39 == 2) return 0x10;
    fn_800453B4(lbl_803CA870, 0x80);
    if (a->x3c->vAC() != 0) {
        fn_80253EE4(a->x3c->vAC(), 0.0f);
    }
    return 5;
}

int fn_801E0A4C(void* o, St2* a, St2* s) {
    if (s->x39 == 2) return 0x10;
    fn_800453B4(lbl_803CA870, 0x81);
    if (a->x3c->vA8() != 0) {
        fn_80253EE4(a->x3c->vA8(), 0.0f);
    }
    return 5;
}

void fn_801E0AD4(VO4* o) {
    o->v94();
    fn_801D7CA8(0, 0, 0x10);
}

int fn_801E0B10(void) { return 0x1c; }
int fn_801E0B18(void) { return 0x62; }
int fn_801E0B20(void) { return 0x38; }

}
