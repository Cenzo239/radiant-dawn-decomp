#include "game/rE_800E5DE4/evproc.h"

void fn_800E7E70(EvProc* p) {
    f32 sx = 0.0f;
    f32 sy = 0.0f;
    int i;
    if (lbl_803E7320.count > 0) {
        f32 ang;
        for (i = 0; i < lbl_803E7320.count; i++) {
            u8* u = fn_800CFB0C(fn_800CFD18(&lbl_803E7320, i));
            sx += (s8)u[0x102];
            sy += (s8)u[0x103];
        }
        sx /= lbl_803E7320.count;
        sy /= lbl_803E7320.count;
        ang = fn_800FB100(p->actor1, lbl_804CD934 + sx, lbl_804CD934 + sy);
        fn_80102E10(p->actor1, 0x18, 0, ang, 0);
        fn_800D5B20(p->h1);
    }
    fn_800E24F8(p->name);
}

void fn_800E7FC0(EvProc* p) {
    EvCmd* c = fn_800E3A10(p->name, p);
    if (c) {
        fn_800E5878(c, HandleActor(p->h1));
    }
}

void fn_800E801C(EvProc* p) {
    if (p->cb && !p->doneCb) {
        p->doneCb = 1;
        p->cb(p);
    }
}

void fn_800E8048(void* parent, void (*cb)(EvProc*)) {
    fn_800E5DE4(fn_80081194(lbl_803846C0, parent), cb, (char*)lbl_8036707C + 0x4D);
}

void fn_800E8098(void* parent, void (*cb)(EvProc*)) {
    fn_800E5DE4(fn_80081194(lbl_803846C0, parent), cb, (char*)lbl_8036707C + 0x57);
}

void fn_800E80E8(void* parent, void (*cb)(EvProc*)) {
    fn_800E5DE4(fn_80081194(lbl_803846C0, parent), cb, (char*)lbl_8036707C + 0x61);
}

void fn_800E8138(void* parent, void (*cb)(EvProc*)) {
    fn_800E5DE4(fn_80081194(lbl_803846C0, parent), cb, (char*)lbl_8036707C + 0x6C);
}

void fn_800E8188(void* parent, void (*cb)(EvProc*)) {
    EvProc* p = fn_80081194(lbl_803846C0, parent);
    fn_800E5DE4(p, cb, (char*)lbl_8036707C + 0x7F);
    p->unk6E = -1;
}

void fn_800E81EC(void* parent, void (*cb)(EvProc*)) {
    EvProc* p = fn_80081194(lbl_803846C0, parent);
    fn_800E5DE4(p, cb, (char*)lbl_8036707C + 0x88);
    p->unk6E = -1;
}

void fn_800E8250(EvCmd* c) {
    EvProc* p = c->proc;
    void* a = c->ctl->unkA4;
    s32 n = c->ctl->unkA8;
    if (fn_800E46C4(c, 0)) {
        fn_80103234(a, 1, 0x20, p);
        if (n == 0) {
            if (p->cb && !p->doneCb) {
                p->doneCb = 1;
                p->cb(p);
            }
        }
    }
    fn_800E28E4(c);
}

#pragma push

#pragma use_lmw_stmw on

void fn_800E8304(EvProc* p) {
    int i;
    for (i = 0; i < lbl_803E7320.count; i++) {
        u8* u = fn_800CFB0C(fn_800CFD18(&lbl_803E7320, i));
        EvCmd* c = fn_800E3A10(p->name, p);
        if (c) {
            fn_800E5878(c, u);
            c->ctl->onEvent = fn_800E8250;
            fn_800E4904(c, 0, u);
            fn_800E48F0(c, 1, i);
            c->ctl->flags |= 0x400;
        }
    }
}

#pragma pop

void fn_800E83BC(EvProc* p) {
    int i;
    for (i = 0; i < lbl_803E7320.count; i++) {
        fn_80102928(fn_800CFB0C(fn_800CFD18(&lbl_803E7320, i)), -1, 0x10, 0, 0);
    }
}

void fn_800E8428(void* parent, void (*cb)(EvProc*)) {
    fn_800E5DE4(fn_80081194(lbl_80384740, parent), cb, (char*)lbl_8036707C + 0x95);
}

void fn_800E8478(void* parent, void (*cb)(EvProc*)) {
    fn_800E5DE4(fn_80081194(lbl_80384740, parent), cb, (char*)lbl_8036707C + 0xA1);
}

void fn_800E84C8(void* parent, void (*cb)(EvProc*)) {
    fn_800E5DE4(fn_80081194(lbl_80384740, parent), cb, (char*)lbl_8036707C + 0xAD);
}

void fn_800E8518(void* parent, void (*cb)(EvProc*)) {
    fn_800E5DE4(fn_80081194(lbl_80384740, parent), cb, (char*)lbl_8036707C + 0xBA);
}

void fn_800E8568(void* parent, void (*cb)(EvProc*)) {
    fn_800E5DE4(fn_80081194(lbl_80384740, parent), cb, (char*)lbl_8036707C + 0xC6);
}

