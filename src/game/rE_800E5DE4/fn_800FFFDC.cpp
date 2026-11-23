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

static inline MapUnit* UnitAt(s8 x, s8 y) {
    u8 id = lbl_803EC898.g0[x + y * 0x40];
    return id ? (MapUnit*)(lbl_804CB810 + (id - 1) * 0x3F0) : 0;
}



static inline void* Fx(u8* cls, MapUnit* u, void* parent) {
    Probe s;
    Mv* q;
    s.a = u;
    fn_800893E4(cls, fn_80104A70, &s);
    if (parent == 0) parent = (void*)3;
    q = (Mv*)fn_80081050(cls, parent);
    q->unit = u;
    return q;
}






static inline int DirAngle(int c) {
    int n;
    switch (c) {
    case 4: n = 0; break;
    case 6: n = 0x2D; break;
    case 2: n = 0x5A; break;
    case 10: n = 0x87; break;
    case 8: n = 0xB4; break;
    case 9: n = 0xE1; break;
    case 1: n = 0x10E; break;
    case 5: n = 0x13B; break;
    default: n = 0; break;
    }
    return n;
}


static inline BOOL G12() { return lbl_804CB830 == 1 || lbl_804CB830 == 2; }



static inline P46B0* Step(MapUnit* u, int c, int fast, void* parent) {
    P46B0* q = (P46B0*)fn_800811E4(lbl_803855CC, parent);
    CharDesc* d = fn_800F43F0(u);
    q->u = u;
    q->b = c;
    q->c = fast;
    q->h = d->sub->b14 * 10;
    if (fast) q->h = 0x42;
    return q;
}


static inline void PA(MapUnit* u, char* name) {
    fn_80102928(u, fn_800F0994(name), 4, 0x20, 0);
}




typedef struct CD2 { u8 pad0[0xC]; void* vC; u8 b10; } CD2;
typedef struct CD1 { u8 pad0[0x10]; CD2* v10; } CD1;
extern CD1* fn_800F47F4(MapUnit*);
extern s32 fn_80254F28(void*, Vec, f32, f32);
extern Ev* fn_8024F50C(s8);
extern double fn_80295CF0(double);

#pragma pool_strings on
void pool_7d50() {
    const char* volatile s;
    s = "\x95""\xe0""\x82""\xab"""; /* 0x0 */
    s = "\x88""\xda""\x93""\xae"""; /* 0x5 */
    s = ""; /* 0xa */
    s = "\x93""o\x82""\xe8"""; /* 0xb */
    s = "\x8d""~\x82""\xe8"""; /* 0x10 */
    s = "\x83""_\x83""\x81""\x81""[\x83""W"; /* 0x15 */
    s = "EID_SMITE"; /* 0x1e */
    s = "EID_TACKLE"; /* 0x28 */
    s = "\x91""\xcc""\x93""\x96""\x82""\xbd""\x82""\xe8"""; /* 0x33 */
    s = "SFX_BMP_DAMAGE_TACKLE1"; /* 0x3c */
    s = "EID_QUICK_REWARP_F1"; /* 0x53 */
    s = "EID_QUICK_REWARP_T1"; /* 0x67 */
    s = "EID_QUICK_REWARP_W1"; /* 0x7b */
    s = "EID_QUICK_REWARP1"; /* 0x8f */
    s = "EID_RESCUE1"; /* 0xa1 */
    s = "EID_QUICK_REWARP_F2"; /* 0xad */
    s = "EID_QUICK_REWARP_T2"; /* 0xc1 */
    s = "EID_QUICK_REWARP_W2"; /* 0xd5 */
    s = "EID_QUICK_REWARP2"; /* 0xe9 */
    s = "EID_RESCUE2"; /* 0xfb */
    s = "\x95""\xcf""\x90""g"; /* 0x107 */
    s = "EID_INCARNATION"; /* 0x10c */
    s = "\x8e""\x80""\x96""S"; /* 0x11c */
    s = "SFX_BMP_FADE_DIE_AWAY1"; /* 0x121 */
    s = "\x91""\xd2""\x8b""@"; /* 0x138 */
}

static inline BOOL CanFoot(Mv* p) {
    CD1* d = fn_800F47F4(p->unit);
    if (d == 0) return 0;
    if ((d->v10->b10 & 8) == 0) return 0;
    return fn_800F0994("\x88""\xda""\x93""\xae""") == p->f3A;
}
static inline void MkVec(Vec* o, f32 x, f32 y, f32 z) {
    o->x = x;
    o->y = y;
    o->z = z;
}


extern s8 fn_800D858C(void);
extern s8 fn_800D907C(void);
extern s16 fn_800D868C(void);
extern s16 fn_800D878C(void);
extern int fn_800F4628(MapUnit*, int);
extern s8 fn_800F760C(MapUnit*);
extern u8* fn_80078D9C(int, char*, int);
extern void fn_800F3F08(MapUnit*, int);
extern void fn_800F39DC(MapUnit*);
extern void fn_800F4B94(MapUnit*, int);
extern int fn_8011F680(MapUnit*);
extern void fn_800F3F14(MapUnit*, f32);
extern void fn_80078E24(u8*);




typedef struct Node { s32 i; f32 z; f32 h; } Node;
typedef struct T2 { u8 pad[7]; u8 b7; } T2;
typedef struct T1 { u8 pad[8]; T2* v8; } T1;
extern int fn_8011806C(const u8*);
extern T1* fn_801181E8(void*, int, int);
extern f32 fn_80113F00(void*, f32, f32);
extern f32 fn_801142F0(void*, f32, f32);
extern f32 fn_8001EF30(f32, f32, f32, f32);

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
static inline void Flip(Mv* p) {
    int r;
    switch (p->b56) {
    case 1: r = 2; break;
    case 2: r = 1; break;
    case 4: r = 8; break;
    case 8: r = 4; break;
    default: r = 0x40; break;
    }
    p->b56 = r;
}

static inline void Tail(Mv* p) {
    if ((p->h52 & 0x400) == 0 && !CanFoot(p)) {
        int y;
        int x;
        u8* q;
        int dy;
        int dx;
        x = *(s8*)&p->b42;
        y = *(s8*)&p->b43;
        q = p->path;
        for (; *q != 0x40; q++) {
            int c = *q;
switch (c) { case 1: dx = -1; break; case 2: dx = 1; break; default: dx = 0; break; }
switch (c) { case 4: dy = 1; break; case 8: dy = -1; break; default: dy = 0; break; }
            if (fn_801181E8(&lbl_803EC898, (s8)(x + dx), (s8)(y + dy))->v8->b7 & 8) {
                f32 z = fn_80113F00(&lbl_803EC898, (f32)x, (f32)y);
                if (fn_80113F00(&lbl_803EC898, (f32)(x + dx * 2), (f32)(y + dy * 2)) < z) {
                    p->f3C = fn_800F0994("\x93""o\x82""\xe8""");
                } else {
                    p->f3D = fn_800F0994("\x8d""~\x82""\xe8""");
                }
            }
            x += dx;
            y += dy;
        }
    }
}



void fn_800FFFDC(Mv* p, const u8* s) {
    int n = fn_8011806C(s);
    int i;
    u8* d = p->path + p->b55;
    for (i = 0; i < n; i++) {
        u8 c = *s++;
        p->b56 = c;
        *d++ = c;
    }
    *d = 0x40;
    p->b55 += n;
    if (p->h52 & 0x400) p->b56 = 0x40;
    {
        int k = p->h52 & 0xF;
        if (k) p->b56 = k;
    }
    if (p->h52 & 0x800) Flip(p);
    Tail(p);
}

}
