#ifndef GAME_HELPBAR_H
#define GAME_HELPBAR_H
/* The help-bar widget (0x68 bytes, vtable lbl_8038C1C0) as a real C++ class hierarchy.

   Only this shape reproduces the inlined constructor's register colours in its ~30 callers:
   - HbWidget is the polymorphic widget base (vtable lbl_8038CB1C, 0x40 bytes, same layout as WF in
     rI_801DD7D4/fn_wf.h); the vptr sits at 0 because the root HbObj is an empty polymorphic class.
   - HbTextWidget adds a 16-byte string with short-string storage at 0x40 (destructor fn_801D5D54 tests
     bit 31 of 0x40 and frees 0x48; fn_801D5BB0 reads the short length from the byte at 0x40). Its
     constructor zeroes the four words in a loop. Its own vtable is dead (stored and overwritten).
   - HbHelpBar stores its vptr after HbTextWidget's members, which is what the original does.
   Callers must map the compiler vtables to the original labels with a .symbols.json:
     {"__vt__8HbWidget": "lbl_8038CB1C", "__vt__9HbHelpBar": "lbl_8038C1C0", "__nw__FUl": "fn_80079150"}
   Field names are guesses. */
/* Standalone: plain C types, so any region can include it next to its own types.h. */

void* operator new(unsigned long);

class HbStr {
public:
    unsigned long w[4];
    HbStr() { for (int i = 0; i < 4; i++) w[i] = 0; }
};

class HbObj { public: virtual void v0(); };
class HbRc : public HbObj { public: int rc; HbRc() { rc = 0; } };

class HbWidget : public HbRc {
public:
    short id; short x0, y0, x1, y1; short ix0, iy0, ix1, iy1;
    short a1a, a1c, tx, ty; unsigned char c[4]; short a26, a28; float sx, sy, sz; unsigned long flags; void* a3c;
    virtual void v0();
    HbWidget(short x0_, short y0_, short x1_, short y1_, short ix1_, short iy1_, short a26_, int fl) {
        id = -1;
        x0 = x0_; y0 = y0_; x1 = x1_; y1 = y1_;
        ix0 = 0; iy0 = 0; ix1 = ix1_; iy1 = iy1_;
        a1a = 0; a1c = 0; tx = 0; ty = 0;
        c[0] = 0xff; c[1] = 0xff; c[2] = 0xff; c[3] = 0xff;
        a26 = a26_; a28 = 0;
        sx = 1.0f; sy = 1.0f; sz = 1.0f;
        flags = fl; a3c = 0;
    }
};

class HbTextWidget : public HbWidget {
public:
    HbStr s; unsigned char a50; float a54; short a58, a5a, a5c, a5e;
    virtual void v0();
    HbTextWidget(short x0_, short y0_, short x1_, short y1_, short ix1_, short iy1_, short a26_, int fl)
        : HbWidget(x0_, y0_, x1_, y1_, ix1_, iy1_, a26_, fl) {
        a50 = 1;
        a5a = 0; a5e = 0;
    }
};

class HbHelpBar : public HbTextWidget {
public:
    int a60; const char* a64;
    virtual void v0();
    /* a26 is 0x78 in region I and 0x316 in region C2 */
    HbHelpBar(short a26_ = 0x78) : HbTextWidget(0, 400, 0x260, 0x1c0, 0x260, 0x30, a26_, 0x10) {
        a60 = 0; a64 = 0;
        a58 = 0x30; a5c = 0x30;
        a54 = 0.75f;
    }
};

#endif
