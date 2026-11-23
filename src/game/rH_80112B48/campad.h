#ifndef RH_CAMPAD_H
#define RH_CAMPAD_H
/* Pad input object (lbl_804CB5B8) and the free camera of 0x801315B8.. (names guessed). */
#include "game/rH_80112B48/types.h"
class Pad {
public:
    virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C();
    virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34();
    virtual int v38(); virtual int v3C(); virtual int v40(); virtual int v44(); virtual int v48(); virtual int v4C();
    virtual int v50(); virtual int v54(); virtual int v58(); virtual int v5C(); virtual int v60(); virtual int v64();
    virtual int v68(); virtual int v6C(); virtual int v70(); virtual int v74(); virtual int v78(); virtual int v7C();
};
struct CamD {
    u8 pad0[4];
    f32 f04;
    f32 f08;
    f32 f0C;
    f32 f10, f14, f18;
    int mode;
    u8 pad20[0x6c - 0x20];
};
class Cam : public CamD {
public:
    virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual f32 v18(int);
};
extern "C" {
extern Pad* lbl_804CB5B8;
}
#endif
