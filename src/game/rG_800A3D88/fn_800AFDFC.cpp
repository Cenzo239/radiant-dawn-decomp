#include "game/rG_800A3D88/types.h"

// Footstep effect: spawns pooled models when the tracked bone touches the ground.
extern "C" {
typedef f32 Mt[3][4];
struct Vec { f32 x, y, z; };
struct W3 { u32 a, b, c; };
struct MdlF { u32 flags; };
struct PNode { PNode* next; PNode* prev; MdlF m; };
struct Pool { u8 p[8]; PNode** sp; PNode* head; PNode* tail; int count; };
struct ChrU { u8 p[0x30]; void* mdl; u8 p34[0x50 - 0x34]; u32 m50; u8 p54[0x58 - 0x54]; s16 m58; };
struct Ct { u8 p[0xE]; u8 me; };
struct Eo { u8 p[0x30]; Ct* m30; };
struct Fx {
    u8 p[0x30];
    void* m30;
    ChrU* m34;
    u8 p38[4];
    u8 m3c;
    u8 p3d[3];
    f32 m40, m44, m48, m4c;
    u16 m50, m52;
    u8 p54[2];
    s16 m56;
    Pool* m58;
};
extern char lbl_803657E8[];
#define STR(n) (lbl_803657E8 + (n))
int fn_800B4000(ChrU*, int, Vec*, int, int);
void* fn_800AABB4(void*);
void* fn_800A6578(void*, int);
Eo* fn_800E3810(void*, Fx*);
void fn_800E48C8(Eo*, Vec*);
f32 fn_8001E064(int);
void fn_800E49AC(Eo*, f32);
int fn_800AAC3C(void*);
int fn_80007630(void*, const char*);
void fn_803128AC(Mt, f32, f32, f32);
u32 fn_80089ED0();
void fn_80312654(Mt, int, f32);
void fn_80312378(const void*, const void*, void*);
void fn_8000866C(MdlF*, f32);
void fn_800081C4(MdlF*, Mt);
void fn_800081D4(MdlF*);
void fn_80007E90(MdlF*);
static inline int Node(ChrU* c, const char* const& n) {
    int k;
    if (c->mdl == NULL) k = -1;
    else { int t = fn_80007630(c->mdl, n); k = t; }
    return k;
}
static inline PNode* Alloc(Pool* l) {
    PNode* n = *l->sp;
    if (n == NULL) return NULL;
    n->prev = l->tail;
    n->next = NULL;
    if (l->tail != NULL) l->tail->next = n;
    if (l->head == NULL) l->head = n;
    l->tail = n;
    l->sp++;
    l->count++;
    return n;
}
static inline void Free(Pool* l, PNode* n) {
    if (n == NULL) return;
    if (n->next != NULL) n->next->prev = n->prev;
    if (n->prev != NULL) n->prev->next = n->next;
    if (n == l->head) l->head = n->next;
    if (n == l->tail) l->tail = n->prev;
    *--l->sp = n;
    l->count--;
}
void fn_800AFDFC(Fx* f) {
    Mt mb0, m80, m50;
    Vec p, v38, v2c, a20, v14, v8;
MdlF* m;
Eo* o;
ChrU* c2;
PNode* n;
MdlF* m2;
    if (f->m30 == NULL) return;
    ChrU* c = f->m34;
    if (c == NULL) return;
    if (!(c->m50 & 0x8000) && fn_800B4000(c, f->m56, &p, -1, 0)) {
        if (p.y >= f->m48 + f->m4c && p.y > f->m40) f->m40 = p.y;
        if (p.y <= f->m44 + f->m4c && f->m44 < f->m40) {
            *(W3*)&v38 = *(W3*)&p;
            void* q = fn_800A6578(fn_800AABB4(f->m30), 0);
            if (q != NULL) {
                o = fn_800E3810(q, f);
                if (o != NULL) {
                    v38.y = f->m4c;
                    *(W3*)&a20 = *(W3*)&v38;
                    fn_800E48C8(o, &a20);
                    fn_800E49AC(o, fn_8001E064(f->m34->m58));
                    o->m30->me = 3;
                }
            }
            f->m40 = 0.0f;
        }
        if (fn_800AAC3C(f->m30)) {
            if (p.y < f->m4c) {
                if (f->m50 % f->m52 == 0) {
                    Pool* l = f->m58;
                    *(W3*)&v2c = *(W3*)&p;
                    if (l != NULL) {
                        PNode* e = Alloc(l);
                        if (e != NULL) {
                            m = &e->m;
                            v2c.y = f->m4c;
                            if (f->m3c == 3) {
                                c2 = f->m34;
                                *(u32*)&v14.x = 0;
                                *(u32*)&v14.y = 0;
                                *(u32*)&v14.z = 0;
                                fn_800B4000(c2, Node(c2, STR(0x26)), &v14, -1, 0);
                                *(W3*)&v8 = *(W3*)&v14;
                                v2c.x = 0.5f * (v2c.x + v8.x);
                                v2c.z = 0.5f * (v2c.z + v8.z);
                            }
                            fn_803128AC(m50, v2c.x, v2c.y, v2c.z);
                            fn_80312654(m80, 0x79, 0.017453292f * (f32)(fn_80089ED0() % 360));
                            fn_80312378(m50, m80, mb0);
                            fn_8000866C(m, 0.0f);
                            fn_800081C4(m, mb0);
                        }
                    }
                }
                f->m50++;
            } else {
                f->m50 = 0;
            }
        }
    }
    if (f->m58 != NULL) {
        n = NULL;
        goto L;
        do {
            m2 = &n->m;
            fn_800081D4(m2);
            fn_80007E90(m2);
            if (m2->flags & 2) Free(f->m58, n);
L:          Pool* pp = f->m58;
            if (n == NULL) n = pp->head; else n = n->next;
        } while (n != NULL);
    }
}
}
