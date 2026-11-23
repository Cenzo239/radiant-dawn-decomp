/* fn_801E041C (round 20, exact): prompt window with caller-supplied labels (defaults M_ASK_Y / M_ASK_N), width 0xc8, 50.0f spacing.
 * The two key-label objects are real function-local statics (guard byte + inline constructor); check with
 *   python3 -I tools/check_func.py <this file> --strict-references -v --symbol-map <this file>.symbols.json
 * KB/KA/KC stand in for a small class hierarchy with virtual functions (vtables by label). */
#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/vobj.h"
#pragma auto_inline off

extern "C" {

void* fn_80079150(int);

typedef struct KeyStr { void* vt; u8 x4; u8 pad5[3]; const char* x8; u8 xc; u8 xd; u8 pade[2]; } KeyStr;
extern KeyStr lbl_8041EFB0;
extern KeyStr lbl_8041EFC0;
extern KeyStr lbl_8041EFD0;
extern KeyStr lbl_8041EFE0;
extern KeyStr lbl_8041EFF0;
extern KeyStr lbl_8041F000;
extern KeyStr lbl_8041F010;
extern KeyStr lbl_8041F020;
extern s8 lbl_804CBE18;
extern s8 lbl_804CBE19;
extern s8 lbl_804CBE1A;
extern s8 lbl_804CBE1B;
extern s8 lbl_804CBE1C;
extern s8 lbl_804CBE1D;
extern s8 lbl_804CBE1E;
extern s8 lbl_804CBE1F;
extern char lbl_8038C830[];
extern char lbl_8038C7B8[];
extern char lbl_8038C740[];
extern char lbl_8036ED60[];
extern char lbl_8038C8A8[];
extern char lbl_8038C2C8[];
extern char lbl_8038C668[], lbl_8038C2D4[], lbl_8038C594[], lbl_8038C2E0[], lbl_8038C4C0[], lbl_8038C448[], lbl_8038C3D0[], lbl_8038C2EC[], lbl_8038C2F8[];
extern char lbl_804CA930[8], lbl_804CA938[8];

typedef struct Win {
    void* vt0;
    void* vt4;
    s16 x8, xa, xc, xe;
    s16 x10, x12, x14, x16;
    f32 x18;
    s16 x1c, x1e;
    void* x20;
    u8 x24, x25, x26;
} Win;

class KB {
public:
    void* vt;
    u8 x4;
    const char* x8;
    u8 xc;
    u8 xd;
    KB(const char* s, u8 a, u8 b) {
        vt = lbl_8038C830;
        x4 = 0;
        x8 = s;
        xc = a;
        xd = b;
    }
};
class KA : public KB {
public:
    KA(const char* s) : KB(s, 0x1f, 4) { vt = lbl_8038C7B8; }
};
inline void* operator new(unsigned long, void* p) { return p; }


class KC : public KB {
public:
    KC(const char* s) : KB(s, 0x1f, 4) { vt = lbl_8038C740; }
};

class KD : public KB {
public:
    KD(const char* s) : KB(s, 0x1f, 4) { vt = lbl_8038C448; }
};
class KE : public KB {
public:
    KE(const char* s) : KB(s, 0x1f, 4) { vt = lbl_8038C3D0; }
};
class VK { public: virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C();
    virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34(); virtual int v38(); virtual int v3C();
    virtual int v40(); virtual int v44(); virtual int v48(); virtual int v4C(); virtual int v50(); virtual int v54(); virtual int v58(int); virtual int v5C();
    virtual int v60(int); virtual int v64(); virtual int v68(int); virtual int v6C(); virtual int v70(); virtual int v74(const char*); };
Win* fn_801E041C(const char* s1, const char* s2) {
    Win* w;
    static KD sa(lbl_804CA930);
    static KE sc(lbl_804CA938);
    ((VK*)&sa)->v58(0);
    ((VK*)&sc)->v58(0);
    ((VK*)&sa)->v74(s1 ? s1 : lbl_8036ED60);
    ((VK*)&sc)->v74(s2 ? s2 : lbl_8036ED60 + 8);
    ((VK*)&sa)->v60(0x1f);
    ((VK*)&sc)->v60(0x1f);
    ((VK*)&sa)->v68(4);
    ((VK*)&sc)->v68(4);
    w = (Win*)fn_80079150(0x28);
    if (w != NULL) {
        w->vt0 = lbl_8038C2EC;
        w->vt4 = lbl_8038C8A8;
        w->x8 = 0x80;
        w->xa = 0x9c;
        w->xc = 0x160;
        w->xe = 0x88;
        w->x10 = 0;
        w->x12 = 0;
        w->x14 = 0;
        w->x16 = 0;
        w->x18 = 10.0f;
        w->x1c = 0x20;
        w->x1e = 4;
        w->x20 = 0;
        w->x24 = 0;
        w->x25 = 0x1f;
        w->x26 = 4;
        w->vt4 = lbl_8038C2F8;
        w->xe = 0x20;
    }
    w->xc = 0xc8;
    w->x18 = 50.0f;
    w->x10 = 0;
    w->x12 = 0;
    return w;
}
}
