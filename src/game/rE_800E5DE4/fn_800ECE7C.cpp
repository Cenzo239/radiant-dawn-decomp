#include "game/rE_800E5DE4/types.h"
#pragma auto_inline off
typedef struct BSeq { u8 b0; u8 b1; s16 kind; } BSeq;
typedef struct BtlProc { u8 pad[0x30]; BSeq* seq; } BtlProc;
typedef struct MAct { u8 pad[4]; Vec pos; } MAct;
typedef struct Ctl { u8 pad[4]; u16 h4; u8 pad6[0x62]; f32 m68[3][4]; u8 pad98[0xC]; BtlProc* a4; MAct* a8; MAct* aC; int b0; int b4; u8 padb8[0xC]; void* c4; } Ctl;
typedef struct Cmd { u8 pad[0x30]; Ctl* ctl; } Cmd;
extern "C" {
extern u8 lbl_803672A0[];
extern int fn_800E46C4(Cmd*, int);
extern int fn_801CFC58(BSeq*);
extern char* fn_800E1FA0(void*);
extern Cmd* fn_800E3810(char*, Cmd*);
extern void fn_800E5878(Cmd*, MAct*);
extern void fn_800FB228(void*, int);
extern void fn_800E4B20(Cmd*, int);
extern void fn_80313484(const Vec*, const Vec*, Vec*);
extern void fn_803134C4(const Vec*, Vec*);
extern void fn_803134A8(const Vec*, Vec*, f32);
extern void fn_80313460(const Vec*, const Vec*, Vec*);
#if TARGET_PC
extern FE10_PROTO int fn_800F42A0(MAct*, ptr32<const void>, Vec*);
#else
extern int fn_800F42A0(MAct*, const char*, Vec*);
#endif
extern void fn_80312654(f32 (*)[4], int, f32);
extern void fn_80312494(f32 (*)[4], f32 (*)[4]);
extern void fn_80312DB4(f32 (*)[4], const Vec*, Vec*);
extern void fn_8001EACC(Vec*, Vec*, f32 (*)[4]);
extern void fn_80312344(f32 (*)[4], f32 (*)[4]);
extern void fn_800E48C8(Cmd*, Vec);
extern void fn_800E4918(Cmd*, f32);
extern void fn_800E49AC(Cmd*, f32);
extern void fn_800E4A40(Cmd*, f32);
extern void fn_800E28E4(Cmd*);
void fn_800ECE7C(Cmd* c) {
    BtlProc* o = c->ctl->a4;
    MAct* a = c->ctl->a8;
    MAct* b = c->ctl->aC;
    int n = c->ctl->b4;
    Cmd* nc;
    switch (c->ctl->b0) {
    case 0x6E:
    case 0x6F:
        if (fn_800E46C4(c, 5)) {
            if (fn_801CFC58(o->seq)) {
                char* s = fn_800E1FA0(c->ctl->c4);
                if (s) {
                    nc = fn_800E3810(s, c);
                    if (nc) {
                        fn_800E5878(nc, a);
                        nc->ctl->h4 = c->ctl->h4;
                        c->ctl->h4 = 0;
                        break;
                    }
                }
            }
            c->ctl->h4 = 2;
            fn_800FB228(a, 0);
        }
        break;
    case 0x70:
        if (fn_800E46C4(c, 1)) {
            fn_800E4B20(c, -1);
        }
        break;
    }
    if (n == 3) {
        f32 m[3][4];
        Vec pa = a->pos;
        Vec pb = b->pos;
        Vec d;
        fn_80313484(&pb, &pa, &d);
        fn_803134C4(&d, &d);
        fn_803134A8(&d, &d, 0.5f);
        fn_80313460(&pb, &d, &pb);
        if (fn_800F42A0(a, (char*)lbl_803672A0 + 0x159, &pa)) {
            fn_80313484(&pb, &pa, &d);
            Vec up = {0.0f, 0.0f, 1.0f};
            fn_80312654(m, 0x58, 4.712389f);
            fn_80312494(m, m);
            fn_80312DB4(m, &d, &d);
            fn_8001EACC(&up, &d, m);
            fn_80312344(m, c->ctl->m68);
            fn_800E48C8(c, pa);
            fn_800E4918(c, 0.0f);
            fn_800E49AC(c, 0.0f);
            fn_800E4A40(c, 0.0f);
        }
    }
    fn_800E28E4(c);
}
}
