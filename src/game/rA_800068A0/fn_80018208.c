#include "game/rA_800068A0/types.h"

/* GActor per-pass draw state and particle-as-instance drawing. */

typedef struct Vec { f32 x, y, z; } Vec;
typedef f32 Mtx[3][4];
typedef struct GColor { u8 r, g, b, a; } GColor;

typedef struct Part {
    Vec p;
    Vec v;
    f32 age;
    f32 x1C;
    f32 size;
    u8 pad24[8];
    GColor c;
    u8 pad30[0x1C];
} Part;
typedef struct Seg { u8 pad[6]; u16 flags; u8 pad8[0x16]; u16 count; u8 pad20[0x14]; } Seg;
typedef struct Buf { u8 pad[0xC]; Part* parts; u8 pad10[4]; } Buf;
typedef struct Info { u8 pad[4]; u16 flags; u16 n; Seg segs[1]; } Info;
typedef struct St { u8 pad[0x30]; Info* info; Buf* buf; } St;
typedef struct GA {
    u32 flags;
    u32 x4;
    GColor c;
    u32 xC;
    Mtx m;
    u8 pad40[0x14];
    St* st;
} GA;

extern void fn_80312344(const Mtx, Mtx);
extern void fn_8001E638(const Mtx, Mtx);
extern void fn_803128AC(Mtx, f32, f32, f32);
extern void fn_8031292C(Mtx, f32, f32, f32);
extern void fn_8001EACC(const Vec*, const Vec*, Mtx);
extern void fn_80312378(const Mtx, const Mtx, Mtx);
extern void fn_80018888(GA*, int);
extern Vec lbl_80360E3C;

int fn_80018208(GA* a, int pass) {
    St* st = a->st;
    if (st != 0) {
        Info* info = st->info;
        if (info->flags & 0x4000) {
            Seg* s = info->segs;
            Buf* b = st->buf;
            int n = info->n;
            while (n > 0) {
                if ((s->flags & 7) == 6) {
                    Mtx saved;
                    Mtx rot;
                    Mtx t;
                    Mtx sc;
                    Mtx q;
                    Mtx o;
                    Vec up;
                    GColor c;
                    Part* p = b->parts;
                    int i;
                    fn_80312344(a->m, saved);
                    c = a->c;
                    fn_8001E638(saved, rot);
                    for (i = 0; i < s->count; i++, p++) {
                        if (p->age >= 0.0f) {
                            up = lbl_80360E3C;
                            fn_803128AC(t, p->p.x, p->p.y, p->p.z);
                            fn_8031292C(sc, p->size, p->size, p->size);
                            fn_8001EACC(&up, &p->v, q);
                            fn_80312378(sc, rot, o);
                            fn_80312378(q, o, o);
                            fn_80312378(t, o, a->m);
                            a->c.r = p->c.r;
                            a->c.g = p->c.g;
                            a->c.b = p->c.b;
                            a->c.a = p->c.a;
                            fn_80018888(a, pass);
                        }
                    }
                    fn_80312344(saved, a->m);
                    a->c = c;
                    return 1;
                }
                s++;
                b++;
            }
        }
    }
    return 0;
}

extern void fn_80021860(int, int, int);
extern void fn_80021FE8(int);
extern void fn_80021FEC(int);
extern void fn_80021BA4(int, int, int, int);
extern void fn_80010980(void);

int fn_800184BC(GA* a, int pass) {
    u32 fl = a->flags;
    if ((fl & 0xE00273C0) == 0) {
        return 0;
    }
    switch (pass) {
    case 1:
    case 2:
        if (fl & 0x180) {
            if ((fl & 0xE0000000) == 0xA0000000) {
                fn_80021860(1, 3, 1);
            }
        } else if (fl & 0x2000) {
            fn_80021FE8(1);
        }
        break;
    case 3:
        break;
    }
    if (fl & 0x1000) {
        fn_80021FEC(0);
    }
    if (fl & 0x200) {
        fn_80021BA4(1, 4, 1, 0);
    }
    if (fl & 0x20000) {
        fn_80010980();
    }
    if (fl & 0x4000) {
        fn_80021BA4(0, 0, 0, 0);
    }
    switch ((s32)(fl & 0xE0000000)) {
    case 0x20000000:
        fn_80021860(0, 7, 0);
        break;
    case 0x40000000:
        fn_80021860(1, 4, 0);
        break;
    case 0x60000000:
        fn_80021860(1, 2, 0);
        break;
    case (s32)0x80000000:
        fn_80021860(1, 5, 0);
        break;
    case (s32)0xE0000000:
        fn_80021860(1, 3, 1);
        break;
    case (s32)0xC0000000:
        fn_80021860(1, 3, 0);
        break;
    }
    return 1;
}

