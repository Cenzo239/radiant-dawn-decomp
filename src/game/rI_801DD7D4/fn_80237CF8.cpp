/* THP video decode thread: file statics at lbl_80421DB0. */
#include "game/rI_801DD7D4/fn_thp.h"
#pragma auto_inline off

extern "C" {
static u8 sThread[0x318];
static u8 sStack[0x1000];
static u8 sQ1[0x20];
static u8 sQ2[0x20];
static u32 mQ1[3];
static u32 mQ2[3];
void fn_80237E24(void*);
void fn_80237EF0(void*);
extern int lbl_804CBF78;
extern int lbl_804CBF7C;
struct RB { int* ptr; int frame; };
#if TARGET_PC
FE10_PROTO ptr32<RB> fn_80237C68(void);
FE10_PROTO ptr32<RB> fn_80237CB0(void);
FE10_PROTO void fn_80237C9C(ptr32<const void>);
#else
RB* fn_80237C68(void);
RB* fn_80237CB0(void);
void fn_80237C9C(RB*);
#endif
int fn_80238020(RB*);

/* CreateVideoDecodeThread */
int fn_80237CF8(int prio, void* mem) {
    if (mem != NULL) {
        if (fn_8031FC48(sThread, fn_80237EF0, mem, sStack + 0x1000, 0x1000, prio, 1) == 0) {
            return 0;
        }
    } else {
        if (fn_8031FC48(sThread, fn_80237E24, 0, sStack + 0x1000, 0x1000, prio, 1) == 0) {
            return 0;
        }
    }
    fn_8031D224(sQ1, mQ1, 3);
    fn_8031D224(sQ2, mQ2, 3);
    lbl_804CBF78 = 1;
    lbl_804CBF7C = 1;
    return 1;
}
void fn_80237DCC(void) {
    if (lbl_804CBF78 != 0) {
        fn_803202B0(sThread);
    }
}
/* VideoDecoder */
void fn_80237E24(void*) {
    RB* b;
    int skip = 0;
    for (;;) {
        if (lbl_80420420.a7 != 0) {
            while (skip != 0) {
                b = fn_80237CB0();
                {
                    u32 f = (b->frame + lbl_80420420.c0) % lbl_80420420.a50;
                    if (f == lbl_80420420.a50 - 1 && !(lbl_80420420.a6 & 1)) {
                        fn_80238020(b);
                    }
                }
                fn_80237C9C(b);
                lbl_80420420.d8++;
                skip--;
            }
        }
        if (lbl_80420420.a7 != 0) {
            b = fn_80237CB0();
        } else {
            b = fn_80237C68();
        }
        skip = fn_80238020(b);
        fn_80237C9C(b);
    }
}
/* VideoDecoderForOnMemory */
#pragma push
#pragma use_lmw_stmw on
void fn_80237EF0(void* mem) {
    RB rb;
    int size;
    int frame = 0;
    int skip = 0;
    rb.ptr = (int*)mem;
    size = lbl_80420420.bc;
    for (;;) {
        if (lbl_80420420.a7 != 0) {
            while (skip != 0) {
                u32 f;
                skip--;
                lbl_80420420.d8++;
                f = (frame + lbl_80420420.c0) % lbl_80420420.a50;
                if (f == lbl_80420420.a50 - 1) {
                    if (!(lbl_80420420.a6 & 1)) break;
                    size = *rb.ptr;
                    rb.ptr = (int*)lbl_80420420.b4;
                } else {
                    int n = *rb.ptr;
                    rb.ptr = (int*)((u8*)rb.ptr + size);
                    size = n;
                }
                frame++;
            }
        }
        rb.frame = frame;
        skip = fn_80238020(&rb);
        {
            u32 f = (frame + lbl_80420420.c0) % lbl_80420420.a50;
            if (f == lbl_80420420.a50 - 1) {
                if (lbl_80420420.a6 & 1) {
                    size = *rb.ptr;
                    rb.ptr = (int*)lbl_80420420.b4;
                } else {
                    fn_80320548(sThread);
                }
            } else {
                int n = *rb.ptr;
                rb.ptr = (int*)((u8*)rb.ptr + size);
                size = n;
            }
        }
        frame++;
    }
}
/* VideoDecode */
int fn_8032A274(void*, void*, void*, void*, void*);
#if TARGET_PC
FE10_PROTO void fn_80236A48(p32arg);
#else
void fn_80236A48(int);
#endif
struct TS { void* y; void* u; void* v; int frame; };
static inline TS* popFreeTS(void) {
    TS* m;
    fn_8031D34C(sQ1, &m, 1);
    return m;
}
int fn_80238020(RB* rb) {
    TS* ts;
    u32 i;
    u32* sizes;
    u8* ptr;
    int ret = 0;
    sizes = (u32*)((u8*)rb->ptr + 8);
    ptr = (u8*)rb->ptr + lbl_80420420.a6c * 4 + 8;
    ts = popFreeTS();
    for (i = 0; i < lbl_80420420.a6c; i++) {
        switch (lbl_80420420.a70[i]) {
        case 0:
            if ((lbl_80420420.ac = fn_8032A274(ptr, ts->y, ts->u, ts->v, lbl_80420420.a9c)) != 0) {
                if (lbl_804CBF7C != 0) {
                    fn_80236A48(0);
                    lbl_804CBF7C = 0;
                }
                fn_80320548(sThread);
            }
            ts->frame = rb->frame;
            fn_8031D284(sQ2, ts, 1);
            {
                int d = lbl_80420420.d8;
                int t = lbl_80420420.f0 + 1;
                ret = d < t ? t - d : 0;
                lbl_80420420.d8 = d + 1;
            }
            break;
        }
        ptr += *sizes;
        sizes++;
    }
    if (lbl_804CBF7C != 0) {
        fn_80236A48(1);
        lbl_804CBF7C = 0;
    }
    return ret;
}
#pragma pop
}
