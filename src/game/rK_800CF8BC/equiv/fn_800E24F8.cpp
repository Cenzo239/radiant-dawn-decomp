/* fn_800E24F8: functionally equal (renamed, 27 of 141 words differ in registers only). Helpers from fn_800E1E00.cpp (exported bodies removed), body from wip/fn_800E1E00.cpp with the two name buffers declared in the original stack order. */
/* Model processes: load and release of the files behind a character model
 * (.cmp, .gs, .g, .ga, .tpl), language suffixes, event hooks in the animation. */
#include "game/rK_800CF8BC/types.h"

#pragma pool_strings on

/* Sets the string pool at lbl_80366F40 in its original order. */
const char* sPool[16];
void poolOrder() {
    sPool[0] = "%s%s.cmp";
    sPool[1] = "yme/";
    sPool[2] = "%s%s.gs";
    sPool[3] = "%s%s.g";
    sPool[4] = "%s%s.ga";
    sPool[5] = "%s%s.tpl";
    sPool[6] = "_J";
    sPool[7] = "_E";
    sPool[8] = "_G";
    sPool[9] = "_F";
    sPool[10] = "_S";
    sPool[11] = "_I";
    sPool[12] = "_D";
    sPool[13] = "quake";
    sPool[14] = "";
}

struct ModelDef {
    u8 pad0[4];
    const char* name; /* 0x04 */
    u16 flags;        /* 0x08 */
    u8 padA[3];
    u8 xD;            /* 0x0D */
    u8 xE;            /* 0x0E */
    u8 xF;            /* 0x0F */
    s16 sub10;        /* 0x10 */
    s16 sub12;        /* 0x12 */
    void* snd;        /* 0x14 */
};
struct SubEntry {
    u8 pad[4];
    const char* name;
};
class Voice {
public:
    virtual void v08();
    virtual void v0C();
    virtual int active();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void stop(int);
    struct Sd { const char* name; };
    u8 pad4[8];
    Sd* sd; /* 0x0C */
};
struct WaitProc {
    u8 pad[0x30];
    int n30; /* 0x30 */
    int n34; /* 0x34 */
    int t38; /* 0x38 */
};
struct Mtx34 {
    f32 m[12];
};
struct AnimHost {
    u32 f0;
    u8 pad4[0xC];
    Mtx34 o10;
    u8 pad40[4];
    void* o44;
    u8 pad48[0x10];
    f32 x58;
};
struct AnimNode {
    u8 pad[0xC];
    u32 flags;
};
struct Cam {
    u8 pad[0x6C];
};
struct CamB {
    u8 pad[0x6C];
};
class CamH : public CamB {
public:
    virtual void v08(Vec*);
};
struct Colr {
    u8 r, g, b, a;
};
struct ModelProc;
struct ModelData {
    AnimHost* h;  /* 0x00 */
    u16 x4;       /* 0x04 */
    u16 x6;       /* 0x06 */
    s16 x8;       /* 0x08 */
    u8 padA;
    u8 xB;        /* 0x0B */
    u8 xC;        /* 0x0C */
    s8 xD;        /* 0x0D */
    u8 xE;        /* 0x0E */
    u8 xF;        /* 0x0F */
    u8 x10;       /* 0x10 */
    u8 x11;       /* 0x11 */
    u8 x12;       /* 0x12 */
    s8 x13;       /* 0x13 */
    u8 pad14[4];
    u32 flags;    /* 0x18 */
    Vec pos;      /* 0x1C */
    f32 v28[3];   /* 0x28 */
    f32 v34[3];   /* 0x34 */
    f32 rx, ry, rz; /* 0x40 */
    Vec scale;    /* 0x4C */
    Vec vel;      /* 0x58 */
    Colr col;     /* 0x64 */
    f32 m68[12];  /* 0x68 */
    void (*cb98)(ModelProc*); /* 0x98 */
    void (*cb9C)(ModelProc*); /* 0x9C */
    u32 xA0;      /* 0xA0 */
    u32 xA4[8];   /* 0xA4 */
    ModelDef* def;/* 0xC4 */
};
struct ModelProc {
    void* cls;
    u8 pad4[0x14];
    ModelProc* parent; /* 0x18 */
    ModelProc* child;  /* 0x1C */
    u8 pad20[4];
    ModelProc* next;   /* 0x24 */
    u8 pad28[8];
    ModelData* d;      /* 0x30 */
};
struct SndLoad {
    u8 pad[0x10];
    void* parent;
};
struct KeyEntry {
    u16 key;
    s16 val;
};
struct KeyList {
    u16 frame;
    u8 pad2;
    u8 n;
    KeyEntry e[1];
};

extern char lbl_803842E8[];
extern char lbl_803842F4[];
extern u8 lbl_80384218[];
extern u32 lbl_804CB5F4;
extern u8 lbl_80384278[];
extern u8 lbl_803842C8[];
extern u8 lbl_803EC898[];

