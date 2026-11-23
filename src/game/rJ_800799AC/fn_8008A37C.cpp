/* String cursor: returns the current position and advances it by `n`, or past
   the terminator when n < 0 (names guessed). */
#include "game/rJ_800799AC/types.h"

extern "C" u32 strlen(const char*);
struct Cur { void* x0; char* pos; };

static inline int step(const char* p, int n) {
    if (n >= 0) {
        return n;
    }
    return strlen(p) + 1;
}

extern "C" char* fn_8008A37C(Cur* c, int n) {
    char* p = c->pos;
    c->pos += step(p, n);
    return p;
}
