#ifndef _DOLPHIN_AX_H_
#define _DOLPHIN_AX_H_

#include <dolphin/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/* FE10: RVL SDK (Wii) AXPB/AXVPB layout (see lib/ogws/include/revolution/AX/AXPB.h, AXVPB.h); pb at AXVPB+0x28 */
typedef struct _AXPBMIX {
    u16 vL, vDeltaL, vR, vDeltaR;
    u16 vAuxAL, vDeltaAuxAL, vAuxAR, vDeltaAuxAR;
    u16 vAuxBL, vDeltaAuxBL, vAuxBR, vDeltaAuxBR;
    u16 vAuxCL, vDeltaAuxCL, vAuxCR, vDeltaAuxCR;
    u16 vS, vDeltaS, vAuxAS, vDeltaAuxAS, vAuxBS, vDeltaAuxBS, vAuxCS, vDeltaAuxCS;
} AXPBMIX; // 0x30

typedef struct _AXPBITD {
    u16 flag, bufferHi, bufferLo, shiftL, shiftR, targetShiftL, targetShiftR;
} AXPBITD;

typedef struct _AXPBUPDATE {
    u16 updNum[5];
    u16 dataHi;
    u16 dataLo;
} AXPBUPDATE;

typedef struct _AXPBDPOP {
    s16 aL, aAuxAL, aAuxBL, aAuxCL, aR, aAuxAR, aAuxBR, aAuxCR, aS, aAuxAS, aAuxBS, aAuxCS;
} AXPBDPOP; // 0x18

typedef struct _AXPBVE {
    u16 currentVolume;
    s16 currentDelta;
} AXPBVE;

typedef struct _AXPBFIR {
    u16 numCoefs;
    u16 coefsHi;
    u16 coefsLo;
} AXPBFIR;

typedef struct _AXPBADDR {
    u16 loopFlag, format, loopAddressHi, loopAddressLo, endAddressHi, endAddressLo, currentAddressHi, currentAddressLo;
} AXPBADDR;

typedef struct _AXPBADPCM {
    u16 a[8][2];
    u16 gain, pred_scale, yn1, yn2;
} AXPBADPCM;

typedef struct _AXPBSRC {
    u16 ratioHi, ratioLo, currentAddressFrac;
    u16 last_samples[4];
} AXPBSRC;

typedef struct _AXPBADPCMLOOP {
    u16 loop_pred_scale, loop_yn1, loop_yn2;
} AXPBADPCMLOOP;

typedef struct _AXPBLPF {
    u16 on, yn1, a0, b0;
} AXPBLPF;

typedef struct _AXPBBIQUAD {
    u16 on, xn1, xn2, yn1, yn2, b0, b1, b2, a1, a2;
} AXPBBIQUAD;

typedef struct _AXPBRMTMIX {
    u16 vMain0, vDeltaMain0, vAux0, vDeltaAux0, vMain1, vDeltaMain1, vAux1, vDeltaAux1;
    u16 vMain2, vDeltaMain2, vAux2, vDeltaAux2, vMain3, vDeltaMain3, vAux3, vDeltaAux3;
} AXPBRMTMIX;

typedef struct _AXPBRMTDPOP {
    s16 aMain0, aMain1, aMain2, aMain3, aAux0, aAux1, aAux2, aAux3;
} AXPBRMTDPOP;

typedef struct _AXPBRMTSRC {
    u16 currentAddressFrac;
    u16 last_samples[4];
} AXPBRMTSRC;

typedef union __AXPBRMTIIR {
    AXPBLPF lpf;
    AXPBBIQUAD biquad;
} AXPBRMTIIR;

typedef struct _AXPB {
    /* 0x00 */ u16 nextHi;
    /* 0x02 */ u16 nextLo;
    /* 0x04 */ u16 currHi;
    /* 0x06 */ u16 currLo;
    /* 0x08 */ u16 srcSelect;
    /* 0x0A */ u16 coefSelect;
    /* 0x0C */ u32 mixerCtrl;
    /* 0x10 */ u16 state;
    /* 0x12 */ u16 type;
    /* 0x14 */ AXPBMIX mix;
    /* 0x44 */ AXPBITD itd;
    /* 0x52 */ AXPBDPOP dpop;
    /* 0x6A */ AXPBVE ve;
    /* 0x6E */ AXPBADDR addr;
    /* 0x7E */ AXPBADPCM adpcm;
    /* 0xA6 */ AXPBSRC src;
    /* 0xB4 */ AXPBADPCMLOOP adpcmLoop;
    /* 0xBA */ AXPBLPF lpf;
    /* 0xC2 */ AXPBBIQUAD biquad;
    /* 0xD6 */ u16 remote;
    /* 0xD8 */ u16 rmtMixerCtrl;
    /* 0xDA */ AXPBRMTMIX rmtMix;
    /* 0xFA */ AXPBRMTDPOP rmtDpop;
    /* 0x10A */ AXPBRMTSRC rmtSrc;
    /* 0x114 */ AXPBRMTIIR rmtIIR;
    /* 0x128 */ u8 padding[0x140 - 0x128];
} AXPB;

