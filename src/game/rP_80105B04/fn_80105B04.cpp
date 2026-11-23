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
void fn_80105DC0(TimeS* t, u32* h, u32* m, u32* s) {
    s64 v = t->ticks / (*(u32*)0x800000F8 / 4);
    u32 fr = (v * 3) / 2;
    *s = fr % 60;
    *m = (fr / 60) % 60;
    *h = fr / 3600;
}
void fn_80105EB0(SaveA* d, const SaveA* s);
u8 fn_80105F94(SaveA* s) {
    int n = 0;
    int i;
    for (i = 0; i < 0x1E; i++) {
        if (s->s12[i] == 0) break;
        n++;
    }
    return n + 1;
}
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
FHdr* fn_80106A6C(Bank* b, int id) {
    FHdr* h;
    int o;
    int i;
    i = 0;
    o = 0x2000;
    for (; i < 6; o += 0x4000, i++) {
        h = (FHdr*)(b->base + o);
        if (Valid(h) && id == h->x62) return h;
    }
    return 0;
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
void fn_801060FC(void** p, void* parent, void* cb) {
    *p = fn_80078D28(0, 0xFFFDA000, lbl_80367E9C, 0);
    if (lbl_804CB700 & 0x10) {
        fn_80106190(p);
    } else {
        NProc* n = fn_80081194(lbl_803856B8, parent);
        n->buf = *p;
        n->cb = cb;
    }
}
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
}
