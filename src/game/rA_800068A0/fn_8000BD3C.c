#include "game/rA_800068A0/types.h"

/* GAnim.c: resource acquire/release wrappers (fn_8023F1A4 = resource get,
 * fn_8023F1A8 = release, fn_8023F7B8/fn_8023F7EC = get/set resource flags;
 * flag 0x400000 marks the data as already relocated by fn_8000BC20). */

typedef struct GAnim GAnim;

typedef struct GChunk {
    u32 type;
    void* data;
    struct GChunk* next;
} GChunk;

typedef struct GEvent {
    s32 frame;
    u8 x4[0xC];
} GEvent;


typedef struct GLayer {
    struct GActor* actor;
    GAnim* anim;
    GEvent* cur;
    u8 idx;
    u8 pad[3];
} GLayer;

typedef struct GActor {
    u8 x0[0x74];
    struct GActor* child;
} GActor;

struct GAnim {
    GChunk* chunks;     /* 0x00 */
    void* x4;
    u8 nChunks;         /* 0x08 */
    u8 x9[3];
    u32 flags;          /* 0x0C */
    u8 x10[0xC];
    s32 nEvents;        /* 0x1C */
    GEvent* events;     /* 0x20 */
    void* x24;
    void* x28;
    void* x2C;
};

extern GAnim* fn_8023F1A4(void* res, u32 x);
#if TARGET_PC
extern FE10_PROTO void fn_8023F1A8(unsigned int);
#else
extern void fn_8023F1A8(void* res);
#endif
extern u32 fn_8023F7B8(void* res);
extern void fn_8023F7EC(void* res, u32 flags);
extern void fn_8000BC20(GAnim* an); /* GAnim_Relocate, see wip/ */
extern GAnim* fn_80007F10(GActor* a);
extern char lbl_80360B08[];
extern void fn_8001E008(const char* file, int line, const char* msg);

/* GAnim_Get */
GAnim* fn_8000BD3C(void* res) {
    GAnim* an;
    if (res == NULL) {
        an = NULL;
    } else {
        an = fn_8023F1A4(res, 0);
        if (!(fn_8023F7B8(res) & 0x400000)) {
            fn_8000BC20(an);
            fn_8023F7EC(res, 0x400000);
        }
    }
    return an;
}

/* GAnim_GetEx */
GAnim* fn_8000BDB0(void* res, u32 x) {
    GAnim* an;
    if (res == NULL) {
        return NULL;
    }
    an = fn_8023F1A4(res, x);
    if (!(fn_8023F7B8(res) & 0x400000)) {
        fn_8000BC20(an);
        fn_8023F7EC(res, 0x400000);
    }
    return an;
}

/* GAnim_Release */
void fn_8000BE20(GAnim* an) {
    fn_8023F1A8(an);
}

/* GActor_GetAnimLayers */
s32 fn_8000BE24(GActor* a, GLayer* out) {
    s32 n = 0;
    for (; a != NULL; a = a->child) {
        out[n].actor = a;
        out[n].anim = fn_80007F10(a);
        out[n].cur = out[n].anim->events;
        out[n].idx = 0;
        n++;
    }
    return n;
}

/* GAnim_PopNextEvents: finds the earliest pending event frame over all layers
 * and pops the events at that frame into out[]. Returns the frame or -1. */
s32 fn_8000BEA8(s32 n, GLayer* layers, GEvent** out) {
    s32 i;
    GLayer* l;
    GEvent* e;
    s32 best;
    best = 10000;
    l = layers;
    for (i = 0; i < n; i++, l++) {
        e = l->cur;
        if (e != NULL && e->frame < best) {
            best = e->frame;
        }
    }
    if (best == 10000) {
        return -1;
    }
    for (i = 0; i < n; i++, layers++, out++) {
        if (layers->cur == NULL || best != layers->cur->frame) {
            *out = NULL;
        } else {
            *out = layers->cur;
            layers->cur++;
            if (++layers->idx == layers->anim->nEvents) {
                layers->cur = NULL;
            }
        }
    }
    return best;
}
