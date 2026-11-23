#include "game/rE_800E5DE4/mapunit.h"
#pragma auto_inline off

typedef struct Mtx34 { f32 m[3][4]; } Mtx34;
typedef struct Vec2f { f32 x, y; } Vec2f;
struct KBase { u8 pad[0x44]; };
class KVt : public KBase {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void Play(void*, void*, int);
    virtual void Play2(void*, void*, int, int, int, int);
};
typedef struct OptB { u8 pad[0x11]; u8 b11; } OptB;
typedef struct UProcM { u8 pad[0x30]; MapUnit* u; } UProcM;
typedef struct CD2 { u8 pad0[4]; void* v4; void* v8; void* vC; void* v10_; } CD2;
typedef struct Tile2 { u8 pad[7]; u8 b7; void* v8; void* vC; void* v10; } Tile2;
typedef struct Tile { u8 pad[8]; Tile2* v8; } Tile;
typedef struct CD1 { u8 pad0[0x10]; struct { u8 pad[4]; void* v4; void* v8; void* vC; u8 b10; }* v10; } CD1;

extern "C" {
extern u8 lbl_803CAB38[];
extern KVt lbl_803E7290_obj;
extern u8 lbl_803E7290[];
extern u8 lbl_804CB740;
extern u8 lbl_804CA4AC;
extern Vec2f lbl_803E8FD8;
extern Vec2f lbl_803E8FE4;
extern u8 lbl_803EC898[];
extern void fn_80313460(Vec*, Vec*, Vec*);
#if TARGET_PC
extern FE10_PROTO void fn_80011B90(p32arg, Vec*, Vec*);
#else
extern void fn_80011B90(int, Vec*, Vec*);
#endif
extern void fn_80312654(Mtx34*, int, f32);
extern void fn_8031292C(Mtx34*, f32, f32, f32);
extern void fn_803128AC(Mtx34*, f32, f32, f32);
extern void fn_80312378(Mtx34*, Mtx34*, void*);
extern int fn_801196F0(u8);
extern OptB* fn_80060728(void*);
extern CD1* fn_800F47F4(MapUnit*);
extern int fn_80008C98(void*, int);
extern int fn_80118098(void*, int, int);
extern int fn_8011D260(u8);
extern Tile* fn_8010B240(u8);
extern Vec fn_800076E8(void*, s8);
extern void fn_800FB904(s16, f32, f32);
extern int fn_800E4588(void);
extern f32 fn_80113F00(void*, f32, f32);
extern u8* fn_8013B9A8(void);
#if TARGET_PC
extern FE10_PROTO unsigned char * fn_80068DE4(void);
extern FE10_PROTO void* fn_800E3810(void*, p32arg);
#else
extern int fn_80068DE4(void);
extern void* fn_800E3810(void*, int);
#endif
extern void fn_800E48AC(void*, f32, f32, f32);
extern void fn_800E49AC(void*, f32);
extern int fn_80008EB4(void*);
extern Vec fn_800F7790(MapUnit*);
extern Tile* fn_801181E8(void*, int, int);
extern void fn_802549C4(void*, Vec, f32);
extern void fn_80254F28(void*, Vec, f32, f32);
extern void fn_800F172C(void*, Vec*);
extern void fn_800F1F88(void*);
extern void fn_8013C14C(int, int, void*, f32);

static inline BOOL InRect(Vec v, f32 f) {
    f32 a = -f;
    if (v.x > a && v.x < 608.0f + f && v.y > 1.25f * a && v.y < 1.5f * f + 448.0f) return 1;
    return 0;
}
static inline void Grow(Vec v) {
    if (lbl_803E8FD8.x > v.x) lbl_803E8FD8.x = v.x;
    if (lbl_803E8FD8.y > v.y) lbl_803E8FD8.y = v.y;
    if (lbl_803E8FE4.x < v.x) lbl_803E8FE4.x = v.x;
    if (lbl_803E8FE4.y < v.y) lbl_803E8FE4.y = v.y;
}

static inline u8 Kind(MapUnit* m) {
    u8 k = *((u8*)m + 0x118);
    if ((s8)k == -1) k = *(*(u8**)((u8*)m + 0xEC) + 0xE1);
    return k;
}



void fn_800F7A98(MapUnit* m) {
    Mtx34 t, rx, ry, s;
    Vec a = *(Vec*)&m->x;
    Vec b = *(Vec*)&m->offX;
    f32 ang = 0.015625f * (f32)m->angle;
    f32 sc = 0.0001f * (0.06f * (f32)(m->unkC6 * lbl_804CA4AC));
    fn_80313460(&a, &b, &a);
    fn_80312654(&ry, 0x59, 0.017453292f * ang);
    fn_80312654(&rx, 0x58, 4.712389f);
    fn_8031292C(&s, sc, sc, sc);
    fn_803128AC(&t, a.x, a.y, a.z);
    fn_80312378(&ry, &s, &s);
    fn_80312378(&rx, &s, &s);
    fn_80312378(&t, &s, (u8*)m + 0x38);
}
}
