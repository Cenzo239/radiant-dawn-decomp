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

f32 fn_800FD7F0(int a, int b) {
    int n;
    switch (a) {
    case 1:
        switch (b) {
        case 1: n = 0; return (f32)n;
        case 8: n = 0x13B; return (f32)n;
        case 4: n = 0xE1; return (f32)n;
        }
        break;
    case 2:
        switch (b) {
        case 2: n = 0xB4; return (f32)n;
        case 8: n = 0x2D; return (f32)n;
        case 4: n = 0x87; return (f32)n;
        }
        break;
    case 8:
        switch (b) {
        case 1: n = 0x87; return (f32)n;
        case 2: n = 0xE1; return (f32)n;
        case 8: n = 0x10E; return (f32)n;
        }
        break;
    case 4:
        switch (b) {
        case 1: n = 0x2D; return (f32)n;
        case 2: n = 0x13B; return (f32)n;
        case 3: break;
        case 4: n = 0x5A; return (f32)n;
        }
        break;
    }
    return 0.0f;
}

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

int fn_800FDA20(Mv* p, int x, int y, f32 f) {
    MapUnit* u;
    MapUnit* t;
    BOOL fast;
    void* parent;
    if ((p->h52 & 0x200) == 0) return 0;
    u = p->unit;
    if (x == u->mapX && y == u->mapY) return 0;
    t = UnitAt(x, y);
    if (t == 0) return 0;
    if (fn_800FAE08(t)) return 0;
    if (t == p->unit) return 0;
    fast = Fast(p);
    parent = 0;
    if (p->h52 & 0x80) parent = p->v18;
    {
        int dur = p->h34;
        if (fn_800F7724(t)) {
            Spawn* q = (Spawn*)fn_800811E4(lbl_803851F0, parent);
            q->u = t;
            q->f = f;
            q->flag = fast;
            q->dur = dur;
        }
    }
    return 1;
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
void fn_800FDBDC(Mv* p) {
    if (p->b55) {
        if (p->h52 & 0x40) fn_800FAFF0(p->unit, 0);
        Fx(lbl_80385090, p->unit, p);
        Fx(lbl_803850B0, p->unit, p);
    }
}

void fn_800FDCBC(Mv* p) {
    if (p->b55) {
        fn_800F651C(p->unit, p->f3A);
        fn_800F651C(p->unit, p->f3B);
        fn_800F651C(p->unit, p->f3C);
        fn_800F651C(p->unit, p->f3D);
    }
}

int fn_800FDD30(Mv* p) {
    if (p->b55) {
        if (fn_800F66F8(p->unit, p->f3A) == 0) return 1;
        if (fn_800F66F8(p->unit, p->f3B) == 0) return 1;
        if (fn_800F66F8(p->unit, p->f3C) == 0) return 1;
        if (fn_800F66F8(p->unit, p->f3D) == 0) return 1;
    }
    return 0;
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

void fn_800FED4C(Mv* p) {
    f32 fx, fy;
    s8 x, y;
    MapUnit* u;
    p->h34 = 0x10;
    u = p->unit;
    p->h38 = 0;
    p->b50 = 0xFF;
    p->b51 = 0xFF;
    fx = u->x;
    fy = u->y;
    x = fx;
    y = fy;
    switch (p->h52 & 0x30) {
    case 0x10:
        p->b50 = 0;
        break;
    case 0x20:
        p->b51 = 0;
        break;
    }
    if (G12()) {
        if (*((u8*)p->unit->unkF4 + 8) == 1) {
            if (lbl_803EC898.g1[x + y * 0x40] == 0) {
                fn_80083DC4(p, 0);
            }
        }
    }
}

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
void fn_800FEEF0(Mv* p) {
    u8 c = p->path[p->b54];
    Step(p->unit, c, Fast(p), p);
    p->b54 += 2;
    p->b44 += p->b44 - p->b42;
    p->b45 += p->b45 - p->b43;
    p->f5C[0] = p->f5C[3];
    p->f5C[1] = p->f5C[4];
    p->f5C[2] = p->f5C[5];
    p->f5C[3] = p->f5C[6];
    p->f5C[4] = p->f5C[7];
    p->f5C[5] = p->f5C[8];
    p->f5C[6] = p->f5C[9];
    p->f5C[7] = p->f5C[10];
    p->f5C[8] = p->f5C[11];
}

static inline void PA(MapUnit* u, char* name) {
    fn_80102928(u, fn_800F0994(name), 4, 0x20, 0);
}
void fn_800FF05C(Mv* p) {
    if (p->h52 & 0x40) {
        u8* c = lbl_803CAB38;
        int x = p->s44;
        int y = p->s45;
        *(f32*)(c + 0x934) = (f32)x;
        *(f32*)(c + 0x938) = (f32)y;
        fn_80062230(c, (f32)x, (f32)y);
        *(f32*)(c + 0x944) = (f32)x;
        *(f32*)(c + 0x948) = (f32)y;
    }
    PA(p->unit, (char*)lbl_80367D50 + 5);
}

void fn_800FF8C0(Mv* p) {
    p->h52 |= 0x8000;
    if ((p->h52 & 0x100) == 0) {
        int c = p->b56;
        MapUnit* u = p->unit;
        if (c != 0x40 && c != 0) {
            fn_80102E10(u, -1, 0, (f32)DirAngle(c), 0);
        }
    }
}

typedef struct CD2 { u8 pad0[0xC]; void* vC; u8 b10; } CD2;
typedef struct CD1 { u8 pad0[0x10]; CD2* v10; } CD1;
extern CD1* fn_800F47F4(MapUnit*);
extern s32 fn_80254F28(void*, Vec, f32, f32);
extern Ev* fn_8024F50C(s8);
extern double fn_80295CF0(double);

static inline BOOL CanFoot(Mv* p) {
    CD1* d = fn_800F47F4(p->unit);
    if (d == 0) return 0;
    if ((d->v10->b10 & 8) == 0) return 0;
    return fn_800F0994((char*)lbl_80367D50 + 5) == p->f3A;
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


void fn_800FFC58(Mv* p) {
    Ev* e;
    if (p->h52 & 0x80) {
        fn_800F39DC(p->unit);
        if ((p->h52 & 0x8000) == 0) {
            if ((p->h52 & 0x100) == 0) {
                int c = p->b56;
                MapUnit* u = p->unit;
                if (c != 0x40 && c != 0) {
                    fn_80102E10(u, 0, 0, (f32)DirAngle(c), 0);
                }
            }
            {
                MapUnit* u = p->unit;
                if (p->f3B != u->unkC7) {
                    fn_800F4B94(u, p->f3B);
                }
            }
        }
        {
            int v = 0xFF;
            if (p->h52 & 0x10) v = 0xFF;
            if (p->h52 & 0x20) {
                v = 0;
                p->unit->flags |= 0x20;
            }
            if (fn_8011F680(p->unit)) v = 0;
            fn_800F3F08(p->unit, v);
        }
    }
    p->unit->flags2 &= ~0x6000000000ULL;
    fn_800F3F14(p->unit, 1.0f);
    p->unit->flags &= ~0x4000;
    if ((s8)p->b57 >= 0 && p->v58) {
        e = fn_8024F50C(p->b57);
        if (e && e->v2()) {
            if (p->v58 != e->vC) {
                *(s8*)&p->b57 = -1;
                p->v58 = 0;
            } else {
                e->v7(1000);
                e->Stop();
            }
        }
    }
    fn_80078E24(p->v90);
    p->v90 = 0;
    fn_80078E24(p->path);
    p->path = 0;
}

typedef struct Node { s32 i; f32 z; f32 h; } Node;
typedef struct T2 { u8 pad[7]; u8 b7; } T2;
typedef struct T1 { u8 pad[8]; T2* v8; } T1;
extern int fn_8011806C(u8*);
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
        int dx, dy;
        u8* q;
        int x, y;
        char* b;
        y = (s8)p->b43;
        x = (s8)p->b42;
        b = (char*)lbl_80367D50;
        q = p->path;
        for (; *q != 0x40; q++) {
            int c = *q;
            dx = DX(c);
            dy = DY(c);
            if (fn_801181E8(&lbl_803EC898, (s8)(x + dx), (s8)(y + dy))->v8->b7 & 8) {
                f32 z = fn_80113F00(&lbl_803EC898, (f32)x, (f32)y);
                if (fn_80113F00(&lbl_803EC898, (f32)(x + dx * 2), (f32)(y + dy * 2)) < z) {
                    p->f3C = fn_800F0994(b + 0xB);
                } else {
                    p->f3D = fn_800F0994(b + 0x10);
                }
            }
            x += dx;
            y += dy;
        }
    }
}


void fn_80100384(Mv* p) {
    if (CanFoot(p) && (p->h52 & 0x400) == 0) {
        u8* q;
        Node* a;
        Node* b;
        int x, y;
        int i;
        MapUnit* u = p->unit;
        f32 fx = u->x;
        f32 fy = u->y;
        a = (Node*)p->v90;
        b = a;
        q = p->path;
        x = fx;
        y = fy;
        for (i = 0; i < 0x100; i++, q++, a++) {
            f32 z;
            f32 dz;
            if (p->h52 & 0x1000) {
                z = fn_801142F0(&lbl_803EC898, 0.5f + (f32)x, 0.5f + (f32)y);
            } else {
                z = fn_80113F00(&lbl_803EC898, 0.5f + (f32)x, 0.5f + (f32)y);
            }
            a->h = z;
            a->i = i;
            a->z = a->h;
            dz = a->z - b->z;
            if (dz < 0.0f) {
                int j;
                for (j = b->i + 1; j < a->i; j++) {
                    Node* n = (Node*)p->v90 + j;
                    n->z = fn_8001EF30(b->z, a->z, (f32)(a->i - b->i), (f32)(n->i - b->i));
                }
                b = a;
            }
            if (dz > 0.0f) {
                if (*q == 0x40) {
                    int k;
                    for (k = a->i; k >= b->i; k--) {
                        Node* n = (Node*)p->v90 + k;
                        if (a->h > n->h) {
                            b = n;
                            break;
                        }
                    }
                    {
                        int j;
                        for (j = b->i + 1; j < a->i; j++) {
                            Node* n = (Node*)p->v90 + j;
                            n->z = fn_8001EF30(b->z, a->z, (f32)(a->i - b->i), (f32)(n->i - b->i));
                        }
                    }
                } else {
                    a->z = b->z;
                }
            }
            if (*q == 0x40) return;
            switch (*q) {
            case 8: y--; break;
            case 4: y++; break;
            case 1: x--; break;
            case 2: x++; break;
            }
        }
    }
}
}
