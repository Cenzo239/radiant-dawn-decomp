/* wip near misses for fn_801E7024.cpp (whole file kept so declarations stay together):
   fn_801E7218: 17 of 73 words differ
   fn_801E733C: 19 of 85 words differ
   fn_801E74CC: 4 of 57 words differ
   fn_801E77E8: 14 of 84 words differ
   fn_801E7990: 17 of 38 words differ
*/
#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/vobj.h"
#include "game/rI_801DD7D4/rlist.h"
#pragma auto_inline off

extern "C" {

extern char lbl_803CAB38[];
extern char lbl_8036EE94[];
extern char lbl_8038CC64[];
extern char* lbl_804CB810;
int* fn_8006074C(void*);
int fn_80060754(void*);
int fn_80290D04(char*, int, const char*, ...);
u8* fn_80077064(const char*);
int fn_800D0864(int);
void fn_8010E41C(u8*, int);
s8 fn_8012C9BC(void*, int);
void* fn_801059B0(void);
int fn_80105328(void*, int);
void* fn_8024BC94(void);
void fn_8024519C(void*, int);
void* fn_80076F54(const char*);
void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E720(f32);
void fn_80011CBC(void*, void*);
extern char fn_80006EE0[];
void fn_801D7014(int, int, int, int, int);
void fn_801D8C24(int, int, int);
void fn_80072ACC(int, int, int, int, int, int, int);
void fn_801E2204(void*, s16*, s16*);

u8 fn_801E7024(void) {
    char buf[0x20];
    u8* p;
    u8 r;
    fn_80290D04(buf, 0x20, lbl_8036EE94, *fn_8006074C(lbl_803CAB38));
    p = fn_80077064(buf);
    r = 0;
    if (p[0] != 0) {
        r = p[0];
    } else if (p[1] != 0) {
        r = p[1];
    } else if (p[2] != 0) {
        r = p[2];
    } else if (p[3] != 0) {
        r = p[3];
    }
    return r;
}

u8 fn_801E70C4(void) {
    char buf[0x20];
    fn_80290D04(buf, 0x20, lbl_8036EE94, *fn_8006074C(lbl_803CAB38));
    return fn_80077064(buf)[0];
}

u8 fn_801E7114(void) {
    char buf[0x20];
    fn_80290D04(buf, 0x20, lbl_8036EE94, *fn_8006074C(lbl_803CAB38));
    return fn_80077064(buf)[1];
}

u8 fn_801E7164(void) {
    char buf[0x20];
    fn_80290D04(buf, 0x20, lbl_8036EE94, *fn_8006074C(lbl_803CAB38));
    return fn_80077064(buf)[2];
}

u8 fn_801E71B4(void) {
    char buf[0x20];
    fn_80290D04(buf, 0x20, lbl_8036EE94, *fn_8006074C(lbl_803CAB38));
    return fn_80077064(buf)[3];
}

int fn_801E7204(u8 i) {
    return fn_800D0864(((int*)lbl_8038CC64)[i]);
}

typedef struct Item {
    u32 id;
    u8 x4;
    u8 b0 : 2;
    u8 used : 1;
    u8 b3 : 5;
    u8 pad6[0x28 - 6];
} Item;
typedef struct UnitT {
    u8 pad0[0xec];
    int xec;
    u8 padf0[4];
    u8* xf4;
    u8 padf8[0x1bc - 0xf8];
    Item items[7];
} UnitT;

static inline UnitT* getUnit(u8 id) {
    return id != 0 ? (UnitT*)(lbl_804CB810 + (id - 1) * 0x3F0) : NULL;
}

#pragma use_lmw_stmw on
BOOL fn_801E7218(int id) {
    u8 mask[4];
    int r;
    UnitT* u;
    int i;
    if (id == 0) {
        return 0;
    }
    r = 0;
    fn_8010E41C(mask, 4);
    for (i = 1; i <= 0xfe; i++) {
        u = getUnit(i);
        if (u->xec != 0 && mask[u->xf4[8]] != 0) {
            s8 k = fn_8012C9BC(u, id);
            if (k >= 0 && !u->items[k].used) {
                r = 1;
                break;
            }
        }
    }
    if (r == 0) {
        if (fn_80060754(lbl_803CAB38) != 0) {
            id = fn_80105328(fn_801059B0(), id);
            if (id >= 0) {
                Item* it = *(Item**)((u8*)fn_801059B0() + 4);
                if (!it[id].used) {
                    r = 1;
                }
            }
        }
    }
    return r;
}

static inline int countItem(UnitT* u, u32 id) {
    int c = 0;
    Item* it = u->items;
    int j;
    for (j = 0; j < 7; j++, it++) {
        u32 v;
        if (it == NULL) break;
        v = it->id;
        if (v == 0) break;
        if (!it->used && id == v) c++;
    }
    return c;
}

int fn_801E733C(u32 id) {
    u8 mask[4];
    int r;
    if (id == 0) {
        return 0;
    }
    r = 0;
    fn_8010E41C(mask, 4);
    {
        int i;
        for (i = 1; i <= 0xfe; i++) {
            UnitT* u = getUnit(i);
            if (u->xec != 0 && mask[u->xf4[8]] != 0) {
                r += countItem(u, id);
            }
        }
    }
    if (fn_80060754(lbl_803CAB38) != 0) {
        int j = 0;
        int n = *(int*)fn_801059B0();
        int ofs = 0;
        for (; j < n; j++, ofs += 0x28) {
            Item* it = (Item*)(*(u8**)((u8*)fn_801059B0() + 4) + ofs);
            if (it != NULL) {
                u32 v = it->id;
                if (v != 0 && !it->used && id == v) {
                    r++;
                }
            }
        }
    }
    return r;
}
#pragma use_lmw_stmw off

int fn_801E7490(Item* it) {
    u32 v;
    if (it == NULL || (v = it->id) == 0) {
        return 0;
    }
    if (it->used) {
        return 1;
    }
    return fn_801E733C(v);
}

void fn_801E74CC(void) {
    u8* e;
    void* s = fn_8024BC94();
    int* p = (int*)fn_80076F54(lbl_8036EE94 + 0xf);
    if (p != NULL) {
        u32 n = *p;
        u32 i;
        e = (u8*)(p + 1);
        for (i = 0; i < n; i++, e += 0x30) {
            fn_8024519C(s, *(int*)(e + 0xc));
        }
    }
    p = (int*)fn_80076F54(lbl_8036EE94 + 0x1e);
    if (p != NULL) {
        u32 i = 0;
        u32 n = *p;
        e = (u8*)(p + 1);
        for (; i < n; i++, e += 0x2c) {
            fn_8024519C(s, *(int*)(e + 0x20));
            fn_8024519C(s, *(int*)(e + 0x24));
            fn_8024519C(s, *(int*)(e + 0x28));
        }
    }
}

typedef struct HNode { struct HNode* prev; struct HNode* next; void* val; void* handle; } HNode;
typedef struct HList { int size; HNode* prev; HNode* next; } HList;
typedef struct Menu {
    void** vt;
    u8 pad4[6];
    s16 xa, xc, xe, x10;
    s16 x12, x14, x16, x18;
    u8 pad1a[4];
    s16 x1e, x20;
    u8 pad22[0x52 - 0x22];
    s16 x52;
    u8 pad54[2];
    s16 x56, x58, x5a, x5c, x5e;
    u8 pad60[0x70 - 0x60];
    HList list;
    u8 (*x7c)(int, void*);
    void* x80;
    void* x84;
} Menu;

static inline void hClear(Menu* o) {
    HNode* p = o->list.next;
    HNode* e = (HNode*)&o->list.prev;
    if (p != e) {
        HNode* last = e->prev;
        p->prev->next = last->next;
        last->next->prev = p->prev;
        while (p != e) {
            void** h = (void**)&p->val;
            HNode* t;
            if (h != NULL) {
                if (h[1] != NULL) {
                    fn_80011CBC(fn_80006EE0, h[1]);
                }
            }
            t = p;
            p = p->next;
            fn_80079210(t);
            o->list.size--;
        }
    }
}

void fn_801E7730(Menu* o) {
    hClear(o);
    o->x52 = 0;
}

class MenuV {
public:
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2C();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3C();
    virtual void v40();
    virtual int v44();
    virtual void v48();
    virtual int v4C();
};

void fn_801E77E8(Menu* o, int i) {
    int vis;
    s16 cols, cnt, rows;
    int m;
    if (i == o->x52) {
        return;
    }
    vis = ((MenuV*)o)->v4C();
    cols = o->x5c;
    m = cols - 1;
    cnt = o->list.size;
    rows = (cnt + m) / cols;
    if (i < 0 || cnt <= i) {
        return;
    }
    if ((s16)vis > rows) {
        vis = rows;
    }
    if (i < o->x52) {
        do {
            s16 s = --o->x52;
            if (s > m) {
                s16 r = s / cols;
                if (r - o->x5a == 0) {
                    o->x5a--;
                }
            }
        } while (i < o->x52);
    } else {
        s16 v = vis;
        do {
            if (++o->x52 > cnt - 1) {
                o->x52 = cnt - 1;
            }
            {
                s16 r = o->x52 / cols;
                if (r < rows - 1 && v - 1 == r - o->x5a) {
                    o->x5a++;
                }
            }
        } while (o->x52 < i);
    }
    o->x56 = -0x8000;
    o->x58 = -0x8000;
}

void fn_801E7938(Menu* o, void* c) {
    HNode* n;
    HNode* first = o->list.next;
    n = first;
    while (n != (HNode*)&o->list.prev && n->val != c) {
        n = n->next;
    }
    if (n != (HNode*)&o->list.prev) {
        int k = 0;
        for (; first != n; first = first->next) {
            k++;
        }
        fn_801E77E8(o, (s16)k);
    }
}

u32 fn_801E7990(Menu* o) {
    s16 q[2];
    s16 p[2];
    int w = ((MenuV*)o)->v44();
    int cols = o->x5c;
    int sel = o->x52;
    int top = o->x5a;
    int row = sel / cols;
    int h = o->x5e;
    int ox = o->x1e;
    int oy = o->x20;
    p[0] = w * (s16)(sel - row * cols) + ox;
    p[1] = h * (s16)((s16)row - top) + oy;
    fn_801E2204(o, q, p);
    return *(u32*)q;
}

BOOL fn_801E7BC0(Menu* o, int a) {
    BOOL r = 1;
    if (o->x7c != NULL) {
        r = o->x7c(a, o->x80) != 0;
    }
    return r;
}

void fn_801E7DA4(void* o, int x, int y, int w, int h, int k) {
    fn_80072ACC(x + (w >> 1), y + (h >> 1), w, 0x17, 0x19, 0x4c, k);
}

void fn_801E7DD0(VO0* o) {
    o->v14();
    fn_8007E154();
    fn_8007E720(3.0f);
    fn_8007E164();
    fn_801D8C24(0, 0, 0x10);
}

void fn_801E89D4(VO0* o) { o->v24(); }

void* fn_8012E3A4(void*);
s8 fn_8012E9B4(void*, void*);
int fn_8012EA2C(void*, int);

int fn_801E89E4(Menu* o, void* a) {
    if (o->x7c != NULL) {
        return o->x7c((int)a, o->x80) != 0;
    }
    if (fn_8012E3A4(o->x84) == a) {
        return 1;
    }
    {
        s8 k = fn_8012E9B4(o->x84, a);
        if (k >= 0) {
            return fn_8012EA2C(o->x84, k);
        }
    }
    return 0;
}

void fn_801E8CF8(Menu* o) {
    ((VO0*)o)->v14();
    fn_801D7014(0, 0, (s16)(o->xe - o->xa), (s16)(o->x10 - o->xc), 0x10);
}

int fn_801E8E50(void) { return 4; }

s16 fn_801E8E58(Menu* o) {
    return (s16)(o->x16 - o->x12) / o->x5c;
}

void fn_801E8E78(void) {}
void fn_801E8E7C(void) {}
int fn_801E8E80(void) { return 10; }

}
