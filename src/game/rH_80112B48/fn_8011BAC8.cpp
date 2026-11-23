/* Skill list save and load, 8011BAC8, 8011BC50. */
#include "game/rH_80112B48/types.h"
#pragma auto_inline off

extern "C" {
struct Sl {
    u8* item;
    u8 uses;
    u8 flags;
    void clear();
};
typedef void (Sl::*SlMF)();
struct SlFn {
    SlMF f;
    SlFn() {}
    SlFn(SlMF x) : f(x) {}
};
extern SlMF lbl_80385CD4;
extern void fn_8008A5AC(void*, u8);
extern void fn_8008A5C0(void*, u16);
extern u8 fn_8008A1A0(void*);
extern void fn_8011A298(Sl*, void*);
extern void fn_8011A36C(Sl*);

static inline SlFn SlEach(Sl* a, Sl* e, SlFn f) {
    while (a != e) {
        (a->*f.f)();
        a++;
    }
    return f;
}

static inline u8 SlCount(Sl* p) {
    Sl* q = p;
    u8 n = 0;
    int i;
    for (i = 0; i < 18; i++) {
        if (q && q->item) {
            n++;
        }
        q++;
    }
    return n;
}

static inline void SlSave(Sl* p, void* s) {
    if (p->item == 0) {
        fn_8008A5C0(s, (int)0xffff);
        fn_8008A5C0(s, 0);
    } else {
        fn_8008A5C0(s, p->item[0x1c]);
        fn_8008A5AC(s, p->uses);
        fn_8008A5AC(s, p->flags);
    }
}

void fn_8011BAC8(Sl* list, void* s) {
    int i;
    fn_8008A5AC(s, SlCount(list));
    for (i = 0; i < 18; i++) {
        if (list && list->item) {
            SlSave(list, s);
        }
        list++;
    }
}

void fn_8011BC50(Sl* list, void* s) {
    {
        SlFn g(lbl_80385CD4);
        SlEach(list, list + 18, g);
    }
    {
        int i;
        u32 n = fn_8008A1A0(s);
        for (i = 0; (u8)i < n; i++) {
            fn_8011A298(&list[(u8)i], s);
        }
    }
    fn_8011A36C(list);
}
}
