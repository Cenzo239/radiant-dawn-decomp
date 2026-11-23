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

void fn_80105EB0(SaveA* d, const SaveA* s) {
    int i;
    d->w0 = s->w0;
    d->w4 = s->w4;
    *(u64*)&d->w8 = *(const u64*)&s->w8;
    d->x10 = s->x10;
    d->x44 = s->x44;
    d->x45 = s->x45;
    d->x46 = s->x46;
    d->x47 = s->x47;
    if (d->x48 == -1) d->x48 = s->x48;
    d->x4b = s->x4b;
    for (i = 0; i < 0x1E; i++) {
        d->s12[i] = s->s12[i];
    }
    d->w34 = 0;
    d->w38 = 0;
    d->w3c = 0;
    d->w40 = 0;
    d->w34 = s->w34;
    d->w38 = s->w38;
    d->w3c = s->w3c;
    d->w40 = s->w40;
}


}
