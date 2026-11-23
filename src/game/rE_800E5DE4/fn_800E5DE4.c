#include "game/rE_800E5DE4/evproc.h"

/* 0x6E: skill/weapon id looked up by name, or -1 in mode 2. */
static inline void EvProc_SetSkill(EvProc* p, char* name) {
    if (fn_8002DD1C(lbl_803C8E80) == 2) {
        p->unk6E = -1;
    } else {
        p->unk6E = fn_800F0994(name);
    }
}

void fn_800E5DE4(EvProc* p, void (*cb)(EvProc*), const char* name) {
    char* tbl;
    BOOL found;
    p->cb = cb;
    p->doneCb = 0;
    p->sub = NULL;
    p->unk30 = fn_800D68BC();
    tbl = (char*)lbl_8036707C;
    p->unk70 = 0;
    p->unk6C = 0;
    p->unk6D = 0;
    if (fn_8002DD1C(lbl_803C8E80) == 2) {
        p->unk6E = -1;
    } else {
        p->unk6E = fn_800F0994(tbl);
    }
    fn_801CE800(p->unk30);
    fn_801CEAE0(p->unk30);
    fn_801CEC98(p->unk30);
    p->h1 = fn_800D683C(p->unk30);
    p->h2 = fn_800D6840(p->unk30);
    p->actor1 = HandleActor(p->h1);
    p->actor2 = HandleActor(p->h2);
    if (name) {
        strcpy(p->name, name);
    } else {
        p->name[0] = 0;
    }
    found = 0;
    if (p->actor1 && fn_8011F600(p->actor1)) {
        found = 1;
    }
    if (p->actor2 && fn_8011F600(p->actor2)) {
        found = 1;
    }
    if (!found) {
        fn_80083DC4(p, 0x63);
    }
}

void fn_800E5F60(EvProc* p) {
    void* a;
    u8* c;
    if (p->unk6E >= 0) {
        a = HandleActor(p->h1);
        c = fn_8012FCD0();
        *(f32*)(c + 0x68) = lbl_804CD928;
        fn_800FAFF0(a, 0);
        fn_800F651C(a, p->unk6E);
    }
}

void fn_800E5FE0(EvProc* p) {
    void* a;
    if (p->unk6E >= 0) {
        a = HandleActor(p->h1);
        fn_80102928(a, p->unk6E, 0x10, 0, 0);
        fn_80102CD8(a, -1, 0x10, 0);
        fn_80103304(a, p);
        fn_800FB228(a, 1);
    }
}

void fn_800E607C(EvProc* p) {
    Actor* a = HandleActor(p->h1);
    if (p->unk6E < 0) {
        fn_80083B78(p);
        return;
    }
    if (fn_800FAFD4(a, 0x16) && p->sub) {
        char* s = SubStr40(p->sub);
        if (s) {
            EvCmd* q = fn_800E3810(s, p);
            if (q) {
                Vec pos = a->pos;
                fn_800E48AC(q, pos.x, pos.y, pos.z - lbl_804CD92C);
            }
        }
    }
    if (fn_800FAFD4(a, 2)) {
        fn_80083B78(p);
    } else if (fn_800FAE98(a)) {
        fn_80083B78(p);
    }
}

void fn_800E6198(EvProc* p) {
    fn_800FB228(HandleActor(p->h1), 0);
}

void fn_800E61BC(EvProc* p) {
    void* a;
    fn_800E4548(p);
    if (p->cb && !p->doneCb) {
        p->doneCb = 1;
        p->cb(p);
    }
    if (!fn_801CE5B8(p->h1)) {
        a = HandleActor(p->h1);
        if (a) {
            fn_80103D50(a, 0x10);
        }
    }
    if (!fn_801CE5B8(p->h2)) {
        a = HandleActor(p->h2);
        if (a) {
            fn_80103D50(a, 0x10);
        }
    }
}

void fn_800E628C(EvProc* p) {
    Handle* h = p->h2;
    void* a = HandleActor(h);
    if (fn_801CE5B8(h)) {
        if (fn_800F7724(a)) {
            if (fn_8011F428(a)) {
                fn_80103A20(a, p);
            } else {
                fn_801039E8(a, p);
            }
        }
    } else {
        fn_80103D50(a, 0x10);
    }
}

void fn_800E6334(EvProc* p) {
    if (p->name[0] == 0) {
        p->sub = fn_80030CF4(p->h1->obj);
        if (p->sub) {
            fn_800E24F8(SubStr40(p->sub));
            fn_800E24F8(SubStr44(p->sub));
            fn_800E24F8(SubStr48(p->sub));
        }
    } else {
        fn_800E24F8(p->name);
    }
}

