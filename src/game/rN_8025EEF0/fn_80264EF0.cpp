/* Dictionary menu: name caption */
#include "game/rN_8025EEF0/dict.h"
#include "game/rN_8025EEF0/calls.h"

#pragma use_lmw_stmw on

extern "C" {

void fn_801BCA5C(f32 v);
void fn_801BCA94(void);
void* fn_80076F54(const char* s);
const char* fn_80118C44(void* p);
int fn_800CA3DC(const char* s, int a, f32 v);
void fn_801C6DA0(int a, const char* s, f32 x, f32 y);

void fn_80264EF0(int x, int y) {
    DictState* pg;
    const char* text;
    const char* msg;
    pg = DICT_PAGE(lbl_804CC004, lbl_804CC004->page);
    fn_801BCA5C(-3.0f);
    switch (lbl_804CC004->mode) {
    case 0:
        msg = 0;
        break;
    case 1:
        switch (lbl_804CC004->page) {
        case 0: {
            void* u = fn_80076F54(*(const char**)lbl_804CC004->list[pg->cur]);
            if (u != 0) {
                msg = fn_80118C44(u);
            } else {
                msg = lbl_80372C90 + 0x213;
            }
            break;
        }
        case 1:
            msg = *(const char**)lbl_804CC004->list[pg->cur];
            break;
        }
        break;
    }
    fn_801BCA94();
    if (msg != 0) {
        text = fn_800D0864(msg);
        fn_801C6DA0(8, text, x - fn_800CA3DC(fn_800D0864(msg), -1, 1.0f) / 2, y);
    }
    fn_801BCA5C(3.0f);
}

}
