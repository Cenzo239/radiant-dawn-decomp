#include "game/rL_80133EB4/map3d.h"
#pragma auto_inline off
#pragma use_lmw_stmw on
extern "C" {
extern u8 lbl_803EC898[];
extern u8 lbl_803CB770[];
extern u8 lbl_803CAB38[];
extern char lbl_803697B4[];
extern MapModel* fn_8013B9A8(void);
extern Mesh* fn_80135A54(MapModel*, int, int, u32, u32);
extern Mesh* fn_80135800(MapModel*, int, int, u32, u32);
extern void fn_801CB5EC(Mesh*, void*, int, int);
extern u8 fn_80118130(void*, int, int);
extern void fn_80118380(void*, int, int, const char*);
extern void* fn_8013A890(MapModel*, Mesh*);
extern void fn_80272624(void*, f32);
extern void fn_801CA3DC(Mesh*, int);
extern void fn_801CA3E4(Mesh*, int);
extern void fn_801CB3B4(Mesh*, void*, int);
extern void fn_800661A0(void*, int, int, int, int);
extern s8* fn_800661A0_(void*, int, int, int, int);
extern void fn_8006625C(void*, int, int, int);
extern void* fn_800E3810(const char*, void*);
extern void fn_801CA5D4(Vec*, Mesh*);
extern void fn_800E48C8(void*, Vec*);

s8* Mark(void);
void fn_8013E34C(int x, int y, s8 a, int t, void* proc) {
    Mesh* r;
    MapModel* mm = fn_8013B9A8();
    if (mm) {
        Mesh* m = fn_80135A54(mm, x, y, 0x10000000, 0x10);
        if (m) {
            fn_801CB5EC(m, proc, 0xFF, t);
            x = m->tx;
            y = m->ty;
            if (t > 0) {
                switch (fn_80118130(lbl_803EC898, x, y)) {
                case 0x2C:
                    fn_80118380(lbl_803EC898, x, y, lbl_803697B4 + 0xAD);
                    break;
                case 0xAA:
                    fn_80118380(lbl_803EC898, x, y, lbl_803697B4 + 0xC1);
                    break;
                case 0x80:
                    fn_80118380(lbl_803EC898, x, y, lbl_803697B4 + 0xD7);
                    break;
                }
            }
            {
                void* e = fn_8013A890(mm, m);
                if (e) fn_80272624(e, 1.0f);
            }
            {
                r = fn_80135800(mm, x, y, 0x40000000, 0x10);
                if (r) {
                    fn_801CA3DC(r, 0);
                    fn_801CA3E4(r, 1);
                    fn_801CB3B4(r, proc, t);
                    fn_800661A0(lbl_803CB770, x, y, 0x13, 0);
                }
            }
        }
        {
            s8* q = ((s8*(*)(void*, int, int, int, int))fn_800661A0)(lbl_803CB770, (s8)x, (s8)y, 6, 0);
            q[0] = x;
            q[1] = y;
            q[2] = 6;
            q[3] = a;
            q[4] = a;
        }
    }
}

static inline void SetPos(void* e, const Vec& p) {
    Vec t = p;
    fn_800E48C8(e, &t);
}
struct W3 { u32 a, b, c; };
void fn_8013E530(int x, int y, int t, void* proc) {
    Vec a1;
    Vec a2;
    MapModel* mm = fn_8013B9A8();
    if (mm) {
        Mesh* m = fn_80135A54(mm, x, y, 0x10000000, 0x10);
        if (m) {
            fn_801CB5EC(m, proc, 0, t);
            x = m->tx;
            y = m->ty;
            if (t > 0) {
                switch (fn_80118130(lbl_803EC898, x, y)) {
                case 0x2C:
                    fn_80118380(lbl_803EC898, x, y, lbl_803697B4 + 0xEB);
                    break;
                case 0x80:
                {
                    void* e = fn_800E3810(lbl_803697B4 + 0x100, proc);
                    if (e) {
                        Vec t;
                        fn_801CA5D4(&t, m);
                        *(W3*)&a1 = *(W3*)&t;
                        Vec c = a1;
                        fn_800E48C8(e, &c);
                    }
                    break;
                }
                case 0x20:
                {
                    void* e = fn_800E3810(lbl_803697B4 + 0x112, proc);
                    if (e) {
                        Vec t;
                        fn_801CA5D4(&t, m);
                        *(W3*)&a2 = *(W3*)&t;
                        Vec c = a2;
                        fn_800E48C8(e, &c);
                    }
                    break;
                }
                }
            }
            {
                void* e = fn_8013A890(mm, m);
                if (e) fn_80272624(e, 0.0f);
            }
        }
        fn_8006625C(lbl_803CB770, (s8)x, (s8)y, 6);
    }
}

struct Cl4 { u8 r, g, b, a; };
extern void fn_803031CC(void);
extern void fn_80302B80(int, int);
extern void fn_80303200(int, int, int, int, int);
extern void fn_80021B2C(int);
extern void fn_80021A08(int, int, int, int, int, int, int);
extern void fn_80021BF4(int);
extern void fn_80021EF8(int, int);
extern void fn_80021CB4(int, int, int, int);
extern void fn_80021C34(int);
extern void fn_80021F7C(int, int, int, int);
extern void fn_80021B68(int);
extern void fn_803128AC(void*, f32, f32, f32);
extern void* fn_8000FB88(void);
extern void fn_80312378(void*, void*, void*);
extern void fn_80307E48(void*, int);
extern void fn_80021784(int);
extern u8* fn_8006074C(void*);
extern void fn_80021BA4(int, int, int, int);
extern void fn_80306EA0(int, Cl4);
extern void fn_80021FF0(int, int);
extern void fn_80022050(int, int);
extern void fn_80021E20(int, int, int, int, int);
extern void fn_80021D18(int, int, int, int, int, int);
extern void fn_80021E8C(int, int, int, int, int);
extern void fn_80021D9C(int, int, int, int, int, int);
void fn_8013E7FC(void) {
    u8 m[0x30];
    u8* o;
    fn_803031CC();
    fn_80302B80(9, 1);
    fn_80302B80(0xB, 1);
    fn_80303200(0, 9, 1, 4, 0);
    fn_80303200(0, 0xB, 1, 5, 0);
    fn_80021B2C(1);
    fn_80021A08(4, 0, 0, 1, 0, 0, 2);
    fn_80021BF4(1);
    fn_80021EF8(0, 4);
    fn_80021CB4(0, 0xFF, 0xFF, 4);
    fn_80021C34(0);
    fn_80021F7C(0, 1, 4, 0x3C);
    fn_80021B68(0);
    fn_803128AC(m, 0.0f, 0.0f, -0.0125f);
    fn_80312378(fn_8000FB88(), m, m);
    fn_80307E48(m, 0);
    fn_80021784(0);
    o = fn_8006074C(lbl_803CAB38);
    if (o && (o[0x8E] & 0x80)) {
        Cl4 c = {0xC0, 0xC0, 0xC0, 0x60};
        fn_80306EA0(0, c);
        fn_80021FF0(0, 0xC);
        fn_80022050(0, 0x1C);
        fn_80021E20(0, 0xF, 0xA, 0xE, 0xF);
        fn_80021D18(0, 0, 0, 1, 1, 0);
        fn_80021E8C(0, 7, 5, 6, 7);
        fn_80021D9C(0, 0, 0, 1, 1, 0);
        fn_80021BA4(1, 4, 5, 0);
    } else {
        fn_80021BA4(1, 4, 1, 0);
    }
}
extern int fn_80068D74(void);
extern void fn_8013EA08(f32, int, int, void*);
extern void fn_80011838(int);

struct MapG {
    int w, h;
    u8 pad8[0x200D - 8];
    u8 x200d[0x40][0x40];
    u8 pad300d[0x710E - 0x300D];
    s16 x710e[0x40][0x40];
    u8 padb10e[0xD18E - 0x910E];
    u16 xd18e[0x40][0x40];

    s8 xf18e[0x40][0x40];
};
struct EP { u8 pad[0x34]; f32 x34; };
}
