#include "game/rC2_8005259C/base.h"
struct Rec { u8 b0, b1; u16 h2; u32 w4; s16 h8; s16 ha; int wc; };
struct GS { u8 pad[0x10]; u8 b10; u8 p11[0x543]; Rec recs[0x3c]; };
struct ChapD { const char* name; };
struct Ver { u8 pad[0x24]; u32 w24; };
struct CK { u8 pad[8]; u8 b8; };
struct UX { u8 pad[0xec]; void* ec; u8 pf0[4]; CK* f4; u8 pe[0x3f0 - 0xf8]; };
extern "C" {
extern GS lbl_803CAB38;
extern UX* lbl_804CB810;
extern char lbl_803620E4[116];
ChapD* fn_8010B094(u8);
Ver* fn_8024BC94(void);
int fn_8012D07C(int);
int fn_80290DDC(char*, const char*, ...);
u32 fn_8023F9F4(const char*);
void fn_80075D78(const char*);
void fn_8010C8EC(const char*, int);
void fn_800763E0(const char*);
void fn_8010E41C(void*, int);
void fn_80128E14(UX*, int);
void fn_801283F8(UX*);
}
static inline UX* unitAt(u8 id) {
    if (id) {
        return &lbl_804CB810[id - 1];
    }
    return 0;
}
static inline int firstFree(GS* g) {
    int i;
    for (i = 0; i < 0x3c; g = (GS*)((u8*)g + 0x10), i++) {
        if (g->recs[0].h2 == 0) {
            return i;
        }
    }
    return -1;
}

extern "C" void fn_80063858(void) {
    char a[0x20];
    char b[0x20];
    u8 buf[0x10];
    GS* g = &lbl_803CAB38;
    ChapD* c = fn_8010B094(g->b10);
    if (c && (fn_8024BC94()->w24 & 0x20000) && firstFree(g) == 0 && fn_8012D07C(5) == 0) {
        const char* s = lbl_803620E4;
        fn_80290DDC(a, s + 0x51, c->name);
        fn_80290DDC(b, s + 0x5c);
        if (fn_8023F9F4(b) != 0x40000) {
            fn_80075D78(b);
            fn_8010C8EC(a, -1);
            fn_800763E0(b);
        }
        fn_8010E41C(buf, 5);
        {
            u8* p = buf;
            int i;
            for (i = 1; i <= 0xfe; i++) {
                UX* u = unitAt(i);
                if (u->ec && p[u->f4->b8]) {
                    fn_80128E14(u, 0);
                    fn_801283F8(u);
                }
            }
        }
    }
}
