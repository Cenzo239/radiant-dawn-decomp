#include "game/rG_800A3D88/types.h"

// Font reload: reopens the fonts and the two ruby resources.
extern "C" {
extern void* lbl_803E7260[6];
void fn_800068A0(void*, const char*);
void fn_80006A2C(void*);
struct Res {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual char* v6();
    void* p;
};
extern u8 lbl_804CB6E0[8];
extern u8 lbl_804CB6E8[8];
extern Res* lbl_804CB6F0;
extern char* lbl_80382A20[6][2];
int fn_801D09F0();
void* fn_80079150(int);
void* fn_80077348(void*);
void fn_80077478(void*, const char*, int, int);
void fn_80077400(void*);
#define RA ((Res*)lbl_804CB6E0)
#define RB ((Res*)lbl_804CB6E8)
#define LOAD(o, R) { o = R; if (o->p == NULL) { fn_800068A0(&o->p, R->v6()); } }
#define UNLOAD(R) { Res* u = R; if (u->p != NULL) { fn_80006A2C(&u->p); } }
void fn_800CA0A4() {
Res* o;
Res* o2;
void** h;
char** s;
int i;
    h = lbl_803E7260;
    s = lbl_80382A20[0];
    for (i = 0; i < 6; i++, s += 2) {
        fn_80077400(*h);
        fn_80077478(*h, s[fn_801D09F0()], 0x80, 0);
        h++;
    }
    UNLOAD(RA);
    LOAD(o, RA);
    UNLOAD(RB);
    LOAD(o2, RB);
}
}
