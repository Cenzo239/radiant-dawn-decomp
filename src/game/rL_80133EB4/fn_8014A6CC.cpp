/* Talk: open a text box slot, measuring the widest line of the script for the portrait's window. */
#include "game/rL_80133EB4/types.h"
#pragma use_lmw_stmw off

struct R9 { s16 a, b, c, d, e, f, g, h, i; };
struct Pos { s16 x, y, z; };
struct Portrait {
    u8 pad0[0x57];
    u8 x57;
    s16 x58, x5a;
    u8 pad5c[0x68 - 0x5C];
    s16 x68, x6a, x6c;
    u8 pad6e[0x74 - 0x6E];
    s16 x74, x76;
    u8 pad78[0x80 - 0x78];
    u8 x80;
    u8 pad81[2];
    u8 x83;
};
struct Actor {
    u8 pad0[0x41];
    u8 x41, x42;
};
struct Slot { u8 p[0x18]; };
struct TalkA {
    int x0;
    u8 pad4[0x10 - 4];
    u8* x10;
    void* x14;
    u8 pad18[0x1C - 0x18];
    Slot slots[16];
    s8 x19c[0x4C];
    u8 x1e8;
    u8 pad1e9[0x1F8 - 0x1E9];
    u32 x1f8;
    u8 pad1fc[4];
    s8 x200;
    u8 pad201;
    u8 x202;
    u8 pad203[0x208 - 0x203];
    Actor* actor[5];
    Portrait* x21c[9];
    Portrait* x240;
};

