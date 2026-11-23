/* fn_800ED4AC: exact (round m1). The effect spawn is an inline taking the actor as a parameter. */
/* fn_800ED4AC: battle sequence step. If the attacker's action 0x16 is due, spawns the map effect model
   named by fn_800E28AC at the attacker's position (one unit lower when the model is not flagged 0x80),
   then runs the hit and heal steps and returns whether the attacker's animation has finished. */
#include "game/rE_800E5DE4/types.h"
#pragma auto_inline off

typedef struct BSeq { u8 pad[2]; s16 kind; u8 pad4[5]; u8 b9; } BSeq;
typedef struct BtlProc {
    u8 pad[0x30];
    BSeq* seq;    /* 0x30 */
    Handle* h1;   /* 0x34 */
    Handle* h2;   /* 0x38 */
} BtlProc;
typedef struct MAct { u8 pad[4]; Vec pos; } MAct;
typedef struct MDef { u8 pad[8]; u16 flags; } MDef;
typedef struct Ctl { u8 pad[0xC4]; MDef* def; } Ctl;
typedef struct Cmd { u8 pad[0x30]; Ctl* ctl; } Cmd;

extern "C" {
extern BOOL fn_800D6114(Handle*, int);
extern BOOL fn_800D60C0(Handle*);
#if TARGET_PC
extern FE10_PROTO p32ret fn_800D6164(...);
#else
extern BOOL fn_800D6164(Handle*);
#endif
extern f32 fn_800D5F6C(Handle*);
extern void* fn_801CE474(Handle*);
extern char* fn_800E28AC(void*, int);
extern Cmd* fn_800E3810(char*, void*);
extern Vec fn_800F7790(MAct*);
extern void fn_800E48C8(Cmd*, Vec);
extern void fn_800E49AC(Cmd*, f32);
extern void fn_800ED100(BtlProc*);
extern BOOL fn_800ED24C(BtlProc*);
extern int fn_800FAFD4(MAct*, int);
extern int fn_800FAE98(MAct*);

static inline MAct* Act(Handle* h) { return h->obj ? (MAct*)h->obj->actor : 0; }
static inline Vec ActPos(MAct* a) { return a->pos; }
static inline int AnimBusy(BtlProc* p) {
    if (fn_800D6164(p->h1)) return 0;
    if (p->seq->b9 && fn_800FAFD4(Act(p->h1), 5)) return 1;
    return fn_800FAE98(Act(p->h1));
}
static inline Vec Get7790(MAct* a) { return fn_800F7790(a); }
static inline Vec ActPos2(MAct* a) { return ActPos(a); }
static inline void EffPos(Cmd* c, MAct* a) {
    Vec v;
    if (c->ctl->def->flags & 0x80) {
        Vec t = a->pos;
        v = t;
    } else {
        const Vec& t = fn_800F7790(a);
        v.x = t.x;
        v.y = t.y;
        v.z = t.z - 1.0f;
    }
    fn_800E48C8(c, v);
}
static inline void Spawn(BtlProc* p, MAct* a) {
        char* s = fn_800E28AC(fn_801CE474(p->h1), 0);
        if (s) {
            Cmd* c = fn_800E3810(s, p);
            if (c) {
                f32 f = fn_800D5F6C(p->h1);
                EffPos(c, a);
                fn_800E49AC(c, f);
            }
        }
}
BOOL fn_800ED4AC(BtlProc* p) {
    if (fn_800D6114(p->h1, 0x16)) {
        MAct* a = Act(p->h1);
        Spawn(p, a);
    }
    if (fn_800D60C0(p->h1)) {
        fn_800ED100(p);
    }
    fn_800ED24C(p);
    return AnimBusy(p) == 0;
}
}
