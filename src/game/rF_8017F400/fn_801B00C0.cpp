#include "game/rF_8017F400/types.h"

#pragma auto_inline off

extern "C" {

typedef struct Names1 { const char* a[5][6]; } Names1;
typedef struct Names2 { const char* a[6][2]; } Names2;

typedef struct Lang {
    u8 pad[0x1BC8];
    u8 lang;
} Lang;

typedef struct Save {
    u8 pad[0x11];
    u8 x11;
} Save;

extern Names1 lbl_8036DA88;
extern Names2 lbl_8036DC60;
extern u8 lbl_803CAB38[];
extern Lang* fn_8024BC94(void);
extern Save* fn_80060728(void* p);
extern void fn_8023F1A0(const char* path, int a);
extern int fn_801D09F0(void);

/* picture list and shared state */
struct E { E() {} char c; };

typedef struct LData {
    void* res;  /* 0x00 */
    void* x4;   /* 0x04 */
    u8 pad8[0x18 - 8];
    void* x18;  /* 0x18 */
    int x1C;
    int x20;
    int x24;
    int x28;
    int x2C;
    int x30;
    int x34;
    int x38;
    int x3C;
    int x40;
    int x44;
    int x48;
    int x4C;
    int x50;
    int x54;
    int x58;
    int x5C;
    int x60;
    int x64;
    f32 x68;
} LData;

extern LData* lbl_804CB9BC;
extern void* lbl_804CB9B8;
extern int lbl_804CB9C0;
extern int lbl_804CB9C4;
extern int lbl_804CB9C8;
extern void fn_801B3B3C(void* p, E e);
extern void fn_801B3E68(void* p, E e);
extern void fn_801B4280(void* p, E e);
extern void fn_801B05F8(void);

static inline const char* Name1(void) {
    Names1 t = lbl_8036DA88;
    int lang = (s8)fn_8024BC94()->lang;
    return t.a[fn_80060728(lbl_803CAB38)->x11][lang];
}

static inline const char* Name2(void) {
    Names2 t = lbl_8036DC60;
    int w = fn_801D09F0();
    return t.a[(s8)fn_8024BC94()->lang][w];
}

void fn_801B00C0(void) {
    fn_8023F1A0(Name1(), 0);
    fn_8023F1A0(Name2(), 0);
}

static inline void Draw0(void* x) { fn_801B3B3C(x, E()); }
static inline void Draw1(void* x) { fn_801B3E68(x, E()); }
static inline void Draw2(void* x) { fn_801B4280(x, E()); }

void fn_801B0418(void) {
    switch (lbl_804CB9BC->x24) {
    case 0:
        Draw0(lbl_804CB9BC->x18);
        break;
    case 1:
        Draw1(lbl_804CB9BC->x18);
        break;
    case 2:
        Draw2(lbl_804CB9BC->x18);
        break;
    }
}

static inline void Move(int y, int x) {
    lbl_804CB9BC->x54 = lbl_804CB9BC->x4C;
    lbl_804CB9BC->x58 = lbl_804CB9BC->x50;
    lbl_804CB9BC->x5C = x;
    lbl_804CB9BC->x60 = y;
    lbl_804CB9BC->x48 = 0;
}

void fn_801B04A4(void) {
    lbl_804CB9BC->x1C = 0x18;
    lbl_804CB9BC->x20 = 0x48;
    lbl_804CB9BC->x24 = 0;
    lbl_804CB9BC->x2C = 0;
    lbl_804CB9BC->x28 = 2;
    lbl_804CB9BC->x3C = 0;
    lbl_804CB9BC->x38 = 0;
    { int x = lbl_804CB9BC->x1C + 0xF5; int y = lbl_804CB9BC->x20 + 0x22; Move(y, x); }
    fn_801B05F8();
}

void fn_801B0530(void) {
    lbl_804CB9BC->x1C = 0x18;
    lbl_804CB9BC->x20 = 0x48;
    lbl_804CB9BC->x24 = lbl_804CB9C0;
    lbl_804CB9BC->x2C = lbl_804CB9C4;
    lbl_804CB9BC->x38 = lbl_804CB9C8;
    lbl_804CB9BC->x28 = 2;
    {
        int v = lbl_804CB9BC->x38;
        lbl_804CB9BC->x44 = v;
        lbl_804CB9BC->x40 = v;
        lbl_804CB9BC->x3C = v;
    }
    { int x = lbl_804CB9BC->x1C + 0xF5; int y = lbl_804CB9BC->x20 + 0x22 + (lbl_804CB9BC->x2C - lbl_804CB9BC->x38 / 32) * 32; Move(y, x); }
    fn_801B05F8();
}


extern char lbl_8036DCE0[];
extern const char* fn_800D0864(const char* s);

const char* fn_801B092C(void) {
    const char* s;
    switch (lbl_804CB9BC->x28) {
    case 0:
        switch (lbl_804CB9BC->x24) {
        case 0:
            s = lbl_8036DCE0 + 0x2E;
            break;
        case 1:
            s = lbl_8036DCE0 + 0x41;
            break;
        case 2:
            s = lbl_8036DCE0 + 0x55;
            break;
        }
        break;
    case 1:
        s = lbl_8036DCE0 + 0x68;
        break;
    case 2:
        s = lbl_8036DCE0 + 0x73;
        break;
    }
    return fn_800D0864(s);
}

void fn_801B0DD8(void) {
    lbl_804CB9BC->x2C--;
    if (lbl_804CB9BC->x2C - lbl_804CB9BC->x38 / 32 <= 0) {
        lbl_804CB9BC->x38 -= 32;
        if (lbl_804CB9BC->x38 < 0) {
            lbl_804CB9BC->x38 = 0;
        }
    }
}

void fn_801B0E28(void) {
    int max = (*(int*)lbl_804CB9BC->x18 - 8) * 32;
    lbl_804CB9BC->x2C++;
    if (lbl_804CB9BC->x2C - lbl_804CB9BC->x38 / 32 >= 7) {
        lbl_804CB9BC->x38 += 32;
        if (lbl_804CB9BC->x38 > max) {
            lbl_804CB9BC->x38 = max;
        }
    }
}


extern void* fn_800C3558(void);
extern void fn_801D0C88(void* a, const char* s);
extern void fn_80062598(void* a, void* b);

void fn_801B1DC8(void) {
    fn_801D0C88(fn_800C3558(), lbl_8036DCE0 + 0xC9);
}

void fn_801B1ED4(void) {
    fn_80062598(lbl_803CAB38, lbl_804CB9B8);
}


extern void fn_801BCA5C(f32 v);
extern void fn_80072ACC(int a, int b, int c, int d, int e, int f, int g);
extern void fn_800712E8(int a, int b, int c);

void fn_801B3688(void) {
    fn_801BCA5C(-5.0f);
    if (lbl_804CB9BC->x28 == 2) {
        lbl_804CB9BC->x64 = lbl_804CB9BC->x50 + 0xD;
        lbl_804CB9BC->x68 += 0.2f;
        if (lbl_804CB9BC->x68 > 1.0f) {
            lbl_804CB9BC->x68 = 1.0f;
        }
    } else {
        lbl_804CB9BC->x68 -= 0.2f;
    }
    if (lbl_804CB9BC->x68 < 0.0f) {
        lbl_804CB9BC->x68 = 0.0f;
    }
    if (lbl_804CB9BC->x68 > 0.0f) {
        fn_80072ACC(lbl_804CB9BC->x1C + 0x187, lbl_804CB9BC->x64, 290.0f * lbl_804CB9BC->x68, 0x18, 0x19, 0x4B, 1);
    }
    fn_801BCA5C(-5.0f);
    fn_800712E8(lbl_804CB9BC->x4C, lbl_804CB9BC->x50, 1);
    fn_801BCA5C(10.0f);
}

extern u8 lbl_80389328[];
extern void* fn_80081194(void* cls, void* parent);
extern void* fn_80078CCC(u32 size, const char* tag, int arg);
extern void memset(void* p, int v, u32 n);
extern void fn_8009E694(int a);
extern void fn_800C835C(int a, int b);
extern void* fn_800A2918(void);
extern void fn_80083DC4(void* p, int r);

typedef struct LProc {
    u8 pad[0x30];
    LData* d;
} LProc;

static inline void NewProc(void* parent) {
    lbl_804CB9B8 = fn_80081194(lbl_80389328, parent);
    ((LProc*)lbl_804CB9B8)->d = (LData*)fn_80078CCC(0x6C, lbl_8036DCE0 + 0x147, 0);
    lbl_804CB9BC = ((LProc*)lbl_804CB9B8)->d;
    memset(lbl_804CB9BC, 0, 0x6C);
}

void* fn_801B39C4(void* parent) {
    NewProc(parent);
    return lbl_804CB9B8;
}

void fn_801B3A30(void) {
    fn_8009E694(1);
    fn_800C835C(1, 0);
    NewProc(fn_800A2918());
    fn_80083DC4(lbl_804CB9B8, 3);
}

const char* fn_801B3ABC(void) {
    Names1 t = lbl_8036DA88;
    int lang = (s8)fn_8024BC94()->lang;
    return t.a[fn_80060728(lbl_803CAB38)->x11][lang];
}

}
