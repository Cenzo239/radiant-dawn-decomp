#include "game/rG_800A3D88/types.h"

// Attached effect: follow the bones of the model it is attached to, then apply scale and offset.
extern "C" {
typedef f32 Mt[3][4];
struct Bone { u8 p[4]; Bone* m4; Bone* m8; u8 pc[4]; Mt m10; u8 p40[0xEC - 0x40]; u32 ec; };
struct EMdl { u8 p[0x10]; Mt m10; u8 p40[0x64 - 0x40]; void* m64; u8 p68[0x84 - 0x68]; int m84; };
struct EAtt { u8 p[0x30]; EMdl* m30; u8 p34[0x5C - 0x34]; s16 m5c; };
struct EDat { u8 p[0x22]; u16 m22; };
struct Eff {
    u8 p[0x34];
    EMdl* m34;
    EDat* m38;
    EAtt* m3c;
    u8 p40[4];
    s16 m44;
    u16 m46;
    f32 m48, m4c, m50, m54;
};
extern char lbl_80365B64[];
f32 fn_8001E064(int);
u8* fn_800080B8(EMdl*);
u8* fn_800080E4(EMdl*);
u8 fn_800A6844(EDat*, int);
int fn_80009BC8(EMdl*, const char*);
Bone* fn_800078E4(EMdl*, int);
void fn_80312344(const void*, void*);
void fn_80312378(const void*, const void*, void*);
void fn_800BF798(Bone*, Bone*, u8*, u8*, u8*, int);
void fn_8001CD78(EMdl*);
void fn_80007860(EMdl*, int, Mt);
void fn_8000F328(Bone*, Mt);
void fn_8031292C(Mt, f32, f32, f32);
void fn_803128AC(Mt, f32, f32, f32);
void fn_80312654(Mt, int, f32);
#define MAT(base, b) ((base) + ((b)->ec >> 20) * 0x30)
static inline void Link(Eff* e, EMdl* src, u8* ms, u8* md, u8* mc, const char* n, Bone*& c) {
    Mt t1, t2;
int ib;
Bone* d;
Bone* bb;
Bone* ba;
int ia;
        ia = fn_80009BC8(src, n);
        ib = fn_80009BC8(e->m34, n);
        if (ia >= 0 && ib >= 0) {
            ba = fn_800078E4(src, ia);
            bb = fn_800078E4(e->m34, ib);
            fn_80312344(MAT(ms, ba), MAT(md, bb));
            fn_80312378(MAT(md, bb), bb->m10, MAT(mc, bb));
            c = bb->m8;
            if (c != NULL) {
                d = ba->m8;
                if (d != NULL) {
                    fn_80312344(MAT(ms, d), MAT(md, c));
                    fn_80312378(MAT(md, c), c->m10, MAT(mc, c));
                    if (c->m4 != NULL && d->m4 != NULL) fn_800BF798(d->m4, c->m4, ms, md, mc, 2);
                    if (c->m8 != NULL) {
                        if (d->m8 != NULL) {
                            fn_800BF798(d->m8, c->m8, ms, md, mc, 2);
                        } else {
                            fn_80312378(MAT(ms, d), c->m10, t2);
                            fn_80312378(t2, MAT(md, c->m8), MAT(md, c->m8));
                        }
                    }
                } else {
                    fn_80312378(MAT(ms, ba), bb->m10, t1);
                    fn_80312378(t1, MAT(md, bb->m8), MAT(md, bb->m8));
                }
            }
            fn_8001CD78(e->m34);
        }
}
void fn_800BFA4C(Eff* e) {
    Mt m128, mf8, mc8, m98, m68;
EMdl* src;
Bone* c;
u8* ms;
u8* md;
u8* mc;
const char* n;
    if (e->m34 == NULL) return;
    EAtt* a = e->m3c;
    if (a == NULL) return;
    if (e->m44 < 0) return;
    src = a->m30;
    e->m34->m84 = (int)(256.0f * fn_8001E064(a->m5c));
    if (e->m34->m64 != NULL) {
        ms = fn_800080B8(src);
        md = fn_800080B8(e->m34);
        mc = fn_800080E4(e->m34);
        n = NULL;
        switch (fn_800A6844(e->m38, -1)) {
        case 0xA:
            n = lbl_80365B64 + 0x26;
            break;
        case 0xB:
            n = lbl_80365B64 + 0x2C;
            break;
        }
        Link(e, src, ms, md, mc, n, c);
        fn_80312344(src->m10, e->m34->m10);
    } else {
        if (e->m46 & 2) return;
        Bone* b = fn_800078E4(src, e->m44);
        fn_80007860(src, e->m44, mf8);
        fn_8000F328(b, m128);
        fn_80312378(mf8, m128, e->m34->m10);
    }
    f32 sc = e->m54;
    f32 s = sc * (0.00390625f * e->m38->m22);
    if (1.0f != s) {
        fn_8031292C(mc8, s, s, s);
        fn_80312378(e->m34->m10, mc8, e->m34->m10);
    }
    fn_803128AC(m98, e->m48, e->m4c, e->m50);
    fn_80312378(e->m34->m10, m98, e->m34->m10);
    if (e->m46 & 0x20) {
        fn_80312654(m68, 0x79, 3.1415927f);
        fn_80312378(e->m34->m10, m68, e->m34->m10);
    }
}
}
