/* NEAR MISS: fn_800581F4 and fn_8005840C. GET still expands to the by-value wrapper here (88/87 words, wrong lbz form). Best: get0 taking const char* s, wrapped by get2(const char* const& s), and p then ends in r26 where the originals want r29 / r27: 12 and 10 words off. */
/* Create the sortie process, unless the chapter's event flag says it has no scene. */
#include "game/rC2_8005259C/base.h"
struct FlagTable { u8 pad[0x144]; const char* names[0x80]; u32 hashes[0x80]; u8 bits[0x10]; };
struct Opt { u8 pad[0x8c]; u8 b8c; };
struct Pr { u8 pad[0x40]; int a40; int a44; int a48; };
extern "C" {
extern FlagTable lbl_803CAB38;
extern char lbl_80361F9C[316];
extern u32 lbl_804CB700;
extern u8 lbl_8037E248[];
u32 fn_80076D18(const char*);
int fn_80291188(const char*, const char*);
Opt* fn_8006074C(FlagTable*);
void* fn_80085708(const char*);
Pr* fn_80081194(void*, void*);
Pr* fn_80081050(void*, void*);
void fn_801E4094(Pr*);
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
static inline bool flagHas(FlagTable* t, const char* const& name) {
    if (name[0] == 0) {
        return false;
    }
    return flagFind(t, name) >= 0;
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
static inline bool flagGet(FlagTable* t, const char* const& name) {
    if (name[0] == 0) {
        return false;
    }
    return flagGetBit(t, flagFind(t, name));
}
static inline bool has0(const char* s) { return flagHas(&lbl_803CAB38, s); }
static inline bool get0(const char* s) { return flagGet(&lbl_803CAB38, s); }
#define GET get0(lbl_80361F9C)
#define MKPROC(p, parent, mode) \
    if (parent) { \
        p = fn_80081194(lbl_8037E248, parent); \
    } else { \
        p = fn_80081050(lbl_8037E248, parent); \
    } \
    if (p) { \
        fn_801E4094(p); \
        p->a40 = 0; \
        p->a44 = 0; \
        p->a48 = 0; \
    } \
    p->a40 = mode;

#pragma use_lmw_stmw on
extern "C" Pr* fn_800581F4(void* parent) {
    int mode;
    Pr* p;
    if (lbl_804CB700 & 0x10) {
        mode = 1;
    } else {
        mode = fn_8006074C(&lbl_803CAB38)->b8c;
    }
    if (mode == 0) {
        p = 0;
    } else {
        if (flagHas(&lbl_803CAB38, lbl_80361F9C) && GET) {
            if (fn_80085708(lbl_80361F9C + 0xd) == 0) {
                p = 0;
                goto end;
            }
        }
        MKPROC(p, parent, mode)
    }
end:
    return p;
}

extern "C" Pr* fn_8005840C(int mode, void* parent) {
    Pr* p;
    if (mode == 0) {
        return 0;
    }
    if (flagHas(&lbl_803CAB38, lbl_80361F9C) && GET) {
        if (fn_80085708(lbl_80361F9C + 0xd) == 0) {
            return 0;
        }
    }
    MKPROC(p, parent, mode)
    return p;
}
