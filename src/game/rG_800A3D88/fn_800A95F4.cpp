#include "game/rG_800A3D88/types.h"

// Battle scene setup once the models are ready.
extern "C" {
struct Ev { u8 p[0x32]; u8 m32; u8 p33[0x54 - 0x33]; struct Res* m54; };
struct Res { u8 m8pad[8]; u8 m8; u8 m9; };
struct ChI { u8 p[0x50]; u32 m50; u8 p54[0x78 - 0x54]; void* m78; void* m7c; ChI* m80; };
struct Bat {
    u8 p[0x30];
    Ev* m30;
    void* m34;
    void* m38;
    ChI* e[2];
    struct { u8 p[0x80]; void* m80; }* m44;
};
extern char lbl_803653B8[];
void fn_800AABEC(Ev*);
void fn_800AEC54(void*);
void fn_800AEC70(void*);
int fn_800BD280(ChI*);
void fn_800B29D0(ChI*);
void fn_800B2810(ChI*, int, f32);
void fn_8027DF74(void*, f32, f32, f32);
f32 fn_800A84A4(const char*);
void fn_800B2994(ChI*, f32);
void fn_800AAB94(Ev*, f32);
#if TARGET_PC
FE10_PROTO ptr32<void> fn_800A7460(void*, const char*);
#else
void* fn_800A7460(void*, const char*);
#endif
void fn_800AA848(Ev*, ChI*);
static inline ChI* At(Bat* b, int i) { if (i < 0) return NULL; return b->e[i]; }
#define ADV(q) (q = (Bat*)((u8*)q + 4))
static inline ChI* At2(Bat* q, int i) { if (i < 0) return NULL; return q->e[0]; }
void fn_800A95F4(Bat* b) {
/*P*/
ChI* a;
int i;
Bat* q;
u8 m;
void* w;
ChI* o;
/*E*/
    fn_800AABEC(b->m30);
    fn_800AEC54(b->m34);
    fn_800AEC70(b->m38);
    int m2 = b->m30->m32;
    m = m2;
    for (q = b, i = 0; i < 2; i++, ADV(q)) {
        a = At2(q, i);
        o = At(b, 1 - i);
        if (!fn_800BD280(a) || !fn_800BD280(o)) o = NULL;
        fn_800B29D0(a);
        fn_800B2810(a, m, 0.0f);
        a->m80 = o;
    }
    w = b->m44->m80;
    if (w != NULL) fn_8027DF74(w, 0.0f, 0.0f, 0.0f);
    Res* r = b->m30->m54;
    if (r != NULL) {
        f32 t = (int)r->m9;
        if (0.0f == t) t = fn_800A84A4(lbl_803653B8 + 0xB);
        switch (b->m30->m32) {
        case 2:
        case 3:
            for (q = b, i = 0; i < 2; i++, ADV(q)) {
                if (fn_800BD280(At2(q, i))) fn_800B2994(At2(q, i), t);
            }
            fn_800AAB94(b->m30, t);
            if (w != NULL) fn_8027DF74(w, 0.0f, t, 0.0f);
            break;
        }
        for (q = b, i = 0; i < 2; i++, ADV(q)) {
            if (fn_800BD280(At2(q, i))) {
                if (r->m8 & 1) At2(q, i)->m50 |= 0x2000;
                else At2(q, i)->m50 &= ~0x2000;
                if (fn_800A7460(At2(q, i)->m78, lbl_803653B8 + 0x14)) fn_800AA848(b->m30, At2(q, i));
            }
        }
    }
}
}
