#include "game/rG_800A3D88/battle.h"

#pragma auto_inline off

extern "C" {

extern const f32 lbl_804CD354;
extern char lbl_80365488[];
extern u8 lbl_80382220[];

int fn_801D04AC(Scr*);
#if TARGET_PC
FE10_PROTO struct Entry18 * fn_800A79A4(const char*, int);
#else
int fn_800A79A4(const char*, int);
#endif
struct UnitH { u8 pad[0x3F0]; void* m3f0; };
UnitH** fn_801D0784(Scr*, int);
void* fn_800A75E8(void*, int);
int fn_800AA548(Ev*, const char*, int);
void fn_800AAB1C(Ev*, int);
void fn_800AE940(void*, int);
void fn_800AAB38(Ev*, int);
void fn_800A5D68(Body*, int, int);
void fn_800AA97C(Ev*);
void fn_800AAA38(Ev*);
void fn_800A4B00(Body*, void*);
void fn_801CEC98(Scr*);
void fn_800A9E64(Battle*, int, int);
void* fn_800B7468(Chan*);
#if TARGET_PC
FE10_PROTO void fn_800AA1E4(Battle*, ptr32<const void>);
#else
void fn_800AA1E4(Battle*, void*);
#endif
void fn_800A9FC8(Battle*, int, int);
struct Chr38 { u8 pad[0x38]; void* m38; };
Chr38* fn_800B5784(Chan*, int);
void fn_800A6978(void*, int);
void* fn_800BAB5C(Chan*, Scr*);
void fn_800E24F8(void*);
int fn_800BD280(Chan*);
int fn_800BD218(Chan*);
int fn_800B5D14(Chan*);
int fn_800B0C28(Chan*);
int fn_801D02FC(Scr*);
int fn_801CE608(UnitH**);
int fn_800BCC54(Chan*);
int fn_800B7260(Chan*, int);
void fn_800ADA7C(void*);
void fn_80083DC4(void*, int);
void fn_800A99C4(void*);
int fn_800B65F8(Chan*);
int fn_800B663C(Chan*);
int fn_800B1B48(Chan*, int, int, u16, int);
void fn_800A5F08(Body*, Chan*, int);
void fn_801CEAE0(Scr*);
void fn_800BB3DC(void*, Scr*);
f32 fn_800A84A4(const char*);
int fn_801CFCE0(Scr*);
void fn_800AD740(Battle*, Chan*, Chan*);
void fn_800AD068(Battle*, Chan*, Chan*, int);
void fn_800A47AC(Body*, int);
void fn_800B26B0(Chan*, const char*, int, u16);
int fn_801CFE78(Scr*, int);
void fn_800AAFAC(Battle*, int);
void fn_800AADBC(Battle*, int);
void* fn_8017C288(void*);
void fn_8017C1AC(void*, int);
void fn_800846BC(void*);
int fn_801D038C(Scr*);
int fn_800A8208(const char*);
void fn_8017C218(int, void*);
void fn_80081280(int, void*);
void fn_800B0BF4(Chan*, int);
#if TARGET_PC
FE10_PROTO ptr32<void> fn_800A7460(void*, const char*);
#else
void* fn_800A7460(void*, const char*);
#endif
void fn_800BD024(Chan*, const char*);

static inline void* UnitRes(Scr* s, int i) {
    UnitH* u = *fn_801D0784(s, i);
    if (u != NULL) {
        return u->m3f0;
    }
    return NULL;
}

void fn_800AB1D0(Battle* p) {
    const char* x = lbl_803C8E80.x1624;
    p->m78 = 0;
    if (fn_801D04AC(p->m88) == 0) {
        p->m78 = 1;
    }
    if (lbl_803C8E80.flags & 0x04000000) {
        if (fn_800A79A4(x, 4) != 0) {
            p->m78 = 4;
        }
    }
    if (lbl_803C8E80.flags & 0x02000000) {
        if (fn_800A75E8(UnitRes(p->m88, 0), 1) != NULL
            && fn_800A75E8(UnitRes(p->m88, 1), 1) != NULL
            && fn_800A79A4(x, 2) != 0) {
            if (fn_801D04AC(p->m88) != 0) {
                p->m78 = 2;
            } else {
                p->m78 = 3;
            }
        }
    }
}

static inline BOOL CanShow(Battle* p) {
    switch (p->m78) {
    case 0:
    case 2:
        return 1;
    case 1:
    default:
        return 0;
    }
}

void fn_800AB310(Battle* p) {
    int fc = lbl_803C8E80.fc;
    u8 fd = lbl_803C8E80.fd;
    if (fn_800AA548(p->m30, lbl_803C8E80.x1624, p->m78) != 0) {
        if (!(p->m30->m54->m8 & 2)) {
            fn_800AAB1C(p->m30, fc);
            fn_800AE940(p->m34, fc);
        }
        fn_800AAB38(p->m30, fd);
    }
    p->m81 = 1;
    Res54* r = p->m30->m54;
    if (r != NULL && !(r->m8 & 0x10)) {
        p->m81 = 0;
    }
    if (!CanShow(p)) {
        p->m81 = 0;
    }
}

void fn_800AB988(Battle* p) {
    p->m44->m76 = p->m78;
    p->m44->m75 = 0;
    if (lbl_803C8E80.flags & 0x00C00000) {
        p->m44->m75 = 1;
    }
    if (lbl_803C8E80.flags & 0x10000000) {
        p->m44->m75 = 1;
    }
    if (lbl_803C8E80.flags & 0x08000000) {
        p->m44->m75 = 2;
        fn_800A5D68(p->m44, 1, 0);
    }
    if (p->m81 != 0 && p->m70->m54 == 0) {
        Res54* r = p->m30->m54;
        if (r != NULL) {
            if (r->m8 & 0x20) {
                fn_800AA97C(p->m30);
            }
            if (r->m8 & 0x40) {
                fn_800AAA38(p->m30);
            }
        }
    }
    void* a = p->m70;
    if (lbl_803C8E80.flags & 0x00400000) {
        a = p->ch[1];
        p->m44->m6d = 1;
    }
    if (lbl_803C8E80.flags & 0x00800000) {
        a = p->ch[1];
        p->m44->m6e = 1;
    }
    fn_800A4B00(p->m44, a);
}

void fn_800ABD80(Battle* p) {
    fn_801CEC98(p->m88);
    switch (p->m88->m1) {
    case 2:
    case 3:
        fn_800A9E64(p, -1, -1);
        if (fn_800B7468(p->m70) != NULL) {
            fn_800AA1E4(p, fn_800B7468(p->m70));
            fn_800A9FC8(p, -1, -1);
        }
        break;
    }
    for (int i = 0; i < 2; i++) {
        Chr38* c = fn_800B5784(p->m70, i);
        if (c != NULL) {
            fn_800A6978(c->m38, p->m78);
        }
    }
    void* x = fn_800BAB5C(p->m70, p->m88);
    if (x != NULL) {
        fn_800E24F8(x);
    }
}

static inline Chan* ChGet(Battle* p, int i) {
    if (i < 0) {
        return NULL;
    }
    return p->ch[i];
}

BOOL fn_800ACE88(Battle* p) {
    for (int i = 0; i < 2; i++) {
        Chan* c = ChGet(p, i);
        if (fn_800BD280(c) != 0 && !(c->flags & 0x400000)) {
            if (c->flags & 0x100) {
                return 1;
            }
            if (fn_800BD218(c) != 0) {
                return 1;
            }
            if (fn_800B5D14(c) == 0 && fn_800B0C28(c) == 0) {
                return 1;
            }
        }
    }
    return 0;
}

BOOL fn_800AD954(Battle* p) {
    if (p->m6b < p->m6a) {
        return 0;
    }
    if (p->m88->m8 != 0 && (lbl_803C8E80.flags & 0x00200000)) {
        return 1;
    }
    if (fn_801D02FC(p->m88) == 0x28
        && fn_801CE608(fn_801D0784(p->m88, p->m70->m55)) != 0
        && fn_801CE608(fn_801D0784(p->m88, p->m74->m55)) != 0) {
        return 1;
    }
    if (fn_800BCC54(p->m70) != 0) {
        return 0;
    }
    if (p->m88->m9 != 0 && fn_800B7260(p->m70, 5) != 0) {
        p->m80 = 1;
        return 1;
    }
    if (fn_800B5D14(p->m70) != 0) {
        return 1;
    }
    return 0;
}

void fn_800ADC84(void* p) {
    fn_800ADA7C(p);
}

void fn_800ADC88(Battle* p) {
    fn_80083DC4(p, 1);
    if (p->m81 != 0) {
        fn_80083DC4(p, 0);
    }
    if (p->m82 != 0) {
        fn_80083DC4(p, 2);
    }
}

void fn_800ADCE8(Battle* p) {
    if (++p->m94 > 0x2A30) {
        fn_80083DC4(p, 0xC);
    }
}

void fn_800ADD08(void* p) {
    fn_800A99C4(p);
}

BOOL fn_800ADD10(Battle* p) {
    BOOL r;
    if (p->m7e > 0) {
        p->m7e--;
        r = 1;
    } else {
        r = 0;
    }
    return r;
}

BOOL fn_800ADD54(Battle* p) {
    if (fn_800B65F8(p->m70) != 0 && fn_800B663C(p->m70) == 0) {
        return 0;
    }
    p->m70->flags &= ~0x00080000;
    return 1;
}

void fn_800ADDB8(Battle* p) {
    int v = 0xFFFF;
    int id = p->m68;
    if (p->m80) {
        v = 6;
    }
    if (fn_800B1B48(p->m70, id, -1, v, -1) != 0) {
        fn_800A4B00(p->m44, p->m70);
        fn_800A5F08(p->m44, p->m70, id);
    } else {
        fn_80083DC4(p, 4);
    }
}

void fn_800ADE58(Battle* p) {
    fn_801CEAE0(p->m88);
    fn_801CEC98(p->m88);
    fn_800BB3DC(p->m74, p->m88);
    p->m6b = 0;
    p->m6a = 1;
    p->m7e = fn_800A84A4(lbl_80365488 + 0x10C);
}

BOOL fn_800ADECC(Battle* p) {
    if (p->m6b < p->m6a) {
        if (fn_801CFCE0(p->m88) != 0) {
            fn_800AD740(p, p->m74, p->m70);
        } else {
            fn_800AD068(p, p->m74, p->m70, -1);
        }
        fn_800A4B00(p->m44, p->m74);
        fn_800A47AC(p->m44, 0);
    }
    return fn_800AD954(p) == 0;
}

void fn_800ADF64(Battle* p) {
    p->m79 = 0;
    int n = p->m88->mC;
    if (n > 0) {
        int v = 0xFFFF;
        fn_800B26B0(p->m70, lbl_80365488 + 0x49, -1, v);
    }
}

BOOL fn_800ADFA4(Battle* p) {
    Scr* s = p->m88;
    int i = p->m79;
    if (i >= s->mC) {
        return 1;
    }
    p->m79 = i + 1;
    int id = s->mE[i];
    if (fn_801CFE78(s, id) == 0) {
        fn_800AAFAC(p, id);
        fn_800AADBC(p, id);
    }
    p->m80 = 1;
    return 0;
}

void fn_800AE03C(Battle* p) {
    void* o = fn_8017C288(p);
    if (o != NULL) {
        fn_8017C1AC(o, -1);
    }
    fn_800846BC(lbl_80382220);
    p->m94 = 0;
    if (fn_801D038C(p->m88) >= 0) {
        fn_80083DC4(p, 8);
    }
}

void fn_800AE0A8(Battle* p) {
    if (!(p->m74->flags & 0x400000)) {
        int id = fn_800A8208(lbl_80365488 + 0x11B);
        int v = 0xFFFF;
        fn_800B1B48(p->m74, id, -1, v, -1);
        fn_800A4B00(p->m44, p->m70);
        fn_800A5F08(p->m44, p->m74, id);
    }
}

void fn_800AE13C(Battle* p) {
    struct Sub { u8 pad[0xF4]; Res54* f4; };
    UnitH* u = *fn_801D0784(p->m88, fn_801D038C(p->m88));
    Sub* r = (Sub*)(u != NULL ? u->m3f0 : NULL);
    int w = (int)fn_800A84A4(lbl_80365488 + 0x120);
    int t = (int)((f32)w * lbl_804CD354);
    switch (r->f4->m8) {
    case 0:
        fn_8017C218(2, p);
        fn_80081280(0, p);
        fn_80083DC4(p, 0xA);
        break;
    default:
        p->m7c = t;
        fn_80083DC4(p, 0xC);
        break;
    }
}

void fn_800AE230(Battle* p) {
    int id = fn_800A8208(lbl_80365488 + 0x131);
    int v = 0xFFFF;
    if (fn_800B1B48(p->m70, id, -1, v, -1) != 0) {
        p->m4c = 0;
        fn_800B0BF4(p->m70, 1);
        p->m70->flags |= 0x01000000;
        p->m70->flags |= 0x02000000;
        if (fn_800A7460(p->m70->m78, lbl_80365488 + 0x136) != NULL) {
            fn_800BD024(p->m70, lbl_80365488 + 0x49);
        }
        fn_800A4B00(p->m44, p->m70);
        fn_800A5F08(p->m44, p->m70, id);
        int w = (int)fn_800A84A4(lbl_80365488 + 0x13F);
        p->m7c = (f32)w * lbl_804CD354;
    }
}

} // extern "C"
