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
static inline int Calc(FSlot* s, s8 w) {
    return (f32)(w * w) * (0.1f * (f32)BaseVal(s));
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
void fn_80111D68(FSlot* s, void* w);

struct Reader { u8 pad[4]; int pos; };
extern void* lbl_804CBFC8;
void* fn_80244690(void* a, int id);
void* fn_8010B204(int id);
u16 fn_8008A1B4(Reader* r);
u8 fn_8008A1A0(Reader* r);
void fn_8008A3D8(Reader* r, char* s, int n);

int fn_80110BB4(FSlot* s, ItemE* it);


static inline int P1(FSlot* s, s8 v) {
    if (v < 0) v = s->f20 ? s->mt : 0;
    return (f32)(v * v) * (0.1f * (f32)BaseVal(s));
}
static inline int P2(FSlot* s, s8 v) {
    if (v < 0) v = s->f20 ? s->hit : 0;
    return Calc(s, v / 5);
}
static inline int P3(FSlot* s, s8 v) {
    if (v < 0) v = s->f20 ? s->crt : 0;
    return Calc(s, v / 3);
}
static inline int P4(FSlot* s, s8 v) {
    if (v < 0) v = s->f20 ? s->wt : 0;
    return (f32)(v * v) * (0.1f * (f32)BaseVal(s));
}
static inline int fn_80112364x(int a, int b, int c, int d) { return a + b + c + d; }
void* fn_800D0864(const char*);
char* fn_80112B48(FSlot*);
static inline char* N0(FSlot* s) {
    ItemE* it = s->item;
    if (it == 0) return 0;
    if (s->f20 == 0) {
        if (fn_80076F54(it->id)) return (char*)fn_800D0864(it->id);
        return it->name;
    }
    return fn_80112B48(s);
}
#define LV(N, P) static inline char* N(FSlot* s) { \
    ItemE* it = s->item; \
    if (it == 0) return 0; \
    if (s->f20 == 0) { \
        if (fn_80076F54(it->id)) return (char*)fn_800D0864(it->id); \
        return it->name; \
    } \
    if (s->f20) return s->name; \
    return P(s); \
}
LV(N1, N0)
LV(N2, N1)
LV(N3, N2)
char* fn_80110F08(FSlot* s) {
    ItemE* it = s->item;
    if (it == 0) return 0;
    if (s->f20 == 0) {
        if (fn_80076F54(it->id)) return (char*)fn_800D0864(it->id);
        return it->name;
    }
    if (s->f20) return s->name;
    return N3(s);
}
void fn_801115A8(u16* o, const char* s) {
    int i;
    if (s == 0 || *s == 0) {
        o[0] = 0;
        o[1] = 0;
        o[2] = 0;
        o[3] = 0;
        o[4] = 0;
        o[5] = 0;
        o[6] = 0;
        o[7] = 0;
        o[8] = 0;
        o[9] = 0;
        o[10] = 0;
        o[11] = 0;
        return;
    }
    for (i = 0; i < 0xC; i++) {
        switch (*s) {
        case '*': *o = 0x14B; break;
        case 'S': *o = 0xFB; break;
        case 'A': *o = 0xB5; break;
        case 'B': *o = 0x79; break;
        case 'C': *o = 0x47; break;
        case 'D': *o = 0x1F; break;
        case 'E': *o = 1; break;
        case '-': *o = 0; break;
        }
        o++;
        s++;
    }
}
}
