#ifndef RC_8004BE18_DECLS_H
#define RC_8004BE18_DECLS_H

#include "game/rC_8004BE18/types.h"
#include "game/rC_8004BE18/labels.h"



extern Unit* lbl_804CB3D8;
extern void* lbl_804CB3E0;
extern ItemRef lbl_804CB3E8;
extern ItemSlot lbl_803CAAE0;
extern u8 lbl_803CAB20[];
extern u8 lbl_803CAB08[];
extern struct FlagTable lbl_803CAB38;

extern "C" void fn_80107C80(ItemSlot* slot, int arg, s16 x, s16 y);
extern "C" int fn_80060754(struct FlagTable* p);
extern "C" void fn_8013F204(void);
extern "C" void fn_8013F1C4(void);


static inline ItemSlot* getSlot(int idx) {
    if (idx == 7) {
        return &lbl_803CAAE0;
    }
    return &lbl_804CB3D8->items[idx];
}

extern "C" int fn_80111F5C(ItemSlot* s);
extern "C" u8 fn_8011F024(Unit* u, ItemSlot* s);
extern "C" int fn_8011F0E0(Unit* u, ItemSlot* s);
extern "C" MenuProc* fn_80081194(void* p, MenuProc* proc);
extern "C" MenuProc* fn_800D569C(void* p);
extern "C" void fn_800D56E8(MenuProc* p);
extern "C" void fn_80083B78(MenuProc* p);
extern "C" void fn_8012A80C(Unit* u, s8 idx);
extern "C" int fn_8012BCB0(Unit* u);
extern "C" void fn_8012CAD8(Unit* u);
extern "C" int fn_8012B35C(Unit* u, ItemData* d);
extern f32 lbl_804CCEA4;
extern u8 lbl_8037B348[];
extern u8 lbl_804CB3B0[8];
extern u8 lbl_803CAA68[];
extern u8 lbl_8037D8A0[];


typedef struct ProcXY {
    u8 pad0[0x30];
    s16 x;
    s16 y;
} ProcXY;

typedef struct Word { int i0; u8 pad[0x1204]; } Word;
extern Word lbl_803E7320;
typedef struct MapThing {
    s8 b0;
    s8 b1;
    u8 b2;
    u8 b3;
    u8 b4;
    u8 b5;
} MapThing;
extern u8 lbl_803CB770[];
extern u8 lbl_803EC898[];
extern u8 lbl_8037D950[];
extern "C" void fn_800399B0(Unit* u, s8 idx);
extern "C" void fn_8012A088(Unit* u, int idx);
extern "C" u8 fn_80127520(Unit* u);
extern "C" int fn_8012C998(Unit* u, ItemData* d);
extern "C" int fn_8012C8BC(Unit* u, ItemData* d);
extern "C" int fn_8012BC2C(Unit* u, ItemData* d);
extern "C" int fn_8012C7BC(Unit* u, ItemData* d);
extern "C" void fn_8006A144(void);
extern "C" MapThing* fn_80066130(void* p, s8 x, s8 y, int n);
extern "C" ItemSlot* fn_80066D18(MapThing* m);
extern "C" ItemData* fn_8010B204(u8 id);
extern "C" u8 fn_801107C0(ItemData* x, Unit* u);
extern "C" u8 fn_801107A0(ItemData* x, Unit* u);
extern "C" void fn_80115DEC(void* p, s8 x, s8 y, u8 a, u8 b);
extern "C" void fn_80117E30(void* p, s8 x, s8 y, u8 a);

static inline u32 dataFlag4(ItemSlot* s) { return fn_801116B8(s)->flags4 & 4; }

static inline u8 getItemType(ItemData* d) {
    return d ? d->type : 0x13;
}

static inline void refreshProc(MenuProc* p) {
    u8 t = p->a6;
    fn_800D56E8(p);
    p->a6 = t;
}

