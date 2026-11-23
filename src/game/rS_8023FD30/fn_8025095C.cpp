#include "game/rS_8023FD30/audio.h"

/* Volume faders of the sound manager. One per category plus per-channel arrays. */
struct SndFader {
    s32 t;
    s32 frames;
    f32 cur;
    f32 from;
    f32 to;
};

extern "C" {

extern SndFader lbl_8042EE78;
extern SndFader lbl_8042EE8C;
extern SndFader lbl_8042EEA0;
extern SndFader lbl_8042EEB4;
extern SndFader lbl_8042EEC8;
extern SndFader lbl_8042EEDC;
extern SndFader lbl_8042EEF0[8];
extern SndFader lbl_8042EF90[8];
extern SndFader lbl_8042F030[8];
extern SndFader lbl_8042F0D0[8];

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

FADE_SET(8025095C, lbl_8042EE78)
FADE_SET(80250A08, lbl_8042EE8C)
FADE_SET(80250AB4, lbl_8042EEA0)
FADE_SET(80250B60, lbl_8042EEB4)
FADE_SET(80250C0C, lbl_8042EEC8)
FADE_SET(80250CB8, lbl_8042EEDC)

#define FADE_SET_I(addr, arr) \
    void fn_##addr(s8 i, f32 target, f32 ms) { \
        SndMutex& m = lbl_8042E798; \
        m.lock(); \
        if (i >= 0 && i < 8) { \
            arr[i].t = 0; \
            arr[i].frames = ms / 16.666666f; \
            arr[i].from = arr[i].cur; \
            arr[i].to = target; \
        } \
        m.unlock(); \
    }

FADE_SET_I(80250D64, lbl_8042EEF0)
FADE_SET_I(80250E38, lbl_8042EF90)
FADE_SET_I(80250F0C, lbl_8042F030)
FADE_SET_I(80250FE0, lbl_8042F0D0)

}
