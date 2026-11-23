#ifndef RI_THP_H
#define RI_THP_H
/* THP movie player state (shape follows the DolphinSDK THPPlayer sample; names are guesses). */
#include "game/rI_801DD7D4/types.h"
#ifdef __cplusplus
extern "C" {
#endif
struct THPAudioBuf { void* a0; s16* cur; u32 valid; };
struct THPPlayer {
    u8 p0[0x44];
    int a44;
    int a48;
    f32 a4c;
    u32 a50;       /* numFrames */
    u8 p54[0x58 - 0x54];
    int a58;
    int a5c;
    u8 p60[0x64 - 0x60];
    int a64;       /* movieDataOffsets */
    u8 p68[4];
    u32 a6c;       /* numComponents */
    u8 a70[0x80 - 0x70];
    int a80;
    int a84;
    u32 a88;
    u8 p8c[0x9C - 0x8C];  /* frameComp */
    void* a9c;     /* thpWork */
    int a0;        /* open */
    u8 a4;         /* state */
    u8 a5;         /* internalState */
    u8 a6;         /* playFlag */
    u8 a7;         /* audioExist */
    int a8;        /* dvdError */
    int ac;        /* videoError */
    int b0;
    int b4;
    int b8;
    int bc;
    int c0;
    u8 pc4[4];
    s64 c8;
    int d0;
    u32 d4;
    int d8;
    f32 dc;        /* curVolume */
    f32 e0;        /* targetVolume */
    f32 e4;        /* deltaVolume */
    int e8;        /* rampCount */
    int ec;
    int f0;
    int f4;
    int f8;
    int* fc;
    THPAudioBuf* buf;  /* +0x100 */
};
extern THPPlayer lbl_80420420;
void* memcpy(void*, const void*, u32);
void* memset(void*, int, u32);
int fn_8031D34C(void*, void*, int);
int fn_8031D284(void*, void*, int);
void fn_8031D224(void*, void*, int);
int fn_8031FC48(void*, void*, void*, void*, int, int, int);
void fn_803202B0(void*);
void fn_80320548(void*);
void* fn_80079940(int, int);
int OSDisableInterrupts(void);
void OSRestoreInterrupts(int);
#ifdef __cplusplus
}
#endif
#endif
