/* 12 words: e and the first dispName result swap r30 and r26. Includes the whole reader family for context. */
/* FE8 (Path of Radiance) save transfer: copies person data through a stream */
#include "game/rN_8025EEF0/calls.h"

#pragma use_lmw_stmw on

struct BufData { u8* buf; u8* cur; int size; u8 own; };
class Buf : public BufData {
public:
    virtual u32 v08();
    virtual u32 v0C();
    virtual u32 v10();
};
struct Reader : public BufData { void* vt; };

extern "C" {

extern u8 lbl_80380928[];
extern u8 lbl_80380940[];
extern char lbl_8037336C[];
extern char lbl_804CA3B8[8];
void fn_8008A4B0(Reader* r, const char* s, int a);
u32 fn_8008A1DC(Reader* r);
int fn_8008A1A0(Reader* r);
void fn_8008A5AC(Buf* w, u8 v);
void fn_80076D48(const char* s, u32 v);
BOOL fn_8026C650(void* p, void* a);
int fn_8026C75C(void*, Buf* w, void* src);
void fn_80077174(const char* s);
void fn_800763E0(void* p);
void fn_8026CA0C(void*, u8* a);
void fn_8026CDD0(void*, u8* a);
int fn_8026C348(Buf* p, Buf* w);
int fn_8026C4C0(Buf* p, Buf* w);

struct BufObj : public Buf { int m14; };

static inline void readerDtor(Reader* r) {
    r->vt = lbl_80380940;
    if (r->own) {
        fn_80078E24(r->buf);
        r->buf = 0;
        r->own = 0;
    }
}

BOOL fn_8026C1C8(BufObj* p, void* a, void* b) {
    Reader r;
    Reader& rr = r;
    u8* m;
    r.cur = 0;
    r.buf = 0;
    r.size = 0;
    r.own = 0;
    r.vt = lbl_80380928;
    m = (u8*)fn_80078CCC(0x2000, lbl_804CA3B8, 0);
    r.buf = m;
    r.cur = m;
    r.size = 0x2000;
    r.own = 1;
    if (fn_8026C650(p, b) == 0) {
        readerDtor(&r);
        return 0;
    }
    p->m14 = fn_8026C75C(p, p, b);
    fn_80075D78((const char*)a);
    fn_8026C348(p, (Buf*)&rr);
    fn_8026C4C0(p, (Buf*)&rr);
    fn_8026CA0C(p, (u8*)p->v08());
    fn_8026CDD0(p, (u8*)p->v08());
    fn_80077174(lbl_8037336C);
    fn_80077174(lbl_8037336C + 5);
    fn_800763E0(a);
    readerDtor(&r);
    return 1;
}

void fn_8008A5E4(Buf* w, int v);
void fn_8008A48C(Reader* r, void* a);
int fn_8008A1B4(Reader* r);
void fn_8008A7D0(Buf* w, int a, int b);

int fn_8026C348(Buf*, Buf* w) {
    /*P*/
    int n;
    int i;
    Reader r;
/*E*/
    fn_8008A4B0(&r, lbl_8037336C + 0xA, 0);
    n = fn_8008A1DC(&r);
    if ((u32)n > 0x47) {
        n = 0x47;
    }
    fn_80076D48(lbl_8037336C + 5, w->v10());
    for (i = 0; i < n; i++) {
        fn_8008A5AC(w, i + 1);
        r.cur += 0x18;
        fn_8008A1DC(&r);
        r.cur += 0x1D;
        fn_8008A5AC(w, 0);
        { for (int j = 0; j < 8; j++) { int b = fn_8008A1A0(&r); fn_8008A5AC(w, b); } }
        { for (int k = 0; k < 8; k++) { fn_8008A5AC(w, 0); } }
        r.cur = (u8*)(((u32)r.cur + 0x13) & ~3);
    }
    fn_8008A5AC(w, 0);
    readerDtor(&r);
    return n;
}

static inline const char* SS() { return lbl_8037336C; }
int fn_8026C4C0(Buf*, Buf* w) {
    /*P*/
    Reader r;
    int n;
    int v;
    int i;
/*E*/
    fn_8008A4B0(&r, lbl_8037336C + 0x16, 0);
    n = fn_8008A1DC(&r);
    fn_80076D48(lbl_8037336C, w->v10());
    for (i = 0; i < n; i++) {
        fn_8008A5AC(w, i + 1);
        r.cur += 0x14;
        fn_8008A1DC(&r);
        v = 0;
        { for (int m = 0; m < 5; m++) {
            const char* t = (const char*)fn_8008A1DC(&r);
            if (t != 0 && fn_80291188(t, lbl_8037336C + 0x1F) == 0) {
                v = 0x14;
            }
        } }
        fn_8008A5AC(w, v);
        r.cur += 0x18;
        { for (int j = 0; j < 8; j++) { int b = fn_8008A1A0(&r); fn_8008A5AC(w, b); } }
        { for (int k = 0; k < 8; k++) { int b = fn_8008A1A0(&r); fn_8008A5AC(w, b); } }
        r.cur = (u8*)(((u32)r.cur + 0x13) & ~3);
    }
    fn_8008A5AC(w, 0);
    readerDtor(&r);
    return n;
}

int fn_8026C75C(void*, Buf* w, void* src) {
    /*P*/
    int c1;
    Reader r;
    int c2;
    int i;
/*E*/
    c1 = 0;
    c2 = 0;
    fn_8008A5E4(w, 0);
    fn_8008A5E4(w, 0);
    fn_8008A48C(&r, src);
    r.cur += 0x70;
    fn_8008A1DC(&r);
    r.cur += 0x44;
    fn_8008A1DC(&r);
    r.cur += 0x214;
    fn_8008A1DC(&r);
    r.cur += 0x20;
    fn_8008A1DC(&r);
    for (i = 0; i < 0x9F; i++) {
        int t = fn_8008A1B4(&r);
        if ((u16)t != 0) {
            fn_8008A5AC(w, t);
            {
                int t2 = fn_8008A1B4(&r);
                fn_8008A5AC(w, t2);
            }
            r.cur += 5;
            {
                int t3 = fn_8008A1A0(&r);
                fn_8008A5AC(w, t3);
            }
            r.cur += 0x10;
            fn_8008A5AC(w, 0);
            { for (int j = 0; j < 8; j++) { int b = fn_8008A1A0(&r); fn_8008A5AC(w, b); } }
            r.cur += 0x18;
            { for (int j = 0; j < 8; j++) {
                if (fn_8008A1DC(&r) == 0xBB0100) {
                    c1++;
                }
            } }
            { for (int j = 0; j < 8; j++) { int b = fn_8008A1A0(&r); fn_8008A5AC(w, b); } }
            r.cur += 0xE;
            fn_8008A7D0(w, 8, 0);
            { for (int j = 0; j < 8; j++) { int b = fn_8008A1A0(&r); fn_8008A5AC(w, b); } }
            c2++;
            r.cur += 0x17;
        }
    }
    fn_8008A5AC(w, 0);
    fn_8008A1DC(&r);
    { for (int j = 0; j < 0xC8; j++) {
        if (fn_8008A1DC(&r) == 0xBB0100) {
            c1++;
        }
    } }
    fn_8008A1DC(&r);
    i = w->v0C();
    w->cur = w->buf;
    fn_8008A5E4(w, c1);
    fn_8008A5E4(w, c2);
    readerDtor(&r);
    return i;
}

struct NamePair { const char* a; const char* b; };
extern NamePair lbl_803922E8[];
struct PairHdr { u8 pad[4]; int n; };
struct PairTbl { PairHdr* h; u8* items; };

static inline const char* pairName(NamePair* t) {
    if (t->b != 0) {
        return t->b;
    }
    return t->a;
}

static inline int findId(const char* s) {
    NamePair* t = lbl_803922E8;
    int i;
    for (i = 0; i < 0x47; i++, t++) {
        if (fn_80291188(s, pairName(t)) == 0) {
            return i;
        }
    }
    return 0;
}

static inline u8* findEntry(PairTbl* p, int id) {
    int i;
    for (i = 0; i < p->h->n; i++) {
        u8* e = p->items + i * 0x24;
        if (*(s8*)e == id) {
            return e;
        }
    }
    return 0;
}

u8* fn_8026D02C(PairTbl* p, u8* q) {
    const char* s = (const char*)(q + 4);
    return findEntry(p, findId(s));
}

u8* fn_80077064(const char* s);

static inline u8* findRow(u8* tbl, int id) {
    /*P*/
    u8* p;
/*E*/
    for (p = tbl; *(s8*)p != 0; p += 0x12) {
        if (id == *(s8*)p) {
            return p;
        }
    }
    return 0;
}

static inline u8 grade(u8 v) {
    if (v >= 0xFB) return 0x53;
    if (v >= 0xB5) return 0x41;
    if (v >= 0x79) return 0x42;
    if (v >= 0x47) return 0x43;
    if (v >= 0x1F) return 0x44;
    return v >= 1 ? 0x45 : 0x2D;
}

#define ADDS(i, j) e[i] += a[j] + b[j]

void fn_8026CA0C(void*, u8* data) {
    /*P*/
    u32 n;
    u8* t2;
    u8* e;
    u32 i;
    u8* t1;
/*E*/
    e = data + 8;
    n = *(u32*)(data + 4);
    t1 = fn_80077064(lbl_8037336C + 5);
    t2 = fn_80077064(lbl_8037336C);
    for (i = 0; i < n; e += 0x24, i++) {
        /*P*/
        s8 id;
        u8* a;
        u8* b;
        int j;
/*E*/
        id = *(s8*)e;
        if (id != 0) {
            a = findRow(t1, id);
            b = findRow(t2, *(s8*)(e + 1));
            ADDS(2, 1);
            ADDS(4, 2);
            ADDS(5, 3);
            ADDS(6, 4);
            ADDS(7, 5);
            ADDS(8, 6);
            e[9] = e[9] + a[7];
            ADDS(10, 8);
            ADDS(11, 9);
            if ((s8)e[4] >= (s8)b[10]) e[3] |= 1;
            if ((s8)e[5] >= (s8)b[11]) e[3] |= 2;
            if ((s8)e[6] >= (s8)b[12]) e[3] |= 4;
            if ((s8)e[7] >= (s8)b[13]) e[3] |= 8;
            if ((s8)e[8] >= (s8)b[14]) e[3] |= 0x10;
            if ((s8)e[9] >= (s8)b[15]) e[3] |= 0x20;
            if ((s8)e[10] >= (s8)b[16]) e[3] |= 0x40;
            if ((s8)e[11] >= (s8)b[17]) e[3] |= 0x80;
            for (j = 0; j < 8; j++) {
                e[0xC + j] = grade(e[0xC + j]);
            }
        }
    }
}

static inline int findId2(const char* const& s) {
    NamePair* t = lbl_803922E8;
    int i;
    for (i = 0; i < 0x47; i++, t++) {
        if (fn_80291188(s, t->a) == 0) {
            return i;
        }
    }
    return 0;
}

static inline u8* findE(u8* e, int count, int id) {
    int j;
    for (j = 0; j < count; j++, e += 0x24) {
        s8 v = *e;
        if (v != 0 && id == v) {
            return e;
        }
    }
    return 0;
}

void fn_8026CDD0(void*, u8* data) {
    /*P*/
u8* q;
    u8* ent;
    int m;
    int count;
    u8* base;
    int id;
    int zero;
    Reader r;
    int i;
    int k;
    int n;
    const char* s;
/*E*/
    base = data + 8;
    count = *(int*)(data + 4);
    fn_8008A4B0(&r, lbl_8037336C + 0x2A, 0);
    n = fn_8008A1DC(&r);
    zero = 0;
    for (i = 0; i < n; i++) {
        s = (const char*)fn_8008A1DC(&r);
        if (s != 0) {
            s += 4;
        }
        id = findId2(s);
        ent = findE(base, count, id);
        if (ent == 0) {
            int sk = fn_8008A1DC(&r); r.cur += sk * 8;
        } else {
            m = fn_8008A1DC(&r);
            for (k = 0; k < m; k++) {
                const char* p = (const char*)fn_8008A1DC(&r);
                int id2 = 0;
                if (p != 0) {
                    id2 = findId2(p + 4);
                }
                if (id2 != 0) {
                    int a, b, c;
                    q = ent + k;
                    u8 old;
                    q[0x14] = id2;
                    old = q[0x1C];
                    a = fn_8008A1A0(&r);
                    b = fn_8008A1A0(&r);
                    c = fn_8008A1A0(&r);
                    fn_8008A1A0(&r);
                    q[0x1C] = zero;
                    if (old > (u8)a) q[0x1C]++;
                    if (old > (u8)b) q[0x1C]++;
                    if (old > (u8)c) q[0x1C]++;
                } else {
                    q = ent + k;
                    q[0x14] = zero;
                    q[0x1C] = zero;
                    fn_8008A1DC(&r);
                }
            }
        }
    }
    readerDtor(&r);
}

void* fn_8010599C(int a);
void fn_80105704(void* a);
void fn_80105260(void* a, const char* s);
extern int lbl_804CB80C;
extern int lbl_804CB800;
int fn_80290D04(char* b, int n, const char* f, ...);
void fn_802452B4(u8* s, const char* b);
void* fn_8010B1D8(const char* s);
void fn_80119BB4(void* a, void* b, int c);
void fn_801130D4(void* a, void* b, int c, int d);

static inline const char* dispName(const char* s) {
    int i;
    for (i = 0; i < 0x47; i++) {
        if (fn_80291188(s, lbl_803922E8[i].a) == 0) {
            NamePair* t = &lbl_803922E8[i];
            return pairName(t);
        }
    }
    return 0;
}

void fn_8026D0F8(PairTbl* p) {
    /*P*/
    void* v;
    int flag;
int off;
    int n;
    u8* q;
u8* e;
    int cnt;
    const char* name;
    u32 w;
    const char* other;
    int i;
    int j;
    void* u1;
    void* u2;
/*E*/
    char buf88[0x40];
    char buf48[0x40];
    char buf8[0x40];
    v = fn_8010599C(3);
    fn_80105704(v);
    n = *(int*)p->h;
    { for (int i0 = 0; i0 < n; i0++) {
        fn_80105260(v, lbl_8037336C + 0x38);
    } }
    lbl_804CB80C = 0;
    lbl_804CB800 = 0;
    cnt = p->h->n;
    for (i = 0, off = 0; i < cnt; off += 0x24, i++) {
        e = p->items + off;
        name = lbl_803922E8[*(s8*)e].a;
        w = *(u32*)name;
        for (j = 0; j < 8; j++) {
            u8* o;
            q = e + j;
            if (q[0x1C] != 0 && q[0x14] != 0) {
                o = findEntry(p, q[0x14]);
                if (o != 0) {
                    other = lbl_803922E8[*(s8*)o].a;
                    if (w <= *(u32*)other) {
                        if (q[0x1C] >= 1) {
                            fn_80290D04(buf88, 0x40, lbl_8037336C + 0x41, name, other);
                            fn_802452B4(fn_8024BC94(), buf88);
                        }
                        if (q[0x1C] >= 2) {
                            fn_80290D04(buf88, 0x40, lbl_8037336C + 0x4F, name, other);
                            fn_802452B4(fn_8024BC94(), buf88);
                        }
                        if (q[0x1C] >= 3) {
                            fn_80290D04(buf88, 0x40, lbl_8037336C + 0x5D, name, other);
                            fn_802452B4(fn_8024BC94(), buf88);
                        }
                        flag = 1;
                        if (fn_80291188(name, lbl_8037336C + 0x6B) != 0 && fn_80291188(other, lbl_8037336C + 0x6B) != 0) {
                            flag = 0;
                        }
                        const char* a = dispName(name);
                        const char* b = dispName(other);
                        if (a != 0 && b != 0) {
                            fn_80290D04(buf48, 0x40, lbl_8037336C + 0x71, a);
                            fn_80290D04(buf8, 0x40, lbl_8037336C + 0x71, b);
                            u1 = fn_8010B1D8(buf48);
                            u2 = fn_8010B1D8(buf8);
                            if (u1 != 0 && u2 != 0) {
                                fn_80119BB4(u1, u2, (s8)q[0x1C]);
                                if (flag == 0 && q[0x1C] >= 3) {
                                    fn_801130D4(u1, u2, 1, 5);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

}
