/* New-game setup. The two flag lookups differ only in that the second goes through a by-value wrapper (c1): this orders its string and index registers. */
/* New-game and new-chapter setup of the global game data. Bits at +0x544 are looked up by name through a
 * hashed string table (names at +0x144, hashes at +0x344). */
#include "game/rC2_8005259C/base.h"
struct Ver { u8 pad[0x40]; u32 w40; };
struct Big { u8 pad[0x1d428]; f32 lim; };
struct GD {
    u8 p0[0x10];
    u8 b10, b11;
    u16 h12;
    u8 c14[4];
    u8 p18[0x18];
    u8 a30[0x24];
    u8 a54[0x3c];
    u8 b90, b91, b92;
    u8 p93[0xb];
    u8 b9e;
    u8 p9f[0x1b];
    u16 hba;
    u8 pbc[4];
    u16 hc0, hc2, hc4, hc6;
    u8 pc8[0x6c];
    u8 a134[8];
    u8 a13c[8];
    const char* names[0x80];
    u32 hash[0x80];
    u8 bits[0x10];
    u8 p554[0x3e0];
    f32 x934, y938, x93c, y940, x944, y948, z94c;
};
extern "C" {
extern char lbl_803620E4[0x60];
extern u8 lbl_803C8E80[];
extern u8 lbl_803E9288[];
extern u8 lbl_803CB770[];
extern Big lbl_803EC898;
void* fn_8010B094(int);
u8 fn_80092E10(void*);
const char* fn_80092D04(void*, int);
#if TARGET_PC
FE10_PROTO ptr32<const char> fn_80092D88(void*, int);
#else
const char* fn_80092D88(void*, int);
#endif
void fn_802910CC(void*, const char*, int);
void fn_8010E7F4(void*, int);
void fn_800615DC(GD*, int);
void fn_80061808(GD*, f32);
void fn_80063C30(void*);
u32 fn_80076D18(const char*);
int fn_80291188(const char*, const char*);
void fn_8002697C(void*);
void fn_8012CBF0(void);
void* fn_801059B0(void);
void fn_80105704(void*);
void* memset(void*, int, u32);
void fn_800660C4(void*);
Ver* fn_8024BCA0(void);
void* fn_800C3558(void);
void fn_801D0C88(void*, const char*);
int fn_801D0E68(void*, const char*);
f32 fn_801142F0(Big*, f32, f32);
}
static inline int flagFind(GD* t, const char* const& name) {
    u32 h = fn_80076D18(name);
    int i;
    for (i = 0; i < 0x80; i++) {
        if (h == t->hash[i] && fn_80291188(t->names[i], name) == 0) {
            return i;
        }
    }
    return -1;
}
static inline void clearBit(GD* g, int i) {
    if (i >= 0 && i < 0x80) {
        if (i >= 0) {
            if (i >= 0 && i < 0x80) {
                g->bits[i >> 3] &= ~(1 << (i & 7));
            }
        }
    }
}

static inline void c1(GD* g, const char* s) { clearBit(g, flagFind(g, s)); }
static inline bool hasCur(void) { return fn_801059B0() != 0; }

extern "C" void fn_800610F4(GD* g) {
    int o = 1;
    int z = 0;
    g->b10 = z;
    g->h12 = o;
    g->b11 = z;
    g->b90 = z;
    g->b92 = fn_80092E10(fn_8010B094(0));
    g->c14[0] = o;
    g->c14[1] = 2;
    g->c14[2] = 2;
    g->c14[3] = 2;
    g->a30[0] = z;
    g->a30[0xc] = z;
    g->a30[0x18] = z;
    g->a54[0] = z;
    g->a54[0xc] = z;
    g->a54[0x18] = z;
    g->a54[0x24] = z;
    g->a54[0x30] = z;
    fn_8010E7F4(g->a134, 0);
    fn_8010E7F4(g->a13c, 3);
    fn_800615DC(g, 0x3e8);
    fn_80061808(g, 1000.0f);
    fn_80063C30(g->names);
    clearBit(g, flagFind(g, lbl_803620E4 + 0x20));
    c1(g, lbl_803620E4 + 0x2c);
    fn_8002697C(lbl_803C8E80);
    fn_8012CBF0();
    if (hasCur()) {
        fn_80105704(fn_801059B0());
    }
    memset(lbl_803E9288, 0, 0xc);
    fn_800660C4(lbl_803CB770);
}
