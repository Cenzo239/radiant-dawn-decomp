/* Talk/event text system: state at lbl_804181AC and shared externs. */
#ifndef RL_TALK_H
#define RL_TALK_H
#include "game/rL_80133EB4/map3d.h"

extern "C" {

struct Talk {
    void* proc;        /* 0x000 */
    u32 str0;          /* 0x004 */
    u32 str1;          /* 0x008 */
    char* strp;        /* 0x00C */
    char* cur;         /* 0x010 */
    void* x14;         /* 0x014 */
    void* x18;         /* 0x018 */
    u8 slots[0x19C - 0x1C]; /* 0x01C: 16 of 0x18 bytes */
    s8 x19c[0x28];
    void* x1c4[8];     /* 0x1C4 */
    void* x1e4;        /* 0x1E4 */
    u8 x1e8;           /* 0x1E8 */
    u8 x1e9;           /* 0x1E9 */
    u8 x1ea;
    u8 x1eb;
    s16 x1ec;
    s16 x1ee;
    s16 x1f0;
    u8 x1f2;           /* 0x1F2 */
    u8 x1f3;
    u32 x1f4;
    u32 x1f8;
    u32 x1fc;
    s8 cur200;         /* 0x200 */
    s8 x201;
    s8 x202;
    s8 x203;
    s16 x204;
    s16 x206;
    u8* actor[5];      /* 0x208 */
    void* x21c[9];     /* 0x21C */
    void* x240;        /* 0x240 */
};

extern Talk lbl_804181AC;
extern u32 lbl_804CB878;
extern u32 lbl_804CB700;
extern u8 lbl_80418160[];
extern u8 lbl_80386A98[];
extern u8 lbl_80386C30[];
extern char lbl_804CA788[8];
extern char lbl_804CA790[8];

extern void* fn_80083B84(void*);
extern void fn_80083B78(void*);
extern void fn_80083DC4(void*, int);
extern void fn_80083174(void*);
extern void fn_80081A90(void*);
extern void* fn_8017F37C(const char*, const char*, const char*);
extern void* fn_800D4188(void*, void*);
extern void fn_800D3BCC(void*, int);
#if TARGET_PC
extern FE10_PROTO void * fn_80076F54(void*);
#else
extern int fn_80076F54(void*);
#endif
extern void fn_8014D350(u32*);
extern void fn_8014D220(u32*);
extern u8* fn_800C3558(void);
extern void fn_8014B650(void*);
extern u8 fn_800D3CF4(void*);
extern void fn_800C7114(void*, void*);
extern void fn_80151D28(void*, void*);
extern void fn_8014CF98(void);
extern void* fn_800D4228(void*);
extern void* fn_800811E4(void*, void*);
extern void fn_800D3C90(void*, int);
extern void fn_800C900C(int, int);
extern u32 fn_800C7FE8(void);
extern void fn_800C835C(int, int);
extern int fn_80068D74(void);
extern void fn_80068CBC(void);
extern void fn_80150F0C(void*);
extern void fn_800C71CC(void*, void*);
extern void fn_800C4240(void*);
extern int fn_8014D070(void*);

struct PT { u8 pad0[0x30]; Talk* t; };

struct Empty { Empty() {} char c; };
extern const char* fn_800D0864(const void*);
extern u32 strlen(const char*);
extern void fn_800250B0(u32*, int, u32, const char*, const char*, Empty);
extern void fn_80150C68(void*);
extern void fn_80006A2C(void*);
extern void fn_800D42A0(void*);
extern void fn_8014CFEC(void);
extern void fn_80068C08(void);
extern void fn_8014D364(u32*);
#if TARGET_PC
extern FE10_PROTO void fn_800DF6C8(ptr32<const void>);
#else
extern void fn_800DF6C8(void*);
#endif
extern void* lbl_804CB880;


extern void fn_8014D310(u32*);
extern void fn_8014EEEC(void*);
extern u8 lbl_80413F10[];
}
#endif
