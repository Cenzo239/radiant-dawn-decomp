/* Script command 0xC handler: waits on a named flag, then hands the command
   to the event runner. Names guessed. */
#include "game/rJ_800799AC/types.h"
#pragma use_lmw_stmw on

extern "C" {
char* fn_8009D948(void* cmd, int ofs);
u32 fn_80076D18(const char*);
int fn_80291188(const char*, const char*);
void* fn_800C3558(void);
void fn_801D0D58(void*, void*);
void fn_801D0E18(void*);
}

struct FlagTable {
    u8 pad0[0x144];
    const char* names[0x80]; /* 0x144 */
    u32 hashes[0x80];        /* 0x344 */
    u8 bits[0x10];           /* 0x544 */
};
extern "C" FlagTable lbl_803CAB38;

static inline int flagFind(FlagTable* t, const char* name) {
    u32 h = fn_80076D18(name);
    FlagTable* p = t;
    int i;
    for (i = 0; i < 0x80; i++) {
        if (h == p->hashes[0] && fn_80291188(p->names[0], name) == 0) {
            return i;
        }
        p = (FlagTable*)((u8*)p + 4);
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
    if (*name == 0) {
        return false;
    }
    return flagGetBit(t, flagFind(t, name));
}

struct Cmd { u8 pad[0x14]; u16 x14; };

extern "C" int fn_8008D91C(Cmd* cmd) {
    char* name = fn_8009D948(cmd, cmd->x14);
    if (*name != 0 && !flagGet(&lbl_803CAB38, name)) {
        return 0;
    }
    fn_801D0D58(fn_800C3558(), cmd);
    fn_801D0E18(fn_800C3558());
    return 1;
}
