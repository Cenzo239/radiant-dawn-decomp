#include "game/rS_8023FD30/audio.h"

struct SndFader {
    s32 t;
    s32 frames;
    f32 cur;
    f32 from;
    f32 to;
};

class PlayerBase {
public:
    virtual void v08();
    u8 pad04[0x49 - 4];
    s8 countdown;  /* +0x49 */
    u8 pad4A[0x5C - 0x4A];
    void* handle;  /* +0x5C */
};

extern "C" {

extern SndFader lbl_8042F170;
extern SndFader lbl_8042F184;
extern SndFader lbl_8042F198;
extern void* lbl_804CBFF4;
void fn_802A2030(void*, s32, s32);
int fn_802A23B8(void*);
void fn_802ABCC4(void*, s32);

#define FADE_SET(addr, fd) \
    void fn_##addr(f32 target, f32 ms) { \
        SndMutex& m = lbl_8042E798; \
        m.lock(); \
        fd.t = 0; \
        fd.frames = ms / 16.666666f; \
        fd.from = fd.cur; \
        fd.to = target; \
        m.unlock(); \
    }

FADE_SET(80257A14, lbl_8042F170)
FADE_SET(80257AC0, lbl_8042F184)
FADE_SET(80257B6C, lbl_8042F198)

void* fn_80257C18(void* cb) {
    SndMutex& m = lbl_8042E798;
    SndLock l(m);
    void* old;
    m.lock();
    old = lbl_804CBFF4;
    m.unlock();
    lbl_804CBFF4 = cb;
    return old;
}

#define PLAYER_METHODS2(has, pause, playing) \
    BOOL fn_##has(PlayerBase* self) { \
        SndMutex& m = lbl_8042E798; \
        BOOL r; \
        m.lock(); \
        r = self->handle != 0; \
        m.unlock(); \
        return r; \
    } \
    void fn_##pause(PlayerBase* self, s32 ms) { \
        SndLock l(lbl_8042E798); \
        if (self->countdown++ > 0) { \
            return; \
        } \
        if (self->handle != 0) { \
            fn_802A2030(self->handle, 1, (f32)ms / 16.666666f); \
        } \
    } \
    BOOL fn_##playing(PlayerBase* self) { \
        SndLock l(lbl_8042E798); \
        BOOL r = FALSE; \
        if (self->handle != 0 && fn_802A23B8(self->handle) != 0) { \
            r = TRUE; \
        } \
        return r; \
    }

PLAYER_METHODS2(80258A6C, 80258ADC, 80258BD8)
PLAYER_METHODS2(80259EBC, 80259F2C, 8025A028)
PLAYER_METHODS2(8025B014, 8025B084, 8025B180)
PLAYER_METHODS2(8025C0C0, 8025C130, 8025C22C)

void fn_80259E28(u8* self, s32 a) {
    SndLock l(lbl_8042E798);
    fn_802ABCC4(self + 0x60, a);
}

}
