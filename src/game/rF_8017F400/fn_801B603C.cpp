#include "game/rF_8017F400/types.h"

#pragma auto_inline off

extern "C" {

class Face {
public:
    u8 pad[0x58];
    virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1C();
    virtual void getRect(int i, int* a, int* b, int* c, int* d); /* +0x20 */
};

/* gallery / bonus viewer */
typedef struct GView {
    u8 pad[0x30];
    void* x30;     /* 0x30 */
    Face** pages;  /* 0x34 */
    void* x38;     /* 0x38 */
    void* tex;     /* 0x3C */
    void* x40;     /* 0x40 */
    void* x44;     /* 0x44 */
    void* x48;     /* 0x48 */
    void* x4C;     /* 0x4C */
    void* x50;     /* 0x50 */
    void* x54;     /* 0x54 */
    s16 x58;
    s16 x5A;
    s16 x5C;
    s16 x5E;
    u8 x60;
    u8 pad61;
    s8 x62;
    u8 x63;
    u8 x64;
    s8 x65;
    u8 x66;
    u8 pad67;
    s16 x68;
    s16 x6A;
    u8 x6C;
    u8 x6D;
    u8 x6E;
    u8 x6F;
} GView;

extern char lbl_8036DEB0[];
extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E4E4(f32 x, f32 y, f32 z, f32 w);
#if TARGET_PC
extern FE10_PROTO void fn_8007E374(void* a, p32arg, int c);
#else
extern void fn_8007E374(void* a, int b, int c);
#endif
extern void fn_8007E7B4(void);
extern void fn_8007E7DC(int a);
#if TARGET_PC
extern FE10_PROTO void fn_8007E174(p32arg, int b);
#else
extern void fn_8007E174(int a, int b);
#endif
extern void fn_800800D4(int a);
extern void fn_80080430(f32 a, f32 b, f32 c, f32 d, f32 e, f32 f);
extern void fn_80080578(int a);
extern void fn_80080308(void);
extern s8 fn_80244D88(void);
extern void fn_8007E7F4(void);
extern void fn_80072ACC(int a, int b, int c, int d, int e, int f, int g);
extern void fn_800712E8(int a, int b, int c);
extern void fn_80179204(void* p, int a);
extern void fn_80179214(void* p);
extern void fn_80179A84(void* p);
extern void fn_8017A188(void* p);
extern void fn_80312318(void* m);
extern void fn_80307E48(void* m, int a);
extern void fn_80021784(int a);
#if TARGET_PC
extern FE10_PROTO void fn_80020764(int a, int b, int c, int d, p32arg);
#else
extern void fn_80020764(int a, int b, int c, int d, int e);
#endif
extern void fn_80020AE0(f32 z, int a, int b, int c, int d);
extern void fn_80179888(void* p, int a);
extern void fn_80083B78(void* p);
extern f32 fn_8001EBC8(int m, f32 a, f32 b, f32 c, f32 d);
extern void fn_80083DC4(void* p, int r);
extern void fn_8017A968(void* p, const char* s);

void fn_801B603C(GView* p) {
    switch (p->x6C) {
    case 1:
    case 2:
        fn_8007E154();
        fn_8007E4E4(0.0f, 0.0f, 500.0f, 1.0f);
        fn_8007E374(p->tex, 5, 0x11);
        fn_8007E7B4();
        fn_8007E7DC(0xFF);
        fn_8007E164();
        fn_800800D4(1);
        fn_80080430(10.0f, 6.0f, 0.0f, 0.0f, 376.0f, 56.0f);
        fn_80080578(0);
        fn_80080308();
        break;
    default:
        fn_8007E154();
        fn_8007E4E4(0.0f, 0.0f, 500.0f, 1.0f);
        fn_8007E374(p->tex, 4, 0x11);
        fn_8007E7B4();
        fn_8007E7DC(0xFF);
        fn_8007E164();
        fn_800800D4(1);
        fn_80080430(10.0f, 6.0f, 0.0f, 0.0f, 320.0f, 56.0f);
        fn_80080578(0);
        fn_80080308();
        break;
    }
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 600.0f, 1.0f);
    fn_8007E374(p->tex, 0, 0x11);
    fn_8007E7B4();
    fn_8007E7DC(0xFF);
    fn_8007E164();
    fn_800800D4(1);
    fn_80080430(0.0f, 0.0f, 0.0f, 0.0f, 608.0f, 448.0f);
    fn_80080578(0);
    fn_80080308();
}

