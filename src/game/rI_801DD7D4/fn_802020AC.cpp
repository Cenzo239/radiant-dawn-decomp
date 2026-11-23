/* fn_802020AC: builds the help bar (0x68 widget, id -0x1000) and a 0x48 info panel (id 3) holding a
   resource looked up by name and an icon for byte +0x44 of the screen, then sets the help text from the
   screen's context (+0x48)->+0x30.
   Exact (check_func.py --symbol-map fn_802020AC.symbols.json --strict-references). */
#include "game/rI_801DD7D4/types.h"
#include "game/helpbar.h"

/* 0x48 panel: HbWidget plus two pointers; its constructor calls slot 9 (vtable +0x2C). */
class HbInfoPanel : public HbWidget {
public:
    void* a40; void* a44;
    virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual void v9();
    HbInfoPanel() : HbWidget(0x14, 0x13c, 0xe4, 0x18c, 0xd0, 0x50, 0x46, 0x10) {
        a40 = 0;
        a44 = 0;
        v9();
    }
};

struct Ctx { u8 p[0x30]; const char* x30; };
struct Sc { u8 p[0x44]; u8 x44; u8 p45[3]; Ctx* x48; };
extern "C" {
void* fn_801E5640(void*, int, int);
void fn_801E5448(void*, void*);
extern char lbl_8036FBC0[];
void* fn_800D0864(const char*);
#if TARGET_PC
FE10_PROTO ptr32<void> fn_801E7204(u8);
#else
void* fn_801E7204(u8);
#endif
}
extern "C" void fn_802020AC(Sc* o) {
    HbHelpBar* s;
    HbInfoPanel* g;
    s = new HbHelpBar;
    s->id = -0x1000;
    s->s.w[3] = 1;
    s->a64 = lbl_8036FBC0;
    s->flags |= 0x10;
    s->a60 = 0;
    s->a28 = 8;
    fn_801E5448(o, s);
    g = new HbInfoPanel;
    g->id = 3;
    g->a28 = 0;
    g->a40 = fn_800D0864(lbl_8036FBC0 + 1);
    g->a44 = fn_801E7204(o->x44);
    fn_801E5448(o, g);
    {
        const char* m = o->x48->x30;
        HbHelpBar* w = (HbHelpBar*)fn_801E5640(o, -0x1000, 0);
        if (w) w->a64 = m;
    }
}
