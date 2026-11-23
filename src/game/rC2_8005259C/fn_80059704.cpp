#include "game/rC2_8005259C/base.h"
class Snd { public:
    virtual void v08(); virtual void v0C(); virtual int v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20();
    virtual void v24(int);
};
struct MU { u8 pad[0xe8]; MU* next; u8 p[0x1c]; u64 flags; };
struct UL { MU* head; u8 p[8]; MU* h2; };
struct BgObj { u8 pad[0x44]; void* a44; void* a48; };
struct GD { u8 pad[0x9e]; u8 b9e; };
extern "C" {
extern UL* lbl_804CB814;
extern int lbl_803E7320[];
extern const s16 lbl_804CA350;
extern GD lbl_803CAB38;
extern u8 lbl_803EC898[];
extern u8 lbl_804CB818;
extern u32 lbl_804CB700;
extern char lbl_80361F9C[316];
void fn_80058094(void);
void fn_8011FE74(MU*, int);
int fn_8010E2F4(UL*);
void fn_80185720(void);
void fn_80114D00(void*);
void fn_801D607C(void);
void fn_800761F0(void*);
void fn_8012FCC0(void);
void fn_801E40B0(void*, int);
void fn_80252418(const char*, f32);
Snd* fn_8024F3FC(int);
void fn_8012FC9C(void);
}
static inline const s16& maxS(const s16& a, const s16& b) { return a < b ? b : a; }

extern "C" void fn_80059704(BgObj* o) {
    MU* u;
    {
        MU* n;
        MU* v = lbl_804CB814->h2;
        while (v) {
            n = v->next;
            v->flags &= ~0x800ULL;
            v = n;
        }
    }
    fn_80058094();
    u = lbl_804CB814->head;
    while (u) {
        MU* n = u->next;
        if (u->flags & 0x10000dcULL) {
            u->flags &= ~0x10000dcULL;
            fn_8011FE74(u, 5);
        }
        u = n;
    }
    {
        int t = lbl_803E7320[0];
        s16 c = t - fn_8010E2F4(lbl_804CB814);
        lbl_803CAB38.b9e = maxS(c, lbl_804CA350);
    }
    fn_80185720();
    fn_80114D00(lbl_803EC898);
    fn_801D607C();
    fn_800761F0(o->a44);
    fn_800761F0(o->a48);
    while (lbl_804CB818) {
        fn_8012FCC0();
    }
    if (o) {
        fn_801E40B0(o, 0);
    }
    if (!(lbl_804CB700 & 0x10)) {
        Snd* v;
        fn_80252418(lbl_80361F9C + 0x70, 0.0f);
        v = fn_8024F3FC(0);
        if (v && v->v10()) {
            v->v24(0x1f4);
            v->v0C();
        }
    }
    lbl_804CB700 &= ~0x10000;
    fn_8012FC9C();
}
