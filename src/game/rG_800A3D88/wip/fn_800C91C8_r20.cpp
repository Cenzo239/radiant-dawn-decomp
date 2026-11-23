/* Round 20 draft, NOT at a counted level (check_regs.py: other): fn_800C91C8. Self-contained, complete source. Instruction count ours 25 orig 26. What differs: same cause as fn_800C9084: the original forms the pool base lbl_80382930 once at entry and compares against addi r0,r5,0 / 0x80 / 0x70; also ends in b fn_800893C4; blr (26 vs 25 instructions). */
#include "game/rG_800A3D88/types.h"
extern "C" {
extern u8 lbl_80382930[];
extern u8 lbl_803829D8[];
struct P { void* vt; u8 pad[0x14]; u32 m18; u8 pad1c[0xF]; u8 m2b; };
void fn_800893C4(P*);
void fn_80083E20(void*);

struct Q { u8 pad[0x36]; s16 m36; };
void fn_800C91C8(P*);
void fn_800C9230(Q* p);


extern int lbl_804CB6F4;
extern void* lbl_803E7260[6];
void fn_80077C4C(int);
void* fn_80077DB0(int);
void* fn_80077DD4();
void fn_800C9EC0();

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

void fn_800C9F0C();

int fn_800CAB40(char* s);

struct S92 { u8 pad[0x30]; u8 m30; u8 p31[3]; s16 m34; u8 p36[2]; f32 m38; f32 m3c; u8 p40[8]; void* m48; u8 m4c[8]; };
int fn_8030585C(int,int,int,int,int);
void* fn_80079958(int,int);
void DCInvalidateRange(void*,int);
void fn_80305A40(void*,void*,int,int,int,int,int,int);
void fn_80305C94(f32,f32,f32,void*,int,int,int,int,int);
void* fn_80081050(void*,int);
extern u8 lbl_803829A0[];
void fn_800C92CC(S92* p);

struct V986 { void* vt; void* m4; virtual void a0(); };
}

#pragma use_lmw_stmw off
/* ---- from rG_800A3D88/wip/fn_800C9230.cpp ---- */
extern "C" {
// Near misses, see NOTES.md. Needs declarations from ../fn_800C9230.cpp.
void fn_800C91C8(P* p) {
    if (p->m2b == 0x7B) return;
    if (p->vt == lbl_803829D8) return;
    if (p->vt == lbl_80382930 + 0) return;
    if (p->vt == lbl_80382930 + 0x80) return;
    if (p->vt == lbl_80382930 + 0x70) return;
    if (p->m18 == 1) return;
    if (p->m18 == 7) return;
    fn_800893C4(p);
}
}
