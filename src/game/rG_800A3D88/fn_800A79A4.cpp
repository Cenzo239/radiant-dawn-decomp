#include "game/rG_800A3D88/types.h"

// Battle data: find a table 0x10 entry by name, take one of its five slots (with fallbacks) and return that table 0x18 entry.
extern "C" {
extern u8* lbl_804CB664;
extern u8* lbl_804CB668;
int fn_80109A2C(u8**);
int fn_80291188(const char*, const char*);
struct Entry10 { const char* name; s16 slot[5]; u8 pad[2]; };
struct Entry18 { u8 p[0x18]; };
#define TBL_COUNT(n, tbl) { u8* r_ = tbl; n = (u16)fn_80109A2C(&r_); fn_80109A2C(&r_); }
#define TBL_DATA(e, T, tbl) { u8* r_ = tbl; fn_80109A2C(&r_); fn_80109A2C(&r_); e = (T*)r_; }
static inline u16 Count(u8* tbl) {
    u8* r = tbl;
    u16 n = fn_80109A2C(&r);
    fn_80109A2C(&r);
    return n;
}
static inline u8* Data(u8* tbl) {
    u8* r = tbl;
    fn_80109A2C(&r);
    fn_80109A2C(&r);
    return r;
}
static inline int Index10(const char* name) {
    if (name == NULL) {
        return -1;
    }
int i;
u16 n;
Entry10* e;

u8* rb; u8* ra; ra=lbl_804CB668; n=(u16)fn_80109A2C(&ra); fn_80109A2C(&ra); rb=lbl_804CB668; fn_80109A2C(&rb); fn_80109A2C(&rb); e=(Entry10*)rb;
    for (i = 0; i < n; i++, e++) {
        if (fn_80291188(name, e->name) == 0) {
            return i;
        }
    }
    return -1;
}
static inline Entry10* At10(const char* name) {
    int i = Index10(name);
    if (i < 0) {
        return NULL;
    }
Entry10* z; TBL_DATA(z, Entry10, lbl_804CB668); return z + i;
}
static inline int Slot(Entry10* e, int k) {
    if (k < 0 || k >= 5) return -1;
    int r = -1;
    if (e->slot[k] >= 0) r = e->slot[k];
    return r;
}
static inline Entry18* At18(int v) { return (Entry18*)Data(lbl_804CB664) + v; }
#pragma use_lmw_stmw on
Entry18* fn_800A79A4(const char* name, int k) {
    Entry10* e = At10(name);
    if (e != NULL) {
        int v = Slot(e, k);
        if (v < 0) {
            if (k == 3) v = Slot(e, 2);
            if (v < 0) v = Slot(e, 0);
        }
        if (v < 0) return NULL;
return At18(v);
    }
    return NULL;
}
}
