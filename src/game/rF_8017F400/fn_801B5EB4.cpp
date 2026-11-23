/* fn_801B5EB4: draw a text line with a scissor mode (0 none, 1..3 the fn_801B5E3C family) and a palette colour. */
#include "game/rF_8017F400/types.h"
extern "C" {
extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E4E4(f32, f32, f32, f32);
#if TARGET_PC
extern FE10_PROTO void fn_8007E174(p32arg, int);
#else
extern void fn_8007E174(int, int);
#endif
extern void fn_8007E7DC(int);
extern void fn_8007E7B4(void);
#if TARGET_PC
extern FE10_PROTO void fn_8007E74C(ptr32<const void>, ptr32<const void>);
#else
extern void fn_8007E74C(void*, void*);
#endif
extern void fn_800800D4(int);
extern void fn_80080330(f32, f32);
extern u8* fn_800CD204(int);
extern void fn_80080508(GXColor);
extern void fn_80080B00(int, GXColor, f32);
extern void fn_80080C24(const char*);
extern void fn_80080308(void);
extern void fn_801B5E3C(void);
extern void fn_801B5E50(void);
extern void fn_801B5E64(void);
extern GXColor lbl_804CF2C0;
static inline void SetCol(u8* p) { fn_80080508(*(GXColor*)p); }
void fn_801B5EB4(int mode, int col, const char* s, f32 x, f32 y) {
    if (s == 0) return;
    fn_8007E154();
    fn_8007E4E4(x, y, 300.0f, 1.0f);
    fn_8007E174(0, 0x13);
    fn_8007E7DC(0xFF);
    switch (mode) {
    case 1: fn_8007E74C((void*)fn_801B5E50, 0); break;
    case 2: fn_8007E74C((void*)fn_801B5E3C, 0); break;
    case 3: fn_8007E74C((void*)fn_801B5E64, 0); break;
    case 0: fn_8007E7B4(); break;
    }
    fn_8007E164();
    fn_800800D4(5);
    fn_80080330(0.0f, 0.0f);
    SetCol(fn_800CD204((u8)col));
    fn_80080B00(1, lbl_804CF2C0, 1.0f);
    fn_80080C24(s);
    fn_80080308();
}
}