void fn_800E85B8(void* parent, void (*cb)(EvProc*)) {
    fn_800E5DE4(fn_80081194(lbl_80384740, parent), cb, (char*)lbl_8036707C + 0xD1);
}

void fn_800E8608(void* parent, void (*cb)(EvProc*)) {
    fn_800E5DE4(fn_80081194(lbl_80384740, parent), cb, (char*)lbl_8036707C + 0xE3);
}

void fn_800E8658(EvProc* p) {
    if (p->cb && !p->doneCb) {
        p->doneCb = 1;
        p->cb(p);
    }
    fn_80103234(HandleActor(p->h2), 1, 0x20, p);
}

void fn_800E86D4(void* parent, void (*cb)(EvProc*)) {
    fn_800E5DE4(fn_80081194(lbl_80384778, parent), cb, NULL);
}

void fn_800E871C(EvProc* p) {
    EvCmd* a = EvProc_CreateAnim(p);
    if (a) {
        a->ctl->onEvent = fn_800E6A10;
    }
    fn_800D6C44(0x32, 0x1E, 0);
}

void fn_800E8834(EvProc* p) {
    fn_800D6C44(0x64, 0x3C, 0);
}

void fn_800E8844(void* parent, void (*cb)(EvProc*)) {
    fn_800E5DE4(fn_80081194(lbl_803847D0, parent), cb, NULL);
}

void fn_800E888C(EvCmd* c) {
    EvProc* p = c->proc;
    EvCmd* e;
    if (fn_800E46C4(c, 0)) {
        if (*(s16*)((u8*)p->unk30 + 2) == 0x70) {
            fn_800EE270(fn_800D5C44(p->h2), p);
            PlayAt(p->h2);
        } else {
            fn_80103234(HandleActor(p->h2), 1, 0x20, p);
            e = fn_800E3A10((char*)lbl_8036707C + 0xF1, p);
            if (e) {
                fn_800E5878(e, HandleActor(p->h2));
            }
        }
        if (p->cb && !p->doneCb) {
            p->doneCb = 1;
            p->cb(p);
        }
    }
    fn_800E28E4(c);
}

void fn_800E89F0(EvProc* p) {
    EvCmd* a = EvProc_CreateAnim(p);
    if (a) {
        a->ctl->onEvent = fn_800E888C;
        if (*(s16*)((u8*)p->unk30 + 2) != 0x70) {
            fn_800E24F8((char*)lbl_8036707C + 0xF1);
        }
    }
}

void fn_800E8B20(void* parent, void (*cb)(EvProc*)) {
    fn_800E5DE4(fn_80081194(lbl_80384854, parent), cb, (char*)lbl_8036707C + 0x103);
}

void fn_800E8B70(EvProc* p) {
    void* a = HandleActor(fn_800D6840(p->unk30));
    u16 flags = 0x10;
    if (p->u78.b) {
        flags |= 0x20;
    }
    fn_80103CE4(a, flags, p->unk6C, p->unk6D, p);
}

void fn_800E8BE8(s8 a, s8 b, void* parent) {
    EvProc* p = fn_80081194(lbl_80384898, parent);
    fn_800E5DE4(p, NULL, NULL);
    p->unk6C = a;
    p->unk6D = b;
    p->u78.b = 0;
}

void fn_800E8C54(s8 a, s8 b, void* parent) {
    EvProc* p = fn_80081194(lbl_80384898, parent);
    fn_800E5DE4(p, NULL, NULL);
    p->unk6C = a;
    p->unk6D = b;
    p->u78.b = 1;
}

void fn_800E8CC0(EvCmd* c) {
    EvProc* p = c->proc;
    void* m;
    if (fn_800E46C4(c, 0)) {
        m = fn_80135800(fn_8013B9A8(), p->unk6C, p->unk6D, 0x80000, 0x10);
        if (m) {
            GXColor col = lbl_804CD940;
            fn_801CB920(m, p, &col, 0x20);
        }
    }
    if (fn_800E46C4(c, 5)) {
        fn_800FB228(p->actor1, 0);
    }
    fn_800E28E4(c);
}

void fn_800E8D84(EvProc* p) {
    EvCmd* a = EvProc_CreateAnim(p);
    if (a) {
        a->ctl->onEvent = fn_800E8CC0;
        fn_800E57B4(a, p->unk6C, p->unk6D);
    }
}

void fn_800E8EAC(s8 a, s8 b, void* parent) {
    EvProc* p = fn_80081194(lbl_80384900, parent);
    fn_800E5DE4(p, NULL, NULL);
    p->unk6C = a;
    p->unk6D = b;
}

void fn_800E92C8(EvProc* p) {
    UnitObj* u;
    EvCmd* c = fn_800E3A10(p->name, p);
    if (c) {
        u = p->h2->obj;
        fn_800E4904(c, 0, NULL);
        fn_800E4904(c, 1, u);
        fn_800E5BB0(c, u);
        fn_800E49AC(c, p->unk70);
        c->ctl->onEvent = fn_800E8F10;
    }
}

void fn_800E9380(void* parent, void (*cb)(EvProc*)) {
    EvProc* p = fn_80081194(lbl_80384980, parent);
    fn_800E5DE4(p, cb, (char*)lbl_8036707C + 0x14E);
    p->u78.b = 3;
    EvProc_ShowState(p);
}

