/* Quadtree over mesh bounding boxes, and the save/load of map render settings. */
#include "game/rL_80133EB4/types.h"

extern "C" {

struct Mesh {
    u8 flags;         /* 0x00 */
    u8 pad1[0xF];
    u8* owner;        /* 0x10 */
    u8 pad14[0xB0 - 0x14];
    f32 minx, miny, minz; /* 0xB0 */
    f32 maxx, maxy, maxz; /* 0xBC */
    Mesh* next;       /* 0xC8 */
    u8 padCC[4];
};

struct QTNode {
    u8 split;         /* 0x00 */
    u8 visible;       /* 0x01 */
    u16 count;        /* 0x02 */
    Vec min;          /* 0x04 */
    Vec max;          /* 0x10 */
    Mesh* head;       /* 0x1C */
    Mesh* tail;       /* 0x20 */
    QTNode* kid[4];   /* 0x24 */
};

extern Vec lbl_80369450;
extern Vec lbl_8036945C;
extern int fn_80020F04(Vec*, Vec*);

void fn_80133EB4(QTNode* n);

static inline void CopyVec(Vec* d, const Vec& s) { *d = s; }

static inline void QTReset(QTNode* n) {
    int i;
    n->head = 0;
    n->tail = 0;
    n->count = 0;
    n->visible = 0;
    {
        Vec a = lbl_80369450;
        n->min = a;
    }
    {
        Vec b = lbl_8036945C;
        n->max = b;
    }
    if (n->split) {
        for (i = 0; i < 4; i++) fn_80133EB4(n->kid[i]);
    }
}

#pragma push
#pragma auto_inline off
void fn_80133EB4(QTNode* n) {
    int i;
    n->head = 0;
    n->tail = 0;
    n->count = 0;
    n->visible = 0;
    {
        Vec a = lbl_80369450;
        n->min = a;
    }
    {
        Vec b = lbl_8036945C;
        n->max = b;
    }
    if (n->split) {
        for (i = 0; i < 4; i++) QTReset(n->kid[i]);
    }
}

#pragma pop

#pragma auto_inline off

int fn_80134024(QTNode* n) {
    Mesh* m;
    int i;
    if (n->count == 0) return 0;
    m = n->head;
    if (m == 0) {
        n->min.z = 10000.0f;
        n->max.z = -10000.0f;
    } else {
        n->min.z = m->minz;
        n->max.z = m->maxz;
    }
    while (m != 0) {
        if (n->min.z > m->minz) n->min.z = m->minz;
        if (n->max.z < m->maxz) n->max.z = m->maxz;
        m = m->next;
    }
    if (n->split) {
        for (i = 0; i < 4; i++) {
            if (fn_80134024(n->kid[i])) {
                if (n->min.z > n->kid[i]->min.z) n->min.z = n->kid[i]->min.z;
                if (n->max.z < n->kid[i]->max.z) n->max.z = n->kid[i]->max.z;
            }
        }
    }
    return 1;
}

static inline BOOL QTAdd(QTNode* n, Mesh* m) {
    if (m->minx >= n->min.x && m->miny >= n->min.y && m->maxx <= n->max.x && m->maxy <= n->max.y) {
        if (n->head == 0) n->head = m;
        if (n->tail != 0) n->tail->next = m;
        n->tail = m;
        n->count++;
        return 1;
    }
    return 0;
}

void fn_80134140(QTNode* n) {
    Mesh* m;
    Mesh* next;
    int i;
    if (n->split) {
        struct { f32 x, y; } c;
        f32 x0 = n->min.x;
        c.x = 0.5f * (x0 + n->max.x);
        c.y = 0.5f * (n->min.y + n->max.y);
        n->kid[0]->min.x = x0;
        n->kid[0]->max.x = c.x;
        n->kid[0]->min.y = n->min.y;
        n->kid[0]->max.y = c.y;
        n->kid[1]->min.x = c.x;
        n->kid[1]->max.x = n->max.x;
        n->kid[1]->min.y = n->min.y;
        n->kid[1]->max.y = c.y;
        n->kid[2]->min.x = c.x;
        n->kid[2]->max.x = n->max.x;
        n->kid[2]->min.y = c.y;
        n->kid[2]->max.y = n->max.y;
        n->kid[3]->min.x = n->min.x;
        n->kid[3]->max.x = c.x;
        n->kid[3]->min.y = c.y;
        n->kid[3]->max.y = n->max.y;
        m = n->head;
        n->tail = 0;
        n->head = 0;
        while (m != 0) {
            next = m->next;
            m->next = 0;
            if (!QTAdd(n->kid[0], m) && !QTAdd(n->kid[1], m) && !QTAdd(n->kid[2], m) && !QTAdd(n->kid[3], m)) {
                if (n->head == 0) n->head = m;
                if (n->tail != 0) n->tail->next = m;
                n->tail = m;
            }
            m = next;
        }
        for (i = 0; i < 4; i++) fn_80134140(n->kid[i]);
    }
}

void fn_8013450C(QTNode* n, QTNode* parent) {
    Mesh* m;
    int i;
    if (n->count != 0) {
        if (parent == 0 || parent->visible == 0) {
            if (fn_80020F04(&n->min, &n->max)) {
                n->visible = 1;
            } else {
                n->visible = 0;
            }
        } else {
            n->visible = parent->visible;
        }
        m = n->head;
        while (m != 0) {
            if ((*(u32*)(m->owner + 0xB8) & 4) != 0 ||
                (!n->visible && !fn_80020F04((Vec*)&m->minx, (Vec*)&m->maxx))) {
                m->flags &= ~0x20;
            } else {
                m->flags |= 0x20;
            }
            m = m->next;
        }
        if (n->split) {
            for (i = 0; i < 4; i++) fn_8013450C(n->kid[i], n);
        }
    }
}

extern char lbl_803694D4[];
extern int fn_80291188(const char*, const char*);

const char* fn_80134624(u32 i) {
    switch (i) {
    case 0: return lbl_803694D4;
    case 1: return lbl_803694D4 + 5;
    case 2: return lbl_803694D4 + 0xA;
    case 3: return lbl_803694D4 + 0x13;
    case 4: return lbl_803694D4 + 0x1C;
    case 5: return lbl_803694D4 + 0x1F;
    case 6: return lbl_803694D4 + 0x24;
    case 7: return lbl_803694D4 + 0x29;
    case 8: return lbl_803694D4 + 0x2C;
    case 9: return lbl_803694D4 + 0x31;
    case 10: return lbl_803694D4 + 0x36;
    case 11: return lbl_803694D4 + 0x3B;
    case 12: return lbl_803694D4 + 0x40;
    case 13: return lbl_803694D4 + 0x45;
    case 14: return lbl_803694D4 + 0x48;
    case 15: return lbl_803694D4 + 0x4B;
    case 16: return lbl_803694D4 + 0x4E;
    case 17: return lbl_803694D4 + 0x51;
    case 18: return lbl_803694D4 + 0x56;
    case 19: return lbl_803694D4 + 0x5B;
    case 20: return lbl_803694D4 + 0x62;
    case 21: return lbl_803694D4 + 0x67;
    default: return lbl_803694D4 + 0x6C;
    }
}

int fn_801347B0(const char* name) {
    int i;
    for (i = 0; i < 0x16; i++) {
        if (fn_80291188(fn_80134624(i), name) == 0) return i;
    }
    return 0x15;
}

struct Color { u8 r, g, b, a; };
extern u8 lbl_804CB830;
extern u8 lbl_804CB834[4];
extern u8 lbl_804CB838;
extern u8 lbl_804CB839;
extern u8 lbl_804CB83A;
extern u8 lbl_804CB83B;
extern Color lbl_804CB83C;
extern u16 lbl_804CB840;
extern u16 lbl_804CB842;
extern u16 lbl_804CB844;
extern s8 lbl_804CB846;
extern s16 lbl_804CB848;
extern s16 lbl_804CB84A;
extern u8 lbl_804CB84C;
extern u8 lbl_804CB84D;
extern u8 lbl_804CB84E;
extern Color lbl_80413BE8[4];
extern Color lbl_80413BF8[4];
extern u8 lbl_80413C08[0x40];
extern u8 lbl_80380928[];
extern u8 lbl_80380940[];
extern void fn_8008A5AC(void*, u8);
extern void fn_8008A5C0(void*, u16);
extern u8 fn_8008A1A0(void*);
extern s16 fn_8008A1B4(void*);
extern void fn_8008A48C(void*, void*);
extern void fn_80078E24(void*);
extern void fn_8001A218(int, void*);
struct CamN { u8 pad0[4]; f32 x, y, z; f32 x2, y2; u8 pad18[4]; int id; };
extern CamN* fn_8012FCD0(void);
extern void fn_8012F558(CamN*);
extern void fn_8012F5CC(CamN*, int);

void fn_8013498C(void* s) {
    int i;
    u8* a;
    u8* b;
    CamN* c;
    fn_8008A5AC(s, 4);
    fn_8008A5AC(s, lbl_804CB830);
    fn_8008A5AC(s, lbl_804CB839);
    fn_8008A5AC(s, lbl_804CB83A);
    fn_8008A5AC(s, lbl_804CB83B);
    fn_8008A5AC(s, lbl_804CB83C.r);
    fn_8008A5AC(s, lbl_804CB83C.g);
    fn_8008A5AC(s, lbl_804CB83C.b);
    for (i = 0; i < 4; i++) fn_8008A5AC(s, lbl_804CB834[i]);
    for (i = 0; i < 4; i++) {
        fn_8008A5AC(s, lbl_80413BE8[i].r);
        fn_8008A5AC(s, lbl_80413BE8[i].g);
        fn_8008A5AC(s, lbl_80413BE8[i].b);
        fn_8008A5AC(s, lbl_80413BF8[i].r);
        fn_8008A5AC(s, lbl_80413BF8[i].g);
        fn_8008A5AC(s, lbl_80413BF8[i].b);
    }
    fn_8008A5C0(s, lbl_804CB840);
    fn_8008A5C0(s, lbl_804CB842);
    fn_8008A5C0(s, lbl_804CB844);
    c = fn_8012FCD0();
    if (c) {
        lbl_804CB846 = c->id;
        lbl_804CB848 = 64.0f * c->x;
        lbl_804CB84A = 64.0f * c->y;
    }
    fn_8008A5AC(s, lbl_804CB846);
    fn_8008A5C0(s, lbl_804CB848);
    fn_8008A5C0(s, lbl_804CB84A);
    fn_8008A5AC(s, lbl_804CB838);
    fn_8008A5AC(s, lbl_804CB84C);
    fn_8008A5AC(s, lbl_804CB84D);
    fn_8008A5AC(s, lbl_804CB84E);
}

void fn_80134B80(void* s) {
    u8 ver;
    int i;
    CamN* c;
    ver = fn_8008A1A0(s);
    lbl_804CB830 = fn_8008A1A0(s);
    lbl_804CB839 = fn_8008A1A0(s);
    lbl_804CB83A = fn_8008A1A0(s);
    lbl_804CB83B = fn_8008A1A0(s);
    lbl_804CB83C.r = fn_8008A1A0(s);
    lbl_804CB83C.g = fn_8008A1A0(s);
    lbl_804CB83C.b = fn_8008A1A0(s);
    for (i = 0; i < 4; i++) lbl_804CB834[i] = fn_8008A1A0(s);
    for (i = 0; i < 4; i++) {
        lbl_80413BE8[i].r = fn_8008A1A0(s);
        lbl_80413BE8[i].g = fn_8008A1A0(s);
        lbl_80413BE8[i].b = fn_8008A1A0(s);
        lbl_80413BF8[i].r = fn_8008A1A0(s);
        lbl_80413BF8[i].g = fn_8008A1A0(s);
        lbl_80413BF8[i].b = fn_8008A1A0(s);
    }
    lbl_804CB840 = fn_8008A1B4(s);
    lbl_804CB842 = fn_8008A1B4(s);
    lbl_804CB844 = fn_8008A1B4(s);
    lbl_804CB846 = fn_8008A1A0(s);
    lbl_804CB848 = fn_8008A1B4(s);
    lbl_804CB84A = fn_8008A1B4(s);
    c = fn_8012FCD0();
    if (c) {
        fn_8012F558(c);
        if (lbl_804CB846 >= 0) {
            fn_8012F5CC(c, lbl_804CB846);
            {
                f32 t = lbl_804CB848 / 64.0f;
                c->x = t;
                c->x2 = t;
            }
            {
                f32 t = lbl_804CB84A / 64.0f;
                c->y = t;
                c->y2 = t;
            }
        }
    }
    if (ver >= 3) {
        lbl_804CB838 = fn_8008A1A0(s);
        if (ver >= 4) {
            lbl_804CB84C = fn_8008A1A0(s);
            lbl_804CB84D = fn_8008A1A0(s);
            lbl_804CB84E = fn_8008A1A0(s);
        }
    }
}

struct MemStream {
    u8* base;
    u8* cur;
    int size;
    u8 owned;
    void* vt;
};

void fn_80134DB0(void) {
    MemStream w;
    w.vt = lbl_80380928;
    w.owned = 0;
    w.base = lbl_80413C08;
    w.cur = lbl_80413C08;
    w.size = 0x40;
    fn_8013498C(&w);
    w.vt = lbl_80380940;
    if (w.owned) {
        fn_80078E24(w.base);
        w.base = 0;
        w.owned = 0;
    }
}

void fn_80134E30(void) {
    MemStream w;
    fn_8008A48C(&w, lbl_80413C08);
    fn_80134B80(&w);
    w.vt = lbl_80380940;
    if (w.owned) {
        fn_80078E24(w.base);
        w.base = 0;
        w.owned = 0;
    }
}

struct Sc {
    u8 pad0[0xC];
    Mesh* mesh;  /* 0x0C */
    u8 pad10[0x52 - 0x10];
    s16 nMesh;   /* 0x52 */
    u8 pad54[0xB4 - 0x54];
    u32 flagsB4;
};

#pragma use_lmw_stmw on
#pragma use_lmw_stmw off

} /* extern "C" */
