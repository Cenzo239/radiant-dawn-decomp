#ifndef RN_8025EEF0_CALLS_H
#define RN_8025EEF0_CALLS_H
/* Prototypes of functions outside the region, as far as this region's calls tell. */
#include "game/rN_8025EEF0/types.h"
extern "C" {
void fn_80083DC4(void* p, int label);     /* Proc_Goto */
void fn_80083B78(void* p);                /* Proc_Break */
void* fn_80083B84(void* cls);             /* Proc_Find */
void* fn_80081050(void* cls, void* parent);
void* fn_80081194(void* cls, void* parent);
void fn_80081A90(void* p);                /* Proc_End */
void fn_800846BC(void* cls);
#if TARGET_PC
FE10_PROTO void fn_8009E554(void* cls, void* parent);
#else
void* fn_8009E554(void* cls, void* parent);
#endif
void* fn_80078CCC(int size, const char* name, int a);  /* alloc */
void fn_80078E24(void* p);                /* free */
void fn_80079210(void* p);                /* operator delete */
u8* fn_8024BC94(void);                    /* current save data */
int fn_801D09F0(void);                    /* video mode / widescreen */
void fn_8023F1A0(const char* s, int a);   /* load archive */
int fn_8023F880(const char* s);           /* archive loaded? */
void fn_80006A2C(void* p);
void* fn_80075D78(const char* s);         /* load file */
void fn_800761F0(void* p);
void fn_8001D424(void* p);
#if TARGET_PC
FE10_PROTO void fn_803080DC(int x, int y, int w, int h); /* GX scissor */
#else
int fn_803080DC(int x, int y, int w, int h); /* GX scissor */
#endif
int fn_80291188(const char* a, const char* b); /* strcmp */
int fn_80290DDC(char* b, const char* f, ...);  /* sprintf */
#if TARGET_PC
FE10_PROTO p32ret fn_80085708(const char* s);
#else
int fn_80085708(const char* s);
#endif
const char* fn_800D0864(const char* s);   /* message lookup */
void fn_800CD4A4(int a);
void* fn_80060728(void* p);
void* fn_8006074C(void* p);
}
#endif
