#include "game/rQ_80163178/common.h"
extern "C" {
extern ListHdr lbl_803E7320[];
extern u8 lbl_803877B0[];
extern u8 lbl_803CAB38[];
extern struct Sb* lbl_804CB814;
void fn_800392FC(void*, int, int);
void fn_800CFB34(ListHdr*);
void fn_80167704(void*);
int fn_80168098(void);
int fn_801681C4(Unit*, Unit*);
void fn_801681E0(Unit**, Unit**, int (*)(Unit*, Unit*));
int fn_8028DB44(int);
u8 fn_801107C0(u8*, Unit*);
s8 fn_8012408C(Unit*);
}
struct Sb { u8 d[0xC]; };
extern "C" void fn_8016CF78(FF* f, s8 x, s8 y) {
    int i = x + y * 0x40;
    Map* m = &lbl_803EC898;
    u8 t;
    if (m->b5S[i]) {
        return;
    }
    if ((f->u->w3B4 & 0x20000) && (m->ter[3][i] & 2)) {
        return;
    }
    f->x = x;
    f->y = y;
    t = m->ter[0][i];
    if (t == 0 || t == f->u->tid) {
        fn_800392FC(f, x, y);
    }
}
extern "C" void fn_8017293C(FF* f, s8 x, s8 y) {
    int i = x + y * 0x40;
    Map* m = &lbl_803EC898;
    u8 t;
    if (m->b5S[i]) {
        return;
    }
    if ((f->u->w3B4 & 0x20000) && (m->ter[3][i] & 2)) {
        return;
    }
    f->x = x;
    f->y = y;
    t = m->ter[0][i];
    if (t == 0 || t == f->u->tid) {
        fn_800392FC(f, x, y);
    }
}
extern "C" void fn_80172494(Unit* u, int x, int y) {
    struct G { void* vt; Unit* u; };
    G f;
    G* pf = &f;
    f.vt = lbl_803877B0;
    fn_800CFB34(lbl_803E7320);
    pf->u = u;
    if (y < 0) {
        y = u->y;
    }
    fn_800392FC(pf, (s8)(x < 0 ? x = u->x : x), (s8)y);
}
/*V*/
/*VE*/
