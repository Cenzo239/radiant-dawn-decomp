#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/vobj.h"
#pragma auto_inline off
extern "C" {
int fn_8011B8A4(void*);
extern char lbl_80371B80[];
int fn_8024F92C(const char*);
void fn_80255060(const char*, f32);
void fn_80253EE4(const char*, f32);
#if TARGET_PC
FE10_PROTO ptr32<void> fn_80127A90(void*);
#else
void* fn_80127A90(void*);
#endif
#if TARGET_PC
FE10_PROTO void fn_801C6D94(i32arg, f32, f32, f32);
#else
void fn_801C6D94(void*, f32, f32, f32);
#endif
class V { public: virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(void*); };
struct S48 { u8 p[0x40]; f32 a40; u8* a44; };
static inline void sfxLoop(const char* s) {
    if ((s8)fn_8024F92C(s) < 0) fn_80253EE4(s, 0.0f);
}
void fn_8021EA80(V* o0, void* a) {
    S48* o = (S48*)o0;
    f32 c; f32 t;
    o0->v18(a);
    int n=fn_8011B8A4(o->a44 + 0x12c); c=*(const f32*)&o->a40; t=n;
    if (*(const f32*)&o->a40 < t) {
        o->a40 += 0.2f;
        if (o->a40 > t) o->a40 = t;
        sfxLoop(lbl_80371B80 + 0xb1);
    } else if (c > t) {
        o->a40 -= 0.2f;
        if (o->a40 < t) o->a40 = t;
        sfxLoop(lbl_80371B80 + 0xb1);
    } else {
        fn_80255060(lbl_80371B80 + 0xb1, 0.0f);
    }
    {
        f32 z = o->a40;
        int x = 0x41; int y = 0x2c;
        fn_801C6D94(fn_80127A90(o->a44), x, y, z);
    }
}
}
