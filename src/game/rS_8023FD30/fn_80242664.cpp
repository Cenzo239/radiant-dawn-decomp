#include "game/rS_8023FD30/types.h"
class TalkItem2 {
public:
    virtual void v08();
    virtual void v0C();
    virtual int v10();
    virtual void* v14();
    int kind;
    struct { u8 pad[4]; void* a; void* b; }* info;
};
struct Proc18 { u8 pad[0x18]; void* v18; u8 pad1C[0x44 - 0x1C]; void* v44; };
extern "C" {
extern u8 lbl_803CAB38[];
void* fn_801E5640(void*, s32, s32);
TalkItem2* fn_80240868(void*);
BOOL fn_80058718(void);
BOOL fn_8002460C(void);
void fn_801D23AC(void*);
void* fn_800D4228(const char*);
void fn_800893D4(void* proc);
void* fn_8024BC94(void);
void fn_801E5870(void);
extern char lbl_803728A8[];
#if TARGET_PC
FE10_PROTO void fn_80068D34(ptr32<const void>);
#else
void fn_80068D34(void*);
#endif
void* fn_8012CE54(void*);
s8 fn_8012E9B4(void*, void*);
void fn_8012E3AC(void*, int);
void fn_802452B4(void*, void*);
void fn_8012D620(void);
void fn_8012D6B4(void);
f32* fn_8025121C(int);
void fn_80250E38(f32, f32, int);
void* fn_8006074C(void*);
#if TARGET_PC
FE10_PROTO ptr32<void> fn_80068528(void* chap);
FE10_PROTO ptr32<void> fn_800685B0(void* chap);
#else
void* fn_80068528(void* chap);
void* fn_800685B0(void* chap);
#endif
s8 fn_8024F7EC(void* bgm);
void fn_80251838(f32, int, void*);

/* After the talk: applies its result, then restarts the map music. */
void fn_80242664(Proc18* self) {
    TalkItem2* t;
    void* sv;
    void* a;
    void* b;
    int x;
    int y;
    void* c;
    t = fn_80240868(fn_801E5640(self, 0x81, 0));
    if (fn_80058718() == 0 && fn_8002460C() == 0) {
        fn_801D23AC(self->v18);
    } else {
        void* proc = fn_800D4228(lbl_803728A8 + 0x7A);
        if (proc) {
            fn_800893D4(proc);
        }
    }
    sv = fn_8024BC94();
    fn_801E5870();
    switch (t->kind) {
    case 0: {
        a = fn_8012CE54(t->info->a);
        b = fn_8012CE54(t->info->b);
        x = fn_8012E9B4(a, b);
        y = fn_8012E9B4(b, a);
        fn_8012E3AC(a, x);
        fn_8012E3AC(b, y);
        fn_802452B4(sv, t->v14());
        break;
    }
    case 1:
        fn_80068D34(self->v44);
        fn_802452B4(sv, t->v14());
        break;
    }
    fn_8012D620();
    fn_8012D6B4();
    if (fn_80058718()) {
        c = fn_800685B0(fn_8006074C(lbl_803CAB38));
        if (fn_8024F7EC(c)) {
            fn_80251838(500.0f, 0, c);
        }
    } else {
        if (0.0f != fn_8025121C(6)[4]) {
            fn_80250E38(0.0f, 500.0f, 6);
        }
        void* d = fn_80068528(fn_8006074C(lbl_803CAB38));
        if (fn_8024F7EC(d)) {
            fn_80251838(500.0f, 0, d);
        }
    }
}
}
