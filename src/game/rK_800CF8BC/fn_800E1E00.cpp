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
#if TARGET_PC
FE10_PROTO void fn_80011B90(p32arg, Vec*, Vec*);
#else
void fn_80011B90(int, Vec*, Vec*);
#endif
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
void fn_800E1E00(WaitProc* p) {
    /*P*/
    int i;
    Voice* v;
    int j;
    const char* s;
/*E*/
    for (i = 0; i < 16; i++) {
        v = fn_8024F50C(i);
        if (v && v->active() && v->sd) {
            s = v->sd->name;
            if (fn_80291480(s, lbl_803842F4) == s) {
                v->stop(0);
            }
        }
    }
    for (j = 0; j < p->n34; j++) {
        fn_802573EC();
    }
}
#pragma use_lmw_stmw off

void fn_800E1EC0(WaitProc* p) {
    /*P*/
    int i;
    Voice* v;
    const char* s;
    int f;
/*E*/
    if (p->n30 <= 0) {
        for (i = 0; i < 16; i++) {
            v = fn_8024F50C(i);
            if (v && v->active() && v->sd) {
                s = v->sd->name;
                if (fn_80291480(s, lbl_803842E8) == s) {
                    f = 1;
                    goto done;
                }
            }
        }
        f = 0;
    done:
        if (!f) {
            if ((p->t38 = p->t38 + 1) >= 0x708) {
                fn_80083B78(p);
            }
        }
    }
}

void* fn_800E1FE0(ModelDef* m, void* h) {
    char path[0x40];
    char sub[0x40];
    char name[0x40];
    int mode;
    void* r;
    fn_80290DDC(path, "%s%s.cmp", "yme/", fn_800E22F8(m, name));
    fn_800E22F8(m, sub);
    mode = 0;
    {
        u16 fl = m->flags;
        if (fl & 0x400) mode = 0x2040;
        if (fl & 0x200) mode = 0x2080;
        if (fl & 0x800) mode |= 0x200;
    }
    if (fn_8023F9F4(path) == 0x40000) {
        return 0;
    }
    r = fn_8023F1A4(path, mode);
    fn_80290DDC(path, "%s%s.gs", "yme/", sub);
    fn_80009214(h, path, mode);
    fn_80290DDC(path, "%s%s.g", "yme/", sub);
    fn_80009274(h, path, mode);
    fn_80290DDC(path, "%s%s.ga", "yme/", sub);
    fn_80009150(h, path, mode);
    fn_80290DDC(path, "%s%s.tpl", "yme/", sub);
    if (fn_8023F838(path)) {
        fn_800092D4(h, path, mode);
    }
    fn_80006F20(h);
    return r;
}

static inline void cmpPath(char* path, ModelDef* m) {
    char name[0x40];
    fn_80290DDC(path, "%s%s.cmp", "yme/", fn_800E22F8(m, name));
}

void fn_800E2170(ModelDef* m, void* h) {
    char path[0x40];
    fn_80006EE0(h);
    cmpPath(path, m);
    fn_8023F4EC(path);
}

int fn_800E21D0(ModelDef* m) {
    if (m->flags & 0x1000) {
        int lang;
        char buf[0x40];
        lang = (s8)fn_80244D88();
        strcpy(buf, m->name);
        switch (lang) {
        case 0: fn_80291110(buf, "_J"); break;
        case 1: fn_80291110(buf, "_E"); break;
        case 2: fn_80291110(buf, "_G"); break;
        case 3: fn_80291110(buf, "_F"); break;
        case 4: fn_80291110(buf, "_S"); break;
        case 5: fn_80291110(buf, "_I"); break;
        case 6: fn_80291110(buf, "_D"); break;
        }
        if (fn_80076F54(buf)) {
            return lang;
        }
    }
    return -1;
}

char* fn_800E22F8(ModelDef* m, char* buf) {
    strcpy(buf, m->name);
    switch (fn_800E21D0(m)) {
    case 0: fn_80291110(buf, "_J"); break;
    case 1: fn_80291110(buf, "_E"); break;
    case 2: fn_80291110(buf, "_G"); break;
    case 3: fn_80291110(buf, "_F"); break;
    case 4: fn_80291110(buf, "_S"); break;
    case 5: fn_80291110(buf, "_I"); break;
    case 6: fn_80291110(buf, "_D"); break;
    }
    return buf;
}

