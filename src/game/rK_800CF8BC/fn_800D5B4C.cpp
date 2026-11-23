#include "game/rK_800CF8BC/types.h"
#include "game/rH_80112B48/map.h"

#pragma use_lmw_stmw on

extern Map lbl_803EC898;
extern char lbl_8036651C[];
extern u8 lbl_803CAB38[];
extern s8 lbl_804CB742;
extern u8 lbl_803C8E80[];
extern u8 lbl_804CB838;
extern u8 lbl_80383FB8[];
extern u8 lbl_80383FD8[];

struct Actor {
    u8 pad0[4];
    Vec pos;     /* 0x04 */
    u8 pad10[0x18];
    u8 o28[0xC4 - 0x28];
    s16 hC4;     /* 0xC4 */
    u8 padC6[0xD8 - 0xC6];
    s8 bD8;      /* 0xD8 */
    u8 padD9[0x102 - 0xD9];
    s8 x;        /* 0x102 */
    s8 y;        /* 0x103 */
};

struct BUnit {
    u8 pad0[0x48];
    const char* o48;
    u8 pad4C[0x102 - 0x4C];
    s8 x;        /* 0x102 */
    s8 y;        /* 0x103 */
    u8 pad104[0x3F0 - 0x104];
    Actor* actor; /* 0x3F0 */
};

struct Sel {
    BUnit* u;
    u8 pad4[2];
    s16 x6;
    u8 pad8[0x10];
    s16 h18;
};

static inline Actor* SelActor(Sel* s) {
    if (s->u) {
        return s->u->actor;
    }
    return 0;
}

struct Bat {
    u8 b0;
    u8 b1;    /* 0x01 */
    s16 h2;   /* 0x02 */
    u8 pad4[5];
    u8 b9;    /* 0x09 */
};

struct BatEntry {
    u8 pad[0x10];
    void* o10;
    const char* o14;
};

struct CamB {
    u8 pad0[8];
    f32 f8;  /* 0x08 */
    u8 padC[0x1C - 0xC];
    int o1C; /* 0x1C */
    u8 pad20[0x68 - 0x20];
    f32 f68; /* 0x68 */
};
class Cam : public CamB {
public:
    virtual void v08(Vec);
};

struct CamProc {
    u8 proc[0x30];
    f32 f30;
    u8 pad34[0x60 - 0x34];
    int o60;
};

struct SaveProc {
    u8 proc[0x30];
    int n;
    Actor* a[3];
};

struct Color {
    u8 r, g, b, a;
};

struct RingProc {
    u8 proc[0x30];
    int cx;
    int cy;
    int r;
    int t;
    int d;
    Color col;
};

struct Glob {
    u8 pad0[0x3F0];
    u32 u3F0;
    u8 pad3F4[0x48B - 0x3F4];
    u8 b48B;
    u8 pad48C[0x890 - 0x48C];
    u32 u890;
    u8 pad894[0x15EC - 0x894];
    u32 fl;
    u32 u15F0;
    u32 u15F4;
};

