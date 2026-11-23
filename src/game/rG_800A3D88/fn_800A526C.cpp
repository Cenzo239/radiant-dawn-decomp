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
Vec fn_800B3A1C(Tgt*, int, int);
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
// Battle body: largest camera scale among the target or both characters.
static inline Tgt* Target(Body* b) {
    Tgt* t = b->m98;
    if (t == NULL) return NULL;
    switch (b->m72 & 0xE000) {
    case 0:
    case 0x4000:
    case 0x8000:
    case 0xA000:
        return t;
    case 0x2000:
        return t->m80;
    case 0x6000:
        return b->m94;
    }
    return NULL;
}
f32 fn_800A526C(Body* b) {
    f32 m = 1.0f;
    if (!(b->m72 & 0x200)) return m;
    if (b->m7c != NULL && (b->m7c->m8 & 0x100)) {
        Tgt* t = Target(b);
        if (t != NULL) return fn_800A7370(t->m78, lbl_80365064 + 0xC4);
    }
    const char* s = lbl_80365064;
    Tgt* c;
    Body* q;
    int i;
    for (q = b, i = 0; i < 2; i++, ADV(q)) {
        c = q->mA0[0];
        if (fn_800BD280(c)) {
            f32 v = fn_800A7370(c->m78, s + 0xC4);
            if (m < v) m = v;
        }
    }
    return m;
}
}