void fn_800E63E8(EvProc* p) {
    void* a = HandleActor(fn_801D0784(p->unk30, 0));
    void* b = HandleActor(fn_801D0784(p->unk30, 1));
    if (a) {
        if (b) {
            fn_8010301C(a, b, 0x10, 0, p);
            fn_8010301C(b, a, 0x10, 0, p);
        } else {
            fn_801030B8(a, p->unk6C, p->unk6D, 0x10, 0, p);
        }
    }
}

void fn_800E64D0(EvProc* p) {
    void* a = HandleActor(fn_801D0784(p->unk30, 0));
    void* b = HandleActor(fn_801D0784(p->unk30, 1));
    if (a) {
        if (b) {
            fn_8010301C(a, b, 0x10, 0, p);
        } else {
            fn_801030B8(a, p->unk6C, p->unk6D, 0x10, 0, p);
        }
    }
}

void fn_800E6594(EvProc* p) {
    fn_800EFB6C(p->h2, NULL, p, 3);
}

void fn_800E65A8(EvCmd* c) {
    EvProc* p = c->proc;
    u8* t;
    if (fn_80008E28(c->ctl->unk0, 0x12) < 0) {
        t = fn_8012FCD0();
        *(f32*)(t + 0x68) = lbl_804CD928;
        if (fn_801D049C(p->unk30) > 1) {
            fn_800D5B20(p->h2);
        }
    }
}

void fn_800E660C(EvCmd* c) {
    s16 v;
    EvProc* p = c->proc;
    u8* t;
    if (fn_800E46C4(c, 0)) {
        v = p->h2->unkE;
        fn_800EFEB8(p->h2, v, p);
        fn_800EE6CC(fn_800F7790(HandleActor(p->h2)), v, p);
        fn_80103234(HandleActor(p->h2), 1, 0x20, p);
        if (p->cb && !p->doneCb) {
            p->doneCb = 1;
            p->cb(p);
        }
    }
    if (fn_800E46C4(c, 0x12)) {
        t = fn_8012FCD0();
        *(f32*)(t + 0x68) = lbl_804CD928;
        fn_800E5CA8(c);
        fn_800D5B20(p->h2);
    }
    if (fn_800E46C4(c, 5)) {
        fn_800FB228(p->actor1, 0);
    }
    fn_800E28E4(c);
}

void fn_800E676C(EvCmd* c) {
    EvProc* p = c->proc;
    u8* t;
    if (fn_80008E28(c->ctl->unk0, 0x12) < 0) {
        t = fn_8012FCD0();
        *(f32*)(t + 0x68) = lbl_804CD928;
        if (fn_801D049C(p->unk30) > 1) {
            fn_800D5B20(p->h2);
        }
    }
}

void fn_800E67D0(EvCmd* c) {
    EvProc* p = c->proc;
    u8* t;
    if (fn_800E46C4(c, 0)) {
        if (*(s16*)((u8*)p->unk30 + 2) == 0x70) {
            fn_800EE270(fn_800D5C44(p->h2), p);
            PlayAt(p->h2);
        } else {
            fn_80103234(HandleActor(p->h2), 1, 0x20, p);
        }
        if (p->cb && !p->doneCb) {
            p->doneCb = 1;
            p->cb(p);
        }
    }
    if (fn_800E46C4(c, 0x12)) {
        t = fn_8012FCD0();
        *(f32*)(t + 0x68) = lbl_804CD928;
        fn_800E5CA8(c);
        fn_800D5B20(p->h2);
    }
    if (fn_800E46C4(c, 5)) {
        fn_800FB228(p->actor1, 0);
    }
    fn_800E28E4(c);
}

void fn_800E6948(EvCmd* c) {
    EvProc* p = c->proc;
    void* a;
    if (fn_800E46C4(c, 0)) {
        a = p->actor1;
        if (a) {
            fn_80108CC0((u8*)a + 0x110, a, 4);
            fn_80114D00(lbl_803EC898);
            fn_801484B4(p);
        }
        if (p->cb && !p->doneCb) {
            p->doneCb = 1;
            p->cb(p);
        }
    }
    if (fn_800E46C4(c, 5)) {
        fn_800FB228(p->actor1, 0);
    }
    fn_800E28E4(c);
}

