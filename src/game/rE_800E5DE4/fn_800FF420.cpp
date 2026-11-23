#include "game/rE_800E5DE4/mapunit.h"
#pragma auto_inline off

/* Map-unit movement process (guessed): walks a MapUnit along a path string of
 * direction bytes at +0x8C, 800FD7F0..800FFFDC. */
typedef struct Probe { u8 pad[0x30]; void* a; } Probe;

typedef struct Mv {
    u8 pad0[0x18];
    void* v18;      /* 0x18 */
    u8 pad1C[0x14];
    MapUnit* unit;  /* 0x30 */
    u16 h34;        /* 0x34 */
    u16 h36;        /* 0x36 */
    u16 h38;        /* 0x38 */
    s8 f3A;         /* 0x3A */
    s8 f3B;         /* 0x3B */
    s8 f3C;         /* 0x3C */
    s8 f3D;         /* 0x3D */
    s16 h3E;        /* 0x3E */
    s16 h40;        /* 0x40 */
    u8 b42, b43;    /* 0x42 */
    union { struct { u8 b44, b45; }; struct { s8 s44, s45; }; }; /* 0x44 */
    u8 b46, b47;    /* 0x46 */
    u8 pad48[8];
    u8 b50, b51;    /* 0x50 */
    u16 h52;        /* 0x52 */
    u8 b54, b55, b56; /* 0x54 */
    u8 b57;         /* 0x57 */
    void* v58;      /* 0x58 */
    f32 f5C[12];    /* 0x5C */
    u8* path;       /* 0x8C */
    u8* v90;        /* 0x90 */
} Mv;

typedef struct Spawn {
    u8 pad[0x30];
    MapUnit* u;   /* 0x30 */
    u8 pad34[4];
    s32 dur;      /* 0x38 */
    f32 f;        /* 0x3C */
    u8 pad40[0x2C];
    u8 flag;      /* 0x6C */
} Spawn;

typedef struct Opt { u8 pad[4]; u32 hi : 6; u32 mode : 2; u32 rest : 24; } Opt;

class Ev {
public:
    virtual void v0();
    virtual void Stop();
    virtual int v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7(int);
    void* vC_pad[2];
    void* vC;
};
class Pad {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual u32 Held();
};

typedef struct CharFlags { u8 pad0[0x14]; u8 b14; } CharFlags;
typedef struct CharDesc { u8 pad0[0x10]; CharFlags* sub; } CharDesc;
typedef struct P46B0 { u8 pad[0x30]; MapUnit* u; u16 b; u8 pad36[0x32]; s16 h; u8 pad6A[2]; u8 c; } P46B0;

