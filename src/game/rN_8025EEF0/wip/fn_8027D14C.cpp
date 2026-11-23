/* NEAR MISS: registers only: temporaries take r31, should be r30 with m in r31. */
/* Conversation room setup (normal and FE8 data) */
#include "game/rN_8025EEF0/prim2d.h"

struct C4 { u8 r, g, b, a; };
struct RoomA { u8 pad[0x40]; s16 m40, m42, m44, m46; f32 m48, m4C, m50; s16 m54; u8 pad56[2]; void* m58; };
struct RoomB { s16 m[8]; };
struct RoomC { f32 m[8]; };
struct Bar { u8 pad[0x28]; void* vt; };

extern "C" {

extern u8* lbl_804CC06C;
extern u8* lbl_804CC074;
extern char lbl_8037359C[];
void* memset(void* p, int v, u32 n);
RoomA* fn_80272A14(void);
u8* fn_80272A8C(void);
f32* fn_80272B08(void);
void fn_80272FAC(int a, int b, int c);
void* fn_8027D784(int n);
void* fn_8027D790(void* p);
void fn_801798A8(void* p, int a);
C4* fn_800CD204(int i);
void fn_80179A58(void* p, C4* c);
void fn_801C6EAC(const char* a, const char* b, char* c);
void fn_800068A0(void* a, char* b);
void* fn_80076F54(const char* s);
void fn_80274A14(void);
void fn_802732FC(int a, int b, int c);
void fn_8027D6F8(void* p);
int fn_8027D700(void* p);
int fn_8027D728(void* p);
int fn_8027D708(void* p);
int fn_80272E3C(int id);
int fn_802401F4(void* p);
f32 fn_80272D58(void);
int fn_80272B84(void);

void fn_8027D14C(void) {
    char buf[0x60];
/*P*/
    int m4;
    int v;
    int i;
    int m;
    void* rr;
    int k;
    int off;
    s16 v1;
    s16 v2;
    u8* e;
    f32 c;
    f32 n;
/*E*/
    memset(lbl_804CC074, 0, 0xF4);
    *(s16*)(lbl_804CC074 + 0xEC) = 0xFF;
    fn_80272A14()->m48 = 304.0f;
    fn_80272A14()->m4C = 244.0f;
    fn_80272A14()->m50 = 1.0f;
    fn_80272FAC(-100, -100, 0);
    *(u8**)lbl_804CC074 = fn_8024BC94();
    {
        rr = fn_8027D784(0x2C);
        if (rr != 0) rr = fn_8027D790(rr);
        fn_80272A14()->m58 = rr;
    }
    fn_801798A8(fn_80272A14()->m58, 1);
    {
        C4 cc = *fn_800CD204(4);
        fn_80179A58(fn_80272A14()->m58, &cc);
    }
    fn_801C6EAC(lbl_8037359C + 0x101, lbl_8037359C + 0x12A, buf);
    fn_800068A0(lbl_804CC074 + 0x68, buf);
    fn_80075D78(lbl_8037359C + 0x13E);
    {
        int* f = (int*)fn_80076F54(lbl_8037359C + 0x150);
        *(int*)(lbl_804CC074 + 4) = *f;
        *(int**)(lbl_804CC074 + 8) = f + 1;
    }
    fn_80272A14()->m44 = 0x1B0;
    fn_80272A14()->m46 = 0xF8;
    { v1 = fn_80272A14()->m44; fn_80272A14()->m40 = -v1 / 2; }
    { v2 = fn_80272A14()->m46; fn_80272A14()->m42 = -v2 / 2; }
    fn_80272A14()->m54 = 0;
    *(s16*)(fn_80272A8C() + 0xC) = 5;
    {
        k = (s16)(fn_802401F4(*(u8**)(lbl_804CC074 + 8) + *(s16*)(fn_80272A8C() + 8) * 0x2C) - 1);
        m = *(s16*)(fn_80272A8C() + 0xC) * 2;
        *(s16*)(fn_80272A8C() + m) = k;
    }
    {
        f32 z = 0.0f;
        m4 = *(s16*)(fn_80272A8C() + 0xC) * 4;
        *(f32*)((u8*)fn_80272B08() + m4) = z;
    }
    {
        v = (int)fn_80272D58();
        int w = fn_80272B84();
        fn_802732FC(w, v, 0);
    }
    off = 0;
    c = 0.0f;
    n = 3.0f * (f32)*(int*)(lbl_804CC074 + 4);
    for (i = 0; i < *(int*)(lbl_804CC074 + 4); off += 0x2C, i++) {
        e = *(u8**)(lbl_804CC074 + 8) + off;
        if (fn_80272E3C(fn_8027D700(e)) != 0) c += 1.0f;
        if (fn_80272E3C(fn_8027D728(e)) != 0) c += 1.0f;
        if (fn_80272E3C(fn_8027D708(e)) != 0) c += 1.0f;
    }
    *(int*)(lbl_804CC074 + 0xF0) = (int)(100.0f * (c / n));
}

}
