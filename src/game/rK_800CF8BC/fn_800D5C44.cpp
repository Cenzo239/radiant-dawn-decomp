/* fn_800D5C44: exact (round m10). Position of a selection: the actor's own position call, else the inlined
 * fn_800D5B4C. Lever: in the inline copy of fn_800D5B4C the three float temporaries are declared az, ay, ax
 * (reversed against the stand-alone function): inside an inline the last-declared local takes the lowest
 * float register, which gives lfs f0,f1,f2. Helpers from fn_800D5B4C.cpp (exported bodies removed). */
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
void fn_8010301C(u32, u32, int, int, void*);
void* fn_800E3A10(const char*, void*);
void fn_800E5884(void*, u32, u32);
const char* fn_800D0864(const char*);
int fn_8013B9B0();
void fn_801CE2F4(const char*, int, int);
void fn_8009F630(void*);
f32 fn_801142F0(Map*, f32, f32);
Vec fn_800F7790(Actor*);
void fn_80011B90(int, Vec*, Vec*);
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

/* Local inline copy of fn_800D5B4C_i (matched elsewhere): the original inlines it here. */
static inline Vec fn_800D5B4C_i(Sel* s){
    Vec v = {0.0f, 0.0f, 0.0f};
    BUnit* u = s->u;
    Actor* a = SelActor(s);
    if (a) {
        f32 az;
        f32 ay;
        f32 ax;
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

f32 fn_800D5F6C(Sel* s);

int fn_800D5FC8(Sel* s);

int fn_800D6044(Sel* s);

int fn_800D60C0(Sel* s);

int fn_800D6114(Sel* s, int k);

void* fn_800D6164();

void fn_800D616C(Sel* s);

void fn_800D619C(Sel* s, int k);


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
const char* fn_800D621C(Bat* b);


BatEntry* fn_800D64B0Inner(Bat* b, int k);
void* fn_800D64B0(Bat* b, int k);

void fn_800D64E4(Bat* b);

void fn_800D6624(Bat* b);

void fn_800D6724(Bat* b);

void fn_800D679C(Bat* b);

Sel* fn_800D683C(Bat* b);

Sel* fn_800D6840(Bat* b);

Bat* fn_800D68BC();


static inline void CamV(Cam* c, Vec a) { c->v08(a); }

void fn_800D68C0(CamProc* p);
void fn_800D6950(CamProc* p);

void fn_800D6A44(void* parent);

void fn_800D6A64();

void fn_800D6A70(SaveProc* p);

void fn_800D6B4C(SaveProc* p);

void fn_800D6C28(void* parent);

void fn_800D6C38();

void fn_800D6C44(int a, int b, int c);


#pragma use_lmw_stmw off
void fn_800D6D10(RingProc* p);
#pragma use_lmw_stmw on

void fn_800D6E78(RingProc* p);

void fn_800D6E84(RingProc* p);


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

extern "C" {
Vec fn_800D5C44(Sel* s) {
    Vec v = {0.0f, 0.0f, 0.0f};
    Actor* a = SelActor(s);
    if (a) {
        v = fn_800F7790(a);
    } else {
        v = fn_800D5B4C_i(s);
    }
    return v;
}
}
