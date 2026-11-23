/* fn_80136C34: functionally equal (regs level per tools/check_regs.py; registers differ from the original). .maplink loaders: three tile link tables. From wip/near2.cpp with the declarations of fn_8013608C.cpp (bodies stripped). */
/* Map model: loading of the per-map data files (.mapinst, .mapdata, .maplight, .mapfog, .mapshader, .maplink). */
#include "game/rL_80133EB4/map3d.h"
#pragma auto_inline off
#pragma use_lmw_stmw on

extern "C" {

struct Color { u8 r, g, b, a; };

extern char lbl_803694D4[];
extern u8 lbl_803EC898[];
extern u8 lbl_804CB830;
extern u8 lbl_804CB838;
extern u8 lbl_804CB839;
extern u8 lbl_804CB83A;
extern u8 lbl_804CB83B;
extern Color lbl_804CB83C;
extern u8 lbl_804CB83D;
extern u8 lbl_804CB83E;
extern u8 lbl_804CB83F;
extern s16 lbl_804CB840;
extern s16 lbl_804CB842;
extern s16 lbl_804CB844;
extern u8 lbl_804CB84C;
extern u8 lbl_804CB84F;
extern u8 lbl_804CB850;
extern u8 lbl_804CB851;
extern u8 lbl_804CB852;
extern u8 lbl_804CA734;
extern Color lbl_80413BE8[4];
extern Color lbl_80413BF8[4];

extern void fn_80290DDC(char*, const char*, ...);
extern int fn_80076F54(char*);
extern u8* fn_80077064(char*);
extern void* fn_800791B0(u32);
extern u8* fn_801CBA60(Mesh*, u8*);
extern u8 fn_80109A18(u8**);
extern u16 fn_80109A2C(u8**);
extern u32 fn_80109A50(u8**);
extern f32 fn_80109AD0(u8**);
extern char* fn_80109A88(u8**);
extern u8 fn_801194FC(char*);
extern void fn_8013A35C(MapModel*);
extern void fn_80136C34(MapModel*);

int fn_8013608C(MapModel* mm);

void fn_80136164(MapModel* mm);

static inline void SetColor(Color* d, Color c) { *d = c; }

void fn_80136348(MapModel* mm);

static inline void SetFog(u8 mode, u8 start, u8 end, Color c) {
    lbl_804CB839 = mode;
    lbl_804CB83A = start;
    lbl_804CB83B = end;
    lbl_804CB83C = c;
}

void fn_8013677C(MapModel* mm);

extern void fn_80010968(int);
extern u8* fn_80010960(void);
extern void fn_80010AB8(void);
extern void fn_80010AE4(void);

extern u8* fn_8017C218(u8, void*);
extern const Color lbl_804CDE8C;

extern void fn_80113428(void*);
extern void fn_8011398C(void*);
extern void fn_801136C0(void*);
extern void fn_801135C0(void*);

void fn_80137988(MapModel* mm, int b);

} /* extern "C" */

/* ---- fn_80136C34 ---- */
struct ML { u8 pad[0x508E]; u16 link[0x1000]; };
#define L(i) ((ML*)lbl_803EC898)->link[i]
#define HDR(off) fn_80290DDC(path, lbl_803694D4 + off, mm->name); if (fn_80076F54(path)) { r = fn_80077064(path); fn_80109A18(&r); fn_80109A18(&r);
extern "C" {
void fn_80136C34(MapModel* mm) {
    char path[0x48];
    u8* r = 0;
    /*P*/
    int x1;
    int y1;
    int n1;
    int n3;
    int x2;
    int y2;
    int n2;
    int i2;
    int x3;
    int y3;
    int i1;
    int i3;
/*E*/
    HDR(0xDD)
        n1 = fn_80109A2C(&r);
        for (i1 = 0; i1 < n1; i1++) {
            u8 v;
            x1 = (s8)fn_80109A18(&r);
            y1 = (s8)fn_80109A18(&r);
            v = fn_80109A18(&r);
            L(x1 + y1 * 0x40) = v;
        }
    }
    HDR(0xE8)
        n2 = fn_80109A2C(&r);
        for (i2 = 0; i2 < n2; i2++) {
            u8 v;
            x2 = (s8)fn_80109A18(&r);
            y2 = (s8)fn_80109A18(&r);
            v = fn_80109A18(&r);
            L(x2 + y2 * 0x40) = (L(x2 + y2 * 0x40) & ~0xF00) | (v << 8);
        }
    }
    HDR(0xF5)
        n3 = fn_80109A2C(&r);
        for (i3 = 0; i3 < n3; i3++) {
            u8 v;
            x3 = (s8)fn_80109A18(&r);
            y3 = (s8)fn_80109A18(&r);
            v = fn_80109A18(&r);
            L(x3 + y3 * 0x40) = v + (~v & 0xF) * 0x10;
        }
    }
}
}