typedef struct _AXVPB {
    /* 0x00 */ void* next;
    /* 0x04 */ void* prev;
    /* 0x08 */ void* next1;
    /* 0x0C */ u32 priority;
    /* 0x10 */ void (*callback)(void*);
    /* 0x14 */ u32 userContext;
    /* 0x18 */ u32 index;
    /* 0x1C */ u32 sync;
    /* 0x20 */ u32 depop;
    /* 0x24 */ void* itdBuffer;
    /* 0x28 */ AXPB pb;
} AXVPB;

typedef struct _AXPBITDBUFFER {
    /* 0x00 */ s16 data[32];
} AXPBITDBUFFER;

typedef struct _AXPBU {
    /* 0x00 */ u16 data[128];
} AXPBU;

typedef struct _AXSPB {
    /* 0x00 */ u16 dpopLHi;
    /* 0x02 */ u16 dpopLLo;
    /* 0x04 */ s16 dpopLDelta;
    /* 0x06 */ u16 dpopRHi;
    /* 0x08 */ u16 dpopRLo;
    /* 0x0A */ s16 dpopRDelta;
    /* 0x0C */ u16 dpopSHi;
    /* 0x0E */ u16 dpopSLo;
    /* 0x10 */ s16 dpopSDelta;
    /* 0x12 */ u16 dpopALHi;
    /* 0x14 */ u16 dpopALLo;
    /* 0x16 */ s16 dpopALDelta;
    /* 0x18 */ u16 dpopARHi;
    /* 0x1A */ u16 dpopARLo;
    /* 0x1C */ s16 dpopARDelta;
    /* 0x1E */ u16 dpopASHi;
    /* 0x20 */ u16 dpopASLo;
    /* 0x22 */ s16 dpopASDelta;
    /* 0x24 */ u16 dpopBLHi;
    /* 0x26 */ u16 dpopBLLo;
    /* 0x28 */ s16 dpopBLDelta;
    /* 0x2A */ u16 dpopBRHi;
    /* 0x2C */ u16 dpopBRLo;
    /* 0x2E */ s16 dpopBRDelta;
    /* 0x30 */ u16 dpopBSHi;
    /* 0x32 */ u16 dpopBSLo;
    /* 0x34 */ s16 dpopBSDelta;
} AXSPB;

typedef struct _AXPROFILE {
    /* 0x00 */ u64 axFrameStart;
    /* 0x08 */ u64 auxProcessingStart;
    /* 0x10 */ u64 auxProcessingEnd;
    /* 0x18 */ u64 userCallbackStart;
    /* 0x20 */ u64 userCallbackEnd;
    /* 0x28 */ u64 axFrameEnd;
    /* 0x30 */ u32 axNumVoices;
} AXPROFILE;

typedef struct AX_AUX_DATA {
    /* 0x00 */ s32* l;
    /* 0x00 */ s32* r;
    /* 0x00 */ s32* s;
} AX_AUX_DATA;

typedef struct AX_AUX_DATA_DPL2 {
    /* 0x00 */ s32* l;
    /* 0x00 */ s32* r;
    /* 0x00 */ s32* ls;
    /* 0x00 */ s32* rs;
} AX_AUX_DATA_DPL2;

typedef void (*AXCallback)();

#define AX_DSP_SLAVE_LENGTH 0xF80
#define AX_MAX_VOICES 96 // RVL

#define AX_SRC_TYPE_NONE     0
#define AX_SRC_TYPE_LINEAR   1
#define AX_SRC_TYPE_4TAP_8K  2
#define AX_SRC_TYPE_4TAP_12K 3
#define AX_SRC_TYPE_4TAP_16K 4

