/* Talk/event text system: script tokenizer and the state at lbl_804181AC. */
#include "game/rL_80133EB4/map3d.h"
#pragma auto_inline off
#pragma use_lmw_stmw on

extern "C" {

struct Talk {
    void* proc;        /* 0x000 */
    u32 str0;          /* 0x004 */
    u32 str1;          /* 0x008 */
    char* strp;        /* 0x00C */
    char* cur;         /* 0x010 */
    void* x14;         /* 0x014 */
    void* x18;         /* 0x018 */
    u8 slots[0x19C - 0x1C]; /* 0x01C: 16 of 0x18 bytes */
    s8 x19c[0x28];
    void* x1c4[8];     /* 0x1C4 */
    void* x1e4;        /* 0x1E4 */
    u8 x1e8;           /* 0x1E8 */
    u8 x1e9;           /* 0x1E9 */
    u8 x1ea;
    u8 x1eb;
    s16 x1ec;
    s16 x1ee;
    s16 x1f0;
    u8 x1f2;           /* 0x1F2 */
    u8 x1f3;
    u32 x1f4;
    u32 x1f8;
    u32 x1fc;
    s8 cur200;         /* 0x200 */
    s8 x201;
    s8 x202;
    s8 x203;
    s16 x204;
    s16 x206;
    u8* actor[5];      /* 0x208 */
    void* x21c[9];     /* 0x21C */
    void* x240;        /* 0x240 */
};

extern Talk lbl_804181AC;
extern u32 lbl_804CB878;
extern u32 lbl_804CB700;
extern u8 lbl_80418160[];
extern u8 lbl_80386A98[];
extern u8 lbl_80386C30[];
extern char lbl_804CA788[8];
extern char lbl_804CA790[8];

extern void* fn_80083B84(void*);
extern void fn_80083B78(void*);
extern void fn_80083DC4(void*, int);
extern void fn_80083174(void*);
extern void fn_80081A90(void*);
extern void* fn_8017F37C(const char*, const char*, const char*);
extern void* fn_800D4188(void*, void*);
extern void fn_800D3BCC(void*, int);
#if TARGET_PC
extern FE10_PROTO void * fn_80076F54(void*);
#else
extern int fn_80076F54(void*);
#endif
extern void fn_8014D350(u32*);
extern void fn_8014D220(u32*);
extern u8* fn_800C3558(void);
extern void fn_8014B650(void*);
extern u8 fn_800D3CF4(void*);
extern void fn_800C7114(void*, void*);
extern void fn_80151D28(void*, void*);
extern void fn_8014CF98(void);
extern void* fn_800D4228(void*);
extern void* fn_800811E4(void*, void*);
extern void fn_800D3C90(void*, int);
extern void fn_800C900C(int, int);
extern u32 fn_800C7FE8(void);
extern void fn_800C835C(int, int);
extern int fn_80068D74(void);
extern void fn_80068CBC(void);
extern void fn_80150F0C(void*);
extern void fn_800C71CC(void*, void*);
extern void fn_800C4240(void*);
extern int fn_8014D070(void*);

u32 fn_80148634(void) {
    u32 f = lbl_804CB878;
    lbl_804CB878 = f & ~0x400;
    if (f & 0x2000) return 0;
    if (!(lbl_804CB5B8->v48() & 0x400)) {
        if (!(lbl_804CB5B8->v34() & 0x400004) || !(lbl_804CB5B8->v34() & 0x400)) {
            if (lbl_804CB878 & 8) {
                if (!(lbl_804CB5B8->v48() & 0x800)) return 0;
            } else {
                return (lbl_804CB700 & 3) != 0;
            }
        } else {
            lbl_804CB878 |= 0x400;
        }
    }
    lbl_804CB878 |= 0x200;
    return 1;
}

static inline BOOL IsSjisLead(const u8* p) {
    u8 c = p[0];
    if ((c >= 0x81 && c <= 0x9F) || (c >= 0xE0 && c <= 0xFC)) {
        c = p[1];
        if ((c >= 0x40 && c <= 0x7E) || (c >= 0x80 && c <= 0xFC)) return 1;
    }
    return 0;
}

u8* fn_80148728(u8** s) {
    u8* d;
    int n;
    {
        s8* q = (s8*)*s;
        if (q == 0) return 0;
        if (*q == 0) return 0;
        if (*q == '|') {
            *s = (u8*)q + 1;
            return 0;
        }
    }
    n = 0;
    d = lbl_80418160;
    while (**s != '|' && n < 0x40) {
        if (IsSjisLead(*s)) {
            n += 2;
            *d = *(*s)++;
            d[1] = *(*s)++;
            d += 2;
        } else {
            n++;
            *d++ = *(*s)++;
        }
    }
    *d = 0;
    (*s)++;
    return lbl_80418160;
}

int fn_80148858(char** s) {
    BOOL neg;
    int v;
    {
        char* q = *s;
        char c;
        if (q == 0) return 0x40BBDEF8;
        c = *q;
        if (c == 0) return 0x40BBDEF8;
        if (c == 0) {
            *s = q + 1;
            return 0x40BBDEF8;
        }
    }
    neg = 0;
    v = 0;
    while (**s != '|') {
        char c = **s;
        v *= 10;
        if (c >= '0' && c <= '9') {
            v += c - '0';
        } else if (c >= 'A' && c <= 'F') {
            v += c - 'A' + 10;
        } else if (c == '-') {
            neg = 1;
        }
        (*s)++;
    }
    if (neg) v = -v;
    (*s)++;
    return v;
}

static inline int Hex(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    return 0;
}

int fn_8014893C(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    return 0;
}

static inline u8* CurActor(Talk* t) {
    int i;
    if (t->cur200 < 0) return 0;
    i = t->x19c[t->cur200];
    if (i < 0) return 0;
    return t->actor[i];
}

void* fn_8014A504(Talk* t) {
    u8* a;
    if (t->x1e8) return t->x21c[0];
    a = CurActor(t);
    if (a == 0) return 0;
    return t->x21c[(s8)a[0x43]];
}

int fn_8014A5A8(Talk* t, u8** s) {
    fn_800D4188(fn_8017F37C(lbl_804CA790, (char*)fn_80148728(s), 0), t->proc);
    if (t->x1e9 && !(lbl_804CB700 & 3)) {
        fn_80083DC4(t->proc, 1);
        return 2;
    }
    if (t->x18) fn_800D3BCC(fn_800D4188(t->x18, t->proc), 8);
    return 1;
}

void fn_8014A63C(Talk* t, u8** s) {
    void* p;
    if (t->x14) {
        fn_80081A90(t->x14);
        t->x14 = 0;
    }
    p = fn_8017F37C(lbl_804CA788, (char*)fn_80148728(s), 0);
    if (fn_80076F54(p) == 0) p = lbl_80386C30;
    t->x14 = fn_800D4188(p, t->proc);
}

void fn_8014AD1C(void* a, char* s, int* n, int* d) {
    *n = Hex(s[0]);
    switch (s[1]) {
    case 'L':
        *d = -1;
        break;
    case 'R':
        *d = 1;
        break;
    case 'D':
        *d = 0;
        break;
    }
}

void fn_8014B558(void) {
    if (fn_800C7FE8() & 4) {
        lbl_804181AC.x1f2 = 2;
    } else if (fn_800C7FE8() & 8) {
        lbl_804181AC.x1f2 = 5;
    } else if (fn_80068D74() == 0) {
        fn_800C835C(1, 0);
        lbl_804181AC.x1f2 = 2;
    } else {
        lbl_804181AC.x1f2 = 2;
        fn_800C835C(3, lbl_804181AC.x204);
    }
}

void fn_8014B5FC(void) {
    if (fn_80068D74()) {
        fn_80068CBC();
        lbl_804CB878 |= 0x80;
    }
    if (lbl_804181AC.x18) fn_800D4188(lbl_804181AC.x18, lbl_804181AC.proc);
}

void fn_8014C25C(void) {
    fn_8014D350(&lbl_804CB878);
    lbl_804CB878 &= ~0x30;
    lbl_804181AC.cur += 2;
    fn_80083DC4(lbl_804181AC.proc, 0);
}

int fn_8014C83C(void) {
    Talk* t = &lbl_804181AC;
    if (t->x14 && fn_800D3CF4(t->x14) && fn_800D3CF4(t->x14) != 0xFF) return 0xFF - fn_800D3CF4(t->x14);
    return 0;
}

struct PT { u8 pad0[0x30]; Talk* t; };

struct Empty { Empty() {} char c; };
extern const char* fn_800D0864(const void*);
extern u32 strlen(const char*);
extern void fn_800250B0(u32*, int, u32, const char*, const char*, Empty);
extern void fn_80150C68(void*);
extern void fn_80006A2C(void*);
extern void fn_800D42A0(void*);
extern void fn_8014CFEC(void);
extern void fn_80068C08(void);
extern void fn_8014D364(u32*);
#if TARGET_PC
extern FE10_PROTO void fn_800DF6C8(ptr32<const void>);
#else
extern void fn_800DF6C8(void*);
#endif
extern void* lbl_804CB880;

void fn_8014C148(const void* a) {
    const char* s = fn_800D0864(a);
    Talk* t = &lbl_804181AC;
    u32 n;
    int i;
    for (i = 0; i < 16; i++) t->x19c[i] = -1;
    n = (t->str0 >> 31) == 0 ? (*(u8*)&t->str0 & 0x7F) : t->str1;
    fn_800250B0(&lbl_804181AC.str0, 0, n, s, s + strlen(s), Empty());
    lbl_804181AC.cur = (lbl_804181AC.str0 >> 31) == 0 ? (char*)&lbl_804181AC.str0 + 1 : lbl_804181AC.strp;
    lbl_804CB878 &= ~0x30;
    fn_80083DC4(lbl_804181AC.proc, 0);
}

extern void fn_8014D310(u32*);
extern void fn_8014EEEC(void*);
extern u8 lbl_80413F10[];

void fn_8014BC80(const char* text, void* parent) {
    u32 n;
    int i;
    fn_8014D310(&lbl_804CB878);
    lbl_804181AC.proc = fn_800811E4(lbl_80386A98, parent);
    {
        for (i = 0; i < 5; i++) lbl_804181AC.actor[i] = 0;
        for (i = 0; i < 9; i++) lbl_804181AC.x21c[i] = 0;
        for (i = 0; i < 16; i++) {
            lbl_804181AC.slots[i * 0x18] = 0;
            lbl_804181AC.x19c[i] = -1;
        }
        for (i = 0; i < 8; i++) lbl_804181AC.x1c4[i] = 0;
        lbl_804181AC.x1e4 = lbl_804181AC.x1c4;
        lbl_804181AC.x201 = -1;
        lbl_804181AC.cur200 = -1;
        lbl_804181AC.x203 = -1;
        lbl_804181AC.x202 = -1;
        lbl_804181AC.x1f4 = 1;
        n = (lbl_804181AC.str0 >> 31) == 0 ? (*(u8*)&lbl_804181AC.str0 & 0x7F) : lbl_804181AC.str1;
    }
    fn_800250B0(&lbl_804181AC.str0, 0, n, text, text + strlen(text), Empty());
    lbl_804181AC.cur = (lbl_804181AC.str0 >> 31) == 0 ? (char*)&lbl_804181AC.str0 + 1 : lbl_804181AC.strp;
    {
        Talk* t = &lbl_804181AC;
        t->x18 = 0;
        t->x14 = 0;
        t->x1ec = 8;
        t->x1ee = 8;
        t->x1f0 = 0;
        t->x1f8 = 0x808;
        t->x1fc = 0x808;
        t->x1f3 = 1;
        t->x204 = 800;
        t->x1ea = 0;
        t->x1eb = 0;
        t->x206 = 0;
        t->x1e9 = 0;
        ((u8*)t)[0x1AC] = 0;
    }
    fn_8014EEEC(lbl_80413F10);
    fn_8014D220(&lbl_804CB878);
    if (lbl_804CB700 & 1) {
        fn_8014B650(lbl_804181AC.proc);
    } else {
        fn_800C3558()[0x1C] = 1;
    }
}

} /* extern "C" */
