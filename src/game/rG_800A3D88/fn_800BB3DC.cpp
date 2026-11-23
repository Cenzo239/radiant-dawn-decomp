#include "game/rG_800A3D88/types.h"

// Battle character: spawn the attack effect named by a battle event at the character's root.
extern "C" {
struct Vec { f32 x, y, z; };
struct W3 { u32 a, b, c; };
struct ChrU { u8 p[0x30]; void* mdl; u8 p34[0x58 - 0x34]; s16 m58; };
struct Ct { u8 p[0xE]; u8 me; };
struct Eo { u8 p[0x30]; Ct* m30; };
struct EfE { u8 p[8]; void* m8; };
extern char lbl_803657E8[];
#define STR(n) (lbl_803657E8 + (n))
int fn_801CFB10(void*);
#if TARGET_PC
FE10_PROTO void * fn_801CFF0C(void*, int);
FE10_PROTO EfE* fn_800A7E34(p32arg);
#else
int fn_801CFF0C(void*, int);
EfE* fn_800A7E34(int);
#endif
Eo* fn_800E3810(void*, ChrU*);
int fn_80007630(void*, const char*);
int fn_800B4000(ChrU*, int, Vec*, int, int);
void fn_800E48C8(Eo*, Vec*);
f32 fn_8001E064(int);
void fn_800E49AC(Eo*, f32);
static inline void* Find(void* ev) {
    if (ev == NULL) return NULL;
    if (fn_801CFB10(ev)) {
        EfE* e = fn_800A7E34(fn_801CFF0C(ev, fn_801CFB10(ev)));
        if (e != NULL && e->m8 != NULL) return e->m8;
    }
    return NULL;
}
static inline int Node(ChrU* c, const char* const& n) {
    int k;
    if (c->mdl == NULL) k = -1;
    else { int t = fn_80007630(c->mdl, n); k = t; }
    return k;
}
int fn_800BB3DC(ChrU* c, void* ev) {
    Vec a, t;
    void* s = Find(ev);
    if (s == NULL) return 0;
    Eo* o = fn_800E3810(s, c);
    if (o != NULL) {
        *(u32*)&t.x = 0;
        *(u32*)&t.y = 0;
        *(u32*)&t.z = 0;
        fn_800B4000(c, Node(c, STR(0x26)), &t, -1, 0);
        *(W3*)&a = *(W3*)&t;
        fn_800E48C8(o, &a);
        fn_800E49AC(o, fn_8001E064(c->m58));
        o->m30->me = 3;
        return 1;
    }
    return 0;
}
}
