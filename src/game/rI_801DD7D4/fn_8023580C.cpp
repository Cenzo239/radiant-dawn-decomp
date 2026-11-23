/* fn_8023580C (0xAC): THPPlayer's VideoDecoderForOnMemory thread (DolphinSDK THPVideoDecode.c).
 * Decodes frame after frame straight from the in-memory movie; at the last frame it either wraps to the
 * start (loop flag) or suspends itself. Never returns. */
#include "game/rI_801DD7D4/fn_thp.h"
extern "C" {
struct THPReadBuffer { u8* ptr; s32 frameNumber; int isValid; };
extern u8 lbl_8041F090[];            /* VideoDecodeThread */
void fn_802358B8(THPReadBuffer*);    /* VideoDecode */
void fn_8023580C(void* ptr) {
    THPReadBuffer readBuffer;
    s32 tmp;
    s32 size;
    s32 readFrame;
    u32 frame;
    size = lbl_80420420.bc;          /* initReadSize */
    readBuffer.ptr = (u8*)ptr;
    readFrame = 0;
    while (1) {
        readBuffer.frameNumber = readFrame;
        fn_802358B8(&readBuffer);
        frame = (readFrame + lbl_80420420.c0) % lbl_80420420.a50;
        if (frame == lbl_80420420.a50 - 1) {
            if (lbl_80420420.a6 & 1) {
                size = *(s32*)readBuffer.ptr;
                readBuffer.ptr = (u8*)lbl_80420420.b4;   /* movieData */
            } else {
                fn_80320548(lbl_8041F090);               /* OSSuspendThread */
            }
        } else {
            tmp = *(s32*)readBuffer.ptr;
            readBuffer.ptr += size;
            size = tmp;
        }
        readFrame++;
    }
}
}
