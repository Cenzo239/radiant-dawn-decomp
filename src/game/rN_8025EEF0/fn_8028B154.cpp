#include "game/rN_8025EEF0/calls.h"
extern "C" {
extern char lbl_803932EC[];
extern void* lbl_804CC0F0;
void* fn_8029C7D8(void);
void fn_8029D3E8(void*,int,int);
void fn_8030D688(int);
void fn_8008939C(void* proc);
void fn_8024DEF0(f32 v);
void fn_80256EE8(void* p);
void fn_8025704C(f32 v);
void fn_80256FA4(void* p);
void fn_802570D0(f32 v);
u32 fn_8030585C(int w, int h, int a, int b, int c);
void* fn_80079958(u32 size, int align);
void DCInvalidateRange(void* p, u32 n);
void fn_80305A40(void* o, void* p, int w, int h, int a, int b, int c, int d);
void fn_80305C94(void* o, int a, int b, int c, int d, int e, f32 x, f32 y, f32 z);


struct TvTex { u8 d[0x20]; };
// The original 0x60-byte block starts at lbl_80430CE0.
// Keep the texture and the two state areas as separately pooled statics.
static TvTex tex;
static u8 stateA[0x2c];
static u8 stateC[0x14];
void fn_8028B154(void) {
    int i;
    u32 size;
    fn_8024DEF0(250.0f);
    fn_80256EE8(stateA);
    fn_8025704C(250.0f);
    fn_80256FA4(stateC);
    fn_802570D0(250.0f);
    fn_8029D3E8(fn_8029C7D8(), 2, 0xFA);
    {
        int proc = fn_80085708(lbl_803932EC);
        if (proc != 0) {
            fn_8008939C((void*)proc);
        }
    }
    for (i = 0; i < 4; i++) {
        fn_8030D688(i);
    }
    size = fn_8030585C(0x260, 0x1C0, 4, 0, 0);
    if (lbl_804CC0F0 == 0) {
        lbl_804CC0F0 = fn_80079958(size, 0x40);
    }
    DCInvalidateRange(lbl_804CC0F0, size);
    fn_80305A40(&tex, lbl_804CC0F0, 0x260, 0x1C0, 4, 0, 0, 0);
    fn_80305C94(&tex, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f);
}



}
