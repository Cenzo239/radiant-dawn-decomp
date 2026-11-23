/* fn_80023360: Sally (battle preparation) menu init: parses the proc's name string into a list of
   (x, y) byte pairs fed to the deploy table lbl_803E7320, starts the child proc lbl_80378968, adds the
   help bar (0x68 widget, id -0x1000, line 2 on), clears three field-config bytes and sets bit 16 of
   the global state word.
   Exact (check_func.py --symbol-map fn_80023360.symbols.json --strict-references). */
#include "game/rA_800068A0/types.h"
#include "game/helpbar.h"

extern "C" {
struct SsoStr {
    u32 isLong : 1;
    u32 pad : 31;
    u32 pad4;
    char* ptr;
};
struct Sub2C { u8 pad[0x2C]; u8 b2C; };
struct SallyM { u8 pad[0x40]; SsoStr s; void* p4c; Sub2C* p50; };
struct Fld { u8 pad[0x21]; u8 b21; u8 b22; u8 pad2[5]; u32 w28; };
extern char lbl_80361118[];
extern int lbl_803E7320[0x20];
extern u8 lbl_80378968[];
extern u8 lbl_803CAB38[];
extern u8 lbl_804CB140;
extern u32 lbl_804CB700;
extern void* fn_80081050(void*, void*);
extern void fn_8012FC90(void);
extern int fn_8010CF20(const char*, char*);
extern void fn_800CFB34(void*);
#if TARGET_PC
extern FE10_PROTO void fn_800CFC50(void*, int, int, int, p32arg);
#else
extern void fn_800CFC50(void*, int, int, int, int);
#endif
extern Fld* fn_80060728(void*);
extern void* fn_801E5640(void*, int, int);
extern void fn_801E5448(void*, void*);

void fn_80023360(SallyM* p) {
    char buf[0x80];
    int n;
    u8* q;
    int i;
    Sub2C* c;
    lbl_804CB140 = 0;
    lbl_804CB700 &= ~1;
    n = fn_8010CF20(!p->s.isLong ? (char*)&p->s + 1 : p->s.ptr, buf);
    fn_800CFB34(lbl_803E7320);
    q = (u8*)buf;
    for (i = 0; i < n; i++) {
        fn_800CFC50(lbl_803E7320, (s8)q[0], (s8)q[1], 0, 0);
        q += 2;
    }
    c = (Sub2C*)fn_80081050(lbl_80378968, p);
    p->p50 = c;
    c->b2C |= 8;
    {
        HbHelpBar* b = new HbHelpBar(0x316);
        int one = 1;
        HbHelpBar* x;
        b->id = -0x1000;
        b->s.w[3] = one;
        b->a64 = lbl_80361118;
        b->flags |= 0x10;
        b->a60 = 0;
        b->a28 = 8;
        fn_801E5448(p, b);
        x = (HbHelpBar*)fn_801E5640(p, -0x1000, 0);
        if (x != 0) x->a60 = one;
    }
    {
        Fld* f;
        f = fn_80060728(lbl_803CAB38); f->b21 = 0;
        f = fn_80060728(lbl_803CAB38); f->b22 = 0;
        f = fn_80060728(lbl_803CAB38); f->w28 = 0;
    }
    lbl_804CB700 |= 0x10000;
    fn_8012FC90();
}
}