extern "C" {
Voice* fn_8024F50C(s8);
char* fn_80291480(const char*, const char*);
void fn_802573EC();
void fn_80083B78(void*);
int fn_80290DDC(char*, const char*, ...);
int fn_8023F9F4(const char*);
void* fn_8023F1A4(const char*, int);
void fn_8023F1A0(const char*, int);
void fn_80009214(void*, const char*, int);
void fn_80009274(void*, const char*, int);
void fn_80009150(void*, const char*, int);
void fn_800092D4(void*, const char*, int);
int fn_8023F838(const char*);
int fn_8023F880(const char*);
void fn_80006F20(void*);
void fn_80006EE0(void*);
void fn_8023F4EC(const char*);
s8 fn_80244D88();
char* strcpy(char*, const char*);
void fn_80291110(char*, const char*);
ModelDef* fn_80076F54(const char*);
int fn_800E21D0(ModelDef*);
char* fn_800E22F8(ModelDef*, char*);
void fn_800E24F8(const char*);
int fn_80007630(void*, const char*);
AnimNode* fn_800078E4(void*, int);
Vec fn_800076E8(void*, int);
void fn_8001E9E4(void*, Vec*);
void fn_80313484(const Vec*, const Vec*, Vec*);
f32 fn_80313508(const Vec*);
SndLoad* fn_8013B9A8();
int fn_802578F0();
void fn_800846BC(void*);
WaitProc* fn_80083B84(void*);
void* fn_80081050(void*, void*);
int fn_80257520(void*);
void fn_80257340(void*, int);
int fn_80257628(void*);
SubEntry* fn_8010AF20(int);
CamH* fn_8012FCD0();
void fn_8012F5CC(void*, int);
int fn_80008EB4(void*);
int fn_80008C98(void*, int);
int fn_80008CF0(void*, int);
void fn_800F15AC(void*, f32, f32, f32);
void fn_800F172C(void*, Vec*);
void fn_800F199C(void*, void*);
void fn_800F1C30(void*, int, void*);
void fn_800F1E9C(void*, void*);
void fn_800F1F88(void*);
void* fn_80007F10(void*);
int fn_80009E20(void*, KeyList**);
void fn_8000866C(void*, f32);
void* fn_80006E1C(void*);
void fn_80083DC4(void*, int);
void fn_80008F54(void*, int);
void fn_800088A0(void*, f32);
u32 fn_80089ED0();
void fn_800096E4(void*, int);
void* fn_80081194(void*, void*);
void* fn_80078CCC(int, const char*, int);
void fn_800E4768(ModelData*, const char*);
void fn_8017C2F4(void*);
void fn_8017D9B4(void*, void*);
void fn_8023FAF0(const char*);
void fn_8017C3B0(void*);
void fn_80078E24(void*);
u32 fn_8017FA1C();
void fn_800081D4(void*);
void fn_80017DF0(void*);
f32 fn_8001EF30(f32, f32, f32, f32);
void fn_80008F10(void*, int, int, int);
void fn_80008F20(void*, u8);
void fn_80009A2C(void*);
void fn_80007C58(void*);
void fn_800E4C14(ModelProc*);
void fn_800E2A78(ModelProc*);
void fn_8017C40C(void*);
void fn_8017D17C(void*);
void fn_80312318(Mtx34*);
void fn_80312344(const Mtx34*, Mtx34*);
void fn_80312378(const Mtx34*, const Mtx34*, Mtx34*);
void fn_8031292C(Mtx34*, f32, f32, f32);
void fn_803128AC(Mtx34*, f32, f32, f32);
void fn_80313460(const Vec*, const Vec*, Vec*);
void fn_803134A8(const Vec*, Vec*, f32);
void fn_80011B90(int, Vec*, Vec*);
void fn_80118B20(void*, f32, f32, Mtx34*, int, int);
void fn_8001D748(Mtx34*, int, f32, f32, f32);
int fn_800D44EC();
int fn_801D09F0();
f32 fn_80113F00(void*, f32, f32);
Vec fn_800F7790(void*);
f32 fn_80176A4C(f32, f32, f32, f32);
f32 fn_80176B0C(f32, f32, f32, f32);
int fn_80008C98(void*, int);
int fn_80008E88(void*, int, int);
void* fn_80076F60(const char*);

#pragma use_lmw_stmw on

void fn_800E1E00(WaitProc* p);

#pragma use_lmw_stmw off

void fn_800E1EC0(WaitProc* p);

void* fn_800E1FE0(ModelDef* m, void* h);


static inline void cmpPath(char* path, ModelDef* m) {
    char name[0x40];
    fn_80290DDC(path, "%s%s.cmp", "yme/", fn_800E22F8(m, name));
}
void fn_800E2170(ModelDef* m, void* h);

int fn_800E21D0(ModelDef* m);

char* fn_800E22F8(ModelDef* m, char* buf);

Vec fn_800E240C(ModelProc* p);


static inline const char* subName(int k) {
    if (k >= 0) {
        SubEntry* e = fn_8010AF20(k);
        if (e) return e->name;
    }
    return 0;
}

#pragma use_lmw_stmw off

int fn_800E272C(const char* s);


struct Lst {
    u8 pad[0x40];
    void* e[1];
};
struct LstH {
    Lst* l;
};
static inline void* lstAt(Lst* l, int i) {
    if (l) return l->e[i];
    return 0;
}
void* fn_800E28AC(LstH* h, int i);

void fn_800E2A78(ModelProc* p);


static inline void setRx(ModelProc* p, f32 v) {
    ModelData* d;
    ModelDef* def;
    d = p->d;
    def = d->def;
    if (def && (def->flags & 0x10)) {
        u32 r = fn_80089ED0();
        p->d->rx = r % 0x168;
    } else {
        d->rx = v;
    }
}
static inline void setRy(ModelProc* p, f32 v) {
    ModelData* d;
    ModelDef* def;
    d = p->d;
    def = d->def;
    if (def && (def->flags & 0x20)) {
        u32 r = fn_80089ED0();
        p->d->ry = r % 0x168;
    } else {
        d->ry = v;
    }
}
static inline void setRz(ModelProc* p, f32 v) {
    ModelData* d;
    ModelDef* def;
    d = p->d;
    def = d->def;
    if (def && (def->flags & 0x40)) {
        u32 r = fn_80089ED0();
        p->d->rz = r % 0x168;
    } else {
        d->rz = v;
    }
}
static inline void setPos(ModelProc* p, Vec v) {
    p->d->pos.x = v.x;
    p->d->pos.y = v.y;
    p->d->pos.z = v.z;
}
static inline void setScale(ModelProc* p, Vec v) {
    p->d->scale = v;
}
static inline void inherit(ModelProc* c, ModelProc* q) {
    c->d->flags |= q->d->flags & 0x80270F7;
    c->d->flags |= 0x20000000;
    setPos(c, q->d->pos);
    setScale(c, q->d->scale);
    setRx(c, q->d->rx);
    setRy(c, q->d->ry);
    setRz(c, q->d->rz);
    c->d->xE = q->d->xE;
    c->d->xF = q->d->xF;
    c->d->x12 = q->d->x12;
    c->d->x11 = q->d->x11;
    c->d->x13 = q->d->x13;
}
static inline void initAll(ModelProc* p, const char* name) {
    p->d = (ModelData*)fn_80078CCC(0xC8, "", 0);
    fn_800E4768(p->d, name);
    setRx(p, 0.0f);
    setRy(p, 0.0f);
    setRz(p, 0.0f);
    p->d->flags |= 0x8000;
    p->d->flags |= 0x80000000;
}
static inline ModelProc* create(const char* name, void* parent) {
    ModelProc* p;
    if (!fn_80076F54(name)) {
        return 0;
    }
    if (!parent) {
        parent = (void*)4;
    }
    p = (ModelProc*)fn_80081050(lbl_80384278, parent);
    initAll(p, name);
    return p;
}
static inline ModelProc* create2(const char* name, void* parent) {
    ModelProc* p;
    if (!fn_80076F54(name)) {
        return 0;
    }
    p = (ModelProc*)fn_80081194(lbl_80384278, parent);
    initAll(p, name);
    return p;
}

struct Rng {
    u8 pad[0x14];
    int a;
    int b;
};
void fn_800E2D8C(ModelProc* p);


static inline ModelProc* firstModel(ModelProc* q) {
    ModelProc* c = q->child;
    while (c) {
        if (c->cls == lbl_80384278) {
            return c;
        }
        c = c->next;
    }
    return 0;
}
int fn_800E369C(ModelProc* q);

void fn_800E36E4(AnimHost** h);

ModelProc* fn_800E3810(const char* name, void* parent);

ModelProc* fn_800E3A10(const char* name, void* parent);

ModelProc* fn_800E3C04(const char* name, void* parent);

ModelProc* fn_800E3E38(const char* name, void* parent);

ModelProc* fn_800E4060(const char* name, void* parent);

ModelProc* fn_800E4278(const char* name, void* parent);

int fn_800E4674(ModelProc* p);


static inline int kInl(ModelProc* p, int key) {
    while (p) {
        AnimHost* h = p->d->h;
        if (h && fn_80008C98(h, key)) {
            return 1;
        }
        p = firstModel(p);
    }
    return 0;
}
int fn_800E46C4(ModelProc* p, int key);


extern Colr lbl_804CD8F8;
static inline void setCol(ModelData* d, Colr c) {
    d->col.r = c.r;
    d->col.g = c.g;
    d->col.b = c.b;
    d->col.a = c.a;
}
void fn_800E4768(ModelData* d, const char* name);

void fn_800E48C8(ModelProc* p, const Vec* v);

void fn_800E4918(ModelProc* p, f32 v);

void fn_800E49AC(ModelProc* p, f32 v);

void fn_800E4A40(ModelProc* p, f32 v);


class VoiceH {
public:
    virtual void v08();
    virtual void kill();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void fade(int);
};

extern int fn_800F14B4(int);
extern VoiceH* fn_8024F704(int);

#pragma use_lmw_stmw on

void fn_800E4B20(ModelProc* p, int n);

#pragma use_lmw_stmw off

extern f32 lbl_804CD91C;
void fn_800E4C14(ModelProc* p);

void fn_800E515C(ModelProc* p);

void fn_800E57B4(ModelProc* p, int x, int y);


extern void fn_800E59CC(ModelProc*, Vec*, Vec*);

struct PosHolder {
    u8 pad[4];
    Vec pos;
};

static inline Vec holderPos(PosHolder* a) {
    return a->pos;
}
void fn_800E5884(ModelProc* p, PosHolder* a, PosHolder* b);

void fn_800E59CC(ModelProc* p, Vec* a, Vec* b);


struct RotProc {
    u8 pad[0x30];
    ModelProc* m;
    f32 ax, ay, az;
    f32 bx, by, bz;
    f32 t4C;
    f32 t50;
};
void fn_800E5BD8(RotProc* e);


static inline void spawnRot(ModelProc* p, int n, Vec b, Vec a) {
    if (n >= 0) {
        RotProc* w = (RotProc*)fn_80081050(lbl_803842C8, p);
        w->ax = b.x;
        w->ay = b.y;
        w->az = b.z;
        w->bx = a.x;
        w->by = a.y;
        w->bz = a.z;
        w->t4C = n;
        w->m = p;
    }
}
void fn_800E5CA8(ModelProc* p);

}

