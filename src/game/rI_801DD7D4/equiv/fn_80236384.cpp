/* fn_80236384: class `sched` (round 19): same instructions per basic block as the original, a few of them
   (independent loads, constants or stores) in another order; checked with tools/equiv/dd.py. */
/* fn_80236384: THPPlayerOpen (DolphinSDK THPPlayer sample, with one extra flag argument):
   opens the movie, reads and checks the header and the component infos. */
#include "game/rI_801DD7D4/fn_thp.h"
extern "C" {
extern int lbl_804CBF50;          /* Initialized */
extern u8 lbl_80420620[];         /* WorkBuffer */
extern char lbl_80372750[];       /* "THP" */
int fn_802F6718(const char*, void*);                 /* DVDOpen */
int fn_802F6C90(void*, void*, int, int, int);        /* DVDReadPrio */
int fn_802F69C4(void*);                              /* DVDClose */
int fn_80291188(const char*, const char*);           /* strcmp */
#define P lbl_80420420
static inline BOOL isZero(int x) { if (x != 0) return FALSE; return TRUE; }
BOOL fn_80236384(const char* fileName, BOOL onMemory, int extra) {
    s32 offset;
    u32 i;
    if (!lbl_804CBF50) return FALSE;
    {
    THPPlayer* p = &lbl_80420420;
    if (p->a0) return FALSE;
    memset(&p->a80, 0, 0xc);
    memset(p->p8c, 0, 0x10);
    if (fn_802F6718(fileName, p) == 0) return FALSE;
    if (fn_802F6C90(p, lbl_80420620, 0x40, 0, 2) < 0) {
        fn_802F69C4(p);
        return FALSE;
    }
    memcpy((u8*)p + 0x3c, lbl_80420620, 0x30);
    if (fn_80291188((char*)p + 0x3c, lbl_80372750) != 0) {
        fn_802F69C4(p);
        return FALSE;
    }
    if (*(u32*)((u8*)p + 0x40) != 0x11000) {
        fn_802F69C4(p);
        return FALSE;
    }
    offset = p->a5c;
    if (fn_802F6C90(p, lbl_80420620, 0x20, offset, 2) < 0) {
        fn_802F69C4(p);
        return FALSE;
    }
    memcpy(&p->a6c, lbl_80420620, 0x14);
    p->a7 = 0;
    offset += 0x14;
    for (i = 0; i < p->a6c; i++) {
        switch (p->a70[i]) {
        case 0:
            if (fn_802F6C90(p, lbl_80420620, 0x20, offset, 2) < 0) {
                fn_802F69C4(p);
                return FALSE;
            }
            memcpy(&p->a80, lbl_80420620, 0xc);
            offset += 0xc;
            break;
        case 1:
            if (fn_802F6C90(p, lbl_80420620, 0x20, offset, 2) < 0) {
                fn_802F69C4(p);
                return FALSE;
            }
            memcpy(p->p8c, lbl_80420620, 0x10);
            p->a7 = 1;
            offset += 0x10;
            break;
        default:
            return FALSE;
        }
    }
    p->a4 = p->a5 = 0;
    p->a6 = 0;
    p->b0 = onMemory;
    p->a0 = 1;
    p->dc = 127.0f;
    p->e0 = p->dc;
    p->e8 = 0;
    {
        int v;
        switch (extra) {
        default: v = 0; break;
        case 0: v = 1; break;
        }
        lbl_80420420.f8 = v;
    }
    return TRUE;
    }
}
}
