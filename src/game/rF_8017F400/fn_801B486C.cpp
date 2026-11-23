#include "game/rF_8017F400/types.h"
#pragma auto_inline off
extern "C" {
/* cursor unit info window draw */
struct C4 { u8 r, g, b, a; };
struct Vec3 { f32 x, y, z; };
struct UStat { u16 a : 3; u16 d : 3; u16 b : 3; u16 c : 3; u16 e : 3; u16 f : 1; };
typedef struct UWin {
    u8 pad[0x30];
    u8* unit;
    s16 x34;
    s16 x36;
    u8 alpha;
    u8 t;
    u8 maxA;
    u8 dur;
    u8 pad3C[4];
    void* tex;
    s16 x44;
    s16 x46;
} UWin;
class IconFont {
public:
    u8 pad[0x44];
    virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14();
    virtual void draw(int x, int y, int id);
};
extern u8 lbl_803E7290[];
extern u8 lbl_803CAB38[];
extern char lbl_8036DE44[];
extern void* lbl_804CB58C;
extern void* lbl_804CA4E8;
extern void* lbl_804CA4EC;
extern const C4 lbl_8036DE28[4];
extern int fn_8019120C(void);
extern u8* fn_80060728(void*);
extern void fn_80191240(s16*, s16*, int*);
extern void* fn_801246A4(u8*);
extern u8* fn_800C3FD0(void*);
extern void fn_800C3EE0(u8*, int);
extern int fn_800C3F64(u8*);
extern void fn_8007E154(void);
extern void fn_8007E164(void);
#if TARGET_PC
extern FE10_PROTO void fn_8007E174(p32arg, int);
#else
extern void fn_8007E174(int, int);
#endif
extern void fn_8007E4E4(f32, f32, f32, f32);
extern void fn_8007E7DC(int);
extern void fn_8007E720(f32);
#if TARGET_PC
extern FE10_PROTO void fn_8007E374(void*, p32arg, int);
#else
extern void fn_8007E374(void*, int, int);
#endif
extern void fn_800800D4(int);
extern void fn_80080430(f32, f32, f32, f32, f32, f32);
extern void fn_80080348(f32, f32, f32, f32);
extern void fn_80080368(f32, f32, f32, f32);
extern void fn_80080508(C4);
extern void fn_80080578(int);
extern void fn_80080308(void);
extern const C4* fn_800CD204(int);
extern void* fn_800C6210(void*, int);
extern void fn_800C48A8(int, int, int, void*, int);
extern void fn_800C429C(void*);
#if TARGET_PC
extern FE10_PROTO void fn_800F97A4(u8*, p32arg, p32arg);
#else
extern void fn_800F97A4(u8*, int, int);
#endif
extern void fn_80075714(int, int, u8*);
extern u8 fn_80126B0C(u8*);
extern const char* fn_80118C44(void*);
extern int fn_800CA3DC(const char*, int, f32);
extern void fn_800CB3A8(f32, f32, s16, s16, int, int, int, const char*, ...);
extern int fn_80290DDC(char*, const char*, ...);
extern s16 fn_801237EC(u8*);
extern char* strcpy(char*, const char*);
extern int fn_8011B77C(u8*, void*);
extern void* fn_8012759C(u8*);
extern void fn_80108048(void*, int, int, int);
extern s8 fn_801284C4(u8*);

static inline void DrawText(int cx, int y, int c, const char* s) {
    fn_800CB3A8(1.0f, 0.0f, cx - fn_800CA3DC(s, -1, 1.0f) / 2, y, c, 0, 0, s);
}

void fn_801B486C(UWin* p) {
    u32 army;
    int big = 0;
    int kind;
    char buf[0x40];
    if (fn_8019120C() == 0) {
        if (*(s8*)(fn_80060728(lbl_803CAB38) + 8) == 0) return;
        if (p->unit == 0) return;
        army = (*(u8**)(p->unit + 0xF4))[8];
        kind = *(s8*)(fn_80060728(lbl_803CAB38) + 8);
    } else {
        fn_80191240(&p->x44, &p->x46, &kind);
        if (p->x44 == -1) return;
        army = 0;
        p->alpha = p->maxA;
    }
    if (p->tex == 0) return;
    if (p->alpha == 0) return;
    if (kind >= 4 && kind <= 6) big = 1;
    if (fn_8019120C() == 0) {
        u8* u = p->unit;
        Vec3 pos = *(Vec3*)(u + 0x1C);
        f32 k = 0.5f;
        f32 fx = (int)(k + pos.x);
        f32 fy = (int)(k + pos.y);
        p->x44 = fx - 130.0f;
        p->x46 = fy - 120.0f;
        if (*(u32*)(u + 0x10C) & 0x18) return;
        if (p->x36 < 0) {
            u8* e = fn_800C3FD0(fn_801246A4(u));
            if (e == 0) return;
            fn_800C3EE0(e, 0);
            if (fn_800C3F64(e) == 0) return;
            p->x36 = *(s16*)(e + 0x22);
        }
    }
    if (big) p->x46 -= 0x18;
    fn_8007E154();
    fn_8007E4E4(p->x44, p->x46, 101.0f, 1.0f);
    fn_8007E7DC(p->alpha);
    fn_8007E164();
    {
    struct T { C4 c[4]; } tbl = *(const T*)lbl_8036DE28;
    fn_8007E154();
    fn_8007E374(p->tex, kind - 1, 0x11);
    fn_8007E164();
    fn_800800D4(1);
    fn_80080430(0.0f, 0.0f, 0.0f, 0.0f, 272.0f, big ? 0x80 : 0x68);
    fn_80080508(tbl.c[army]);
    fn_80080578(0);
    fn_80080308();
    }
    fn_8007E154();
    fn_8007E720(-0.1f);
    fn_8007E164();
    if (!big) {
        fn_8007E154();
        fn_8007E374(p->tex, 6, 0x11);
        fn_8007E164();
        fn_800800D4(1);
        fn_80080430(83.0f, 32.0f, 0.0f, 0.0f, 32.0f, 24.0f);
        fn_80080508(*fn_800CD204(1));
        fn_80080578(0);
        fn_80080308();
        fn_8007E154();
        fn_8007E374(p->tex, 7, 0x11);
        fn_8007E164();
        fn_800800D4(1);
        fn_80080430(151.0f, 32.0f, 0.0f, 0.0f, 32.0f, 24.0f);
        fn_80080508(*fn_800CD204(1));
        fn_80080578(0);
        fn_80080308();
    } else {
        fn_8007E154();
        fn_8007E374(p->tex, 6, 0x11);
        fn_8007E164();
        fn_800800D4(1);
        fn_80080430(83.0f, 32.0f, 0.0f, 0.0f, 32.0f, 24.0f);
        fn_80080508(*fn_800CD204(1));
        fn_80080578(0);
        fn_80080308();
        fn_8007E154();
        fn_8007E374(p->tex, 7, 0x11);
        fn_8007E164();
        fn_800800D4(1);
        fn_80080430(151.0f, 32.0f, 0.0f, 0.0f, 32.0f, 24.0f);
        fn_80080508(*fn_800CD204(1));
        fn_80080578(0);
        fn_80080308();
        fn_8007E154();
        fn_8007E374(p->tex, 8, 0x11);
        fn_8007E164();
        fn_800800D4(1);
        fn_80080430(79.0f, 58.0f, 0.0f, 0.0f, 40.0f, 24.0f);
        fn_80080508(*fn_800CD204(1));
        fn_80080578(0);
        fn_80080308();
    }
    fn_8007E154();
    fn_8007E720(0.1f);
    fn_8007E164();
    if (fn_8019120C() != 0) return;
    fn_8007E154();
    fn_8007E720(-0.1f);
    fn_8007E164();
    {
        void* w = fn_800C6210(fn_801246A4(p->unit), 0);
        fn_800C48A8(10, big ? 0x18 : 10, p->alpha, w, 0);
        fn_800C429C(w);
    }
    {
        UStat* st = (UStat*)(p->unit + 0x110);
        if ((int)st->a > 0) ((IconFont*)lbl_803E7290)->draw(0xC, -9, 0x1A);
        else if ((int)st->b > 0) ((IconFont*)lbl_803E7290)->draw(0xC, -9, 0x1B);
        else if ((int)st->c > 0) ((IconFont*)lbl_803E7290)->draw(0xC, -9, 0x1C);
        else if ((int)st->d > 0) ((IconFont*)lbl_803E7290)->draw(0xC, -9, 0x1D);
        else if ((int)st->e > 0) ((IconFont*)lbl_803E7290)->draw(0xC, -9, 0x1E);
        else if ((int)st->f > 0) ((IconFont*)lbl_803E7290)->draw(0xC, -9, 0x1F);
    }
    fn_800F97A4(p->unit, 0x4E, 5);
    fn_80075714(0xE8, 5, p->unit);
    if (big && fn_80126B0C(p->unit) != 0xFF) {
        fn_8007E154();
        fn_8007E374(p->tex, 9, 0x11);
        fn_8007E164();
        {
            int w = 88.0f * (1.0f + fn_80126B0C(p->unit)) / 100.0f;
            int x0 = 0x9C, y0 = 0x40, h = 8;
            fn_800800D4(1);
            fn_80080348(x0, y0, 0.0f, 0.0f);
            fn_80080368(x0 + w, y0 + h, w, h);
            fn_80080578(0);
            fn_80080308();
        }
    }
    fn_8007E154();
    fn_8007E174(0, 0x13);
    fn_8007E164();
    {
        const char* nm = fn_80118C44(*(void**)(p->unit + 0xEC));
        DrawText(0xA6, 4, 1, nm);
    }
    if (*(u32*)(p->unit + 0x10C) & 0x10000000) {
        fn_80290DDC(buf, lbl_8036DE44);
        DrawText(0x7F, 0x1E, 1, buf);
        fn_800CB3A8(1.0f, 0.0f, 0xD2, 0x1E, 1, 0, 0, lbl_8036DE44 + 3);
        fn_80290DDC(buf, lbl_8036DE44);
        DrawText(0xC4, 0x1E, 1, buf);
        fn_80290DDC(buf, lbl_8036DE44);
        DrawText(0xE6, 0x1E, 4, buf);
    } else {
        fn_80290DDC(buf, lbl_8036DE44 + 5, *(s8*)(p->unit + 0xFE));
        DrawText(0x7F, 0x1E, 1, buf);
        fn_800CB3A8(1.0f, 0.0f, 0xD8, 0x1E, 1, 0, 0, lbl_8036DE44 + 3);
        fn_80290DDC(buf, lbl_8036DE44 + 5, *(s8*)(p->unit + 0x114));
        DrawText(0xC4, 0x1E, 1, buf);
        fn_80290DDC(buf, lbl_8036DE44 + 5, (int)fn_801237EC(p->unit));
        DrawText(0xF1, 0x1E, 0xC, buf);
    }
    if (big) {
        if (fn_80126B0C(p->unit) != 0xFF) fn_80290DDC(buf, lbl_8036DE44 + 5, fn_80126B0C(p->unit));
        else strcpy(buf, lbl_8036DE44 + 8);
        DrawText(0x88, 0x37, 1, buf);
    }
    {
        int ic;
        int ly = 0x38;
        if (big) ly = 0x4E;
        if (fn_8011B77C(p->unit + 0x12C, lbl_804CA4E8) != 0) {
            fn_80290DDC(buf, lbl_8036DE44 + 5, (int)fn_801284C4(p->unit));
            DrawText(0x7C, (s16)ly + 2, 1, buf);
            {
                int r = fn_8011B77C(p->unit + 0x12C, lbl_804CA4EC);
                ic = 0x38;
                if (r == 0) ic = 0x37;
            }
            fn_8007E154();
            fn_8007E374(lbl_804CB58C, ic, 0x11);
            fn_8007E164();
            {
                int w = 106.0f * fn_801284C4(p->unit) / 30.0f;
                int x0 = 0x92, h = 8;
                fn_800800D4(1);
                fn_80080348(x0, ly + 0xC, 0.0f, 0.0f);
                fn_80080368(x0 + w, ly + 0x14, 88.0f, h);
                fn_80080578(0);
                fn_80080308();
            }
            {
                u8* j = *(u8**)(p->unit + 0xF0);
                u16 m;
                if (fn_8011B77C(p->unit + 0x12C, lbl_804CA4EC) == 0) j = *(u8**)(j + 0x18);
                m = *(u16*)(j + 0xEE);
                if (m & 0x40) ic = 0x34;
                else if (m & 0x100) ic = 0x35;
                else if (m & 0x80) ic = 0x36;
            }
            fn_8007E154();
            fn_8007E374(lbl_804CB58C, ic, 0x11);
            fn_8007E164();
            {
                int x0 = 0x54, w = 0x18, h = 0x18;
                fn_800800D4(1);
                fn_80080348(x0, ly + 2, 0.0f, 0.0f);
                fn_80080368(x0 + w, ly + 2 + h, w, h);
                fn_80080578(0);
                fn_80080308();
            }
        } else if (fn_8012759C(p->unit) != 0) {
            fn_80108048(fn_8012759C(p->unit), 1, 0x52, ly);
        }
    }
    fn_8007E154();
    fn_8007E720(0.1f);
    fn_8007E7DC(0xFF);
    fn_8007E164();
}
}
