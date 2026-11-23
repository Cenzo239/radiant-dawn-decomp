#include "game/rB_8002E1C4/types.h"

/* On-screen notice frame (class lbl_803794D0). */
struct Notice {
    u8 pad[0x30];
    f32 x30;
    f32 x34;
    s16 x38;
    s8 alpha;
    u8 pad3b[2];
    s8 slot;
    char text[0x30];
    u8 pad6e;
};
extern u8 lbl_803794D0[];
extern const f32 lbl_804CCD58;
extern const f32 lbl_804CCD24;
extern const f32 lbl_804CCCF4;
extern const f32 lbl_804CCD48;
extern const f32 lbl_804CCD4C;

extern const f32 lbl_804CCD28; /* 1.0f */
extern u8 lbl_804CB184[4];
extern "C" {
#if TARGET_PC
FE10_PROTO Notice* fn_80081050(void* cls, p32arg);
#else
Notice* fn_80081050(void* cls, int k);
#endif
const char* fn_800D0864(const char* key);
char* fn_802910CC(char* d, const char* s, int n);
int fn_800CA3DC(const char* s, int n, f32 a);
void fn_80081A90(Notice* n);

void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E174(void* t, int a);
void fn_8007E4E4(f32 x, f32 y, f32 z, f32 w);
void fn_8007E720(f32 a);
void fn_80072EE0(int a, int b, int c);
f32 fn_8017F68C(int k, f32 a, f32 b, f32 t, f32 d);
void fn_800CB3A8(f32 a, f32 b, s16 x, s16 y, int c, int d, int e, const char* fmt, ...);
u32 fn_800C7FE8(void);

void fn_80039060(Notice* n) {
    f32 x = fn_8017F68C(6, n->x30, n->x34, n->alpha, lbl_804CCD48);
    fn_8007E154();
    fn_8007E4E4(lbl_804CCD4C, x, lbl_804CCCF4, lbl_804CCD28);
    fn_8007E164();
    fn_80072EE0(0, 0, n->x38);
    fn_8007E154();
    fn_8007E174(0, 0x13);
    fn_8007E720(lbl_804CCD24);
    fn_8007E164();
    fn_800CB3A8(lbl_804CCD28, lbl_804CCCF4, 0x30, 0xe, 1, 1, 0, n->text);
    {
    u32 k = fn_800C7FE8();
    if ((k & 0xc) && (k & 2)) fn_80081A90(n);
    }
}

void fn_800391E0(const char* key) {
    Notice* n = (Notice*)fn_80081050(lbl_803794D0, 3);
    fn_802910CC(n->text, fn_800D0864(key), 0x2f);
    n->text[0x30] = 0;
    n->x38 = fn_800CA3DC(n->text, -1, lbl_804CCD28) + 0x60;
    const f32 ys[4] = {375.0f, 325.0f, 275.0f, 225.0f};
    for (n->slot = 0; n->slot < 4; n->slot++) {
        if (lbl_804CB184[n->slot] == 0) {
            lbl_804CB184[n->slot] = 1;
            break;
        }
    }
    if (n->slot == 4) {
        fn_80081A90(n);
    } else {
        n->x30 = lbl_804CCD58;
        n->x34 = ys[n->slot];
    }
}
}
