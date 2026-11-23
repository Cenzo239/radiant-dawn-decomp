/* fn_801116F4 (item sale value): exact (round m25a). From equiv/fn_801116F4.cpp: the price term is a `static inline int price(ItemE*, FSlot*)`
 * returning p * s->uses; that gives the price the lower volatile register (r4) and the cached flag word r5. */
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
int fn_80111230(int v);

Flags2* fn_801116B8(FSlot* s);

bool fn_80111F5C(FSlot* s);

static inline int Calc(FSlot* s, s8 w) {
    return (f32)(w * w) * (0.1f * (f32)BaseVal(s));
}
int fn_801120C0(FSlot* s, s8 v);

int fn_8011215C(FSlot* s, s8 v);

int fn_80112214(FSlot* s, s8 v);

int fn_801122C8(FSlot* s, s8 v);


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
ItemHook* fn_80111850(ItemE* x);

int fn_801118C0(void* a, ItemE* x);

int fn_8011196C(void* a, ItemE* x, void* b);

int fn_80111A0C(void* a, ItemE* x, void* b);

int fn_80111A98(void* a, ItemE* x, void* b);

FSlot* fn_80111B64(FSlot* d, const FSlot* s);

FSlot* fn_80111C78(FSlot* d, FSlot* s);

void fn_80111D68(FSlot* s, void* w);

struct Reader { u8 pad[4]; int pos; };
extern void* lbl_804CBFC8;
void* fn_80244690(void* a, int id);
void* fn_8010B204(int id);
u16 fn_8008A1B4(Reader* r);
u8 fn_8008A1A0(Reader* r);
void fn_8008A3D8(Reader* r, char* s, int n);
void fn_80111E48(FSlot* s, Reader* r);

int fn_80110BB4(FSlot* s, ItemE* it);
int fn_80110C60(FSlot* s);

}

/* ---- from build/tmp/r19hpbs/frag_f16f4.cpp ---- */
extern "C" {
static inline u64* FlagsOf(ItemE* it) { if (it) return (u64*)&it->fh; return (u64*)&lbl_804CB7F0; }
static inline int price(ItemE* it, FSlot* s) {
    u16 p = 0;
    if (it) p = it->price;
    return p * s->uses;
}
int fn_801116F4(FSlot* s) {
    ItemE* it;
    int v;
    u64* f;
    if (s->item == 0) return 0;
    v = 0;
    FlagGuard();
    it = s->item;
    if (it) f = (u64*)&it->fh;
    else f = (u64*)&lbl_804CB7F0;
    if (*f & 0xFFE00000ULL) v += 50000;
    if (s->f10) v += 50000;
    v += price(it, s);
    if (*f & 0x10) v += 10000;
    if (*f & 0x40) v += 10000;
    if (*f & 0x80) v += 10000;
    if (*f & 0x20) v += 10000;
    if (*f & 0x100) v += 2000;
    if (*f & 0x400) v += 2000;
    if (*f & 0x200) v += 2000;
    if (*f & 0x1000) v += 2000;
    if (*f & 0x2000) v += 1000;
    if (*f & 0x10000) v += 1000;
    if (it == fn_8010B228(lbl_803680E8 + 0x64E)) v += 20000;
    return v;
}
}
