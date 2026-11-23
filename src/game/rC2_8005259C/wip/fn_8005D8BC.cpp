/* NEAR MISS: 4 of 82 words (fn_8005DFD0 differs only in the callee fn_8006F6A4). `w` wants r29 and
 * `top` r30, ours are swapped. Declaration order, an inline for the centring and an int w did not help. */
#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw off
class ECmd { public: VPAD(0) VPAD(1) VPAD(2) VPAD(3) virtual const char* v18(MenuEntry* e); };
typedef struct MEnt { u8 pad0[0x30]; s16 x; s16 y; ECmd* cmd; u8 b38; u8 active; } MEnt;
class SelfD { public:
  VPAD(0) VPAD(1) VPAD(2) VPAD(3) VPAD(4) VPAD(5) VPAD(6) VPAD(7)
  VPAD(8) VPAD(9) VPAD(10) VPAD(11) VPAD(12) VPAD(13) VPAD(14) VPAD(15)
  VPAD(16) VPAD(17) 
  virtual void v50(Menu* m);
  virtual void v54(MEnt* e);
};
extern "C" {
int fn_800CB0FC(int n, f32 s);
int fn_800CA3DC(const char* str, int n, f32 s);
void fn_8006F1B4(int a, s16 b, u8 c);
void fn_800800D4(int n);
void fn_80080330(f32 x, f32 y);
void fn_80080ABC(int a, f32 s);
void fn_80080C24(const char* s);
void fn_80080308(void);
}
extern "C" void fn_8005D8BC(SelfD* self, Menu* m, MEnt* e) {
        const char* s;
    int fh;
    int top;
    int tw;
    s16 w;

    w = m->owner->v50();
    top = (0x1f - fn_800CB0FC(-1, 1.0f)) >> 1;
    s = e->cmd->v18((MenuEntry*)e);
    tw = fn_800CA3DC(s, -1, 1.0f);
    fn_8006F1B4(0, e->y, e->b38);
    self->v50(m);
    fn_800800D4(5);
    fn_80080330((f32)((w - tw) >> 1), (f32)(top + e->y));
    self->v54(e);
    fn_80080ABC(1, 2.0f);
    fn_80080C24(e->cmd->v18((MenuEntry*)e));
    fn_80080308();
}
/* SOLVED: see ../fn_8005D8BC.cpp (declare top as s16). Kept only for history. */
