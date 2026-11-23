/* EXACT (round 23a): fn_8026AB7C, from equiv/fn_8026AB7C.cpp. introFind now takes the count and the row offset by reference from the caller (introFindR), with the caller declaring `int id; s16 n; int i; int ofs;` in that order. */
/* (older header) functionally equal (renamed). Helpers from ../fn_8026A724.cpp, body from wip/fn_8026A9D4.cpp */
/* Title-screen intro movies (FE10Intro.bin): procs that play character intro scenes. */
#include "game/rN_8025EEF0/types.h"

#pragma use_lmw_stmw on

extern "C" {

void* fn_80083B84(void* cls);
#if TARGET_PC
FE10_PROTO ptr32<void> fn_80011F0C(void);
#else
void* fn_80011F0C(void);
#endif
void* fn_80012308(void* a, void* b);
#if TARGET_PC
FE10_PROTO void fn_80022254(void* a, ptr32<const void>);
#else
void fn_80022254(void* a, void* b);
#endif
void* fn_80007F3C(void* a);
#if TARGET_PC
FE10_PROTO void fn_80014E24(void* a, const char* name, void* fn, p32arg);
#else
void fn_80014E24(void* a, const char* name, void* fn, int n);
#endif
u8 fn_80244D88(void);
void* fn_800E3810(const char* s, void* parent);
int fn_800E44CC(void);
void fn_80083B78(void* p);
void fn_80083DC4(void* p, int label);
void fn_800CD4A4(int a);
#if TARGET_PC
FE10_PROTO void* fn_800AAD1C(p32arg);
#else
void* fn_800AAD1C(int a);
#endif
void fn_800AAB14(void* a, int b);
void fn_800AAB8C(void* a, int b);
#if TARGET_PC
FE10_PROTO void fn_800AA4C0(void* a, p32arg, int c);
#else
void fn_800AA4C0(void* a, int b, int c);
#endif
void fn_80081A90(void* a);
void fn_800A99C4(void* scene);
void fn_8014C64C(void);
void fn_8001D424(void* p);
void fn_800761F0(void* p);
void fn_800763E0(const char* s);
void fn_800A8B70(void);
void fn_80252418(const char* s, f32 v);
void fn_80250E38(int a, f32 b, f32 c);
void fn_80250F0C(int a, f32 b, f32 c);
void fn_800B8810(void* p);
void fn_800B8154(void* p);

extern u8 lbl_80391E80[];
extern char lbl_8037307C[];

struct UnitAnimCmd {
    u8 pad[0x14];
    u8* u;  /* 0x14 */
};

static inline void* unitOf(void) {
    u8* p = (u8*)fn_80083B84(lbl_80391E80);
    if (p != 0) {
        return *(void**)(p + 0x70);
    }
    return 0;
}





void fn_8026A864(void*, void*, UnitAnimCmd* c);



struct IntroProc {
    u8 pad[0x54];
    u8 skip;     /* 0x54 */
    u8 m55;
    u8 m56;      /* 0x56 */
    u8 pad57[0x60 - 0x57];
    s16 t;       /* 0x60 */
    s16 dur;     /* 0x62 */
    u8 pad64[0x6C - 0x64];
    void* m6C;   /* 0x6C */
    void* m70;   /* 0x70 */
    u8* m74;     /* 0x74 */
    void* m78;   /* 0x78 */
};



struct ScriptObj { u8 pad[0x30]; u8* d; };



static inline void introSkip(IntroProc* p) {
    if ((lbl_804CB5B8->v48() & 0xFFF0) != 0) {
        p->skip = 1;
        fn_80083B78(p);
        if ((lbl_804CB5B8->v48() & 0x800) != 0) {
            fn_800CD4A4(4);
        } else {
            fn_800CD4A4(5);
        }
    }
}
















void* fn_80075D78(const char* s);
void* fn_8001D3B4(const char* s);
const char* fn_800D0DBC(const char* s);
void* fn_80177260(void* p);
void fn_800A8660(void);
u8* fn_80077064(const char* s);
int fn_80109A2C(void* p);
void* fn_80060728(void* p);
void fn_80109744(void* p);
void fn_801097FC(void* p);
#if TARGET_PC
FE10_PROTO int fn_800A64AC(p32arg);
#else
int fn_800A64AC(int a);
#endif
int fn_80290DDC(char* b, const char* f, ...);
void fn_800A947C(void* scene);
extern u8 lbl_803CAB38[];
extern u8 lbl_804CC038;

struct GameCfg { u32 f0 : 3; u32 mode : 2; u32 rest : 27; };

struct IntroEnt { u8 id; u8 pad[0x3F]; };
#define INTRO_NAME (lbl_8037307C + 0x3F)







static inline int introFindR(int i, int id, s16& n, int& ofs) {
    void* h;
    u8* t;
    h = fn_80077064(INTRO_NAME);
    n = (s16)fn_80109A2C(&h);
    ofs = i * 0x40;
    for (; i < n; ofs += 0x40, i++) {
        t = fn_80077064(INTRO_NAME) + 4;
        if (id == t[ofs]) {
            return i;
        }
    }
    return -1;
}

#pragma push
#pragma use_lmw_stmw off

#pragma pop

void fn_8026AB7C(u8* q) {
    int id;
    s16 n;
    int i;
    int ofs;
    i = *(s16*)(q + 0x5E) + 1;
    id = *(u16*)(q + 0x5C);
    i = introFindR(i, id, n, ofs);
    *(s16*)(q + 0x5E) = i;
    if ((s16)i < 0) {
        fn_80083DC4(q, 4);
    }
}


}
