#ifndef RI_FE_H
#define RI_FE_H
/* Archive/file entry manager (0x802383F4..0x8023FBF4): the entry and its file statics.
   Names are guesses. Each file that uses the statics must keep this exact order. */
#include "game/rI_801DD7D4/fn_thp.h"
#include "game/rI_801DD7D4/vobj.h"
struct FE {
    void* vt;
    int a4;
    int a8;
    char name[0x3F];
    s8 a4b;
    u32 hash;
    volatile u32 flags;
    u16 rc;
    s8 a56;
    u8 p57;
    u32 a58;
    FE* parent;
    u32 data;
    u32 size;
    u32 pos;
    u8 task[0x98 - 0x6C];
    FE* a98;
};
#if TARGET_PC
/* Host: one shared copy defined in port/rvl-extra/os_min.cpp, sized for 64-bit
   pointers (MEMList, lock object with host vptr, OSThread). */
#define sA fe10_fe_sA
#define sB fe10_fe_sB
#define sPad fe10_fe_sPad
#define sLock fe10_fe_sLock
#define sQ1 fe10_fe_sQ1
#define sQ2 fe10_fe_sQ2
#define sThread fe10_fe_sThread
#define sStack fe10_fe_sStack
extern "C" {
extern u8 sA[0x20];
extern u8 sB[0x20];
extern u8 sPad[0x20];
extern u8 sLock[0x40];
extern u8 sQ1[0x40];
extern u8 sQ2[0x40];
extern u8 sThread[0x400];
extern u8 sStack[0x2000];
}
#else
extern "C" {
static u8 sA[0xC];
static u8 sB[0xC];
static u8 sPad[0xC];
static u8 sLock[0x1C];
static u8 sQ1[0x20];
static u8 sQ2[0x20];
static u8 sThread[0x318];
static u8 sStack[0x2000];
}
#endif
#endif
