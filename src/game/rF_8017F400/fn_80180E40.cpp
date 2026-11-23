#include "game/rF_8017F400/types.h"

#pragma auto_inline off

extern "C" {

typedef struct TrackOwner {
    u8 pad[0x30];
    Track* tracks; /* 0x30, new Track[8] */
} TrackOwner;

extern u8 lbl_80387CD0[];  /* process class descriptor for TrackOwner */
extern u8 lbl_803EC898[];  /* map data */
extern void* fn_80083B84(void* cls);          /* find process instance by class */
#if TARGET_PC
extern FE10_PROTO void* fn_80081050(void* cls, p32arg); /* create process instance */
#else
extern void* fn_80081050(void* cls, int arg); /* create process instance */
#endif
extern void fn_800846BC(void* cls);
extern f32 fn_801142F0(f32 x, f32 y, void* map); /* terrain height at x,y */
extern void fn_801804F8(Track* p, s32 key, const Vec& val);
extern void fn_80180598(Track* p, s32 x);
extern void fn_801805D4(Track* p);
extern void fn_80180C90(Track* t, u8 v);
extern void fn_80180C98(Track* t, const GXColor& c);
extern u32 lbl_804CB700;    /* skip / fast-forward flags */
extern u8 lbl_80387CF8[];   /* process class: EventArrowWait waiter */
extern void fn_80083B78(void* proc);            /* process: request delete */
extern void* fn_8009E898(void);
extern void* fn_80081194(void* cls, void* parent); /* create process with parent */
typedef struct ScriptCtx {
    u8 pad[0x1C];
    u8 waiting; /* 0x1C */
} ScriptCtx;
extern ScriptCtx* fn_800C3558(void);
extern void fn_800C3C3C(const char* name, void* func, int nargs); /* register script command */

static inline TrackOwner* GetTrackOwner(void)
{
    TrackOwner* o = (TrackOwner*)fn_80083B84(lbl_80387CD0);
    if (o == NULL) {
        o = (TrackOwner*)fn_80081050(lbl_80387CD0, 3);
    }
    return o;
}

Track* fn_80180E40(int idx)
{
    return &GetTrackOwner()->tracks[idx];
}

static inline BOOL Track_IsDone(Track* t)
{
    return t->unk10 >= t->unk18;
}

static inline BOOL AllTracksDone(TrackOwner* o)
{
    for (int i = 0; i < 8; i++) {
        Track* t = &o->tracks[i];
        if (!Track_IsDone(t)) {
            return FALSE;
        }
    }
    return TRUE;
}

/* any track still running? */
BOOL fn_80180E9C(void)
{
    TrackOwner* o = (TrackOwner*)fn_80083B84(lbl_80387CD0);
    if (o == NULL) {
        return FALSE;
    }
    if (AllTracksDone(o)) {
        return FALSE;
    }
    return TRUE;
}

void fn_80180FB8(void)
{
    fn_800846BC(lbl_80387CD0);
}

static inline Vec VecMake(f32 x, f32 y, f32 z)
{
    Vec v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

/* add key at time ms (converted to frames) to track idx at tile (x, y), height z (<= -1000: terrain) */
BOOL fn_80180FC4(int idx, int ms, int x, int y, int z)
{
    Track* t = fn_80180E40(idx);
    if (z <= -1000) {
        z = fn_801142F0(0.5f + x, 0.5f + y, lbl_803EC898) - 1.0f;
    }
    fn_801804F8(t, ms / 16.666666f, VecMake(0.5f + x, 0.5f + y, z));
    return TRUE;
}

BOOL fn_80181104(int idx, int ms)
{
    fn_80180598(fn_80180E40(idx), ms / 16.666666f);
    return TRUE;
}

BOOL fn_80181168(int idx)
{
    fn_801805D4(fn_80180E40(idx));
    return TRUE;
}

BOOL fn_80181190(void)
{
    fn_80180FB8();
    return TRUE;
}

BOOL fn_801811B4(int idx, int flag)
{
    fn_80180C90(fn_80180E40(idx), flag != 0);
    return TRUE;
}

static inline GXColor ColorMake(u8 r, u8 g, u8 b, u8 a)
{
    GXColor c;
    c.r = r;
    c.g = g;
    c.b = b;
    c.a = a;
    return c;
}

BOOL fn_801811F4(int idx, u8 r, u8 g, u8 b, u8 a)
{
    Track* t = fn_80180E40(idx);
    fn_80180C98(t, ColorMake(r, g, b, a));
    return TRUE;
}

/* waiter process update: dies when all arrows done */
void fn_80181268(void* proc)
{
    if (lbl_804CB700 & 0x8001) {
        fn_80083B78(proc);
    } else if (!fn_80180E9C()) {
        fn_80083B78(proc);
    }
}

/* EventArrowWait */
BOOL fn_801812B8(void)
{
    if (lbl_804CB700 & 0x8001) {
        return FALSE;
    }
    if (fn_80180E9C()) {
        fn_80081194(lbl_80387CF8, fn_8009E898());
        ScriptCtx* ctx = fn_800C3558();
        ctx->waiting = 1;
    }
    return TRUE;
}

/* this TU's pooled .rodata strings (@stringBase); referenced through the
   symbols.txt label because the checker resolves "@stringBase0" to another TU */
extern const char lbl_8036B654[];

/* register EventArrow script commands */
void fn_80181318(void)
{
    fn_800C3C3C(lbl_8036B654 /* "EventArrowAppend" */, (void*)fn_80180FC4, 5);
    fn_800C3C3C(lbl_8036B654 + 0x11 /* "EventArrowStart" */, (void*)fn_80181104, 2);
    fn_800C3C3C(lbl_8036B654 + 0x21 /* "EventArrowFocus" */, (void*)fn_801811B4, 2);
    fn_800C3C3C(lbl_8036B654 + 0x31 /* "EventArrowColor" */, (void*)fn_801811F4, 5);
    fn_800C3C3C(lbl_8036B654 + 0x41 /* "EventArrowFadeOut" */, (void*)fn_80181168, 1);
    fn_800C3C3C(lbl_8036B654 + 0x53 /* "EventArrowWait" */, (void*)fn_801812B8, 0);
    fn_800C3C3C(lbl_8036B654 + 0x62 /* "EventArrowDelete" */, (void*)fn_80181190, 0);
}

}
