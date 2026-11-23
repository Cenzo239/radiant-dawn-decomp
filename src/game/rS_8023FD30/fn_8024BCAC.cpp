#include "game/rS_8023FD30/types.h"
/* Top of the save stream: system block, then one tagged section per game subsystem. */
struct SaveSysB {
    u64 magic;
    u32 date;
    u32 ver;
    u64 v10;
    u32 v18;
    u32 v1C;
    s64 time;
    u64 v28;
    u8 v30;
    u8 v31;
    u8 v32;
    u8 v33;
    u8 v34;
    u8 v35;
    u8 v36;
    u8 v37;
    s16 v38;
    u8 pad3A[0x55 - 0x3A];
    u8 v55;
};
struct GameState {
    u8 pad00[0x10];
    u8 v10;
    u8 pad11;
    s16 v12;
    u8 pad14[0x9C - 0x14];
    u8 v9C;
    u8 pad9D[2];
    u8 v9F;
    u64 vA0;
};
struct Blob {
    u8* data;
    u32 size;
    u32 cap;
};
struct LongStr {
    u32 word0;
    u32 size;
    void* data;
};
struct NameLists {
    Blob v[8];
    LongStr s60;
};
struct Reader {
    void* data;
    void* cur;
    u32 size;
    u8 own;
    u8 pad0D[3];
    void* vt;
};
extern "C" {
extern SaveSysB lbl_80429400;
extern GameState lbl_803CAB38;
extern u8 lbl_803E9000[];
extern u8 lbl_803E9288[];
extern u8 lbl_803CB770[];
extern u8 lbl_803CA870[];
extern char lbl_80372B4C[];
extern char lbl_80380940[];
extern u8* lbl_804CBFD0;
s64 OSGetTime(void);
void fn_8008A48C(void*, void*);
void fn_80078E24(void*);
int fn_8024BED8(void*);
void fn_80245E44(void*, void*);
void fn_8008A820(void*, const char*);
void fn_8008A780(void*, u32, void*);
void fn_80242920(void*);
void fn_80062AE8(void*, void*);
void fn_8013498C(void*);
void fn_8012D38C(void*);
void fn_801058B4(void*);
void fn_80105768(void*, void*);
void fn_80066AC0(void*, void*);
void fn_80119C48(void*);
void fn_801131D8(void*);
#if TARGET_PC
FE10_PROTO void fn_8017DA3C(ptr32<const void>);
FE10_PROTO void fn_8004A424(void*, ptr32<const void>);
#else
void fn_8017DA3C(void*);
void fn_8004A424(void*, void*);
#endif

extern NameLists* lbl_804CBFC8;
extern u32 lbl_804CB80C;
extern u32 lbl_804CB800;
void* fn_80079150(u32);
void fn_80079210(void*);
void fn_80245F9C(void*, void*);
void fn_8008A518(void*, const char*);
void fn_8008A43C(void*, u32, void*);
#if TARGET_PC
FE10_PROTO void fn_80242BB0(ptr32<const void>, ptr32<const void>);
#else
void fn_80242BB0(void*, void*);
#endif
void fn_80062DE0(void*, void*);
void fn_80134B80(void*);
void fn_8012D3EC(void*);
void fn_80105928(void*);
void fn_801057DC(void*, void*);
void fn_80066B84(void*, void*);
void fn_80119CD8(void*);
void fn_80113274(void*);
#if TARGET_PC
FE10_PROTO void fn_8017DA48(ptr32<const void>);
#else
void fn_8017DA48(void*);
#endif
int fn_8024BCAC(void) {
    Reader r;
    fn_8008A48C(&r, lbl_804CBFD0);
    int v = fn_8024BED8(&r);
    r.vt = lbl_80380940;
    if (r.own) {
        fn_80078E24(r.data);
        r.data = 0;
        r.own = 0;
    }
    return v;
}
static inline void blobFree(Blob* b) {
    if (b) {
        if (b) {
            if (b) {
                if (b) {
                    if (b->data) {
                        b->size -= (b->data + b->size) - b->data;
                        fn_80079210(b->data);
                    }
                }
            }
        }
    }
}
int fn_8024BED8(void* st) {
    const char* s;
    NameLists* t;
    SaveSysB* sys;
    sys = &lbl_80429400;
    fn_80245F9C(sys, st);
    t = (NameLists*)fn_80079150(0x6C);
    if (t) {
        u32* w = (u32*)t;
        w[0] = 0; w[1] = 0; w[2] = 0; w[3] = 0; w[4] = 0; w[5] = 0; w[6] = 0; w[7] = 0; w[8] = 0;
        w[9] = 0; w[10] = 0; w[11] = 0; w[12] = 0; w[13] = 0; w[14] = 0; w[15] = 0; w[16] = 0; w[17] = 0;
        w[18] = 0; w[19] = 0; w[20] = 0; w[21] = 0; w[22] = 0; w[23] = 0; w[24] = 0; w[25] = 0; w[26] = 0;
    }
    lbl_804CBFC8 = t;
    s = lbl_80372B4C;
    fn_8008A518(st, s + 0xBF);
    fn_80242BB0(t, st);
    fn_8008A518(st, s + 0xC4);
    fn_80062DE0(&lbl_803CAB38, st);
    fn_8008A518(st, s + 0xC9);
    fn_80134B80(st);
    fn_8008A518(st, s + 0xCE);
    fn_8012D3EC(st);
    fn_8008A518(st, s + 0xD3);
    fn_80105928(st);
    fn_801057DC(lbl_803E9000, st);
    fn_8008A518(st, s + 0xD8);
    fn_8008A43C(st, 0xC, lbl_803E9288);
    fn_8008A518(st, s + 0xDD);
    fn_80066B84(lbl_803CB770, st);
    if (sys->ver >= 9) {
        fn_8008A518(st, s + 0xE2);
        fn_80119CD8(st);
        fn_8008A518(st, s + 0xE7);
        fn_80113274(st);
    } else {
        lbl_804CB80C = 0;
        lbl_804CB800 = 0;
    }
    fn_8008A518(st, lbl_80372B4C + 0xEC);
    fn_8017DA48(st);
    NameLists* d = lbl_804CBFC8;
    if (d) {
        if (&d->s60) {
            if (d->s60.word0 >> 31) {
                fn_80079210(d->s60.data);
            }
        }
        blobFree(&d->v[7]);
        blobFree(&d->v[6]);
        blobFree(&d->v[5]);
        blobFree(&d->v[4]);
        blobFree(&d->v[3]);
        blobFree(&d->v[2]);
        blobFree(&d->v[1]);
        blobFree(&d->v[0]);
        fn_80079210(d);
    }
    lbl_804CBFC8 = 0;
    return 1;
}
int fn_8024BD18(void* st) {
    SaveSysB* sys = &lbl_80429400;
    sys->ver = 0x11;
    sys->time = OSGetTime();
    GameState* g = &lbl_803CAB38;
    sys->v28 = g->vA0;
    sys->v34 = g->v9F;
    sys->v35 = sys->v55;
    sys->v36 = g->v10;
    sys->v38 = g->v12;
    switch (sys->v31) {
    case 0:
        sys->v37 = g->v9C;
        break;
    case 1:
        sys->v37 = 8;
        break;
    }
    fn_80245E44(sys, st);
    const char* s = lbl_80372B4C;
    fn_8008A820(st, s + 0xBF);
    fn_80242920(st);
    fn_8008A820(st, s + 0xC4);
    fn_80062AE8(&lbl_803CAB38, st);
    fn_8008A820(st, s + 0xC9);
    fn_8013498C(st);
    fn_8008A820(st, s + 0xCE);
    fn_8012D38C(st);
    fn_8008A820(st, s + 0xD3);
    fn_801058B4(st);
    fn_80105768(lbl_803E9000, st);
    fn_8008A820(st, s + 0xD8);
    fn_8008A780(st, 0xC, lbl_803E9288);
    fn_8008A820(st, s + 0xDD);
    fn_80066AC0(lbl_803CB770, st);
    fn_8008A820(st, s + 0xE2);
    fn_80119C48(st);
    fn_8008A820(st, s + 0xE7);
    fn_801131D8(st);
    fn_8008A820(st, s + 0xEC);
    fn_8017DA3C(st);
    return 1;
}
int fn_8024C2B4(void* st) {
    SaveSysB* sys = &lbl_80429400;
    GameState* g = &lbl_803CAB38;
    sys->ver = 0x11;
    sys->v35 = sys->v55;
    sys->v36 = g->v10;
    sys->v38 = g->v12;
    sys->v37 = g->v9C;
    fn_80245E44(sys, st);
    const char* s = lbl_80372B4C;
    fn_8008A820(st, s + 0xC4);
    fn_80062AE8(g, st);
    fn_8008A820(st, s + 0xC9);
    fn_8013498C(st);
    fn_8008A820(st, s + 0xCE);
    fn_8012D38C(st);
    fn_8008A820(st, s + 0xD3);
    fn_801058B4(st);
    fn_80105768(lbl_803E9000, st);
    fn_8008A820(st, s + 0xD8);
    fn_8008A780(st, 0xC, lbl_803E9288);
    fn_8008A820(st, s + 0xDD);
    fn_80066AC0(lbl_803CB770, st);
    fn_8008A820(st, s + 0xE2);
    fn_80119C48(st);
    fn_8008A820(st, s + 0xE7);
    fn_801131D8(st);
    fn_8008A820(st, s + 0xF2);
    fn_8004A424(lbl_803CA870, st);
    fn_8008A820(st, s + 0xEC);
    fn_8017DA3C(st);
    return 1;
}
}