extern "C" void fn_80114B44(void* p, int a, int b);
extern "C" void fn_80114888(void* p, int a);
extern "C" int fn_8012BA20(Unit* u, ItemData* d);
extern "C" void fn_80039C40(Unit* u, ItemData* d);
extern "C" void fn_80039AE4(Unit* u, ItemData* d);
extern "C" void fn_80051FF4(void* b);
typedef struct Bytes4 { u8 b[4]; } Bytes4;
typedef struct Bytes8 { u8 b[8]; } Bytes8;
extern "C" Bytes4* fn_800CD204(int id);
extern "C" void fn_80080508(Bytes4* p);
typedef struct FlagTable {
    u8 pad0[0x10];
    u8 b10;             /* 0x10 */
    u8 pad11[0x144 - 0x11];
    char* names[0x80];  /* 0x144 */
    u32 hashes[0x80];   /* 0x344 */
    u8 bits[0x10];      /* 0x544 */
    u8 pad554[0x988 - 0x554];
} FlagTable;
typedef struct Word0 { u32 w0; } Word0;
extern "C" Word0* fn_80060728(FlagTable* t);
extern "C" int fn_80060780(FlagTable* t);
extern "C" int fn_8011B77C(void* p, void* q);
extern "C" int fn_8010E2F4(void* p);
extern "C" u32 fn_80076D18(const char* s);
extern "C" int fn_80291188(const char* a, const char* b);
extern "C" int fn_8011EF78(Unit* u);
extern "C" void fn_800677E0(Unit* u);
extern "C" void fn_8006746C(Unit* u);
extern void* lbl_804CA4D8;
extern void* lbl_804CB814;

static inline u8 itemStatA(ItemData* d, Unit* u) {
    return d ? fn_801107A0(d, u) : 0;
}
static inline u8 itemStatB(ItemData* d, Unit* u) {
    return d ? fn_801107C0(d, u) : 0;
}

static inline int flagFind(FlagTable* t, const char* name) {
    u32 h = fn_80076D18(name);
    int i;
    for (i = 0; i < 0x80; i++) {
        if (h == t->hashes[i] && fn_80291188(t->names[i], name) == 0) {
            return i;
        }
    }
    return -1;
}
static inline bool flagTestBit(FlagTable* t, int i) {
    if (i < 0 || i >= 0x80) {
        return false;
    }
    return t->bits[i >> 3] & (1 << (i & 7));
}
static inline bool flagGetBit(FlagTable* t, int i) {
    if (i < 0 || i >= 0x80) {
        return false;
    }
    return flagTestBit(t, i);
}
static inline bool flagGet(FlagTable* t, const char* name) {
    if (name[0] == 0) {
        return false;
    }
    return flagGetBit(t, flagFind(t, name));
}
static inline bool flagExists(FlagTable* t, const char* name) {
    if (flagFind(t, name) >= 0 && flagGet(t, name)) {
        return true;
    }
    return false;
}

extern void* lbl_804CA4EC;
extern void* lbl_804CA4F0;
extern void* lbl_804CA4F4;
extern void* lbl_804CA510;
extern void* lbl_804CA5BC;
extern void* lbl_804CA5C0;
extern void* lbl_804CA5E0;
extern void* lbl_804CA62C;
extern void* lbl_804CA630;
extern void* lbl_804CA650;
extern void* lbl_804CA654;
extern void* lbl_804CA658;
extern void* lbl_804CA678;
extern void* lbl_804CA69C;
extern void* lbl_804CA6D8;
extern void* lbl_804CA6F0;
extern void* lbl_804CA6F4;
extern void* lbl_804CA6F8;
extern void* lbl_804CB5B8;
extern "C" s8 fn_801284C4(Unit* u);
extern "C" void fn_8003B514(Unit* u);
static inline int unitHas(void* key) { return fn_8011B77C(lbl_803CA870.unit->x12c, key); }

