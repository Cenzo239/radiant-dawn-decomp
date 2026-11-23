/* Dictionary menu: list building and paging */
#include "game/rN_8025EEF0/dict.h"

#pragma use_lmw_stmw on

extern "C" {

int fn_80291188(const char* a, const char* b);
BOOL fn_8025F6B8(const char* s, int mode);
void fn_80078E24(void* p);
void* fn_80078CCC(int size, const char* name, int a);
void fn_800C4240(void* p);
void fn_800C3FD0(void* p);
void* fn_800C6118(void* a, int b, int c, int d, void* e);
void* fn_80076F54(const char* s);

static inline int dictFind(void* sel, Dict14* e, int n) {
    int i = 0;
    for (; i < n; e++, i++) {
        if (sel == e) {
            break;
        }
    }
    return i;
}
static inline int dictFind4(void* sel, Dict10* e, int n) {
    int i = 0;
    for (; i < n; e++, i++) {
        if (sel == e) {
            break;
        }
    }
    return i;
}
#pragma push
#pragma auto_inline off
void fn_80264204(int page, int cur, int instant) {
    u8* save;
    DictState* pg;
    int ofs;
    pg = DICT_PAGE(lbl_804CC004, page);
    save = fn_8024BC94();
    ofs = cur - (int)pg->f40;
    if (ofs < 0) {
        ofs = 0;
    }
    if (ofs >= 9) {
        ofs = 8;
    }
    if (lbl_804CC004->listCount != 0) {
        int y = ofs * 0x1C + 0x84;
        if (instant) {
            pg->m2E = 0x24;
            pg->m30 = y;
            pg->m32 = 0x24;
            pg->m34 = y;
            pg->m36 = 0;
        } else {
            pg->m2E = pg->m2A;
            pg->m30 = pg->m2C;
            pg->m32 = 0x24;
            pg->m34 = y;
            pg->m36 = 4;
        }
        pg->cur = cur;
        switch (page) {
        case 0: {
            int n = *lbl_804306E8.cnt1;
            int i = dictFind(lbl_804CC004->list[pg->cur], lbl_804306E8.t1, n);
            if (i != n) {
                *(s16*)(save + 0x18EA) = i;
            }
            break;
        }
        case 1: {
            int n = *lbl_804306E8.cnt4;
            int i = dictFind4(lbl_804CC004->list[pg->cur], lbl_804306E8.t4, n);
            if (i != n) {
                *(s16*)(save + 0x18EC) = i;
            }
            break;
        }
        }
    }
}
#pragma pop

void fn_80264034(int cur) {
    DictState* st = lbl_804CC004;
    st->mode = 1;
    lbl_804CC004->page = 0;
    st->cur = cur;
    int n = lbl_804CC004->listCount;
    f32 f;
    f32 top;
    int lim = n - 8;
    if (cur > lim) {
        top = lim;
    } else {
        top = cur;
    }
    if (top < 0.0f) {
        top = 0.0f;
    }
    f = st->f38;
    DictState* s0 = lbl_804CC004;
    DictState* pg = DICT_PAGE(s0, s0->page);
    lim = n - 9;
    if (top > lim) {
        top = lim;
    }
    if (top < 0.0f) {
        top = 0.0f;
    }
    pg->f3C = f;
    pg->f40 = top;
    pg->m48 = 1;
    pg->m44 = 1;
    fn_80264204(0, cur, 1);
    int z = 0;
    DictState* pg2;
    DictState* s1 = lbl_804CC004;
    s1->x1E = 0x46;
    s1->y20 = 0x42;
    s1->x22 = 0x46;
    s1->y24 = 0x42;
    s1->t26 = z;
    s1->page = z;
    DictState* s2 = lbl_804CC004;
    pg2 = DICT_PAGE(s2, s2->page);
    if (s2->m74 != 0) {
        fn_800C4240(s2->m74);
        lbl_804CC004->m74 = (void*)z;
    }
    DictState* s3 = lbl_804CC004;
    if (s3->page == 0 && s3->mode == 1) {
        void** e = (void**)fn_80076F54(*(const char**)s3->list[pg2->cur]);
        if (e != 0) {
            fn_800C3FD0(e[4]);
            lbl_804CC004->m74 = fn_800C6118(e[4], 0, 0, 0x640E, lbl_804CC000);
        }
    }
}

}
