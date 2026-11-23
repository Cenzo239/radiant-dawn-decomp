#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

extern "C" void fn_800539F8(void) {
    Unit2* u = (Unit2*)lbl_803CA870.unit;
    fn_80103D50(u, -1);
    fn_800620A8(&lbl_803CAB38, u->x102, u->y103);
}

extern "C" void fn_80053A7C(void) {
    fn_80068A58();
}

extern "C" void fn_80053A80(void) {
    s8 y;
    s8 x;
    Unit* u = fn_800677E4();
    fn_800679EC();
    y = u->y103;
    x = u->x102;
    {
        s8 z = fn_8012408C(u);
        fn_8014083C(x, y, z);
    }
    fn_80122460(u);
}

extern "C" int fn_80053AEC(ScriptCtx* c) {
    u32 w = *c->pc;
    if ((w >> 24) == lbl_803CA870.b0c) {
        fn_80083DC4(c, (w >> 16) & 0xff);
    }
    c->pc++;
    return 1;
}

extern "C" int fn_80053B4C(ScriptCtx* c) {
    if (lbl_804CB728 == 9) {
        fn_80083DC4(c, (*c->pc >> 16) & 0xff);
    }
    c->pc++;
    return 1;
}

extern "C" int fn_80053BA0(ScriptCtx* c) {
    c->pc++;
    return 1;
}

extern "C" int fn_80053BB4(ScriptCtx* c) {
    c->pc++;
    return 1;
}

typedef void (*ScriptFn)(ScriptCtx*);
extern "C" int fn_80053BC8(ScriptCtx* c) {
    if (lbl_804CB728 == 9) {
        ScriptFn f = (ScriptFn)c->pc[1];
        c->pc += 2;
        f(c);
        c->pc -= 2;
    }
    c->pc += 2;
    return 1;
}

extern "C" int fn_80053C30(ScriptCtx* c) {
    fn_800310E4((const char*)c->pc[1], 0, 0x28, 0);
    c->pc += 2;
    return 1;
}

extern "C" int fn_80053C80(ScriptCtx* c) {
    fn_800310E4(fn_800D0864((const char*)c->pc[1]), 0, 0x28, 0);
    c->pc += 2;
    return 1;
}

extern "C" int fn_80053CD4(ScriptCtx* c) {
    if (fn_8012FCD8(0)) {
        return 0;
    }
    c->pc++;
    return 1;
}

extern "C" int fn_80053D24(ScriptCtx* c) {
    c->pc++;
    return 1;
}

extern "C" int fn_80053D38(ScriptCtx* c) {
    c->pc++;
    return 1;
}

extern "C" int fn_80053D4C(ScriptCtx* c) {
    c->pc++;
    return 1;
}

extern "C" int fn_80053D60(ScriptCtx* c) {
    fn_800CD4A4((s16)(*c->pc >> 16));
    c->pc++;
    return 1;
}

extern "C" void fn_80053DAC(void) {
    fn_80089388(2, lbl_8037DD18);
}

extern "C" int fn_80053DBC(int a) {
    Unit2* u = fn_8002C590(&lbl_803C8E80);
    Unit2* o;
    s8 x;
    s8 y;
    if (u == 0) {
        return 0;
    }
    if (!(u->flags108 & 2)) {
        return 0;
    }
    o = u->link3f0;
    fn_8011EB4C(o, &x, &y);
    fn_801037D4(o->f8, o->f8->x102, o->f8->y103, x, y, a);
    fn_8011E300(o, x, y, 1);
    return 1;
}

extern "C" void fn_80053E7C(void* p) {
    Word* w = fn_800CFD3C(&lbl_803E7320);
    if (w == 0) {
        fn_80083DC4(p, 0x63);
    } else {
        Unit2* u = (Unit2*)fn_800CFB0C(w);
        if (u && !((u32)u->flags108 & 0x10000dc)) {
            fn_800620A8(&lbl_803CAB38, u->x102, u->y103);
        }
    }
}
