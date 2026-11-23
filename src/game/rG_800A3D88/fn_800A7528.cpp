#include "game/rG_800A3D88/types.h"

// Data table accessors. Each table blob starts with a header that
// fn_80109A2C (stream read/skip) consumes: the first read returns the entry count.

extern "C" {

extern u8* lbl_804CB650;
extern u8* lbl_804CB658;
extern u8* lbl_804CB668;
extern u8* lbl_804CB66C;
extern u8* lbl_804CB670;
extern u8* lbl_804CB674;
extern u8* lbl_804CB678;
extern u8* lbl_804CB67C;
extern u8* lbl_804CB680;
extern u8* lbl_804CB688;

int fn_80109A2C(u8**);
int fn_80291188(const char*, const char*);

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

/* Inside an inline, the same reads only colour correctly as bare blocks. */
#define TBL_COUNT(n, tbl) { u8* r_ = tbl; n = (u16)fn_80109A2C(&r_); fn_80109A2C(&r_); }
#define TBL_DATA(e, T, tbl) { u8* r_ = tbl; fn_80109A2C(&r_); fn_80109A2C(&r_); e = (T*)r_; }

struct Entry154 {
    const char* name;
    u8 pad[0x150];
};

Entry154* fn_800A7528(const char* name) {
    if (name == NULL) {
        return NULL;
    }
    int n = Count(lbl_804CB650);
    Entry154* e = (Entry154*)Data(lbl_804CB650);
    for (int i = 0; i < n; i++, e++) {
        if (fn_80291188(e->name, name) == 0) {
            return e;
        }
    }
    return NULL;
}

u8* fn_800A7948(int i) {
    if (i < 0) {
        return NULL;
    }
    return Data(lbl_804CB658) + i * 0x18;
}

struct Entry8 {
    const char* name;
    s32 v;
};

struct Entry10 {
    const char* name;
    u8 pad[0xC];
};

static inline int Index10(const char* name) {
    if (name == NULL) {
        return -1;
    }
    int n;
    Entry10* e;
    int i;
    TBL_COUNT(n, lbl_804CB668);
    TBL_DATA(e, Entry10, lbl_804CB668);
    for (i = 0; i < n; i++, e++) {
        if (fn_80291188(name, e->name) == 0) {
            return i;
        }
    }
    return -1;
}

static inline Entry10* At10(int i) {
    if (i < 0) {
        return NULL;
    }
    return (Entry10*)Data(lbl_804CB668) + i;
}

Entry10* fn_800A7B38(const char* name) {
    return At10(Index10(name));
}

int fn_800A7C28(const char* name) {
    if (name == NULL) {
        return -1;
    }
    int n = Count(lbl_804CB66C);
    Entry8* e = (Entry8*)Data(lbl_804CB66C);
    for (int i = 0; i < n; i++, e++) {
        if (fn_80291188(name, e->name) == 0) {
            return i;
        }
    }
    return -1;
}

Entry8* fn_800A7CE8(int i) {
    if (i < 0) {
        return NULL;
    }
    return (Entry8*)Data(lbl_804CB66C) + i;
}

struct Entry14 {
    const char* name;
    const char* name2;
    u8 pad[0xC];
};

static inline int Index14(const char* name) {
    if (name == NULL) {
        return -1;
    }
    int n;
    Entry14* e;
    int i;
    TBL_COUNT(n, lbl_804CB670);
    TBL_DATA(e, Entry14, lbl_804CB670);
    for (i = 0; i < n; i++, e++) {
        if (fn_80291188(name, e->name) == 0) {
            return i;
        }
    }
    return -1;
}

static inline Entry14* At14(int i) {
    if (i < 0) {
        return NULL;
    }
    return (Entry14*)Data(lbl_804CB670) + i;
}

Entry14* fn_800A7D44(const char* name) {
    return At14(Index14(name));
}

Entry14* fn_800A7E34(const char** name) {
    if (name != NULL) {
        int n = Count(lbl_804CB670);
        Entry14* e = (Entry14*)Data(lbl_804CB670);
        for (int i = 0; i < n; i++, e++) {
            if (fn_80291188(e->name2, *name) == 0) {
                return e;
            }
        }
    }
    return NULL;
}

struct Entry24 {
    const char* name;
    const char* name2;
    u8 pad[0x1C];
};

int fn_800A7EEC(const char* name) {
    if (name == NULL) {
        return -1;
    }
    int n = Count(lbl_804CB674);
    Entry24* e = (Entry24*)Data(lbl_804CB674);
    for (int i = 0; i < n; i++, e++) {
        if (fn_80291188(name, e->name) == 0) {
            return i;
        }
    }
    return -1;
}

Entry24* fn_800A7FAC(int i) {
    if (i < 0) {
        return NULL;
    }
    return (Entry24*)Data(lbl_804CB674) + i;
}

static inline int Index24(const char* name) {
    if (name == NULL) {
        return -1;
    }
    int n;
    Entry24* e;
    int i;
    TBL_COUNT(n, lbl_804CB674);
    TBL_DATA(e, Entry24, lbl_804CB674);
    for (i = 0; i < n; i++, e++) {
        if (fn_80291188(name, e->name) == 0) {
            return i;
        }
    }
    return -1;
}

static inline Entry24* At24(int i) {
    if (i < 0) {
        return NULL;
    }
    return (Entry24*)Data(lbl_804CB674) + i;
}

Entry24* fn_800A8008(const char* name) {
    return At24(Index24(name));
}

Entry24* fn_800A80F8(u8** p) {
    const char* s = (const char*)(*p + 4);
    int n = Count(lbl_804CB674);
    Entry24* e = (Entry24*)Data(lbl_804CB674);
    for (int i = 0; i < n; i++, e++) {
        if (fn_80291188(e->name2, s) == 0) {
            return e;
        }
    }
    return NULL;
}

Entry8* fn_800A81AC(int i) {
    if (i < 0) {
        return NULL;
    }
    return (Entry8*)Data(lbl_804CB678) + i;
}

struct EntryC {
    const char* name;
    u8 pad[8];
};

int fn_800A8208(const char* name) {
    if (name == NULL) {
        return 0;
    }
    int n = Count(lbl_804CB67C);
    EntryC* e = (EntryC*)Data(lbl_804CB67C);
    for (int i = 0; i < n; i++, e++) {
        if (fn_80291188(name, e->name) == 0) {
            return i;
        }
    }
    return -1;
}

EntryC* fn_800A82C8(int i) {
    if (i < 0) {
        return NULL;
    }
    return (EntryC*)Data(lbl_804CB67C) + i;
}

EntryC* fn_800A8324(const char* name) {
    if (name == NULL) {
        return NULL;
    }
    int n = Count(lbl_804CB680);
    EntryC* e = (EntryC*)Data(lbl_804CB680);
    for (int i = 0; i < n; i++, e++) {
        if (fn_80291188(e->name, name) == 0) {
            return e;
        }
    }
    return NULL;
}

Entry10* fn_800A83E4(const char* name) {
    if (name == NULL) {
        return NULL;
    }
    int n = Count(lbl_804CB688);
    Entry10* e = (Entry10*)Data(lbl_804CB688);
    for (int i = 0; i < n; i++, e++) {
        if (fn_80291188(e->name, name) == 0) {
            return e;
        }
    }
    return NULL;
}

u32 fn_800A67EC(u8* p) {
    return (u32)(p - Data(lbl_804CB674)) / 0x24;
}

u32 fn_800A6B7C(u8* p) {
    return (u32)(p - Data(lbl_804CB67C)) / 0xC;
}

struct Params {
    u8 pad[0x10];
    u32 flags;
    u8 pad14[4];
    s16 v[1];
};

extern u8* lbl_804CB694;
extern u8* lbl_804CB698;
extern u8* lbl_804CB69C;
extern const f32 lbl_804CD2C8;
extern const f32 lbl_804CD2CC;
extern const f32 lbl_804CD2D8;

static inline int Index98(const char* name) {
    if (name == NULL) {
        return 0;
    }
    int n;
    const char** e;
    int i;
    TBL_COUNT(n, lbl_804CB698);
    TBL_DATA(e, const char*, lbl_804CB698);
    for (i = 0; i < n; i++, e++) {
        if (fn_80291188(name, *e) == 0) {
            return i;
        }
    }
    return -1;
}

f32 fn_800A7370(Params* self, const char* name) {
    int i = Index98(name);
    if (i < 0) {
        return lbl_804CD2C8;
    }
    return lbl_804CD2CC * self->v[i];
}

static inline int Index94(const char* name) {
    if (name == NULL) {
        return 0;
    }
    int n;
    const char** e;
    int i;
    TBL_COUNT(n, lbl_804CB694);
    TBL_DATA(e, const char*, lbl_804CB694);
    for (i = 0; i < n; i++, e++) {
        if (fn_80291188(name, *e) == 0) {
            return i;
        }
    }
    return -1;
}

#pragma push
#pragma use_lmw_stmw on
u32 fn_800A7460(Params* self, const char* name) {
    int i = Index94(name);
    if (i < 0) {
        return 0;
    }
    return self->flags & (1 << i);
}
#pragma pop

struct BitRow {
    u32 w[4];
};

struct BitOwner {
    u8 pad[0x40];
    BitRow rows[1];
};

BOOL fn_800A7324(BitOwner* self, int i, int b) {
    return (self->rows[i].w[b / 32] & (1 << (b % 32))) != 0;
}

extern u8* lbl_804CB65C;
extern u8* lbl_804CB660;

struct Entry14b {
    u8 pad[4];
    u16 v[8];
};

u8* fn_800A85CC(int a, int b) {
    Entry14b* p = (Entry14b*)Data(lbl_804CB65C) + a;
    if (p == NULL) {
        return NULL;
    }
    u8* q;
    TBL_DATA(q, u8, lbl_804CB660);
    return q + p->v[b] * 0x14;
}

extern u8* lbl_804CB664;
extern u8* lbl_804CB684;
extern u8* lbl_804CB68C;
extern char lbl_803651B0[];

void fn_80290DDC(char*, const char*, ...);
u32 fn_8023F9F4(char*);
void fn_8023F1A0(char*, s32);
u32 fn_80089ED0();
void fn_800E24F8(void*);
void fn_80257340(void*, s32);
s32 fn_80257740();
void fn_80320978(unsigned long long);

int fn_800A64AC(const char* s) {
    if (s != NULL) {
        if (fn_80291188(s, lbl_803651B0) == 0) {
            return 0;
        }
        if (fn_80291188(s, lbl_803651B0 + 7) == 0) {
            return 1;
        }
        if (fn_80291188(s, lbl_803651B0 + 0xE) == 0) {
            return 2;
        }
        if (fn_80291188(s, lbl_803651B0 + 0x15) == 0) {
            return 3;
        }
        if (fn_80291188(s, lbl_803651B0 + 0x1C) == 0) {
            return 4;
        }
    }
    return -1;
}

struct CharAnim {
    u8 pad[0x4];
    s16 h[5];
};

static inline int AnimId(int v) {
    int r = -1;
    if (v >= 0) {
        r = v;
    }
    return r;
}

u8* fn_800A66C4(CharAnim* a, int i) {
    int id;
    if (i < 0 || i >= 5) {
        id = -1;
    } else {
        id = AnimId(a->h[i]);
    }
    if (id < 0) {
        if (i == 3) {
            id = AnimId(a->h[2]);
        }
        if (id < 0) {
            id = AnimId(a->h[0]);
        }
    }
    if (id < 0) {
        return NULL;
    }
    return Data(lbl_804CB664) + id * 0x18;
}

static inline u8* At658(int i) {
    if (i < 0) {
        return NULL;
    }
    return Data(lbl_804CB658) + i * 0x18;
}

struct Ent18 {
    u8 pad[4];
    void* s[5];
};

struct Ctl {
    u8 pad[0xC];
    u8 idx;
};

void fn_800A6588(Ctl* c) {
    Ent18* e = (Ent18*)At658(c->idx);
    if (e != NULL) {
        for (int i = 0; i < 5; i++) {
            if (e->s[i] != NULL) {
                fn_800E24F8(e->s[i]);
            }
        }
    }
}

#define OS_BUS_CLOCK (*(u32*)0x800000F8)

struct Slot4 {
    u8 pad[4];
    void* h;
    void* s8;
    void* sc;
    void* s10;
};

void fn_800A6618(Slot4* s) {
    if (s->h != NULL) {
        fn_80257340(s->h, 0x10000);
        while (fn_80257740() == 0) {
            fn_80320978((OS_BUS_CLOCK / 4 / 1000) * 5LL);
        }
    }
}

void fn_800A6790(Slot4* s) {
    if (s->s8 != NULL) {
        fn_800E24F8(s->s8);
    }
    if (s->sc != NULL) {
        fn_800E24F8(s->sc);
    }
    if (s->s10 != NULL) {
        fn_800E24F8(s->s10);
    }
}

struct Named4 {
    u8 pad[4];
    const char* name;
};

static inline char* MakePath(Named4* e, char* buf) {
    fn_80290DDC(buf, lbl_803651B0 + 0x1F, e->name);
    if (fn_8023F9F4(buf) == 0x40000) {
        return NULL;
    }
    return buf;
}

char* fn_800A6BD4(Named4* e, char* buf) {
    fn_80290DDC(buf, lbl_803651B0 + 0x1F, e->name);
    if (fn_8023F9F4(buf) == 0x40000) {
        return NULL;
    }
    return buf;
}

struct RandSet {
    u8 pad[0xB];
    u8 n;
    u8* ids;
    u8* weights;
};

u8* fn_800A6C38(RandSet* s) {
    int n = s->n;
    int sel = 0;
    if (n > 1) {
        int r = fn_80089ED0() % 100;
        for (int i = 0; i < n; i++) {
            r -= s->weights[i];
            if (r < 0) {
                sel = i;
                break;
            }
        }
    }
    n = s->ids[sel];
    if (n < 0) {
        return NULL;
    }
    return Data(lbl_804CB680) + n * 0xC;
}

struct Lookups {
    u8 pad[4];
    s16 h[1];
};

u8* fn_800A6D08(Lookups* l, int i) {
    if (i < 0) {
        return NULL;
    }
    int id = l->h[i];
    if (id < 0) {
        return NULL;
    }
    return Data(lbl_804CB684) + id * 0x14;
}

struct Lookups2 {
    u8 pad[8];
    s8* t[1];
};

u8* fn_800A6D7C(Lookups2* l, int i, int j) {
    int id = l->t[i][j];
    if (id < 0) {
        return NULL;
    }
    return Data(lbl_804CB684) + id * 0x14;
}

struct Lookups3 {
    u8 pad[0x140];
    s16 h[1];
};

u8* fn_800A6F34(Lookups3* l, int i) {
    int id = l->h[i];
    if (id < 0) {
        return NULL;
    }
    return Data(lbl_804CB68C) + id * 0x48;
}

extern void fn_800763E0(const char*);

void fn_800A8B70() {
    fn_800763E0(lbl_803651B0 + 0x45);
}


} // extern "C"
