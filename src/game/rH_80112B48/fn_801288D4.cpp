/* Promotion, load and save of unit strings, 801288D4..8012978C. */
#include "game/rH_80112B48/unit.h"
#pragma auto_inline off

extern "C" {

extern int fn_8011B77C(void*, void*);
extern void fn_8012CAD8(Unit*);
extern void fn_8011B32C(void*, void*);
extern void fn_8011B958(void*, void*);
extern void fn_8011A36C(void*);
extern void* fn_80128AA0(Unit*);
extern void fn_80111B34(Inv*);
extern void fn_80111C24(Inv*, int);
extern void fn_80110BB4(Inv*, void*);
extern void fn_8012BC54(Unit*, int, Inv*);
extern void fn_801291BC(Unit*);
extern u8* fn_80076F54(void*);
extern u8* fn_80077064(void*);
extern void fn_8011FF20(Unit*, int);
extern void fn_8008A5AC(void*, u8);
extern void fn_8008A5C0(void*, u16);
extern void fn_8008A5E4(void*, u32);
extern u8 fn_8008A1A0(void*);
extern u16 fn_8008A1B4(void*);
extern u32 fn_8008A1DC(void*);
extern void* fn_802448AC(void*, u8);
extern void* fn_802449B8(void*, u8);
extern void* fn_80244AC4(void*, u8);
extern void* fn_80244BD0(void*, u8);
extern void* lbl_804CBFC8;
extern char lbl_803691D0[];
extern void* lbl_804CA4E8;
extern void* lbl_804CA4EC;

struct SkSlot {
    void* item;
    u8 b4;
};

void fn_801288D4(Unit* u) {
    SkSlot* p = (SkSlot*)u->skills;
    int i;
    for (i = 0; i < 18; i++) {
        if (p && p->item && p->b4 == 1) {
            fn_8011B32C(u->skills, p->item);
        }
        p++;
    }
    {
        Job* j = (Job*)u->job->promoted;
        u->job = j;
        fn_8011B958(u->skills, (u8*)j + 0x24);
    }
    fn_8011A36C(u->skills);
    if (fn_80128AA0(u)) {
        Inv t;
        fn_80111B34(&t);
        fn_80110BB4(&t, fn_80128AA0(u));
        if (&u->inv[0] && u->inv[0].item && u->inv[0].bit10) {
            t.bit10 = 1;
        }
        fn_8012BC54(u, 0, &t);
        u->inv[0].equipped = 1;
        fn_80111C24(&t, -1);
    }
    if (u->hp > u->job->max[0]) {
        u->hp = u->job->max[0];
    }
    u->flags &= ~(u64)0x2000;
    if (fn_8011B77C(u->skills, lbl_804CA4EC)) {
        u->u100 = 30;
    } else if (u->flags10C & 0x8000000) {
        u->u100 = 0;
    }
    fn_8012CAD8(u);
    if (!fn_8011B77C(u->skills, lbl_804CA4EC)) {
        u->flags &= ~(u64)0x8000000;
    }
}

struct UDef {
    u16 h0;
    u16 h2;
    u8 pad4[0x44 - 4];
    void* p44, *p48, *p4c, *p50, *p54;
    u8 pad58[0x62 - 0x58];
    u8 b62;
    u8 b63;
};

#pragma push
#pragma use_lmw_stmw on
void fn_80129214(Unit* u, UDef* d) {
    if (d->p44) {
        void* c, *b, *a;
        u8* p;
        fn_801291BC(u);
        c = d->p4c;
        b = d->p54;
        a = d->p48;
        p = fn_80076F54(d->p44);
        if (p) {
            u->ptr[0] = *(void**)(p + 0x18);
            u->cnt[0] = 0;
        }
        p = fn_80076F54(a);
        if (p) {
            u->ptr[1] = *(void**)(p + 0x18);
            u->cnt[1] = 0;
        }
        p = fn_80076F54(b);
        if (p) {
            u->ptr[2] = *(void**)(p + 0x18);
            u->cnt[2] = 0;
        }
        p = fn_80076F54(c);
        if (p) {
            u->ptr[3] = *(void**)p;
            u->cnt[3] = 0;
        }
        p = fn_80076F54(d->p50);
        if (p) {
            u->p3A4 = *(void**)p;
        }
        u->b3A8 = d->b62;
        if (d->h2 & 2) {
            u->w3B4 |= 0x2000000;
        }
        switch (u->team[8]) {
        case 0:
        case 5:
        case 7:
        case 8:
        case 9:
        case 10:
            u->w3B4 &= ~0x2000000;
            break;
        }
        if (d->h2 & 0x10) {
            u->w3B4 |= 0x10000000;
        }
        if (d->h2 & 0x20) {
            u->w3B4 |= 0x20000000;
        }
        if (d->h2 & 0x40) {
            u->w3B4 |= 0x20000;
        }
        if (d->h2 & 0x100) {
            u->w3B4 |= 0x40000;
        }
        if (d->h2 & 0x200) {
            u->w3B4 |= 0x800000;
        }
        if (d->h2 & 0x80) {
            u->flags10C |= 0x4000000;
        }
        fn_8011FF20(u, d->b63);
    }
}
#pragma pop

void fn_80129650(Unit* u, void* s) {
    u8* p;
    p = fn_80077064(u->ptr[0]);
    fn_8008A5AC(s, *(u32*)(p + 0x2c));
    p = fn_80077064(u->ptr[1]);
    fn_8008A5AC(s, *(u32*)(p + 0x2c));
    p = fn_80077064(u->ptr[2]);
    fn_8008A5AC(s, *(u32*)(p + 0x2c));
    fn_8008A5AC(s, fn_80077064(u->ptr[3])[4]);
    fn_8008A5AC(s, fn_80077064(u->p3A4)[4]);
    fn_8008A5AC(s, u->cnt[0]);
    fn_8008A5AC(s, u->cnt[1]);
    fn_8008A5AC(s, u->cnt[2]);
    fn_8008A5AC(s, u->cnt[3]);
    fn_8008A5E4(s, u->w3B4);
    fn_8008A5C0(s, u->h3B8);
    fn_8008A5AC(s, u->b3BA);
    fn_8008A5AC(s, u->b3BC);
    fn_8008A5AC(s, u->b3A8);
    fn_8008A5C0(s, *(u16*)&u->pad3BD[1]);
    fn_8008A5C0(s, 0);
}

void fn_8012978C(Unit* u, void* s) {
    void* g;
    u8* p;
    fn_801291BC(u);
    g = lbl_804CBFC8;
    if (g) {
        p = fn_80076F54(fn_802448AC(g, fn_8008A1A0(s)));
        if (p) {
            u->ptr[0] = *(void**)(p + 0x18);
            u->cnt[0] = 0;
        }
        p = fn_80076F54(fn_802449B8(g, fn_8008A1A0(s)));
        if (p) {
            u->ptr[1] = *(void**)(p + 0x18);
            u->cnt[1] = 0;
        }
        p = fn_80076F54(fn_802449B8(g, fn_8008A1A0(s)));
        if (p) {
            u->ptr[2] = *(void**)(p + 0x18);
            u->cnt[2] = 0;
        }
        p = fn_80076F54(fn_80244AC4(g, fn_8008A1A0(s)));
        if (p) {
            u->ptr[3] = *(void**)p;
            u->cnt[3] = 0;
        }
        p = fn_80076F54(fn_80244BD0(g, fn_8008A1A0(s)));
        if (p) {
            u->p3A4 = *(void**)p;
        }
    } else {
        void** t = (void**)fn_80077064(lbl_803691D0);
        p = fn_80076F54(t[fn_8008A1A0(s)]);
        if (p) {
            u->ptr[0] = *(void**)(p + 0x18);
            u->cnt[0] = 0;
        }
        t = (void**)fn_80077064(lbl_803691D0 + 0xf);
        p = fn_80076F54(t[fn_8008A1A0(s)]);
        if (p) {
            u->ptr[1] = *(void**)(p + 0x18);
            u->cnt[1] = 0;
        }
        t = (void**)fn_80077064(lbl_803691D0 + 0xf);
        p = fn_80076F54(t[fn_8008A1A0(s)]);
        if (p) {
            u->ptr[2] = *(void**)(p + 0x18);
            u->cnt[2] = 0;
        }
        t = (void**)fn_80077064(lbl_803691D0 + 0x1e);
        p = fn_80076F54(t[fn_8008A1A0(s)]);
        if (p) {
            u->ptr[3] = *(void**)p;
            u->cnt[3] = 0;
        }
        t = (void**)fn_80077064(lbl_803691D0 + 0x2e);
        p = fn_80076F54(t[fn_8008A1A0(s)]);
        if (p) {
            u->p3A4 = *(void**)p;
        }
    }
    u->cnt[0] = fn_8008A1A0(s);
    u->cnt[1] = fn_8008A1A0(s);
    u->cnt[2] = fn_8008A1A0(s);
    u->cnt[3] = fn_8008A1A0(s);
    u->w3B4 = fn_8008A1DC(s);
    u->h3B8 = fn_8008A1B4(s);
    u->b3BA = fn_8008A1A0(s);
    u->b3BC = fn_8008A1A0(s);
    u->b3A8 = fn_8008A1A0(s);
    *(u16*)&u->pad3BD[1] = fn_8008A1B4(s);
    fn_8008A1B4(s);
}

}
