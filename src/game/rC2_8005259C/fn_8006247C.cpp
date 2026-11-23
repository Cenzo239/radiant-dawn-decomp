#include "game/rC2_8005259C/base.h"
struct FlagTable { u8 pad[0x144]; const char* names[0x80]; u32 hashes[0x80]; u8 bits[0x10]; };
extern "C" {
extern FlagTable lbl_803CAB38;
extern char lbl_803620E4[116];
extern u8 lbl_803CB770[];
u32 fn_80076D18(const char*);
int fn_80291188(const char*, const char*);
void fn_8013B974(void);
void fn_80066968(void*);
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
static inline bool flagGet(FlagTable* t, const char* const& name) {
    if (name[0] == 0) {
        return false;
    }
    return flagGetBit(t, flagFind(t, name));
}
static inline bool at1(const char* s) { return flagGet(&lbl_803CAB38, s); }

extern "C" void fn_8006247C(void) {
    fn_8013B974();
    if (at1(lbl_803620E4 + 0x2c)) {
        fn_80066968(lbl_803CB770);
    }
}