extern "C" {
void fn_8013E7FC();
void fn_80021BA4(int, int, int, int);
f32 fn_8001EF44(int, int, f32, f32);
int fn_8028DB44(int);
int fn_80117A0C(Map*, int, int);
u8** fn_801181E8(Map*, int, int);
void fn_8013EE5C(int, int, Color);
void fn_80011838(int);
void fn_800106AC(int, void*, void*);
void fn_80083B78(void*);
void* fn_80083B84(u8*);
#if TARGET_PC
FE10_PROTO void fn_8010301C(p32arg, p32arg, int, int, p32arg);
#else
void fn_8010301C(u32, u32, int, int, void*);
#endif
void* fn_800E3A10(const char*, void*);
#if TARGET_PC
FE10_PROTO void fn_800E5884(void*, p32arg, p32arg);
#else
void fn_800E5884(void*, u32, u32);
#endif
const char* fn_800D0864(const char*);
int fn_8013B9B0();
void fn_801CE2F4(const char*, int, int);
void fn_8009F630(void*);
f32 fn_801142F0(Map*, f32, f32);
Vec fn_800F7790(Actor*);
#if TARGET_PC
FE10_PROTO void fn_80011B90(p32arg, Vec*, Vec*);
#else
void fn_80011B90(int, Vec*, Vec*);
#endif
int fn_80008C98(void*, int);
void* fn_800E45B0(int);
int fn_800E46C4(void*, int);
void fn_800F3F30(Actor*, int);
void fn_800F3F1C(Actor*, int);
void* fn_801CE474(Sel*);
int fn_800F002C(void*, int);
Sel* fn_801D07A4(Bat*);
int fn_801D04D0(Bat*);
Sel* fn_801D0784(Bat*, int);
Sel* fn_801D07D8(Bat*);
int fn_801CFA90(Bat*);
BatEntry* fn_801CFF0C(Bat*, int);
int fn_801CFB7C(Bat*);
int fn_801CFED8(Bat*, int);
int fn_801CFCE0(Bat*);
u8** fn_800F43F0(Actor*);
int fn_801D049C(Bat*);
void fn_800620A8(void*, f32, f32);
void fn_800F001C();
void fn_800EE77C();
void fn_800F6604(Actor*, const char*);
void fn_801D0518(void*, void*);
void fn_801CEC98(Bat*);
void fn_800E24F8(const char*);
int fn_801CEAE0(Bat*);
void* fn_800E28AC(void*, int);
Cam* fn_8012FCD0();
void fn_8012F5CC(Cam*, int);
void fn_8012FCC0();
void fn_8012FCB0();
Bat* fn_801CE7F4();
void fn_80081050(u8*, void*);
void fn_800846BC(u8*);
void* fn_80010BB0(int);
void fn_80010C38(void*, void*);
void fn_80010C20(void*);
void* fn_80068DE4();
void fn_8017EA78(int, int, int, int, int, void*);
void fn_8017F194(int, int, int, void*);

#pragma push
#pragma inline_max_size(1000)
Vec fn_800D5B4C(Sel* s) {
    Vec v = {0.0f, 0.0f, 0.0f};
    BUnit* u = s->u;
    Actor* a = u ? u->actor : 0;
    if (a) {
        f32 ax;
        f32 ay;
        f32 az;
        ax = a->pos.x;
        ay = a->pos.y;
        az = a->pos.z;
        v.x = ax;
        v.y = ay;
        v.z = az;
    } else if (u) {
        v.x = 0.5f + u->x;
        v.y = 0.5f + u->y;
        v.z = fn_801142F0(&lbl_803EC898, v.x, v.y);
    }
    return v;
}

Vec fn_800D5C44(Sel* s);

Vec fn_800D5DC4(Sel* s);
#pragma pop

f32 fn_800D5F6C(Sel* s) {
    Actor* a = SelActor(s);
    if (a) {
        return 0.015625f * a->hC4;
    }
    return 0.0f;
}

int fn_800D5FC8(Sel* s) {
    if (fn_80008C98(SelActor(s)->o28, 0)) {
        return 1;
    }
    {
        void* t = fn_800E45B0(1);
        if (t && fn_800E46C4(t, 0)) {
            return 1;
        }
    }
    return 0;
}

int fn_800D6044(Sel* s) {
    if (fn_80008C98(SelActor(s)->o28, 1)) {
        return 1;
    }
    {
        void* t = fn_800E45B0(1);
        if (t && fn_800E46C4(t, 1)) {
            return 1;
        }
    }
    return 0;
}

int fn_800D60C0(Sel* s) {
    if (fn_80008C98(SelActor(s)->o28, 2)) {
        return 1;
    }
    return 0;
}

int fn_800D6114(Sel* s, int k) {
    if (fn_80008C98(SelActor(s)->o28, k)) {
        return 1;
    }
    return 0;
}

void* fn_800D6164() { return fn_800E45B0(1); }

void fn_800D616C(Sel* s) {
    Actor* a = SelActor(s);
    if (a) {
        fn_800F3F30(a, s->h18);
    }
}

void fn_800D619C(Sel* s, int k) {
    Actor* a = SelActor(s);
    if (a) {
        s->h18 = a->bD8;
        fn_800F3F30(a, fn_800F002C(fn_801CE474(s), k));
    } else {
        s->h18 = -1;
    }
}

static inline Sel* BatTarget(Bat* b) {
    Sel* s;
    if (fn_801D04D0(b)) {
        s = fn_801D0784(b, 1);
    } else {
        s = fn_801D07D8(b);
        if (s == 0 || SelActor(s) == 0) {
            s = fn_801D07A4(b);
        }
    }
    return s;
}

const char* fn_800D621C(Bat* b) {
    Sel* atk = fn_801D07A4(b);
    Sel* tgt = BatTarget(b);
    Actor* a;
    if (tgt) {
        a = SelActor(tgt);
    } else {
        a = 0;
    }
    if (fn_801CFA90(b)) {
        BatEntry* e = fn_801CFF0C(b, fn_801CFA90(b));
        if (e) {
            const char* s = e->o14;
            if (s) {
                return s;
            }
        }
    }
    if (fn_801CFB7C(b)) {
        BatEntry* e = fn_801CFF0C(b, fn_801CFB7C(b));
        if (e) {
            const char* s = e->o14;
            if (s) {
                return s;
            }
        }
    }
    if (fn_801CFED8(b, 0x7E)) {
        return lbl_8036651C;
    }
    switch (b->h2) {
    case 0x6E:
    case 0x6F:
        if (fn_801CFCE0(b)) {
            return lbl_8036651C + 0xD;
        }
        break;
    case 0x70:
        if (a && (((u8*)fn_800F43F0(a)[4])[0x10] & 2)) {
            return lbl_8036651C + 0xD;
        }
        break;
    }
    {
        Sel* q = (Sel*)fn_801CE474(atk);
        switch (b->b1) {
        case 1:
        case 3:
        case 4:
        case 5:
        case 7:
            if (q) {
                BUnit* u = q->u;
                const char* s = u ? u->o48 : 0;
                if (s) {
                    return u ? u->o48 : 0;
                }
            }
            switch (b->h2) {
            case 0x6F:
                return lbl_8036651C + 0x17;
            case 0x6E:
                if (fn_801D049C(b) > 1) {
                    return lbl_8036651C + 0x21;
                }
                return lbl_8036651C + 0x2B;
            }
            break;
        case 0:
        case 2:
        case 6:
            break;
        }
    }
    return 0;
}

BatEntry* fn_800D64B0Inner(Bat* b, int k);

void* fn_800D64B0(Bat* b, int k) {
    BatEntry* e = fn_801CFF0C(b, k);
    if (e) {
        return e->o10;
    }
    return 0;
}

void fn_800D64E4(Bat* b) {
    int n = 0;
    int i = 0;
    f32 x = 0.0f;
    f32 y = x;
    for (; i < 3; i++) {
        Actor* a = SelActor(fn_801D0784(b, i));
        if (a) {
            n++;
            x += a->x;
            y += a->y;
        }
    }
    if (n > 0) {
        x /= n;
        y /= n;
        fn_800620A8(lbl_803CAB38, x, y);
    }
}

void fn_800D6624(Bat* b) {
    Actor* a0;
    Actor* a1;
    Actor* a2;
    fn_800F001C();
    fn_800EE77C();
    a0 = SelActor(fn_801D0784(b, 0));
    a1 = SelActor(fn_801D0784(b, 1));
    a2 = SelActor(fn_801D0784(b, 2));
    if (a0) {
        fn_800F6604(a0, lbl_8036651C + 0x35);
    }
    if (a1) {
        fn_800F6604(a1, lbl_8036651C + 0x35);
    }
    if (a2) {
        fn_800F6604(a2, lbl_8036651C + 0x35);
    }
}

void fn_800D6724(Bat* b) {
    u8 save[0xC0];
    fn_801D0518(save, b);
    do {
        fn_801CEC98(b);
        {
            const char* s = fn_800D621C(b);
            if (s) {
                fn_800E24F8(s);
            }
        }
    } while (b->b9 && fn_801CEAE0(b));
    fn_801D0518(b, save);
}

void fn_800D679C(Bat* b) {
    Sel* s = fn_801D07A4(b);
    if (s) {
        switch (b->b1) {
        case 2: {
            void* p = fn_800E28AC(fn_801CE474(s), 0);
            if (p) {
                fn_800E24F8((const char*)p);
            }
        }
        case 3:
        case 4:
        case 6: {
            void* p = fn_800E28AC(fn_801CE474(s), 1);
            if (p) {
                fn_800E24F8((const char*)p);
            }
            break;
        }
        case 5:
            break;
        }
    }
}

Sel* fn_800D683C(Bat* b) { return fn_801D07A4(b); }

Sel* fn_800D6840(Bat* b) { return BatTarget(b); }

Bat* fn_800D68BC() { return fn_801CE7F4(); }

static inline void CamV(Cam* c, Vec a) { c->v08(a); }

void fn_800D68C0(CamProc* p);

void fn_800D6950(CamProc* p) {
    Bat* b = fn_801CE7F4();
    Cam* c = fn_8012FCD0();
    int lv;
    p->f30 = c->f8;
    p->o60 = c->o1C;
    if (c->f8 < 30.0f) {
        c->f8 = 40.0f;
    }
    lv = -1;
    if (*(u32*)(lbl_803C8E80 + 0x15EC) & 0x20000) {
        lv = 2;
    } else {
        if (fn_801D049C(b) >= 5) {
            lv = 1;
        }
        if (fn_801D049C(b) >= 10) {
            lv = 2;
        }
    }
    if (lv >= 0) {
        if (c->o1C < lv) {
            fn_8012F5CC(c, lv);
        }
        fn_800D64E4(b);
    }
    c->f68 = 3.0f;
    fn_8012FCB0();
    lbl_804CB742 = -8;
}

void fn_800D6A44(void* parent) {
    if (!(lbl_804CB838 & 2)) {
        fn_80081050(lbl_80383FB8, parent);
    }
}

void fn_800D6A64() { fn_800846BC(lbl_80383FB8); }

void fn_800D6A70(SaveProc* p) {
    void* a = fn_80010BB0(1);
    void* c = fn_80010BB0(2);
    Bat* b;
    int i;
    fn_80010C38(a, c);
    fn_80010C20(c);
    b = fn_801CE7F4();
    p->n = 0;
    for (i = 0; i < 3; i++) {
        Actor* x = SelActor(fn_801D0784(b, i));
        if (x) {
            fn_800F3F1C(x, 2);
            p->a[p->n++] = x;
        }
    }
}

void fn_800D6B4C(SaveProc* p) {
    int i;
    Actor** q;
    for (i = 0; i < p->n; i++) {
        fn_800F3F1C(p->a[i], 1);
    }
    fn_80010C20(0);
    {
        void* t = fn_80068DE4();
        fn_8017EA78(0, 0x64, 0x64, 0, 0, t);
        fn_8017EA78(1, 0x64, 0x64, 0, 0, t);
        fn_8017EA78(2, 0x64, 0x64, 0, 0, t);
        fn_8017F194(0x64, 0x64, 0, t);
    }
}

void fn_800D6C28(void* parent) { fn_80081050(lbl_80383FD8, parent); }

void fn_800D6C38() { fn_800846BC(lbl_80383FD8); }

void fn_800D6C44(int a, int b, int c) {
    if (fn_80083B84(lbl_80383FD8)) {
        void* t = fn_80068DE4();
        fn_8017EA78(0, a, a, b, c, t);
        fn_8017EA78(1, a, a, b, c, t);
        fn_8017EA78(2, a, 0x64, b, c, t);
        fn_8017F194(a, b, c, t);
    }
}

#pragma use_lmw_stmw off
void fn_800D6D10(RingProc* p);
#pragma use_lmw_stmw on

void fn_800D6E78(RingProc* p) { p->t = 0; }

void fn_800D6E84(RingProc* p) {
    p->t++;
    fn_800106AC(3, fn_800D6D10, p);
    if (p->t >= p->d) {
        fn_80083B78(p);
    }
}

static inline void ChatMsg(Glob* g, const char* s) {
    if (g) {
        int t = fn_8013B9B0();
        if (g->b48B) {
            fn_801CE2F4(s, 9, t);
        } else {
            fn_801CE2F4(s, 10, t);
        }
    }
}

int fn_800D70F4(void* p);
}
