/* fn_800C763C: functionally equal (regs, 9 of 17 words differ in registers only). Helpers from fn_800C725C.cpp (exported bodies removed), body from wip/fn_800C7850.cpp. */
#include "game/rG_800A3D88/types.h"

// Face fade processes and the shared face resource cache (lbl_803E7200).

#pragma auto_inline off

extern "C" {

extern u8 lbl_803828B0[];
extern u8 lbl_803828D0[];
extern u8 lbl_803828F8[];
extern u8 lbl_80382918[];
extern void* lbl_803E50D0[8];
extern u32 lbl_804CB700;
extern const f32 lbl_804CD560;
extern const f32 lbl_804CD588;

f32 fn_8017F68C(int, f32, f32, f32, f32);
void fn_80083B78(void*);
void* fn_80081050(void*, void*);
void* fn_80081194(void*, void*);
void fn_80081A90(void*);
void fn_800C3E70(void*, char*);
void fn_80006A2C(void*);
void* fn_800C3FD0(void*);
void fn_800068EC(void*, char*, int);
void fn_800C3EE0(void*, u16);
void fn_800C3F64(void*);

struct FaceX {
    u8 pad[0x40];
    u8 id;
    u8 m41;
    u8 m42;
};

struct FadeP {
    u8 pad[0x60];
    int idx;
    int n;
    int t;
    int from;
};
void fn_800C725C(FadeP* p);

FadeP* fn_800C7324(int idx, int n, void* parent);

void fn_800C73D0(FadeP* p);

void fn_800C7400(FadeP* p);


static inline void FaceFree(FaceX* f) {
    if (f != NULL) {
        void** s = &lbl_803E50D0[f->id];
        if (*s != NULL) {
            fn_80081A90(*s);
        }
        *s = NULL;
    }
}
void fn_800C74F0(FadeP* p);

FadeP* fn_800C755C(int idx, int n, void* parent);


struct DimP {
    u8 pad[0x30];
    int idx;
    int t;
    int n;
    int from;
    int to;
    int mode;
};
void fn_800C7680(DimP* p);

DimP* fn_800C777C(int idx, int to, int n, void* parent);


/* Face resource cache: up to 8 loaded faces */
struct FaceCache {
    void* res[8];
    void* key[8];
    s16 del[8];
    s16 ref[8];
};

extern FaceCache lbl_803E7200;


#pragma push
#pragma use_lmw_stmw on

#pragma pop

void fn_800C7B14();

void fn_800C7B18(void* name, int f);

void fn_800C7B50(void* name);


/* lbl_804CB6D4: pad/input state object */
struct PadS {
    u8 pad[0x30];
    u8 m30;
    u8 pad31;
    u16 m32;
};

extern PadS* lbl_804CB6D4;
u32 fn_800C7F90();

BOOL fn_800C7FA0();

BOOL fn_800C7FC4();

u16 fn_800C7FE8();

u8 fn_800C7FF4();


} // extern "C"


/* ---- from rG_800A3D88/wip/fn_800C7850.cpp ---- */
extern "C" {
// fn_800C763C 7/17 (r4/r5/r6 colours). fn_800C7850 size 0x9C vs 0xAC: loop unrolled over per-array base registers r5..r9.
// fn_800C78FC 36/40 and fn_800C79A0 50/59: need stmw and per-array induction pointers; structure right, registers not.
void fn_800C763C(DimP* p) {
    FaceX* f = (FaceX*)lbl_803E50D0[p->idx];
    p->t = 0;
    int v = f->m41;
    p->from = v;
    if (v < p->to) {
        p->mode = 0;
        return;
    }
    p->mode = 4;
}
}
