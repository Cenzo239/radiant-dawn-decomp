/* Talk script control-code interpreter (one script token per call). */
#include "game/rL_80133EB4/types.h"
#pragma use_lmw_stmw off
#pragma auto_inline off

struct Portrait {
    u8 pad0[0x70];
    int x70;
    u8 pad74[0x7B - 0x74];
    u8 x7b;
};
struct TalkI {
    int x0;
    u8 pad4[0x18 - 4];
    void* x18;
    u8 pad1c[0x19C - 0x1C];
    s8 x19c[0x10];
    u8 x1ac[0x1E4 - 0x1AC];
    void** x1e4;
    u8 pad1e8;
    u8 x1e9;
    u8 x1ea;
    u8 pad1eb;
    u16 x1ec;
    u16 pad1ee;
    u16 x1f0;
    u8 x1f2;
    u8 x1f3;
    u8 pad1f4[4];
    u32 x1f8;
    u8 pad1fc[4];
    s8 x200;
    u8 pad201;
    s8 x202;
    u8 pad203;
    s16 x204;
    s16 x206;
    u8 pad208[0x21C - 0x208];
    Portrait* x21c[9];
};
class Snd {
public:
    virtual void v0();
    virtual void v1();
    virtual int v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7(int);
};
class Inp {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual u32 v16();
};

