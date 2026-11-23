#include "game/rC2_8005259C/base.h"
/* Map highlight list: fills a list of x,y pairs from a query. Play timer split. */
struct P8 { u8 x, y; };
struct Mark {
    u8 pad[0xA0];
    u64 ticks;
    u8 pad2[0x954 - 0xA8];
    s8 n;
    P8 pts[1];
};
extern "C" {
int fn_8010CF20(void*, P8*);
}
static inline void push(Mark* m, u8 x, u8 y) {
    m->pts[m->n].x = x;
    m->pts[m->n].y = y;
    m->n++;
}
static inline s8 fill(Mark* m, void* q, P8* buf) {
    int n = fn_8010CF20(q, buf);
    for (int i = 0; i < n; i++) {
        push(m, buf[i].x, buf[i].y);
    }
    return n;
}
extern "C" {
s8 fn_80061AB8(Mark* m, void* q) {
    P8 buf[0x40]; m->n = 0; return fill(m, q, buf);
}
s8 fn_80061DD0(Mark* m, void* q) {
    P8 buf[0x40];
    int n = fn_8010CF20(q, buf);
    for (int i = 0; i < n; i++) {
        push(m, buf[i].x, buf[i].y);
    }
    return n;
}

}