extern "C" {
extern u32 lbl_804CB700;
extern u32 lbl_804CB878;
extern Pos lbl_803E50F0[];
extern char* fn_80148728(u8**);
extern u8* fn_80077D44(u8*);
extern int fn_800CAD6C(u8**, int, f32);
extern int fn_801D09F0(void);
extern R9 fn_8022A174(int, int, int);
extern void fn_80150AFC(Portrait*, int, int);
extern void fn_80150AC0(Portrait*, int, int);
#if TARGET_PC
extern FE10_PROTO void fn_80151CC4(Portrait*, p32arg);
#else
extern void fn_80151CC4(Portrait*, int);
#endif
extern int fn_800C4020(Slot*);
extern Actor* fn_800C6118(Slot*, int, int, u32, int);
extern void fn_800C4104(Actor*, int, int, int);
extern u8 fn_800D3CF4(void*);
extern u32 fn_800C7FE8(void);
#if TARGET_PC
extern FE10_PROTO void fn_800C70BC(Actor*, p32arg);
#else
extern void fn_800C70BC(Actor*, int);
#endif

static inline int Hex(u8 c) {
    if ((s8)c >= '0' && (s8)c <= '9') return (s8)c - '0';
    if ((s8)c >= 'A' && (s8)c <= 'F') return (s8)c - 'A' + 10;
    if ((s8)c >= 'a' && (s8)c <= 'f') return (s8)c - 'a' + 10;
    return 0;
}
static inline void Place(TalkA* t, int k, const R9& v) {
    R9 r = v;
    t->x240->x68 = r.a;
    t->x240->x6a = r.b;
    t->x240->x6c = r.c;
    t->x240->x58 = r.d;
    t->x240->x5a = r.e;
    t->x240->x74 = r.f;
    t->x240->x76 = r.g;
    fn_80150AFC(t->x240, r.f, r.g);
    fn_80150AC0(t->x240, r.d, r.e);
    lbl_803E50F0[(s8)k].x = r.h;
    lbl_803E50F0[(s8)k].y = r.i;
}
static inline u8 Alpha(TalkA* t) {
    if (t->x14 && fn_800D3CF4(t->x14) && fn_800D3CF4(t->x14) != 0xFF) return fn_800D3CF4(t->x14);
    return 0xFF;
}

void fn_8014A6CC(TalkA* t, u8** cur) {
    /*P*/
    int k;
    int mx;
    int w;
    int on;
    u8* old;
    int dir;
    int i;
    /*E*/
    k = Hex((*cur)[1]);
    switch ((s8)(*cur)[2]) {
    case 'L':
        dir = -1;
        break;
    case 'R':
        dir = 1;
        break;
    case 'D':
        dir = 0;
        break;
    }
    t->x202 = k;
    s8 n = t->x202;
    if (t->x1e8 == 0) t->x240 = t->x21c[n];
    *cur += 3;
    for (i = 0; i < 5; i++) {
        if (t->actor[i]) continue;
        if (t->x1e8 == 0 && t->x240 && t->x240->x80 == 0) {
            if (t->x240->x83) {
                u8* s = t->x10;
                mx = -1;
                on = 1;
                for (;;) {
                    w = 0;
                    for (;;) {
                        u8 c = *s;
                        if ((s8)c == 0) goto done;
                        if ((s8)c == 10 || (s8)c == 16) {
                            switch ((s8)c) {
                            case 1:
                                s += 2;
                                break;
                            case 2:
                                s += 3;
                                break;
                            case 3:
                                s += 4;
                                break;
                            case 4:
                                s += 1;
                                fn_80148728(&s);
                                break;
                            case 5:
                                s += 1;
                                while (fn_80148728(&s)) {}
                                break;
                            case 7:
                            case 12:
                                s += 3;
                                break;
                            case 8:
                                s += 3;
                                break;
                            case 9:
                                s += 1;
                                break;
                            case 11:
                                s += 3;
                                break;
                            case 13:
                                s += 3;
                                break;
                            case 10:
                            case 16:
                            case 17:
                            case 18:
                                s += 1;
                                break;
                            }
                            break;
                        }
                        if ((s8)c == 7 || (s8)c == 12) on = (s8)s[2] - '0' == k;
                        old = *(u8* const*)&s;
                        switch ((s8)c) {
                        case 1:
                            s = old + 2;
                            break;
                        case 2:
                            s = old + 3;
                            break;
                        case 3:
                            s = old + 4;
                            break;
                        case 4:
                            s = old + 1;
                            fn_80148728(&s);
                            break;
                        case 5:
                            s = old + 1;
                            while (fn_80148728(&s)) {}
                            break;
                        case 7:
                        case 12:
                            s = old + 3;
                            break;
                        case 8:
                            s = old + 3;
                            break;
                        case 9:
                            s = old + 1;
                            break;
                        case 11:
                            s = old + 3;
                            break;
                        case 13:
                            s = old + 3;
                            break;
                        case 10:
                        case 16:
                        case 17:
                        case 18:
                            s = old + 1;
                            break;
                        }
                        if (old == s) {
                            if (on) {
                                w += fn_800CAD6C(&s, 2, 1.0f);
                            } else {
                                s = fn_80077D44(s);
                            }
                        }
                    }
                    if (mx < w) mx = w;
                }
            done:
                if (mx < w) mx = w;
                if (fn_801D09F0()) mx = 796.0f * (f32)mx / 608.0f;
                Place(t, k, fn_8022A174(k, mx + 0xE0, t->x21c[k]->x57));
            }
            fn_80151CC4(t->x240, t->x0);
        }
        if (lbl_804CB700 & 3) t->x1f8 = 0x300;
        if (fn_800C4020(&t->slots[t->x200]) == 0) t->x1f8 |= 0x8000;
        fn_800C4104(t->actor[i] = fn_800C6118(&t->slots[t->x200], 0, 0, t->x1f8, t->x0), (s8)k, dir, (lbl_804CB878 >> 21) & 1);
        u8 a;
        if (lbl_804CB878 & 1) {
            a = Alpha(t);
        } else {
            a = Alpha(t) - 0x4D;
        }
        t->actor[i]->x41 = a;
        if ((t->x1f8 & 0x100) == 0) {
            if (fn_800C7FE8() & 0xC) {
                t->actor[i]->x42 = 0xFF;
            } else {
                fn_800C70BC(t->actor[i], t->x0);
            }
        }
        t->x1f8 = 0x808;
        t->x19c[t->x200] = i;
        return;
    }
}
}
