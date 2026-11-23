/* AI: use a staff on the best reachable target (names guessed). */
#include "game/rQ_80163178/common.h"
extern "C" {
extern ListHdr lbl_803E7320[];
#if TARGET_PC
FE10_PROTO extern void *lbl_804CA514;
#else
extern u32 lbl_804CA514;
#endif
u8* fn_80158C98(void);
#if TARGET_PC
FE10_PROTO int fn_8011B77C(void*, p32arg);
#else
int fn_8011B77C(void*, u32);
#endif
int fn_801719A4(Unit*, int, s16*, s16*);
#if TARGET_PC
FE10_PROTO p32ret fn_80079150(int);
#else
u32 fn_80079150(int);
#endif
#if TARGET_PC
FE10_PROTO void fn_80079210(p32arg);
#else
void fn_80079210(u32);
#endif
#if TARGET_PC
FE10_PROTO void fn_8013BE90(p32arg, int);
#else
void fn_8013BE90(int, int);
#endif
void fn_8013BED8(void);
u8* fn_80116294(Map*, u32, int, int, int);
int fn_8016510C(Unit*, u8*, s16*, s16*);
int fn_8016D11C(Unit*);
void fn_8016F94C(Unit*, int, int, int, u16, int, int, int);
int fn_80170C48(int, int, int, int);
void fn_80160610(u8, int, int, Unit*, int, int, int, int, int);
s8* fn_800CFD18(ListHdr*, int);

struct TmpBuf {
    u32 p;
    TmpBuf(int n) { p = fn_80079150(n); }
    ~TmpBuf() { fn_80079210(p); }
};
u8 fn_80165240(Unit* u, s8 a) {
    s16 x, y;
    /*P*/
    u8* r;
    u8* k;
    s8* c;
/*E*/
    if (!(u->w3B4 & 0x20000000)) {
        return 0;
    }
    k = fn_80158C98();
    if (fn_8011B77C((u8*)u + 0x12C, lbl_804CA514) && !(*(u32*)(k + 0x14) & 0x400)) {
        if (!fn_801719A4(u, 0x100, &x, &y)) {
            return 0;
        }
        TmpBuf buf(lbl_803EC898.w * lbl_803EC898.h);
        fn_8013BE90(0, 9);
        r = fn_80116294(&lbl_803EC898, buf.p, (s8)x, (s8)y, lbl_803EC898.w * lbl_803EC898.h);
        fn_8013BED8();
        if (fn_8016510C(u, r, &x, &y)) {
            fn_8016F94C(u, x, y, 1, fn_8016D11C(u), 0, 0, -1);
            if (lbl_804183F0.done && fn_80170C48(x, y, lbl_803CA870.x, lbl_803CA870.y)) {
                fn_80160610(0xB, (s8)*(u8*)&lbl_803CA870.x, lbl_803CA870.y, lbl_803CA870.unit2, (s8)x, (s8)y, a, 0, 0);
                lbl_804183F0.res[1] = 0xE;
            }
            return lbl_804183F0.done;
        }
    } else if (!fn_801719A4(u, 0, &x, &y)) {
        return 0;
    }
    c = 0;
    while (lbl_803E7320->n > 0) {
        c = fn_800CFD18(lbl_803E7320, 0);
        break;
    }
    if (!c) {
        return 0;
    }
    fn_8016F94C(u, x, y, 1, fn_8016D11C(u), 0, 0, -1);
    if (lbl_804183F0.done && x == lbl_803CA870.x && y == lbl_803CA870.y) {
        fn_80160610(0xC, lbl_803CA870.x, lbl_803CA870.y, lbl_803CA870.unit2, c[0], (s8)((u8*)c)[1], a, 0, 0);
        lbl_804183F0.res[1] = 0xF;
    }
    return lbl_804183F0.done;
}
}
