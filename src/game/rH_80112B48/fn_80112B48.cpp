/* Item name getter with the recursion written out by hand, 80112B48. */
#include "game/rH_80112B48/unit.h"
#pragma auto_inline off
extern "C" {
extern int fn_8011B77C(void*, void*);
extern u8* fn_801116B8(Inv*);
#if TARGET_PC
extern FE10_PROTO void * fn_80076F54(void*);
#else
extern int fn_80076F54(void*);
#endif
extern char* fn_800D0864(void*);
extern int fn_80108660(void* s);
extern char* fn_8010F5E0(void*);
struct NmS { char** p; u8 b4; u8 pad:2; u8 own:1; u8 r:5; char buf[1]; };
char* fn_80112B48(NmS* s);
#define LV(x) if (s->own) return s->buf; \
    p = s->p; if (p == 0) return 0; \
    if (!s->own) { \
        if (fn_80076F54(p[1])) return fn_800D0864(p[1]); \
        return p[0]; \
    } \
    x
static inline char* L4(NmS* s) {
    char** p;
    if (s->own) return s->buf;
    p = s->p; if (p == 0) return 0;
    if (fn_80108660(s) == 0) return fn_8010F5E0(s->p);
    return fn_80112B48(s);
}
static inline char* L3(NmS* s) { char** p; LV(return L4(s);) }
static inline char* L2(NmS* s) { char** p; LV(return L3(s);) }
#pragma push
#pragma inline_max_size(600)
char* fn_80112B48(NmS* s) {
    char** p;
    LV(return L2(s);)
}
#pragma pop
}
