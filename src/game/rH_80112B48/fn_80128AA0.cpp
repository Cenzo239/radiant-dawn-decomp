/* fn_80128AA0 (0x2D0): exact (round 21; check_func.py --strict-references MATCH).
 * Looks up the weapon-rank variant of a unit's job: takes the job's id string (job->s1C), drops its last
 * character and appends "3", "2" or "1" by fn_8012C250(u, 5) (>= 0x14b, >= 0xfb, else), then returns
 * fn_8010B228(name). MSL std::string throughout:
 *   std::string s(job->s1C); s = s.substr(0, s.size() - 1); s += "3"/"2"/"1"; return fn_8010B228(s.c_str());
 * Shares the string pool lbl_80369170 with fn_80128FFC (substr constructor, wip/r19b_fn_80128FFC.cpp).
 * Codegen notes: the string is a struct with only a destructor (construction through the strCtor inline keeps
 * the Empty temporaries in the original's slots; a real constructor moves them); the result of fn_8010B228 is
 * returned straight from the call so that the destructor temp gets r31. The "3"/"2"/"1" literals are the
 * first six bytes of the pool lbl_80369170 (pool_strings on); fn_80128FFC's "basic_string: out_of_range"
 * follows there.
 */
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
struct JobS { u8 pad0[0x1c]; const char* s1C; };
struct UnitS { u8 pad0[0xf0]; JobS* job; };
extern "C" {
u32 strlen(const char*);
void fn_80024EFC(MslString*, u32);
void fn_800250B0(MslString*, u32, u32, const char*, const char*, Empty);
void fn_80079210(void*);
void* fn_8010B228(const char*);
int fn_8012C250(UnitS*, int);
void fn_80128FFC(MslString* out, MslString* str, u32 pos, u32 n);
void* fn_80128AA0(UnitS* u);
}
static inline u32 strSize(const MslString* s) { return s->l.isLong == 0 ? s->s.size : s->l.size; }
static inline const char* strData(const MslString* s) { return s->l.isLong == 0 ? s->s.data : s->l.data; }
static inline void strCtor(MslString* s, const char* p) {
    u32 n;
    *(u32*)s = 0;
    s->l.size = 0;
    s->l.data = 0;
    n = strlen(p);
    fn_80024EFC(s, n);
    fn_800250B0(s, 0, 0, p, p + n, Empty());
}
static inline void strDtor(MslString* s) {
    if (s->l.isLong) {
        fn_80079210(s->l.data);
    }
}
static inline void strAssign(MslString* s, const MslString* o) {
    if (s->l.isLong == 0 && o->l.isLong == 0) {
        *s = *o;
    } else {
        u32 n = s->l.isLong ? s->l.size : s->s.size;
        const char* p;
        u32 m;
        if (o->l.isLong == 0) {
            p = o->s.data;
            m = o->s.size;
        } else {
            p = o->l.data;
            m = o->l.size;
        }
        fn_800250B0(s, 0, n, p, p + m, Empty());
    }
}
static inline void strAppend(MslString* s, const char* p) {
    u32 n = strSize(s);
    fn_800250B0(s, n, 0, p, p + strlen(p), Empty());
}
struct Str : MslString {
    ~Str() { strDtor(this); }
};
extern "C" void* fn_80128AA0(UnitS* u) {
    const char* name = u->job->s1C;
    int lv;
    if (name == 0) {
        return 0;
    }
    Str s;
    strCtor(&s, name);
    lv = fn_8012C250(u, 5);
    {
        Str t;
        fn_80128FFC(&t, &s, 0, strSize(&s) - 1);
        strAssign(&s, &t);
    }
    if ((s16)lv >= 0x14b) {
        strAppend(&s, "3");
    } else if ((s16)lv >= 0xfb) {
        strAppend(&s, "2");
    } else {
        strAppend(&s, "1");
    }
    return fn_8010B228(strData(&s));
}
