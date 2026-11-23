#include "game/rA_800068A0/types.h"
/* GActor frame step: advances the animation, collects key events and handles looping. */
extern "C" {
typedef struct GKey { u16 id; s16 val; } GKey;
typedef struct GAnim { u8 x0[0x10]; int loop; int start; int end; } GAnim;
typedef struct GActor {
    u32 flags;
    struct GActor* parent;
    u8 x8[0x44 - 8];
    GAnim* anim;
    u8 x48[0x54 - 0x48];
    void* x54;
    f32 frame;
    f32 speed;
    u8 x60[0x74 - 0x60];
    struct GActor* child;
    u8 x78[0x8C - 0x78];
    GKey keys[4];
} GActor;
extern f32 lbl_804CA040;
extern int fn_80009EF8(GAnim* a, int frame, int id);
extern int fn_8000A22C(f32 a, f32 b, GAnim* an, GKey* out);
extern void fn_8000A460(GKey* a, GKey* b, GKey* c);
static inline f32 getDt(void) { return lbl_804CA040; }
static inline BOOL hasKey(GActor* a, u16 id) {
    GKey* k = a->keys;
    int i;
    for (i = 0; i < 4; i++, k++) {
        if (k->id == id) return TRUE;
    }
    return FALSE;
}
static inline GAnim* findAnim(GActor* a) {
    GActor* p;
    for (p = a; p != 0; p = p->parent) {
        if (p->anim != 0) return p->anim;
    }
    return 0;
}
extern void fn_800156C8(GActor*);
void fn_800081D4(GActor* a) {
    GKey ev[4];
    f32 d = a->speed * getDt();
    f32 from, to;
    GAnim* an = findAnim(a);
    if (an == 0) return;
    u32 fl = a->flags;
    a->flags = fl & ~2;
    if (fl & 4) return;
    if (a->child != 0 && !(a->flags & 0x100000)) {
        fn_800081D4(a->child);
    }
    from = a->frame;
    to = from + d;
    a->frame = to;
    if (a->flags & 8) {
        if (hasKey(a, 4)) {
            if (hasKey(a, 3)) {
                a->frame = from;
                to = from;
                from -= d;
            } else {
                from = (f32)fn_80009EF8(findAnim(a), (int)to, 3);
                to = from + d;
                a->frame = to;
            }
        }
    }
    fn_8000A22C(from, to, an, a->keys);
    int e = an->end;
    if (a->frame >= (f32)e || a->frame <= (f32)an->start) {
        BOOL lp = FALSE;
        switch (a->flags & 0x30) {
        case 0x10:
            lp = TRUE;
            break;
        case 0x20:
            lp = FALSE;
            break;
        default:
            if (an->loop != 0) lp = TRUE;
            break;
        }
        if ((a->flags & 8) && hasKey(a, 4)) {
            lp = FALSE;
        }
        if (lp) {
            f32 f = a->frame;
            if (f >= (f32)e) {
                to = f - (f32)(e - an->start);
                a->frame = to;
                from = (f32)(an->start - 1);
            } else {
                int s = an->start;
                if (f <= (f32)s) {
                    f32 g = f + (f32)(e - s);
                    a->frame = g;
                    from = g - 1.0f;
                    to = (f32)an->end;
                }
            }
            if (fn_8000A22C(from, to, an, ev) > 0) {
                fn_8000A460(a->keys, ev, a->keys);
            }
        } else {
            if (a->frame >= (f32)e) {
                a->frame = (f32)e;
            } else {
                int s = an->start;
                if (a->frame <= (f32)s) {
                    a->frame = (f32)s;
                }
            }
        }
        a->flags |= 2;
    }
    if (a->x54 != 0) {
        fn_800156C8(a);
    }
}
}
