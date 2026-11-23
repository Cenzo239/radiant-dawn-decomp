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

void fn_80272624(SndHandle* h, f32 vol) {
    SndObj* o = handleObj(h);
    if (o != 0 && o->isPlaying() != 0) {
        o->setVol(vol, 0.0f);
    }
    h->vol = vol;
}

void fn_802726C8(SndHandle* h, int a) {
    SndObj* o = handleObj(h);
    if (o != 0 && o->isPlaying() != 0) {
        o->stop(a);
    }
    handleInit(h);
}

void fn_802729A8(SndHandle* h) { handleInit(h); }

SndObj* fn_802729F8(SndHandle* h) { return handleObj(h); }


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

void fn_802727A0(SndHandle* h, void* mtx) {
    Snd3D* o = (Snd3D*)handleObj(h);
    if (o != 0 && o->isPlaying() != 0) {
        Vec3i p = h->pos;
        Vec3i d;
        Vec3i c;
        Vec3i t1;
        Vec3i t2;
        Vec3i r;
        switch ((s8)h->m0) {
        case 1: {
            f32 z, y, x;
            fn_80312DB4(mtx, &p, &p);
            x = p.x;
            y = p.y;
            z = p.z;
            t1.x = x;
            t1.y = y;
            t1.z = z;
            o->setPos(&t1);
            break;
        }
        case 4: {
            f32 z, y, x;
            fn_80312DB4(mtx, &p, &p);
            x = p.x;
            y = p.y;
            z = p.z;
            t2.x = x;
            t2.y = y;
            t2.z = z;
            o->setPos(&t2);
            if (h->m2 != 0) {
                fn_800622B8(&r, lbl_803CAB38);
                *(VecW*)&c = *(VecW*)&r;
                fn_80313484(&p, &c, &d);
                f32 dist = fn_80313508(&d);
                f32 vol = h->vol;
                if (dist < (f32)h->m2) {
                    vol *= fn_8001EF30(1.0f, 0.0f, h->m2, dist);
                } else {
                    vol *= 0.0f;
                }
                o->setVol(vol, 0.0f);
            }
            break;
        }
        }
    }
}

}
