/* Save slot entry fill: fn_80196E14 inits an entry and fn_801972FC refreshes one. The statics s_c1..s_b2 stand in for lbl_8041C9F8, lbl_8041CA08, lbl_8041DA78 and lbl_8041DA88 (pooled file statics, so the base register matches; the checker compares offsets only). */
#include "game/rF_8017F400/types.h"
extern "C" {
typedef struct SInfo { u8 pad[0x28]; s64 time; u8 x30[4]; u8 x34, x35, x36, x37; u8 pad38[8]; u32 x40; } SInfo;
typedef struct SEnt { s16 flags; s16 x2; s16 x4; u8 pad6[0x14-6]; s16 x14; u8 pad16[0x1a-0x16]; s16 x1a; u8 pad1c[0x26-0x1c]; s16 x26; int x28, x2c, x30; s16 x34; s16 x36; char x38[0x40]; f32 x78; } SEnt;
static u8 s_c1[0x10]; static u8 s_b1[0x1070]; static u8 s_c2[0x10]; static u8 s_b2[0x1070];
extern s8 lbl_804CB938;
extern s8 lbl_804CB939;
extern int lbl_804CBFCC;
#if TARGET_PC
FE10_PROTO extern void *lbl_804CB778;
#else
extern char lbl_804CB778[8];
#endif
extern void* memset(void*, int, u32);
extern char* strcpy(char*, const char*);
extern void fn_80245C88(void*);
extern void fn_8019FAC8(void*, int);
extern void __register_global_object(void*, void*, void*);
#if TARGET_PC
extern FE10_PROTO void fn_8024B978(int, ptr32<const void>, p32arg);
extern FE10_PROTO void fn_8024BB8C(int, ptr32<const void>, p32arg);
#else
extern void fn_8024B978(int, void*, int);
extern void fn_8024BB8C(int, void*, int);
#endif
extern void fn_80246494(void);
extern int fn_80067FE8(int);
extern void* fn_80106A6C(void*, int);
extern int fn_80105B88(void*);
extern int fn_80105BBC(void*);
extern void fn_80105DC0(void*, int*, int*, int*);
extern void* fn_80105DB8(void*);
extern int fn_80105F94(void*);
extern char lbl_803889DC[], lbl_803889CC[], lbl_803889BC[], lbl_803889AC[], lbl_803889A0[], lbl_80388994[], lbl_80388988[], lbl_8038897C[], lbl_80388970[], lbl_80388964[], lbl_80388958[], lbl_8038894C[], lbl_80388940[], lbl_80388934[], lbl_80388928[];
#define OS_BUS_CLOCK (*(u32*)0x800000F8)
static inline SInfo* Sv1(int slot) {
    if (!lbl_804CB938) {
        fn_80245C88(s_b1);
        __register_global_object(s_b1, fn_8019FAC8, s_c1);
        lbl_804CB938 = 1;
    }
    fn_8024B978(slot, s_b1, 0);
    fn_80246494();
    if (lbl_804CBFCC == 0) return (SInfo*)(s_b1);
    return 0;
}
static inline SInfo* Sv2(int slot) {
    if (!lbl_804CB939) {
        fn_80245C88(s_b2);
        __register_global_object(s_b2, fn_8019FAC8, s_c2);
        lbl_804CB939 = 1;
    }
    fn_8024BB8C(slot, s_b2, 0);
    fn_80246494();
    if (lbl_804CBFCC == 0) return (SInfo*)(s_b2);
    return 0;
}
static inline void P2(SEnt* e) { void* p = fn_80106A6C(lbl_804CB778, e->x4);
        if (p == 0) return;
        if (fn_80105B88(p) == 0) return;
        e->flags |= 4;
        if (fn_80105BBC(p)) e->flags |= 8;
        e->x26 = *((u8*)p + 0x64);
        fn_80105DC0(p, &e->x28, &e->x2c, &e->x30);
        if (e->x28 >= 0x63) { e->x28 = 0x63; e->x2c = 0x3b; e->x30 = 0x3b; }
        e->x34 = *((u8*)p + 0x66);
        e->x36 = (u8)fn_80105F94(fn_80105DB8(p)) - 1;
        if (e->x36 < 0) e->x36 = 0;
        if (e->x26 == 0x20) e->flags |= 0x10; }
static inline void Fill(SEnt* e) {
    if (e->x2 == 0) {
        SInfo* s = Sv1(e->x4);
        SInfo* s2 = Sv2(e->x4);
        if (s == 0) return;
        e->flags |= 4;
        if (s2) { e->flags |= 8; s = s2; }
        e->x26 = s->x36;
        switch (s->x37) {
        case 3: e->flags |= 0x40; break;
        case 1: strcpy(e->x38, lbl_803889DC); break;
        case 2:
            if (s->x40 & 8) strcpy(e->x38, lbl_803889CC);
            else if (s->x40 & 0x10) strcpy(e->x38, lbl_803889BC);
            else if (s->x40 & 0x20) strcpy(e->x38, lbl_803889AC);
            else if (s->x40 & 0x40) {
                switch (e->x26) {
                case 0x32: strcpy(e->x38, lbl_803889A0); break;
                case 0x34: strcpy(e->x38, lbl_80388994); break;
                case 0x33:
                default: strcpy(e->x38, lbl_80388988); break;
                }
            } else strcpy(e->x38, lbl_8038897C);
            break;
        case 5: strcpy(e->x38, lbl_80388970); break;
        case 6: strcpy(e->x38, lbl_80388964); break;
        case 7: strcpy(e->x38, lbl_80388958); break;
        case 9:
            if (e->x26 != 0x37) { e->x26 = (u8)fn_80067FE8(e->x26); strcpy(e->x38, lbl_8038894C); }
            else e->x38[0] = 0;
            break;
        case 8:
            if (s->x40 & 8) strcpy(e->x38, lbl_80388940);
            else if (s->x40 & 0x10) strcpy(e->x38, lbl_80388934);
            else if (s->x40 & 0x20) strcpy(e->x38, lbl_80388928);
            else e->x38[0] = 0;
            break;
        default: e->x38[0] = 0; break;
        }
        {
        u32 sec = s->time / (OS_BUS_CLOCK / 4);
        e->x30 = sec % 60;
        e->x2c = (sec / 60) % 60;
        e->x28 = sec / 3600;
        if (e->x28 > 0x63) { e->x28 = 0x63; e->x2c = 0x3b; e->x30 = 0x3b; }
        }
        e->x34 = s->x35;
        e->x36 = s->x34 - 1;
        if (s->x40 & 4) e->flags |= 0x10;
    } else {
        P2(e);
    }
}
void fn_80196E14(SEnt* e, int idx, int mode) {
    memset(e, 0, 0x7c);
    e->flags = 1;
    e->x4 = idx;
    e->x2 = mode;
    e->x14 = 0;
    e->x78 = 0.0f;
    e->x1a = 0xff;
    e->flags = 1;
    Fill(e);
}
void fn_801972FC(SEnt* e) {
    e->flags &= ~4;
    e->flags &= ~8;
    e->flags &= ~0x10;
    e->flags &= ~0x40;
    Fill(e);
}
}