extern "C" ItemData* fn_8010B228(const char* name);
extern "C" void fn_8003A3BC(Unit* u, ItemData* d);
extern "C" void fn_8003A664(Unit* u, ItemData* d);
extern "C" void fn_8003A368(Unit* u);
extern "C" int fn_8023FC50(void);
extern "C" void fn_8003A250(Unit* u);
extern "C" void fn_8003A1FC(Unit* u);
extern "C" void fn_8003A0C4(Unit* u);
extern "C" void fn_8003A03C(Unit* u);
extern "C" void fn_80039FB4(Unit* u);
extern "C" void fn_80039F2C(Unit* u, int n);

extern u8 lbl_803CAA98[];
extern u8 lbl_803CAA8C[];
extern u8 lbl_803CAA80[];
extern u8 lbl_803CAA74[];
class ProcBase {
public:
    VPAD(0)
    virtual void* v0c();                     /* 0x0C */
};
extern "C" void fn_800310E4(void* p, int a, int b, int c);
#if TARGET_PC
extern "C" FE10_PROTO void fn_8023FC40(ptr32<const void>);
#else
extern "C" void fn_8023FC40(void* p);
#endif
extern "C" int fn_8012BB48(Unit* u, ItemData* d);
extern "C" int fn_801118C0(Unit* u, ItemData* d);

extern "C" void fn_80039D6C(Unit* u, MapThing* m);

extern "C" void fn_8003B574(Unit* u);
extern "C" u8 fn_800CFB4C(Word* w);

static inline ItemSlot* cmdItem(int i) { return &lbl_803CA870.unit->items[i]; }

static inline bool tryUseItems(void) {
    int i;
    for (i = 0; i < 7; i++) {
        ItemSlot* s = cmdItem(i);
        if (s == 0 || s->data == 0) {
            break;
        }
        if ((fn_801116B8(s)->flags4 & 1) && (fn_801116B8(s)->flags4 & 0x10) == 0 &&
            fn_8012BA20(lbl_803CA870.unit, s->data)) {
            fn_80039AE4(lbl_803CA870.unit, s->data);
            if (lbl_803E7320.i0) {
                return true;
            }
        }
    }
    return false;
}

extern "C" void fn_8003A30C(Unit* u);
extern "C" void fn_8003A2A4(Unit* u);
#if TARGET_PC
extern "C" FE10_PROTO int fn_8011EF14(Unit* u, p32arg);
#else
extern "C" int fn_8011EF14(Unit* u, int n);
#endif
extern "C" void fn_8003AEEC(Unit* u);
extern "C" void fn_8003ADE0(Unit* u);
extern "C" Pos8* fn_800CFD18(Word* w, int n);

struct Mask {
    u8 v;
    Mask() {}
    Mask(const Mask& o) { v = o.v; }
    bool test(const Mask& o) const { return v & o.v; }
};
class MaskObj {
public:
    VPAD(0) VPAD(1) VPAD(2) VPAD(3) VPAD(4) VPAD(5) VPAD(6) VPAD(7)
    VPAD(8) VPAD(9) VPAD(10) VPAD(11) VPAD(12) VPAD(13) VPAD(14) VPAD(15)
    VPAD(16) VPAD(17) VPAD(18) VPAD(19) VPAD(20) VPAD(21)
    virtual Mask v60();                      /* 0x60 */
};
extern "C" Mask fn_8012C5D8(Unit* u);
extern "C" void fn_8003AA60(Unit* u, const Mask& m);
extern f32 lbl_804CCEA0;

extern "C" int fn_800A05B0(int n, s8 x, s8 y);
extern "C" int fn_800A0ED4(int n, s8 x, s8 y);
#if TARGET_PC
extern "C" FE10_PROTO struct Slot * fn_8011B560(void* p, void* q);
#else
extern "C" int fn_8011B560(void* p, void* q);
#endif

extern "C" void fn_801151BC(void* p, Unit* u);
#if TARGET_PC
extern "C" FE10_PROTO void fn_8011567C(void* p, p32arg);
#else
extern "C" void fn_8011567C(void* p, int n);
#endif
extern "C" void fn_80115764(void* p, s8 x, s8 y, int n);
extern "C" void fn_800620A8(FlagTable* t, f32 x, f32 y);
extern "C" CursorRef* fn_80062A9C(FlagTable* t, int n);

#endif
