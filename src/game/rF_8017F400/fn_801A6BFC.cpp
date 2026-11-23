#include "game/rF_8017F400/types.h"
#pragma auto_inline off
extern "C" {
/* fullscreen overlay: collects units into per-army groups and links the cursor list */
struct Cur { int page; int idx; int key; const void* name; int n; u8* unit; void* eff; Cur* prev; Cur* next; };
struct Page { int id; f32 x; f32 y; int n; Cur c[5]; };
typedef struct SD {
    u8 done; u8 pad1[3]; u32 flags; s8 state; u8 pad9; s16 timer; void* res;
    Page pages[4];
    u8 pad320[0x348 - 0x320];
    int order[2][2];
} SD;
typedef struct Unit {
    u8 pad0[0xEC]; void* xEC; u8 padF0[4]; u8* xF4; u8 padF8[5]; u8 xFD; u8 padFE[0xE]; u32 x10C; u8 pad110[0x3F0 - 0x110];
} Unit;
extern SD* lbl_804CB964;
extern void* lbl_804CB960;
extern Unit* lbl_804CB810;
extern char lbl_8036D22C[];
extern void memset(void*, int, u32);
extern void fn_8010E41C(u8*, int);
extern const void* fn_80127B28(Unit*);
extern int fn_800FADB8(Unit*);
extern void* fn_800E3C04(const char*, void*);

static inline Unit* UnitAt(int id) { return (u8)id ? &lbl_804CB810[(u8)id - 1] : 0; }

void fn_801A6BFC(void) {
/*P*/
    Cur* c;
    int i;
    int id;
    Unit* u;
    const void* name;
    int i2;
    u8 army;
    Page* p;
    int j;
    int y;
    int x;
    u8 key;
    Page* p2;
    int i3;
    int k;
    Cur* last;
    Page* p3;
    Cur* c3;
/*E*/
    u8 mask[0x10];
    memset(lbl_804CB964->pages, 0, sizeof(lbl_804CB964->pages));
    fn_8010E41C(mask, 3);
    for (id = 1; id <= 0xFE; id++) {
        u = UnitAt(id);
        if (u->xEC != 0 && mask[u->xF4[8]] != 0) {
            name = fn_80127B28(u);
            key = u->xFD;
            army = u->xF4[8];
            if (!(u->x10C & 0x10000D8) && fn_800FADB8(u) == 0) {
                for (i = 0; i < 4; i++) {
                    p = &lbl_804CB964->pages[i];
                    p->id = i;
                    if (army == i) {
                        c = p->c;
                        for (j = 0; j < 5; c++, j++) {
                            if (c->name == 0) {
                                p->n++;
                                c->page = p->id;
                                c->key = key;
                                c->idx = j;
                                c->name = name;
                                c->n = 0;
                                c->eff = 0;
                                c->prev = 0;
                                c->next = 0;
                            }
                            if (key == c->key) {
                                c->n++;
                                if ((u->x10C & 0x100) && c->unit == 0) {
                                    c->unit = (u8*)u;
                                    c->eff = fn_800E3C04(lbl_8036D22C + 0x7E, lbl_804CB960);
                                }
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    y = 0x58;
    x = 0x18;
    for (i2 = 0; i2 < 4; i2++) {
        p2 = &lbl_804CB964->pages[lbl_804CB964->order[0][i2]];
        if (p2->n > 0) {
            p2->x = x;
            p2->y = y;
            y += p2->n * 0x18 + 0x20;
        }
    }
    last = 0;
    for (i3 = 0; i3 < 4; i3++) {
        p3 = &lbl_804CB964->pages[lbl_804CB964->order[0][i3]];
        c3 = p3->c;
        for (k = 0; k < p3->n; c3++, k++) {
            c3->prev = last;
            if (last) last->next = c3;
            last = c3;
        }
    }
}
}
