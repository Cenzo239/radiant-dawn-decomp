#include "game/rE_800E5DE4/types.h"
#pragma auto_inline off

typedef struct BSeq { u8 pad[2]; s16 kind; } BSeq;
typedef struct BtlProc {
    u8 pad[0x30];
    BSeq* seq;    /* 0x30 */
    Handle* h1;   /* 0x34 */
    Handle* h2;   /* 0x38 */
    void* v3C;    /* 0x3C */
    u8 b40;       /* 0x40 */
} BtlProc;

extern "C" {
extern BOOL fn_801CFCE0(BSeq*);
extern BOOL fn_801CFC0C(BSeq*);
extern void fn_800EBB74(BtlProc*);
extern void fn_800EB988(BtlProc*);
extern void fn_800EBE80(BtlProc*);
extern void fn_800EFEB8(Handle*, int, BtlProc*);
extern Vec fn_800D5C44(Handle*);
extern void fn_800EE61C(const Vec&, int, BtlProc*);
extern void* fn_80103234(void*, int, int, void*);

static inline void* HandleActorX(Handle* h) { return h->obj ? h->obj->actor : 0; }
static inline void Pop(const Vec& v, int n, BtlProc* p) {
    Vec w = v;
    fn_800EE61C(w, n, p);
}

void fn_800ED7E4(BtlProc* p) {
    switch (p->seq->kind) {
    case 0x6E:
    case 0x6F:
        if (fn_801CFCE0(p->seq)) {
            fn_800EBB74(p);
            break;
        }
        fn_800EB988(p);
        if (fn_801CFC0C(p->seq)) {
            s16 n = p->h1->unkE;
            if (n) {
                fn_800EFEB8(p->h1, n, p);
                if (p->b40 != 2) {
                    Pop(fn_800D5C44(p->h1), n, p);
                }
                fn_80103234(HandleActorX(p->h1), 1, 0x20, p);
            }
        }
        break;
    case 0x70:
        fn_800EBE80(p);
        break;
    }
}
}
