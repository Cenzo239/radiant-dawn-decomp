/* WIP (round 19): class `other`, 155 of 160 instructions, complete and believed correct (follows the SDK
   sample). Left: (1) the original materialises WaitUntilPrepare()'s result (`beq; li r0,1; b; li r0,0;
   cmpwi r0,0`) where ours tests msg directly; inline/static/auto-inline/C/deferred forms all fold.
   (2) load order of movieDataOffsets vs WorkBuffer[0] in the initOffset sum.
   Needs --symbol-map fn_80236A5C.symbols.json for the pooled statics. */
/* fn_80236A5C: THPPlayerPrepare(frameNum, playFlag, audioTrack) of the DolphinSDK THPPlayer sample:
   picks the start frame, creates and starts the decode/read threads, waits for the first frame and
   installs the post-retrace callback. */
#include "game/rI_801DD7D4/fn_thp.h"
#pragma auto_inline off
extern "C" {
int fn_802F6C90(void*, void*, int, int, int);   /* DVDReadPrio */
void fn_80237CF8(int, void*);                    /* CreateVideoDecodeThread */
void fn_802356BC(int, void*);                    /* CreateAudioDecodeThread */
void fn_80237A80(int);                           /* CreateReadThread */
void fn_80236978(void);                          /* InitAllMessageQueue */
void fn_80237DCC(void);                          /* VideoDecodeThreadStart */
void fn_8023578C(void);                          /* AudioDecodeThreadStart */
void fn_80237B20(void);                          /* ReadThreadStart */
void fn_80236E18(u32);                           /* PlayControl */
void* fn_8032F774(void*);                        /* VISetPostRetraceCallback */
extern void* lbl_804CBF58;                       /* OldVIPostCallback */
struct PlayerPad { THPPlayer p; u8 pad[0x200 - sizeof(THPPlayer)]; };
static PlayerPad sT;                             /* ActivePlayer */
static s32 sWork[0x10];                          /* WorkBuffer */
static u8 sQ[0x20];                              /* PrepareReadyQueue */
#define P sT.p
#define PI(off) (*(s32*)((u8*)&sT + (off)))
#define PU(off) (*(u32*)((u8*)&sT + (off)))
static inline BOOL WaitUntilPrepare(void) {
    void* msg;
    fn_8031D34C(sQ, &msg, 1);
    if (msg) return TRUE; else return FALSE;
}
#pragma use_lmw_stmw on
BOOL fn_80236A5C(s32 frameNum, s32 playFlag, s32 audioTrack) {
    s32 offset;
    u8* threadData;
    if (P.a0 && P.a4 == 0) {
        if (frameNum > 0) {
            if (PI(0x60) == 0) return FALSE;
            if (P.a50 > frameNum) {
                offset = PI(0x60) + (frameNum - 1) * 4;
                if (fn_802F6C90(&sT, sWork, 0x20, offset, 2) < 0) return FALSE;
                P.b8 = P.a64 + sWork[0];
                P.c0 = frameNum;
                P.bc = sWork[1] - sWork[0];
            } else {
                return FALSE;
            }
        } else {
            P.b8 = P.a64;
            P.bc = PI(0x54);
            P.c0 = frameNum;
        }
        if (P.a7) {
            if (audioTrack < 0 || audioTrack >= PU(0x98)) return FALSE;
            P.ec = audioTrack;
        }
        P.a6 = playFlag & 1;
        P.d8 = 0;
        if (P.b0) {
            if (fn_802F6C90(&sT, (void*)P.b4, P.a58, P.a64, 2) < 0) return FALSE;
            threadData = (u8*)P.b4 + P.b8 - P.a64;
            fn_80237CF8(0x14, threadData);
            if (P.a7) fn_802356BC(0xc, threadData);
        } else {
            fn_80237CF8(0x14, 0);
            if (P.a7) fn_802356BC(0xc, 0);
            fn_80237A80(8);
        }
        P.f0 = -1;
        P.f4 = 0;
        fn_80236978();
        fn_80237DCC();
        if (P.a7) fn_8023578C();
        if (!P.b0) fn_80237B20();
        if (!WaitUntilPrepare()) return FALSE;
        P.a4 = 1;
        P.a5 = 0;
        P.fc = 0;
        P.buf = 0;
        lbl_804CBF58 = fn_8032F774(fn_80236E18);
        return TRUE;
    }
    return FALSE;
}
}
