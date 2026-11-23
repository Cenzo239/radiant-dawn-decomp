/* Result report: creation, one row per chapter */
#include "game/rN_8025EEF0/calls.h"

struct C4 { u8 r, g, b, a; };

extern "C" {

struct RepRow { u8 id; u8 pad; s16 m2; int m4; };
struct Rep { void* tex; void* win; s16 m8; u8 padA[2]; RepRow rows[1]; };
extern Rep* lbl_804CC0D4;
extern u8* lbl_804CC0D0;
extern char lbl_80373CF0[];
extern char lbl_804CA798[8];
extern u8 lbl_803CAB38[];
void* memset(void* p, int v, unsigned n);
int fn_8006041C(void* l);
void fn_8006054C(void* l, int i, void* a, void* b, void* c, void* d, void* e);
void* fn_80179660(void* p);
void fn_80179854(void* w, f32 v);
void fn_80179A58(void* w, C4* c);
void fn_801798A8(void* w, int a);
C4* fn_800CD204(int i);
void fn_801C6EAC(const char* a, const char* b, char* out);

void fn_8028871C(void* parent) {
    char name[0x60];
    int a24, a20, a1C, a18;
    C4 col;
    s16 a10, aE, aC, aA;
    u8 k9, k8;
    {
        lbl_804CC0D0 = (u8*)parent;
    }
    *(void**)(lbl_804CC0D0 + 0x30) = fn_80078CCC(0x29C, lbl_80373CF0 + 0x9F, 0);
    memset(*(void**)(lbl_804CC0D0 + 0x30), 0, 0x29C);
    lbl_804CC0D4 = *(Rep**)(lbl_804CC0D0 + 0x30);
    lbl_804CC0D4->m8 = 0;
    {
        int i;
        void* l = lbl_803CAB38 + 0x554;
        for (i = fn_8006041C(l) - 1; i >= 0; i--) {
            RepRow* r = &lbl_804CC0D4->rows[lbl_804CC0D4->m8];
            if (i == fn_8006041C(l) - 1) {
                fn_8006054C(l, i, &r->id, &a10, &a24, &r->m2, &r->m4);
                lbl_804CC0D4->m8++;
            } else {
                fn_8006054C(l, i, &k9, &a10, &a24, &aC, &a1C);
                fn_8006054C(l, i + 1, &k8, &aE, &a20, &aA, &a18);
                if (k9 != k8) {
                    fn_8006054C(l, i, &r->id, &a10, &a24, &r->m2, &r->m4);
                    lbl_804CC0D4->m8++;
                }
            }
        }
    }
    {
        void* w = fn_80078CCC(0x2C, lbl_804CA798, 0);
        if (w != 0) {
            w = fn_80179660(w);
        }
        lbl_804CC0D4->win = w;
    }
    {
        void* w = lbl_804CC0D4->win;
        fn_80179854(w, 95.0f);
        col = *fn_800CD204(4);
        fn_80179A58(w, &col);
        fn_801798A8(w, 1);
    }
    fn_801C6EAC(lbl_80373CF0 + 0x16, lbl_80373CF0 + 0x37, name);
    fn_8023F1A0(name, 0);
}

}
