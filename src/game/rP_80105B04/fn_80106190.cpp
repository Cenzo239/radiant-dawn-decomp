/* Round 21 draft of fn_80106190 (writes three empty save-file headers), level
   `other`: complete and self-contained, 73 instructions against 76. Every
   store and constant is the original's. What differs: the original has a dead
   `li r3,0` after the constants (probably the high word of a 64-bit operand
   of the ticks-per-hour product) and keeps the first header pointer in a
   third saved register (r29, frame 0x20 against 0x10). Nine spellings of the
   64-bit product (operand order, s64/u64, an s64 field) gave the same code. */
#include "game/rP_80105B04/rp.h"
/* Save-file records. */
struct SlotArr { u8 pad[8]; u8 a[1]; };
struct SaveA {
    u32 w0, w4, w8, wC;
    u16 x10;
    u8 s12[0x1E];
    u8 pad30[4];
    u32 w34, w38, w3c, w40;
    u8 x44, x45, x46, x47;
    u8 x48;
    u8 pad49[2];
    u8 x4b;
};
extern "C" {
extern char lbl_80367E9C[];
extern u8 lbl_803856B8[];
extern u32 lbl_804CB700;
#if TARGET_PC
FE10_PROTO void fn_8028C0D0(void* a, void* d, int sz, int n);
#else
void* fn_8028C0D0(void* a, void* d, int sz, int n);
#endif
void fn_80111C24(void* p, int d);
void fn_80079210(void* p);
SlotArr* fn_80105B04(SlotArr* p, int d);
s64 fn_8028C418(s64 a, s64 b);
struct TimeS { u8 pad[0x58]; s64 ticks; };
void fn_80105EB0(SaveA* d, const SaveA* s);
struct Bank { u8* base; };
struct FHdr {
    u8 pad[0x40];
    u32 magic;
    u32 ver;
    u8 pad48[0x18];
    u8 x60, x61, x62, x63;
};
extern u8* lbl_804CB778;
static inline FHdr* At(Bank* b, int i) {
    return (FHdr*)(b->base + i * 0x4000 + 0x2000);
}
static inline BOOL Valid(FHdr* h) {
    if (h->magic != 0x4645384A) return 0;
    return h->ver == 0x20050201;
}
int fn_80105BBC(FHdr* h);
}
extern "C" {
void* fn_80078D28(int a, int n, const char* s, int b);
struct NProc { u8 pad[0x54]; void* buf; u8 pad58[8]; void* cb; };
NProc* fn_80081194(void* s, void* p);
void fn_80106190(void** p);
void* memset(void* p, int v, u32 n);
void fn_80079E70(int r);
struct SFile {
    u8 pad[0x40];
    u32 magic, ver, n;
    u8 pad4c[0xC];
    u32 tickHi, tickLo;
    u8 x60, x61, x62, x63, x64, x65, x66;
    u8 pad67 : 1;
    u8 lo : 7;
};
#define SF(p, o) ((SFile*)((u8*)(p) + (o)))
void fn_80106190(void** p);
void fn_80105EB0(SaveA* d, const SaveA* s);



}

/* ---- from build/tmp/r21small/rP/frag_fn_80106190.cpp ---- */
extern "C" {
extern "C" {
/* fn_80106190: 68 of 73 words: not solved. The constants are hoisted into r10..r12, r30 before the first block, so it probably stores them through locals */
void fn_80106190(void** p) {
    SFile* f;
    memset(*p, 0, 0x26000);
    f = SF(*p, 0x2000);
    f->magic = 0x4645384A;
    f->ver = 0x20050201;
    f->n = 1;
    f->x60 = 2;
    f->x62 = 0;
    f->x64 = 3;
    f->x65 = 4;
    f->x66 = 0;
    f->pad67 = 1;
    *(u64*)&f->tickHi = (u64)(*(u32*)0x800000F8 / 4) * 3600;
    f = SF(*p, 0x6000);
    f->magic = 0x4645384A;
    f->ver = 0x20050201;
    f->n = 2;
    f->x60 = 2;
    f->x62 = 1;
    f->x64 = 4;
    f->x65 = 4;
    f->x66 = 0;
    f->pad67 = 1;
    f = SF(*p, 0xA000);
    f->magic = 0x4645384A;
    f->ver = 0x20050201;
    f->n = 3;
    f->x60 = 2;
    f->x62 = 2;
    f->x64 = 5;
    f->x65 = 4;
    f->x66 = 0;
    f->pad67 = 1;
    fn_80079E70(0);
}
}
}
