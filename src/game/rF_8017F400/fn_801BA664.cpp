#include "game/rF_8017F400/types.h"
#pragma auto_inline off
extern "C" {
typedef struct SkillD { u8 pad[0x1F]; u8 x1F; } SkillD;
typedef struct Slot { SkillD* p; u8 pad[4]; } Slot;
typedef struct UEc { u8 pad[0xE1]; s8 xE1; u8 padE2[4]; u16 xE6; u8 padE8[4]; u16 xEC; u8 padEE[0x16]; s8 x104; } UEc;
typedef struct U {
    u8 pad[0xEC];
    UEc* ec;
    UEc* xF0;
    u8 padF4[4];
    U* xF8;
    u8 padFC[2]; s8 xFE; u8 padFF[0xD];
    u32 flags;
    struct { u8 d[4]; } x110;
    s8 x114; u8 pad115[3]; s8 x118;
    u8 pad119[0x13];
    Slot x12C[18];
} U;
typedef struct Row { U* u; u8 pad[4]; void* x8; U* xC; U* x10; u16 x14; u8 x16; u8 x17; u8 x18, x19, x1A, x1B; } Row;

extern void* fn_80118F00(UEc*);
extern const char* fn_800D0864(const char*);
extern const char* fn_80118C44(UEc*);
extern int fn_80290DDC(char*, const char*, ...);
extern char lbl_80389B48[], lbl_80389B3C[], lbl_80389B30[];
extern char lbl_80389BA0[], lbl_80389B94[];
extern char lbl_804CA804[4], lbl_804CA800[4];
extern char lbl_80389BC0[], lbl_80389BAC[];
extern void fn_801B5EB4(int, int, void*, f32, f32);

static inline int SortKey(U* u) {
    int k;
    u32 f;
    if (u == NULL) return 0;
    f = u->flags;
    k = -(int)u->ec->xE6;
    if (f & 0x200000) k -= 2000;
    if (f & 0x10) k -= 1000;
    if (f & 0x400000) k += 1000;
    if (f & 0x10000) k += 2000;
    return k;
}

int fn_801BA664(void* self, Row* e, int col) {
    U* u = e->u;
    switch (col) {
    case 0:
        return SortKey(u);
    case 1:
        return -(int)u->xF0->xEC;
    case 2: {
        u64 f = (u64)u->flags & 0xC0000000ULL;
        switch (f) {
        case 0: return 2;
        case 0x40000000: return 1;
        case 0x80000000: return 0;
        }
        break;
    }
    }
    return 0;
}

const void* fn_801BA760(void* self, Row* e, int col) {
    U* u = e->u;
    switch (col) {
    case 0:
        return 0;
    case 1:
        return fn_80118F00(u->xF0);
    case 2: {
        u64 f = (u64)u->flags & 0xC0000000ULL;
        switch (f) {
        case 0: return fn_800D0864(lbl_80389B48);
        case 0x40000000: return fn_800D0864(lbl_80389B3C);
        case 0x80000000: return fn_800D0864(lbl_80389B30);
        }
        break;
    }
    }
    return 0;
}

char* fn_801BA8C0(char* buf, Row* e, int col) {
    switch (col) {
    case 0:
        return 0;
    case 1:
        if (e->xC == NULL) {
            fn_80290DDC(buf, lbl_80389BA0);
        } else {
            fn_80290DDC(buf, lbl_804CA804, fn_80118C44(e->xC->ec));
        }
        break;
    case 2:
        if (e->x10 == NULL) {
            fn_80290DDC(buf, lbl_80389B94);
        } else {
            fn_80290DDC(buf, lbl_804CA800, fn_80118C44(e->x10->ec));
        }
        break;
    }
    return buf;
}

#define CELLEND *a = 0; *c = 0x38; *d = *b + 0x14

void fn_801BA994(void* self, int col, int* a, int* b, int* c, int* d) {
    switch (col) {
    case 0: *b = 0; break;
    case 1: *b = 0x2E4; break;
    }
    CELLEND;
}

const char* fn_801BA9E0(void* self, int col) {
    switch (col) {
    case 1: return lbl_80389BC0;
    default: return lbl_80389BAC;
    }
}

int fn_801BAA04(void* self, Row* e, int col) {
    U* u = e->u;
    int r = 0;
    switch (col) {
    case 0:
        return SortKey(u);
    case 1:
        if (e->xC != 0) r = 1;
        if (e->x10 != 0) r++;
        return r;
    }
    return 0;
}

void fn_801BAAA4(void* self, int col, int* a, int* b, int* c, int* d) {
    switch (col) {
    case 0: *b = 0; break;
    case 1: *b = 0x1F4; break;
    case 2: *b = 0x208; break;
    case 3: *b = 0x21C; break;
    case 4: *b = 0x230; break;
    case 5: *b = 0x244; break;
    case 6: *b = 0x258; break;
    case 7: *b = 0x26C; break;
    case 8: *b = 0x280; break;
    case 9: *b = 0x294; break;
    case 10: *b = 0x2A8; break;
    case 11: *b = 0x2BC; break;
    case 12: *b = 0x2D0; break;
    }
    CELLEND;
}

void fn_801BB26C(void* self, int col, int* a, int* b, int* c, int* d) {
    switch (col) {
    case 0: *b = 0; break;
    case 1: *b = 0x2F8; break;
    case 2: *b = 0x320; break;
    case 3: *b = 0x334; break;
    }
    CELLEND;
}
void fn_801BB818(void* self, int col, int* a, int* b, int* c, int* d) {
    switch (col) {
    case 0: *b = 0; break;
    case 1: *b = 0x1CC; break;
    case 2: *b = 0x1E0; break;
    }
    CELLEND;
}
void fn_801BBA8C(void* self, int col, int* a, int* b, int* c, int* d) {
    switch (col) {
    case 0: *b = 0; break;
    case 1: *b = 0x154; break;
    case 2: *b = 0x168; break;
    case 3: *b = 0x17C; break;
    case 4: *b = 0x190; break;
    case 5: *b = 0x1A4; break;
    case 6: *b = 0x1B8; break;
    }
    CELLEND;
}
void fn_801BBDE4(void* self, int col, int* a, int* b, int* c, int* d) {
    switch (col) {
    case 0: *b = 0; break;
    case 1: *b = 0x104; break;
    case 2: *b = 0x118; break;
    case 3: *b = 0x12C; break;
    case 4: *b = 0x140; break;
    }
    CELLEND;
}

struct IconBase { u8 d[0x44]; };
class IconFont : public IconBase {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4(int x, int y, int id);
};
extern u8 lbl_803E7290[];
extern u8 lbl_803E72D8[];
#define ICONS ((IconFont*)lbl_803E7290)
#define ICONS2 ((IconFont*)lbl_803E72D8)

extern int fn_8012C250(U* u, int i);
extern const char* fn_801113DC(int);
extern char lbl_804CA834[4], lbl_804CA830[4], lbl_804CA82C[4], lbl_804CA828[4], lbl_804CA824[4], lbl_804CA820[4], lbl_804CA81C[4], lbl_804CA818[4], lbl_804CA814[4], lbl_804CA810[4], lbl_804CA80C[4], lbl_804CA808[4];
extern char lbl_80389CC4[], lbl_80389CB0[], lbl_80389C9C[], lbl_80389C88[], lbl_80389C74[], lbl_80389C60[], lbl_80389C4C[], lbl_80389C38[], lbl_80389C24[], lbl_80389C10[], lbl_80389BFC[], lbl_80389BE8[], lbl_80389BD4[];
extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E4E4(f32 x, f32 y, f32 z, f32 w);
#if TARGET_PC
extern FE10_PROTO void fn_8007E374(void* tex, p32arg, int b);
#else
extern void fn_8007E374(void* tex, int a, int b);
#endif
#if TARGET_PC
extern FE10_PROTO void fn_8007E74C(ptr32<const void>, ptr32<const void>);
#else
extern void fn_8007E74C(void* cb, s16* r);
#endif
extern void fn_8007E7DC(int a);
extern u16 fn_800CEABC(int);
extern void fn_801B5E64(void);
extern void fn_801B5E3C(void);
extern int fn_801196F0(int);
extern U* fn_8012E3A4(U*);
extern s8 fn_8012E9B4(U*, U*);
extern u8 fn_8012E8A0(U*, int);
extern int fn_80109174(void*);
extern int fn_801091E0(void*, int);
extern void fn_80291110(char*, char*);
extern char lbl_804CA844[4], lbl_804CA840[4], lbl_804CA838[8];
extern char lbl_80389D4C[], lbl_80389D40[], lbl_80389CD8[];

const char* fn_801BAB7C(void* self, int col) {
    switch (col) {
    case 1: return lbl_80389CC4;
    case 2: return lbl_80389CB0;
    case 3: return lbl_80389C9C;
    case 4: return lbl_80389C88;
    case 5: return lbl_80389C74;
    case 6: return lbl_80389C60;
    case 7: return lbl_80389C4C;
    case 8: return lbl_80389C38;
    case 9: return lbl_80389C24;
    case 10: return lbl_80389C10;
    case 11: return lbl_80389BFC;
    case 12: return lbl_80389BE8;
    case 0:
    default: return lbl_80389BD4;
    }
}

int fn_801BAC38(void* self, Row* e, int col) {
    U* u = e->u;
    switch (col) {
    case 0: return SortKey(u);
    case 1: return (s16)fn_8012C250(u, 0);
    case 2: return (s16)fn_8012C250(u, 1);
    case 3: return (s16)fn_8012C250(u, 2);
    case 4: return (s16)fn_8012C250(u, 3);
    case 5: return (s16)fn_8012C250(u, 4);
    case 6: return (s16)fn_8012C250(u, 5);
    case 7: return (s16)fn_8012C250(u, 6);
    case 8: return (s16)fn_8012C250(u, 7);
    case 9: return (s16)fn_8012C250(u, 8);
    case 10: return (s16)fn_8012C250(u, 9);
    case 11: return (s16)fn_8012C250(u, 10);
    case 12: return (s16)fn_8012C250(u, 11);
    }
    return 0;
}

#define WL(i, s) fn_80290DDC(buf, s, fn_801113DC((s16)fn_8012C250(u, i))); break

char* fn_801BAD90(char* buf, Row* e, int col) {
    U* u = e->u;
    switch (col) {
    case 0: return 0;
    case 1: WL(0, lbl_804CA834);
    case 2: WL(1, lbl_804CA830);
    case 3: WL(2, lbl_804CA82C);
    case 4: WL(3, lbl_804CA828);
    case 5: WL(4, lbl_804CA824);
    case 6: WL(5, lbl_804CA820);
    case 7: WL(6, lbl_804CA81C);
    case 8: WL(7, lbl_804CA818);
    case 9: WL(8, lbl_804CA814);
    case 10: WL(9, lbl_804CA810);
    case 11: WL(10, lbl_804CA80C);
    case 12: WL(11, lbl_804CA808);
    }
    return buf;
}

void fn_801BAFF4(void* self, void* tex, f32 x, f32 y) {
    fn_8007E154();
    fn_8007E4E4(x, y, 300.0f, 1.0f);
    fn_8007E374(tex, 1, 0x11);
    fn_8007E74C((void*)fn_801B5E64, 0);
    fn_8007E7DC(0xC0);
    fn_8007E164();
    ICONS->v4(0, 0, fn_800CEABC(0));
    ICONS->v4(0x1B, 0, fn_800CEABC(1));
    ICONS->v4(0x36, 0, fn_800CEABC(2));
    ICONS->v4(0x51, 0, fn_800CEABC(3));
    ICONS->v4(0x6C, 0, fn_800CEABC(4));
    ICONS->v4(0x87, 0, fn_800CEABC(5));
    ICONS->v4(0xA2, 0, fn_800CEABC(6));
    ICONS->v4(0xBD, 0, fn_800CEABC(7));
    ICONS->v4(0xD8, 0, fn_800CEABC(8));
    ICONS->v4(0xF3, 0, fn_800CEABC(9));
    ICONS->v4(0x10E, 0, fn_800CEABC(10));
    ICONS->v4(0x129, 0, fn_800CEABC(11));
}

static inline s8 Aff(U* u) { s8 v = u->x118; if (v == -1) v = u->ec->xE1; return v; }
static inline BOOL SlotOK(Slot* s) {
    if (s == NULL) return 0;
    if (s->p == NULL) return 0;
    return s->p->x1F != 0;
}
static inline BOOL SOK(Slot* s) { return s && s->p && s->p->x1F; }
static inline BOOL SOK2(Slot* s) { return s->p && s->p->x1F; }
static inline SkillD* G(Slot* s) { return s->p; }
static inline u8 X1F(SkillD* s) { return s->x1F; }
static inline u8 X(Slot* s) { if (s) { SkillD* d = s->p; if (d) return d->x1F; } return 0; }

int fn_801BB8B8(void* self, Row* e, int col) {
    U* u = e->u;
    switch (col) {
    case 0:
        return SortKey(u);
    case 1:
        return u->xF8 != 0;
    case 2:
        return fn_80109174(&u->x110);
    }
    return 0;
}

char* fn_801BB958(char* buf, Row* e, int col) {
    U* u = e->u;
    void* l = &u->x110;
    switch (col) {
    case 0:
        return 0;
    case 1:
        if (u->xF8) {
            fn_80290DDC(buf, lbl_804CA844, fn_80118C44(u->xF8->ec));
        } else {
            fn_80290DDC(buf, lbl_80389D4C);
        }
        break;
    case 2:
        if (fn_80109174(l) == 0) {
            fn_80290DDC(buf, lbl_80389D40);
        } else {
            int i;
            char t[8];
            fn_80290DDC(buf, lbl_804CA840);
            for (i = 0; i < fn_80109174(l); i++) {
                fn_80290DDC(t, lbl_804CA838, fn_801091E0(l, i) - 1);
                fn_80291110(buf, t);
            }
        }
        break;
    }
    return buf;
}
extern s8 fn_8012408C(void*);
extern s8 fn_8012401C(void*);
extern s8 fn_80124144(void*);
int fn_801BBBA4(void* self, Row* e, int col) {
    U* u = e->u;
    switch (col) {
    case 0: return SortKey(u);
    case 1: return e->x18;
    case 2: return e->x19;
    case 3: return e->x1A + e->x1B * 100;
    case 4: return fn_8012408C(u);
    case 5: return fn_8012401C(u);
    case 6: return fn_80124144(u);
    }
    return 0;
}

extern char lbl_804CA874[4], lbl_804CA870[4], lbl_804CA868[8], lbl_804CA860[8], lbl_804CA858[8], lbl_804CA854[4], lbl_804CA850[4], lbl_804CA84C[4], lbl_804CA848[4];
extern char lbl_80389D94[];
char* fn_801BBC84(char* buf, Row* e, int col) {
    U* u = e->u;
    switch (col) {
    case 0: return 0;
    case 1: fn_80290DDC(buf, lbl_804CA874, e->x18); break;
    case 2: fn_80290DDC(buf, lbl_804CA870, e->x19); break;
    case 3:
        if (e->x1A == 0) {
            fn_80290DDC(buf, lbl_804CA868);
        } else if (e->x1A != e->x1B) {
            if (e->x1B == 0xFF) {
                fn_80290DDC(buf, lbl_804CA860, e->x1A, fn_800D0864(lbl_80389D94));
            } else {
                fn_80290DDC(buf, lbl_804CA858, e->x1A, e->x1B);
            }
        } else {
            fn_80290DDC(buf, lbl_804CA854, e->x1A);
        }
        break;
    case 4: fn_80290DDC(buf, lbl_804CA850, fn_8012408C(u)); break;
    case 5: fn_80290DDC(buf, lbl_804CA84C, fn_8012401C(u)); break;
    case 6: fn_80290DDC(buf, lbl_804CA848, fn_80124144(u)); break;
    }
    return buf;
}
int fn_801BBECC(void* self, Row* e, int col) {
    U* u = e->u;
    switch (col) {
    case 0: return SortKey(u);
    case 1: if (e->x8 == 0) return 0; return ((u16*)e->x8)[7];
    case 2: return e->x16;
    case 3: return e->x14;
    case 4: return e->x17;
    }
    return 0;
}
extern const char* fn_8010F5E0(void*);
extern char lbl_80389E3C[], lbl_804CA894[4], lbl_804CA88C[8], lbl_804CA888[4], lbl_804CA880[8], lbl_804CA87C[4], lbl_804CA878[4];
char* fn_801BBF8C(char* buf, Row* e, int col) {
    switch (col) {
    case 0: return 0;
    case 1:
        if (e->x8 == 0) { fn_80290DDC(buf, lbl_80389E3C); } else { fn_80290DDC(buf, lbl_804CA894, fn_8010F5E0(e->x8)); }
        break;
    case 2:
        if (e->x16 == 0) { fn_80290DDC(buf, lbl_804CA88C); } else { fn_80290DDC(buf, lbl_804CA888, e->x16); }
        break;
    case 3:
        if (e->x14 == 0) { fn_80290DDC(buf, lbl_804CA880); } else { fn_80290DDC(buf, lbl_804CA87C, e->x14); }
        break;
    case 4:
        fn_80290DDC(buf, lbl_804CA878, e->x17);
        break;
    }
    return buf;
}
void fn_801BC094(void* self, int col, int* a, int* b, int* c, int* d) {
    switch (col) {
    case 0: *b = 0; break;
    case 1: *b = 0x78; break;
    case 2: *b = 0x8C; break;
    case 3: *b = 0xA0; break;
    case 4: *b = 0xB4; break;
    case 5: *b = 0xC8; break;
    case 6: *b = 0xDC; break;
    case 7: *b = 0xF0; break;
    }
    CELLEND;
}
extern char lbl_80389F94[], lbl_80389F80[], lbl_80389F6C[], lbl_80389F54[], lbl_80389F40[], lbl_80389F2C[], lbl_80389F18[], lbl_80389F04[];
const char* fn_801BC130(void* self, int col) {
    switch (col) {
    case 1: return lbl_80389F94;
    case 2: return lbl_80389F80;
    case 3: return lbl_80389F6C;
    case 4: return lbl_80389F54;
    case 5: return lbl_80389F40;
    case 6: return lbl_80389F2C;
    case 7: return lbl_80389F18;
    case 0:
    default: return lbl_80389F04;
    }
}
extern s16 fn_8012386C(U*), fn_80123998(U*), fn_80123AC4(U*), fn_80123BF0(U*), fn_80123D1C(U*), fn_80123DC4(U*), fn_80123EF0(U*);
int fn_801BC1B0(void* self, Row* e, int col) {
    U* u = e->u;
    switch (col) {
    case 0: return SortKey(u);
    case 1: return fn_8012386C(u);
    case 2: return fn_80123998(u);
    case 3: return fn_80123AC4(u);
    case 4: return fn_80123BF0(u);
    case 5: return fn_80123D1C(u);
    case 6: return fn_80123DC4(u);
    case 7: return fn_80123EF0(u);
    }
    return 0;
}
void fn_801BC548(void* self, int col, int* a, int* b, int* c, int* d) {
    switch (col) {
    case 0: *b = 0; break;
    case 1: *b = 0x14; break;
    case 2: *b = 0x28; break;
    case 3: *b = 0x3C; break;
    case 4: *b = 0x50; break;
    case 5: *b = 0x64; break;
    }
    CELLEND;
}
extern u8 fn_80126B0C(U*);
extern s16 fn_801237EC(U*);
int fn_801BC654(void* self, Row* e, int col) {
    U* u = e->u;
    switch (col) {
    case 0: return SortKey(u);
    case 1: return -(int)u->xF0->xEC;
    case 2: return u->xFE;
    case 3: return fn_80126B0C(u);
    case 4: return u->x114;
    case 5: return fn_801237EC(u);
    }
    return 0;
}
extern char lbl_804CA8EC[4], lbl_804CA8E4[8], lbl_804CA8E0[4], lbl_804CA8DC[4], lbl_804CA8D8[4], lbl_804CA8D0[8], lbl_80389FA8[];
const char* fn_801BC740(char* buf, Row* e, int col) {
    U* u = e->u;
    switch (col) {
    case 0: return 0;
    case 1: return (const char*)fn_80118F00(u->xF0);
    case 2: fn_80290DDC(buf, lbl_804CA8EC, u->xFE); break;
    case 3:
        if (fn_80126B0C(u) == 0xFF) {
            fn_80290DDC(buf, lbl_804CA8E4);
        } else {
            fn_80290DDC(buf, lbl_804CA8E0, fn_80126B0C(u));
        }
        break;
    case 4: fn_80290DDC(buf, lbl_804CA8DC, u->x114); break;
    case 5: {
        int v = fn_801237EC(u);
        if (v >= u->xF0->x104) {
            fn_80290DDC(buf, lbl_80389FA8, 0x27, v, lbl_804CA8D8);
        } else {
            fn_80290DDC(buf, lbl_804CA8D0, v);
        }
        break;
    }
    }
    return buf;
}

static inline void Txt(int px, int r5, const void* s, f32 x, f32 y) { fn_801B5EB4(2, r5, (void*)s, 32.0f + (x + (f32)px), y); }
}
