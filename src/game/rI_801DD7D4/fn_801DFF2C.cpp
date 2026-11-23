/* fn_801DFF2C (round 20, exact): yes/no prompt window (0x28) with the labels M_ASK_Y / M_ASK_N reset; owner stored at +0x20.
 * The two key-label objects are real function-local statics (guard byte + inline constructor); check with
 *   python3 -I tools/check_func.py <this file> --strict-references -v --symbol-map <this file>.symbols.json
 * KB/KA/KC stand in for a small class hierarchy with virtual functions (vtables by label). */
#pragma pool_strings on
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
extern char lbl_8038C668[];

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

Win* fn_801DFF2C(void* a) {
    Win* w;
    static KA sa("M_ASK_Y");
    static KC sc("M_ASK_N");
    ((VO0*)&sa)->v58(0);
    ((VO0*)&sc)->v58(0);
    w = (Win*)fn_80079150(0x28);
    if (w != NULL) {
        w->vt0 = lbl_8038C2C8;
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
        w->vt4 = lbl_8038C668;
        w->x20 = 0;
        w->x24 = 0;
        w->x25 = 0x1f;
        w->x26 = 4;
    }
    w->x20 = a;
    return w;
}

}