/* ---- from rK_800CF8BC/wip/fn_800E1E00.cpp ---- */
extern "C" {
/* Near misses from fn_800E1E00.cpp. Same declarations as that file.
 * fn_800E24F8: 17 words with the body written in place (see below it is the
 *   wrapper form, 31 words). Only m/mode/snd/base registers rotate: m should sit
 *   in r29 below the lis base (r31), but always lands in r31.
 * fn_800E28E4: 11 words in plain form, 19 with this wrapper. Outer h should be
 *   r30 and the inlined quakeOf h r29; they come out swapped. Writing quakeOf in
 *   place fixes the registers but mirrors the stack slots. */
static inline int openFile(const char* path, int mode) {
    if (fn_8023F9F4(path) == 0x40000) {
        return 0;
    }
    fn_8023F1A0(path, mode);
    return 1;
}

static inline void loadChain(ModelDef* m) {
    /*P*/
    SndLoad* l;
    WaitProc* w;
    void* snd;
    int mode;
/*E*/
    char path[0x40];
    char name[0x40];
    fn_80290DDC(path, "%s%s.cmp", "yme/", fn_800E22F8(m, name));
    mode = 0;
    {
        u16 fl = m->flags;
        if (fl & 0x400) mode = 0x2040;
        if (fl & 0x200) mode = 0x2080;
        if (fl & 0x800) mode |= 0x200;
    }
    if (openFile(path, mode)) {
        snd = m->snd;
        if (snd) {
            l = fn_8013B9A8();
            if (l && l->parent) {
                if (fn_802578F0() >= 0x18) {
                    fn_800846BC(lbl_80384218);
                }
                w = fn_80083B84(lbl_80384218);
                if (!w) {
                    w = (WaitProc*)fn_80081050(lbl_80384218, l->parent);
                }
                if (!fn_80257520(snd)) {
                    fn_80257340(snd, 0x10000);
                    w->n34++;
                }
                w->n30++;
                w->t38 = 0;
            }
            {
                WaitProc* w2 = fn_80083B84(lbl_80384218);
                if (w2) {
                    w2->n30--;
                    w2->t38 = 0;
                }
            }
        }
        if (subName(m->sub10)) {
            fn_800E24F8(subName(m->sub10));
        }
        if (subName(m->sub12)) {
            fn_800E24F8(subName(m->sub12));
        }
    }
}

#pragma use_lmw_stmw on
#pragma push
#pragma auto_inline off
void fn_800E24F8(const char* s) {
    if (s) {
        ModelDef* m = fn_80076F54(s);
        if (m) {
            loadChain(m);
        }
    }
}
#pragma pop
#pragma use_lmw_stmw off

}
