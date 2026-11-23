/* fn_8000BC20 (GAnim_Relocate, 0x11C): exact (round m8). Turns the file offsets of an animation resource into pointers.
 * Self-contained: the types of fn_8000BD3C.c plus this function. In the chunk loop the chunk's data pointer is a named
 * block local (`void** d = c->data; d[1] = (u8*)d + 8;`): c then takes r3 and d r4. With the expression written out
 * twice (`((void**)c->data)[1] = (u8*)c->data + 8`) the two registers are exchanged. */
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
extern void fn_8023F1A8(void* res);
extern u32 fn_8023F7B8(void* res);
extern void fn_8023F7EC(void* res, u32 flags);
extern void fn_8000BC20(GAnim* an); /* GAnim_Relocate, see wip/ */
extern GAnim* fn_80007F10(GActor* a);
extern char lbl_80360B08[];
extern void fn_8001E008(const char* file, int line, const char* msg);

/* GAnim_Get */
GAnim* fn_8000BD3C(void* res);

/* GAnim_GetEx */
GAnim* fn_8000BDB0(void* res, u32 x);

/* GAnim_Release */
void fn_8000BE20(GAnim* an);

/* GActor_GetAnimLayers */
s32 fn_8000BE24(GActor* a, GLayer* out);

/* GAnim_PopNextEvents: finds the earliest pending event frame over all layers
 * and pops the events at that frame into out[]. Returns the frame or -1. */
s32 fn_8000BEA8(s32 n, GLayer* layers, GEvent** out);

#define RELOC(base, f) if ((base)->f != NULL) { (base)->f = (void*)((u32)(base)->f + (u32)(base)); }

/* GAnim_Relocate */
void fn_8000BC20(GAnim* an) {
    GChunk* c;
    if (an->flags & 8) {
        fn_8001E008(lbl_80360B08, 0x287, lbl_80360B08 + 0x5E);
    }
    RELOC(an, x4);
    RELOC(an, events);
    RELOC(an, x24);
    RELOC(an, x28);
    RELOC(an, x2C);
    if (an->nChunks < 1) {
        an->chunks = NULL;
    }
    if (an->chunks != NULL) {
        c = an->chunks = (GChunk*)((u32)an->chunks + (u32)an);
        while (c != NULL) {
            c->data = (void*)((u32)c->data + (u32)an);
            if ((s32)c->type != 13) {
                { void** d = (void**)c->data;
                d[1] = (u8*)d + 8; }
            }
            if (c->next != NULL) {
                c->next = (GChunk*)((u32)c->next + (u32)an);
            }
            c = c->next;
        }
    }
}

