/* Archive/file entry manager: file statics at lbl_80425478 (two entry lists, a lock object, queues, loader thread). */
#include "game/rI_801DD7D4/fn_thp.h"
#include "game/rI_801DD7D4/vobj.h"
#pragma auto_inline off

struct FE {
    void* vt;
    int a4;
    int a8;
    char name[0x3F];
    u8 a4b;
    u32 hash;
    volatile u32 flags;
    u16 rc;
    u8 a56;
    u8 p57;
    u32 a58;
    FE* parent;
    u32 data;
    u32 size;
    u32 pos;
};
struct Ent { int a0; char* name; u32 data; u32 size; };
struct Hdr { int a0; u16 count; u16 a6; Ent ent[1]; };
struct Lmsg { u8 kind; u8 p[3]; int a4; int a8; };

extern "C" {
static u8 sA[0xC];
static u8 sB[0xC];
static u8 sPad[0xC];
static u8 sLock[0x1C];
static u8 sQ1[0x20];
static u8 sQ2[0x20];
static u8 sThread[0x318];
static u8 sStack[0x2000];
extern u8 lbl_804CBF98;
extern void* lbl_804CBF9C;
extern void* lbl_804CBFA0;
extern void* lbl_804CBFA4;
void fn_80238FB8(void*);

void fn_802383F4(void) {
    int off;
    int i;
    if (lbl_804CBF98 == 0) {
        lbl_804CBF9C = fn_80079940(0xc00, 0x40);
        lbl_804CBFA0 = fn_80079940(0x400, 0x40);
        lbl_804CBFA4 = fn_80079940(0x400, 0x40);
        fn_8031D224(sQ1, lbl_804CBFA0, 0x100);
        fn_8031D224(sQ2, lbl_804CBFA4, 0x100);
        for (i = 0, off = 0; i < 0x100; i++, off += 0xc) {
            fn_8031D284(sQ2, (u8*)lbl_804CBF9C + off, 1);
        }
#if TARGET_PC
        fn_8031FC48(sThread, (void*)fn_80238FB8, 0, sStack + 0x2000, 0x2000, 0x10, 1);
#else
        fn_8031FC48(sThread, fn_80238FB8, 0, sStack + 0x2000, 0x2000, 0x10, 1);
#endif
        fn_803202B0(sThread);
        lbl_804CBF98 = 1;
    }
}

struct Loc { u8 p[8]; u16* cls; u8 pc[4]; u8* lower; };
struct LocS { u8 p[0x38]; Loc* c; };
extern LocS lbl_80393728;
static inline int bad(int c) {
    return c < 0 || c >= 0x100;
}
static inline int up(int c) {
    return bad(c) ? 0 : lbl_80393728.c->cls[c] & 0x200;
}
static inline int low(int c) {
    return bad(c) ? c : lbl_80393728.c->lower[c];
}
/* normalise a path: strip a leading slash, lower-case it, map \ to /, and hash it */
void fn_8023B5B0(FE* e, const char* s) {
    char* d;
    int i;
    if (*s == '/' || *s == '\\') s++;
    e->hash = 0;
    d = e->name;
    for (i = 0; *s != 0 && i < 0x3e; i++, s++, d++) {
        if (up(*s)) {
            *d = low(*s);
        } else if (*s == '\\') {
            *d = '/';
        } else {
            *d = *s;
        }
        e->hash = *d + e->hash * 0x25;
    }
    *d = 0;
}

static inline u32 flg(FE* e, u32 m) { return e->flags & m; }
u64 fn_8028C418(u64, u64);
char* strcpy(char*, const char*);
char* fn_80291314(const char*, int);
FE* fn_8023D9B8(void);
u64 OSGetTime(void);
void fn_802BC1C8(void*, FE*);
#pragma push
#pragma use_lmw_stmw on
void fn_8023B6C4(FE* e) {
    char buf[0x80];
    if (!flg(e, 0x08000000)) return;
    if (flg(e, 0x04000000)) {
        if (!flg(e, 0x00100000)) return;
    }
    if (flg(e, 0x00800000)) return;
    {
        Hdr* h = (Hdr*)e->data;
        Ent* n = h->ent;
        int i;
        for (i = 0; i < h->count; i++, n++) {
            FE* c;
            char* p;
            n->name = (char*)((u32)n->name + (u32)h);
            n->data = n->data + (u32)h;
            strcpy(buf, e->name);
            p = fn_80291314(buf, '/');
            if (p != NULL) {
                strcpy(p + 1, n->name);
            } else {
                strcpy(buf, n->name);
            }
            c = fn_8023D9B8();
            fn_8023B5B0(c, buf);
            {
                u32 f = e->flags;
                c->flags = 0;
                {
                    u32 t = c->flags | (f & 0xE3D8F1AF);
                    t |= 0x10200000;
                    c->flags = t;
                }
            }
            c->a4b = e->a4b;
            c->parent = e;
            c->data = n->data;
            c->size = n->size;
            c->pos = n->size;
            c->a58 = fn_8028C418(OSGetTime(), *(u32*)0x800000F8 >> 2);
            if ((c->data & 0xF0000000) != 0x90000000) {
                ((VO0N*)sLock)->v08();
                fn_802BC1C8(sA, c);
                ((VO0N*)sLock)->v10();
            } else {
                ((VO0N*)sLock)->v08();
                fn_802BC1C8(sB, c);
                ((VO0N*)sLock)->v10();
            }
        }
    }
}
#pragma pop
void fn_8023BE08(int, int b, int, int a) {
    Lmsg* m;
    fn_8031D34C(sQ2, &m, 1);
    m->kind = 1;
    m->a4 = a;
    m->a8 = b;
    fn_8031D284(sQ1, m, 1);
}
void fn_8023BE80(int, int b, int, int a) {
    Lmsg* m;
    fn_8031D34C(sQ2, &m, 1);
    m->kind = 2;
    m->a4 = a;
    m->a8 = b;
    fn_8031D284(sQ1, m, 1);
}
extern u8 lbl_80390C58[];
void fn_80079210(void*);
#if TARGET_PC
FE10_PROTO FE* fn_8023DCC0(p32arg);
#else
FE* fn_8023DCC0(u32);
#endif
int fn_8023F8B8(u32 k) {
    FE* e = fn_8023DCC0(k);
    if (e == NULL) return -1;
    return e->rc;
}
extern s8 lbl_804CAA9C;
int fn_8023FBF4(void) { return lbl_804CAA9C; }
struct Guard {
    VO0N* m;
    Guard(VO0N* l) : m(l) { m->v08(); }
    ~Guard() { m->v10(); }
};
FE* fn_802BC2A4(void*, FE*);
#pragma push
#pragma use_lmw_stmw on
#define FINDD(d, l, k, r) { \
    FE* p; \
    k->v08(); \
    l = sB; \
    if ((d & 0xF0000000) != 0x90000000) l = sA; \
    for (p = fn_802BC2A4(l, NULL); p != NULL; p = fn_802BC2A4(l, p)) { \
        if (p->data == d) { r = p; break; } \
    } \
    k->v10(); \
}
char* fn_8023F92C(u32 d) {
    void* l;
    VO0N* k = (VO0N*)sLock;
    FE* r = NULL;
    FINDD(d, l, k, r)
    if (r != NULL) return r->name;
    return NULL;
}
u32 fn_8023FB24(u32 d) {
    FE* r = NULL;
    VO0N* k = (VO0N*)sLock;
    void* l;
    FINDD(d, l, k, r)
    if (r == NULL) return 0;
    return r->size;
}
#pragma pop
void fn_802FAB20(int);
int fn_8030EC9C(int, int, int);
void* fn_8030EA0C(void*, int, int, int, int);
void* fn_8030ECD8(void*, u32);
void* fn_8030E294(void*, u32, int);
void fn_802BC1B0(void*, int);
void fn_8023825C(u32);
extern void* lbl_804CBF94;
extern void* lbl_804CBF90;
extern u8 lbl_8041F080[];
void fn_8023F0C8(u32 mem2) {
    int n;
    fn_802FAB20(1);
    n = fn_8030EC9C(0xa8, 0x400, 4);
    lbl_804CBF94 = fn_8030EA0C(fn_80079940(n, 0x40), n, 0xa8, 4, 4);
    n = mem2 & ~0x1f;
    if (n != 0) {
        lbl_804CBF90 = fn_8030E294(fn_8030ECD8(lbl_8041F080, n), n, 4);
    }
    fn_802BC1B0(sA, 4);
    fn_802BC1B0(sB, 4);
    fn_802BC1B0(sPad, 4);
    fn_802383F4();
    fn_8023825C(0x100);
}
void fn_802BC238(void*, FE*);
#if TARGET_PC
FE10_PROTO void fn_80075AC0(p32arg);
#else
void fn_80075AC0(u32);
#endif
void fn_8030EC2C(void*, FE*);
class VD { public: virtual void d(int); };
#pragma push
#pragma use_lmw_stmw on
void fn_8023B894(FE* e) {
    u32 d;
    VO0N* k;
    FE* r;
    void* l;
    Hdr* h;
    int i;
    FE* p;
    if (flg(e, 0x04000000)) {
        if (!flg(e, 0x00100000)) return;
    }
    if (flg(e, 0x00800000)) return;
    if (flg(e, 0x08000000)) {
        h = (Hdr*)e->data;
        i = 0;
        if (i < h->count) {
            k = (VO0N*)sLock;
            for (; i < h->count; i++) {
                d = h->ent[0].data;
                r = NULL;
                ((VO0N*)sLock)->v08();
                l = sB;
                if ((d & 0xF0000000) != 0x90000000) l = sA;
                for (p = fn_802BC2A4(l, NULL); p != NULL; p = fn_802BC2A4(l, p)) {
                    if (p->data == d) { r = p; break; }
                }
                k->v10();
                if (r != NULL) fn_8023B894(r);
            }
        }
    } else if (flg(e, 1)) {
        fn_80075AC0(e->data);
        e->flags &= ~1;
    }
}
void fn_8023B9D8(FE* e) {
    u32 d;
    FE* r;
    VO0N* k;
    void* l;
    Hdr* h;
    Ent* n;
    int i;
    FE* p;
    if (flg(e, 0x04000000)) {
        if (!flg(e, 0x00100000)) return;
    }
    if (flg(e, 0x00800000)) return;
    if (flg(e, 0x08000000)) {
        h = (Hdr*)e->data;
        i = 0;
        n = h->ent;
        if (i < h->count) {
            k = (VO0N*)sLock;
            for (; i < h->count; i++, n++) {
                d = n->data;
                r = NULL;
                ((VO0N*)sLock)->v08();
                l = sB;
                if ((d & 0xF0000000) != 0x90000000) l = sA;
                for (p = fn_802BC2A4(l, NULL); p != NULL; p = fn_802BC2A4(l, p)) {
                    if (p->data == d) { r = p; break; }
                }
                k->v10();
                if (r != NULL) {
                    k->v08();
                    if ((r->data & 0xF0000000) != 0x90000000) {
                        fn_802BC238(sA, r);
                    } else {
                        fn_802BC238(sB, r);
                    }
                    k->v10();
                    ((VD*)r)->d(-1);
                    fn_8030EC2C(lbl_804CBF94, r);
                }
            }
        }
    }
}
#pragma pop
}
