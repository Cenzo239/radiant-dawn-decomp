/* Bonus experience tally (names guessed): a list of up to eight named awards
   gathered at the end of a chapter.
   Level: sched. Same instructions; in the block after the first call the
   original stores `base` right after `li r0,0` and finishes the handler
   address (`addi r4,r4,fn_8008D91C@l`) one slot later, ours the other way
   round. No dependency between the moved lines; symcheck --anon: 18 blocks,
   0 differ. */
#include "game/rJ_800799AC/types.h"

extern "C" {
int fn_80062780(void* save);
void fn_8009EAB8(int cmd, void* handler);
const char* fn_800D0864(const char* id);
char* strcpy(char*, const char*);
void fn_8006198C(void* save, f32 v);
int fn_8008D91C(void*);
extern char lbl_803631E0[];
}

struct Save {
    u8 pad[0xba];
    s16 xba;
    int xbc;
};
extern "C" Save lbl_803CAB38;

struct Tally {
    char names[8][0x20]; /* 0x000 */
    int vals[8];         /* 0x100 */
    int seen;            /* 0x120 */
    int n;               /* 0x124 */
    int base;            /* 0x128 */

    void add(const char* name, int v) {
        strcpy(names[n], name);
        vals[n] = v;
        n++;
        seen++;
    }
    int sum() {
        int s = 0;
        int i;
        for (i = 0; i < n; i++) {
            s += vals[i];
        }
        return s;
    }
};
extern "C" Tally lbl_803E4EF8;
extern "C" Tally* lbl_804CB608;

extern "C" {
void fn_8008D75C(void) {
    int total;
    Tally* t = &lbl_803E4EF8;
    t->base = fn_80062780(&lbl_803CAB38);
    t->n = 0;
    t->seen = 0;
    lbl_804CB608 = t;
    fn_8009EAB8(0xc, fn_8008D91C);
    if (lbl_803CAB38.xba != 0) {
        strcpy(t->names[t->n], fn_800D0864(lbl_803631E0));
        t->vals[t->n] = lbl_803CAB38.xba;
        t->n++;
        t->seen++;
    }
    total = t->sum();
    lbl_803CAB38.xbc = total;
    fn_8006198C(&lbl_803CAB38, total);
}
}
