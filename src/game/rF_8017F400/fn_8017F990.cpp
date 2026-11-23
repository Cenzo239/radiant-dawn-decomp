#include "game/rF_8017F400/types.h"
extern "C" {

typedef s64 OSTime;
extern OSTime OSGetTime(void);
extern int fn_8028DB54(int x); /* abs */

#define OS_BUS_CLOCK (*(u32*)0x800000F8)
#define OS_TIMER_CLOCK (OS_BUS_CLOCK / 4)

extern int lbl_804CB8D8;    /* frame counter */
extern OSTime lbl_804CB8E0; /* previous frame time */
extern OSTime lbl_804CB8E8; /* current frame time */

/* random-ish int in [min(a,b), ...) from the timer */
int fn_8017F990(int a, int b)
{
    int range = fn_8028DB54(b - a);
    int r = (OSGetTime() / (OS_TIMER_CLOCK / 1000)) % range;
    if (a < b) {
        return r + a;
    }
    return r + b;
}

int fn_8017FA1C(void)
{
    return lbl_804CB8D8;
}

OSTime fn_8017FA24(void)
{
    return lbl_804CB8E8 - lbl_804CB8E0;
}

void fn_8017FA40(void)
{
    lbl_804CB8D8++;
    lbl_804CB8E0 = lbl_804CB8E8;
    lbl_804CB8E8 = OSGetTime();
}

/* OSTime -> hours/minutes/seconds */
void fn_8017FA84(OSTime t, u32* h, u32* m, u32* s)
{
    u32 sec = t / OS_TIMER_CLOCK;
    *s = sec % 60;
    *m = (sec / 60) % 60;
    *h = sec / 3600;
}

typedef struct Rect16 {
    s16 x0, y0, x1, y1;
} Rect16;

/* rects overlap (inclusive) */
BOOL fn_8017FB24(Rect16* a, Rect16* b)
{
    if (a->x1 < b->x0) {
        return 0;
    }
    if (b->x1 < a->x0) {
        return 0;
    }
    if (a->y1 < b->y0) {
        return 0;
    }
    if (b->y1 < a->y0) {
        return 0;
    }
    return 1;
}

static inline void Rect16_Move(Rect16* r, s16 dx, s16 dy)
{
    r->x0 += dx;
    r->y0 += dy;
    r->x1 += dx;
    r->y1 += dy;
}

/* move rect so its origin is at 0,0 */
void fn_8017FB88(Rect16* r)
{
    Rect16_Move(r, -r->x0, -r->y0);
}

/* OS message queue (OSMessageQueue is 0x20 bytes) */
typedef struct OSThread {
    u8 pad[0x318];
} OSThread;
typedef struct OSMessageQueue {
    u8 pad[0x20];
} OSMessageQueue;
typedef void* OSMessage;
extern int fn_8031D34C(OSMessageQueue* q, OSMessage* msg, int flags); /* OSReceiveMessage */
extern int fn_8031D284(OSMessageQueue* q, OSMessage msg, int flags);  /* OSSendMessage */
extern int fn_8017F4C8(void* src, void* dst);

typedef struct DecompRequest {
    void* src;
    void* dst;
    void (*callback)(void* arg, void* src, void* dst);
    void* arg;
} DecompRequest;

/* file statics; CW (C++ mode) lays them out in declaration order:
   sThread = lbl_80418680, sStack = +0x318, sReqQ = lbl_8041C998, sFreeQ = lbl_8041C9B8 */
static OSThread sThread;
static u8 sStack[0x4000];
static OSMessageQueue sReqQ;
static OSMessageQueue sFreeQ;

/* queue a background LZ decompression */
void fn_8017FBCC(void* src, void* dst, void (*callback)(void*, void*, void*), void* arg)
{
    DecompRequest* req;
    fn_8031D34C(&sFreeQ, (OSMessage*)&req, 1);
    req->src = src;
    req->dst = dst;
    req->callback = callback;
    req->arg = arg;
    fn_8031D284(&sReqQ, req, 1);
}

/* decompression thread main loop */
void fn_8017FC60(void)
{
    DecompRequest* req;
    for (;;) {
        req = NULL;
        fn_8031D34C(&sReqQ, (OSMessage*)&req, 1);
        fn_8017F4C8(req->src, req->dst);
        if (req->callback != NULL) {
            req->callback(req->arg, req->src, req->dst);
        }
        fn_8031D284(&sFreeQ, req, 1);
    }
}



extern DecompRequest* lbl_804CB8F0; /* request pool */
extern OSMessage* lbl_804CB8F4;     /* requestQ buffer */
extern OSMessage* lbl_804CB8F8;     /* freeQ buffer */

extern void* fn_80079940(u32 size, u32 align); /* alloc */
extern void fn_8031D224(OSMessageQueue* q, OSMessage* buf, int count); /* OSInitMessageQueue */
extern int fn_8031FC48(OSThread* t, void (*func)(void), void* param, void* stack, u32 stackSize, int prio, u16 attr); /* OSCreateThread */
extern int fn_803202B0(OSThread* t); /* OSResumeThread */

/* init background decompression thread */
void fn_8017FCE0(void)
{
    int i;
    lbl_804CB8F0 = (DecompRequest*)fn_80079940(0x1000, 0x40);
    lbl_804CB8F4 = (OSMessage*)fn_80079940(0x400, 0x40);
    lbl_804CB8F8 = (OSMessage*)fn_80079940(0x400, 0x40);
    fn_8031D224(&sReqQ, lbl_804CB8F4, 0x100);
    fn_8031D224(&sFreeQ, lbl_804CB8F8, 0x100);
    for (i = 0; i < 0x100; i++) {
        fn_8031D284(&sFreeQ, &lbl_804CB8F0[i], 1);
    }
    fn_8031FC48(&sThread, fn_8017FC60, NULL, sStack + sizeof(sStack), 0x4000, 0x10, 1);
    fn_803202B0(&sThread);
}

}
