#include "game/rE_800E5DE4/evproc.h"

void fn_800EF6F0(void* p) {
    fn_800EF25C(p);
}

void fn_800EF9B4(FadeProc* q) {
    int i;
    /* walking pointer: the original's induction variable lives in r30 */
    FadeProc* r = q;
    for (i = 0; i < 2; i++) {
        if (r->child[0]) {
            fn_80081A90(r->child[0]);
        }
        r = (FadeProc*)((u8*)r + 4);
    }
    fn_8001D424(q->font);
    q->font = NULL;
}

void fn_800EFA24(FadeProc* q) {
    s32 a;
    if (++q->timer == 8) {
        q->timer = 8;
        fn_80083B78(q);
    }
    a = fn_8001EF30(0.0f, 255.0f, 8.0f, q->timer);
    if (q->child[0]) {
        q->child[0]->alpha = a;
    }
    if (q->child[1]) {
        q->child[1]->alpha = a;
    }
}

void fn_800EFAC8(FadeProc* q) {
    s32 a;
    if (++q->timer == 0x10) {
        q->timer = 0x10;
        fn_80083B78(q);
    }
    a = fn_8001EF30(255.0f, 0.0f, 16.0f, q->timer);
    if (q->child[0]) {
        q->child[0]->alpha = a;
    }
    if (q->child[1]) {
        q->child[1]->alpha = a;
    }
}

/* Opens the HP gauge window for one or two units. */
void fn_800EFB6C(Handle* a, Handle* b, void* parent, int mode) {
    fn_800EF6F4(fn_80081050(lbl_80384EE8, parent), a, b, mode);
}

void fn_800EFBCC(void) {
    FadeProc* q = fn_80083B84(lbl_80384EE8);
    if (q) {
        fn_80083DC4(q, 0);
    }
}

BOOL fn_800EFC04(void) {
    return fn_80083B84(lbl_80384EE8) != NULL;
}

void fn_800EFC38(Handle* h) {
    FadeProc* q = fn_80083B84(lbl_80384EE8);
    if (q) {
        FadeChild* c = FadeProc_Find(q, h);
        if (c) {
            c->unk43 = 2;
            c->unk42 = 0xF;
            c->unk41 = 0;
            c->unk44 = 0;
        }
    }
}

void fn_800EFCD4(Handle* h) {
    FadeProc* q = fn_80083B84(lbl_80384EE8);
    if (q) {
        FadeChild* c = FadeProc_Find(q, h);
        if (c) {
            c->unk43 = 2;
            c->unk42 = 0xF;
            c->unk41 = 0;
            c->unk44 = 1;
        }
    }
}

void fn_800EFD74(GaugeProc* g) {
    g->h->unk6 = g->value;
    fn_800D5AF0(g->h);
}

int fn_800EFE88(GaugeProc* g, Handle* key) {
    if (g->h == key) {
        fn_80081A90(g);
    }
    return 0;
}

BOOL fn_800EFFE8(void) {
    return fn_80083B84(lbl_80384F18) != NULL;
}

void fn_800F001C(void) {
    fn_8023F1A0(lbl_80367458, 0);
}

/* Weapon-type index -> short type code string ("sw", "sp", ...). */
char* fn_800F08DC(u32 type) {
    switch (type) {
    case 1:
        return (char*)lbl_803674B4 + 0x4CB;
    case 2:
        return (char*)lbl_803674B4 + 0x4CE;
    case 3:
        return (char*)lbl_803674B4 + 0x4D1;
    case 4:
        return (char*)lbl_803674B4 + 0x4D4;
    case 5:
        return (char*)lbl_803674B4 + 0x4D7;
    case 6:
        return (char*)lbl_803674B4 + 0x4DA;
    case 7:
        return (char*)lbl_803674B4 + 0x4DD;
    case 8:
        return (char*)lbl_803674B4 + 0x4E0;
    case 0:
        return (char*)lbl_803674B4 + 0x4E3;
    }
    return NULL;
}

/* Looks a name up in the (data-file) name table; returns index or -1. */
int fn_800F0994(char* name) {
    u16 n;
    NameEntry* e;
    int i;
    u8* rd = lbl_804CB7C0;
    n = fn_80109A2C(&rd);
    fn_80109A2C(&rd);
    e = (NameEntry*)rd;
    for (i = 0; i < n; i++, e++) {
        if (fn_80291188(e->name, name) == 0) {
            return i;
        }
    }
    return -1;
}

int fn_800F0A2C(int k) {
    switch (k) {
    case 4:
        return 5;
    case 6:
        return 7;
    case 9:
        return 10;
    case 11:
        return 12;
    case 14:
        return 15;
    case 16:
        return 17;
    case 19:
        return 20;
    case 20:
        return 21;
    case 21:
        return 22;
    case 22:
        return 23;
    }
    return -1;
}

NameEntry* fn_800F0AA8(int i) {
    u8* rd = lbl_804CB7C0;
    fn_80109A2C(&rd);
    fn_80109A2C(&rd);
    return (NameEntry*)rd + i;
}

u8* fn_800F0AF4(int i) {
    return lbl_804CB7BC + i * 0x14;
}

void
#if TARGET_PC
*
#endif
fn_800F0B04(void* p) {
#if TARGET_PC
    return fn_80076F54(p);
#else
    fn_80076F54(p);
#endif
}

/* Builds model/animation file paths into the static buffer lbl_803E8F98. */
char* fn_800F0B08(CharData* c, int k) {
    if (k < 0) {
        fn_80290DDC(lbl_803E8F98, (char*)lbl_803674B4 + 0x51C, (char*)lbl_803674B4 + 0x52A, c->pid->name);
    } else {
        u8* rd = lbl_804CB7C4;
        fn_80109A2C(&rd);
        fn_80109A2C(&rd);
        fn_80290DDC(lbl_803E8F98, (char*)lbl_803674B4 + 0x52F, (char*)lbl_803674B4 + 0x52A, c->pid->name,
                    ((Entry8*)rd)[k].name);
    }
    return lbl_803E8F98;
}

char* fn_800F0BC8(CharData* c) {
    fn_80290DDC(lbl_803E8F98, (char*)lbl_803674B4 + 0x53B, (char*)lbl_803674B4 + 0x52A, c->pid->name);
    return lbl_803E8F98;
}

char* fn_800F0C18(CharData* c) {
    fn_80290DDC(lbl_803E8F98, (char*)lbl_803674B4 + 0x548, (char*)lbl_803674B4 + 0x52A, c->pid->name);
    return lbl_803E8F98;
}

char* fn_800F0C68(CharData* c) {
    fn_80290DDC(lbl_803E8F98, (char*)lbl_803674B4 + 0x558, (char*)lbl_803674B4 + 0x52A, c->pid->name, c->unkC);
    return lbl_803E8F98;
}

u8 fn_800F1490(Tbl30* t, int i, int j) {
    return (t->rows + i * 0x30)[j + 0x18];
}

int fn_800F14A8(Flags16* f) {
    return f->flags & 1;
}

void fn_800F172C(void* a, Vec* v) {
    fn_800F15AC(a, v->x, v->y, v->z);
}

EvCmd* fn_800F1820(FxSpec* s, void* parent) {
    FxSlot* e;
    int i;
    char* name;
    EvCmd* c;
    if (!s) {
        return NULL;
    }
    e = s->slot;
    for (i = 0; i < 4; i++, e++) {
        name = fn_800F173C(e->id);
        if (name) {
            c = fn_800E3810(name, parent);
            if (c) {
                fn_800E48F0(c, 0, e->arg);
            }
            return c;
        }
    }
    return NULL;
}

