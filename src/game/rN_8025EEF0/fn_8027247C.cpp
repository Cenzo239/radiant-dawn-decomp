/* exact since the round 21 regs review (was regs, 12 words, "float registers"). Helpers from ../fn_80272624.cpp, body from wip/fn_8027247C.cpp
   symcheck: (c) fixed. fn_80253DAC and fn_80253718 take a fourth/third f32 (fade time, see rS_8023FD30/fn_8024F3FC.cpp) and the
   original passes 0.0f; the draft declared them without it, so f2 held pos->y at the call. wip/fn_8027247C.cpp still has that. */
/* Sound handle wrapper: slot id into fn_8024F484's sound table. */
#include "game/rN_8025EEF0/calls.h"

#pragma use_lmw_stmw on

extern "C" {

class SndObj {
public:
    virtual void v08(); virtual void v0C();
    virtual int isPlaying();   /* 0x10 */
    virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20();
    virtual void stop(int a);  /* 0x24 */
    virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34();
    virtual void setVol(f32 a, f32 b); /* 0x38 */
};

SndObj* fn_8024F484(int id);

struct Vec3i { f32 x, y, z; };
struct VecW { u32 a, b, c; };
struct SndHandle {
    u8 m0;
    u8 id;
    u8 m2;
    f32 vol;
    Vec3i pos;
    int m14;
};

static inline SndObj* handleObj(SndHandle* h) {
    int id = (s8)h->id;
    if (id < 0) {
        return 0;
    }
    return fn_8024F484(id);
}

static inline void handleInit(SndHandle* h) {
    Vec3i v;
    *(s8*)&h->m0 = -1;
    *(s8*)&h->id = -1;
    h->m2 = 0;
    *(int*)&v.x = 0;
    *(int*)&v.y = 0;
    *(int*)&v.z = 0;
    h->vol = 0.0f;
    h->pos = v;
    h->m14 = 0;
}










void fn_80312DB4(void* m, Vec3i* a, Vec3i* b);
void fn_800622B8(void* out, void* p);
void fn_80313484(Vec3i* a, Vec3i* b, Vec3i* out);
f32 fn_80313508(Vec3i* v);
f32 fn_8001EF30(f32 a, f32 b, f32 c, f32 d);
extern u8 lbl_803CAB38[];

class Snd3D : public SndObj {
public:
    virtual void v3C(); virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4C();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5C(); virtual void v60();
    virtual void v64(); virtual void v68(); virtual void v6C(); virtual void v70(); virtual void v74();
    virtual void v78(); virtual void v7C(); virtual void v80(); virtual void v84(); virtual void v88();
    virtual void v8C(); virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9C();
    virtual void vA0(); virtual void vA4(); virtual void vA8(); virtual void vAC();
    virtual void setPos(Vec3i* p); /* 0xB0 */
};





#if TARGET_PC
FE10_PROTO u8 fn_80253DAC(p32arg, Vec3i* pos, f32 v, f32 ms);
FE10_PROTO u8 fn_80253718(p32arg, f32 v, f32 ms);
#else
u8 fn_80253DAC(int id, Vec3i* pos, f32 v, f32 ms);
u8 fn_80253718(int id, f32 v, f32 ms);
#endif

#pragma push
#pragma use_lmw_stmw off
void fn_8027247C(SndHandle* h, int mode, int id, int b, Vec3i* pos, f32 vol) {
    SndObj* o = handleObj(h);
    if (o != 0 && o->isPlaying() != 0) {
        o->stop(0);
    }
    handleInit(h);
    switch (mode) {
    case 1: {
        Vec3i t;
        f32 z, y, x;
        x = pos->x;
        y = pos->y;
        z = pos->z;
        t.x = x;
        t.y = y;
        t.z = z;
        h->id = fn_80253DAC(id, &t, vol, 0.0f);
        break;
    }
    case 4: {
        Vec3i t;
        f32 z, y, x;
        x = pos->x;
        y = pos->y;
        z = pos->z;
        t.x = x;
        t.y = y;
        t.z = z;
        h->id = fn_80253DAC(id, &t, vol, 0.0f);
        break;
    }
    case 3:
        h->id = fn_80253718(id, vol, 0.0f);
        break;
    }
    {
        f32 z, y, x;
        x = pos->x;
        y = pos->y;
        z = pos->z;
        h->m0 = mode;
        h->pos.x = x;
        h->pos.y = y;
        h->pos.z = z;
    }
    h->m2 = b;
    h->vol = vol;
}
#pragma pop



}
