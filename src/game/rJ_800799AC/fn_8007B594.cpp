/* Controller base class accessors (object array at lbl_803D7918). */
#include "game/rJ_800799AC/pad.h"

extern "C" {

extern Pad* lbl_803D7918[4];
extern int lbl_804CB5BC;
void fn_803234A0(int chan, int cmd);

Pad* fn_8007B594(int i) {
    return lbl_803D7918[i];
}

void fn_8007B5A8(Pad* p) {
    p->rawPrev = p->raw;
}

int fn_8007B5B4(Pad* p) {
    int r = 0;
    if (p->raw != 0 || p->axis[0] != 0 || p->axis[1] != 0 || p->axis[2] != 0 || p->axis[3] != 0 ||
        p->axis[4] != 0 || p->axis[6] != 0 || p->axis[5] != 0 || p->axis[7] != 0) {
        r = 1;
    }
    return r;
}

void fn_8007B630(Pad* p) {
    p->rawPrev = p->raw;
    p->raw = 0;
    p->axis[0] = 0;
    p->axis[1] = 0;
    p->axis[2] = 0;
    p->axis[3] = 0;
    p->axis[4] = 0;
    p->axis[5] = 0;
    p->axis[6] = 0;
    p->axis[7] = 0;
}

void fn_8007B664(Pad* p) {
    p->raw = 0;
    p->rawPrev = 0;
    p->axis[0] = 0;
    p->axis[1] = 0;
    p->axis[2] = 0;
    p->axis[3] = 0;
    p->axis[4] = 0;
    p->axis[5] = 0;
    p->axis[6] = 0;
    p->axis[7] = 0;
}

int fn_8007B694(Pad* p) {
    return p->f58;
}

void fn_8007B69C(Pad* p, int v) {
    p->f58 = v;
}

u32 fn_8007B800(Pad* p) {
    return p->held & (p->prev ^ p->held);
}

u32 fn_8007B814(Pad* p) {
    return p->held;
}

int fn_8007B81C(Pad* p) {
    return p->f3C;
}

int fn_8007B824(Pad* p) {
    return p->f38;
}

void fn_8007B82C(Pad* p) {
}

u32 fn_8007BC70(Pad* p, u32 m) {
    return p->flags2 & m;
}

int fn_8007BC7C(Pad* p) {
    return p->f40;
}

int fn_8007BC84(Pad* p) {
    return p->axis[0];
}

int fn_8007BC8C(Pad* p) {
    return p->axis[1];
}

int fn_8007BC94(Pad* p) {
    return p->axis[2];
}

int fn_8007BC9C(Pad* p) {
    return p->axis[3];
}

u32 fn_8007BEAC(Pad* p, u32 m) {
    return p->flags & m;
}

void fn_8007BEB8(Pad* p, u32 m) {
    p->flags &= ~m;
}

void fn_8007BEC8(Pad* p, u32 m) {
    p->flags |= m;
}

void fn_8007BED8(Pad* p, u32 m) {
    p->flags2 &= ~m;
}

void fn_8007BEE8(Pad* p, u32 m) {
    p->flags2 |= m;
}

void fn_8007BEF8(Pad* p, u32 m) {
    p->held &= ~m;
    p->press &= ~m;
    p->repeat &= ~m;
}

void fn_8007BF24(Pad* p, u32 m) {
    p->held |= m;
    p->press |= m;
    p->repeat |= m;
}

void fn_8007BF4C(Pad* p, int v) {
    p->f40 = v;
}

void fn_8007BF54(Pad* p, int v) {
    p->f3C = v;
}

void fn_8007BF5C(Pad* p, int v) {
    p->f38 = v;
}

int fn_8007BF64(Pad* p) {
    return p->axis[7];
}

int fn_8007BF6C(Pad* p) {
    return p->axis[6];
}

int fn_8007BF74(Pad* p) {
    return p->axis[5];
}

int fn_8007BF7C(Pad* p) {
    return p->axis[4];
}

u32 fn_8007BF84(Pad* p) {
    return p->prev & (p->prev ^ p->held);
}

u32 fn_8007BF98(Pad* p) {
    return p->repeat;
}

u32 fn_8007BFA0(Pad* p) {
    return p->press;
}

u32 fn_8007BFA8(Pad* p) {
    return p->prev;
}

u32 fn_8007BFB0(Pad* p) {
    return p->rawPrev & (p->rawPrev ^ p->raw);
}

u32 fn_8007BFC4(Pad* p) {
    return p->raw & (p->rawPrev ^ p->raw);
}

u32 fn_8007BFD8(Pad* p) {
    return p->rawPrev;
}

u32 fn_8007BFE0(Pad* p) {
    return p->raw;
}

int fn_8007BFE8(Pad* p) {
    return -1;
}

int fn_8007BFF0(Pad* p) {
    return p->f8;
}

void fn_8007BFF8(Pad* p) {
    p->held = 0;
    p->prev = 0;
    p->press = 0;
    p->repeat = 0;
    p->axis[0] = 0;
    p->axis[1] = 0;
    p->axis[2] = 0;
    p->axis[3] = 0;
    p->axis[4] = 0;
    p->axis[5] = 0;
    p->axis[6] = 0;
    p->axis[7] = 0;
}

void fn_8007C030(Pad* p) {
    fn_803234A0(p->chan, 0);
    p->rumble = 0;
}

int fn_8007C0DC(Pad* p) {
    return 1;
}

}
