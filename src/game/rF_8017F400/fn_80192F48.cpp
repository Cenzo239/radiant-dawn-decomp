#include "game/rF_8017F400/types.h"

#pragma auto_inline off

extern "C" {

/* fade/overlay process (class lbl_803885F0) */
typedef struct FadeProc {
    u8 pad[0x30];
    u16 flags;  /* 0x30 */
    s16 dir;    /* 0x32 */
    s16 speed;  /* 0x34 */
    s16 mode;   /* 0x36 */
    s16 alpha;  /* 0x38 */
} FadeProc;

extern u8 lbl_803885F0[];
extern void fn_801912E0(void* arg);
#if TARGET_PC
extern FE10_PROTO void fn_80177284(ptr32<const void>, void* arg); /* register draw callback */
#else
extern void fn_80177284(void (*func)(void*), void* arg); /* register draw callback */
#endif
extern void* fn_80083B84(void* cls);
extern void* fn_80081050(void* cls, void* parent);
extern void fn_800846BC(void* cls);

static inline FadeProc* Fade_Get(void)
{
    return (FadeProc*)fn_80083B84(lbl_803885F0);
}

void fn_80192F48(FadeProc* p)
{
    p->flags = 0;
    p->dir = 1;
    p->speed = 0;
    p->mode = 0;
    p->alpha = 0;
    fn_80177284(fn_801912E0, p);
}

void fn_80192F74(void)
{
}

void fn_80192F78(void* parent)
{
    if (Fade_Get() == NULL) {
        fn_80081050(lbl_803885F0, parent);
    }
}

void fn_80192FC8(void)
{
    fn_800846BC(lbl_803885F0);
}

void fn_80192FD4(void)
{
    FadeProc* f = Fade_Get();
    if (f != NULL) {
        f->dir = 0;
        f->mode = 2;
    }
}

void fn_80193014(void)
{
    FadeProc* f = Fade_Get();
    if (f != NULL) {
        f->dir = 1;
        f->mode = 0xE;
    }
}

void fn_80193054(void)
{
    FadeProc* f = Fade_Get();
    if (f != NULL) {
        f->dir = 1;
        f->mode = 0;
    }
}

void fn_80193094(void)
{
    FadeProc* f = Fade_Get();
    if (f != NULL) {
        f->dir = 0;
        f->speed = 8;
        f->alpha = 0xFF;
    }
}

void fn_801930DC(void)
{
    FadeProc* f = Fade_Get();
    if (f != NULL) {
        f->dir = 1;
        f->speed = 0;
        f->alpha = 0;
    }
}

void fn_80193120(void)
{
    FadeProc* f = Fade_Get();
    if (f != NULL) {
        f->flags |= 1;
    }
}

void fn_8019315C(void)
{
    FadeProc* f = Fade_Get();
    if (f != NULL) {
        f->flags &= ~1;
    }
}

}
