#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/vobj.h"
#include "game/rI_801DD7D4/rlist.h"
#pragma auto_inline off
extern "C" {
void fn_8007E154(void);
void fn_8007E164(void);
#if TARGET_PC
FE10_PROTO void fn_8007E174(p32arg, u16);
#else
void fn_8007E174(int, u16);
#endif
void fn_8007E720(f32);
int fn_800CA3DC(const char*, int, f32);
int fn_800CB0FC(int, f32);
void fn_800CB3A8(s16, s16, int, int, int, const char*, f32, f32, ...);
const char* fn_800D0864(const char*);
void fn_801D820C(s16, s16, int, int, int, int);
void fn_801D855C(s16, s16, s16, int);
extern char lbl_8038F4B0[];
extern char lbl_804CAA18[4];
extern char lbl_804CAA20[7];
extern char lbl_804CAA28[7];
extern char lbl_804CAA30[4];
extern char lbl_804CAA34[7];
extern char lbl_804CAA3C[7];
extern char lbl_804CAA44[7];
extern char lbl_804CAA4C[7];
extern char lbl_804CAA54[7];
extern char lbl_804CAA5C[7];
typedef struct KB { u8 pad[0x2d]; u8 x2d; u8 x2e; u8 pad2f[5]; RList l; } KB;
class Wd {
public:
    virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(KB*);
    u8 p4[6];
    s16 xa, xc, xe, x10, x12, x14, x16, x18;
    u8 p1a[0x38 - 0x1a];
    u32 x38;
    void* x3c;
    int x40;
};
static inline int kind3(int i) {
    switch (i) {
    case 0: return 0x16;
    case 1: return 0x17;
    case 2: return 0x18;
    default: return 0xb;
    }
}
static inline int kind6(int i) {
    switch (i) {
    case 0: return 0xb;
    case 1: return 0xc;
    case 2: return 0xd;
    case 3: return 0xe;
    case 4: return 0xf;
    case 5: return 0x10;
    default: return 0xb;
    }
}
#define TAB_LOOP(n, kind)     for (i = 0; i < n; i++) {         fn_8007E154();         fn_8007E720(0.01f);         fn_8007E164();         {             int k = kind(i);             int sel = 0;             BOOL ok = 0;             if (a->x2d == 0 && a->x2e == 0 && o->x3c != NULL) ok = 1;             if (ok) {                 void* c = o->x3c;                 if ((a->l.size != 0 ? (void*)a->l.prev->val : NULL) == c) sel = 1;             }             fn_801D820C(x, y, k, i == o->x40, sel, 0x10);         }         x += st;     }
#define TAB_TITLE     {         int t;         w = (int)((s16)(o->xe - o->xa) - x);         t = (s16)(o->x18 - o->x14);         t = (t - fn_800CB0FC(-1, 1.0f)) >> 1;         fn_8007E154();         fn_8007E174(0, o->x38 | 3);         fn_8007E164();         TITLE_SWITCH         {             int d = ((s16)w - fn_800CA3DC(s, -1, 0.8f)) >> 1;             fn_800CB3A8((int)(x + d), y + t - 1.0f, 1, 1, 0, s, 0.8f, 0.0f);         }         fn_801D855C(x, y, w, 0x10);     }
void fn_802114BC(Wd* o, KB* a) {
    const char* s;
    int i;
    int w;
    f32 x, y;
    o->v18(a);
    x = 0.0f;
    y = x; f32 st=20.0f;
    TAB_LOOP(3, kind3)
#define TITLE_SWITCH         switch (o->x40) {         case 0: s = fn_800D0864(lbl_804CAA28); break;         case 1: s = fn_800D0864(lbl_804CAA20); break;         case 2: s = fn_800D0864(lbl_8038F4B0); break;         default: s = lbl_804CAA18; break;         }
    TAB_TITLE
#undef TITLE_SWITCH
}
void fn_802117F8(Wd* o, KB* a) {
    const char* s;
    int i;
    int w;
    f32 x, y;
    o->v18(a);
    x = 0.0f;
    y = x; f32 st=20.0f;
    TAB_LOOP(6, kind6)
#define TITLE_SWITCH         switch (o->x40) {         case 0: s = fn_800D0864(lbl_804CAA5C); break;         case 1: s = fn_800D0864(lbl_804CAA54); break;         case 2: s = fn_800D0864(lbl_804CAA4C); break;         case 3: s = fn_800D0864(lbl_804CAA44); break;         case 4: s = fn_800D0864(lbl_804CAA3C); break;         case 5: s = fn_800D0864(lbl_804CAA34); break;         default: s = lbl_804CAA30; break;         }
    TAB_TITLE
}
void fn_80211B98(Wd* o, KB* a) {
    int i;
    f32 x, y;
    o->v18(a);
    x = 0.0f;
    y = x; f32 st=20.0f;
    TAB_LOOP(3, kind3)
}
void fn_80211EB4(Wd* o, KB* a) {
    int i;
    f32 x, y;
    o->v18(a);
    x = 0.0f;
    y = x; f32 st=20.0f;
    TAB_LOOP(6, kind6)
}
}
