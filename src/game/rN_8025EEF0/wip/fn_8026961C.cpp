/* 6 words: third slot loop wants i r31, s r30; declaration orders that fix it break the first two loops. */
#include "game/rN_8025EEF0/calls.h"
struct Slot { void* u; s16 a, b; };
extern "C" {
extern Slot lbl_80430740[3][20];
void fn_800C4AA8(void* p);
void fn_8017AB5C(void* p, int a);
void fn_8011FE74(void* u, int a);
void fn_8026961C(u8* p) {
    Slot* s;
    int i;
    if (*(void**)(p + 0x34) != 0) {
        fn_80006A2C(p + 0x34);
    }
    if (*(void**)(p + 0x38) != 0) {
        fn_800C4AA8(p + 0x38);
    }
    if (*(void**)(p + 0x3C) != 0) {
        fn_8017AB5C(*(void**)(p + 0x3C), 1);
    }
    {
        Slot* s0 = lbl_80430740[0];
        int i0;
        for (i0 = 0; i0 < 0x14 && s0->u != 0; s0++, i0++) {
            fn_8011FE74(s0->u, 8);
        }
    }
    {
        s = lbl_80430740[1];
        for (i = 0; i < 0x14 && s->u != 0; s++, i++) {
            fn_8011FE74(s->u, 9);
        }
    }
    {
        Slot* s2;
        int i2;
        s2 = lbl_80430740[2];
        for (i2 = 0; i2 < 0x14 && s2->u != 0; s2++, i2++) {
            fn_8011FE74(s2->u, 10);
        }
    }
}

}
