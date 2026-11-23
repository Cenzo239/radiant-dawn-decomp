/* Unit: weapon rules, inventory queries and the unit table, 8012BA20..8012CECC. */
#include "game/rH_80112B48/unit.h"
#pragma auto_inline off

extern "C" {

extern int fn_8011B77C(void*, void*);
extern int fn_8012ADC8(Unit*, u8*);
extern u8* fn_801116B8(Inv*);
extern void fn_80111C78(Inv*, Inv*);
extern Inv* fn_80127648(Unit*);
extern void* lbl_804CA4EC;
extern void* lbl_804CA4F8;
extern void* lbl_804CA4FC;
extern void* lbl_804CA514;
extern void* lbl_804CA518;
extern void* lbl_804CA6B0;
extern int fn_800626E0(void*);
extern u8 lbl_803CAB38[];
extern void fn_8010F4F0(u8*, u8*);
extern int fn_801118C0(Unit*, u8*);
#if TARGET_PC
extern FE10_PROTO p32ret fn_80111850(u8*);
#else
extern int fn_80111850(u8*);
#endif
extern int fn_800CD4DC(Unit*, u8*);
int fn_8012C0A8(Unit*, u32, int);
extern int fn_80111230(int);
extern int fn_80111488(int);
extern void* fn_80076F54(void*);
extern void* fn_800791B0(u32);
extern void* fn_8028BE18(void*, void*, void*, u32, u32);
extern void fn_8012E264(void* u);
extern void fn_8002E1EC(void* p, int flag);
extern void fn_8010DF10(void*, int);
extern void fn_801221E8(Unit*, int);
extern void fn_8010E168(void*, Unit*);

#define HAS(u, s) fn_8011B77C((u)->skills, s)

struct Team {
    Unit* head;
    Unit* tail;
    int n;
};

extern Team* lbl_804CB814;

extern void* lbl_804CA52C;
extern void* lbl_804CA530;
extern void* lbl_804CA534;
extern void* lbl_804CA538;
extern void* lbl_804CA53C;
extern void* lbl_804CA540;
extern void* lbl_804CA544;
extern void* lbl_804CA548;
extern void* lbl_804CA54C;
extern void* lbl_804CA550;

static inline BOOL WeapRank(Unit* u, u8* w) {
    u32 f = *(u32*)(w + 0x3c);
    if (f & 4) {
        if (HAS(u, lbl_804CA4FC)) {
            return 1;
        }
        if (HAS(u, lbl_804CA4EC)) {
            return 1;
        }
        return 0;
    }
    if (u->wt == 0) {
        return 1;
    }
    if (f & 2) {
        return 0;
    }
    return !(f & 0x10);
}

BOOL fn_8012BA20(Unit* u, u8* w) {
    if ((*(u32*)(w + 0x3c) & 1) == 0) {
        return 0;
    }
    {
        BOOL t = WeapRank(u, w);
        if (t == 0) {
            return 0;
        }
    }
    return fn_8012ADC8(u, w) != 0;
}

BOOL fn_8012BB08(Unit* u, u8* w) {
    if ((*(u32*)(w + 0x3c) & 1) == 0) {
        return 0;
    }
    return fn_8012ADC8(u, w) != 0;
}

static inline BOOL WeapRank2(Unit* u, u8* w, u32 f, u32 g) {
    if (f & 4) {
        if (HAS(u, lbl_804CA4FC)) {
            return 1;
        }
        if (HAS(u, lbl_804CA4EC)) {
            return 1;
        }
        return 0;
    }
    if (u->wt == 0) {
        return 1;
    }
    if (f & 2) {
        return 0;
    }
    return !g;
}

BOOL fn_8012BB48(Unit* u, u8* w) {
    u32 f = *(u32*)(w + 0x3c);
    u32 g = f & 0x10;
    if (g == 0) {
        return 0;
    }
    {
        BOOL t = WeapRank2(u, w, f, g);
        if (t == 0) {
            return 0;
        }
    }
    return fn_8012ADC8(u, w) != 0;
}

BOOL fn_8012BC2C(Unit* u, u8* w) {
    u32 f = *(u32*)(w + 0x3c);
    u32 g = *(u32*)(w + 0x38);
    if ((f & 0x20) == 0) {
        return 0;
    }
    return !(g & 0x10000);
}

void fn_8012BC54(Unit* u, int i, Inv* o) {
    fn_801116B8(o);
    fn_80111C78(&u->inv[i], o);
}

BOOL fn_8012BCB0(Unit* u) {
    int i;
    for (i = 0; i < 7; i++) {
        if (u->inv[i].item == 0) {
            break;
        }
    }
    return !i;
}

int fn_8012BD30(Unit* u, u8* item) {
    int i;
    for (i = 0; i < 7; i++) {
        if (u->inv[i].item == 0) {
            break;
        }
        if (u->inv[i].item == item) {
            return i;
        }
    }
    return -1;
}

int fn_8012BDFC(Unit* u) {
    int i;
    for (i = 0; i < 7; i++) {
        if (u->inv[i].item == 0) {
            break;
        }
    }
    return i;
}

u8 fn_8012BE78(Unit* u) {
    Inv* it = u->inv;
    u8 n = 0;
    int i;
    for (i = 0; i < 7; i++) {
        if (it->item == 0) {
            break;
        }
        if (*(u32*)(fn_801116B8(it) + 4) & 0x11) {
            n++;
        }
        it++;
    }
    return n;
}

u8 fn_8012BEF4(Unit* u) {
    Inv* it = u->inv;
    u8 n = 0;
    int i;
    for (i = 0; i < 7; i++) {
        if (it->item == 0) {
            break;
        }
        if (*(u32*)(fn_801116B8(it) + 4) & 0x60) {
            n++;
        }
        it++;
    }
    return n;
}

BOOL fn_8012BF70(Unit* u, u16* d) {
    if ((*d & 0x800) && HAS(u, lbl_804CA4F8)) {
        return 1;
    }
    if ((*d & 0x200) && HAS(u, lbl_804CA4FC)) {
        return 1;
    }
    {
        u32 m = *d;
        Inv* it;
        if (HAS(u, lbl_804CA6B0)) {
            return 0;
        }
        it = fn_80127648(u);
        if (it && (*(u32*)(fn_801116B8(it) + 4) & 0x100000)) {
            return 0;
        }
        if (it && (*(u32*)(fn_801116B8(it) + 4) & 0x20000)) {
            m = (u16)(m & ~2);
        }
        if (it && (*(u32*)(fn_801116B8(it) + 4) & 0x40000)) {
            m = (u16)(m & ~0x10);
        }
        return (*(u16*)((u8*)u->job + 0xee) & m) != 0;
    }
}

int fn_8012C0A8(Unit* u, u32 k, int v) {
    u8 i = k;
    if (*(s16*)((u8*)u->job + i * 2 + 0xb8) == 0) {
        switch (k) {
        case 6:
        case 7:
        case 8:
        case 12:
            break;
        case 0:
            if (!HAS(u, lbl_804CA52C)) {
                return 0;
            }
            break;
        case 1:
            if (!HAS(u, lbl_804CA530)) {
                return 0;
            }
            break;
        case 2:
            if (!HAS(u, lbl_804CA534)) {
                return 0;
            }
            break;
        case 3:
            if (!HAS(u, lbl_804CA538)) {
                return 0;
            }
            break;
        case 9:
            if (!HAS(u, lbl_804CA548)) {
                return 0;
            }
            break;
        case 10:
            if (!HAS(u, lbl_804CA54C)) {
                return 0;
            }
            break;
        case 5:
            if (!HAS(u, lbl_804CA544)) {
                return 0;
            }
            break;
        case 4:
            if (!HAS(u, lbl_804CA540)) {
                return 0;
            }
            break;
        case 11:
            if (!HAS(u, lbl_804CA550)) {
                return 0;
            }
            break;
        case 13:
            if (!HAS(u, lbl_804CA53C)) {
                return 0;
            }
            break;
        }
    }
    {
        int m = *(s16*)((u8*)u->job + i * 2 + 0xd0);
        if (v > m) {
            v = m;
        }
    }
    return v;
}

#if TARGET_PC
int fn_8012C250(Unit* u, int i) {
    return fn_8012C0A8(u, i, u->s2D4[i]);
}
#else
void fn_8012C250(Unit* u, int i) {
    fn_8012C0A8(u, i, u->s2D4[i]);
}
#endif

void fn_8012C5D8(u8* d, Unit* u) {
    *d = 0;
    if (HAS(u, lbl_804CA514)) {
        *d |= 8;
        return;
    }
    if (HAS(u, lbl_804CA518)) {
        if (fn_800626E0(lbl_803CAB38) < 0x32) {
            *d |= 0x20;
        } else {
            *d |= 0x10;
            return;
        }
    }
    {
        Inv* it = u->inv;
        int i;
        for (i = 0; i < 7; i++) {
            u8 t;
            if (it->item == 0) {
                break;
            }
            fn_8010F4F0(&t, it->item);
            *d |= t;
            it++;
        }
    }
}

int fn_8012C6C4(Unit* u, u8* k) {
    if (HAS(u, lbl_804CA514)) {
        return -2;
    }
    if (HAS(u, lbl_804CA518) && fn_800626E0(lbl_803CAB38) >= 0x32) {
        return -2;
    }
    {
        Inv* it = u->inv;
        int i;
        for (i = 0; i < 7; i++) {
            u8 t;
            if (it->item == 0) {
                break;
            }
            fn_8010F4F0(&t, it->item);
            if (t & *k) {
                return i;
            }
            it++;
        }
    }
    return -1;
}

int fn_8012C794(Unit* u, u8 k) {
    return fn_8012C6C4(u, &k);
}

static inline BOOL WeapB(Unit* u, u8* w) {
    u32 f = *(u32*)(w + 0x3c);
    u32 g = f & 0x10;
    if (g == 0) {
        return 0;
    }
    {
        BOOL t = WeapRank2(u, w, f, g);
        if (t == 0) {
            return 0;
        }
    }
    return fn_8012ADC8(u, w) != 0;
}

int fn_8012C7BC(Unit* u, u8* w) {
    {
        BOOL t = WeapB(u, w);
        if (t == 0) {
            return 0;
        }
    }
    return fn_801118C0(u, w);
}

static inline u8 ItemB4(int p) {
    Inv* i = (Inv*)p;
    if (i == 0) {
        return 0;
    }
    if (i->item == 0) {
        return 0;
    }
    return i->uses;
}

static inline u8 ItemB5(int p) {
    Inv* i = (Inv*)p;
    if (i == 0) {
        return 0;
    }
    if (i->item == 0) {
        return 0;
    }
    return ((u8*)i)[5];
}

int fn_8012C8BC(Unit* u, u8* w) {
    if (fn_800CD4DC(u, w) == 0x13) {
        if (ItemB4(fn_80111850(w)) == 0) {
            return 0;
        }
        return fn_801118C0(u, w);
    }
    if (ItemB5(fn_80111850(w)) == 0) {
        return 0;
    }
    return fn_801118C0(u, w);
}

int fn_8012C998(Unit* u, u8* w) {
    u32 f = *(u32*)(w + 0x3c);
    if (f & 0x11) {
        return fn_8012ADC8(u, w);
    }
    if (f & 0x60) {
        return fn_8012ADC8(u, w);
    }
    return 0;
}

static inline BOOL CanUseA(Inv* p) {
    if (p == 0 || p->item == 0) {
        return 0;
    }
    return (*(u64*)fn_801116B8(p) & ((u64)0x100 << 32)) != 0;
}

BOOL fn_8012CA88(Unit* u) {
    return CanUseA(fn_80127648(u));
}

void fn_8012CAD8(Unit* u) {
    if (CanUseA(fn_80127648(u))) {
        u->flags |= 0x800000;
    } else {
        u->flags &= ~(u64)0x800000;
    }
}

void fn_8012CB70(void) {
    if (lbl_804CB810 == 0) {
        lbl_804CB810 = (Unit*)fn_8028BE18(fn_800791B0(0x3E830), fn_8012E264, fn_8002E1EC, 0x3f0, 0xfe);
    }
    if (lbl_804CB814 == 0) {
        lbl_804CB814 = (Team*)fn_8028BE18(fn_800791B0(0x94), 0, 0, 0xc, 0xb);
    }
}

void fn_8012CBF0(void) {
    int i;
    int off;
    off = 0;
    for (i = 0; i < 0xb; i++) {
        fn_8010DF10((u8*)lbl_804CB814 + off, (u8)i);
        off += 0xc;
    }
    i = 0;
    off = 0;
    for (; i < 0xfe; i++) {
        fn_801221E8((Unit*)((u8*)lbl_804CB810 + off), i + 1);
        fn_8010E168((u8*)lbl_804CB814 + 0x30, (Unit*)((u8*)lbl_804CB810 + off));
        off += 0x3f0;
    }
}

static inline Unit* FindUnit(Person* p) {
    if (p == 0) {
        return 0;
    }
    {
        Team* t = lbl_804CB814;
        int i;
        for (i = 0; i < 0xb; i++) {
            Unit* u;
            for (u = t->head; u; u = u->next) {
                if (u->person && u->person == p) {
                    return u;
                }
            }
            t++;
        }
    }
    return 0;
}

Unit* fn_8012CE54(void* id) {
    return FindUnit((Person*)fn_80076F54(id));
}

Unit* fn_8012CECC(Person* p) {
    if (p == 0) {
        return 0;
    }
    {
        Team* t = lbl_804CB814;
        int i;
        for (i = 0; i < 0xb; i++) {
            Unit* u;
            for (u = t->head; u; u = u->next) {
                if (u->person && u->person == p) {
                    return u;
                }
            }
            t++;
        }
    }
    return 0;
}


}