Vec fn_800E240C(ModelProc* p) {
    Vec r = {0.0f, 0.0f, 0.0f};
    AnimHost* h = p->d->h;
    if (h) {
        int i = fn_80007630(h, "quake");
        if (i >= 0) {
            Vec a;
            Vec b;
            fn_800078E4(h, i)->flags |= 0x08000000;
            a = fn_800076E8(h, i);
            fn_8001E9E4(&h->o10, &b);
            fn_80313484(&a, &b, &r);
        }
    }
    return r;
}

static inline const char* subName(int k) {
    if (k >= 0) {
        SubEntry* e = fn_8010AF20(k);
        if (e) return e->name;
    }
    return 0;
}

#pragma use_lmw_stmw off

int fn_800E272C(const char* s) {
    ModelDef* m = fn_80076F54(s);
    char name[0x40];
    char path[0x40];
    void* snd;
    if (!m) {
        return 1;
    }
    fn_80290DDC(path, "%s%s.cmp", "yme/", fn_800E22F8(m, name));
    if (!fn_8023F880(path)) {
        return 0;
    }
    snd = m->snd;
    if (snd && fn_80257520(snd) && !fn_80257628(snd)) {
        return 0;
    }
    if (subName(m->sub10) && !fn_800E272C(subName(m->sub10))) {
        return 0;
    }
    if (subName(m->sub12) && !fn_800E272C(subName(m->sub12))) {
        return 0;
    }
    return 1;
}

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
void* fn_800E28AC(LstH* h, int i) {
    if (h) {
        Lst* l = h->l;
        if (l) return lstAt(l, i);
    }
    return 0;
}

void fn_800E2A78(ModelProc* p) {
    AnimHost* h = p->d->h;
    if (fn_80008EB4(h)) {
        ModelData* d = p->d;
        if (d->x12 == 0) {
            if (d->flags & 8) {
                fn_800F15AC(h, -10000.0f, -10000.0f, -10000.0f);
            } else {
                switch (d->def->flags & 7) {
                case 0: {
                    Vec t = d->pos;
                    fn_800F172C(h, &t);
                    break;
                }
                default:
                    fn_800F15AC(h, -10000.0f, -10000.0f, -10000.0f);
                }
            }
        }
        if (fn_80008C98(h, 0x1C)) {
            lbl_804CB5F4 |= 1;
            p->d->flags |= 0x40000000;
        }
        if (fn_80008C98(h, 0x1D)) {
            lbl_804CB5F4 &= ~1;
            p->d->flags &= ~0x40000000;
        }
        fn_800F199C(h, p);
        fn_800F1C30(h, p->d->xD, p);
        fn_800F1E9C(h, p);
        fn_800F1F88(h);
        if (fn_80008C98(h, 0x1E)) {
            int id = fn_80008CF0(h, 0x1E);
            KeyList* buf[0x40];
            int n = fn_80009E20(fn_80007F10(h), buf);
            KeyList** q = buf;
            int i;
            for (i = 0; i < n; q++, i++) {
                KeyEntry* e;
                KeyList* k;
                int j;
                k = *q;
                e = k->e;
                for (j = 0; j < k->n; j++, e++) {
                    if (e->key == 0x1F && e->val == (s16)id) {
                        fn_8000866C(h, k->frame);
                        break;
                    }
                }
            }
        }
    }
}

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

