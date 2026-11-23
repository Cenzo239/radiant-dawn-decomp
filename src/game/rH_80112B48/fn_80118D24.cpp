/* Person, job and unit initialisers with the slot constructor, 80118D24, 80118DF4, 8012E264. */
#include "game/rH_80112B48/unit.h"
#pragma auto_inline off

extern "C" {
extern void* memset(void*, int, u32);
extern void fn_80111B34(void*);
extern void fn_80111C24(void*, int);
extern void fn_8028BFD8(void*, void*, void*, u32, u32);
extern void fn_80129150(void*);
extern u8 lbl_80379438[];

#if TARGET_PC
struct Slot {
    FE10_P32(u8) item; /* host: 32-bit window offset, see fn_8011ABCC.cpp */
    u8 uses;
    u8 flags;
#else
struct Slot {
    u8* item;
    u8 uses;
    u8 flags;
#endif
    void init() {
        item = 0;
        uses = 2;
        flags = 0;
        if (item) {
            flags |= item[0x20] == 0 ? 1 : 0;
        }
    }
};

struct JobA {
    u8 pad0[0x22];
    s8 a[8];
    s8 b[8];
    u8 pad32[0x4c - 0x32];
    Slot slots[18];
    u8 padDC[0xfc - 0xdc];
};

JobA* fn_80118D24(JobA* p) {
    s8 z = 0;
    p->a[7] = z;
    p->a[6] = z;
    p->a[5] = z;
    p->a[4] = z;
    p->a[3] = z;
    p->a[2] = z;
    p->a[1] = z;
    p->a[0] = z;
    p->b[7] = z;
    p->b[6] = z;
    p->b[5] = z;
    p->b[4] = z;
    p->b[3] = z;
    p->b[2] = z;
    p->b[1] = z;
    p->b[0] = z;
    {
        Slot* s = p->slots;
        do {
            s->init();
            s++;
        } while (s < p->slots + 18);
    }
    memset(p, 0, sizeof(JobA));
    return p;
}

struct JobB {
    u8 pad0[0x24];
    Slot slots[18];
    u8 padB4[0xee - 0xb4];
    u16 hEE;
    u8 padF0[0xfc - 0xf0];
    s8 v[4][8];
};

JobB* fn_80118DF4(JobB* p) {
    {
        Slot* s = p->slots;
        do {
            s->init();
            s++;
        } while (s < p->slots + 18);
    }
    p->hEE = 0;
    {
        int i, j;
        for (i = 0; i < 4; i++) {
            for (j = 7; j >= 0; j--) {
                p->v[i][j] = 0;
            }
        }
    }
    memset(p, 0, 0x11c);
    return p;
}

Unit* fn_8012E264(Unit* u) {
    u32 z = 0;
    *(u16*)u = z;
    u->flags = z;
    u->stat[7] = z;
    u->stat[6] = z;
    u->stat[5] = z;
    u->stat[4] = z;
    u->stat[3] = z;
    u->stat[2] = z;
    u->stat[1] = z;
    u->stat[0] = z;
    u->pad121[7] = z;
    u->pad121[6] = z;
    u->pad121[5] = z;
    u->pad121[4] = z;
    u->pad121[3] = z;
    u->pad121[2] = z;
    u->pad121[1] = z;
    u->pad121[0] = z;
    {
        Slot* s = (Slot*)u->skills;
        do {
            s->init();
            s++;
        } while (s < (Slot*)u->inv);
    }
    fn_8028BFD8(u->inv, (void*)fn_80111B34, (void*)fn_80111C24, 0x28, 7);
    *(u16*)((u8*)u + 0x382) = 0;
    *(u8**)((u8*)u + 0x2ec) = lbl_80379438;
    *(u8**)((u8*)u + 0x348) = lbl_80379438;
    *(u8**)((u8*)u + 0x358) = lbl_80379438;
    *(u8**)((u8*)u + 0x368) = lbl_80379438;
    *(u16*)((u8*)u + 0x384) = 0;
    *(u16*)((u8*)u + 0x386) = 0;
    *(u16*)((u8*)u + 0x388) = 0;
    *(u16*)((u8*)u + 0x38a) = 0;
    *(u16*)((u8*)u + 0x38c) = 0;
    *((u8*)u + 0x38e) = 0;
    *((u8*)u + 0x38f) = 0;
    fn_80129150((u8*)u + 0x3c4);
    return u;
}

}
