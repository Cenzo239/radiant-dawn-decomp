/* Dictionary menu: description text */
#include "game/rN_8025EEF0/dict.h"
#include "game/rN_8025EEF0/prim2d.h"

extern "C" {

f32 fn_8017F68C(f32 a, f32 b, f32 c, f32 d, int e);
void fn_801BCA5C(f32 v);
void fn_801BCA94(void);
void fn_80263D18(const char* s);
void fn_800809D0(void);
void fn_80080330(f32 x, f32 y);
void fn_800804D4(int r, int g, int b, int a);
void fn_80080C24(const char* s);

void fn_80265060(int x, int y) {
        int i;
    u8* m;
    DictState* pg;
    int off;
    int yy;
    u8 alpha;
    int msg;

    msg = (int)fn_8017F68C(0.0f, 255.0f, 12 - *(s8*)((u8*)lbl_804CC004 + 0x70), 12.0f, 0);
    pg = DICT_PAGE(lbl_804CC004, lbl_804CC004->page);
    fn_801BCA5C(-1.0f);
    alpha = (u8)msg < 0x5A ? 0 : (u8)msg;
    switch (lbl_804CC004->mode) {
    case 0:
        msg = 0;
        break;
    case 1:
        switch (lbl_804CC004->page) {
        case 0:
            msg = *(int*)((u8*)lbl_804CC004->list[pg->cur] + 8);
            break;
        case 1:
            msg = *(int*)((u8*)lbl_804CC004->list[pg->cur] + 8);
            break;
        }
        break;
    }
    if (msg != 0) {
        fn_801BCA94();
        fn_80263D18(fn_800D0864((const char*)msg));
        fn_801BCA94();
        yy = y + 0x28; i = 0; off = 0;
        for (; i < lbl_804CC004->nlines; off += 4, yy += 0x1C, i++) {
            if (*(char**)((u8*)lbl_804CC004->lines + off) != 0) {
                fn_800800D4(5);
                fn_800809D0();
                fn_80080330(x + 0xE, yy);
                fn_800804D4(0xE4, 0xC3, 0xA0, alpha);
                fn_80080C24(*(char**)((u8*)lbl_804CC004->lines + off));
                fn_80080308();
            }
        }
    }
    if (lbl_804CC004->page == 0 && (m = (u8*)lbl_804CC004->m74) != 0) {
        f32 fx = x + 0xB5;
        f32 fy = y + 0x146;
        *(f32*)(m + 0x38) = fx;
        *(f32*)(m + 0x3C) = fy;
        if (lbl_804CC004->nlines < 7) {
            *((u8*)lbl_804CC004->m74 + 0x42) = alpha;
        } else {
            *((u8*)lbl_804CC004->m74 + 0x42) = 0;
        }
    }
    if (lbl_804CC004->m7C != 0) {
        *((u8*)lbl_804CC004->m7C + 0x64) = alpha;
    }
    fn_801BCA5C(1.0f);
}

}
