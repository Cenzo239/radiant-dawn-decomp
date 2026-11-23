/* EXACT (round m9, m9-s): fn_801B0E88. Picture list: move the help cursor. Computes the cursor target (x, y)
 * for the current area (+0x28: 0 tabs, 1 and 2 the two thumbnail columns), starts a 4-frame move from the old
 * position, stores the scroll value v and, when the help display is on (fn_801A2224), shows the help text for
 * the area/tab at (x, y) via fn_801A1DCC. From equiv/fn_801B0E88.cpp; the fix is `x = d->x1C; x += 0x10;` in
 * case 0 only (in-place add keeps x in r31 and d in r5). Port caveat: as in the original, x and y (and s in
 * the help switch) are left unset when the area or tab index is out of range. */
#include "game/rF_8017F400/types.h"
#pragma auto_inline off
extern "C" {
/* picture list input: moves between tabs, thumbnails and columns */
typedef struct LData {
    void* res;
    void* x4;
    u8 pad8[0xC];
    void* x14;
    void* x18;
    int x1C;
    int x20;
    int x24;
    int x28;
    int x2C;
    int x30;
    int x34;
    int x38;
    int x3C;
    int x40;
    int x44;
    int x48;
    int x4C;
    int x50;
    int x54;
    int x58;
    int x5C;
    int x60;
} LData;
class Pad { public:
    virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34();
    virtual void v38();
    virtual u32 trig();
    virtual void v40(); virtual void v44();
    virtual u32 held();
};
extern LData* lbl_804CB9BC;
extern void* lbl_804CB9B8;
extern Pad* lbl_804CB5B8;
extern u8 lbl_8041EB20[];
extern char lbl_8036DCE0[];
extern int fn_801B45AC(void*);
extern f32 fn_8017F68C(f32, f32, f32, f32, int);
extern void fn_80179888(void*, int);
extern int fn_801B45CC(void);
extern int fn_801A2224(void*);
extern void* fn_801B092C(void);
extern void fn_801A1AC4(void*, void*, void*, f32, f32);
extern void fn_801B45F0(void*);
extern void fn_801A1CFC(void*);
extern void fn_80083DC4(void*, int);
extern void fn_80253EE4(const char*, f32);
extern void fn_801B0E88(int);
extern void fn_801B0418(void);
extern void fn_801B0DD8(void);
extern void fn_801B0E28(void);
extern void fn_801B45B4(void**, void*);
extern void fn_801B46B4(void**, int);
extern void fn_801B4638(void**, int);
extern void** fn_801B45C0(void**, void**);
extern int fn_801B09D0(void**, int);
extern s8 fn_801B0B58(void**, int);
extern int fn_8028DB44(int);
extern f32 fn_801B4600(int);
void fn_801B10B0(void);

}

/* ---- from build/tmp/r22b/fr_e88.cpp ---- */
extern "C" {
extern "C" {
const char* fn_800D0864(const char* s);
void fn_801A1DCC(void* p, const char* s, f32 x, f32 y);
void fn_801B0E88(int v) {
    int x;
    int y;
    const char* s;
    LData* d = lbl_804CB9BC;
    switch (d->x28) {
    case 0:
        x = d->x1C;
        x += 0x10;
        y = d->x20 + 0xA + d->x24 * 0x1C;
        break;
    case 1:
        x = d->x1C + 0x78;
        y = d->x20 + 0x22 + (d->x2C - d->x38 / 32) * 32;
        break;
    case 2:
        x = d->x1C + 0xF5;
        y = d->x20 + 0x22 + (d->x2C - d->x38 / 32) * 32;
        break;
    }
    lbl_804CB9BC->x54 = lbl_804CB9BC->x4C;
    lbl_804CB9BC->x58 = lbl_804CB9BC->x50;
    lbl_804CB9BC->x5C = x;
    lbl_804CB9BC->x60 = y;
    lbl_804CB9BC->x48 = 4;
    lbl_804CB9BC->x44 = lbl_804CB9BC->x38;
    lbl_804CB9BC->x34 = v;
    lbl_804CB9BC->x30 = v;
    if (fn_801A2224(lbl_8041EB20) != 0) {
        switch (lbl_804CB9BC->x28) {
        case 0:
            switch (lbl_804CB9BC->x24) {
            case 0:
                s = lbl_8036DCE0 + 0x2E;
                break;
            case 1:
                s = lbl_8036DCE0 + 0x41;
                break;
            case 2:
                s = lbl_8036DCE0 + 0x55;
                break;
            }
            break;
        case 1:
            s = lbl_8036DCE0 + 0x68;
            break;
        case 2:
            s = lbl_8036DCE0 + 0x73;
            break;
        }
        fn_801A1DCC(lbl_8041EB20, fn_800D0864(s), x, y);
    }
}

}
}
