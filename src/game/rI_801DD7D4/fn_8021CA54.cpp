#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/rlist.h"
#pragma auto_inline off
#pragma use_lmw_stmw on
extern "C" {
void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E720(f32);
void fn_8007E7E8(int);
void fn_8007E7B4(void);
void fn_800712E8(int, int, int);
int fn_8028DB44(int);
void* fn_8010B22C(int);
#if TARGET_PC
FE10_PROTO int fn_80119F24(void*, p32arg);
#else
int fn_80119F24(void*, int);
#endif
extern int lbl_804CB7A8;
struct Ctx { u8 p[0x2d]; u8 x2d, x2e; u8 p2[5]; int x34; struct { u8 p[8]; void* x8; }* x38; };
struct GV { virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18(void*); };
struct C1 { u8 p[0x1e]; s16 x1e, x20; u8 p2[0x3e]; u8 x60; u8 p61[7]; u8 x68; u8 p69; s16 x6a, x6c, x6e; };
struct S8 { void* p; u8 x4; u8 x5; u8 p6[2]; };
struct Bk { u8 p[0x12c]; S8 s[18]; };
struct Ib { u8 p[0x1f]; u8 x1f; };
struct LN2 { LN2* prev; LN2* next; u8* val; };
struct L2 { int size; LN2* prev; LN2* next; };
void fn_8021CA54(C1* o, Ctx* a) {
        int hl;
    int px;
    s16 x;
    s16 y;
    ((GV*)o)->v18(a);
    {
        int m = o->x6a * 0x78;
        px = o->x6c;
        x = o->x1e + m + 0x3c;
        y = o->x20 + 0x96;
    }
    if ((px == -0x8000 && o->x6e == -0x8000) || (fn_8028DB44(px - x) <= 1 && fn_8028DB44(o->x6e - y) <= 1)) {
        o->x6c = x;
        o->x6e = y;
    } else {
        o->x6c = (px + x + 1) >> 1;
        o->x6e = (y + o->x6e + 1) >> 1;
    }
    if (o->x60 == 1 && o->x68) {
        hl = 0;
        int b = 0;
        if (a->x2d || a->x2e) b = 1;
        if (!b) {
            void* t;
            if (a->x34) t = a->x38->x8; else t = 0;
            if (t == o) hl = 1;
        }
        fn_8007E154();
        fn_8007E720(-2.0f);
        fn_8007E164();
        fn_800712E8(o->x6c, o->x6e, hl);
    }
    fn_8007E154();
    fn_8007E7B4();
    fn_8007E7E8(0x80);
    fn_8007E164();
}
int fn_80225C70(Bk* o) {
    u8* b = (u8*)o;
        S8* e;
    int off;
    Ib* it;
    int i;
    i = 0;
    off = 0;
    for (; i < 18; i++) {
        e = (S8*)(b + 0x12c + off);
        if (e && (it = (Ib*)e->p) != 0 && it->x1f && !(e->x5 & 1)) return 1;
        off += 8;
    }
    for (i = 0; i < lbl_804CB7A8; i++) {
        Ib* b = (Ib*)fn_8010B22C(i);
        if (b->x1f && fn_80119F24(b, (int)o)) return 1;
    }
    return 0;
}
void fn_80224AAC(L2* a, L2* b) {
        LN2* ae;
    LN2* ai;
    LN2* bi;
    LN2* be;
    LN2* j;
    LN2* last;
    int n;
    u8 k;
    if (a == b) return;
    ai = a->next;
    ae = (LN2*)&a->prev;
    bi = b->next;
    be = (LN2*)&b->prev;
    while (ai != ae && bi != be) {
        k = ai->val[0x1c];
        if (bi->val[0x1c] < k) {
            j = bi->next;
            n = 1;
            while (j != be) {
                if (j->val[0x1c] >= k) break;
                j = j->next;
                n++;
            }
            last = j->prev;
            bi->prev->next = last->next;
            last->next->prev = bi->prev;
            ai->prev->next = bi;
            bi->prev = ai->prev;
            LN2* nb = j;
            ai->prev = last;
            last->next = ai;
            bi = nb;
            b->size -= n;
            a->size += n;
        }
        ai = ai->next;
    }
    if (bi != be && b->size != 0) {
        LN2* lst;
        LN2* first = b->next;
        LN2* e2 = (LN2*)((u8*)b + 4);
        lst = b->prev;
        b->next = e2;
        b->prev = e2;
        ai->prev->next = first;
        first->prev = ai->prev;
        ai->prev = lst;
        lst->next = ai;
        a->size += b->size;
        b->size = 0;
    }
}
}
