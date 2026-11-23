#include "game/rI_801DD7D4/fn_thp.h"
#pragma auto_inline off
struct P2 { u8 a, b; };
#define PC(i) lbl_8041F030.a1a[i].a = m->a1a[i].a; lbl_8041F030.a1a[i].b = m->a1a[i].b;
extern "C" {
struct RM { u32 a0; u16 a4, a6, a8, aa, ac, ae, a10; u8 p12[2]; u32 a14; u8 a18, a19; P2 a1a[12]; u8 a32[7]; };
extern RM lbl_8041F030;
extern RM lbl_803A03F8, lbl_803A0470, lbl_803A04AC, lbl_803A0434;
extern RM* lbl_804CBF28;
extern char lbl_803726A8[];
int VIGetTvFormat(void);
void OSPanic(const char*, int, const char*, ...);
void fn_80304638(RM*, RM*, int, int);
u32 OSGetMEM1ArenaLo(void);
u32 OSGetMEM1ArenaHi(void);
u32 OSGetMEM2ArenaLo(void);
u32 OSGetMEM2ArenaHi(void);
void OSSetMEM1ArenaLo(u32);
void OSSetMEM2ArenaLo(u32);
#if TARGET_PC
FE10_PROTO void* fn_8030E294(p32arg, u32, int);
#else
void* fn_8030E294(u32, u32, int);
#endif
void fn_8030ECF8(void*, void*, int);
void fn_800784E0(void);
void fn_800785FC(const char*, u32);
#if TARGET_PC
FE10_PROTO void * fn_8030ECD8(void*, u32);
#else
u32 fn_8030ECD8(void*, u32);
#endif
#if TARGET_PC
FE10_PROTO extern u32 lbl_804CBF20, lbl_804CBF2C, lbl_804CBF3C; FE10_PROTO extern void *lbl_804CBF30, *lbl_804CBF34;
#else
extern u32 lbl_804CBF20, lbl_804CBF30, lbl_804CBF2C, lbl_804CBF34, lbl_804CBF3C;
#endif
#if TARGET_PC
FE10_PROTO extern unsigned int lbl_804CBF40;
#else
extern void* lbl_804CBF40;
#endif
extern u8 lbl_8041F070[0x10], lbl_8041F080[0x10];
void fn_802352C8(void);
void DVDInit(void);
void fn_8032FAD0(void);
void fn_802F1AB0(void);
void fn_80235098(const RM*);
void* GXInit(u32, u32);
extern void* lbl_804CBF24;
void fn_80308090(f32,f32,f32,f32,f32,f32);
void fn_803080DC(int,int,u16,u16);
f32 fn_80304978(u16,u16);
int fn_80304BA8(f32 yscale);
void fn_80304770(int,int,u16,u16);
void fn_803047F0(u16,u16);
void fn_80304CEC(u8,void*,int,void*);
void fn_80304ED0(int);
void fn_80307854(int,int);
#if TARGET_PC
FE10_PROTO void fn_80304EE4(p32arg, int);
#else
void fn_80304EE4(u32,int);
#endif
void fn_803304B4(RM*);
#if TARGET_PC
FE10_PROTO void fn_803310B0(p32arg);
#else
void fn_803310B0(u32);
#endif
void fn_80330F9C(void);
void fn_80330018(void);
#if TARGET_PC
FE10_PROTO extern void *lbl_804CBF38;
#else
extern u32 lbl_804CBF38;
#endif
void fn_80234F1C(const RM* m) {
    u16 lines;
    DVDInit();
    fn_8032FAD0();
    fn_802F1AB0();
    fn_80235098(m);
    fn_802352C8();
    lbl_804CBF24 = GXInit(lbl_804CBF20, 0x80000);
    fn_80308090(0.0f, 0.0f, lbl_804CBF28->a4, lbl_804CBF28->a6, 0.0f, 1.0f);
    fn_803080DC(0, 0, lbl_804CBF28->a4, lbl_804CBF28->a6);
    lines = fn_80304BA8(fn_80304978(lbl_804CBF28->a6, lbl_804CBF28->a8));
    fn_80304770(0, 0, lbl_804CBF28->a4, lbl_804CBF28->a6);
    fn_803047F0(lbl_804CBF28->a4, lines);
    fn_80304CEC(lbl_804CBF28->a19, lbl_804CBF28->a1a, 1, lbl_804CBF28->a32);
    fn_80304ED0(0);
    if (lbl_804CBF28->a19) fn_80307854(2, 0); else fn_80307854(1, 0);
    fn_80304EE4(lbl_804CBF34, 1);
    fn_803304B4(lbl_804CBF28);
    fn_803310B0(lbl_804CBF30);
    lbl_804CBF38 = lbl_804CBF34;
    fn_80330F9C();
    fn_80330018();
    if (lbl_804CBF28->a0 & 1) fn_80330018();
}
}
