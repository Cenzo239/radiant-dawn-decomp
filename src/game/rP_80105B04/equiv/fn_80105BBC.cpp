/* fn_80105BBC: true when a valid suspend save exists whose owner is the save
   file h. Level: regs (loop counter and offsets in other volatile registers).
   Rewritten: the old near.cpp attempt had the lookup nested the wrong way; it
   is two nested search inlines that return the entry or NULL. */
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
void* fn_8028C0D0(void* a, void* d, int sz, int n);
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

/* ---- from build/tmp/r21small/rP/frag_fn_80105BBC.cpp ---- */
extern "C" {
extern "C" {
/* The save buffer holds six 0x4000-byte chapter saves from +0x2000 and two
   0x6000-byte suspend saves from +0x1A000. */
static inline FHdr* FindFile(u8* base, int id) {
    int o;
    int i;
    for (i = 0, o = 0x2000; i < 6; o += 0x4000, i++) {
        FHdr* f = (FHdr*)(base + o);
        if (Valid(f) && id == f->x62) return f;
    }
    return 0;
}
static inline FHdr* FindSuspend(u8* base) {
    int j;
    u32 o = 0x1A000;
    for (j = 0; j < 2; j++, o += 0x6000) {
        FHdr* c = (FHdr*)(base + o);
        if (Valid(c)) {
            if (FindFile(base, c->x63)) return c;
        }
    }
    return 0;
}
/* True when the valid suspend save belongs to the file h. */
int fn_80105BBC(FHdr* h) {
    FHdr* g;
    if (!Valid(h)) return 0;
    if (h->x60 != 2) return 0;
    g = FindSuspend(lbl_804CB778);
    if (g == 0) return 0;
    return g->x63 == h->x62;
}
}
}
