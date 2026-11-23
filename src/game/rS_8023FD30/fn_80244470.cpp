#include "game/rS_8023FD30/types.h"

/* Builds "PID_xxx"-style names from the id tables in the save header into its string. */
struct Empty {
    Empty() {}
    char c;
};

struct MslString {
    union {
        struct {
            u32 isLong : 1;
            u32 pad : 31;
            u32 size;
            char* data;
        } l;
        struct {
            u8 isLong : 1;
            u8 size : 7;
            char data[11];
        } s;
    };
};

struct NameTables {
    const char** persons;  /* +0x00 */
    u8 pad04[8];
    const char** jobs;     /* +0x0C */
    u8 pad10[8];
    const char** items;    /* +0x18 */
    u8 pad1C[8];
    const char** skills;   /* +0x24 */
    u8 pad28[8];
    const char** seq30;    /* +0x30 */
    u8 pad34[8];
    const char** seq3C;    /* +0x3C */
    u8 pad40[8];
    const char** seq48;    /* +0x48 */
    u8 pad4C[8];
    const char** seq54;    /* +0x54 */
    u8 pad58[8];
    MslString str;         /* +0x60 */
};

extern "C" {

extern char lbl_80372B4C[];
u32 strlen(const char*);
void fn_800250B0(MslString*, u32, u32, const char*, const char*, const Empty&);

}

static inline u32 strSize(MslString* s) {
    return s->l.isLong == 0 ? s->s.size : s->l.size;
}

static inline const char* strData(MslString* s) {
    return s->l.isLong == 0 ? s->s.data : s->l.data;
}

static inline void strAssign(MslString* s, const char* p, u32 n, Empty e) {
    u32 len;
    len = strlen(p);
    fn_800250B0(s, 0, n, p, p + len, e);
}

static inline void strAppend(MslString* s, const char* p, u32 n, Empty e) {
    u32 len;
    len = strlen(p);
    fn_800250B0(s, n, 0, p, p + len, e);
}

static inline void strAssignZ(MslString* s, const char* const& p) {
    u32 n = strSize(s);
    strAssign(s, p, n, Empty());
}

static inline void strAppendZ(MslString* s, const char* p) {
    u32 n = strSize(s);
    strAppend(s, p, n, Empty());
}

extern "C" {

#define NAME_BODY(lit, value) \
        strAssignZ(&t->str, lit); \
        strAppendZ(&t->str, value); \
        return strData(&t->str);

#define NAME1(addr, prefix, field) \
    const char* fn_##addr(NameTables* t, s32 i) { \
        NAME_BODY(lbl_80372B4C + prefix, t->field[i - 1]) \
    }

#define NAME2(addr, prefix, field) \
    const char* fn_##addr(NameTables* t, u16 i) { \
        NAME_BODY(lbl_80372B4C + prefix, t->field[i]) \
    }

NAME1(80244470, 0x50, persons)
NAME1(80244580, 0x55, jobs)
NAME1(80244690, 0x5A, items)
NAME2(802447A0, 0x5F, skills)
NAME2(802448AC, 0x64, seq30)
NAME2(802449B8, 0x64, seq3C)
NAME2(80244AC4, 0x64, seq48)
NAME2(80244BD0, 0x69, seq54)

}