extern u8* fn_8000F470(void);
extern int fn_80312494(const Mtx, Mtx);
extern void fn_80312DB4(const Mtx, const Vec*, Vec*);
extern void fn_803134C4(const Vec*, Vec*);
extern void fn_8031356C(const Vec*, const Vec*, Vec*);
extern f32 fn_80313508(const Vec*);
extern f32 fn_8001EA74(const Vec*, const Vec*);
extern void fn_80312830(Mtx, const Vec*, f32);
extern void fn_80312318(Mtx);
extern void fn_8001E9FC(const Mtx, const Mtx, Mtx, f32);

void fn_80018E48(Mtx m, Mtx out, f32 t) {
    u8* cam = fn_8000F470();
    Mtx r;
    Mtx id;
    Vec c;
    Vec a;
    Vec b;
    fn_80312344(m, out);
    if (cam != 0) {
        a = *(Vec*)(cam + 0xEC);
        b = *(Vec*)(cam + 0xEC);
        fn_80312494(out, r);
        fn_80312DB4(r, &b, &b);
        fn_803134C4(&b, &b);
        fn_8031356C(&a, &b, &c);
        if (fn_80313508(&c) > 0.0f) {
            f32 ang = fn_8001EA74(&a, &b);
            fn_80312830(r, &c, ang);
            fn_80312318(id);
            fn_8001E9FC(id, r, r, t);
            fn_80312378(r, m, out);
        }
    }
}

typedef struct CamI { u8 pad[8]; f32 x, y, z; } CamI;
typedef struct LightC { u8 pad[2]; u8 r, g, b; } LightC;
typedef struct LightD { u8 pad[4]; u8 r, g, b; } LightD;
typedef struct GA2 {
    u32 flags;
    u32 x4;
    GColor c;
    u32 xC;
    Mtx m;
    u8 pad40[0x40];
    u8 x80;
    u8 pad81[3];
    s32 x84;
} GA2;
typedef struct GRes48 { u8 pad[0x3C]; void* x3C; void* x40; } GRes48;

extern GRes48* fn_80007F3C(void*);
extern int fn_80015070(GRes48*, int, int);
extern f32 fn_8001E064(s16);
extern LightC* fn_80010C18(void);
extern CamI* fn_80010DA4(LightC*, int);
extern Vec lbl_80360E68;

void fn_8001A644(GA2* a);
/* fn_8001A644: near miss, 6 of 196 words differ. Depends on types and helpers from ../fn_80018208.c; goes there in address order. */
void fn_8001A644(GA2* a) {
    GRes48* m = fn_80007F3C(a);
    if (fn_80015070(m, 0x100, 0) > 0) {
        Mtx saved;
        Mtx sh;
        Mtx t;
        Mtx o;
        Vec d;
        GColor c;
        u32 fl;
        u8 x80;
        f32 h;
        LightC* l;
        CamI* cam;
        int v0;
        int v1;
        int al;
        int k;
        fn_80312344(a->m, saved);
        fl = a->flags;
        c = a->c;
        a->flags = (fl & 0x200000) | 0xC001F800;
        d = lbl_80360E68;
        x80 = a->x80;
        h = fn_8001E064(a->x84);
        fn_803128AC(t, 0.0f, -h, 0.0f);
        fn_80312378(t, a->m, o);
        l = fn_80010C18();
        cam = fn_80010DA4(l, 1);
        if (cam != 0) {
            d.x = -cam->x;
            d.y = 2.0f * -cam->y;
            d.z = -cam->z;
        }
        fn_80312318(sh);
        sh[0][1] = -d.x / d.y;
        sh[1][1] = 0.0f;
        sh[2][1] = -d.z / d.y;
        fn_80312378(sh, o, o);
        fn_803128AC(t, 0.0f, h + 0.025, 0.0f);
        fn_80312378(t, o, a->m);
        a->c.r = 0;
        a->c.g = 0;
        a->c.b = 0;
        v0 = (l->r + l->g + l->b) / 3;
        v1 = v0;
        if (cam != 0) {
            v1 = (((LightD*)cam)->r + ((LightD*)cam)->g + ((LightD*)cam)->b) / 3;
        }
        k = v1 * (0xFF - v0) / 255;
        if (k < 0) {
            k = 0;
        }
        if (k > 0xC0) {
            k = 0xC0;
        }
        a->x80 = a->c.a * k / 255;
        a->c.a = 0xFF;
        if (m->x3C != 0 && fn_80018208((GA*)a, 1) == 0) {
            fn_80018888((GA*)a, 1);
        }
        if (m->x40 != 0 && fn_80018208((GA*)a, 2) == 0) {
            fn_80018888((GA*)a, 2);
        }
        fn_80312344(saved, a->m);
        a->flags = fl;
        a->c = c;
        a->x80 = x80;
    }
    fn_80015070(m, 0, 4);
}
