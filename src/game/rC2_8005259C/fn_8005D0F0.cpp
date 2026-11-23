#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

extern "C" void fn_8005D0F0(void* p) {
    fn_801E5880(p);
    fn_801A7B20(p);
}

extern "C" void fn_8005D124(void* p) {
    fn_80185720(fn_801E5890(p));
    fn_80083B78(p);
}

extern "C" void fn_8005D15C(void* p) {
    fn_801E5880(p);
    fn_801911D4(p);
}

extern "C" void fn_8005D190(void* p) {
    fn_80185720(fn_801E5890(p));
    fn_80083B78(p);
}

extern "C" void fn_8005D1C8(void* p) {
    fn_801E5880(p);
    lbl_803CAB38.b9c = 2;
    fn_8019F85C(p);
}

extern "C" void fn_8005D20C(void* p) {
    fn_80185720(fn_801E5890(p));
    fn_80083B78(p);
}

extern "C" void fn_8005D244(void* p) {
    Spr* r = (Spr*)fn_800D4228(lbl_80361F9C + 0x15);
    u8* q;
    const char* str;
    Spr* t;
    if (r == 0 || r->f28 >= 0) {
        fn_800D3BCC(fn_800D4188(lbl_80361F9C + 0x15, p), 4);
    }
    fn_8012FCB0();
    q = fn_801DFF2C(fn_800D0864(*(const char**)lbl_804CB554));
    q[0x24] = 1;
    fn_800D5448(q, p, 0);
    str = lbl_80361F9C + 0x128;
    t = fn_801E5640(p, -0x1000, 0);
    if (t) {
        t->f64 = str;
    }
}

typedef struct Proc50b {
    u8 pad0[0x50];
    u8 b50;
} Proc50b;
extern "C" void fn_8005D2FC(Proc50b* p) {
    fn_8012FCC0();
    switch (lbl_803CA870.b0c) {
    case 0x81:
        fn_80083DC4(p, 0x27);
        break;
    case 0x80:
        fn_80083DC4(p, p->b50);
        break;
    }
}

extern "C" void fn_8005D368(void* parent) {
    u8* p = fn_801DFF2C(fn_800D0864(lbl_8037F790));
    p[0x24] = 1;
    fn_800D5448(p, parent, 0);
}

extern "C" void fn_8005D3B4(void* p) {
    switch (lbl_803CA870.b0c) {
    case 0x81:
        fn_80083DC4(p, 0x26);
        break;
    case 0x80:
        fn_80083DC4(p, 1);
        break;
    }
}

extern "C" void fn_8005D3EC(void) {
    fn_800CD514(fn_800CD4A4(0x11));
}

extern "C" void fn_8005D414(void* proc) {
    Spr* s;
    fn_801BA544((void (*)(void*))fn_8005D680, proc);
    s = fn_801E5640(proc, -0x1000, 0);
    if (s) {
        fn_801E5558(proc, s, 0);
    }
}
