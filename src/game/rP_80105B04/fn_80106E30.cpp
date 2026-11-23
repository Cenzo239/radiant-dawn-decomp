#include "game/rP_80105B04/rp.h"
struct Entry6 { u8 pad[4]; u8 kind; };
extern "C" {
extern u8 lbl_803CAB38[];
Entry6* fn_80062A9C(void* game, u8 id);

int fn_80106E30(u8* p) {
    Entry6* e = fn_80062A9C(lbl_803CAB38, *p);
    if (e == 0) return 0;
    switch (e->kind) {
    case 0: return 0;
    case 1: return 8;
    case 2: return 7;
    case 3: return 4;
    case 4: return 5;
    default: return 0;
    }
}
}
