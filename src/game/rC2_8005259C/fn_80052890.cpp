#include "game/rC2_8005259C/base.h"
struct CK { u8 pad[8]; u8 b8; };
struct UX { u8 pad[0xec]; void* ec; u8 pf0[4]; CK* f4; u8 pf8[0x14]; u32 f10c; u8 pe[0x3f0 - 0x110]; };
struct GS { u8 pad[0x92c]; u8 b92c; };
extern "C" {
extern UX* lbl_804CB810;
extern GS lbl_803CAB38;
UX* fn_800677E4(void);
void fn_8010E41C(void*, int);
}
static inline UX* unitAt(u8 id) {
    if (id) {
        return &lbl_804CB810[id - 1];
    }
    return 0;
}

extern "C" void fn_80052890(void) {
    UX* c = fn_800677E4();
    if (c == 0) {
        u8 buf[0x10];
        int found = 0;
        int i;
        fn_8010E41C(buf, 1);
        for (i = 1; i < 0xff; i++) {
            UX* u = unitAt(i);
            if (u->ec && buf[u->f4->b8] && (u->f10c & 0x800)) {
                found = 1;
                break;
            }
        }
        if (found) {
            lbl_803CAB38.b92c = 2;
        } else {
            lbl_803CAB38.b92c = 1;
        }
    } else if (c->f10c & 1) {
        lbl_803CAB38.b92c = 4;
    } else {
        switch (c->f4->b8) {
        case 0:
            lbl_803CAB38.b92c = 3;
            break;
        case 1:
            if (c->f10c & 0x800) {
                lbl_803CAB38.b92c = 6;
            } else {
                lbl_803CAB38.b92c = 5;
            }
            break;
        case 2:
            lbl_803CAB38.b92c = 8;
            break;
        case 3:
            lbl_803CAB38.b92c = 7;
            break;
        }
    }
}