void fn_800E6A10(EvCmd* c) {
    EvProc* p = c->proc;
    if (fn_800E46C4(c, 0)) {
        if (p->cb && !p->doneCb) {
            p->doneCb = 1;
            p->cb(p);
        }
    }
    if (fn_800E46C4(c, 5)) {
        fn_800FB228(p->actor1, 0);
    }
}

void fn_800E6AA4(EvCmd* c) {
    fn_800F6604(HandleActor(c->proc->h1), (char*)lbl_8036707C + 0x11);
}

void fn_800E6AD4(EvCmd* c) {
    s16 v;
    EvProc* p = c->proc;
    if (fn_800E46C4(c, 0)) {
        v = p->h2->unkE;
        if (v != 0) {
            fn_800EFEB8(p->h2, v, p);
            fn_800EE6CC(fn_800F7790(HandleActor(p->h2)), v, p);
            fn_80103234(HandleActor(p->h2), 1, 0x20, p);
        }
        v = p->h1->unkE;
        if (v != 0) {
            fn_800EFEB8(p->h1, v, p);
            fn_800EE6CC(fn_800F7790(HandleActor(p->h1)), v, p);
            fn_80103234(HandleActor(p->h1), 1, 0x20, p);
            fn_80102C6C(HandleActor(p->h1), (char*)lbl_8036707C + 0x11, 0x10, 0, 0);
            fn_80102CD8(HandleActor(p->h1), -1, 0x10, 0);
        }
        if (p->cb && !p->doneCb) {
            p->doneCb = 1;
            p->cb(p);
        }
    }
    if (fn_800E46C4(c, 5)) {
        fn_800FB228(p->actor1, 0);
    }
    fn_800E28E4(c);
}

void fn_800E6D04(EvProc* p) {
    EvCmd* a = EvProc_CreateAnim(p);
    if (a) {
        a->ctl->onUpdate = fn_800E676C;
        a->ctl->onEvent = fn_800E67D0;
    }
}

void fn_800E6E1C(EvProc* p) {
    EvCmd* a = EvProc_CreateAnim(p);
    if (a) {
        a->ctl->onUpdate = fn_800E65A8;
        a->ctl->onEvent = fn_800E660C;
    }
}

void fn_800E6F34(void* parent, void (*cb)(EvProc*)) {
    fn_800E5DE4(fn_80081194(lbl_80384300, parent), cb, NULL);
}

void fn_800E6F7C(void* parent, void (*cb)(EvProc*)) {
    fn_800E5DE4(fn_80081194(lbl_80384300, parent), cb, NULL);
}

void fn_800E6FC4(void* parent, void (*cb)(EvProc*)) {
    fn_800E5DE4(fn_80081194(lbl_80384300, parent), cb, NULL);
}

void fn_800E700C(void* parent, void (*cb)(EvProc*)) {
    fn_800E5DE4(fn_80081194(lbl_80384300, parent), cb, NULL);
}

void fn_800E7054(void* parent, void (*cb)(EvProc*)) {
    fn_800E5DE4(fn_80081194(lbl_80384330, parent), cb, NULL);
}

void fn_800E709C(void* parent, void (*cb)(EvProc*)) {
    fn_800E5DE4(fn_80081194(lbl_80384330, parent), cb, NULL);
}

void fn_800E70E4(void* parent, void (*cb)(EvProc*)) {
    fn_800E5DE4(fn_80081194(lbl_80384330, parent), cb, NULL);
}

void fn_800E712C(void* parent, void (*cb)(EvProc*)) {
    fn_800E5DE4(fn_80081194(lbl_80384330, parent), cb, NULL);
}

void fn_800E7174(EvProc* p) {
    s16 v = p->h2->unkE;
    fn_800EFEB8(p->h2, v, p);
    fn_800EE6CC(fn_800F7790(HandleActor(p->h2)), v, p);
    fn_80103234(HandleActor(p->h2), 1, 0x20, p);
    if (p->cb && !p->doneCb) {
        p->doneCb = 1;
        p->cb(p);
    }
}

void fn_800E7260(void* parent, void (*cb)(EvProc*)) {
    fn_800E5DE4(fn_80081194(lbl_80384398, parent), cb, NULL);
}

void fn_800E72A8(EvProc* p) {
    EvCmd* a = EvProc_CreateAnim(p);
    if (a) {
        a->ctl->onEvent = fn_800E6948;
    }
}

void fn_800E73B0(void* parent, void (*cb)(EvProc*)) {
    fn_800E5DE4(fn_80081194(lbl_803843F8, parent), cb, NULL);
}

