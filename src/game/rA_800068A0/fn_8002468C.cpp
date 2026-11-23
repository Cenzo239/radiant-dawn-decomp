#include "game/rA_800068A0/types.h"

/* Help/sally screen widgets: virtual dispatch through the UI class hierarchy.
 * Slot names are the vtable offsets. */

struct VB { int x0; };

/* vptr at +4 (behind a plain data base). */
class VP4 : public VB {
public:
 virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C();
    virtual int v20(void*, void*); virtual int v24(void*, void*);
 virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34(); virtual int v38(); virtual int v3C(); virtual int v40(); virtual int v44(); virtual int v48(); virtual int v4C(); virtual s32 v50();
 virtual int v54(); virtual int v58(); virtual int v5C(); virtual int v60(); virtual int v64(); virtual int v68(); virtual int v6C(); virtual int v70(); virtual int v74(); virtual int v78(); virtual int v7C(); virtual int v80(); virtual int v84(); virtual int v88(); virtual int v8C(); virtual int v90();
};

/* vptr at +0. */
class VP0 {
public:
    virtual int v08();
    virtual int v0C();
    virtual int v10();
    virtual int v14();
    virtual int v18(void*);
    virtual int v1C();
    virtual int v20();
    virtual int v24();
    virtual int v28();
    virtual int v2C();
    virtual int v30(void*, void*);
    virtual int v34(void*, void*);
    virtual int v38(void*, void*);
    virtual int v3C();
    virtual int v40(void*, void*);
    virtual int v44();
    virtual int v48();
    virtual int v4C();
    virtual void v50(void*);
    virtual void v54(void*);
};

struct WinA {
    u8 pad[0x18];
    struct Sub { u8 pad[0x54]; u8 b54; }* p18;
    u8 pad1C[0x20];
    VP4* p3C;
    u8 b40[0x66];
    s8 sA6;
};

struct WinB {
    u8 pad[0x32];
    s16 s32;
    VP0* p34;
    u8 b38, b39, b3A;
};

extern "C" {

extern s32 fn_800CB0FC(int, f32);
#if TARGET_PC
extern FE10_PROTO s32 fn_800CA3DC(p32arg, int, f32);
#else
extern s32 fn_800CA3DC(int, int, f32);
#endif
extern void fn_8006F1B4(int, int, int);
extern void fn_800800D4(int);
extern void fn_80080330(f32, f32);
extern void fn_80080ABC(int, f32);
#if TARGET_PC
extern FE10_PROTO void fn_80080C24(p32arg);
#else
extern void fn_80080C24(int);
#endif
extern void fn_80080308(void);


/* Draws a window title centred over its frame (names guessed). */
void fn_8002468C(VP0* self, WinA* a, WinB* b) {
    s32 tw;
    s32 w;
    s16 h;
    w = a->p3C->v50();
    h = (0x1F - fn_800CB0FC(-1, 1.0f)) >> 1;
    tw = fn_800CA3DC(b->p34->v18(b), -1, 1.0f);
    fn_8006F1B4(0, b->s32, b->b38);
    self->v50(a);
    fn_800800D4(5);
    fn_80080330(((s16)w - tw) >> 1, h + b->s32);
    self->v54(b);
    fn_80080ABC(1, 2.0f);
    fn_80080C24(b->p34->v18(b));
    fn_80080308();
}

} /* extern "C" */
