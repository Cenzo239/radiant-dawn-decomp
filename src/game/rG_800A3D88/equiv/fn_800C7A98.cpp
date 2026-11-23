/* Round 20, functionally equal (check_regs.py: regs): fn_800C7A98. Self-contained: fn_800C725C.cpp with its exported bodies removed plus the function.
   Uses the four pooled file statics of fn_800C7850.cpp (same translation unit in the original; base ...bss.0 = lbl_803E7200,
   check_regs.py cannot verify that one reference, check_func.py --symbol-map ../fn_800C7850.symbols.json does). */
/* symcheck: (a) block 3: temporaries in other volatile registers, both sthx stores equal; leftover r3 at blr of a void function (clean with --ret=none). */
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


#pragma use_lmw_stmw off
/* ---- from rG_800A3D88/wip/fn_800C7850.cpp ---- */
/* The face cache at lbl_803E7200 is four file statics in the original (one pooled .bss base, per-array addi):
   res +0x00, key +0x20, del +0x40, ref +0x50. */
static void* sRes[8];
static void* sKey[8];
static s16 sDel[8];
static s16 sRef[8];
extern "C" {
void fn_800C7A98(void* name) {
    void* k = fn_800C3FD0(name);
    for (int i = 0; i < 8; i++) {
        if (k == sKey[i]) {
            sDel[i] = 2;
            sRef[i]--;
            return;
        }
    }
}
}
