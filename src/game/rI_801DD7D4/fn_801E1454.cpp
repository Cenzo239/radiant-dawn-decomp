#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/vobj.h"
#pragma auto_inline off
extern "C" {
#if TARGET_PC
FE10_PROTO char * fn_800D0864(p32arg);
#else
int fn_800D0864(int);
#endif
void fn_8007E154(void);
void fn_8007E164(void);
#if TARGET_PC
FE10_PROTO void fn_8007E174(p32arg, int);
#else
void fn_8007E174(int, int);
#endif
void fn_8007E720(f32);
#if TARGET_PC
FE10_PROTO void fn_8007E74C(ptr32<const void>, ptr32<const void>);
#else
void fn_8007E74C(void*, void*);
#endif
void fn_8007E7B4(void);
int fn_800CB0FC(f32, int);
void fn_801E6DA0(int, int, int, const char*, ...);
void fn_800800D4(int);
void fn_80080330(f32, f32);
void fn_80080508(void*);
void fn_80080C24(const char*);
void fn_80080308(void);
void fn_803080DC(int, int, int, int);
extern char lbl_8036ED78[];
struct Rect16 { s16 x, y, w, h; };
void fn_801E2204(void*, s16*, s16*);
struct GXC { u8 r, g, b, a; };
class Lbl { public:
 virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
 virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual GXC* v34();
 virtual void v38(); virtual void v3C(); virtual const char* v40(); virtual int v44();
 u8 pad[0xe]; s16 x12, x14, x16, x18; u8 p1[4]; s16 x1e, x20; u8 p2[0x16]; int x38; u8 p3[4]; int x40; s16 x44; u8 p4[2]; s16 x48, x4a, x4c, x4e; };
void fn_801E2104(void*, Rect16*);
static inline void rectSet(Lbl* o, s16 a, s16 b, s16 c, s16 d) {
    o->x48 = a;
    o->x4a = b;
    o->x4c = c;
    o->x4e = d;
}
void fn_801E1454(Lbl* o) {
    
    const char* s;
    int x;
    int h;
    int y;
    int hh;

    o->v18();
    x = o->x1e;
    h = o->x44;
    y = o->x20;
    hh = (s16)(y + ((h - fn_800CB0FC(1.0f, -1)) >> 1));
    s = o->x40 ? (const char*)fn_800D0864(o->x40) : lbl_8036ED78;
    if (s != NULL) {
        rectSet(o, 0, 0, o->x16 - o->x12, o->x18 - o->x14);
        fn_801E2204(o, &o->x48, &o->x48);
        fn_801E2204(o, &o->x4c, &o->x4c);
        fn_8007E154();
        fn_8007E74C((void*)fn_801E2104, &o->x48);
        fn_8007E720(-1.0f);
        fn_8007E174(0, (u16)(o->x38 | 3));
        fn_8007E164();
        fn_801E6DA0(x, hh, 0x1f, s);
        fn_8007E154();
        fn_8007E7B4();
        fn_8007E164();
    }
}
static inline void sr5(s16 w, s16 h, const Rect16& r) { fn_803080DC(r.x, r.y, w, h); }
void fn_801E2104(void* a, Rect16* src) {
    Rect16 r = *src;
    r.x = r.x < 0 ? 0 : r.x > 0x7ff ? 0x7ff : r.x;
    r.y = r.y < 0 ? 0 : r.y > 0x7ff ? 0x7ff : r.y;
    r.w = r.w < 0 ? 0 : r.w > 0x7ff ? 0x7ff : r.w;
    r.h = r.h < 0 ? 0 : r.h > 0x7ff ? 0x7ff : r.h;
    sr5(r.w - r.x, r.h - r.y, r);
}
}