void fn_800E2D8C(ModelProc* p) {
    /*P*/
    ModelProc* c;
    void* parent;
    const char* cname;
    WaitProc* w;
    SndLoad* l;
    ModelDef* def;
    void* snd;
    AnimHost* h;
    int ga;
    int gb;
/*E*/
    ModelData* d;
    char name[0x40];
    char path[0x40];
    def = p->d->def;
    h = (AnimHost*)fn_80006E1C(p);
    p->d->h = h;
    if (!fn_800E1FE0(def, h)) {
        fn_80083DC4(p, 1);
        return;
    }
    fn_80008F54(h, (u8)p->d->x6);
    fn_800088A0(h, 0.01f * p->d->def->xF);
    if (!(p->d->flags & 1)) h->f0 |= 0x10000;
    if (!(p->d->flags & 2)) h->f0 |= 0x20000;
    if (p->d->flags & 4) h->f0 |= 0x18;
    if (p->d->flags & 0x80) h->f0 |= 0x20000000;
    if (p->d->flags & 0x4000) {
        Rng* g = (Rng*)fn_80007F10(h);
        if (g) {
            ga = g->a;
            gb = g->b;
            {
                int v = ga + fn_80089ED0() % (gb - ga);
                fn_8000866C(h, v);
            }
        }
    }
    if (p->d->flags & 0x20000) {
        fn_8000866C(h, -1.0f);
    }
    {
        snd = p->d->def->snd;
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
            p->d->flags |= 0x10000000;
        }
    }
    {
        ModelData* e = p->d;
        int k = e->def->xD;
        if (k) {
            e->xB = k;
            fn_800096E4(h, k);
        }
    }
    if (subName(p->d->def->sub10)) {
        {
            SubEntry* e;
            int k = p->d->def->sub10;
            if (k >= 0) {
                e = fn_8010AF20(k);
                if (e) {
                    cname = e->name;
                    goto named;
                }
            }
            cname = 0;
        named:;
        }
        parent = p;
        if (!fn_80076F54(cname)) {
            c = 0;
        } else {
            if (!parent) {
                parent = (void*)4;
            }
            c = (ModelProc*)fn_80081050(lbl_80384278, parent);
            initAll(c, cname);
        }
        if (p) {
            inherit(c, p);
        }
    }
    fn_8017C2F4(h);
    fn_8017D9B4(h, p);
    d = p->d;
    if (d->flags & 0x100000) {
        fn_800E22F8(d->def, name);
        fn_80290DDC(path, "%s%s.gs", "yme/", name);
        if (fn_8023F838(path)) fn_8023FAF0(path);
        fn_80290DDC(path, "%s%s.g", "yme/", name);
        if (fn_8023F838(path)) fn_8023FAF0(path);
        fn_80290DDC(path, "%s%s.ga", "yme/", name);
        if (fn_8023F838(path)) fn_8023FAF0(path);
        fn_80290DDC(path, "%s%s.tpl", "yme/", name);
        if (fn_8023F838(path)) fn_8023FAF0(path);
        d = p->d;
    }
    if (d->cb98) {
        d->cb98(p);
    }
}

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

int fn_800E369C(ModelProc* q) {
    if (firstModel(q)) {
        return 0;
    }
    return 1;
}

void fn_800E36E4(AnimHost** h) {
    if (*h) {
        fn_8017C3B0(*h);
        fn_800E2170(((ModelData*)h)->def, *h);
    }
    fn_80078E24(h);
}

