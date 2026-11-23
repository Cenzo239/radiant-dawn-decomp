#include "game/rI_801DD7D4/types.h"
extern "C" {
void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E720(f32);
void fn_8007E7E8(int);
void fn_8007E7B4(void);
int fn_800CB0FC(f32, int);
void fn_800712E8(int, int, int);
int fn_8028DB44(int);
struct Ctx { u8 p[0x2d]; u8 x2d, x2e; u8 p2[5]; int x34; struct { u8 p[8]; void* x8; }* x38; };
struct GV { virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18(void*); virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c(); virtual void v40(int, int, int, int, int); virtual int v44(); virtual void v48(); virtual void v4c(); virtual void v50(); virtual void v54(); virtual void v58(int, int, int, int, int); virtual void v5c(); virtual void v60(void*); };
struct GR { u8 p[0x12]; s16 x12, x14, x16, x18; u8 p1[4]; s16 x1e, x20; u8 p2[0x2a]; u8 x4c, x4d; u8 p3[2]; union { struct { u8 x50, x51; } b; s16 x50s; }; s16 x52, x54, x56, x58, x5a, x5c, x5e; u8 p4[4]; s16 x64; u8 p5[0xa]; int x70; };
void fn_801E82D4(GR* o, Ctx* a) {
        int cw;
    int rh;
    int px;
    s16 x;
    s16 y;
    int hl;
    int h;
    ((GV*)o)->v18(a);
    cw = ((GV*)o)->v44();
    {
        int cols = o->x5c;
        int pos = o->x52;
        px = o->x56;
        int top = o->x5a;
        rh = o->x5e;
        int mx = cw * (s16)(pos % cols);
        int my = rh * (s16)((s16)(pos / cols) - top);
        x = mx + o->x1e;
        y = my + o->x20;
    }
    if ((px == -0x8000 && o->x58 == -0x8000) || (fn_8028DB44(px - x) <= 1 && fn_8028DB44(o->x58 - y) <= 1)) {
        o->x56 = x;
        o->x58 = y;
    } else {
        o->x56 = (px + x + 1) >> 1;
        o->x58 = (y + o->x58 + 1) >> 1;
    }
    if (o->b.x50 && o->x70) {
        hl = 0;
        int b = 0;
        if (a->x2d || a->x2e) b = 1;
        if (!b) {
            void* t;
            if (a->x34) t = a->x38->x8; else t = 0;
            if (t == o) hl = 1;
        }
        fn_8007E154();
        fn_8007E720(-2.0f);
        fn_8007E164();
        h = o->x5e;
        h = (h - fn_800CB0FC(1.0f, -1)) >> 1;
        fn_800712E8(o->x56, o->x58 + h, hl);
        fn_8007E154();
        fn_8007E720(3.0f);
        fn_8007E164();
        ((GV*)o)->v58((s16)(x - o->x1e), y, (s16)cw, rh, hl);
    }
    ((GV*)o)->v60(a);
    fn_8007E154();
    fn_8007E7B4();
    fn_8007E7E8(0x80);
    fn_8007E164();
}
struct GS { u8 p[0x12]; s16 x12, x14, x16, x18; u8 p1[4]; s16 x1e, x20; u8 p2[0x32]; struct { u8 x50, x51; } b; s16 x52, x56_, x56, x58, x5a, x5c, x5e; u8 p4[0x10]; int x70; };
void fn_802241A8(GS* o, Ctx* a) {
        int cw;
    int rh;
    int px;
    s16 x;
    s16 y;
    int hl;
    int h;
    ((GV*)o)->v18(a);
    cw = ((GV*)o)->v44();
    {
        int cols = o->x5c;
        int pos = o->x52;
        px = o->x56;
        int top = o->x5a;
        rh = o->x5e;
        int mx = cw * (s16)(pos % cols);
        int my = rh * (s16)((s16)(pos / cols) - top);
        x = mx + o->x1e;
        y = my + o->x20;
    }
    if ((px == -0x8000 && o->x58 == -0x8000) || (fn_8028DB44(px - x) <= 1 && fn_8028DB44(o->x58 - y) <= 1)) {
        o->x56 = x;
        o->x58 = y;
    } else {
        o->x56 = (px + x + 1) >> 1;
        o->x58 = (y + o->x58 + 1) >> 1;
    }
    if (o->b.x50 && o->x70) {
        hl = 0;
        int b = 0;
        if (a->x2d || a->x2e) b = 1;
        if (!b) {
            void* t;
            if (a->x34) t = a->x38->x8; else t = 0;
            if (t == o) hl = 1;
        }
        fn_8007E154();
        fn_8007E720(-2.0f);
        fn_8007E164();
        h = o->x5e;
        h = (h - fn_800CB0FC(1.0f, -1)) >> 1;
        fn_800712E8(o->x56, o->x58 + h, hl);
        fn_8007E154();
        fn_8007E720(3.0f);
        fn_8007E164();
        ((GV*)o)->v58((s16)(x - o->x1e), y, (s16)cw, rh, hl);
    }
    ((GV*)o)->v60(a);
    fn_8007E154();
    fn_8007E7B4();
    fn_8007E7E8(0x80);
    fn_8007E164();
}
}
