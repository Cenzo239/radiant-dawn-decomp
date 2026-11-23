#include "game/rG_800A3D88/types.h"

// Particle-model pool for a weapon trail process.
extern "C" {
struct PNode { PNode* next; PNode* prev; u8 mdl[0xA4 - 8]; };
struct Pool { PNode* items; PNode** free0; PNode** free; PNode* head; PNode* tail; int used; int n; };
struct EvI;
struct TrailP { u8 p[0x30]; EvI* m30; u8 p34[4]; void* m38; u8 p3c[0x4C - 0x3C]; f32 m4c; u8 p50[4]; u16 m54; u8 p56[2]; Pool* m58; };
extern char lbl_804CA450[4], lbl_804CA454[4], lbl_804CA458[4];
int fn_800AAC3C(EvI*);
f32 fn_800AAAF8(EvI*);
void* fn_800AABB4(EvI*);
void* fn_800A6578(void*, int);
#if TARGET_PC
FE10_PROTO void* fn_800E2408(p32arg);
#else
void* fn_800E2408(void*);
#endif
void* fn_80078CCC(int, const char*, int);
void DCFlushRange(void*, u32);
void fn_80006E94(void*);
void fn_80008F54(void*, int);
void fn_800E1FE0(void*, void*);
static inline Pool* Pool_New(int n) {
    Pool* l = (Pool*)fn_80078CCC(0x1C, lbl_804CA458, 0);
    if (l != NULL) {
        l->items = NULL;
        l->free0 = NULL;
        l->free = NULL;
        l->used = 0;
        l->head = NULL;
        l->tail = NULL;
    }
    return l;
}
static inline void Pool_Setup(TrailP* t) {
/*P*/
int j;
void* m;
int bytes;
int fs;
int o;
Pool* l;
int i;
/*E*/
    l = Pool_New(0);
    int n = t->m54;
    t->m58 = l;
    l->n = n;
    bytes = n * 0xA4;
    fs = (n + 1) * 4;
    l->items = (PNode*)fn_80078CCC(bytes, lbl_804CA454, 0);
    l->free0 = (PNode**)fn_80078CCC(fs, lbl_804CA450, 0);
    DCFlushRange(l->items, bytes);
    DCFlushRange(l->free0, fs);
    l->used = 0;
    for (i = 0; i < l->n; i++) {
        PNode* it = l->items;
        it[i].next = NULL;
        it[i].prev = NULL;
        l->free0[i] = &l->items[i];
    }
    l->free = l->free0;
    l->free0[l->n] = NULL;
    l->head = NULL;
    l->tail = NULL;
    for (j = 0, o = 0; j < t->m54; o += 0xA4, j++) {
        m = (u8*)t->m58->items + o + 8;
        fn_80006E94(m);
        fn_80008F54(m, 0x96);
        fn_800E1FE0(t->m38, m);
    }
}
#pragma use_lmw_stmw on
void fn_800AFC3C(TrailP* t) {
    if (!fn_800AAC3C(t->m30)) return;
    t->m4c = fn_800AAAF8(t->m30);
    void* a = fn_800A6578(fn_800AABB4(t->m30), 4);
    if (a == NULL) return;
    void* g = fn_800E2408(a);
    t->m38 = g;
    if (g == NULL) return;
    Pool_Setup(t);
}
}
