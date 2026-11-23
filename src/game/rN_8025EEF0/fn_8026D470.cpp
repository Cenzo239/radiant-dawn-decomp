/* Random-order list (lbl_804CC044): switch the shown model */
#include "game/rN_8025EEF0/calls.h"

struct ListItem { const char* name; s16 x; s16 y; s16 s; };
struct ListSt {
    u8 pad0[0xC];
    int n;
    u8 pad10[4];
    u8* items;
    u8 pad18[4];
    int cur;
    u8 pad20[0x18];
    const char* m38;
    const char* m3C;
};

extern "C" {

extern ListSt* lbl_804CC044;
u8* fn_800D4228(const char* s);
u8* fn_800D4188(const char* s, void* p);
void fn_800D3C90(u8* p, int a);
void fn_800D3BCC(u8* p, int a);
void fn_800D3990(u8* p);
void fn_800D433C(const char* s);

void fn_8026D470(void) {
    int off;
    f32 y;
    ListItem* e;
    f32 x;
f32 sc;
    u8* o;
    int a;
    int b;
    if (lbl_804CC044->m3C != 0 && fn_800D4228(lbl_804CC044->m3C) != 0) {
        fn_80081A90(fn_800D4228(lbl_804CC044->m3C));
    }
    lbl_804CC044->m3C = lbl_804CC044->m38;
    off = lbl_804CC044->cur * 0xC;
    lbl_804CC044->m38 = *(const char**)(lbl_804CC044->items + off);
    o = fn_800D4228(lbl_804CC044->m3C);
    fn_800D3C90(o, 0x40);
    *(f32*)(o + 0x48) = 0.0f;
    e = (ListItem*)(lbl_804CC044->items + off);
    fn_800D3BCC(fn_800D4188(lbl_804CC044->m38, 0), 0x40);
    fn_800D3990(fn_800D4228(lbl_804CC044->m38));
    x = e->y;
    y = e->x;
    o = fn_800D4228(lbl_804CC044->m38);
    *(f32*)(o + 0x40) = y;
    *(f32*)(o + 0x44) = x;
    *(f32*)(o + 0x48) = -700.0f;
    sc = e->s / 100.0f;
    o = fn_800D4228(lbl_804CC044->m38);
    *(f32*)(o + 0x54) = sc;
    *(f32*)(o + 0x58) = sc;
    a = lbl_804CC044->cur - 1;
    b = lbl_804CC044->cur + 1;
    if (a < 0) {
        a = lbl_804CC044->n - 1;
    }
    if (b > lbl_804CC044->n - 1) {
        b = 0;
    }
    fn_800D433C(*(const char**)(lbl_804CC044->items + a * 0xC));
    fn_800D433C(*(const char**)(lbl_804CC044->items + b * 0xC));
}

}
