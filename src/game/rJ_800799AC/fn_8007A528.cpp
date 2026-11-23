/* Controller system setup. */
#include "game/rJ_800799AC/pad.h"

struct PadData {
    Pad* pads[4];        /* 0x00 */
    u8 status[4][0xC];   /* 0x10 */
    u8 data[4][0x840];   /* 0x40 */
};

extern "C" {

extern PadData lbl_803D7918;
extern void* lbl_80380E14[];
extern void* lbl_80380D28[];
extern int lbl_804CB5BC;
extern Pad* lbl_804CB5B8;
void* fn_80079940(int size, int align);
void* fn_8007A4FC(int size);
int fn_8007A504(void* p);
void fn_80323064(void);
void* memset(void* p, int v, u32 n);
void SISetSamplingRate(int r);
void fn_8032FAD0(void);
void fn_80335A94(void* a, void* b);
void fn_8030D310(void);
void fn_8030D66C(int i);
void fn_8030AAF4(int i);
int fn_80337348(void);

#pragma use_lmw_stmw on
void fn_8007A734(void) {
    Pad* p;
    Pad** pp = lbl_803D7918.pads;
    int i;
    for (i = 0; i < 4; i++) {
        if (*pp != 0) {
            if (*pp != 0) {
                (*pp)->v08(1);
            }
        }
        p = (Pad*)fn_80079940(0x5C, 0x40);
        if (p != 0) {
            *(void***)p = lbl_80380E14;
            p->f4 = 4;
            p->f8 = 4;
            p->v0C(i);
            *(void***)p = lbl_80380D28;
            p->vD0(4);
            p->vD4(p->v14());
            fn_8030D66C(i);
            fn_8030AAF4(i);
        }
        *pp = p;
        pp++;
    }
}
#pragma use_lmw_stmw off

}
