/* Round 23 (r23b), exact: fn_800EF0D8. From wip/r18_fn_800EF0D8.cpp; the only change is the callee prototype from
   docs/signatures/CATALOG.tsv, fn_8007E374(void*, void*, u16): with it 'ori r5,r30,1' schedules before 'mr r4,r31'.
   The old draft's comment follows. */
/* fn_800EF0D8 (round 18): NOT at regs level (class other): same 97 instructions, one pair swapped. The original has
   'ori r5,r30,1' before 'mr r4,r31' in the fn_8007E374 call; ours schedules mr first. 30 spellings of the two arguments tried.
   The ternary as the fifth argument of fn_80080430 is what fixed the float argument schedule. Functionally the same code. */
/* fn_800EF0D8: battle gauge frame sprite (the wide or narrow variant by b47), optionally as the glow pass. */
#include "game/rE_800E5DE4/types.h"
#pragma auto_inline off
typedef struct GProc { u8 pad[0x3C]; void* font; u8 pad40[7]; u8 b47; } GProc;
extern "C" {
extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E4E4(f32, f32, f32, f32);
extern void fn_8007E374(void*, void*, u16);
extern void fn_8007E7DC(u8);
extern void fn_8007E7F4(void);
extern void fn_800800D4(int);
extern void fn_80080430(f32, f32, f32, f32, f32, f32);
extern void fn_80080578(int);
extern void fn_80080308(void);
static inline int GW(GProc* p) { int c = 0xF0; if (p->b47 == 0) c = 0xE8; return c; }
static inline int GH(GProc* p) { int d = 0x58; if (p->b47 == 0) d = 0x48; return d; }
void fn_800EF0D8(f32 x, f32 y, GProc* p, int alpha, int flag) {
    int a;
    int f2;
    int fl;
    s16 ofs;
    f32 z = 404.0f;
    fl = 0x10;
    if (flag) {
        fl = 0x20;
        z -= 1.0f;
    }
    ofs = p->b47 == 0 ? 0 : -8;
    a = 5;
    if (p->b47 == 0) a = 0xA;
    fn_8007E154();
    fn_8007E4E4(x + ofs, y, z, 1.0f);
    fn_8007E374(p->font, (void*)a, fl | 1);
    fn_8007E7DC(alpha);
    fn_8007E164();
    fn_800800D4(1);
    {
        int d = 0x58;
        if (p->b47 == 0) d = 0x48;
        fn_80080430(0.0f, 0.0f, 0.0f, 0.0f, p->b47 == 0 ? 0xE8 : 0xF0, d);
    }
    fn_80080578(0);
    fn_80080308();
    fn_8007E7F4();
}
}
