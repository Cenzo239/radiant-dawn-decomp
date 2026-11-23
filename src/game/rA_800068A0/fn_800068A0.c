#include "game/rA_800068A0/types.h"

/* Resource archive header ("magic" 0x0020AF31 means relocated). */
typedef struct ResEntryA {
    u16 h0;
    u16 h2;
    u32 p4;
    void* p8;
    u32 pC;
    u32 p10;
    u32 p14;
    u32 p18;
    f32 f1C;
    u8 b20;
    u8 b21;
    u8 b22;
    u8 relocated;
} ResEntryA;

typedef struct ResEntryB {
    u16 h0;
    u8 relocated;
    u8 pad3;
    u32 p4;
    void* p8;
} ResEntryB;

typedef struct ResPair {
    ResEntryA* a;
    ResEntryB* b;
} ResPair;

typedef struct ResHeader {
    u32 magic;
    u32 count;
    ResPair* table;
} ResHeader;

extern void* fn_8023F1A4(void* a, u32 b);
#if TARGET_PC
extern FE10_PROTO void fn_8023F1A8(unsigned int);
#else
extern void fn_8023F1A8(void* p);
#endif
extern void fn_80305A40(void* obj, void* p8, u16 h2, u16 h0, u32 p4, u32 pC, u32 p10, BOOL f);
extern void fn_80305C4C(void* obj, void* p8, u16 h2, u16 h0, u32 p4, u32 pC, u32 p10, BOOL f, u32 arg);
extern void fn_80305C94(void* obj, u32 p14, u32 p18, BOOL a, u8 b, BOOL c, f32 x, f32 y, f32 z);
extern void fn_80306018(void* obj, void* p8, u32 p4, u16 h0);
void fn_80006938(ResHeader* h);

void fn_800068A0(ResHeader** out, void* src) {
    ResHeader* h = (ResHeader*)fn_8023F1A4(src, 0);
    *out = h;
    if (h->magic != 0x20AF31) {
        fn_80006938(h);
    }
}

void fn_800068EC(ResHeader** out, void* src, u32 arg) {
    ResHeader* h = (ResHeader*)fn_8023F1A4(src, arg);
    *out = h;
    if (h->magic != 0x20AF31) {
        fn_80006938(h);
    }
}

void fn_80006938(ResHeader* h) {
    u16 i;
    h->magic++;
    h->table = (ResPair*)((u32)h->table + (u32)h);
    for (i = 0; i < h->count; i++) {
        if (h->table[i].a != NULL) {
            h->table[i].a = (ResEntryA*)((u32)h + (u32)h->table[i].a);
            if (h->table[i].a->relocated == 0) {
                h->table[i].a->p8 = (void*)((u32)h + (u32)h->table[i].a->p8);
                h->table[i].a->relocated = 1;
            }
        }
        if (h->table[i].b != NULL) {
            h->table[i].b = (ResEntryB*)((u32)h + (u32)h->table[i].b);
            if (h->table[i].b->relocated == 0) {
                h->table[i].b->p8 = (void*)((u32)h + (u32)h->table[i].b->p8);
                h->table[i].b->relocated = 1;
            }
        }
    }
}

ResPair* fn_80006A0C(ResHeader* h, u32 idx) {
    if (h->count <= idx) {
        idx = 0;
    }
    return &h->table[idx];
}

void fn_80006A2C(ResHeader** p) {
    fn_8023F1A8(*p);
    *p = NULL;
}

void fn_80006A64(ResHeader* h, void* obj, u32 idx) {
    ResEntryA* e = fn_80006A0C(h, idx)->a;
    f32 x = e->b21;
    f32 y = e->b22;
    BOOL f = 0;
    BOOL c = 0;
    BOOL a = 0;
    u8 b = e->b20;
    f32 z = e->f1C;
    if (e->b21 != e->b22) {
        f = 1;
        a = 1;
        b = 1;
        c = 0;
    }
    fn_80305A40(obj, e->p8, e->h2, e->h0, e->p4, e->pC, e->p10, f);
    fn_80305C94(obj, e->p14, e->p18, a, b, c, x, y, z);
}

void fn_80006B84(ResHeader* h, void* obj, void* obj2, u32 arg, u32 idx) {
    ResPair* pair = fn_80006A0C(h, idx);
    ResEntryA* e = pair->a;
    f32 x = e->b21;
    f32 y = e->b22;
    BOOL f = 0;
    BOOL c = 0;
    BOOL a = 0;
    u8 b = e->b20;
    f32 z = e->f1C;
    if (e->b21 != e->b22) {
        f = 1;
        a = 1;
        b = 1;
        c = 0;
    }
    fn_80306018(obj2, pair->b->p8, pair->b->p4, pair->b->h0);
    fn_80305C4C(obj, e->p8, e->h2, e->h0, e->p4, e->pC, e->p10, f, arg);
    fn_80305C94(obj, e->p14, e->p18, a, b, c, x, y, z);
}

BOOL fn_80006CC8(ResHeader* h, u32 idx) {
    return fn_80006A0C(h, idx)->b != NULL;
}
