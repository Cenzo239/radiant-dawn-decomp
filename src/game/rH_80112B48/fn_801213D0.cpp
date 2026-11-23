/* Unit save and load, map-range scan, 801213D0..80121A28. */
#include "game/rH_80112B48/unit.h"
#include "game/rH_80112B48/map.h"
#pragma auto_inline off

extern "C" {

extern Map lbl_803EC898;
struct Side { u8 v[0xc]; };
extern Side* lbl_804CB814;
extern void* lbl_804CBFC8;
extern char lbl_80369010[];

extern void fn_8008A5AC(void*, u8);
extern void fn_8008A5C0(void*, u16);
extern void fn_8008A780(void*, u32, void*);
extern u8 fn_8008A1A0(void*);
extern u16 fn_8008A1B4(void*);
extern void fn_8008A43C(void*, u8, void*);
#if TARGET_PC
extern FE10_PROTO void fn_801093EC(ptr32<const void>, ptr32<const void>);
extern FE10_PROTO void fn_801093FC(ptr32<const void>, ptr32<const void>);
#else
extern void fn_801093EC(void*, void*);
extern void fn_801093FC(void*, void*);
#endif
extern void fn_8011BAC8(void*, void*);
extern void fn_8011BC50(void*, void*);
extern void fn_80111D68(Inv*, void*);
extern void fn_80111E48(Inv*, void*);
#if TARGET_PC
extern FE10_PROTO void fn_80111210(ptr32<const void>, ptr32<const void>);
extern FE10_PROTO void fn_80111220(ptr32<const void>, ptr32<const void>);
extern FE10_PROTO void fn_80106CA8(void*, ptr32<const void>);
extern FE10_PROTO void fn_80106D3C(void*, ptr32<const void>);
#else
extern void fn_80111210(void*, void*);
extern void fn_80111220(void*, void*);
extern void fn_80106CA8(void*, void*);
extern void fn_80106D3C(void*, void*);
#endif
extern u8 fn_8012E830(Unit*);
extern Person* fn_8012E390(Unit*);
extern void fn_8012E388(Unit*, void*);
extern void fn_80129650(Unit*, void*);
extern void fn_8012978C(Unit*, void*);
extern void fn_800FB2B8(Unit*, void*);
extern void fn_800FB304(Unit*, void*);
extern void fn_8024BCA0(Unit*);
extern void* fn_80244470(void*, u16);
extern void* fn_80244580(void*, u16);
extern void* fn_8010B1D8(void*);
extern void* fn_8010B200(void*);
extern void* fn_8010B1B4(u16);
extern void* fn_8010B1DC(u16);
extern void fn_801223E0(Unit*, void*);
extern void fn_80122460(Unit*);
extern void fn_80114888(Map*, int);
extern void fn_80114B44(Map*, int, int);
extern void fn_801151BC(Map*, Unit*);
extern s16 fn_80115CD8(Map*, int, int);
#if TARGET_PC
extern FE10_PROTO void fn_8011567C(Map*, p32arg);
#else
extern void fn_8011567C(Map*, int);
#endif
extern void fn_8011540C(Map*, void*);
extern void fn_80115764(Map*, int, int, int);
extern int fn_801658E4(Unit*, int, int);

struct VSave {
    virtual void save(void*);
    virtual void load(void*);
};
#define VS(u, off) ((VSave*)((u8*)(u) + (off)))
#define U16(u, off) (*(u16*)((u8*)(u) + (off)))
#define U8(u, off) (*(u8*)((u8*)(u) + (off)))

#define ABS(a) ((a) < 0 ? -(a) : (a))

#pragma push
#pragma use_lmw_stmw on
void fn_801213D0(Unit* u, int r) {
    s8 ux = u->x;
    s8 uy = u->y;
    int y;

    fn_80114888(&lbl_803EC898, 6);
    fn_80114B44(&lbl_803EC898, 6, -1);
    fn_801151BC(&lbl_803EC898, u);
    for (y = lbl_803EC898.y0; y <= lbl_803EC898.y1 - 1; y++) {
        int x;
        for (x = lbl_803EC898.x0; x <= lbl_803EC898.x1 - 1; x++) {
            if (ABS(ux - x) + ABS(uy - y) <= r) {
                Map* q = (Map*)((u8*)&lbl_803EC898 + (s8)y * 0x40 + (s8)x);
                if (q->ter[0][0] == 0 && *(s8*)q->g5 == 0 && q->ter[2][0] != 0) {
                    if (fn_80115CD8(&lbl_803EC898, (s8)x, (s8)y) <= 30000) {
                        lbl_803EC898.cur[(s8)x + (s8)y * 0x40] = 0;
                    }
                }
            }
        }
    }
}

#pragma pop

#define Uid(p) ((p) ? (p)->fc : 0)

void fn_80121700(Unit* u, void* s) {
    Person* p = u->person;
    if (p == 0) {
        fn_8008A5C0(s, 0);
    } else {
        fn_8008A5C0(s, p->id);
        fn_8008A5C0(s, U16(u->job, 0xec));
        fn_8008A5AC(s, u->team[8]);
        fn_8008A5AC(s, u->prev ? U8(u->prev, 0xfc) : 0);
        fn_8008A5AC(s, u->next ? U8(u->next, 0xfc) : 0);
        fn_8008A5AC(s, u->actor ? U8(u->actor, 0xfc) : 0);
        fn_8008A5AC(s, u->fd);
        fn_8008A5AC(s, u->gauge);
        fn_8008A5AC(s, u->ff);
        fn_8008A5AC(s, u->u100);
        fn_8008A5AC(s, u->pad101);
        fn_8008A5AC(s, u->x);
        fn_8008A5AC(s, u->y);
        fn_8008A780(s, 8, &u->flags);
        fn_801093EC(u->skills110, s);
        fn_8008A5AC(s, u->hp);
        fn_8008A5AC(s, u->exp115);
        fn_8008A5AC(s, u->u116);
        fn_8008A780(s, 8, u->stat);
        fn_8008A780(s, 8, u->pad121);
        fn_8011BAC8(u->skills, s);
        {
            Inv* it = u->inv;
            int i;
            for (i = 0; i < 7; i++) {
                fn_80111D68(it, s);
                it++;
            }
        }
        fn_80111210(u->s2D4, s);
        fn_80106CA8((u8*)u + 0x382, s);
        if (fn_8012E830(u)) {
            VS(u, 0x2ec)->save(s);
            fn_8008A5C0(s, fn_8012E390(u) ? fn_8012E390(u)->id : 0);
            {
                int c = fn_8012E830(u);
                fn_8008A5AC(s, c);
            }
            fn_8008A780(s, fn_8012E830(u), u->sup);
            VS(u, 0x348)->save(s);
            VS(u, 0x358)->save(s);
            VS(u, 0x368)->save(s);
        }
        fn_8008A5AC(s, U8(u, 0x378));
        fn_8008A5AC(s, U8(u, 0x379));
        fn_8008A5C0(s, U16(u, 0x37a));
        fn_8008A5C0(s, U16(u, 0x37c));
        fn_80129650(u, s);
        fn_800FB2B8(u, s);
        fn_8008A5AC(s, u->u117);
        fn_8008A5AC(s, u->u118);
        fn_8008A5C0(s, u->h37E);
        fn_8008A5AC(s, u->b380);
    }
}

static inline Unit* UnitRead(void* s) {
    return UnitGet(fn_8008A1A0(s));
}

#pragma push
#pragma use_lmw_stmw on
BOOL fn_80121A28(Unit* u, void* s) {
    u16 id;
    void* g;
    fn_8024BCA0(u);
    id = fn_8008A1B4(s);
    if (id == 0) {
        return 0;
    }
    g = lbl_804CBFC8;
    {
        void* a;
        void* b;
        if (g) {
            a = fn_8010B1D8(fn_80244470(g, id));
            b = fn_8010B200(fn_80244580(g, fn_8008A1B4(s)));
        } else {
            a = fn_8010B1B4(id);
            b = fn_8010B1DC(fn_8008A1B4(s));
        }
        u->person = (Person*)a;
        u->job = (Job*)b;
    }
    {
        u8 c = fn_8008A1A0(s);
        fn_801223E0(u, &lbl_804CB814[c]);
    }
    u->prev = UnitRead(s);
    u->next = UnitRead(s);
    u->actor = (u8*)UnitRead(s);
    u->fd = fn_8008A1A0(s);
    u->gauge = fn_8008A1A0(s);
    u->ff = fn_8008A1A0(s);
    u->u100 = fn_8008A1A0(s);
    u->pad101 = fn_8008A1A0(s);
    u->x = fn_8008A1A0(s);
    u->y = fn_8008A1A0(s);
    fn_8008A43C(s, 8, &u->flags);
    fn_801093FC(u->skills110, s);
    u->hp = fn_8008A1A0(s);
    u->exp115 = fn_8008A1A0(s);
    u->u116 = fn_8008A1A0(s);
    fn_8008A43C(s, 8, u->stat);
    fn_8008A43C(s, 8, u->pad121);
    fn_8011BC50(u->skills, s);
    {
        Inv* it = u->inv;
        int i;
        for (i = 0; i < 7; i++) {
            fn_80111E48(it, s);
            it++;
        }
    }
    fn_80111220(u->s2D4, s);
    fn_80106D3C((u8*)u + 0x382, s);
    if (fn_8012E830(u)) {
        int k;
        VS(u, 0x2ec)->load(s);
        k = fn_8008A1B4(s);
        if (g) {
            fn_8012E388(u, k ? fn_8010B1D8(fn_80244470(g, k)) : 0);
        } else {
            fn_8012E388(u, k ? fn_8010B1B4(k) : 0);
        }
        fn_8008A43C(s, fn_8008A1A0(s), u->sup);
        VS(u, 0x348)->load(s);
        VS(u, 0x358)->load(s);
        VS(u, 0x368)->load(s);
    }
    U8(u, 0x378) = fn_8008A1A0(s);
    U8(u, 0x379) = fn_8008A1A0(s);
    U16(u, 0x37a) = fn_8008A1B4(s);
    U16(u, 0x37c) = fn_8008A1B4(s);
    fn_8012978C(u, s);
    fn_800FB304(u, s);
    u->u117 = fn_8008A1A0(s);
    u->u118 = fn_8008A1A0(s);
    u->h37E = fn_8008A1B4(s);
    u->b380 = fn_8008A1A0(s);
    fn_80122460(u);
    return 1;
}
#pragma pop

}
