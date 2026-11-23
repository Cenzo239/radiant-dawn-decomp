#include "game/rG_800A3D88/types.h"

extern "C" {
struct Vec { f32 x, y, z; };
struct Anm { u8 p[8]; u16 m8; };
struct Tgt { u8 p[0x78]; void* m78; u8 p7c[4]; Tgt* m80; };
struct Body {
    u8 p[0x72];
    u16 m72;
    u8 p74[8];
    Anm* m7c;
    u8 p80[8];
    s16 m88, m8a, m8c, m8e;
    f32 m90;
    Tgt* m94;
    Tgt* m98;
    u8 p9c[4];
    Tgt* mA0[2];
};
extern char lbl_80365064[];
f32 fn_800A84A4(const char*);
int fn_800BD280(Tgt*);
void fn_800B3A1C(Vec*, Tgt*, int, int);
void fn_80313484(Vec*, Vec*, Vec*);
f32 fn_800A7370(void*, const char*);
u32 fn_80089ED0();
class Snd {
public:
    virtual void v0(int);
    virtual void v1(int);
    virtual void v2(int);
    virtual void v3(int);
    virtual void v4(int);
    virtual void v5(int);
    virtual void v6(int);
    virtual void v7(int);
    virtual void v8(int);
    virtual void v9(int);
    virtual void v10(int);
    virtual void v11(int);
    virtual void v12(int);
    virtual void v13(int);
    virtual void v14(int);
    virtual void v15(int);
    virtual void v16(int);
    virtual void v17(int);
    virtual void v18(int);
    virtual void v19(int);
    virtual void v20(int);
    virtual void v21(int);
    virtual void v22(int);
    virtual void v23(int);
    virtual void v24(int);
    virtual void v25(int);
    virtual void v26(int);
    virtual void v27(int);
    virtual void v28(int);
    virtual void v29(int);
    virtual void v30(int);
    virtual void v31(int);
    virtual void v32(int);
    virtual void v33(int);
    virtual void v34(int);
    virtual void v35(int);
    virtual void v36(int);
    virtual void v37(int);
    virtual void v38(int);
    virtual void v39(int);
    virtual void v40(int);
};
extern Snd* lbl_804CB5B8;
#define ADV(q) (q = (Body*)((u8*)q + 4))
// Battle body: zoom factor from the distance between the two characters.
f32 fn_800A5120(Body* b) {
    Vec v[2];
    Vec d, t;
    Body* q;
    Vec* p;
    int n;
    int i;
    if ((b->m72 & 0xE000U) == 0x6000) {
        const char* s = lbl_80365064;
        f32 k = 40.0f;
        f32 lo = fn_800A84A4(s + 0xAA);
        f32 hi = fn_800A84A4(s + 0xB7);
        q = b;
        p = v;
        n = 0;
        for (i = 0; i < 2; i++, ADV(q), p++) {
            if (fn_800BD280(q->mA0[0])) {
                fn_800B3A1C(&t, q->mA0[0], (b->m72 >> 10) & 1, -1);
                n++;
                *p = t;
            }
        }
        if (n < 2) return 1.0f;
        fn_80313484(&v[0], &v[1], &d);
        f32 r = (f32)__fabs(d.x) / k;
        if (r < lo) r = lo;
        if (r > hi) r = hi;
        return r;
    }
    return 1.0f;
}
}
