#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/rlist.h"
#pragma auto_inline off
#pragma use_lmw_stmw on
extern "C" {
struct Eq { int pad; const u32* v; Eq(const u32& h) { v = &h; } };
struct LN3 { LN3* prev; LN3* next; u32 val; };
struct L3 { int size; LN3* prev; LN3* next; };
static inline LN3* erase3(L3* l, LN3* it, LN3* j) {
    if (it == j) return j;
    LN3* last = j->prev;
    it->prev->next = last->next;
    last->next->prev = it->prev;
    while (it != j) {
        LN3* t = it;
        it = it->next;
        fn_80079210(t);
        l->size--;
    }
    return j;
}
void fn_80224BCC(L3* l, Eq e) {
    LN3* end = (LN3*)&l->prev;
    LN3* it = l->next;
    while (it != end) {
        if (it->val == *e.v) {
            LN3* j = it->next;
            while (j != end) {
                if (j->val != *e.v) break;
                j = j->next;
            }
            it = erase3(l, it, j);
            if (it == end) break;
        }
        it = it->next;
    }
}
struct M1 { u8 p[0x56]; s16 x56; u8 p58[0x1c]; L3 list; };
void fn_802237FC(M1* o, u32 v) {
    fn_80224BCC(&o->list, Eq(v));
    if ((u32)o->x56 >= o->list.size) {
        o->x56 = o->list.size != 0 ? o->list.size - 1 : 0;
    }
}
extern char lbl_803CA870[];
extern char lbl_8036F03C[];
extern char lbl_804CA990[8];
void* fn_801E5640(void*, int, int);
void fn_800893AC(void*);
void fn_800D56E8(void*);
void fn_80083174(void*);
#if TARGET_PC
FE10_PROTO void fn_801E5734(void*, p32arg);
#else
void fn_801E5734(void*, int);
#endif
void fn_80102C6C(void*, void*, int, int, int);
#if TARGET_PC
FE10_PROTO void fn_801EA538(void*, p32arg);
#else
void fn_801EA538(void*, int);
#endif
struct F2 { u8 p[0x40]; int x40; };
struct F1 { u8 p[0x40]; int x40; F2* x44; u8 p48[0x14]; u8* x5c; };
void fn_801FAF74(F1* o) {
    
    u8* m;
    char* s;
    int v;

    m = o->x5c;
    fn_800893AC(m);
    v = *(s8*)(m + 0xa6);
    fn_800D56E8(m);
    m[0xa6] = v;
    fn_80083174(o->x5c);
    fn_801E5734(o, o->x40);
    s = lbl_8036F03C + 0x4b;
    u8* t = (u8*)fn_801E5640(o, -0x1000, 0);
    if (t != NULL) *(char**)(t + 0x64) = s;
    if (*(void**)lbl_803CA870 != NULL) fn_80102C6C(*(void**)lbl_803CA870, lbl_804CA990, 4, 0, 0);
    if (o->x44 != NULL && o->x44->x40 != NULL) fn_801EA538(o->x44, o->x44->x40);
}
}
