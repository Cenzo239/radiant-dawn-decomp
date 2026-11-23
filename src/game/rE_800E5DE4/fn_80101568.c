/* fn_80101568: exact (round 18). Helpers from fn_801006F0.c (exported bodies removed); same shape as fn_80101268. */
#include "game/rE_800E5DE4/mapunit.h"
#pragma auto_inline off

typedef union PSlot {
    s32 i;
    u32 u;
    f32 f;
    u16 h;
    GXColor c;
    void* p;
    MapUnit* m;
} PSlot;

typedef struct UProc {
    u8 pad0[0x30];
    MapUnit* unit; /* 0x30 */
    PSlot s34;     /* 0x34 */
    PSlot s38;     /* 0x38 */
    PSlot s3C;     /* 0x3C */
    PSlot s40;     /* 0x40 */
    PSlot s44;     /* 0x44 */
    PSlot s48;     /* 0x48 */
    PSlot s4C;     /* 0x4C */
    PSlot s50;     /* 0x50 */
} UProc;

typedef struct Probe { u8 pad[0x30]; void* a; } Probe;

extern u8 lbl_80367D50[];
extern u8 lbl_8038536C[];
extern u8 lbl_80385120[];
extern u8 lbl_80385148[];
extern void* fn_800811E4(void*, void*);
extern void* fn_800893E4(void*, void*, Probe*);
#if TARGET_PC
extern FE10_PROTO void* fn_80081050(void*, void *);
#else
extern void* fn_80081050(void*, int);
#endif
extern void fn_80104A70(void* a, void* b);
extern void fn_800F6604(MapUnit*, char*);
#if TARGET_PC
extern FE10_PROTO int fn_800F0994(char*);
#else
extern void* fn_800F0994(char*);
#endif
#if TARGET_PC
extern FE10_PROTO void fn_80102928(MapUnit*, int, int, int, void *);
#else
extern void fn_80102928(MapUnit*, void*, int, int, int);
#endif
extern u32 fn_800F201C(int);
extern f32 fn_8001EDF8(int, f32, f32, f32, f32);
extern void fn_800F3B50(MapUnit*, f32, f32);
extern void fn_80083B78(void*);
extern void fn_80083DC4(void*, int);
extern f32 fn_800FB08C(MapUnit*, MapUnit*);
extern f32 fn_800FB100(MapUnit*, f32, f32);
#if TARGET_PC
extern FE10_PROTO void fn_80102E10(MapUnit*, int, void *, f32, void*);
#else
extern void fn_80102E10(MapUnit*, int, int, f32, void*);
#endif
extern void fn_800F3F08(MapUnit*, int);
extern int fn_80008C98(void*, int);
void* fn_80100A04(MapUnit* u, s32 a, s32 b, void* parent);

void fn_801006F0(UProc* p);


static inline void U2C(GXColor* c, u32 v) {
    u32 t;
    c->a = v;
    t = v >> 24;
    c->r = t;
    t = v >> 16;
    c->g = t;
    t = v >> 8;
    c->b = t;
}
static inline void SpawnFade(MapUnit* u) {
    GXColor c;
    Probe s;
    UProc* q;
    s.a = u;
    fn_800893E4(lbl_80385120, fn_80104A70, &s);
    q = fn_80081050(lbl_80385120, 3);
    q->unit = u;
    q->s40.i = 2;
    U2C(&c, fn_800F201C(1));
    q->s38.c = c;
}
static inline void PA(MapUnit* u, char* name) {
    fn_80102928(u, fn_800F0994(name), 2, 0, 0);
}
void fn_80100834(UProc* p);


static inline void Face(MapUnit* a, MapUnit* b, void* p) {
    if (b) {
        fn_80102E10(a, 0x10, 0, (f32)(int)fn_800FB08C(a, b), p);
    }
}
void fn_80100FA4(UProc* p);


static inline f32 L(f32 a, f32 b, int n, f32 t) { return fn_8001EDF8(2, a, b, (f32)n, t); }
void fn_801013EC(UProc* p);

void fn_80101268(UProc* p);


typedef struct MC { u8 pad[0x30]; MapUnit* u; } MC;
void fn_801016F8(UProc* p);

void fn_801018BC(UProc* p);


extern void fn_800E24F8(char*);
extern int fn_8028DB44(int);
extern int fn_8011B77C(void*, void*);
extern void* lbl_804CA524;
extern void fn_800F6604(MapUnit*, char*);
extern void* fn_800E3A10(char*, void*);
extern void fn_800E48AC(void*, f32, f32, f32);
extern void fn_8017DB90(int, int, int, int, void*);
#if TARGET_PC
FE10_PROTO void fn_80101B80(void *);
#else
void fn_80101B80();
#endif
void fn_80100A68(UProc* p);


typedef struct EvC { u8 pad[0x30]; struct { u8 pad[0x9C]; void* cb; }* ctl; } EvC;
void fn_80101C60(UProc* p);


/* fn_80101568: start of the "appear at another unit" slide: remember the owner's position, take the target
   unit's position as the goal, turn the owner towards it and face the sprite the same way, alpha 0. */
void fn_80101568(UProc* p) {
    MapUnit* u;
    p->s50.f = 0.0f;
    u = p->unit;
    p->s3C.f = u->x;
    p->s40.f = u->y;
    fn_800F3B50(p->s34.m, p->s3C.f, p->s40.f);
    p->s48.f = p->s38.m->x;
    p->s4C.f = p->s38.m->y;
    u = p->unit;
    {
    int y = p->s4C.f;
    int x = p->s48.f;
    fn_80102E10(u, 0x10, 0, (f32)(int)fn_800FB100(u, 0.5f + (f32)x, 0.5f + (f32)y), p);
    }
    p->s34.m->angle = 64.0f * fn_800FB100(p->s34.m, p->s48.f, p->s4C.f);
    fn_800F3F08(p->s34.m, 0);
}
