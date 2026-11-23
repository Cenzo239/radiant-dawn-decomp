#include "game/rG_800A3D88/types.h"

// Opens the battle data file and relocates the tables that hold offsets.
extern "C" {
struct UnitT { u8 p[0x14D]; u8 n; u8 p14e[2]; u8* tex; };
struct GroupT { u8 p[0xB]; u8 n; u8* idx; u8* rate; };
struct ListT { u8 p[8]; u8* m[16]; };
extern u8* lbl_804CB650;
extern u8* lbl_804CB654;
extern u8* lbl_804CB658;
extern u8* lbl_804CB65C;
extern u8* lbl_804CB660;
extern u8* lbl_804CB664;
extern u8* lbl_804CB668;
extern u8* lbl_804CB66C;
extern u8* lbl_804CB670;
extern u8* lbl_804CB674;
extern u8* lbl_804CB678;
extern u8* lbl_804CB67C;
extern u8* lbl_804CB680;
extern u8* lbl_804CB684;
extern u8* lbl_804CB688;
extern u8* lbl_804CB68C;
extern u8* lbl_804CB690;
extern u8* lbl_804CB694;
extern u8* lbl_804CB698;
extern u8* lbl_804CB69C;
void fn_80075FB4(const char*, int);
u8* fn_80077064(const char*);
u32 fn_80109A2C(u8**);
extern char lbl_803651B0[];
#define S(a) (lbl_803651B0 + ((a) - 0x803651B0))
static inline u16 Cnt(u8* t) {
    u8* r = t;
    u16 n = fn_80109A2C(&r);
    fn_80109A2C(&r);
    return n;
}
static inline u8* Dat(u8* t) {
    u8* r = t;
    fn_80109A2C(&r);
    fn_80109A2C(&r);
    return r;
}
#pragma use_lmw_stmw on
void fn_800A8660() {
    fn_80075FB4(S(0x803651F5), 0x80);
    lbl_804CB650 = fn_80077064(S(0x80365204));
    lbl_804CB654 = fn_80077064(S(0x8036520E));
    lbl_804CB658 = fn_80077064(S(0x8036521C));
    lbl_804CB65C = fn_80077064(S(0x8036522C));
    lbl_804CB660 = fn_80077064(S(0x80365239));
    lbl_804CB664 = fn_80077064(S(0x80365246));
    lbl_804CB668 = fn_80077064(S(0x80365254));
    lbl_804CB66C = fn_80077064(S(0x80365261));
    lbl_804CB670 = fn_80077064(S(0x8036526A));
    lbl_804CB674 = fn_80077064(S(0x80365275));
    lbl_804CB678 = fn_80077064(S(0x80365281));
    lbl_804CB67C = fn_80077064(S(0x80365291));
    lbl_804CB680 = fn_80077064(S(0x8036529D));
    lbl_804CB684 = fn_80077064(S(0x803652AA));
    lbl_804CB688 = fn_80077064(S(0x803652B8));
    lbl_804CB68C = fn_80077064(S(0x803652C7));
    lbl_804CB690 = fn_80077064(S(0x803652D4));
    lbl_804CB694 = fn_80077064(S(0x803652E1));
    lbl_804CB698 = fn_80077064(S(0x803652EC));
    lbl_804CB69C = fn_80077064(S(0x803652F7));
    u8* tex = Dat(fn_80077064(S(0x80365302)));
    int n = Cnt(lbl_804CB650);
    UnitT* u = (UnitT*)Dat(lbl_804CB650);
    for (int i = 0; i < n; i++, u++) {
        u->tex = tex;
        tex += u->n * 8;
    }
    u8* idx = fn_80077064(S(0x8036530B));
    u8* rate = fn_80077064(S(0x8036531D));
    n = Cnt(lbl_804CB684);
    GroupT* g = (GroupT*)Dat(lbl_804CB684);
    for (int i = 0; i < n; i++, g++) {
        g->idx = idx;
        g->rate = rate;
        idx += g->n;
        rate += g->n;
    }
    int cnt = Cnt(lbl_804CB67C);
    u8* q = fn_80077064(S(0x8036532E));
    n = Cnt(lbl_804CB68C);
    ListT* l = (ListT*)Dat(lbl_804CB68C);
    for (int i = 0; i < n; i++, l++) {
        for (int j = 0; j < 16; j++) {
            l->m[j] = q;
            q += cnt;
        }
    }
}
}