void fn_800E73F8(void* parent, void (*cb)(EvProc*)) {
    fn_800E5DE4(fn_80081194(lbl_80384428, parent), cb, NULL);
}

void fn_800E7440(EvProc* p) {
    EvCmd* a = EvProc_CreateAnim(p);
    if (a) {
        a->ctl->onUpdate = fn_800E65A8;
        a->ctl->onEvent = fn_800E660C;
    }
}

void fn_800E7558(EvProc* p) {
    EvCmd* a = EvProc_CreateAnim(p);
    if (a) {
        a->ctl->onUpdate = fn_800E676C;
        a->ctl->onEvent = fn_800E67D0;
    }
}

void fn_800E7670(void* parent, void (*cb)(EvProc*)) {
    fn_800E5DE4(fn_80081194(lbl_80384488, parent), cb, NULL);
}

void fn_800E76B8(void* parent, void (*cb)(EvProc*)) {
    fn_800E5DE4(fn_80081194(lbl_80384488, parent), cb, NULL);
}

void fn_800E7700(void* parent, void (*cb)(EvProc*)) {
    fn_800E5DE4(fn_80081194(lbl_80384488, parent), cb, NULL);
}

void fn_800E7748(void* parent, void (*cb)(EvProc*)) {
    fn_800E5DE4(fn_80081194(lbl_80384488, parent), cb, NULL);
}

void fn_800E7790(EvProc* p) {
    EvCmd* a = EvProc_CreateAnim(p);
    if (a) {
        a->ctl->onEvent = fn_800E6A10;
    }
}

void fn_800E7898(void* parent, void (*cb)(EvProc*)) {
    fn_800E5DE4(fn_80081194(lbl_803845B0, parent), cb, NULL);
}

void fn_800E78E0(void* parent, void (*cb)(EvProc*)) {
    fn_800E5DE4(fn_80081194(lbl_80384530, parent), cb, NULL);
}

void fn_800E7928(void* parent, void (*cb)(EvProc*)) {
    fn_800E5DE4(fn_80081194(lbl_80384530, parent), cb, NULL);
}

void fn_800E7970(void* parent, void (*cb)(EvProc*)) {
    fn_800E5DE4(fn_80081194(lbl_80384530, parent), cb, NULL);
}

void fn_800E79B8(void* parent, void (*cb)(EvProc*)) {
    fn_800E5DE4(fn_80081194(lbl_80384530, parent), cb, NULL);
}

void fn_800E7A00(void* parent, void (*cb)(EvProc*)) {
    fn_800E5DE4(fn_80081194(lbl_80384530, parent), cb, NULL);
}

void fn_800E7A48(void* parent, void (*cb)(EvProc*)) {
    fn_800E5DE4(fn_80081194(lbl_80384530, parent), cb, NULL);
}

void fn_800E7A90(void* parent, void (*cb)(EvProc*)) {
    fn_800E5DE4(fn_80081194(lbl_80384530, parent), cb, NULL);
}

void fn_800E7AD8(EvProc* p) {
    if (p->h1->unkE != 0 || p->h2->unkE != 0) {
        fn_800EFB6C(p->h1, p->h2, p, 0);
    }
    fn_800E24F8((char*)lbl_8036707C + 0x1A);
}

void fn_800E7B38(EvCmd* c) {
    u8* mdl = c->ctl->unkA4 + 0x28;
    int idx = fn_80007630(mdl, (char*)lbl_8036707C + 0x2A);
    if (idx >= 0) {
        Vec pos = fn_800076E8(mdl, idx);
        fn_800E48C8(c, pos);
    }
}

void fn_800E7BD0(EvProc* p) {
    Actor* a = HandleActor(p->h1);
    EvCmd* c;
    if (p->unk6E < 0) {
        fn_80083B78(p);
        return;
    }
    if (fn_800FAFD4(a, 0x16)) {
        c = fn_800E3810((char*)lbl_8036707C + 0x1A, p);
        if (c) {
            fn_800E4904(c, 0, a);
            c->ctl->onEvent = fn_800E7B38;
        }
    }
    if (fn_800FAFD4(a, 2)) {
        fn_80083B78(p);
    } else if (fn_800FAE98(a)) {
        fn_80083B78(p);
    }
}

void fn_800E7CC4(EvProc* p) {
    EvCmd* a = EvProc_CreateAnim(p);
    if (a) {
        a->ctl->onUpdate = fn_800E6AA4;
        a->ctl->onEvent = fn_800E6AD4;
    }
}
