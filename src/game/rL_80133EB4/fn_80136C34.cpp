/* fn_80136C34: map model, .maplink loaders (three tile link tables read into the map's link array). */
#include "game/rL_80133EB4/map3d.h"
#pragma auto_inline off
#pragma use_lmw_stmw on

extern "C" {

extern char lbl_803694D4[];
extern u8 lbl_803EC898[];

extern void fn_80290DDC(char*, const char*, ...);
extern int fn_80076F54(char*);
extern u8* fn_80077064(char*);
extern u8 fn_80109A18(u8**);
extern u16 fn_80109A2C(u8**);

struct ML { u8 pad[0x508E]; u16 link[0x1000]; };
#define L(i) ((ML*)lbl_803EC898)->link[i]
#define HDR(off) fn_80290DDC(path, lbl_803694D4 + off, mm->name); if (fn_80076F54(path)) { r = fn_80077064(path); fn_80109A18(&r); fn_80109A18(&r);

/* Declaration order found by a hill climb; s8 x/y put the hoisted map base above them. */
void fn_80136C34(MapModel* mm) {
    char path[0x48];
    u8* r = 0;
    u8 v3;
    s8 y1;
    s8 x3;
    u8 v2;
    s8 x1;
    s8 x2;
    int n2;
    s8 y3;
    int n3;
    u8 v1;
    s8 y2;
    int n1;
    int i1;
    int i3;
    int i2;
    int o;
    HDR(0xDD)
        n1 = fn_80109A2C(&r);
        for (i1 = 0; i1 < n1; i1++) {
            x1 = fn_80109A18(&r);
            y1 = fn_80109A18(&r);
            v1 = fn_80109A18(&r);
            L(x1 + y1 * 0x40) = v1;
        }
    }
    HDR(0xE8)
        n2 = fn_80109A2C(&r);
        for (i2 = 0; i2 < n2; i2++) {
            x2 = fn_80109A18(&r);
            y2 = fn_80109A18(&r);
            v2 = fn_80109A18(&r);
            o = L(x2 + y2 * 0x40); o &= ~0xF00; o |= v2 << 8; L(x2 + y2 * 0x40) = o;
        }
    }
    HDR(0xF5)
        n3 = fn_80109A2C(&r);
        for (i3 = 0; i3 < n3; i3++) {
            x3 = fn_80109A18(&r);
            y3 = fn_80109A18(&r);
            v3 = fn_80109A18(&r);
            L(x3 + y3 * 0x40) = v3 + (~v3 & 0xF) * 0x10;
        }
    }
}

#undef HDR
#undef L

} /* extern "C" */
