#include "game/rE_800E5DE4/types.h"
#pragma auto_inline off
#pragma use_lmw_stmw on
typedef struct BSeq { u8 b0; u8 b1; s16 kind; } BSeq;
typedef struct Ctl { u8 pad[4]; s16 h4; u8 pad6[2]; s16 h8; u8 padA[0xE]; u32 flags; u8 pad1C[0x7C]; void* v98; void* v9C; void* vA0; } Ctl;
typedef struct Cmd { u8 pad[0x30]; Ctl* ctl; } Cmd;
typedef struct BtlProc {
    u8 pad[0x30];
    BSeq* seq;    /* 0x30 */
    Handle* h1;   /* 0x34 */
    Handle* h2;   /* 0x38 */
} BtlProc;
extern "C" {
#if TARGET_PC
extern FE10_PROTO char ** fn_801CE474(Handle*);
extern FE10_PROTO char* fn_800E28AC(p32arg, int);
#else
extern int fn_801CE474(Handle*);
extern char* fn_800E28AC(int, int);
#endif
extern Cmd* fn_800E3810(char*, BtlProc*);
extern void fn_800E461C(int);
extern void fn_800E4904(Cmd*, int, void*);
extern void fn_800E48F0(Cmd*, int, int);
extern void fn_800FB228(void*, int);
extern void fn_800ECD90(void* c);
extern void fn_800ECE7C(void* c);
extern void fn_800ED0E0(void* c);
static inline void* Act(Handle* h) { return h->obj ? h->obj->actor : 0; }
void fn_800ED100(BtlProc* p) {
/*P*/
    void* a;
    void* b;
    s16 kind;
    u8 b1;
    Cmd* c;
/*E*/
    a = Act(p->h1);
    b = Act(p->h2);
    c = fn_800E3810(fn_800E28AC(fn_801CE474(p->h1), 1), p);
    if (c) {
        fn_800E461C(1);
        kind = p->seq->kind;
        b1 = p->seq->b1;
        c->ctl->h8 = 500;
        c->ctl->v98 = fn_800ECD90;
        c->ctl->v9C = fn_800ECE7C;
        c->ctl->vA0 = fn_800ED0E0;
        c->ctl->flags |= 0x200;
        c->ctl->h4 = 1;
        fn_800E4904(c, 0, p);
        fn_800E4904(c, 1, a);
        fn_800E4904(c, 2, b);
        fn_800E48F0(c, 3, kind);
        fn_800E48F0(c, 4, b1);
        fn_800FB228(a, 1);
    }
}
}