// sync flags
#define AX_SYNC_FLAG_COPYALL       (1 << 31)
#define AX_SYNC_FLAG_UNK1          (1 << 30) // reserved, unused?
#define AX_SYNC_FLAG_UNK2          (1 << 29) // reserved, unused?
#define AX_SYNC_FLAG_UNK3          (1 << 28) // reserved, unused?
#define AX_SYNC_FLAG_UNK4          (1 << 27) // reserved, unused?
#define AX_SYNC_FLAG_UNK5          (1 << 26) // reserved, unused?
#define AX_SYNC_FLAG_UNK6          (1 << 25) // reserved, unused?
#define AX_SYNC_FLAG_UNK7          (1 << 24) // reserved, unused?
#define AX_SYNC_FLAG_UNK8          (1 << 23) // reserved, unused?
#define AX_SYNC_FLAG_UNK9          (1 << 22) // reserved, unused?
#define AX_SYNC_FLAG_UNK10         (1 << 21) // reserved, unused?
#define AX_SYNC_FLAG_COPYADPCMLOOP (1 << 20)
#define AX_SYNC_FLAG_COPYRATIO     (1 << 19)
#define AX_SYNC_FLAG_COPYSRC       (1 << 18)
#define AX_SYNC_FLAG_COPYADPCM     (1 << 17)
#define AX_SYNC_FLAG_COPYCURADDR   (1 << 16)
#define AX_SYNC_FLAG_COPYENDADDR   (1 << 15)
#define AX_SYNC_FLAG_COPYLOOPADDR  (1 << 14)
#define AX_SYNC_FLAG_COPYLOOP      (1 << 13)
#define AX_SYNC_FLAG_COPYADDR      (1 << 12)
#define AX_SYNC_FLAG_COPYFIR       (1 << 11)
#define AX_SYNC_FLAG_SWAPVOL       (1 << 10)
#define AX_SYNC_FLAG_COPYVOL       (1 << 9)
#define AX_SYNC_FLAG_COPYDPOP      (1 << 8)
#define AX_SYNC_FLAG_COPYUPDATE    (1 << 7)
#define AX_SYNC_FLAG_COPYTSHIFT    (1 << 6)
#define AX_SYNC_FLAG_COPYITD       (1 << 5)
#define AX_SYNC_FLAG_COPYAXPBMIX   (1 << 4)
#define AX_SYNC_FLAG_COPYTYPE      (1 << 3)
#define AX_SYNC_FLAG_COPYSTATE     (1 << 2)
#define AX_SYNC_FLAG_COPYMXRCTRL   (1 << 1)
#define AX_SYNC_FLAG_COPYSELECT    (1 << 0)

#define AX_PRIORITY_STACKS 32

// AX
void AXInit(void);
void AXInitEx(u32 outputBufferMode);
BOOL AXIsInit(void); // RVL
void AXQuit(void);

// AXAlloc
void AXFreeVoice(AXVPB* p);
AXVPB* AXAcquireVoice(u32 priority, void (*callback)(void *), u32 userContext);
void AXSetVoicePriority(AXVPB* p, u32 priority);

// AXAux
void AXRegisterAuxACallback(void (*callback)(void*, void*), void* context);
void AXRegisterAuxBCallback(void (*callback)(void*, void*), void* context);

// AXCL
void AXSetMode(u32 mode);
u32 AXGetMode(void);

// AXOut
extern AXPROFILE __AXLocalProfile;

void AXSetStepMode(u32 i);
AXCallback AXRegisterCallback(AXCallback callback);

// AXProf
void AXInitProfile(AXPROFILE* profile, u32 maxProfiles);
u32 AXGetProfile(void);

// AXVPB
void AXSetVoiceSrcType(AXVPB* p, u32 type);
void AXSetVoiceState(AXVPB* p, u16 state);
void AXSetVoiceType(AXVPB* p, u16 type);
void AXSetVoiceMix(AXVPB* p, AXPBMIX* mix);
void AXSetVoiceItdOn(AXVPB* p);
void AXSetVoiceItdTarget(AXVPB* p, u16 lShift, u16 rShift);
void AXSetVoiceUpdateIncrement(AXVPB* p);
void AXSetVoiceUpdateWrite(AXVPB* p, u16 param, u16 data);
void AXSetVoiceDpop(AXVPB* p, AXPBDPOP* dpop);
void AXSetVoiceVe(AXVPB* p, AXPBVE* ve);
void AXSetVoiceVeDelta(AXVPB* p, s16 delta);
void AXSetVoiceFir(AXVPB* p, AXPBFIR* fir);
void AXSetVoiceAddr(AXVPB* p, AXPBADDR* addr);
void AXSetVoiceLoop(AXVPB* p, u16 loop);
void AXSetVoiceLoopAddr(AXVPB* p, u32 addr);
void AXSetVoiceEndAddr(AXVPB* p, u32 addr);
void AXSetVoiceCurrentAddr(AXVPB* p, u32 addr);
void AXSetVoiceAdpcm(AXVPB* p, AXPBADPCM* adpcm);
void AXSetVoiceSrc(AXVPB* p, AXPBSRC* src_);
void AXSetVoiceSrcRatio(AXVPB* p, f32 ratio);
void AXSetVoiceAdpcmLoop(AXVPB* p, AXPBADPCMLOOP* adpcmloop);
void AXSetMaxDspCycles(u32 cycles);
u32 AXGetMaxDspCycles(void);
u32 AXGetDspCycles(void);
void AXSetVoiceLpf(AXVPB* p, AXPBLPF* lpf);
void AXSetVoiceLpfCoefs(AXVPB* p, u16 a0, u16 b0);
void AXGetLpfCoefs(u16 freq, u16* a0, u16* b0);

// DSPCode
extern u16 axDspSlaveLength;
extern u16 axDspSlave[AX_DSP_SLAVE_LENGTH];

#ifdef __cplusplus
}
#endif

#endif // _DOLPHIN_AX_H_
