#include "game/rL_80133EB4/map3d.h"
#pragma auto_inline off
#pragma use_lmw_stmw on
extern "C" {
struct Stone {
    Mesh* m;      /* 0x00 */
    u8* fx;       /* 0x04 */
    void* x08;    /* 0x08 */
    s16 x0c;      /* 0x0C */
    u8 dir;       /* 0x0E */
    u8 idx;       /* 0x0F */
    u8 x10, x11, x12, x13;
    f32 x, y, z;  /* 0x14 */
    f32 vz;       /* 0x20 */
    Vec axis;     /* 0x24 */
    f32 speed;    /* 0x30 */
    f32 acc;      /* 0x34 */
    void* x38;    /* 0x38 */
    f32 x3c;      /* 0x3C */
    u8 mtx[0x30]; /* 0x40 */
    u8 path[0x20];/* 0x70 */
};
struct SP { u8 pad[0x30]; Stone* s; };
struct Cl4 { u8 r, g, b, a; };
extern const Cl4 cGray;
extern char lbl_803697B4[];
extern u8 lbl_803EC898[];
extern u8 lbl_803CAB38[];
extern u8 lbl_803CA870[];
extern int lbl_803E7320[];
extern void* fn_80078D9C(int, const char*, int);
extern void fn_80312318(void*);
extern void fn_801CA2C4(Mesh*);
extern void fn_801CA388(Mesh*, Cl4);
extern void fn_801CA3E4(Mesh*, int);
extern void fn_800E24F8(const char*);
extern u8* fn_800E4060(const char*, void*);
extern void fn_8011800C(void*, void*);
extern void fn_800CFD18(void*, int);
extern void* fn_800CFB0C(void*);
extern void fn_800F6604(void*, const char*);
void fn_8013CCA4(SP* p, Mesh* m, void* path, void* x38) {
    int i;
    p->s = (Stone*)fn_80078D9C(-0x90, lbl_803697B4 + 0x2E, 0);
    p->s->m = m;
    p->s->x38 = x38;
    p->s->x = m->tx;
    p->s->y = m->ty;
    p->s->z = *(f32*)((u8*)m + 0xC);
    p->s->vz = 0.05f;
    p->s->idx = 0;
    p->s->x3c = 0.0f;
    p->s->speed = 5.0f;
    p->s->acc = 0.0f;
    fn_80312318(p->s->mtx);
    fn_801CA2C4(p->s->m);
    {
        Cl4 c = {0x80, 0x80, 0x80, 0xFF};
        fn_801CA388(p->s->m, c);
    }
    fn_801CA3E4(p->s->m, 1);
    p->s->x08 = *(void**)lbl_803CA870;
    fn_800E24F8(lbl_803697B4 + 0x2F);
    fn_800E24F8(lbl_803697B4 + 0x42);
    p->s->fx = fn_800E4060(lbl_803697B4 + 0x4C, p);
    if (p->s->fx) *(u32*)(*(u8**)(p->s->fx + 0x30) + 0x18) |= 0x14;
    fn_8011800C(path, p->s->path);
    for (i = 0; i < lbl_803E7320[0]; i++) {
        void* u = fn_800CFB0C(((void*(*)(void*, int))fn_800CFD18)(lbl_803E7320, i));
        if (u) fn_800F6604(u, lbl_803697B4 + 0x5F);
    }
}
extern u8 lbl_803696D8[];
extern void fn_80083DC4(void*, int);
static const char sNames[0x30] = "E_BuildEventSkip\0\0\0\0E_BuildDest\0E_BuildPitFall";
static const Vec sAxisL = {-1.0f, 0.0f, 0.0f};
static const Vec sAxisR = {1.0f, 0.0f, 0.0f};
static const Vec sAxisD = {0.0f, 0.0f, 1.0f};
static const Vec sAxisU = {0.0f, 0.0f, -1.0f};
const char* fn_dummy_names(void) { return sNames; }
void fn_8013CE9C(SP* p) {
    Stone* s;
    p->s->x0c = 0;
    s = p->s;
    if ((u32)s->path[s->idx] == '@') {
        fn_80083DC4(p, 2);
    } else {
        p->s->x12 = p->s->x10 = (u8)(0.5f + s->x);
        p->s->x13 = p->s->x11 = (u8)(0.5f + p->s->y);
        s = p->s;
        s->dir = s->path[s->idx++];
        switch (p->s->dir) {
        case 8:
        {
            Vec v = sAxisL;
            p->s->axis = v;
            p->s->x11 = p->s->x13 - 1;
            break;
        }
        case 4:
        {
            Vec v = sAxisR;
            p->s->axis = v;
            p->s->x11 = p->s->x13 + 1;
            break;
        }
        case 1:
        {
            Vec v = sAxisD;
            p->s->axis = v;
            p->s->x10 = p->s->x12 - 1;
            break;
        }
        case 2:
        {
            Vec v = sAxisU;
            p->s->axis = v;
            p->s->x10 = p->s->x12 + 1;
            break;
        }
        }
    }
}
extern void fn_8013D0A8(SP*);
extern void fn_801CAA24(Mesh*, void*, int);
extern void fn_801CB0A4(Mesh*, void*, Cl4, int);
extern void fn_802549C4(f32, const char*, Vec*);
extern void fn_8013C14C(f32, int, int, void*);
extern void* fn_800E3A10(const char*, void*);
extern void fn_800E48C8(void*, Vec*);
extern void fn_800E4B20(void*, int);
struct W3 { u32 a, b, c; };
void fn_8013D7B4(SP* p) {
    p->s->speed = 0.0f;
    fn_80312318(p->s->mtx);
    fn_8013D0A8(p);
    fn_801CAA24(p->s->m, p, 0);
    {
        Cl4 c = {0x80, 0x80, 0x80, 0};
        fn_801CB0A4(p->s->m, p, c, 0x3C);
    }
    {
        Vec c;
        Vec v;
        Stone* s = p->s;
        v.x = 0.5f + s->x;
        v.y = 0.5f + s->y;
        v.z = s->z;
        *(W3*)&c = *(W3*)&v;
        {
            Vec d;
            d = c;
            fn_802549C4(0.0f, lbl_803697B4 + 0x90, &d);
        }
        lbl_804CB5B8->vA8(8);
        fn_8013C14C(30.0f, 6, 2, p);
        {
            void* e = fn_800E3A10(lbl_803697B4 + 0x2F, p);
            if (e) {
                Vec b = v;
                fn_800E48C8(e, &b);
            }
        }
    }
    if (p->s->fx) {
        fn_800E4B20(p->s->fx, -1);
        p->s->fx = 0;
    }
}

extern void fn_80083B78(void*);
static const Vec sUp = {0.0f, 1.0f, 0.0f};
extern void fn_80312830(void*, f32, Vec*);
extern void fn_80312DB4(void*, Vec*, Vec*);
extern f32 fn_80116E84(void*, int, int, u8);
extern void* fn_8012CF28(int, int);
extern void fn_80102C6C(void*, const char*, int, int, int);
#if TARGET_PC
extern FE10_PROTO void fn_80102CD8(void*, p32arg, p32arg, p32arg);
extern FE10_PROTO void fn_80103234(void*, int, int, p32arg);
#else
extern void fn_80102CD8(void*, int, int, int);
extern void fn_80103234(void*, int, int, int);
#endif
extern void* fn_800E3810(const char*, void*);
extern void fn_800E5878(void*, void*);
extern void fn_800F7790(Vec*, void*);
extern f32 fn_801142F0(void*, f32, f32);
extern void fn_800620A8(void*, f32, f32);
void fn_8013D404(SP* p) {
    u8 mtx[0x30];
    Vec up = sUp;
    fn_80312830(mtx, 1.57079637f, &p->s->axis);
    fn_80312DB4(mtx, &up, &up);
    {
        f32 half;
        f32 uz;
        f32 d;
        f32 dx;
        f32 dz;
        Stone* s;
        int ax;
        int ay;
        int bx;
        int by;
                d = 3.14159274f * p->s->speed / 360.0f;
        half = 0.5f;
        s = p->s;
        dx = up.x * d;
        uz = up.z; dz = uz * d;
        ax = half + s->x;
        ay = half + s->y;
        s->x += dx;
        p->s->y += dz;
        s = p->s;
        bx = half + s->x;
        by = half + s->y;
        p->s->acc = 0.25f * fn_80116E84(lbl_803EC898, (s8)(int)(half + s->x), (s8)(int)(half + s->y), s->dir);
        p->s->speed += p->s->acc;
        if (p->s->speed > 15.0f) p->s->speed = 15.0f;
        if (p->s->speed < 5.0f) p->s->speed = 5.0f;
        s = p->s;
        if ((int)s->x > s->x12 || (int)s->y > s->x13 || (int)(1.0f + s->x) < s->x12 || (int)(1.0f + s->y) < s->x13) {
            if ((u32)s->path[s->idx] == '@') {
                int v = s->x10;
                s->x = v;
                v = p->s->x11;
                p->s->y = v;
            }
            fn_80083B78(p);
        }
        if (ax != bx || ay != by) {
            void* u = fn_8012CF28(bx, by);
            if (u) {
                fn_80102C6C(u, lbl_803697B4 + 0x5F, 8, 0, 0);
                fn_80102CD8(u, -1, 0x10, 0);
                fn_80103234(u, 1, 2, 0);
                {
                    void* e = fn_800E3810(lbl_803697B4 + 0x42, p);
                    if (e) fn_800E5878(e, u);
                }
                {
                    Vec b;
                    Vec a;
                    fn_800F7790(&a, u);
                    b = a;
                    fn_802549C4(0.0f, lbl_803697B4 + 0x7B, &b);
                }
            }
        }
    }
    {
        f32 h = fn_801142F0(lbl_803EC898, 0.5f + p->s->x, 0.5f + p->s->y);
        Stone* s = p->s;
        if (s->z < h) {
            s->vz *= 1.05f;
        } else {
            s->vz = 0.05f;
        }
        s = p->s;
        s->z += s->vz;
        if (p->s->z > h) p->s->z = h;
    }
    fn_8013D0A8(p);
    fn_800620A8(lbl_803CAB38, p->s->x, p->s->y);
}
extern void fn_801CA3DC(Mesh*, int);
extern int fn_801CA1D8(Mesh*);
extern void fn_801CA5D4(Vec*, Mesh*);
extern void fn_801CB5EC(Mesh*, void*, int, int);

extern MapModel* fn_8013B9A8(void);
extern void fn_803128AC(void*, f32, f32, f32);
extern void fn_80312378(void*, void*, void*);
extern void fn_8031292C(void*, f32, f32, f32);
extern void fn_801CA434(Mesh*, void*);
extern void fn_800E48AC(void*, f32, f32, f32);
extern void fn_800E49AC(f32, void*);
static inline int DirIdx(u8 d) {
    switch (d) {
    case 1: return 2;
    case 2: return 1;
    case 4: return 8;
    case 8: return 4;
    }
    return 0x40;
}
void fn_8013D0A8(SP* p) {
    u8 mS[0x30];
    u8 mR[0x30];
    u8 mT[0x30];
    u8 mO[0x30];
    Vec v;
    MapModel* mm = fn_8013B9A8();
    fn_80312830(mR, 0.017453292f * p->s->speed, &p->s->axis);
    fn_80312378(mR, p->s->mtx, p->s->mtx);
    fn_803128AC(mT, -2.5f, -2.0f, -2.5f);
    fn_80312378(p->s->mtx, mT, mR);
    fn_803128AC(mT, 2.5f, 2.0f, 2.5f);
    fn_80312378(mT, mR, mO);
    {
        f32 sc = mm->scale;
        fn_8031292C(mS, sc, sc, sc);
        fn_80312378(mS, mO, mO);
        fn_803128AC(mT, 5.0f * (p->s->x * sc), 5.0f * (-p->s->z * sc), 5.0f * (p->s->y * sc));
    }
    fn_80312378(mT, mO, mO);
    fn_80312378(mm->xe4, mO, mO);
    fn_801CA434(p->s->m, mO);
    {
        Stone* s = p->s;
        f32 a = s->x3c;
        int ia = a / 180.0f;
        int ib = (a + s->speed) / 180.0f;
        if (a == 0.0f || ia != ib) {
            v.x = 0.5f + s->x;
            v.y = 0.5f + s->y;
            v.z = s->z;
            {
                Vec c;
                c = v;
                fn_802549C4(0.0f, lbl_803697B4 + 0x68, &c);
            }
        }
    }
    p->s->x3c += p->s->speed;
    if (p->s->x3c > 360.0f) p->s->x3c -= 360.0f;
    if (p->s->x3c < -360.0f) p->s->x3c += 360.0f;
    if (p->s->fx) {
        int ang;
        f32 fx = 0.5f + p->s->x;
        f32 fy = 0.5f + p->s->y;
        f32 fz = p->s->z;
        switch (DirIdx(p->s->dir)) {
        case 4: ang = 0; break;
        case 6: ang = 0x2D; break;
        case 2: ang = 0x5A; break;
        case 10: ang = 0x87; break;
        case 8: ang = 0xB4; break;
        case 9: ang = 0xE1; break;
        case 1: ang = 0x10E; break;
        case 5: ang = 0x13B; break;
        default: ang = 0; break;
        }
        fn_800E48AC(p->s->fx, fx, fy, fz);
        fn_800E49AC(ang, p->s->fx);
        *(u32*)(*(u8**)(p->s->fx + 0x30) + 0x18) &= ~0x10;
    }
}

extern void fn_801CA3DC(Mesh*, int);
extern int fn_801CA1D8(Mesh*);
extern void fn_801CA5D4(Vec*, Mesh*);
extern void fn_801CB5EC(Mesh*, void*, int, int);
struct DoorProc { u8 pad0[0x18]; void* x18; u8 pad1c[0x38 - 0x1C]; Mesh* m38; Mesh* m3c; Mesh* m40; Mesh* m44; int t; int n; };
void fn_8013C380(DoorProc* p) {
    Vec a;
    p->t = 0;
    fn_801CA3DC(p->m38, 0xFF);
    fn_801CA3E4(p->m38, 1);
    if (p->m44) {
        fn_801CA3DC(p->m44, 0xFF);
        fn_801CA3E4(p->m44, 1);
    }
    if (p->m3c) {
        fn_801CA3DC(p->m3c, 0);
        fn_801CA3E4(p->m3c, 1);
        if (fn_801CA1D8(p->m3c)) fn_801CAA24(p->m3c, 0, 0);
        {
            void* e = fn_800E3810((char*)lbl_803697B4, p);
            if (e) {
                Vec t;
                fn_801CA5D4(&t, p->m3c);
                *(W3*)&a = *(W3*)&t;
                Vec c = a;
                fn_800E48C8(e, &c);
            }
        }
    }
    if (p->m40) fn_801CB5EC(p->m40, p->x18, 0, 0x3C);
}
}
