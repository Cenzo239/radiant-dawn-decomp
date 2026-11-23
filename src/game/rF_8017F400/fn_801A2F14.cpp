/* EXACT (round 23a): fn_801A2F14 alone, from wip/fn_801A2F14.cpp (fn_801A3104 and fn_801A3898 stay there); the shared zero is an s16 local. */
#include "game/rF_8017F400/types.h"
#pragma auto_inline off
#pragma use_lmw_stmw on
extern "C" {
/* illustration room (MIR_*) mode setup; global at lbl_804CB94C, same object as fn_801A3068.cpp */
typedef struct C4 { u8 r, g, b, a; } C4;
typedef struct IEnt { const char* a; const char* b; } IEnt;
typedef struct IG {
    void* res0; void* res4; void* res8; int xC;
    s16 x10, x12, x14, x16, x18, x1A, x1C, x1E;
    u8 x20; u8 pad21; u16 x22; f32 x24; s16 x28, x2A, x2C; u8 pad2E[2];
    IEnt* x30; char x34[0x60]; void* x94;
} IG;
extern IG* lbl_804CB94C;
extern char lbl_8036D10C[];
extern IEnt lbl_80388AA0[];
extern char lbl_804CA798[8];
extern void* fn_80078CCC(u32, void*, int);
extern void* fn_80179660(void*);
extern void fn_801798A8(void*, int);
extern const u8* fn_800CD204(int);
extern void fn_80179A58(void*, C4);
extern void fn_801C6EAC(const char*, const char*, char*);
extern void fn_800068A0(void*, const char*);
extern void fn_802639D0(void);
extern const char* fn_800D0864(const char*);
extern const char* fn_800CEC24(void);
extern const char* fn_800CEB4C(void);
extern const char* fn_800CF3A4(void);
extern const char* fn_800CF53C(void);
extern int fn_80290DDC(char*, const char*, ...);
extern void fn_80006A2C(void*);
extern char* strcpy(char*, const char*);
extern char* fn_80291110(char*, const char*);
#define STR(a) (lbl_8036D10C + (a) - 0x8036D10C)

void fn_801A2F14(void) {
    char path[0x60];
    IG* g = lbl_804CB94C;
    s16 z = 0;
    lbl_804CB94C->res8 = (void*)z;
    lbl_804CB94C->res4 = (void*)z;
    lbl_804CB94C->xC = z;
    lbl_804CB94C->x10 = z;
    lbl_804CB94C->x12 = -100;
    lbl_804CB94C->x14 = -100;
    lbl_804CB94C->x34[0] = z;
    g->x2A = z;
    g->x28 = z;
    g->x24 = z;
    g->x2C = z;
    {
    void* m = fn_80078CCC(0x2C, lbl_804CA798, 0);
    if (m) m = fn_80179660(m);
    lbl_804CB94C->x94 = m;
    }
    fn_801798A8(lbl_804CB94C->x94, 1);
    fn_80179A58(lbl_804CB94C->x94, *(C4*)fn_800CD204(4));
    lbl_804CB94C->x16 = 4;
    lbl_804CB94C->x18 = lbl_804CB94C->x12;
    lbl_804CB94C->x1A = lbl_804CB94C->x14;
    lbl_804CB94C->x1C = -100;
    lbl_804CB94C->x1E = -100;
    fn_801C6EAC(STR(0x8036D129), STR(0x8036D146), path);
    fn_800068A0(lbl_804CB94C, path);
    fn_802639D0();
}

}
