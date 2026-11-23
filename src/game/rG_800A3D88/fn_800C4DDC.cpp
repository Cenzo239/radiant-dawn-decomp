/* Face portrait: draws the frame, then the mouth and both eyes when the
   portrait resource has them (names guessed). */
#include "game/rG_800A3D88/types.h"

extern "C" {
struct FR { u8 p[0x20]; u16 m20; };
struct Face {
    u8 p[0x30];
    void* m30;
    FR* m34;
    u8 p38[0x10];
    u32 m48;
};
void fn_800C4EDC(Face* f, int x, int y, int a, int flag, f32 z);
void fn_800C57B0(Face* f, int x, int y, int a, int k, int flag, f32 z);
void fn_800C5A34(f32 z, Face* f, int x, int y, int a, int which, int k, int flag);

void fn_800C4DDC(int x, int y, int a, Face* f) {
    fn_800C4EDC(f, x, y, a, 0, 0.0f);
    if (f->m34->m20 & 2) {
        fn_800C57B0(f, x, y, a, (f->m48 & 0x800) ? 7 : 4, 0, 0.0f);
    }
    if (f->m34->m20 & 1) {
        fn_800C5A34(0.0f, f, x, y, a, 0, 0, 0);
        fn_800C5A34(0.0f, f, x, y, a, 1, 0, 0);
    }
}
}
