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
#if TARGET_PC
extern FE10_PROTO void * fn_80076F54(char*);
#else
extern int fn_80076F54(char*);
#endif
extern u8* fn_80077064(char*);
extern void* fn_800791B0(u32);
extern u8* fn_801CBA60(Mesh*, u8*);
extern u8 fn_80109A18(u8**);
extern u16 fn_80109A2C(u8**);
extern u32 fn_80109A50(u8**);
extern f32 fn_80109AD0(u8**);
#if TARGET_PC
extern FE10_PROTO ptr32<char> fn_80109A88(u8**);
#else
extern char* fn_80109A88(u8**);
#endif
extern u8 fn_801194FC(char*);
extern void fn_8013A35C(MapModel*);
extern void fn_80136C34(MapModel*);

int fn_8013608C(MapModel* mm) {
    char path[0x48];
    u8* p;
    Mesh* m;
    int i;
    fn_80290DDC(path, lbl_803694D4 + 0xA4, mm->name);
    if (fn_80076F54(path) == 0) return 0;
    p = fn_80077064(path);
    if (mm->nMesh > 0) {
        mm->mesh = (Mesh*)fn_800791B0(mm->nMesh * 0xD0);
    } else {
        mm->mesh = 0;
    }
    m = mm->mesh;
    for (i = 0; i < mm->nMesh; i++, m++) {
        p = fn_801CBA60(m, p);
    }
    return 1;
}

void fn_80136164(MapModel* mm) {
    char path[0x48];
    u8* r;
    u8 ver;
    fn_80290DDC(path, lbl_803694D4 + 0xAF, mm->name);
    if (fn_80076F54(path)) {
        r = fn_80077064(path);
        mm->version = ver = fn_80109A18(&r);
        if (ver >= 2) {
            fn_80109A18(&r);
            mm->x4c = fn_80109A18(&r);
            mm->x4d = fn_80109A18(&r);
            mm->nGroup = fn_80109A2C(&r);
            mm->nMesh = fn_80109A2C(&r);
            mm->xc4 = 1.0f / fn_80109AD0(&r);
            mm->xab = fn_80109A18(&r);
            mm->xac = fn_80109A18(&r);
            mm->xad = fn_80109A18(&r);
            mm->xae = fn_80109A18(&r);
            mm->xaf = fn_80109A18(&r);
            mm->xb0 = fn_80109A18(&r);
            lbl_804CA734 = fn_80109A18(&r);
            fn_80109A18(&r);
            mm->flags = 0;
            mm->flags |= fn_80109A50(&r);
            mm->xbb = fn_80109A18(&r);
            mm->xb8 = fn_80109A18(&r);
            mm->xb9 = fn_80109A18(&r);
            mm->xba = fn_80109A18(&r);
            lbl_804CB84C = fn_80109A18(&r);
            lbl_804CB84F = fn_80109A18(&r);
            lbl_804CB850 = fn_80109A18(&r);
            lbl_804CB851 = fn_80109A18(&r);
            lbl_804CB852 = 0;
            if (mm->version >= 3) {
                mm->x4e = fn_801194FC(fn_80109A88(&r));
                if (mm->version >= 4) {
                    mm->xc8 = fn_80109AD0(&r);
                }
            }
            fn_8013A35C(mm);
        }
    }
}

static inline void SetColor(Color* d, Color c) { *d = c; }

void fn_80136348(MapModel* mm) {
    char path[0x48];
    Color c;
    u8* r;
    int i;
    fn_80290DDC(path, lbl_803694D4 + 0xBA, mm->name);
    if (fn_80076F54(path)) {
        r = fn_80077064(path);
        fn_80109A18(&r);
        fn_80109A18(&r);
        lbl_804CB840 = fn_80109A2C(&r);
        lbl_804CB842 = fn_80109A2C(&r);
        lbl_804CB844 = fn_80109A2C(&r);
        for (i = 0; i < 4; i++) {
            c.r = fn_80109A18(&r);
            c.g = fn_80109A18(&r);
            c.b = fn_80109A18(&r);
            SetColor(&lbl_80413BF8[i], c);
            c.r = fn_80109A18(&r);
            c.g = fn_80109A18(&r);
            c.b = fn_80109A18(&r);
            SetColor(&lbl_80413BE8[i], c);
        }
    }
}

static inline void SetFog(u8 mode, u8 start, u8 end, Color c) {
    lbl_804CB839 = mode;
    lbl_804CB83A = start;
    lbl_804CB83B = end;
    lbl_804CB83C = c;
}

void fn_8013677C(MapModel* mm) {
    char path[0x48];
    u8* r;
    fn_80290DDC(path, lbl_803694D4 + 0xC6, mm->name);
    if (fn_80076F54(path)) {
        u8 on;
        u8 mode;
        u8 st;
        u8 en;
        Color c;
        r = fn_80077064(path);
        fn_80109A18(&r);
        on = fn_80109A18(&r);
        {
            u8 a = fn_80109A18(&r);
            mode = on ? (u8)(a + 1) : 0;
        }
        st = fn_80109A18(&r);
        en = fn_80109A18(&r);
        c.r = fn_80109A18(&r);
        c.g = fn_80109A18(&r);
        c.b = fn_80109A18(&r);
        c.a = 0;
        SetFog(mode, st, en, c);
    } else {
        Color z = {0, 0, 0, 0};
        SetFog(0, 0, 0, z);
    }
}

#if TARGET_PC
extern FE10_PROTO void fn_80010968(p32arg);
#else
extern void fn_80010968(int);
#endif
extern u8* fn_80010960(void);
extern void fn_80010AB8(void);
extern void fn_80010AE4(void);

extern u8* fn_8017C218(u8, void*);
extern const Color lbl_804CDE8C;

extern void fn_80113428(void*);
extern void fn_8011398C(void*);
extern void fn_801136C0(void*);
extern void fn_801135C0(void*);

void fn_80137988(MapModel* mm, int b) {
    fn_80113428(lbl_803EC898);
    fn_80136C34(mm);
    fn_8011398C(lbl_803EC898);
    fn_801136C0(lbl_803EC898);
    if (b) fn_801135C0(lbl_803EC898);
}

} /* extern "C" */