ModelProc* fn_800E3810(const char* name, void* parent) {
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

ModelProc* fn_800E3A10(const char* name, void* parent) {
    ModelProc* p;
    if (!fn_80076F54(name)) {
        return 0;
    }
    p = (ModelProc*)fn_80081194(lbl_80384278, parent);
    initAll(p, name);
    return p;
}

ModelProc* fn_800E3C04(const char* name, void* parent) {
    ModelProc* p;
    if (!fn_80076F54(name)) {
        return 0;
    }
    p = create(name, parent);
    p->d->x8 = 0xC8;
    p->d->flags |= 8;
    return p;
}

ModelProc* fn_800E3E38(const char* name, void* parent) {
    ModelProc* p;
    if (!fn_80076F54(name)) {
        return 0;
    }
    p = create2(name, parent);
    p->d->x8 = 0xC8;
    p->d->flags |= 8;
    return p;
}

ModelProc* fn_800E4060(const char* name, void* parent) {
    ModelProc* p = create(name, parent);
    if (p) {
        p->d->flags |= 0x08000000;
    }
    return p;
}

ModelProc* fn_800E4278(const char* name, void* parent) {
    ModelProc* p = fn_800E4060(name, parent);
    if (p) {
        p->d->x8 = 0xC8;
        p->d->flags |= 8;
    }
    return p;
}

int fn_800E4674(ModelProc* p) {
    ModelDef* def;
    ModelData* d;
    d = p->d;
    def = d->def;
    if (def) {
        if (d->flags & 8) {
            return 1;
        }
        switch (def->flags & 7) {
        case 3:
        case 4:
        case 5:
        case 6:
            return 1;
        }
    }
    return 0;
}

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
int fn_800E46C4(ModelProc* p, int key) { return kInl(p, key); }

extern Colr lbl_804CD8F8;
static inline void setCol(ModelData* d, Colr c) {
    d->col.r = c.r;
    d->col.g = c.g;
    d->col.b = c.b;
    d->col.a = c.a;
}

void fn_800E4768(ModelData* d, const char* name) {
    d->pos.x = 0.0f;
    d->pos.y = 0.0f;
    d->pos.z = 0.0f;
    d->v28[0] = 0.0f;
    d->v28[1] = 0.0f;
    d->v28[2] = 0.0f;
    d->v34[0] = 0.0f;
    d->v34[1] = 0.0f;
    d->v34[2] = 0.0f;
    d->rx = 0.0f;
    d->ry = 0.0f;
    d->rz = 0.0f;
    d->xE = 1;
    d->scale.x = 1.0f;
    d->scale.y = 1.0f;
    d->scale.z = 1.0f;
    d->vel.x = 0.0f;
    d->vel.y = 0.0f;
    d->vel.z = 0.0f;
    d->xB = 0;
    d->x4 = 0;
    d->x12 = 0;
    d->x11 = 0;
    d->x13 = 0;
    d->cb98 = 0;
    d->cb9C = 0;
    d->xA0 = 0;
    d->h = 0;
    d->x10 = 0xFF;
    d->xF = 0x64;
    setCol(d, lbl_804CD8F8);
    d->def = fn_80076F54(name);
    d->flags = 0;
    d->x8 = 0x320;
    d->x6 = 0x98;
    d->xD = 2;
    fn_80312318((Mtx34*)d->m68);
    d->xA4[0] = 0;
    d->xA4[1] = 0;
    d->xA4[2] = 0;
    d->xA4[3] = 0;
    d->xA4[4] = 0;
    d->xA4[5] = 0;
    d->xA4[6] = 0;
    d->xA4[7] = 0;
    d->xC = 0;
}

void fn_800E48C8(ModelProc* p, const Vec* v) {
    p->d->pos.x = v->x;
    p->d->pos.y = v->y;
    p->d->pos.z = v->z;
}

void fn_800E4918(ModelProc* p, f32 v) {
    setRx(p, v);
}

void fn_800E49AC(ModelProc* p, f32 v) {
    setRy(p, v);
}

void fn_800E4A40(ModelProc* p, f32 v) {
    setRz(p, v);
}

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
#if TARGET_PC
extern FE10_PROTO VoiceH* fn_8024F704(p32arg);
#else
extern VoiceH* fn_8024F704(int);
#endif

#pragma use_lmw_stmw on
void fn_800E4B20(ModelProc* p, int n) {
    /*P*/
    int c;
    KeyList** q;
    int ofs;
    int i;
    int j;
    VoiceH* v;
/*E*/
    if (n < 0) {
        n = 0x3C;
    }
    {
        AnimHost* h = p->d->h;
        p->d->x12 = n;
        p->d->x11 = n;
        p->d->x13 = -1;
        if (h) {
            KeyList* buf[0x40];
            c = fn_80009E20(h->o44, buf);
            q = buf;
            for (i = 0; i < c; q++, i++) {
                j = 0;
                ofs = 0;
                for (; j < (*q)->n; ofs += 4, j++) {
                    int s = fn_800F14B4(*(u16*)((u8*)*q + ofs + 4));
                    if (s) {
                        v = fn_8024F704(s);
                        if (v) {
                            v->fade(1000);
                            v->kill();
                        }
                    }
                }
            }
        }
    }
}
#pragma use_lmw_stmw off

extern f32 lbl_804CD91C;

void fn_800E4C14(ModelProc* p) {
    Mtx34 ms;
    Mtx34 mr;
    Mtx34 mt;
    Mtx34 mo;
    Mtx34 mq;
    Vec pos = p->d->pos;
    Vec vel = p->d->vel;
    AnimHost* h = p->d->h;
    Vec sc = p->d->scale;
    Vec rot = {0.0f, 0.0f, 0.0f};
    if (p->d->flags & 0x10000) {
        fn_80312344((Mtx34*)p->d->m68, &h->o10);
        return;
    }
    if (fn_80313508(&vel) > 0.0f) {
        fn_80313460(&pos, &vel, &pos);
        setPos(p, pos);
    }
    fn_80312318(&mr);
    fn_80312318(&mo);
    if (p->d->flags & 8) {
        sc.x *= 152.0f;
        sc.y *= -149.33333f;
        pos.z = p->d->x8;
        rot.z = p->d->rz;
    } else {
        switch (p->d->def->flags & 7) {
        case 1:
        case 2:
            sc.x *= 152.0f;
            sc.y *= -149.33333f;
            fn_80011B90(0, &pos, &pos);
            pos.z = p->d->x8;
            rot.z = p->d->rz;
            break;
        case 3:
        case 4:
        case 5:
        case 6:
            sc.x *= 152.0f;
            sc.y *= -149.33333f;
            pos.x = 304.0f;
            pos.y = 224.0f;
            pos.z = p->d->x8;
            rot.z = p->d->rz;
            break;
        case 0: {
            struct Cm { u8 pad[0xB1]; u8 xB1; u8 padB2[0x32]; Mtx34 mE4; };
            Cm* c = (Cm*)fn_8013B9A8();
            if (c) {
                switch (c->xB1) {
                case 0:
                    fn_80312344(&c->mE4, &mo);
                    fn_803134A8(&sc, &sc, 0.1f);
                    if (p->d->flags & 0x40) {
                        fn_80118B20(lbl_803EC898, pos.x, pos.y, &mr, 1, 0);
                        fn_80312378(&mr, &mo, &mo);
                    }
                }
            }
            {
                ModelData* d = p->d;
                f32 a, b, c;
                a = d->rx;
                b = d->ry;
                c = d->rz;
                rot.x = a;
                rot.y = b;
                rot.z = c;
            }
            break;
        }
        }
    }
    fn_803134A8(&sc, &sc, 0.01f * p->d->def->xE);
    fn_8031292C(&ms, sc.x, sc.y, sc.z);
    fn_8001D748(&mr, p->d->xE, rot.x, rot.y, rot.z);
    fn_803128AC(&mt, pos.x, pos.y, pos.z);
    if (fn_801D09F0()) {
        switch (p->d->def->flags & 7) {
        case 2:
        case 5:
            fn_8031292C(&mo, 0.75000006f, 1.0f, 1.0f);
            break;
        case 4:
            fn_803128AC(&mq, 304.0f, 0.0f, 0.0f);
            fn_8031292C(&mo, 0.75000006f, 1.0f, 1.0f);
            fn_80312378(&mo, &mq, &mo);
            fn_803128AC(&mq, -304.0f, 0.0f, 0.0f);
            fn_80312378(&mq, &mo, &mo);
            if (fn_800D44EC()) {
                fn_803128AC(&mq, 94.0f, 0.0f, 0.0f);
                fn_80312378(&mq, &mo, &mo);
            }
            break;
        case 6:
            fn_803128AC(&mq, -304.0f, 0.0f, 0.0f);
            fn_8031292C(&mo, 0.75000006f, 1.0f, 1.0f);
            fn_80312378(&mo, &mq, &mo);
            fn_803128AC(&mq, 304.0f, 0.0f, 0.0f);
            fn_80312378(&mq, &mo, &mo);
            if (fn_800D44EC()) {
                fn_803128AC(&mq, -lbl_804CD91C, 0.0f, 0.0f);
                fn_80312378(&mq, &mo, &mo);
            }
            break;
        }
    }
    fn_80312378((Mtx34*)p->d->m68, &ms, &mq);
    fn_80312378(&mr, &mq, &mq);
    fn_80312378(&mo, &mq, &mq);
    fn_80312378(&mt, &mq, &h->o10);
}

void fn_800E515C(ModelProc* p) {
    /*P*/
    ModelProc* q;
    AnimHost* h;
    int n;
    int cur;
    int dt;
    int die;
    Rng* g;
/*E*/
    h = p->d->h;
    die = 0;
    if (h) {
        ModelData* d = p->d;
        int s = d->xF;
        if (s != 100) {
            fn_800088A0(h, 0.01f * d->def->xF * s / 100.0f);
        }
        if (((const ModelData*)p->d)->flags & 0x1000) {
            g = (Rng*)fn_80007F10(h);
            int m = g->b - g->a;
            int v = g->a + fn_8017FA1C() % m;
            fn_8000866C(h, v);
        }
        {
            u32 f = p->d->flags;
            if ((f & 0x80000800) == 0) {
                fn_800081D4(h);
            }
        }
        if (p->d->cb9C) {
            p->d->cb9C(p);
        }
        if (((const ModelData*)p->d)->flags & 0x20000000) {
            q = p->parent;
            if (q) {
                inherit(p, q);
            }
        }
        fn_800E4C14(p);
        {
            u32 f = p->d->flags;
            if ((f & 0x2000) && (f & 0x80000000)) {
                fn_80017DF0(h);
            }
        }
        {
            ModelData* e = p->d;
            int a;
            n = e->x12;
            a = e->x10;
            if (n) {
                dt = e->x13;
                cur = e->x11;
                cur += dt;
                e->x11 = cur;
                if (dt < 0 && cur <= 0) {
                    die = 1;
                }
                if (dt > 0 && cur >= n) {
                    p->d->x12 = 0;
                }
                a = fn_8001EF30(0.0f, a, n, cur);
            }
            {
                Colr c = p->d->col;
                fn_80008F10(h, c.r, c.g, c.b);
                fn_80008F20(h, c.a * a / 255);
            }
        }
        fn_80009A2C(h);
        fn_80007C58(h);
        fn_800E2A78(p);
        fn_8017C40C(h);
        fn_8017D17C(h);
        if (h->f0 & 2) {
            ModelData* e = p->d;
            if (!(e->flags & 0x804)) {
                if ((s8)e->xB > 0) {
                    e->xB--;
                } else {
                    die = 1;
                }
            }
        }
        p->d->flags &= 0x7FFFFFFF;
        if (die) {
            ModelData* e = p->d;
            if (((const ModelData*)e)->flags & 0x40000) {
                e->flags |= 0x10;
                fn_8000866C(h, 0.0f);
            } else {
                fn_80083B78(p);
            }
        }
    }
}

void fn_800E57B4(ModelProc* p, int x, int y) {
    f32 z = fn_80113F00(lbl_803EC898, x, y);
    p->d->pos.x = 0.5f + x;
    p->d->pos.y = 0.5f + y;
    p->d->pos.z = z;
}

extern void fn_800E59CC(ModelProc*, Vec*, Vec*);

struct PosHolder {
    u8 pad[4];
    Vec pos;
};

static inline Vec holderPos(PosHolder* a) {
    return a->pos;
}

void fn_800E5884(ModelProc* p, PosHolder* a, PosHolder* b) {
    Vec* pa = 0;
    Vec* pb = 0;
    Vec va;
    Vec vb;
    if (a) {
        if (p->d->def->flags & 0x80) {
            va = holderPos(a);
        } else {
            va = fn_800F7790(a);
        }
        pa = &va;
    }
    if (b) {
        if (p->d->def->flags & 0x80) {
            vb = holderPos(b);
        } else {
            vb = fn_800F7790(b);
        }
        pb = &vb;
    }
    fn_800E59CC(p, pa, pb);
}

void fn_800E59CC(ModelProc* p, Vec* a, Vec* b) {
    Vec* q = b;
    switch (p->d->def->flags & 8) {
    case 0:
        if (b) {
            q = b;
        }
        break;
    case 8:
        if (a) {
            q = a;
        }
        break;
    }
    if (q) {
        f32 x, y, z;
        z = q->z;
        y = q->y;
        x = q->x;
        p->d->pos.x = x;
        p->d->pos.y = y;
        p->d->pos.z = z;
    }
    if (a && b) {
        setRy(p, fn_80176A4C(a->x, a->y, b->x, b->y));
        if (p->d->def->flags & 0x100) {
            setRx(p, fn_80176A4C(a->z, 0.0f, b->z, fn_80176B0C(a->x, a->y, b->x, b->y)));
        }
    }
}

struct RotProc {
    u8 pad[0x30];
    ModelProc* m;
    f32 ax, ay, az;
    f32 bx, by, bz;
    f32 t4C;
    f32 t50;
};

void fn_800E5BD8(RotProc* e) {
    f32 x;
    f32 y;
    f32 z;
    e->t50 += 1.0f;
    x = fn_8001EF30(e->ax, e->bx, e->t4C, e->t50);
    y = fn_8001EF30(e->ay, e->by, e->t4C, e->t50);
    z = fn_8001EF30(e->az, e->bz, e->t4C, e->t50);
    {
        ModelProc* m = e->m;
        m->d->pos.x = x;
        m->d->pos.y = y;
        m->d->pos.z = z;
    }
    if (e->t50 >= e->t4C) {
        fn_80083B78(e);
    }
}

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

void fn_800E5CA8(ModelProc* p) {
    AnimHost* h = p->d->h;
    if (h) {
        int k = fn_80008E88(h, (int)h->x58, 0x13);
        if (k >= 0) {
            spawnRot(p, (f32)k - h->x58, *(Vec*)p->d->v28, *(Vec*)p->d->v34);
        }
    }
}
}
