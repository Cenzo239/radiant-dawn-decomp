/* video.cpp: screen position / width adjust menu step. Names guessed. */
#include "game/rJ_800799AC/proc.h"
#include "game/rJ_800799AC/pad.h"

struct AdjProc { u8 pad[0x34]; u8 dirty; };
struct Opt { u8 pad[0xA]; s8 w; s8 x; s8 y; };

extern "C" {
extern Pad* lbl_804CB5B8;
extern s8 lbl_804CB600;   /* x offset */
extern s8 lbl_804CB601;   /* y offset */
extern s8 lbl_804CA3D4;   /* width */
extern u8 lbl_803CAB38[];
extern char lbl_80381388[], lbl_80381398[], lbl_803813A8[], lbl_803813C0[];
extern char lbl_803813D8[], lbl_803813F0[], lbl_80381408[], lbl_80381420[];
void fn_80253EE4(const char* name, f32 vol);
Opt* fn_80060728(void*);
void fn_80083B78(void* p);
}

static inline void save(s8 x, s8 y, s8 w) {
    Opt* o = fn_80060728(lbl_803CAB38);
    o->x = x;
    o->y = y;
    o->w = w;
}

extern "C" void fn_8008C300(AdjProc* p) {
    u32 press = lbl_804CB5B8->v48();
    u32 rep = lbl_804CB5B8->v3C();
    if (lbl_804CB600 > -20 && (rep & 0x100001)) {
        lbl_804CB600--;
        p->dirty = 1;
        fn_80253EE4(lbl_80381420, 0.0f);
    } else if (lbl_804CB600 < 20 && (rep & 0x200002)) {
        lbl_804CB600++;
        p->dirty = 1;
        fn_80253EE4(lbl_80381408, 0.0f);
    }
    if (lbl_804CB601 > -15 && (rep & 0x800008)) {
        lbl_804CB601--;
        p->dirty = 1;
        fn_80253EE4(lbl_803813F0, 0.0f);
    } else if (lbl_804CB601 < 15 && (rep & 0x400004)) {
        lbl_804CB601++;
        p->dirty = 1;
        fn_80253EE4(lbl_803813D8, 0.0f);
    }
    if (lbl_804CA3D4 > 14 && (rep & 0x4000000)) {
        lbl_804CA3D4--;
        p->dirty = 1;
        fn_80253EE4(lbl_803813C0, 0.0f);
    } else if (lbl_804CA3D4 < 0x72 && (rep & 0x8000000)) {
        lbl_804CA3D4++;
        p->dirty = 1;
        fn_80253EE4(lbl_803813A8, 0.0f);
    }
    if (press & 0x1000) {
        p->dirty = 1;
        lbl_804CB600 = 0;
        lbl_804CB601 = 0;
        lbl_804CA3D4 = 0x40;
    }
    if (press & 0x400) {
        save(lbl_804CB600, lbl_804CB601, lbl_804CA3D4);
        fn_80253EE4(lbl_80381398, 0.0f);
        fn_80083B78(p);
    } else if (press & 0x800) {
        Opt* o = fn_80060728(lbl_803CAB38);
        lbl_804CB600 = o->x;
        lbl_804CB601 = o->y;
        lbl_804CA3D4 = o->w;
        p->dirty = 1;
        fn_80253EE4(lbl_80381388, 0.0f);
        fn_80083B78(p);
    }
}
