#include "game/rI_801DD7D4/types.h"
#pragma auto_inline off
extern "C" {
extern char lbl_803905A0[];
extern char lbl_80390984[];
void* fn_80081194(void*, void*);
void* fn_80081050(void*, void*);
void fn_801E4094(void*);
void fn_80111B34(void*);
u8 fn_801E71B4(void);
struct P9 { u8 p[0x40]; u8 s[0x28]; int x68, x6c, x70, x74, x78, x7c; u8 x80, x81; u8 p82[2]; f32 x84; void* x88; int x8c; };
P9* fn_80234888(void* parent) {
    P9* p;
    if (parent != NULL) {
        p = (P9*)fn_80081194(lbl_803905A0, parent);
    } else {
        p = (P9*)fn_80081050(lbl_803905A0, parent);
    }
    if (p != NULL) {
        fn_801E4094(p);
        fn_80111B34(p->s);
        p->x68 = 0;
        p->x6c = 0;
        p->x70 = 0;
        p->x74 = 0;
        p->x78 = 0;
        p->x7c = 0;
        p->x80 = 0;
        p->x81 = 0;
        p->x84 = 1.0f;
        p->x88 = 0;
        p->x8c = 0;
    }
    p->x80 = fn_801E71B4();
    switch (p->x80) {
    case 4:
        p->x88 = lbl_80390984;
        break;
    case 0:
    case 1:
    case 2:
    case 3:
    default:
        break;
    }
    return p;
}
}
