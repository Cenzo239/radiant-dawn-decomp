/* Skill list sort (library quicksort over 8-byte slots), 8011BD2C, 8011C014. */
#include "game/rH_80112B48/types.h"
#pragma auto_inline off

extern "C" {

struct SkillSlot {
    u8* item;
    u8 kind;     /* 0x4 */
    u8 pad : 6;
    u8 hide : 1; /* 0x5 */
    u8 on : 1;
};

struct SlotLess {
    char c;
};

BOOL fn_8011A804(SlotLess*, SkillSlot*, SkillSlot*);
extern int lbl_804CA6FC;
extern int lbl_804CA700;
extern void fn_8011CDC0(SkillSlot*, SkillSlot*, SlotLess*);
extern void fn_8011C330(SkillSlot*, SkillSlot*, SkillSlot*, SlotLess*);
extern void fn_8011C2FC(SkillSlot*, SkillSlot*);
void fn_8011C014(SkillSlot*, SkillSlot*, SlotLess*);


static inline void Step(SkillSlot*& first, SkillSlot*& last, SkillSlot* p, SlotLess* c) {
    SkillSlot* j;
    SkillSlot* i;
    i = first;
    j = p;
    while (fn_8011A804(c, i, p)) {
        i++;
    }
    for (;;) {
        j--;
        if (i == j || fn_8011A804(c, j, p)) {
            break;
        }
    }
    if (i < j) {
        fn_8011C2FC(i, j);
        i++;
        for (;;) {
            while (fn_8011A804(c, i, p)) {
                i++;
            }
            do {
                j--;
            } while (!fn_8011A804(c, j, p));
            if (i >= j) {
                break;
            }
            fn_8011C2FC(i, j);
            i++;
        }
    }
    if (i == first) {
        fn_8011C2FC(i, p);
        j = last - 1;
        i++;
        if (!fn_8011A804(c, first, j)) {
            while (i != last && !fn_8011A804(c, first, i)) {
                i++;
            }
            if (i < j) {
                fn_8011C2FC(i, j);
            }
        }
        if (i < j) {
            for (;;) {
                while (!fn_8011A804(c, first, i)) {
                    i++;
                }
                do {
                    j--;
                } while (fn_8011A804(c, first, j));
                if (i >= j) {
                    break;
                }
                fn_8011C2FC(i, j);
                i++;
            }
        }
        first = i;
    } else if (i - first < last - i) {
        fn_8011C014(first, i, c);
        first = i;
    } else {
        fn_8011C014(i, last, c);
        last = i;
    }
}

#define QSORT(name, off)                                                \
void name(SkillSlot* first, SkillSlot* last, SlotLess* c) {             \
    for (;;) {                                                          \
        int n = last - first;                                           \
        SkillSlot* a;                                                   \
        SkillSlot* b;                                                   \
        SkillSlot* p;                                                   \
        if (n <= 1) {                                                   \
            return;                                                     \
        }                                                               \
        if (n <= 20) {                                                  \
            fn_8011CDC0(first, last, c);                                \
            return;                                                     \
        }                                                               \
        a = first + (n / 4 + off % 5);                                  \
        if (++off >= 5) {                                               \
            off = -4;                                                   \
        }                                                               \
        {                                                               \
            int z = n * 3 / 4;                                          \
            b = first + (z + off % 5);                                  \
        }                                                               \
        if (++off >= 5) {                                               \
            off = -4;                                                   \
        }                                                               \
        p = last - 1;                                                   \
        fn_8011C330(a, b, p, c);                                        \
        Step(first, last, p, c);                                        \
    }                                                                   \
}

#pragma push
#pragma use_lmw_stmw on
QSORT(fn_8011BD2C, lbl_804CA6FC)
QSORT(fn_8011C014, lbl_804CA700)
#pragma pop

}
