#include "game/rP_80105B04/rp.h"
struct ItemE {
    char* name;  /* 0 */
    char* id;    /* 4 */
    u8 pad8[6];
    u16 idx;     /* 0xE */
    u16 price;   /* 0x10 */
    u8 pad12[9];
    u8 maxUses;  /* 0x1B */
    u8 pad1C[0x38 - 0x1C];
    u32 fh;      /* 0x38 */
    u32 fl;      /* 0x3C */
};
struct Color { u8 r, g, b, a; };
struct FSlot {
    ItemE* item; /* 0 */
    u8 uses;     /* 4 */
    u8 f80 : 1;  /* 5 */
    u8 f40 : 1;
    u8 f20 : 1;
    u8 f10 : 1;
    u8 f08 : 1;
    u8 f04 : 1;
    u8 f02 : 1;
    u8 f01 : 1;
    char name[0x18]; /* 6 */
    s8 mt;   /* 0x1E */
    s8 hit;  /* 0x1F */
    s8 crt;  /* 0x20 */
    s8 wt;   /* 0x21 */
    Color col; /* 0x22 */
    u8 x26;
};
struct Flags2 { u32 h, l; };
extern "C" {
extern s8 lbl_804CB7E8;
extern u32 lbl_804CB7F0;
extern u32 lbl_804CB7F4;

struct ItemHook {
    int (*f0)(void*, void*);
    u8 pad4[4];
    void (*f8)(void*);
    int (*fC)(void*);
    int (*f10)(void*);
};
extern char lbl_803680E8[];
extern char lbl_803EC390[];
extern const void* const lbl_804CB7F8;
char* strcpy(char* a, const char* b);
char* fn_80291110(char* a, const char* b);
ItemHook* fn_80076F54(const char* s);
void* fn_8010B228(const char* s);
void fn_80110D38(FSlot* s);
void fn_8008A5E4(void* w, int v);
void fn_8008A5C0(void* w, int v);
void fn_8008A5AC(void* w, int v);
void fn_8008A71C(void* w, const char* v);

static inline Flags2* SlotFlags(FSlot* s) {
    if (!lbl_804CB7E8) {
        lbl_804CB7F4 = 0;
        lbl_804CB7F0 = 0;
        lbl_804CB7E8 = 1;
    }
    if (s->item) return (Flags2*)&s->item->fh;
    return (Flags2*)&lbl_804CB7F0;
}
static inline ItemHook* Hook(const ItemE* x) {
    ItemHook* h;
    if (lbl_804CB7F8 != x) {
        *(const void**)&lbl_804CB7F8 = x;
        strcpy(lbl_803EC390, x->name);
        fn_80291110(lbl_803EC390, lbl_803680E8 + 0x657);
    }
    h = fn_80076F54(lbl_803EC390);
    if (h == 0) return 0;
    return h;
}
static inline u32 BaseVal(FSlot* s) {
    u16 p = 0;
    if (s->item) p = s->item->price;
    return p * s->uses;
}
u32 fn_80111074(FSlot* s);
u32 fn_80111094(FSlot* s);
int fn_80111230(int v) {
    if (v >= 0x14B) return 0x14B;
    if (v >= 0xFB) return 0xFB;
    if (v >= 0xB5) return 0xB5;
    if (v >= 0x79) return 0x79;
    if (v >= 0x47) return 0x47;
    if (v >= 0x1F) return 0x1F;
    return v >= 1;
}
Flags2* fn_801116B8(FSlot* s) {
    if (!lbl_804CB7E8) {
        lbl_804CB7F4 = 0;
        lbl_804CB7F0 = 0;
        lbl_804CB7E8 = 1;
    }
    if (s->item) return (Flags2*)&s->item->fh;
    return (Flags2*)&lbl_804CB7F0;
}
bool fn_80111F5C(FSlot* s) {
    Flags2* f;
    ItemE* it;
    if (!lbl_804CB7E8) {
        lbl_804CB7F4 = 0;
        lbl_804CB7F0 = 0;
        lbl_804CB7E8 = 1;
    }
    it = s->item;
    if (it) f = (Flags2*)&it->fh;
    else f = (Flags2*)&lbl_804CB7F0;
    if (f->l & 0x864) return 0;
    if ((u32)s->uses == (u32)(it ? it->maxUses : 0)) return 0;
    return s->f10 == 0;
}
static inline int Calc(FSlot* s, s8 w) {
    return (f32)(w * w) * (0.1f * (f32)BaseVal(s));
}
int fn_801120C0(FSlot* s, s8 v) {
    if (v < 0) v = s->f20 ? s->mt : 0;
    return (f32)(v * v) * (0.1f * (f32)BaseVal(s));
}
int fn_8011215C(FSlot* s, s8 v) {
    if (v < 0) v = s->f20 ? s->hit : 0;
    return Calc(s, v / 5);
}
int fn_80112214(FSlot* s, s8 v) {
    if (v < 0) v = s->f20 ? s->crt : 0;
    return Calc(s, v / 3);
}
int fn_801122C8(FSlot* s, s8 v) {
    if (v < 0) v = s->f20 ? s->wt : 0;
    return (f32)(v * v) * (0.1f * (f32)BaseVal(s));
}

static inline void FlagGuard() {
    if (!lbl_804CB7E8) {
        lbl_804CB7F4 = 0;
        lbl_804CB7F0 = 0;
        lbl_804CB7E8 = 1;
    }
}
static inline u32 PriceOf(ItemE* it) {
    return it ? it->price : 0;
}
ItemHook* fn_80111850(ItemE* x) {
    return Hook(x);
}
int fn_801118C0(void* a, ItemE* x) {
    ItemHook* h = Hook(x);
    if (h == 0) return 0;
    return h->f0(a, x);
}
int fn_8011196C(void* a, ItemE* x, void* b) {
    ItemHook* h = Hook(x);
    if (h->f8) {
        h->f8(b);
        return 1;
    }
    return 0;
}
int fn_80111A0C(void* a, ItemE* x, void* b) {
    return Hook(x)->fC(b);
}
int fn_80111A98(void* a, ItemE* x, void* b) {
    ItemHook* h = Hook(x);
    if (h->f10) return h->f10(b);
    return 0;
}
FSlot* fn_80111B64(FSlot* d, const FSlot* s) {
    d->item = s->item;
    d->uses = s->uses;
    d->f80 = s->f80;
    d->f40 = s->f40;
    d->f10 = s->f10;
    d->f08 = s->f08;
    d->f04 = s->f04;
    d->f20 = s->f20;
    strcpy(d->name, s->name);
    d->mt = s->mt;
    d->hit = s->hit;
    d->crt = s->crt;
    d->wt = s->wt;
    d->col.r = s->col.r;
    d->col.g = s->col.g;
    d->col.b = s->col.b;
    d->col.a = s->col.a;
    d->x26 = s->x26;
    return d;
}
FSlot* fn_80111C78(FSlot* d, FSlot* s) {
    if (d != s) {
        d->item = s->item;
        d->uses = s->uses;
        d->f80 = s->f80;
        d->f40 = s->f40;
        d->f10 = s->f10;
        d->f08 = s->f08;
        d->f04 = s->f04;
        d->f20 = s->f20;
        strcpy(d->name, s->name);
        d->mt = s->mt;
        d->hit = s->hit;
        d->crt = s->crt;
        d->wt = s->wt;
        d->col.r = s->col.r;
        d->col.g = s->col.g;
        d->col.b = s->col.b;
        d->col.a = s->col.a;
        d->x26 = s->x26;
    }
    return d;
}
void fn_80111D68(FSlot* s, void* w);

struct Reader { u8 pad[4]; int pos; };
extern void* lbl_804CBFC8;
void* fn_80244690(void* a, int id);
void* fn_8010B204(int id);
u16 fn_8008A1B4(Reader* r);
u8 fn_8008A1A0(Reader* r);
void fn_8008A3D8(Reader* r, char* s, int n);

void fn_80111E48(FSlot* s, Reader* r) {
    u16 id = fn_8008A1B4(r);
    if (id == 0) {
        r->pos += 2;
        fn_80110D38(s);
        return;
    }
    if (lbl_804CBFC8) {
        s->item = (ItemE*)fn_8010B228((char*)fn_80244690(lbl_804CBFC8, id));
    } else {
        s->item = (ItemE*)fn_8010B204(id);
    }
    *(u16*)&s->uses = fn_8008A1B4(r);
    if (s->f20) {
        fn_8008A3D8(r, s->name, 0x18);
        s->mt = fn_8008A1A0(r);
        s->hit = fn_8008A1A0(r);
        s->crt = fn_8008A1A0(r);
        s->wt = fn_8008A1A0(r);
        s->col.r = fn_8008A1A0(r);
        s->col.g = fn_8008A1A0(r);
        s->col.b = fn_8008A1A0(r);
        s->col.a = fn_8008A1A0(r);
    }
    s->x26 = 0xFF;
}
int fn_80110BB4(FSlot* s, ItemE* it);
int fn_80110C60(FSlot* s) {
    if (SlotFlags(s)->h & 0x10000) return 0;
    if (s->f10) return 0;
    if (--s->uses == 0) {
        fn_80110D38(s);
        return 1;
    }
    return 0;
}
}
