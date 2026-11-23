/* fn_800EB048: 6 of 139 words. The zero used for the Vec words and h88 is r30, r29 in the original (which then reuses r29 for fn_800EA848). */
#include "game/rE_800E5DE4/types.h"
#include "game/rE_800E5DE4/evproc.h"
#pragma auto_inline off

typedef struct EvX {
    EvProc b;
    f32 f84;   /* 0x84 */
    s16 h88;   /* 0x88 */
    s16 h8A;   /* 0x8A */
    f32 f8C;   /* 0x8C */
} EvX;

extern u8 lbl_8036707C[];
extern u8 lbl_803CAB38[];
extern f32 fn_80313508(Vec*);
extern f32 fn_80176A4C(f32, f32, f32, f32);
extern void fn_800E4AD4(EvCmd*, f32);
extern void fn_800E49AC(EvCmd*, f32);
extern void fn_800EA848(EvCmd*);
extern void fn_800EA894(EvCmd*);

static inline void Init(EvX* p) {
    Vec v;
    u32 z = 0;
    *(u32*)&v.x = z;
    *(u32*)&v.y = z;
    *(u32*)&v.z = z;
    v.x = (f32)(p->b.unk7E - p->b.unk7C);
    v.y = (f32)(p->b.unk7F - p->b.unk7D);
    p->f8C = fn_80313508(&v);
    p->h88 = z;
    p->h8A = 8.0f * p->f8C;
    if (p->h8A <= 0) p->h8A = 1;
}
void fn_800EB048(EvX* p) {
    void (*u2)(EvCmd*);
    void (*u1)(EvCmd*);
    EvCmd* c;
    f32 a;
    Init(p);
    a = fn_80176A4C((f32)p->b.unk7C, (f32)p->b.unk7D, (f32)p->b.unk7E, (f32)p->b.unk7F);
    u1 = fn_800EA848;
    u2 = fn_800EA894;
    c = fn_800E3810((char*)lbl_8036707C + 0x1EF, p);
    if (c) {
        fn_800E4904(c, 0, p);
        fn_800E48F0(c, 1, 0);
        c->ctl->onUpdate = u1;
        c->ctl->onEvent = u2;
        c->ctl->flags |= 0x901;
        fn_800E4AD4(c, 1.5f);
        fn_800E49AC(c, a);
    }
    fn_800620A8(lbl_803CAB38, (f32)p->b.unk7E, (f32)p->b.unk7F);
}
