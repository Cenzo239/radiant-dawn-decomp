/* Conversation room: pick the next topic entry and set its caption text */
#include "game/rN_8025EEF0/types.h"

struct Empty { Empty() {} char c; };

extern "C" {
extern void* lbl_80392768[3];
extern void* lbl_80392750[3];
extern char lbl_803927FC[];
void* fn_80079150(u32 n);
const char* fn_800D0864(const char* s);
u32 strlen(const char* s);
void fn_800250B0(u32* s, int a, u32 n, const char* b, const char* e, Empty t);
u32* fn_80077064(const char* s);
u8* fn_8012CE54(const char* s);
u8* fn_8010B1D8(const char* s);
u8* fn_8012E3A4(u8* u);
s8 fn_8012E9B4(u8* u, u8* v);
u8 fn_8012E8BC(u8* u, int k);
void* fn_8010B094(u8 c);
const char* fn_8009285C(void* c);
const char* fn_80092904(void* c);
const char* fn_80092958(void* c);
void fn_800D0B38(int i, const char* s);
}

class Obj {
public:
    virtual ~Obj();
};

struct Cap {
    void* vt;
    int x4;
    int x8;
    u8* xC;
    u8* x10;
    s16 x14, x16;
    s16 x18, x1A;
    f32 x1C;
    u8 pad20[8];
};

struct Txt {
    void* vt;
    int x4;
    int x8;
    u8* xC;
    char* cur;
    u32 s0;
    u32 slen;
    char* sp;
    u8 x20;
    u8 pad21[3];
    int x24;
    int x28;
    char b2C[0x40];
    char b6C[0x40];
    char bAC[0x40];
    char* xEC;
    char* xF0;
    s16 xF4;
    u8 padF6[2];
    u8* xF8;
    u8* xFC;
    s16 x100, x102;
    f32 x104;
};

struct Ent {
    const char* id;
    const char* m4;
    const char* m8;
    const char* mC;
    const char* m10;
    const char* m14;
    const char* m18;
    const char* m1C;
    const char* m20;
    const char* m24;
    u8 x28;
    u8 pad29[3];
};



struct Room {
    u8 pad0[0x38];
    int x38;
    u32 x3C;
    int x40;
};

struct Side {
    u8 pad0[0x50];
    Cap* x50;
    u8 pad54[4];
    Obj* x58;
    u8 pad5C[4];
    Txt* x60;
    u8 pad64[4];
    Obj* x68;
};

static inline u32 idx(const Room* r) { return r->x3C; }

static inline Cap* newCap(Room* r) {
    Cap* c = (Cap*)fn_80079150(sizeof(Cap));
    if (c != 0) {
        int m = r->x38;
        int k = r->x40;
        c->vt = lbl_80392768;
        c->x4 = k;
        c->x8 = m;
        c->xC = 0;
        c->x10 = 0;
        c->x18 = 0;
        c->x1A = 0;
        c->x1C = 0.0f;
        switch (k) {
        case 0:
            c->x14 = 0x174;
            c->x16 = 0x23;
            break;
        case 1:
            c->x14 = 0;
            c->x16 = 0xF4;
            break;
        }
    }
    return c;
}

static inline Txt* newTxt(Room* r) {
    Txt* t = (Txt*)fn_80079150(sizeof(Txt));
    if (t != 0) {
        int m = r->x38;
        int k = r->x40;
        t->vt = lbl_80392750;
        t->x4 = k;
        t->x8 = m;
        t->xC = 0;
        t->cur = 0;
        t->s0 = 0;
        t->slen = 0;
        t->sp = 0;
        t->x20 = 0;
        t->x24 = 0;
        t->x28 = 0;
        t->xF4 = 0;
        t->xF8 = 0;
        t->xFC = 0;
        t->x104 = 0.0f;
        switch (k) {
        case 0:
            t->x100 = 0x1C;
            t->x102 = 0x1C;
            break;
        case 1:
            t->x100 = 0xBB;
            t->x102 = 0xED;
            break;
        }
    }
    return t;
}

static inline void setText(Side* o, const char* key) {
    const char* s;
    Txt* t = o->x60;
    s = fn_800D0864(key);
    u32 n = (t->s0 >> 31) == 0 ? (*(u8*)&t->s0 & 0x7F) : t->slen;
    Empty e;
    fn_800250B0(&t->s0, 0, n, s, s + strlen(s), e);
    t->cur = (t->s0 >> 31) == 0 ? (char*)&t->s0 + 1 : t->sp;
    t->x20 = 0;
    t->b2C[0] = 0;
    t->b6C[0] = 0;
    t->bAC[0] = 0;
    t->xF4 = 0;
    t->xF0 = t->xEC = t->b2C;
}

extern "C" {

void fn_8027163C(Room* r) {
/*P*/
    Cap* c;
    Txt* x;
    Side* o;
    Ent* e;
    u8* u;
    u8* b;
    u32* tbl;
    BOOL found;
    u8* v;
    void* cls;
/*E*/
    o = (Side*)((u8*)r + r->x40 * 4);
    if (o->x58) delete o->x58;
    if (o->x68) delete o->x68;
    o->x58 = (Obj*)o->x50;
    o->x68 = (Obj*)o->x60;
    o->x50 = newCap(r);
    o->x60 = newTxt(r);
    o->x50->x1C = 0.0f;
    o->x60->x104 = 0.0f;
    tbl = fn_80077064(lbl_803927FC);
    u = 0;
    b = 0;
    e = 0;
    while (idx(r) < tbl[0]) {
        u32 i = r->x3C;
        r->x3C = i + 1;
        e = (Ent*)(tbl + 1) + i;
        u = fn_8012CE54(e->id);
        if (u != 0) break;
        if (e->x28) {
            b = fn_8010B1D8(e->id);
            break;
        }
    }
    found = 0;
    if (u != 0 || b != 0) found = 1;
    e = found ? e : 0;
    if (u != 0) {
        c = o->x50;
        c->xC = u;
        c->x10 = 0;
        x = o->x60;
        x->xF8 = u;
        x->xFC = 0;
        if (!(*(u32*)(u + 0x10C) & 8)) {
            setText(o, e->m4);
            if (e->m10) {
                v = fn_8012CE54(e->m10);
                if (v != 0 && fn_8012E3A4(u) == v && fn_8012E8BC(u, fn_8012E9B4(u, v)) >= 3) {
                    setText(o, e->m14);
                }
            } else if (e->m18) {
                v = fn_8012CE54(e->m18);
                if (v != 0 && (!(*(u32*)(v + 0x10C) & 8) || (*(u32*)(v + 0x10C) & 0x20))) {
                    setText(o, e->m1C);
                }
            } else if (e->m20) {
                v = fn_8012CE54(e->m20);
                if (v != 0 && (*(u32*)(v + 0x10C) & 8) && !(*(u32*)(v + 0x10C) & 0x20)) {
                    setText(o, e->m24);
                }
            }
        } else {
            cls = fn_8010B094(u[0x38E]);
            fn_800D0B38(0, fn_8009285C(cls));
            fn_800D0B38(1, fn_80092904(cls));
            fn_800D0B38(2, fn_80092958(cls));
            if (*(u32*)(u + 0x10C) & 0x20) {
                setText(o, e->m8);
            } else {
                setText(o, e->mC);
            }
        }
    } else if (b != 0) {
        c = o->x50;
        c->xC = 0;
        c->x10 = b;
        x = o->x60;
        x->xF8 = 0;
        x->xFC = b;
        setText(o, e->m4);
    }
}

}
