#include "game/rG_800A3D88/types.h"
extern "C" {
extern u8 lbl_80382930[];
extern u8 lbl_803829D8[];
struct P { void* vt; u8 pad[0x14]; u32 m18; u8 pad1c[0xF]; u8 m2b; };
void fn_800893C4(P*);
void fn_80083E20(void*);

struct Q { u8 pad[0x36]; s16 m36; };
void fn_800C91C8(P*);
void fn_800C9230(Q* p) { p->m36 = 0; fn_80083E20(fn_800C91C8); }

extern int lbl_804CB6F4;
extern void* lbl_803E7260[6];
void fn_80077C4C(int);
#if TARGET_PC
FE10_PROTO void* fn_80077DB0(p32arg);
#else
void* fn_80077DB0(int);
#endif
void* fn_80077DD4();
void fn_800C9EC0() {
    if (lbl_804CB6F4 == 0) {
        fn_80077C4C(0);
        fn_80077DB0(0);
        lbl_803E7260[0] = fn_80077DD4();
        lbl_804CB6F4 = 1;
    }
}
}
extern "C" {
extern const f32 lbl_804CD5A0, lbl_804CD5D8, lbl_804CD5FC;
void fn_800068A0(void*, const char*);
void fn_80006A2C(void*);
struct Hold { void* p; void Set(const char* n) { fn_800068A0(this, n); } void Free() { fn_80006A2C(this); } };
struct Res { 
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual char* v6();
  void* volatile p;
 void Load() { if (p == NULL) fn_800068A0((void*)&p, v6()); }
 void Unload() { if (p != NULL) fn_80006A2C((void*)&p); }
};
extern u8 lbl_804CB6E0[8];
extern u8 lbl_804CB6E8[8];
extern Res* lbl_804CB6F0;
extern char* lbl_80382A20[6][2];
int fn_801D09F0();
void fn_8023F1A0(const char*, int);
void* fn_80079150(int);
void* fn_80077348(void*);
void fn_80077478(void*, const char*, int, int);
void fn_80077400(void*);
#define RA ((Res*)lbl_804CB6E0)
#define RB ((Res*)lbl_804CB6E8)
void fn_800C9F0C() {
    char** s = lbl_80382A20[1];
    int i;
    for (i = 1; i < 6; i++, s += 2) {
        fn_8023F1A0(s[fn_801D09F0()], 0xC80);
    }
    fn_8023F1A0(RA->v6(), 0x400);
    fn_8023F1A0(RB->v6(), 0x400);
}


int fn_800CAB40(char* s) {
    if (s[0] != '#') return 0;
    switch (s[1]) {
    case 'A': case 'B': case 'C': case 'F': case 'G': case 'I': case 'R': case 'S': case 'X': case 'Y':
        return 4;
    case 'P':
        return 5;
    case '#': case 'D': case 'E': case 'K': case 'O': case 'c': case 'e': case 'i': case 'k': case 'o': case 's': case 'x': case 'y':
        return 2;
    default: return -1;
    }
}
struct S92 { u8 pad[0x30]; u8 m30; u8 p31[3]; s16 m34; u8 p36[2]; f32 m38; f32 m3c; u8 p40[8]; void* m48; u8 m4c[8]; };
int fn_8030585C(int,int,int,int,int);
void* fn_80079958(int,int);
void DCInvalidateRange(void*,int);
void fn_80305A40(void*,void*,int,int,int,int,int,int);
void fn_80305C94(f32,f32,f32,void*,int,int,int,int,int);
#if TARGET_PC
FE10_PROTO void* fn_80081050(void*, p32arg);
#else
void* fn_80081050(void*,int);
#endif
extern u8 lbl_803829A0[];
void fn_800C92CC(S92* p) {
    int sz;
    p->m48 = 0;
    sz = fn_8030585C(0x260, 0x1C0, 4, 0, 0);
    if (p->m48 == 0) p->m48 = fn_80079958(sz, 0x40);
    DCInvalidateRange(p->m48, sz);
    fn_80305A40(p->m4c, p->m48, 0x260, 0x1C0, 4, 0, 0, 0);
    fn_80305C94(lbl_804CD5A0, lbl_804CD5A0, lbl_804CD5A0, p->m4c, 0, 0, 0, 0, 0);
    *(S92**)((u8*)fn_80081050(lbl_803829A0, 6) + 0x54) = p;
    p->m38 = lbl_804CD5D8;
    p->m3c = lbl_804CD5FC;
    p->m34 = 0;
    p->m30 = 0;
}
struct V986 { void* vt; void* m4; virtual void a0(); };
}
