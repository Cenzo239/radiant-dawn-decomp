#include "game/rS_8023FD30/types.h"
#pragma auto_inline off
struct Col4 { u8 r, g, b, a; };
class Item {
public:
    virtual void v08();
    virtual const char* v0C();
    virtual void v10();
    virtual void v14();
    virtual int v18();
    virtual void v1C();
    virtual int v20();
    int kind;
};
struct LW {
    void* vt;
    u8 pad04[0x12 - 4];
    s16 v12;
    s16 v14;
    s16 v16;
    s16 v18;
    u8 pad1A[0x38 - 0x1A];
    u32 flags;
};
extern "C" {
extern char lbl_80372780[];
void fn_8007E154(void);
#if TARGET_PC
FE10_PROTO void fn_8007E174(p32arg, u16);
#else
void fn_8007E174(s32, u16);
#endif
void fn_8007E164(void);
void fn_800800D4(s32);
void fn_80080330(f32, f32);
void fn_80080508(Col4*);
void fn_80080ABC(f32, s32);
void fn_80080A94(f32);
const char* fn_800D0864(const char*);
void fn_80080C24(const char*);
void fn_80080308(void);
void fn_8007E720(f32);
int fn_800CB0FC(int, f32);
void fn_800CB278(int, s16, u8, const char*, ...);
void fn_801D8ADC(int, s16, s16, int);
}
static inline void setCol(Col4 c) { fn_80080508(&c); }
static inline void pos(int x, int y) { fn_80080330(x, y); }
extern "C" {
void fn_802409E4(LW* w, int x, int y, Item* it) {
    fn_8007E154();
    fn_8007E174(0, (u16)(w->flags | 3));
    fn_8007E164();
int d = (0x1E - fn_800CB0FC(-1, 1.0f)) >> 1; bool off = it->v20() == 0; int yy = y + d; fn_800CB278(x, yy, off, fn_800D0864(it->v0C()));
    Col4 c = {0xFF, 0xBC, 0x75, 0xFF};
    switch (it->kind) {
    case 0:
        fn_800800D4(5);
        pos(x + 0x12A, yy);
        setCol(c);
        fn_80080ABC(2.0f, 1);
        fn_80080C24(fn_800D0864(lbl_80372780 + 0x4F));
        fn_80080308();
        break;
    case 1:
        fn_800800D4(5);
        pos(x + 0x12A, yy);
        setCol(c);
        fn_80080ABC(2.0f, 1);
        switch (it->v18()) {
        case 1:
            fn_80080C24(fn_800D0864(lbl_80372780 + 0x61));
            break;
        case 2:
            fn_80080C24(fn_800D0864(lbl_80372780 + 0x74));
            break;
        case 3:
            fn_80080C24(fn_800D0864(lbl_80372780 + 0x87));
            break;
        }
        fn_80080308();
        break;
    }
    fn_8007E154();
    fn_8007E720(1.8f);
    fn_8007E164();
    fn_801D8ADC(x, y + 0x16, (s16)(w->v16 - w->v12) - 0x40, 0x10);
    fn_8007E154();
    fn_8007E720(-1.8f);
    fn_8007E164();
}
}