extern "C" {
extern u32 lbl_804CB878;
extern u32 lbl_804CB700;
extern Inp* lbl_804CB5B8;
extern u8 lbl_80413F10[];

extern int fn_8014CA74(u32*, u32);
extern void fn_8014CA80(u32*, u32);
extern void fn_8014CA64(u32*, u32);
extern void fn_8014CA90(u32*, u32);
extern void fn_8014CAA0(void*, u32);
extern void fn_8014CAB0(void*, u32);
#if TARGET_PC
extern FE10_PROTO void fn_8014CAC0(p32arg);
#else
extern void fn_8014CAC0(int);
#endif
extern void fn_8014CAC4(void*, int);
extern void fn_8014CACC(void*);
extern void fn_8014CAD8(void*);
extern f32 fn_8014CAE4(void);
extern void fn_8014CF98(void);
#if TARGET_PC
extern FE10_PROTO ptr32<void> fn_8014A4C8(TalkI*);
#else
extern void* fn_8014A4C8(TalkI*);
#endif
extern Portrait* fn_8014A504(TalkI*);
#if TARGET_PC
extern FE10_PROTO ptr32<void> fn_8014A578(TalkI*);
#else
extern void* fn_8014A578(TalkI*);
#endif
extern int fn_8014A5A8(TalkI*, u8**);
extern void fn_8014A63C(TalkI*, u8**);
extern void fn_8014A6CC(TalkI*, u8**);
extern void fn_8014AD1C(TalkI*, u8*, int*, int*);
extern void fn_8014ADCC(TalkI*, int);
extern void* fn_8014ADEC(TalkI*);
extern void fn_8014AE04(TalkI*, u8**);
extern void fn_8014B0C8(TalkI*, u8**);
extern u8 fn_8014B1D8(TalkI*, void*);
extern char* fn_80148728(u8**);
extern int fn_80148858(u8**);
extern int fn_8014893C(s8);
extern void fn_8014EE88(void*);
#if TARGET_PC
extern FE10_PROTO void fn_80151548(void*, p32arg);
extern FE10_PROTO void fn_801520C0(void*, p32arg);
extern FE10_PROTO void fn_80151DE8(void*, p32arg, int);
extern FE10_PROTO void fn_80151F08(void*, p32arg, int);
extern FE10_PROTO void fn_801518C4(void*, p32arg);
#else
extern void fn_80151548(void*, int);
extern void fn_801520C0(void*, int);
extern void fn_80151DE8(void*, int, int);
extern void fn_80151F08(void*, int, int);
extern void fn_801518C4(void*, int);
#endif
extern void fn_801513B0(void*);
#if TARGET_PC
extern FE10_PROTO void fn_80151AA0(void*, p32arg, int);
#else
extern void fn_80151AA0(void*, int, int);
#endif
extern void fn_800C660C(void*, int, int);
extern int fn_800C7FA0(void);
extern void* fn_800D4228(void*);
extern void fn_800D3C30(void*, int);
extern void fn_800D3BCC(void*, int);
extern void fn_800C835C(int, int);
extern Snd* fn_8024F594(int);
#if TARGET_PC
extern FE10_PROTO int fn_802502E0(p32arg);
#else
extern int fn_802502E0(int);
#endif
extern void fn_80255E48(int, char*, f32);
extern void fn_80253EE4(char*, f32);
#if TARGET_PC
extern FE10_PROTO void* fn_800D4188(char*, p32arg);
#else
extern void* fn_800D4188(char*, int);
#endif
extern void fn_800D42A0(char*);
extern void fn_80094648(char*, int, int, int, int, int);
#if TARGET_PC
extern FE10_PROTO ptr32<void> fn_800DEAE8(char*);
extern FE10_PROTO void fn_800DF56C(ptr32<const void>, int);
#else
extern void* fn_800DEAE8(char*);
extern void fn_800DF56C(void*, int);
#endif
extern int fn_80291188(void*, void*);
extern void fn_802910CC(void*, void*, int);
extern void* fn_800C409C(int);

int fn_80149434(TalkI* t, u8** cur) {
    u8* p = *cur;
    switch ((s8)*p) {
    case 0:
        fn_8014CA80(&lbl_804CB878, 0x20);
        return 0;
    case 1: {
        *cur = p + 2;
        void* u = fn_8014A4C8(t);
        switch ((s8)(*cur)[-1]) {
        case 's':
            if (u) {
                fn_8014CAA0(u, 0x800);
                fn_8014CAB0(u, 0);
            } else {
                t->x1f8 &= ~0x800;
            }
            return 1;
        case 'a':
            if (u) {
                fn_8014CAA0(u, 0x800);
                fn_8014CAB0(u, 0x800);
            } else {
                t->x1f8 = (t->x1f8 & ~0x800) | 0x800;
            }
            return 1;
        case '*':
            if (fn_8014CA74(&lbl_804CB878, 2)) return 1;
            fn_8014CA80(&lbl_804CB878, 0x100);
        case '@':
            if (fn_8014CA74(&lbl_804CB878, 2)) return 1;
            fn_8014CAC0(t->x0);
            return 1;
        case 'H':
            if (fn_8014CA74(&lbl_804CB878, 2)) return 1;
            *cur -= 2;
            t->x1ec = 8;
            fn_8014CA80(&lbl_804CB878, 0x30);
            return 2;
        case 'g': {
            fn_8014CA80(&lbl_804CB878, 0x30000);
            Portrait* q = fn_8014A504(t);
            if (!q) q = t->x21c[0];
            q->x7b = 0;
            return 1;
        }
        case 'I':
            fn_8014CA80(&lbl_804CB878, 0x30000);
            return 1;
        case 'c':
            fn_8014CA80(&lbl_804CB878, 0xD0000);
            return 1;
        case 'S':
            fn_8014CA80(&lbl_804CB878, 0x10000);
            return 1;
        case 'P':
            fn_8014EE88(lbl_80413F10);
            fn_80151548(fn_8014A578(t), t->x0);
            return 2;
        case 'G':
            fn_801520C0(fn_8014A578(t), t->x0);
            return 2;
        case 'J':
            fn_8014CA80(&lbl_804CB878, 1);
            return 1;
        default:
            return 4;
        }
    }
    case 2: {
        u8* q = p + 3;
        *cur = q;
        switch ((s8)p[1]) {
        case 'w':
            t->x1ec = 8;
            if (fn_8014CA74(&lbl_804CB878, 0x200)) return 1;
            fn_80151DE8(fn_8014A578(t), t->x0, 1 << ((s8)(*cur)[-1] - '0'));
            return 2;
        case 'b':
            switch ((s8)q[-1]) {
            case 'f':
                fn_800C660C(fn_8014A4C8(t), 2, -1);
                return 1;
            case 's':
                fn_800C660C(fn_8014A4C8(t), 3, -1);
                return 1;
            case 'n':
                fn_800C660C(fn_8014A4C8(t), 1, -1);
                return 1;
            default:
                return 4;
            }
        case 'e': {
            void* u = fn_8014A4C8(t);
            switch ((s8)(*cur)[-1]) {
            case 'O':
                if (u) {
                    fn_800C660C(u, 1, 5);
                } else {
                    t->x1f8 = (t->x1f8 & ~6) | 6;
                }
                return 1;
            case 'o':
                if (u) {
                    fn_800C660C(u, 1, 1);
                } else {
                    t->x1f8 = (t->x1f8 & ~6);
                }
                return 1;
            case 'c':
                if (u) {
                    fn_800C660C(u, -1, 3);
                } else {
                    t->x1f8 = (t->x1f8 & ~6) | 2;
                }
                return 1;
            case 'h':
                if (u) {
                    fn_800C660C(u, 1, 4);
                } else {
                    t->x1f8 = (t->x1f8 & ~6) | 4;
                }
                return 1;
            default:
                return 4;
            }
        }
        case 'f':
            switch ((s8)q[-1]) {
            case '-':
                if (fn_8014CA74(&lbl_804CB700, 3)) return 1;
                if (t->x18) {
                    if (fn_800C7FA0()) {
                        fn_8014CAC4(fn_800D4228(t->x18), 0);
                        return 1;
                    }
                    fn_800D3C30(fn_800D4228(t->x18), 8);
                    return 2;
                }
                return 1;
            case '+':
                if (fn_8014CA74(&lbl_804CB700, 3)) return 1;
                if (t->x18) {
                    if (fn_800C7FA0()) {
                        fn_8014CAC4(fn_800D4228(t->x18), 0xFF);
                        return 1;
                    }
                    fn_800D3BCC(fn_800D4228(t->x18), 8);
                    return 2;
                }
                return 1;
            default:
                return 4;
            }
        case 'm':
            switch ((s8)q[-1]) {
            case 'o':
                t->x1f0 = 0x20;
                break;
            case 'c':
                t->x1f0 = 8;
                break;
            case 'd':
                t->x1f0 = 0;
                break;
            default:
                return 4;
            }
            return 1;
        case 's':
            switch ((s8)q[-1]) {
            case 'e':
                fn_8014CA64(&lbl_804CB878, 8);
                return 1;
            case 'd':
                fn_8014CA80(&lbl_804CB878, 8);
                return 1;
            default:
                return 4;
            }
        case 'F': {
            int k = t->x204;
            int n;
            if (fn_8014CA74(&lbl_804CB700, 2)) k = 0;
            switch ((s8)(*cur)[-1]) {
            case '0':
                n = 2;
                break;
            case '1':
                n = 3;
                break;
            case '2':
                n = 5;
                break;
            case '3':
                n = 6;
                break;
            default:
                return 4;
            }
            fn_800C835C(n, k);
            t->x1ea = 1;
            return 2;
        }
        case 'n':
            if (q[-1] == 'c') {
                fn_8014CA90(&lbl_804CB878, 0x40);
                return 1;
            }
        case 'v': {
            Snd* s = fn_8024F594((s8)fn_8014893C(q[-1]));
            if (s && s->v2()) {
                s->v7(0xFA);
                s->v1();
            }
            return 1;
        }
        case 'W':
            switch ((s8)q[-1]) {
            case 'O':
                fn_8014CA80(&lbl_804CB878, 0x1000);
                break;
            case 'X':
                fn_8014CA64(&lbl_804CB878, 0x1000);
                break;
            }
            return 1;
        case 'O':
            t->x1f3 = fn_8014893C(q[-1]);
            return 1;
        case 'V':
            if (q[-1] == 'W') {
                t->x1ec = 8;
                if (lbl_804CB5B8->v16() & 0x400) return 1;
                if (fn_802502E0(0)) {
                    *cur -= 3;
                    return 2;
                }
            }
            return 1;
        case 'B':
            switch ((s8)q[-1]) {
            case 'O':
                if (fn_8014CA74(&lbl_804CB700, 0x10) == 0) fn_8014CA80(&lbl_804CB878, 0x8000);
            }
            return 1;
        case 'K':
            if (q[-1] == 'H') {
                for (int i = 0; i < 9; i++) {
                    Portrait* q = t->x21c[i];
                    if (q) q->x70 = 0;
                }
                return 1;
            }
            return 4;
        case 'P': {
            void* u = fn_8014A4C8(t);
            switch ((s8)(*cur)[-1]) {
            case 'H':
                if (u) {
                    fn_8014CAA0(u, 0x60000);
                    fn_8014CAB0(u, 0x20000);
                } else {
                    t->x1f8 |= 0x20000;
                }
                return 1;
            case 'L':
                if (u) {
                    fn_8014CAA0(u, 0x60000);
                    fn_8014CAB0(u, 0x40000);
                } else {
                    t->x1f8 |= 0x40000;
                }
                return 1;
            }
        }
        default:
            return 4;
        }
    }
    case 3:
        *cur = p + 4;
        if (p[1] == 'D' && (*cur)[-2] == 'F' && (*cur)[-1] == 'C') {
            t->x1e9 = 0;
            fn_8014CA80(&lbl_804CB878, 8);
            return 1;
        }
        return 4;
    case 4:
        *cur += 1;
        switch ((s8)**cur) {
        case 'R':
            *cur += 1;
            return fn_8014A5A8(t, cur);
        case 'B':
            *cur += 1;
            fn_8014A63C(t, cur);
            fn_800C835C(t->x1f2, t->x204);
            return 1;
        case 'b':
            *cur += 1;
            fn_8014A63C(t, cur);
            return 1;
        case 'V': {
            int k = fn_8014893C((*cur)[1]);
            *cur += 2;
            char* s = fn_80148728(cur);
            if (fn_8014CA74(&lbl_804CB700, 3) == 0) fn_80255E48((s8)k, s, 0.0f);
            return 1;
        }
        case 'S':
            *cur += 1;
            if (fn_8014CA74(&lbl_804CB700, 3) == 0) fn_80253EE4(fn_80148728(cur), 0.0f);
            return 1;
        case 'N':
            *cur += 1;
            switch ((s8)**cur) {
            case 'F':
            {
                Portrait* q = t->x21c[fn_8014893C((*cur)[1])];
                if (q) fn_8014CACC(q);
                t->x1f8 = 0x300;
                fn_8014A6CC(t, cur);
                fn_80148728(cur);
                return 1;
            }
            default:
                return 4;
            }
        case 'F':
            *cur += 1;
            switch ((s8)**cur) {
            case 'T':
                *cur += 1;
                t->x204 = fn_80148858(cur);
                return 1;
            default:
                return 4;
            }
        case 'W': {
            *cur += 1;
            int n = fn_80148858(cur);
            t->x1ec = 8;
            n = (f32)n / fn_8014CAE4();
            fn_80151F08(fn_8014A578(t), t->x0, n);
            return 2;
        }
        case 's': {
            *cur += 1;
            f32 k = fn_8014CAE4();
            t->x206 = (f32)fn_80148858(cur) / k;
            return 1;
        }
        case 'r':
            *cur += 1;
            switch ((s8)**cur) {
            case 'b':
                *cur += 1;
                fn_800D4188(fn_80148728(cur), 0);
                return 1;
            case 'k':
                *cur += 1;
                fn_800D42A0(fn_80148728(cur));
                return 1;
            }
        default:
            return 4;
        }
    case 5: {
        *cur = p + 1;
        char* s = fn_80148728(cur);
        char c = *s;
        if (c == 'F' && s[1] == 'L') {
            fn_8014AE04(t, cur);
            return 1;
        }
        if (c == 'r' && s[1] == 'c') {
            char* a = fn_80148728(cur);
            int b = fn_80148858(cur);
            int d = fn_80148858(cur);
            int e = fn_80148858(cur);
            int f = fn_80148858(cur);
            int g = fn_80148858(cur);
            fn_80148728(cur);
            fn_80094648(a, b, d, e, f, g);
            return 1;
        }
        if (c == 'F' && s[1] == 'X') {
            char* a = fn_80148728(cur);
            int b = fn_80148858(cur);
            fn_80148728(cur);
            void* o = fn_800DEAE8(a);
            fn_800DF56C(o, b);
            *t->x1e4++ = o;
            return 1;
        }
        return 4;
    }
    case 12: {
#if TARGET_PC
        int old; /* host: C++ forbids the jump to case 7 over an initialisation */
        old = t->x200;
#else
        int old = t->x200;
#endif
        t->x200 = fn_8014893C(p[1]);
        t->x202 = fn_8014893C((*cur)[2]);
L:
        if (old != t->x200) fn_8014ADCC(t, t->x202);
        *cur += 3;
        return 1;
    case 7:
        old = t->x200;
        t->x200 = fn_8014893C(p[1]);
        t->x202 = fn_8014893C((*cur)[2]);
        if (fn_80291188(t->x1ac, fn_8014ADEC(t)) == 0) goto L;
        if (old != t->x200) {
            fn_8014CF98();
            fn_8014ADCC(t, t->x202);
            fn_801518C4(fn_8014A578(t), t->x0);
        }
        *cur += 3;
        fn_802910CC(t->x1ac, fn_8014ADEC(t), 0x18);
        return 1;
    }
    case 8:
        fn_8014893C(p[1]);
        fn_8014CAD8(fn_8014A578(t));
        fn_8014A6CC(t, cur);
        return 2;
    case 9:
        fn_8014B0C8(t, cur);
        return 2;
    case 14:
        fn_8014893C(p[1]);
        fn_8014CAD8(fn_8014A578(t));
        fn_8014A6CC(t, cur);
        return 1;
    case 15:
        fn_8014B0C8(t, cur);
        return 1;
    case 11:
        *cur = p + 3;
        return 1;
    case 13: {
        int a;
        int b;
        *cur += 3;
        fn_8014AD1C(t, *cur - 2, &a, &b);
        void* o = fn_800C409C((s8)a);
        if (o) t->x19c[t->x200] = fn_8014B1D8(t, o);
        return 1;
    }
    case 10:
        t->x1f3 = 1;
        *cur += 1;
        fn_8014EE88(lbl_80413F10);
        fn_801513B0(fn_8014A578(t));
        return 1;
    case 16:
        t->x1f3 = 1;
        *cur += 1;
        fn_8014EE88(lbl_80413F10);
        fn_801518C4(fn_8014A578(t), t->x0);
        return 2;
    case 17:
        *cur = p + 1;
        if (t->x1ec != 0x20) t->x1ec = 8;
        fn_80151AA0(fn_8014A578(t), t->x0, t->x206);
        return 2;
    case 18:
        *cur = p + 1;
        return 2;
    default:
        return 3;
    }
}
}