extern "C" {
typedef struct MapData { u8 pad[0xD]; u8 g0[0x2000]; u8 g1[0x1000]; } MapData;
extern MapData lbl_803EC898;
extern const f32 lbl_804CDB4C;
extern u8 lbl_803CAB38[];
extern u8 lbl_80385090[];
extern u8 lbl_803850B0[];
extern u8 lbl_803851F0[];
extern u8 lbl_803855CC[];
extern u8 lbl_80367D50[];
extern u8* lbl_804CB810;
extern u8 lbl_804CB830;
extern Pad* lbl_804CB5B8;
extern int fn_800FAE08(MapUnit*);
extern void fn_800FAFF0(MapUnit*, int);
extern Opt* fn_80060728(void*);
extern int fn_800F7724(MapUnit*);
extern void* fn_800811E4(void*, void*);
extern void* fn_800893E4(void*, void*, Probe*);
extern void* fn_80081050(void*, void*);
extern void fn_80104A70(void* a, void* b);
extern void fn_800F651C(MapUnit*, int);
extern int fn_800F66F8(MapUnit*, int);
extern void fn_80083DC4(void*, int);
#if TARGET_PC
extern FE10_PROTO void fn_80102928(MapUnit*, int, int, int, p32arg);
extern FE10_PROTO void fn_80102E10(MapUnit*, int, p32arg, f32, void*);
#else
extern void fn_80102928(MapUnit*, int, int, int, int);
extern void fn_80102E10(MapUnit*, int, int, f32, void*);
#endif
extern void fn_800FFEB8(Mv*, Vec*);
extern int fn_800F0994(char*);
extern void fn_80062230(u8*, f32, f32);
extern CharDesc* fn_800F43F0(MapUnit*);

typedef struct T2 { u8 pad[7]; u8 b7; } T2;
typedef struct T1 { u8 pad[8]; T2* v8; } T1;
typedef struct CF1 { u8 pad[0x10]; u8 b10; } CF1;
typedef struct CD1 { u8 pad[0x10]; CF1* v10; } CD1;
typedef struct E12 { f32 a; f32 f4; f32 b; } E12;
extern f32 fn_800FD7F0(int, int);
extern int fn_800FDA20(Mv*, int, int, f32);
extern CD1* fn_800F47F4(MapUnit*);
extern f32 fn_801142F0(void*, f32, f32);
extern f32 fn_80113F00(void*, f32, f32);
#if TARGET_PC
extern FE10_PROTO void fn_8013C234(int, int, p32arg);
#else
extern void fn_8013C234(int, int, int);
#endif
extern T1* fn_801181E8(void*, int, int);
extern void fn_800F3F08(MapUnit*, int);
static inline BOOL Fast(Mv* p) {
    if ((p->h52 & 0x80) == 0) {
        switch (fn_80060728(lbl_803CAB38)->mode) {
        case 1:
            if (lbl_804CB5B8->Held() & 0xFFF0) return 1;
            break;
        case 2:
            return 1;
        }
    }
    return 0;
}
static inline BOOL CanFoot(Mv* p) {
    CD1* d = fn_800F47F4(p->unit);
    if (d == 0) return 0;
    if ((d->v10->b10 & 8) == 0) return 0;
    return fn_800F0994((char*)lbl_80367D50 + 5) == p->f3A;
}

struct Ev2 { virtual void v0(); virtual void v1(); virtual int v2(); };
class Ev3 { public:
    virtual void v0(); virtual void v1(); virtual int v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
    virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
    virtual void v40(); virtual void v41(); virtual void Set(Vec);
    void* p4; void* p8; void* vC;
};
struct V : Vec { V(const Vec& o) { x = o.x; y = o.y; z = o.z; } };
extern Ev3* fn_8024F50C(s8 i);
extern void fn_800F3F14(MapUnit*, f32);
extern void fn_80083B78(void*);
extern void fn_8001F0A4(Vec*, Vec*, Vec*, Vec*);
extern f32 fn_8001EFE4(f32, f32, f32, f32, f32);
extern f32 fn_8001EF30(f32, f32, f32, f32);
extern f32 fn_80176A4C(f32, f32, f32, f32);
extern void fn_80312654(f32 (*)[4], int, f32);
extern void fn_80312DB4(f32 (*)[4], Vec*, Vec*);
#define F48 f5C[-5]
#define F4C f5C[-4]
#define CPY(n) *(Vec*)&a[n] = *(Vec*)&p->f5C[(n)*3];
#define S8(f) (*(s8*)&(f))
typedef struct W2 { u32 a, b; } W2; typedef struct WA { W2 ab; u32 c; } WA;
void fn_800FF420(Mv* p) {
    int dur = p->h34 * p->h36 / 256;
    f32 sp = 1.0f;
    if (p->h40 >= 0) sp *= p->h40 / 100.0f;
    if (p->h52 & 0x800) sp *= -1.0f;
    fn_800F3F14(p->unit, sp);
    p->h38 += 1;
    if ((u16)p->h38 >= dur) {
        p->h38 = dur;
        p->b54 += 2;
        fn_80083B78(p);
    }
    {
        Vec k[4] = {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}};
        *(WA*)&k[0] = *(WA*)&((Vec*)p->f5C)[0];
        *(WA*)&k[1] = *(WA*)&((Vec*)p->f5C)[1];
        *(WA*)&k[2] = *(WA*)&((Vec*)p->f5C)[2];
        *(WA*)&k[3] = *(WA*)&((Vec*)p->f5C)[3];
        fn_8001F0A4(&k[0], &k[1], &k[2], &k[3]);
        f32 t = (f32)(u16)p->h38 / dur;
        f32 x = 0.5f + fn_8001EFE4(k[0].x, k[1].x, k[2].x, k[3].x, t);
        f32 y = 0.5f + fn_8001EFE4(k[0].y, k[1].y, k[2].y, k[3].y, t);
        f32 z;
        if (p->h52 & 0x1000) {
            z = fn_801142F0(&lbl_803EC898, x, y);
        } else {
            z = fn_80113F00(&lbl_803EC898, x, y);
        }
        f32 x2 = 0.5f + fn_8001EFE4(k[0].x, k[1].x, k[2].x, k[3].x, 0.01f + t);
        f32 y2 = 0.5f + fn_8001EFE4(k[0].y, k[1].y, k[2].y, k[3].y, 0.01f + t);
        f32 r = fn_80176A4C(x, y, x2, y2);
        if (!(p->h52 & 0x100)) fn_80102E10(p->unit, 8, 0, r, 0);
        {
            MapUnit* u = p->unit;
            u->x = x;
            u->y = y;
            u->z = z;
        }
        if (p->h52 & 0x40) {
            u8* g = lbl_803CAB38;
            *(f32*)(g + 0x934) = x;
            *(f32*)(g + 0x938) = y;
            fn_80062230(g, x, y);
            *(f32*)(g + 0x944) = x;
            *(f32*)(g + 0x948) = y;
        }
        if (S8(p->b46) != (int)x || S8(p->b47) != (int)y) {
            f32 fx = x - (int)x - 0.5f;
            f32 fy = y - (int)y - 0.5f;
            if (fx >= -0.25f && fy >= -0.25f && fx <= 0.25f && fy <= 0.25f) {
                f32 m[3][4];
                Vec v = {1.0f, 1.0f, 0.0f};
                fn_80312654(m, 0x7A, 0.017453292f * -r);
                fn_80312DB4(m, &v, &v);
                if (v.x * v.y < 0.0f) {
                    r -= 90.0f;
                } else {
                    r += 90.0f;
                }
                fn_800FDA20(p, (int)x, (int)y, r);
                p->b46 = (int)x;
                p->b47 = (int)y;
            }
        }
    }
}
}