void fn_801B61B8(GView* p) {
    int dy = 0;
    int w;
    int h;
    int x0;
    int y0;
    int x1;
    int y1;
    fn_8007E154();
    fn_8007E4E4(374.0f, 33.0f, 300.0f, 1.0f);
    fn_8007E374(p->tex, 3, 0x11);
    fn_8007E7B4();
    fn_8007E7DC(0xFF);
    fn_8007E164();
    p->pages[p->x66 / 13]->getRect(p->x66 % 13, &x0, &y0, &x1, &y1);
    {
        s8 m = fn_80244D88();
        if (m != 0 && m >= 0 && m < 7) {
            dy = -1;
            y0 = y0 / 20 * 0x17;
            y1 = y1 / 20 * 0x17;
        }
    }
    w = x1 - x0;
    h = y1 - y0;
    fn_800800D4(1);
    fn_80080430((48 - w) / 2, dy, x0, y0, w, h);
    fn_80080578(3);
    fn_80080308();
    fn_8007E7F4();
}

void fn_801B63A0(GView* p) {
    int x;
    int y;
    int w;
    int h;
    s16 t = p->x6A;
    if (t % 32 == 0) {
        int tx;
        int ty;
        int tw;
        int th;
        if (p->x62 < 0) {
            tx = *(s16*)((u8*)p->pages[p->x63] + p->x65 * 2 + 0x3E);
            ty = 0x42;
            tw = 0;
            th = 0;
        } else {
            tx = 0x28;
            ty = (s16)((p->x62 << 5) + 0x68 - t);
            tw = 0x1B8;
            th = 0x16;
        }
        p->x58 = (p->x58 + tx) / 2;
        p->x5A = (p->x5A + ty) / 2;
        p->x5C = (p->x5C + tw) / 2;
        p->x5E = (p->x5E + th) / 2;
    }
    x = p->x58;
    y = p->x5A;
    w = p->x5C;
    h = p->x5E;
    fn_8007E154();
    fn_8007E7B4();
    fn_8007E164();
    if (p->x62 >= 0) {
        fn_8007E154();
        fn_8007E4E4(x + 0x14, y + 5, 300.0f, 1.0f);
        fn_8007E7DC(0xFF);
        fn_8007E164();
        {
            int a;
            int hh;
            int b;
            a = 0.325f * (w + 0x10);
            hh = h / 2;
            b = 0.75f * (w + 0x10);
            fn_80072ACC(a / 2, hh, a, 0x18, 0x19, 0x4B, 1);
            fn_80072ACC(a + b / 2 + 4, hh, b, 0x18, 0x19, 0x4B, 1);
        }
    }
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 50.0f, 1.0f);
    fn_8007E174(0, 0x11);
    fn_8007E7DC(0xFF);
    fn_8007E164();
    fn_800712E8(x, y, 1);
    fn_8007E7F4();
    if (p->x63 != 0) {
        fn_80179204(p->x40, 1);
    } else {
        fn_80179204(p->x40, 0);
    }
    if (p->x63 < p->x6D - 1) {
        fn_80179204(p->x44, 1);
    } else {
        fn_80179204(p->x44, 0);
    }
    fn_80179214(p->x40);
    fn_80179214(p->x44);
    fn_80179214(p->x48);
    fn_80179A84(p->x4C);
    fn_8017A188(p->x50);
}

void fn_801B6698(void) {
    char m[0x30];
    fn_80312318(m);
    fn_80307E48(m, 0);
    fn_80021784(0);
    fn_80020764(0, 0, 0x260, 0x1C0, 0);
}

void fn_801B66E8(void) {
    char m[0x30];
    fn_80312318(m);
    fn_80307E48(m, 0);
    fn_80021784(0);
    fn_80020AE0(400.0f, 0, 0, 0x260, 0x1C0);
}

extern void fn_801B6738(GView* p);
extern void fn_801B6B18(GView* p);
extern void fn_801B7004(GView* p);
extern void fn_801B739C(Face* f, GView* p, int i);

static inline BOOL IsVisible(GView* p, int i) {
    int b;
    int a = p->x68 / 0x150;
    b = a;
    if (p->x68 % 0x150 != 0) {
        b = a + 1;
    }
    if (i >= a && i <= b) {
        return TRUE;
    }
    return FALSE;
}

static inline void DrawPages(GView* p) {
    for (int i = 0; i < p->x6D; i++) {
        if (IsVisible(p, i)) {
            fn_801B739C(p->pages[i], p, i);
        }
    }
}

void fn_801B7290(GView* p) {
    fn_801B603C(p);
    fn_801B6738(p);
    fn_801B6B18(p);
    fn_801B7004(p);
    fn_801B61B8(p);
    DrawPages(p);
    fn_801B63A0(p);
    p->x6E++;
}

u8 fn_801B76F0(void) {
    return 0;
}

