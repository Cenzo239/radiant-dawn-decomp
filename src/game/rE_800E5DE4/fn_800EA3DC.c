#include "game/rE_800E5DE4/evproc.h"

void fn_800EA3DC(EvProc* p) {
    if (p->unk80 >= p->unk82 - 4) {
        fn_80083B78(p);
    }
}

void fn_800EA3F8(EvProc* p) {
    fn_801CAA24(p->u78.p, 0, 2);
}

void* fn_800EA810(void* parent) {
    fn_800E5DE4(fn_80081194(lbl_80384A04, parent), NULL, NULL);
}

void fn_800EA848(EvCmd* c) {
    GXColor col = {0x80, 0x80, 0x80, 0x40}; /* lbl_804CD970 */
    fn_8000987C(c->ctl->unk0, &col);
}

void fn_800EAF9C(EvProc* p) {
    fn_801CA2C4(p->u78.p);
    fn_801CAA24(p->u78.p, 0, 0);
}

void fn_800EAFDC(EvProc* p) {
    u32* f = (u32*)(p->u78.p + 0x14);
    if (fn_80008C98(f, 0x12)) {
        fn_80083B78(p);
    } else if (*f & 2) {
        fn_80083B78(p);
    }
}

void fn_800EB3C8(EvProc* p) {
    fn_801CAA24(p->u78.p, 0, 2);
}

void fn_800EB3D8(void* parent) {
    fn_800E5DE4(fn_80081194(lbl_80384AB8, parent), NULL, NULL);
}

void fn_800EC204(BtlProc* b) {
    Handle* x;
    Handle* y;
    if (b->unk40 != 2) {
        x = fn_801D0784(b->unk30, 0);
        y = fn_801D0784(b->unk30, 1);
        switch (b->unk40) {
        case 1:
            fn_800EFB6C(y, NULL, b, 0);
            break;
        default:
            fn_800EFB6C(x, y, b, 0);
            break;
        }
    }
}

void fn_800EC294(BtlProc* b) {
    if (b->unk40 != 2) {
        fn_800EFBCC();
    }
}

void fn_800EC2A8(BtlProc* b) {
    fn_801CEAD0(b->unk30);
    b->unk46 = 0;
    if (fn_801CEAE0(b->unk30)) {
        b->h1 = fn_800D683C(b->unk30);
        b->h2 = fn_800D6840(b->unk30);
        fn_800D6724(b->unk30);
    } else {
        fn_80083DC4(b, 9);
    }
}

void fn_800EC320(BtlProc* b) {
    fn_801CEC98(b->unk30);
    b->unk45 = 0;
}

void fn_800EC358(BtlProc* b) {
    if (b->unk42) {
        fn_80083DC4(b, 8);
        return;
    }
    switch (b->unk30[1]) {
    case 1:
    case 5:
        fn_80083DC4(b, 4);
        break;
    case 2:
        fn_80083DC4(b, 2);
        break;
    case 6:
        fn_80083DC4(b, 3);
        break;
    case 3:
        fn_80083DC4(b, 5);
        break;
    case 4:
        fn_80083DC4(b, 6);
        break;
    case 7:
        fn_80083DC4(b, 7);
        break;
    case 0:
        break;
    }
}

void fn_800EC3C8(BtlProc* b) {
    u8* d = b->unk30;
    if ((int)d[0xA] > 0x40) {
        fn_80083DC4(b, 9);
    } else if (d[9]) {
        fn_801CEAE0(d);
        fn_80083DC4(b, 1);
    } else {
        fn_80102C6C(fn_801D080C(d), (char*)lbl_803672A0 + 0xCA, 8, 0x20, 0);
        fn_80083DC4(b, 0);
    }
}

void fn_800EC460(BtlProc* b) {
    b->unk44 = 0;
}

void fn_800ED0E0(EvCmd* c) {
    EvAnimCtl* ctl = c->ctl;
    u16 kind = *(u16*)((u8*)ctl + 4);
    void* a = *(void**)&ctl->unkA8;
    if (kind != 2) {
        fn_800FB228(a, 0);
    }
}

void fn_800ED6A0(BtlProc* b) {
    b->unk48 = -1;
    if (fn_801CFCE0(b->unk30)) {
        fn_800EBB74(b);
    } else {
        fn_800EB988(b);
    }
}

void fn_800ED6F4(BtlProc* b) {
    fn_800D679C(b->unk30);
}

void fn_800ED6FC(BtlProc* b) {
    fn_800FB228(HandleActor(b->h1), 1);
}

void fn_800ED720(BtlProc* b) {
    fn_800FB228(HandleActor(b->h1), 0);
}

void fn_800ED744(BtlProc* b) {
    Handle* h;
    int i;
    for (i = 0; i < 3; i++) {
        void* a;
        h = fn_801D0784(b->unk30, i);
        fn_800D616C(h);
        if (!fn_801CE5B8(h)) {
            a = HandleActor(h);
            if (a) {
                fn_80102928(a, -1, 0x18, 0, 0);
            }
        }
    }
}

void fn_800ED8F8(void) {
    fn_800D6C44(0x32, 0x1E, 0);
}

void fn_800ED908(void) {
    fn_800D6C44(0x64, 0x1E, 0x10);
}

void fn_800EDA80(BtlProc* b) {
    if (b->unk40 != 2) {
        fn_800D6A44(b);
    }
}

void fn_800EDA94(BtlProc* b) {
    if (b->unk40 != 2) {
        fn_800D6A64(b);
    }
}

void fn_800EDAA8(BtlProc* b) {
    b->unk41 = 1;
}

static inline void BtlProc_UpdUnit(Handle* h) {
    void* a;
    fn_800D616C(h);
    a = HandleActor(h);
    if (a) {
        if (fn_801CE5B8(h)) {
            fn_800FBDF0(a);
        } else {
            fn_800F4B94(a, -1);
        }
    }
}

void fn_800EDAB4(BtlProc* b) {
    int i;
    fn_800E4548(b);
    if (!b->unk41) {
        for (i = 0; i < 3; i++) {
            BtlProc_UpdUnit(fn_801D0784(b->unk30, i));
        }
    }
}

