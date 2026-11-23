#include "game/rE_800E5DE4/types.h"
#pragma use_lmw_stmw on
extern const char lbl_80361390[0x200];
extern void* lbl_804CA4DC;
typedef struct SysInfo { u8 pad[0x1bc8]; u8 lang; } SysInfo;
struct SkD { u8 pad[0x1f]; u8 x1f; };
struct Sk { SkD* d; };
struct BU { u8 pad[0x12c]; u8 x12c[4]; };
extern "C" {
SysInfo* fn_8024BC94(void);
const char* fn_8011A054(SkD*);
#if TARGET_PC
FE10_PROTO const char* fn_8011A174(Sk*, p32arg);
#else
const char* fn_8011A174(Sk*, int);
#endif
int fn_80290D04(char* buf, int n, const char* fmt, ...);
void fn_800D0B38(int idx, const char* s);
int fn_8011B77C(void* skills, void* sid);
const char* fn_800D08B4(const char* key, int a);
#if TARGET_PC
FE10_PROTO void fn_801ABBA8(const char* msg, ptr32<const void>, void* a, int b);
#else
void fn_801ABBA8(const char* msg, const char* sfx, void* a, int b);
#endif
static inline int Ix(SkD* d) { return d->x1f ? d->x1f - 1 : 0; }
#pragma inline_max_size(4000)
static inline void body(Sk* s, void* a, BU* u, const char*& nm) {
    /*P*/
    int ix;
    const char* pool;
    const char* key;
    /*E*/
    char buf[0x80];
        pool = lbl_80361390;
    key = pool + 0x8c;
    switch (fn_8024BC94()->lang) {
    case 1:
        ix = Ix(s->d);
        nm = fn_8011A054(s->d);
        fn_80290D04(buf, 0x80, pool + 0x98, fn_8011A174(s, 0), nm, ix);
        break;
    default:
        {
        const char* n2 = fn_8011A054(s->d);
        fn_80290D04(buf, 0x80, pool + 0xa7, Ix(s->d), n2);
        }
        break;
    }
    fn_800D0B38(0, buf);
    fn_801ABBA8(fn_800D08B4(key, fn_8011B77C(u->x12c, lbl_804CA4DC)), pool, a, 0);
}
void fn_80031B24(Sk* s, void* a, BU* u) { const char* nm; body(s, a, u, nm); }
}
