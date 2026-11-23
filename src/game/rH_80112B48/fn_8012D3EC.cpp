/* Unit list rebuild: reset the side lists, init all units, then sort units back into their side lists. */
/* Unit table loops: apply something to every unit of a side, 8012CC80..8012E3A4. */
#include "game/rH_80112B48/unit.h"
#pragma auto_inline off

extern "C" {

extern int fn_8011B77C(void*, void*);
extern void fn_8010E41C(void*, int);
extern void fn_8010E27C(void*, Unit*);
extern void fn_8010E168(void*, Unit*);
extern void fn_8010DF10(void*, int);
extern void fn_8010DF24(void*);
extern void fn_8011FDD8(Unit*, int);
extern void fn_80126EB0(Unit*, int, int);
extern void* fn_80076F54(void*);
extern Unit* fn_80127B68(Unit*);
extern void fn_80121700(Unit*, void*);
extern int fn_80121A28(Unit*, void*);
extern void fn_801221E8(Unit*, int);
extern u8* fn_8024BCA0(void);
extern void fn_800F68DC(Unit*, int);
extern void fn_800F6AEC(Unit*, int);
extern void fn_800F7410(Unit*, int);
extern void fn_800F39DC(Unit*);
extern void fn_800F7A98(Unit*);
extern void fn_800F7D04(Unit*);
extern void fn_800F7BF4(Unit*);
extern void fn_800F91B8(Unit*);
extern void fn_800F93E4(Unit*);
extern void fn_800F9890(void);
extern void fn_800F98CC(void);
extern void fn_800FAD48(void);
extern void fn_800FB824(void);
#if TARGET_PC
extern FE10_PROTO void fn_800F8030(p32arg);
#else
extern void fn_800F8030(int);
#endif
extern int fn_800F69E4(Unit*);
extern int fn_800F760C(Unit*);
extern void* fn_801246A4(Unit*);
extern void fn_800C7B18(void*, int);
#if TARGET_PC
extern FE10_PROTO void fn_80102928(Unit*, int, int, int, p32arg);
#else
extern void fn_80102928(Unit*, int, int, int, int);
#endif
extern void fn_80083B78(void*);
extern void* fn_80081194(void*, void*);
extern u64 fn_8017DA30(u64);
extern u32 lbl_804CB5F4;
extern u32 lbl_804CA710;
extern void* memset(void*, int, u32);
extern void* lbl_804CA4D8;
extern char lbl_80369258[];
extern u8 lbl_80385E20[];
extern u8 lbl_80385E44[];

struct Team {
    Unit* head;
    Unit* tail;
    int n;
};

extern Team* lbl_804CB814;

void fn_8012D3EC(void* r0) {
    /*P*/
    int i3;
    u8* g;
    int o1;
    int i1;
    int o2;
    int i2;
    void* r;
    int n;
    int i4;
    int o4;
    int i5;
    int o5;
    Unit* u;
/*E*/
    r = r0;
    g = fn_8024BCA0();
    for (i1 = 0, o1 = 0; i1 < 0xb; i1++) {
        fn_8010DF10((u8*)lbl_804CB814 + o1, (u8)i1);
        o1 += 0xc;
    }
    for (i2 = 0, o2 = 0; i2 < 0xfe; i2++) {
        fn_801221E8((Unit*)((u8*)lbl_804CB810 + o2), i2 + 1);
        fn_8010E168(&lbl_804CB814[4], (Unit*)((u8*)lbl_804CB810 + o2));
        o2 += 0x3f0;
    }
    n = 0xfe;
    if (*(u32*)(g + 0xc) < 0xb) {
        n = 0x9f;
    }
    for (i3 = 0; i3 < n; i3++) {
        fn_8010E27C(&lbl_804CB814[4], &lbl_804CB810[i3]);
        if (!fn_80121A28(&lbl_804CB810[i3], r)) {
            fn_8010E168(&lbl_804CB814[4], &lbl_804CB810[i3]);
        }
    }
    for (i4 = 0, o4 = 0; i4 < 0xb; i4++, o4 += 0xc) {
        if (i4 != 4) {
            fn_8010DF24((u8*)lbl_804CB814 + o4);
        }
    }
    for (i5 = 0, o5 = 0; i5 < n; o5 += 0x3f0, i5++) {
        u = (Unit*)((u8*)lbl_804CB810 + o5);
        if (u->prev == 0 && u->next == 0) {
            fn_8010E168(&lbl_804CB814[u->team[8]], u);
        }
    }
}
}
