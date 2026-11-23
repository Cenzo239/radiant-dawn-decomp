#include "game/rG_800A3D88/types.h"
extern "C" {
struct C4 { u8 r, g, b, a; };
struct Ef2 { u8 p[0x50]; u8 m50; u8 p51[5]; s16 m56; };
struct Eg { u8 p[0x34]; void* m34; void* m38; u8 p3c[4]; Ef2* m40; };
u8 fn_800A6844(void*, int);
#if TARGET_PC
FE10_PROTO Ef2* fn_80179040(void*, ptr32<const void>, int, Eg*);
#else
Ef2* fn_80179040(void*, const char*, int, Eg*);
#endif
void fn_80177FCC(Ef2*, C4*);
void fn_80178048(Ef2*, int);
f32 fn_800A84A4(const char*);
s16 fn_8001E094(f32);
void fn_801780A0(Ef2*, int);
void fn_801780A8(Ef2*, int);
#if TARGET_PC
FE10_PROTO void fn_80177284(ptr32<const void>, Ef2*);
#else
void fn_80177284(void*, Ef2*);
#endif
void fn_800C0A88(void*);
extern char lbl_80365B64[];
extern C4 lbl_804CD4AC;
static inline const char* Nm(Eg* e) {
    if (e->m34 == NULL) return NULL;
    switch (fn_800A6844(e->m38, -1)) {
    case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 10: case 11: case 14: case 15:
        return lbl_80365B64 + 0xB7;
    case 0: case 9: case 12: case 13: return NULL;
    default: return NULL;
    }
}
void fn_800C0BD0(Eg* e, int a) {
    Ef2* q;
    if (e->m40 != NULL) return;
    const char* n = Nm(e);
    if (n != NULL) {
        e->m40 = fn_80179040(e->m34, n, 1, e);
        if (e->m40 != NULL) {
            C4 c = lbl_804CD4AC;
            fn_80177FCC(e->m40, &c);
            fn_80178048(e->m40, 1);
            f32 t = fn_800A84A4(lbl_80365B64 + 0xBA);
            q = e->m40;
            q->m56 = fn_8001E094(t);
            if (a != 0) {
                e->m40->m50 |= 0x20;
            } else {
                fn_801780A0(e->m40, 0x18);
                fn_801780A8(e->m40, 8);
                fn_80177284((void*)fn_800C0A88, e->m40);
            }
        }
    }
}
int fn_80008C98(void*, int);
s16 fn_80008CF0(void*, int);
void fn_801780B0(Ef2*);
struct Eg3 { u8 p[0x34]; void* m34; void* m38; struct { u8 p[0x30]; void* m30; }* m3c; Ef2* m40; };
#define KILL(e) if ((e)->m40 != NULL) { fn_801780B0((e)->m40); (e)->m40 = NULL; }
void fn_800C0D4C(Eg3* e) {
    if (e->m34 == NULL) return;
    void* m = e->m3c->m30;
    if (fn_80008C98(m, 0x50) != 0) {
        switch (fn_800A6844(e->m38, -1)) {
        case 0xF:
            if (fn_80008CF0(m, 0x50) != 0) fn_800C0BD0((Eg*)e, 0);
            break;
        case 10: case 11:
            if (fn_80008CF0(m, 0x50) == 0) fn_800C0BD0((Eg*)e, 0);
            break;
        default:
            fn_800C0BD0((Eg*)e, 0);
            break;
        }
    }
    if (fn_80008C98(m, 0x51) != 0) {
        switch (fn_800A6844(e->m38, -1)) {
        case 0xF:
            if (fn_80008CF0(m, 0x51) != 0) KILL(e);
            break;
        case 10: case 11:
            if (fn_80008CF0(m, 0x51) == 0) KILL(e);
            break;
        default:
            KILL(e);
            break;
        }
    }
}
}
