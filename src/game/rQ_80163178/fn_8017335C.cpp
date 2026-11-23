#include "game/rQ_80163178/common.h"
extern "C" {
extern ListHdr lbl_803E7320[];
void* memset(void*, int, u32);
void fn_80163010(AiCfg*, Unit*);
void fn_80045120(AiAct*, Unit*);
void fn_80045548(AiAct*);
void fn_80166720(Unit*);
void fn_8010E41C(u8*, int);
void* fn_800CFD18(ListHdr*, int);
Unit* fn_800CFB0C(void* e);
s16 fn_801237EC(Unit*);
int fn_8016335C(Unit*);
int fn_80163178(Unit*);
int fn_801635B8(Unit*, u16);
int fn_80163808(Unit*, u16);
}
#pragma use_lmw_stmw off
extern "C" u8 fn_8017335C(void) {
    int k;
    AiAct* act;
    int m;
    Unit* best;
    int kind;
    int id;
    Unit* v;
    s16 h;
    u8 tbl[0xB];
    k = 0x10000;
    act = &lbl_803CA870;
    m = 0x80000000;
    best = 0;
    fn_8010E41C(tbl, 0);
    for (id = 1; id <= 0xFE; id++) {
        v = UnitGet(id);
        if (v->person && tbl[v->team[8]] && !(v->flags10C & 0x9D)) {
            v->m3D0[0] = 0x40;
            v->b3BC = 0;
            fn_80163010(&lbl_804183F0, v);
            lbl_804183F0.done = 0;
            memset(lbl_804183F0.res, 0, 0x14);
            fn_80045120(act, v);
            fn_80166720(v);
            if (fn_8016335C(v) && fn_80163178(v)) {
                if (fn_801635B8(v, k - 1)) {
                    h = v->h3BE;
 int s = 100.0f * h / fn_801237EC(v);
                    if (s > m) {
                        m = s;
                        best = v;
                        kind = 0;
                    }
                }
                if (fn_80163808(v, k - 1)) {
                    h = v->h3BE;
 int s = 100.0f * h / fn_801237EC(v);
                    if (s > m) {
                        m = s;
                        best = v;
                        kind = 1;
                    }
                }
            }
            lbl_804183F0.done = 0;
            fn_80045548(act);
        }
    }
    if (best) {
        best->m3D0[0] = 0x40;
        best->b3BC = 0;
        fn_80163010(&lbl_804183F0, best);
        lbl_804183F0.done = 0;
        memset(lbl_804183F0.res, 0, 0x14);
        fn_80045120(act, best);
        fn_80166720(best);
        if (kind == 0) {
            int k2 = 0x10000;
            fn_801635B8(best, k2 - 1);
        } else {
            int k2 = 0x10000;
            fn_80163808(best, k2 - 1);
        }
    }
    return lbl_804183F0.done;
}
extern "C" Unit* fn_80173D10(ListHdr* l) {
    int k;
    AiAct* act;
    int m;
    Unit* best;
    int i;
    Unit* v;
    s16 h;
    k = 0x10000;
    act = &lbl_803CA870;
    m = 0x80000000;
    best = 0;
    for (i = 0; i < l->n; i++) {
        v = fn_800CFB0C(fn_800CFD18(l, i));
        v->m3D0[0] = 0x40;
        v->b3BC = 0;
        fn_80163010(&lbl_804183F0, v);
        lbl_804183F0.done = 0;
        memset(lbl_804183F0.res, 0, 0x14);
        fn_80045120(act, v);
        fn_80166720(v);
        if (fn_8016335C(v) && fn_80163178(v)) {
            if (fn_801635B8(v, k - 1)) {
                h = v->h3BE;
 int s = 100.0f * h / fn_801237EC(v);
                if (s > m) {
                    m = s;
                    best = v;
                }
            }
            if (fn_80163808(v, k - 1)) {
                h = v->h3BE;
 int s = 100.0f * h / fn_801237EC(v);
                if (s > m) {
                    m = s;
                    best = v;
                }
            }
        }
        lbl_804183F0.done = 0;
        fn_80045548(act);
    }
    return best;
}
