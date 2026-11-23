#include "game/rG_800A3D88/chr.h"
extern "C" {
struct Eg { u8 p[0x34]; Mdl* m34; struct { u8 p[0x21]; u8 m21; }* m38; u8 p3c[4]; struct Eh* m40; u8 p44[2]; u16 m46; u8 p48[0xC]; f32 m54; u8 p58[0x44]; f32 m9c, ma0; u16 ma4, ma6; };
struct Eh { u8 p[0x50]; u8 m50; u8 p51[5]; s16 m56; };
f32 fn_8001EF30(f32, f32, f32, f32);
void fn_80008F20(Mdl*, u8);
void fn_800081D4(Mdl*);
void fn_80007C58(Mdl*);
void fn_8001B254(Mdl*);
void fn_800180F0(Mdl*);
void fn_8001AFE0(Mdl*);
void fn_800BFA4C(Eg*);
void fn_800BFE24(Eg*);
void fn_800C0D4C(Eg*);
void fn_800BEF58(Eg* e) {
    if (e->m34 == NULL) return;
    if (e->m46 & 1) return;
    if (e->m34 != NULL && e->ma4 != 0) {
        e->ma6++;
        if (e->m38->m21 & 8) {
            fn_80008F20(e->m34, (int)fn_8001EF30(e->m9c, e->ma0, e->ma4, e->ma6));
        } else {
            e->m54 = fn_8001EF30(e->m9c, e->ma0, e->ma4, e->ma6);
        }
        if (e->ma6 >= e->ma4) e->ma4 = 0;
    }
    if (e->m34 != NULL && (e->m46 & 0x10)) {
        fn_800081D4(e->m34);
        fn_80007C58(e->m34);
        fn_8001B254(e->m34);
        fn_800180F0(e->m34);
        fn_8001AFE0(e->m34);
    }
    fn_800BFA4C(e);
    fn_800BFE24(e);
    fn_800C0D4C(e);
}
struct C4 { u8 r, g, b, a; };
struct Pk { u8 p[0x30]; Chr* m30; C4 m34; C4 m38; int m3c; int m40; };
Pk* fn_80081050(void*, Chr*);
f32 fn_800A84A4(const char*);
extern u8 lbl_80382508[];
extern char lbl_803657E8[];
extern C4 lbl_804CD45C;
static inline C4 MCol(Chr* c) { C4 a; if (c->mdl == NULL) { *(u32*)&a = 0; } else { a = *(C4*)((u8*)c->mdl + 8); } return a; }
void fn_800BCF10(Chr* c) {
    int n = fn_800A84A4(lbl_803657E8 + 0x318);
    if (n != 0) {
        C4 col = lbl_804CD45C;
        C4 t;
        C4 a;
        Pk* p = fn_80081050(lbl_80382508, c);
        p->m30 = c;
        p->m3c = 1;
        if (c->mdl == NULL) { *(u32*)&t = 0; } else { t = *(C4*)((u8*)c->mdl + 8); }
        *(u32*)&a = *(u32*)&t;
        p->m34 = a;
        p->m38 = col;
        p->m40 = n;
    }
}
}
