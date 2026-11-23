#include "game/rG_800A3D88/battle.h"

#pragma auto_inline off

extern "C" {

extern const f32 lbl_804CD380;
extern const f32 lbl_804CD384;
extern const f32 lbl_804CD3AC;
extern const f32 lbl_804CD3B0;
extern const f32 lbl_804CD3B8;
extern char lbl_80365488[];
extern char lbl_803656F8[];
extern u8 lbl_8038224C[];
extern u8 lbl_80382440[];
extern u8 lbl_803824E0[];
extern u8 lbl_803CAB38[];

struct UnitH { u8 pad[0x3F0]; struct UnitD* m3f0; };
struct UnitD { u16 flags; };

UnitH* fn_8002C738(SceneGlobal*);
void fn_80186AF0(UnitD*, void*);
BOOL fn_800ACE88(void*);
int fn_800BD280(Chan*);
u8 fn_8024F7EC(const char*);
void fn_80252850(int, f32);
int fn_80251838(int, const char*, f32);
void fn_80252738(int, f32);
void fn_800C835C(int, u16);
void* fn_80081194(void*, void*);
void* fn_80081050(void*, void*);
void* fn_80083B84(void*);
void fn_80134DB0();
void fn_80062598(void*, void*);
void fn_8012D78C();
void fn_80062380(void*, void*);
void fn_80134E30();
void fn_80062454(void*);
void fn_801314E0();
void fn_8012D620();
void fn_8012D908();
void fn_80068AFC(int);
void fn_80068A6C(int);
void fn_80068AB4(int);
void fn_8002BCC4(SceneGlobal*);
UnitH* fn_8002C590(SceneGlobal*);
int fn_8011F428(UnitD*);
#if TARGET_PC
FE10_PROTO void fn_8010301C(void*, void*, int, int, p32arg);
#else
void fn_8010301C(void*, void*, int, int, int);
#endif
void fn_801868E8(UnitD*, void*);
void fn_80081A90(void*);
void fn_8009E554(const char*, void*);
int fn_800A7C28(const char*);
int fn_800AE940(void*, int);
void fn_80006EE0(void*);
void fn_8023F1A8(void*);
void fn_80011CBC(void (*)(void*), void*);

BOOL fn_800AE4FC(void* p) {
    return fn_800ACE88(p);
}

void fn_800AE4AC(void* p) {
    UnitH* u = fn_8002C738(&lbl_803C8E80);
    if (u != NULL) {
        UnitD* d = u->m3f0;
        if (d != NULL) {
            fn_80186AF0(d, p);
        }
    }
}

static inline Chan* ChGet(Battle* p, int i) {
    if (i < 0) {
        return NULL;
    }
    return p->ch[i];
}


void fn_800AE58C(Battle* p) {
    const char* s = lbl_803C8E80.m1600;
    if (s != NULL && *s != 0) {
        p->m7a = fn_8024F7EC(s);
        if ((s8)p->m7a == 3) {
            fn_80252850(3, lbl_804CD380);
        } else {
            p->m7a = fn_80251838(3, s, lbl_804CD380);
        }
    }
}

void fn_800AE61C(Battle* p) {
    int v = (s8)p->m7a;
    if (v >= 0) {
        fn_80252738(v, lbl_804CD384);
    }
}

void fn_800AE634(Battle* p) {
    fn_800C835C(3, p->m7c);
}

void* fn_800AE644(void* parent) {
    return fn_80081194(lbl_8038224C, parent);
}

BOOL fn_800AE654() {
    return fn_80083B84(lbl_8038224C) != NULL;
}

void fn_800AE688(void* p) {
    fn_80134DB0();
    fn_80062598(lbl_803CAB38, p);
    fn_8012D78C();
}

void fn_800AE6C8() {
    fn_80062380(lbl_803CAB38, lbl_803CAB38 + 0x914);
    fn_80134E30();
    fn_80062454(lbl_803CAB38);
    fn_801314E0();
    fn_8012D620();
    fn_8012D908();
}

void fn_800AE714() {
    fn_80068AFC(1000);
    if (lbl_803C8E80.m1600 != NULL) {
        fn_80068A6C(1000);
    }
}

void fn_800AE754() {
    if (lbl_803C8E80.m1600 != NULL) {
        fn_80068AB4(1000);
    }
}


void fn_800AE88C(void* p) {
    if (lbl_803C8E80.flags & 0x00200000) {
        fn_8009E554(lbl_80365488 + 0x236, p);
    }
}

void fn_800AE8B8(void* p) {
    if (lbl_803C8E80.flags & 0x00200000) {
        fn_8009E554(lbl_80365488 + 0x249, p);
    }
}

void* fn_800AE8E4(void* parent) {
    return fn_80081194(lbl_80382440, parent);
}

int fn_800AE8F4(void* p, const char* name) {
    if (name == NULL) {
        return 0;
    }
    return fn_800AE940(p, fn_800A7C28(name));
}

struct Vec {
    f32 x, y, z;
};

struct Sub40 {
    u8 pad[0x30];
    u8 m30;
    u8 pad31[3];
    Vec m34;
};

struct PicP {
    u8 pad[0x30];
    u8 m30;
    u8 pad31[3];
    f32 m34;
    void* m38;
    void* m3c;
    Sub40* m40;
    void* m44;
};

void fn_800AEBD4(PicP* p) {
    if (p->m3c != NULL) {
        fn_80011CBC(fn_80006EE0, p->m3c);
        if (p->m38 != NULL) {
            fn_80011CBC(fn_8023F1A8, p->m38);
        }
        p->m3c = NULL;
        p->m38 = NULL;
        if (p->m40 != NULL) {
            fn_80081A90(p->m40);
            p->m40 = NULL;
        }
    }
}

void fn_800AEC54(PicP* p) {
    Sub40* s = p->m40;
    p->m30 = 1;
    if (s != NULL) {
        s->m30 = 1;
    }
}

void fn_800AEC70(PicP* p) {
    Sub40* s = p->m40;
    p->m30 = 0;
    if (s != NULL) {
        s->m30 = 0;
    }
}

void fn_800AF054(PicP* p) {
    p->m30 = 1;
    p->m38 = NULL;
    p->m3c = NULL;
    p->m40 = NULL;
    p->m34 = lbl_804CD3AC;
}

void fn_800AEEFC(PicP* p);

void fn_800AF078(PicP* p) {
    fn_800AEEFC(p);
}

void fn_800AF07C(PicP* p) {
    p->m30 = 0;
    if (p->m3c != NULL) {
        fn_80011CBC(fn_80006EE0, p->m3c);
        if (p->m38 != NULL) {
            fn_80011CBC(fn_8023F1A8, p->m38);
        }
        p->m3c = NULL;
        p->m38 = NULL;
        if (p->m40 != NULL) {
            fn_80081A90(p->m40);
            p->m40 = NULL;
        }
    }
}

void* fn_800AF104(void* parent) {
    return fn_80081050(lbl_803824E0, parent);
}

void* fn_800AF114() {
    return fn_80083B84(lbl_803824E0);
}

void fn_800AF120(PicP* p) {
    p->m44 = NULL;
}

} // extern "C"
