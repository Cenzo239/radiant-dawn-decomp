#include "game/rP_80105B04/rp.h"
/* Small item and slot accessors, a weapon-triangle table load and lookup. */
struct IF { u8 pad[5]; u8 b80 : 1; u8 b40 : 1; u8 b20 : 1; u8 b10 : 1; u8 lo : 4; };
struct ItemF {
    u8 pad0[0x12];
    u8 x12;
    u8 pad13[0x20 - 0x13];
    u8 x20, x21;
    u8 pad22[0x38 - 0x22];
    u64 flags;
};
struct Tri { u8 a, b; s8 c, d; };
extern "C" {
extern char lbl_803680E8[];
extern Tri lbl_803EC3AC[9][3];
extern char lbl_80368054[];
u8* fn_80077064(const char* s);
char* fn_800D0864(const char* s);
u32 fn_80109A50(u8** s);
u32 fn_80109A88(u8** s);
u8 fn_80109A18(u8** s);
#if TARGET_PC
u8 fn_8010F73C(p32arg s); /* host: s is a 32-bit window offset */
#else
u8 fn_8010F73C(u32 s);
#endif
int fn_80077BE0();
int fn_800CA3DC(const char* s, int n, f32 k);
char* fn_802910CC(char* a, const char* b, int n);
int fn_80290D04(char* a, int n, const char* f, ...);
void* fn_8024BC94();

static inline u16 B20(IF* s) { return s->b20; }
int fn_80108660(IF* s) {
    return B20(s) != 0;
}
void fn_8010F598(volatile u8* p) {
    if (*p & 0x80) *p |= 3;
}
struct NameO { u8 pad[8]; char* id; };
char* fn_8010F628(NameO* o) {
    if (o->id == 0) return lbl_803680E8 + 0x2B;
    return fn_800D0864(o->id);
}
BOOL fn_80110744(ItemF* it) {
    return (it->flags & 0x10B2ULL) != 0;
}
u8 fn_801107A0(ItemF* it) {
    u8 r = it->x20;
    switch (it->x12) {
    case 0xB:
        r = 1;
        break;
    }
    return r;
}
u8 fn_801108D8(ItemF* it) {
    u8 r = it->x21;
    switch (it->x12) {
    case 0xB:
        r = 1;
        break;
    }
    return r;
}
void fn_80112980() {
    u8* s = fn_80077064(lbl_803680E8 + 0x667);
    int n = fn_80109A50(&s);
    Tri* t = &lbl_803EC3AC[0][0];
    int i;
    for (i = 0; i < n; i++) {
        t->a = fn_8010F73C(fn_80109A88(&s));
        t->b = fn_8010F73C(fn_80109A88(&s));
        t->c = fn_80109A18(&s);
        t->d = fn_80109A18(&s);
#if TARGET_PC
        s = (u8*)((FE10_PTRINT(s) + 3) & ~3);
#else
        s = (u8*)(((u32)s + 3) & ~3);
#endif
        t++;
    }
}
void fn_80112A3C(u32 a, u32 b, s16* c, s16* d) {
    int i, j;
    Tri* t;
    *d = 0;
    *c = 0;
    switch (a) {
    case 6:
    case 7:
    case 8:
        switch (b) {
        case 9:
        case 10:
            a = 0x11;
            break;
        }
        break;
    case 9:
    case 10:
        switch (b) {
        case 6:
        case 7:
        case 8:
            b = 0x11;
            break;
        }
        break;
    }
    t = &lbl_803EC3AC[0][0];
    for (i = 0; i < 9; i++) {
        if (t->a == a) {
            for (j = 0; j < 3; j++) {
                if (t->b == b) {
                    *c = t->c;
                    *d = t->d;
                    return;
                }
                t++;
            }
            return;
        }
        t += 3;
    }
}
int fn_80111488(int v) {
    s16 k;
    if (v >= 0x14B) k = 0x14B;
    else if (v >= 0xFB) k = 0xFB;
    else if (v >= 0xB5) k = 0xB5;
    else if (v >= 0x79) k = 0x79;
    else if (v >= 0x47) k = 0x47;
    else if (v >= 0x1F) k = 0x1F;
    else k = v >= 1;
    switch (k) {
    case 0: return 0;
    case 1: return 0x1F;
    case 0x1F: return 0x47;
    case 0x47: return 0x79;
    case 0x79: return 0xB5;
    case 0xB5: return 0xFB;
    case 0xFB: return 0x14B;
    case 0x14B: return 0x14B;
    default: return 0;
    }
}
void fn_80111FE4(char* p, const char* name);
}
