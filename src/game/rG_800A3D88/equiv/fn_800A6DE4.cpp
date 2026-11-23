/* fn_800A6DE4: functionally equal (regs, 9 of 84 words differ in registers only). Helpers from fn_800A7528.cpp (exported bodies removed), body from wip/fn_800A6DE4.cpp with the path buffer at 0x44 bytes (stack offset 0x14 in the original). */
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
Entry154* fn_800A7528(const char* name);

u8* fn_800A7948(int i);


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
Entry10* fn_800A7B38(const char* name);

int fn_800A7C28(const char* name);

Entry8* fn_800A7CE8(int i);


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
Entry14* fn_800A7D44(const char* name);

Entry14* fn_800A7E34(const char** name);


struct Entry24 {
    const char* name;
    const char* name2;
    u8 pad[0x1C];
};
int fn_800A7EEC(const char* name);

Entry24* fn_800A7FAC(int i);


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
Entry24* fn_800A8008(const char* name);

Entry24* fn_800A80F8(u8** p);

Entry8* fn_800A81AC(int i);


struct EntryC {
    const char* name;
    u8 pad[8];
};
int fn_800A8208(const char* name);

EntryC* fn_800A82C8(int i);

EntryC* fn_800A8324(const char* name);

Entry10* fn_800A83E4(const char* name);

u32 fn_800A67EC(u8* p);

u32 fn_800A6B7C(u8* p);


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
f32 fn_800A7370(Params* self, const char* name);


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

u32 fn_800A7460(Params* self, const char* name);

#pragma pop

struct BitRow {
    u32 w[4];
};

struct BitOwner {
    u8 pad[0x40];
    BitRow rows[1];
};
BOOL fn_800A7324(BitOwner* self, int i, int b);


extern u8* lbl_804CB65C;
extern u8* lbl_804CB660;

struct Entry14b {
    u8 pad[4];
    u16 v[8];
};
u8* fn_800A85CC(int a, int b);


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
int fn_800A64AC(const char* s);


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
u8* fn_800A66C4(CharAnim* a, int i);


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
void fn_800A6588(Ctl* c);


#define OS_BUS_CLOCK (*(u32*)0x800000F8)

struct Slot4 {
    u8 pad[4];
    void* h;
    void* s8;
    void* sc;
    void* s10;
};
void fn_800A6618(Slot4* s);

void fn_800A6790(Slot4* s);


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
char* fn_800A6BD4(Named4* e, char* buf);


struct RandSet {
    u8 pad[0xB];
    u8 n;
    u8* ids;
    u8* weights;
};
u8* fn_800A6C38(RandSet* s);


struct Lookups {
    u8 pad[4];
    s16 h[1];
};
u8* fn_800A6D08(Lookups* l, int i);


struct Lookups2 {
    u8 pad[8];
    s8* t[1];
};
u8* fn_800A6D7C(Lookups2* l, int i, int j);


struct Lookups3 {
    u8 pad[0x140];
    s16 h[1];
};
u8* fn_800A6F34(Lookups3* l, int i);


extern void fn_800763E0(const char*);
void fn_800A8B70();



} // extern "C"


/* ---- from rG_800A3D88/wip/fn_800A6DE4.cpp ---- */
extern "C" {
// fn_800A6DE4: 13/84 words differ (buf at 0x18 not 0x14, colours). fn_800A75E8: 77/98, colours in the two Find154 inlines.
static inline RandSet* Get684(s8** t, int j) {
    int id = (*t)[j];
    if (id < 0) {
        return NULL;
    }
    return (RandSet*)(Data(lbl_804CB684) + id * 0x14);
}

static inline Named4* Get680(RandSet* s, int j) {
    int v = s->ids[j];
    if (v < 0) {
        return NULL;
    }
    return (Named4*)(Data(lbl_804CB680) + v * 0xC);
}

#pragma push
#pragma use_lmw_stmw on
void fn_800A6DE4(Lookups2* l, int i) {
    char buf[0x44];
    int n;
    TBL_COUNT(n, lbl_804CB67C);
    for (int c = 0; c < n; c++) {
        RandSet* s = Get684(&l->t[i], c);
        if (s != NULL) {
            int m = s->n;
            for (int j = 0; j < m; j++) {
                Named4* e = Get680(s, j);
                if (e != NULL) {
                    if (MakePath(e, buf) != NULL) {
                        fn_8023F1A0(buf, 0x40);
                    }
                }
            }
        }
    }
}
#pragma pop

void* fn_800F416C(void*);
struct Rule {
    u8 pad[0xC];
    const char* a;
    const char* b;
};
Rule* fn_800A7770(void*, void*, void*);

struct UnitChr {
    u8 pad[0xEC];
    void** ec;
    void** f0;
};

static inline Entry154* Find154(const char* name) {
    if (name == NULL) {
        return NULL;
    }
    int n;
    Entry154* e;
    int i;
    TBL_COUNT(n, lbl_804CB650);
    TBL_DATA(e, Entry154, lbl_804CB650);
    for (i = 0; i < n; i++, e++) {
        if (fn_80291188(e->name, name) == 0) {
            return e;
        }
    }
    return NULL;
}
}
