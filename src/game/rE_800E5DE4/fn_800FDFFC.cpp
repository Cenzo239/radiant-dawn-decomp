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
    s16 h36;        /* 0x36 */
    s16 h38;        /* 0x38 */
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
static inline int DX(int c) {
    switch (c) {
    case 1: return -1;
    case 2: return 1;
    }
    return 0;
}
static inline int DY(int c) {
    switch (c) {
    case 4: return 1;
    case 8: return -1;
    }
    return 0;
}
static inline BOOL G12() { return lbl_804CB830 == 1 || lbl_804CB830 == 2; }
#define S8(f) (*(s8*)&(f))
static inline f32 Ht(Mv* p, int x, int y) {
    if (p->h52 & 0x1000) return fn_801142F0(&lbl_803EC898, 0.5f + x, 0.5f + y);
    return fn_80113F00(&lbl_803EC898, 0.5f + x, 0.5f + y);
}
void fn_800FDFFC(Mv* p) {
/*P*/
    int c;
    int x0;
    int y0;
    u8 nx;
    int x1;
    int y1;
    int ok;
/*E*/
    p->h38 = 0;
    c = p->path[p->b54];
    p->b42 = p->b44;
    p->b43 = p->b45;
    switch (c) {
    case 0x40:
        if (Fast(p)) {
            fn_80102928(p->unit, p->f3B, 8, 0, 0);
        } else {
            fn_80102928(p->unit, p->f3B, 0x10, 0, 0);
        }
        fn_80083DC4(p, 0);
        return;
    default:
        break;
    }
    p->b44 += DX(c);
    p->b45 += DY(c);
    x0 = S8(p->b42);
    y0 = S8(p->b43);
    x1 = S8(p->b44);
    y1 = S8(p->b45);
    nx = p->path[p->b54 + 1];
    fn_800FDA20(p, x1, y1, fn_800FD7F0(c, nx));
    if (CanFoot(p)) {
        p->f5C[-5] = ((E12*)p->v90)[p->b54].f4;
        p->f5C[-4] = ((E12*)p->v90)[p->b54 + 1].f4;
    } else {
        p->f5C[-5] = Ht(p, x0, y0);
        p->f5C[-4] = Ht(p, x1, y1);
        fn_8013C234(x1, y1, 0);
    }
    p->b50 = 0xFF;
    p->b51 = 0xFF;
    switch (p->h52 & 0x30) {
    case 0x10:
        if (p->b54 == 0) p->b50 = 0;
        break;
    case 0x20:
        if (p->b54 == p->b55 - 1) p->b51 = 0;
        break;
    }
    if (G12() && p->unit->unkF4->unk8 == 1) {
        if (lbl_803EC898.g0[x0 + y0 * 0x40 + 0x2000] == 0) p->b50 = 0;
        if (lbl_803EC898.g0[x1 + y1 * 0x40 + 0x2000] == 0) p->b51 = 0;
    }
    ok = 1;
    if (!CanFoot(p)) {
        if (fn_801181E8(&lbl_803EC898, x1, y1)->v8->b7 & 8) {
            fn_800F3F08(p->unit, p->b51);
            fn_80083DC4(p, 4);
        } else if (nx != 0x40) {
            int tx = p->s44 + DX(nx);
            if (fn_801181E8(&lbl_803EC898, (s8)tx, (s8)(p->b45 + DY(nx)))->v8->b7 & 8) ok = 0;
        }
    }
    {
        int dx = p->s44 - S8(p->b42);
        int dy = p->s45 - S8(p->b43);
        p->f5C[0] = p->f5C[3];
        p->f5C[1] = p->f5C[4];
        p->f5C[2] = p->f5C[5];
        p->f5C[3] = p->f5C[6];
        p->f5C[4] = p->f5C[7];
        p->f5C[5] = p->f5C[8];
        p->f5C[6] = p->f5C[9];
        p->f5C[7] = p->f5C[10];
        p->f5C[8] = p->f5C[11];
        if (p->b54 == 0) {
            p->f5C[0] = S8(p->b42) - dx;
            p->f5C[1] = S8(p->b43) - dy;
        }
        if (ok && nx != 0x40 && nx != (u32)c) {
            switch (nx) {
            case 1: x1--; break;
            case 2: x1++; break;
            case 4: y1++; break;
            case 8: y1--; break;
            }
            p->f5C[6] = ((S8(p->b42) + x1) / 2.0f + p->s44) / 2.0f;
            p->f5C[7] = ((S8(p->b43) + y1) / 2.0f + p->s45) / 2.0f;
            p->f5C[9] = x1;
            p->f5C[10] = y1;
        } else {
            p->f5C[6] = p->s44;
            p->f5C[7] = p->s45;
            p->f5C[9] = p->s44 + dx;
            p->f5C[10] = p->s45 + dy;
        }
    }
}
}
