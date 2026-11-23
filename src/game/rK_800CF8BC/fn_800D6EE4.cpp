/* Battle effect pops for triangle attacks, guardian and support (names guessed). */
typedef signed char s8;
typedef unsigned char u8;
typedef unsigned int u32;
typedef int BOOL;
#pragma use_lmw_stmw on

struct C4 { u8 r, g, b, a; };
struct Glob {
    u8 pad0[0x3F0];
    u32 u3F0;
    u8 pad3F4[0x48B - 0x3F4];
    u8 b48B;
    u8 pad48C[0x49C - 0x48C];
    u32 u49C;
    u8 pad4A0[0x890 - 0x4A0];
    u32 u890;
    u8 pad894[0xD30 - 0x894];
    u32 uD30;
    u8 padD34[0x15EC - 0xD34];
    u32 fl;
    u32 u15F0;
    u32 u15F4;
};
struct Item { u32 w0; u8 pad4[0xC]; const char* o10; };
struct Pop { u8 pad[0x30]; int x; int y; int k; u8 pad3C[4]; int t; C4 col; };
struct PU { u8 pad[0x102]; s8 x; s8 y; };

extern "C" {
extern u8 lbl_803C8E80[];
extern char lbl_8036651C[];
extern u8 lbl_80383FF8[];
extern const char* lbl_804CA65C;
extern const char* lbl_804CA660;
extern const char* lbl_804CA664;
extern const char* lbl_804CA6B8;
Item* fn_8010B23C(const char*);
int fn_80124A4C(void*, u32, u32*);
int fn_80124BC0(void*, u32*);
void* fn_800E3A10(const char*, void*);
#if TARGET_PC
FE10_PROTO void fn_800E5878(void*, p32arg);
#else
void fn_800E5878(void*, u32);
#endif
#if TARGET_PC
FE10_PROTO void fn_800E5884(void*, p32arg, p32arg);
#else
void fn_800E5884(void*, u32, u32);
#endif
Pop* fn_80081194(void*, void*);
const char* fn_8011A054(Item*);
int fn_8013B9B0();
void fn_801CE2F4(const char*, int, int);
const char* fn_800D0864(const char*);
#if TARGET_PC
FE10_PROTO void fn_8010301C(p32arg, p32arg, int, int, p32arg);
#else
void fn_8010301C(u32, u32, int, int, void*);
#endif
void fn_8009F630(void*);

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

static inline void Eff(const char* s, u32 u, void* p) {
    if (u) {
        void* m = fn_800E3A10(s, p);
        if (m) fn_800E5878(m, u);
    }
}

static inline void X(Glob* a, Item* v, void* p, u32* buf, int& n, int& j, const char*& s, C4 c, int& r) {
    n = fn_80124A4C(a, v->w0, buf);
    if (n > 0) {
        for (j = 0; j < n; j++) {
            Eff(v->o10, buf[j], p);
            u32 u = buf[j];
            Pop* o = fn_80081194(lbl_80383FF8, p);
            o->x = ((PU*)u)->x;
            o->y = ((PU*)u)->y;
            o->k = 1;
            o->t = 0x3C;
            C4 t = c;
            o->col = t;
        }
        s = fn_8011A054(v);
        ChatMsg(a, s);
        r = 1;
    }
}
#pragma push
#pragma auto_inline off
int fn_800D6EE4(Glob* a, void* p) {
    u32 buf[0x40];
    const char* names[4] = {lbl_804CA660, lbl_804CA65C, lbl_804CA664, 0};
    C4 col[3] = {{255, 255, 255, 0x20}, {255, 0, 0, 0x20}, {0, 0, 0, 0x20}};
    /*P*/
    int n;
    int r;
    Item* v;
    int j;
    const char* s;
    int i;
/*E*/
    r = 0;
    for (i = 0; names[i]; i++) {
        v = fn_8010B23C(names[i]);
        X(a, v, p, buf, n, j, s, col[i], r);
    }
    return r;
}
#pragma pop

#pragma inline_max_size(4000)
#pragma inline_depth(10)
#pragma push
#pragma auto_inline off
int fn_800D70F4(void*);
#pragma pop
extern C4 lbl_804CD878;
static inline void Eff2(const char* const& s, u32 u, void* p) {
    if (u) {
        void* m = fn_800E3A10(s, p);
        if (m) fn_800E5878(m, u);
    }
}
static inline void Sup(Glob* a, Item* v, void* p, u32* buf, const C4& src, int& n, int& j, u32& u, const char*& s) {
    C4 k = src;
    n = fn_80124BC0(a, buf);
    if (n > 0) {
    for (j = 0; j < n; j++) {
        Eff(v->o10, buf[j], p);
        u = buf[j];
        Pop* o = fn_80081194(lbl_80383FF8, p);
        o->x = ((PU*)u)->x;
        o->y = ((PU*)u)->y;
        o->k = 3;
        o->t = 0x3C;
        C4 t = k;
        o->col = t;
    }
        s = fn_8011A054(v);
        ChatMsg(a, s);
    }
}
static inline void W1(Glob* a, Item* v, void* p, u32* buf, const C4& c, int& n, int& j, u32& u, const char*& s) { Sup(a, v, p, buf, c, n, j, u, s); }
static inline void W2(Glob* a, Item* v, void* p, u32* buf, const C4& c, int& n, int& j, u32& u, const char*& s) { W1(a, v, p, buf, c, n, j, u, s); }
static inline void W3(Glob* a, Item* v, void* p, u32* buf, const C4& c, int& n, int& j, u32& u, const char*& s) { W2(a, v, p, buf, c, n, j, u, s); }
static inline int Guard(void* p) {
    Glob* g = (Glob*)lbl_803C8E80;
    if (!(g->fl & 0x40000)) return 0;
    u32 u2;
    u32 u1;
    u1 = g->u890;
    u2 = g->uD30;
    if (!u1 || !u2) return 0;
    Eff2(lbl_8036651C + 0x50, u1, p);
    Eff2(lbl_8036651C + 0x50, u2, p);
    ChatMsg((Glob*)(lbl_803C8E80 + 0x4A0), fn_800D0864(lbl_8036651C + 0x5D));
    return 1;
}
static inline void Sup2(Glob* a, void* p) {
    if (!a) return;
    u32 u2;
    u32 u1;
    u1 = a->u3F0;
    u2 = a->u49C;
    if (!u1 || !u2) return;
    Eff2(lbl_8036651C + 0x68, u1, p);
    Eff2(lbl_8036651C + 0x68, u2, p);
    ChatMsg(a, fn_800D0864(lbl_8036651C + 0x74));
}
static inline Glob* G2(Glob* g) { return (Glob*)((u8*)g + 0x4A0); }
static inline void fn_800D724C_i(Glob* g, Glob* g2, void* p) {
    u32 b2[0x40];
    u32 b1[0x40];
    /*P*/
    const char* s2;
    int n1;
    int j1;
    Item* v;
    u32 u1;
    int n2;
    int j2;
    Item* v2;
    u32 u2;
    const char* s1;
/*E*/

    fn_800D6EE4(g, p);
    fn_800D6EE4(g2, p);
    v = fn_8010B23C(lbl_804CA6B8);
    W1(g, v, p, b1, lbl_804CD878, n1, j1, u1, s1);
    v2 = fn_8010B23C(lbl_804CA6B8);
    W3(g2, v2, p, b2, lbl_804CD878, n2, j2, u2, s2);
    if (!Guard(p)) {
        Sup2(g, p);
        Sup2(g2, p);
    }
    fn_800D70F4(p);
}
void fn_800D724C(void* p) { Glob* g = (Glob*)lbl_803C8E80; Glob* g2 = (Glob*)((u8*)g + 0x4A0); fn_800D724C_i(g, g2, p); }
}