class Pad {
public:
    virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34();
    virtual void v38();
    virtual u32 rep();  /* +0x3C */
    virtual void v40(); virtual void v44();
    virtual u32 held(); /* +0x48 */
};
extern Pad* lbl_804CB5B8;
extern void fn_801791E0(void* p);
extern void fn_80253EE4(const char* s, f32 v);

int fn_801B76F8(GView* p) {
    int cur = p->x63;
    if (cur == 0) {
        if (lbl_804CB5B8->held() & 0x100001) {
            p->x63 = p->x6D - 1;
        }
    } else {
        if (lbl_804CB5B8->rep() & 0x100001) {
            p->x63 = p->x63 - 1;
        }
    }
    if (p->x63 == cur) {
        return 0;
    }
    if (p->x62 < 0) {
        p->x65 = *((u8*)p->pages[p->x63] + 0x21) - 1;
    } else {
        p->x65 = 0;
    }
    p->x64 = 0;
    fn_801791E0(p->x40);
    fn_80083DC4(p, 4);
    fn_80253EE4(lbl_8036DEB0 + 0x6F, 0.0f);
    return 1;
}

extern char lbl_8041EC48[];
extern const char* lbl_80389528[];
extern char lbl_804CA8F0[8];
extern void fn_80290DDC(char* out, const char* fmt, ...);
extern void fn_8023F1A0(const char* path, int a);
extern int fn_8023F880(const char* path);

static inline const char* LangName(void) {
    s8 m = fn_80244D88();
    if (m >= 0) {
        return lbl_80389528[m];
    }
    return lbl_804CA8F0;
}

void fn_801B7808(void) {
    fn_80290DDC(lbl_8041EC48, lbl_8036DEB0 + 0x8B, LangName());
    fn_8023F1A0(lbl_8041EC48, 0x2080);
}

BOOL fn_801B7874(void) {
    fn_80290DDC(lbl_8041EC48, lbl_8036DEB0 + 0x8B, LangName());
    if (fn_8023F880(lbl_8041EC48) != 0) {
        return FALSE;
    }
    return TRUE;
}

void fn_801B8B00(u32* p) {
    p[0] = 0;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0;
    p[4] = 0;
}

void fn_801B8B1C(GView* p) {
    p->x6A += p->x6F;
    fn_80179888(p->x4C, p->x6A);
    if (p->x6A % 32 == 0) {
        fn_80083B78(p);
    }
}

void fn_801B8B84(GView* p) {
    p->x6A -= p->x6F;
    fn_80179888(p->x4C, p->x6A);
    if (p->x6A % 32 == 0) {
        fn_80083B78(p);
    }
}

void fn_801B8BEC(GView* p) {
    p->x64++;
    p->x68 = fn_8001EBC8(2, (p->x63 + 1) * 0x150, p->x63 * 0x150, 16.0f, p->x64);
    if (p->x64 == 16) {
        p->x64 = 0;
        if (p->x62 < 0) {
            fn_80083DC4(p, 6);
        } else {
            fn_80083DC4(p, 1);
        }
    }
}

void fn_801B8CD0(GView* p) {
    p->x64++;
    p->x68 = fn_8001EBC8(2, (p->x63 - 1) * 0x150, p->x63 * 0x150, 16.0f, p->x64);
    if (p->x64 == 16) {
        p->x64 = 0;
        if (p->x62 < 0) {
            fn_80083DC4(p, 6);
        } else {
            fn_80083DC4(p, 1);
        }
    }
}

void fn_801B9384(GView* p) {
    p->x62 = -1;
    if (p->x62 < 0) {
        switch (p->x6C) {
        case 1:
        case 2:
            fn_8017A968(p->x50, lbl_8036DEB0 + 0xA3);
            break;
        case 5:
            fn_8017A968(p->x50, lbl_8036DEB0 + 0xB4);
            break;
        default:
            fn_8017A968(p->x50, lbl_8036DEB0 + 0xC4);
            break;
        }
    } else {
        switch (p->x6C) {
        case 1:
        case 2:
            fn_8017A968(p->x50, lbl_8036DEB0 + 0xD3);
            break;
        case 5:
            fn_8017A968(p->x50, lbl_8036DEB0 + 0xE4);
            break;
        default:
            fn_8017A968(p->x50, lbl_8036DEB0 + 0xF4);
            break;
        }
    }
}


