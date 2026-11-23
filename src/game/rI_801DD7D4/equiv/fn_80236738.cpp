/* fn_80236738: class `sched` (round 19): same instructions per basic block as the original, a few of them
   (independent loads, constants or stores) in another order; checked with tools/equiv/dd.py. */
/* fn_80236738: THPPlayerSetBuffer (DolphinSDK THPPlayer sample): hands out the caller's buffer to the
   read buffers (or the in-memory movie), the three Y/U/V texture sets and the audio buffers. */
#include "game/rI_801DD7D4/fn_thp.h"
extern "C" {
void DCInvalidateRange(void*, u32);
struct THPReadBuffer { u8* ptr; s32 frameNumber; BOOL isValid; };
struct THPTextureSet { u8* ytexture; u8* utexture; u8* vtexture; s32 frameNumber; };
struct THPAudioBuffer { s16* buffer; s16* curPtr; u32 validSample; };
struct THPPlayerS { u8 p0[0x44]; u32 bufSize; u32 audioMaxSamples; u8 p4c[0xc]; u32 movieDataSize; u8 p5c[0x24]; u32 xSize; u32 ySize; u8 p88[0x14]; void* thpWork; BOOL open; u8 state; u8 internalState; u8 playFlag; u8 audioExist; u8 pa8[8]; BOOL onMemory; u8* movieData; u8 pb8[0x4c]; };
/* One view of the pooled statics at lbl_80420420: the player, then its buffer tables. */
struct THPAll { THPPlayerS p; THPReadBuffer rb[10]; THPTextureSet ts[3]; THPAudioBuffer ab[6]; };
#define ALL (*(THPAll*)&lbl_80420420)
#define ActivePlayerS ALL.p
#define ReadBuffer ALL.rb
#define TextureSet ALL.ts
#define AudioBuffer ALL.ab
#define OSRoundUp32B(x) (((u32)(x) + 0x1f) & ~0x1f)
#pragma push
#pragma use_lmw_stmw on
BOOL fn_80236738(u8* buffer) {
    u32 i;
    u8* ptr;
    u32 ysize, uvsize;
    if (ActivePlayerS.open && ActivePlayerS.state == 0) {
        ptr = buffer;
        if (ActivePlayerS.onMemory) {
            ActivePlayerS.movieData = ptr;
            ptr += ActivePlayerS.movieDataSize;
        } else {
            for (i = 0; i < 10; i++) {
                ReadBuffer[i].ptr = ptr;
                ptr += OSRoundUp32B(ActivePlayerS.bufSize);
            }
        }
        ysize = OSRoundUp32B(ActivePlayerS.xSize * ActivePlayerS.ySize);
        uvsize = OSRoundUp32B((u32)(ActivePlayerS.xSize * ActivePlayerS.ySize) / 4);
        for (i = 0; i < 3; i++) {
            TextureSet[i].ytexture = ptr;
            DCInvalidateRange(ptr, ysize);
            ptr += ysize;
            TextureSet[i].utexture = ptr;
            DCInvalidateRange(ptr, uvsize);
            ptr += uvsize;
            TextureSet[i].vtexture = ptr;
            DCInvalidateRange(ptr, uvsize);
            ptr += uvsize;
        }
        if (ActivePlayerS.audioExist) {
            u32 asize = OSRoundUp32B(ActivePlayerS.audioMaxSamples * 4);
            for (i = 0; i < 6; i++) {
                AudioBuffer[i].buffer = (s16*)ptr;
                AudioBuffer[i].curPtr = (s16*)ptr;
                ptr += asize;
                AudioBuffer[i].validSample = 0;
            }
        }
        ActivePlayerS.thpWork = ptr;
        return TRUE;
    }
    return FALSE;
}
#pragma pop
}