void fn_800E9458(void* parent, void (*cb)(EvProc*)) {
    EvProc* p = fn_80081194(lbl_80384980, parent);
    fn_800E5DE4(p, cb, (char*)lbl_8036707C + 0x157);
    p->u78.b = 1;
    EvProc_ShowState(p);
}

void fn_800E9530(void* parent, void (*cb)(EvProc*)) {
    EvProc* p = fn_80081194(lbl_80384980, parent);
    fn_800E5DE4(p, cb, (char*)lbl_8036707C + 0x164);
    p->u78.b = 0;
    EvProc_ShowState(p);
}

void fn_800E9608(void* parent, void (*cb)(EvProc*)) {
    EvProc* p = fn_80081194(lbl_80384980, parent);
    fn_800E5DE4(p, cb, (char*)lbl_8036707C + 0x164);
    p->u78.b = 4;
    EvProc_ShowState(p);
}

void fn_800E96E0(void* parent, int x, int y, int dmg, int type, void (*cb)(EvProc*)) {
    u8* t = fn_8012FCD0();
    if (t) {
        fn_8012F5CC(t, 2);
        if (*(f32*)(t + 8) < 40.0f) {
            *(f32*)(t + 8) = 40.0f;
        }
    }
    if (type == 0) {
        SpawnDamageFx((char*)lbl_8036707C + 0x16E, parent, x, y, dmg);
    } else if (*(s32*)(lbl_803C8E80 + 0x3F0)) {
        EvProc* p = fn_80081194(lbl_80384980, parent);
        fn_800E5DE4(p, cb, (char*)lbl_8036707C + 0x179);
        p->u78.b = 2;
        EvProc_ShowState(p);
        p->unk70 = dmg;
    } else {
        SpawnDamageFx((char*)lbl_8036707C + 0x179, parent, x, y, dmg);
    }
}

void fn_800E990C(void* parent, void (*cb)(EvProc*)) {
    fn_800E5DE4(fn_80081194(lbl_80384300, parent), cb, (char*)lbl_8036707C + 0x184);
}

void fn_800E995C(void* parent, void (*cb)(EvProc*)) {
    fn_800E5DE4(fn_80081194(lbl_80384300, parent), cb, (char*)lbl_8036707C + 0x184);
}

/* Shooter (ballista/onager) event: 0x78 = map object, 0x7C/0x7D = its
 * position, 0x7E/0x7F = target position. */
void fn_800E99AC(EvProc* p) {
    ShooterCfg* cfg = &lbl_803CA870;
    s16 kind;
    char* s;
    p->unk6C = cfg->x;
    p->unk6D = cfg->y;
    kind = *(s16*)((u8*)p->unk30 + 2);
    p->u78.p = fn_80135A54(fn_8013B9A8(), p->unk6C, p->unk6D, 0x8000, 0);
    if (!p->u78.p) {
        fn_80083DC4(p, 0x63);
        return;
    }
    p->unk7C = p->u78.p[1];
    p->unk7D = p->u78.p[2];
    p->unk7E = cfg->tx;
    p->unk7F = cfg->ty;
    fn_800E24F8((char*)lbl_8036707C + 0x196);
    s = fn_800D621C(p->unk30);
    if (s) {
        fn_800E24F8(s);
    }
    fn_800F6604(HandleActor(p->h2), (char*)lbl_8036707C + 0x1A2);
    switch (kind) {
    case 0x6E:
    case 0x6F:
        fn_800F6604(HandleActor(p->h2), (char*)lbl_8036707C + 0x11);
        break;
    case 0x70:
        fn_800F6604(HandleActor(p->h2), (char*)lbl_8036707C + 0x1A7);
        break;
    }
}

void fn_800E9B28(EvProc* p) {
    p->unk70 = fn_80176A4C(p->unk7C, p->unk7D, p->unk7E, p->unk7F);
    fn_801CAD54(p->u78.p, p, 0x14, p->unk70);
    fn_80102C6C(HandleActor(p->h2), (char*)lbl_8036707C + 0x1A2, 0x10, 0, 0);
    fn_801030B8(HandleActor(p->h2), p->unk7C, p->unk7D, 0x18, 0, 0);
    fn_801030B8(HandleActor(p->h1), p->unk7C, p->unk7D, 0x18, 0, 0);
}

void fn_800E9CAC(EvProc* p) {
    fn_801CA2C4(p->u78.p);
    fn_801CAA24(p->u78.p, 0, 0);
    fn_800620A8(lbl_803CAB38, p->unk7E, p->unk7F);
}

void fn_800E9D38(EvProc* p) {
    u32* f = (u32*)(p->u78.p + 0x14);
    if (fn_80008C98(f, 0x12)) {
        fn_80083B78(p);
    } else if (*f & 2) {
        fn_80083B78(p);
    }
}

void fn_800E9DA4(EvCmd* c) {
    GXColor col = {0x80, 0x80, 0x80, 0x40}; /* lbl_804CD94C */
    fn_8000987C(c->ctl->unk0, &col);
}

