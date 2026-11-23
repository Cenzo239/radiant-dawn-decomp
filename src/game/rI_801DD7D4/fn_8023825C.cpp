/* Message-queue worker pool: file statics at lbl_80423120. */
#include "game/rI_801DD7D4/fn_thp.h"
#pragma auto_inline off

extern "C" {
static u8 sQ1[0x20];
static u8 sQ2[0x20];
static u8 sThread[0x318];
static u8 sStack[0x2000];
extern u32 lbl_804CBF84;
extern void* lbl_804CBF80;
extern void* lbl_804CBF88;
extern void* lbl_804CBF8C;
struct Cmd { int a, b, c, d, e, f; };
void fn_802381C8(void*);

void fn_8023825C(u32 n) {
    u32 i;
    lbl_804CBF84 = n;
    lbl_804CBF80 = fn_80079940(n * 0x18, 0x40);
    lbl_804CBF88 = fn_80079940(n * 4, 0x40);
    lbl_804CBF8C = fn_80079940(n * 4, 0x40);
    fn_8031D224(sQ1, lbl_804CBF88, n);
    fn_8031D224(sQ2, lbl_804CBF8C, n);
    for (i = 0; i < n; i++) {
        fn_8031D284(sQ2, (Cmd*)lbl_804CBF80 + i, 1);
    }
    fn_8031FC48(sThread, fn_802381C8, 0, sStack + 0x2000, 0x2000, 0x10, 1);
    fn_803202B0(sThread);
}
#pragma push
#pragma use_lmw_stmw on
int fn_8023835C(int a, int b, int c, int d, int e, int f) {
    Cmd* m;
    fn_8031D34C(sQ2, &m, 1);
    m->a = a;
    m->b = b;
    m->c = c;
    m->d = d;
    m->e = e;
    m->f = f;
    fn_8031D284(sQ1, m, 1);
    return 1;
}
#pragma pop
}
