/* Dictionary menu: list page draw */
#include "game/rN_8025EEF0/dict.h"
#include "game/rN_8025EEF0/prim2d.h"

#pragma use_lmw_stmw on

extern "C" {

void fn_80265BCC(void);
void fn_802643B8(int x, int y);
void fn_802644CC(int x, int y);
void fn_80264EF0(int x, int y);
void fn_80265060(int x, int y);
void fn_801BCA5C(f32 v);
const char* fn_800CEB4C(void);
const char* fn_800CEC24(void);
const char* fn_800CF3A4(void);
const char* fn_800CF470(void);
void fn_80291110(char* a, const char* b);
void fn_801C6D9C(const char* s, int a, int b, int c);
void fn_80179888(void* p, int a);
void fn_8017985C(void* p, int a);
void fn_80179864(void* p, int a);
void fn_80179A84(void* p);

#pragma push
#pragma use_lmw_stmw off
void fn_80263160(void) {
    char sub[0x60];
    char buf[0x60];
    const char* e1;
    const char* f1;
    const char* d1;
    const char* c1;
    const char* s;
    const char* b;
    const char* a;
    const char* c;
    const char* d;
    const char* e;
    const char* s1;
    const char* a1;
    DictState* pg;
    const char* b1;



    pg = DICT_PAGE(lbl_804CC004, lbl_804CC004->page);
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 100.0f, 1.0f);
    fn_8007E7DC(0xFF);
    fn_8007E164();
    fn_80265BCC();
    fn_802643B8(0x46, 0x42);
    fn_802644CC(0x18, 0x78);
    fn_80264EF0(0x199, 0x2A);
    fn_80265060(0xE8, 0x30);
    fn_801BCA5C(-7.0f);
    switch (lbl_804CC004->mode) {
    case 0: {

        s = lbl_80372C90;
        a = fn_800D0864(s + 0x1A1);
        b = fn_800CEB4C();
        c = fn_800D0864(s + 0x199);
        d = fn_800CEC24();
        e = fn_800D0864(s + 0x191);
        fn_80290DDC(buf, s + 0x180, fn_800CF3A4(), e, d, c, b, a);
        fn_801C6D9C(buf, 0xFF, 0, 0);
        break;
    }
    case 1: {

        s1 = lbl_80372C90;
        a1 = fn_800D0864(s1 + 0x1B6);
        b1 = fn_800CEC24();
        c1 = fn_800D0864(s1 + 0x1AD);
        d1 = fn_800CF470();
        e1 = fn_800D0864(s1 + 0x191);
        fn_80290DDC(buf, s1 + 0x180, fn_800CF3A4(), e1, d1, c1, b1, a1);
        DictState* st = lbl_804CC004;
        if (st->page == 0
            && *(s16*)((u8*)st->list[st->cur] + 0xC) >= 0) {
            f1 = fn_800D0864(s1 + 0x1C8);
            fn_80290DDC(sub, s1 + 0x1C2, fn_800CEB4C(), f1);
            fn_80291110(buf, sub);
        }
        fn_801C6D9C(buf, 0xFF, 0, 0);
        break;
    }
    }
    fn_801BCA5C(7.0f);
    fn_80179888(lbl_804CC004->m78, (int)(28.0f * pg->f38));
    if (lbl_804CC004->listCount > 0) {
        fn_8017985C(lbl_804CC004->m78, lbl_804CC004->listCount * 0x1C);
        if (lbl_804CC004->listCount < 9) {
            fn_80179864(lbl_804CC004->m78, lbl_804CC004->listCount * 0x1C);
        } else {
            fn_80179864(lbl_804CC004->m78, 0xFC);
        }
    } else {
        fn_8017985C(lbl_804CC004->m78, 1);
        fn_80179864(lbl_804CC004->m78, 1);
    }
    fn_80179A84(lbl_804CC004->m78);
}
#pragma pop

}
