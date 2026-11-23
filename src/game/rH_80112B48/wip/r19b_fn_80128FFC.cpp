/* NOT MATCHING (other, round 19b first draft): fn_80128FFC = MSL basic_string(const basic_string&, pos, n). 84 of 85 instructions; right logic, but the stack slots come out in the opposite order (original: allocator temp 0x8/0xc, first min temp 0x10, assign's n copy 0x14, second min temp 0x18, parameter n 0x1c) and the error string is loaded after __files instead of before.
 * fn_80128AA0 (not written) is its caller: std::string s(name); s = s.substr(0, s.size() - 1); s += "3"/"2"/"1" by fn_8012C250(u, 5) >= 0x14b / >= 0xfb; return fn_8010B228(s.c_str()). Both share the pool lbl_80369170 ("3", "2", "1", "basic_string: out_of_range"), so they belong in one file with fn_80128AA0 first. */
#include "game/rH_80112B48/types.h"
#pragma pool_strings on
struct Empty {
    Empty() {}
    char c;
};
struct MslString {
    union {
        struct { u32 isLong : 1; u32 pad : 31; u32 size; char* data; } l;
        struct { u8 isLong : 1; u8 size : 7; char data[11]; } s;
    };
};
extern "C" {
extern u8 __files[];
void fn_80290B48(void*, const char*, ...);
void fn_80291BD0(void);
u32 strlen(const char*);
void fn_80024EFC(MslString*, u32);
void fn_800250B0(MslString*, u32, u32, const char*, const char*, const Empty&);
void fn_80079210(void*);
void* fn_8010B228(const char*);
s16 fn_8012C250(void*, u8);
void fn_80128FFC(MslString* out, MslString* str, u32 pos, u32 n);
}
static inline const u32& umin(const u32& a, const u32& b) { return b < a ? b : a; }
static inline void strErr(const char* msg) { fn_80290B48(__files + 0xa0, msg); fn_80291BD0(); }
static inline u32 strSize(const MslString* s) { return s->l.isLong == 0 ? s->s.size : s->l.size; }
static inline void strRep(MslString* s, u32 pos, u32 n1, const char* f, const char* l, Empty e) {
    fn_800250B0(s, pos, n1, f, l, e);
}
static inline void strAssignSub(MslString* out, const MslString* str, u32 pos, u32 n) {
    const char* p;
    u32 sz;
    if (str->l.isLong == 0) {
        p = str->s.data;
        sz = str->s.size;
    } else {
        p = str->l.data;
        sz = str->l.size;
    }
    if (pos > sz) {
        strErr("basic_string: out_of_range");
    }
    n = umin(n, sz - pos);
    p += pos;
    strRep(out, 0, 0, p, p + n, Empty());
}
extern "C" void fn_80128FFC(MslString* out, MslString* str, u32 pos, u32 n) {
    u32 sz;
    *(u32*)out = 0;
    out->l.size = 0;
    out->l.data = 0;
    sz = strSize(str);
    fn_80024EFC(out, pos <= sz ? umin(n, sz - pos) : 0);
    strAssignSub(out, str, pos, n);
}