static inline void SetTitle(GView* p) {
    if (p->x62 < 0) {
        switch (p->x6C) {
        case 1:
        case 2:
            fn_8017A968(p->x50, lbl_8036DEB0 + 0xA3);
            break;
        case 5:
            fn_8017A968(p->x50, lbl_8036DEB0 + 0xB4);
            break;
        default:
            fn_8017A968(p->x50, lbl_8036DEB0 + 0xC4);
            break;
        }
    } else {
        switch (p->x6C) {
        case 1:
        case 2:
            fn_8017A968(p->x50, lbl_8036DEB0 + 0xD3);
            break;
        case 5:
            fn_8017A968(p->x50, lbl_8036DEB0 + 0xE4);
            break;
        default:
            fn_8017A968(p->x50, lbl_8036DEB0 + 0xF4);
            break;
        }
    }
}

void fn_801B9C20(GView* p) {
    SetTitle(p);
}

extern void fn_80081A90(void* p);
#if TARGET_PC
extern FE10_PROTO void fn_801C6D2C(ptr32<const void>, GView* p, int m, ptr32<const void>, ptr32<const void>);
#else
extern void fn_801C6D2C(void* a, GView* p, int m, void* cb, GView* q);
#endif
extern u8* fn_80060728(void* p);
extern u8 lbl_803CAB38[];
extern void fn_801B9F30(void* a, GView* p);
#if TARGET_PC
extern FE10_PROTO void* fn_80177284(ptr32<const void>, void* arg);
#else
extern void* fn_80177284(void* cb, void* arg);
#endif
extern GView* fn_80081194(void* cls, void* parent);
extern u8 lbl_80389548[];
extern u8 lbl_80389570[];
extern u8 lbl_8038966C[];
extern u8 lbl_80389758[];
extern u8 lbl_803CA870[];
extern void fn_801BA20C(void* p, void* arg);

void fn_801BA094(GView* p) {
    if (p->x30 != NULL) {
        fn_80081A90(p->x30);
        p->x30 = NULL;
    }
}

typedef struct GHolder {
    u8 pad[0x18];
    GView* v;
} GHolder;

void fn_801BA0D8(GHolder* h) {
    GView* p = h->v;
    void* e = *(void**)((u8*)p->x38 + p->x62 * 0x1C);
    switch (p->x6C) {
    case 0:
    case 5:
        fn_801C6D2C(e, p, 0, (void*)fn_801BA094, p);
        break;
    case 1:
    case 2:
    case 3:
        fn_801C6D2C(e, p, 1, (void*)fn_801BA094, p);
        break;
    case 4:
        fn_801C6D2C(e, p, 2, (void*)fn_801BA094, p);
        break;
    }
}

void fn_801BA158(GHolder* h) {
    GView* p = h->v;
    fn_801B9F30(*(void**)(fn_80060728(lbl_803CAB38) + 0x24), p);
    if (p->x30 == NULL) {
        p->x30 = fn_80177284((void*)fn_801B7290, p);
    }
}

void fn_801BA1B8(void* parent) {
    fn_80081194(lbl_80389548, parent);
}

void fn_801BA1C8(u8 a, void* parent) {
    GView* p = fn_80081194(lbl_80389570, parent);
    p->x60 = a;
    p->x54 = NULL;
    p->x6C = 0;
}

void fn_801BA354(void* parent) {
    GView* p = fn_80081194(lbl_80389570, parent);
    p->x60 = 0;
    p->x54 = (void*)fn_801BA20C;
    p->x6C = 5;
}

void fn_801BA39C(void* parent) {
    GView* p = fn_80081194(lbl_8038966C, parent);
    p->x54 = NULL;
    p->x6C = 3;
}

void fn_801BA3D8(u8 a, void* parent) {
    GView* p = fn_80081194(lbl_8038966C, parent);
    p->x54 = NULL;
    p->x60 = a;
    p->x6C = 4;
}

void fn_801BA420(GView* p) {
    if (lbl_803CA870[0xC] == 0x81) {
        fn_80083DC4(p, 0);
    }
    SetTitle(p);
}

void fn_801BA544(void* a, void* parent) {
    GView* p = fn_80081194(lbl_80389758, parent);
    p->x54 = a;
    p->x6C = 1;
}

void fn_801BA584(void* a, void* parent) {
    GView* p = fn_80081194(lbl_80389758, parent);
    p->x54 = a;
    p->x6C = 2;
}

void fn_801BA5C4(void* unused, int m, int* a, int* b, int* c, int* d) {
    switch (m) {
    case 0:
        *b = 0;
        break;
    case 1:
        *b = 0x14;
        break;
    case 2:
        *b = 0x30C;
        break;
    }
    *a = 0;
    *c = 0x38;
    *d = *b + 0x14;
}

extern char lbl_80389B7C[];
extern char lbl_80389B68[];
extern char lbl_80389B54[];

const char* fn_801BA628(void* unused, int m) {
    switch (m) {
    case 1:
        return lbl_80389B7C;
    case 2:
        return lbl_80389B68;
    default:
        return lbl_80389B54;
    }
}

}
