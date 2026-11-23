// Initialize the two screen-state blocks with the original default values.
typedef float f32;
struct ScreenState {
    f32 x0, x4, x8, xC, x10, x14;
    int x18;
    f32 x1C;
    int x20;
    f32 x24, x28;
};
struct SecondState { f32 x0, x4, x8, xC, x10; unsigned char pad[0x2150]; };
extern struct ScreenState lbl_80430D00;
extern struct SecondState lbl_80430D2C;
extern f32 lbl_804D0B68;
extern f32 lbl_804D0B78;
extern f32 lbl_804D0B98;
extern f32 lbl_804D0BC4;
extern f32 lbl_804D0BC8;
extern f32 lbl_804D0BCC;
extern f32 lbl_804D0BD0;
extern f32 lbl_804D0BD4;
extern f32 lbl_804D0BD8;

void fn_8028BC54(void) {
    lbl_80430D00.x0 = lbl_804D0BC4;
    lbl_80430D00.x4 = lbl_804D0BC8;
    lbl_80430D00.x8 = lbl_804D0BCC;
    lbl_80430D00.xC = lbl_804D0BD0;
    lbl_80430D00.x10 = lbl_804D0B98;
    lbl_80430D00.x14 = lbl_804D0B78;
    lbl_80430D00.x18 = 5;
    lbl_80430D00.x1C = lbl_804D0BC4;
    lbl_80430D00.x20 = 0;
    lbl_80430D00.x24 = lbl_804D0B68;
    lbl_80430D00.x28 = lbl_804D0B78;
    lbl_80430D2C.x0 = lbl_804D0BD4;
    lbl_80430D2C.x4 = lbl_804D0BD8;
    lbl_80430D2C.x8 = lbl_804D0B78;
    lbl_80430D2C.xC = lbl_804D0B68;
    lbl_80430D2C.x10 = lbl_804D0B78;
}
