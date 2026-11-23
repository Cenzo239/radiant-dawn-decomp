#include "game/rF_8017F400/types.h"

#pragma auto_inline off

extern "C" {

/* letterbox process: 0x5C+ bytes */
typedef struct LBox {
    u8 pad[0x30];
    f32 y;        /* 0x30 */
    f32 x34;      /* 0x34 */
    void* tex;    /* 0x38 */
    u8 x3C;
    u8 alpha;     /* 0x3D */
    u8 t;         /* 0x3E */
    u8 maxAlpha;  /* 0x3F */
    u8 dur;       /* 0x40 */
    u8 pad41;
    s16 x42;      /* 0x42 */
    s16 a[4];     /* 0x44 */
    u32 b[4];     /* 0x4C */
} LBox;

/* timed text process */
typedef struct TText {
    u8 pad[0x31];
    u8 state;     /* 0x31 */
    u8 alpha;     /* 0x32 */
    u8 x33;       /* 0x33 */
    s16 t;        /* 0x34 */
    s16 fadeIn;   /* 0x36 */
    s16 wait;     /* 0x38 */
    s16 fadeOut;  /* 0x3A */
    s16 x;        /* 0x3C */
    s16 y;        /* 0x3E */
    u8 pad40[4];
    u32 text;     /* 0x44 */
} TText;

extern char lbl_8036D57C[];
extern u8 lbl_803891A4[];
extern u32 lbl_804CB700;
extern void fn_801C6EAC(const char* a, const char* b, char* out);
extern void* fn_8001D3B4(const char* path);
#if TARGET_PC
extern FE10_PROTO void fn_8017DAD4(const char* path, ptr32<const void>, void* arg, int z);
extern FE10_PROTO void* fn_80177284(ptr32<const void>, void* arg);
#else
extern void fn_8017DAD4(const char* path, void* cb, void* arg, int z);
extern void* fn_80177284(void* cb, void* arg);
#endif
#if TARGET_PC
extern FE10_PROTO void * fn_80076F54(const char* s);
#else
extern int fn_80076F54(const char* s);
#endif
extern s16 fn_8009A9A8(const char* s);
extern void fn_801ACD98(void* p);
extern void fn_8001D424(void* p);
extern f32 fn_8001EF30(f32 a, f32 b, f32 c, f32 d);
extern f32 fn_8001EBC8(int m, f32 a, f32 b, f32 c, f32 d);
extern void fn_80083B78(void* p);
extern void* fn_80081050(void* cls, void* parent);
extern void fn_800846BC(void* cls);
extern void* fn_80083B84(void* cls);
extern void fn_80083DC4(void* p, int r);
extern const char* fn_800D0864(const char* id);
extern int fn_800CA3DC(const char* s, int n, f32 scale);
extern void fn_803080DC(int a, int b, int c, int d);
extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E4E4(f32 x, f32 y, f32 z, f32 w);
extern void fn_8007E7DC(int a);
extern void fn_80074718(int x, int y, u32 t);
extern f32 fn_8017F68C(int a, f32 x, f32 y, f32 t, f32 d);

void fn_801AD0D0(LBox* p) {
    char path[0x60];
    fn_801C6EAC(lbl_8036D57C + 0xBE, lbl_8036D57C + 0xD5, path);
    p->tex = fn_8001D3B4(path);
}

void fn_801AD11C(LBox* p) {
    char path[0x60];
    p->y = 0.0f;
    p->x34 = 0.0f;
    p->alpha = 0;
    p->maxAlpha = 0xC0;
    p->dur = 10;
    p->t = 0;
    p->x3C = 0;
    p->a[0] = 0;
    p->b[0] = 0;
    p->a[1] = 0;
    p->b[1] = 0;
    p->a[2] = 0;
    p->b[2] = 0;
    p->a[3] = 0;
    p->b[3] = 0;
    p->tex = NULL;
    fn_801C6EAC(lbl_8036D57C + 0xBE, lbl_8036D57C + 0xD5, path);
    fn_8017DAD4(path, (void*)fn_801AD0D0, p, 0);
    fn_80177284((void*)fn_801ACD98, p);
    if (fn_80076F54(lbl_8036D57C + 0xDA) != 0) {
        p->x42 = fn_8009A9A8(lbl_8036D57C + 0xDA);
    } else {
        p->x42 = 0;
    }
}

void fn_801AD208(LBox* p) {
    if (p->tex != NULL) {
        fn_8001D424(p->tex);
    }
}

void fn_801AD21C(LBox* p) {
    if (p->t < p->dur) {
        p->t++;
    }
    p->alpha = fn_8001EF30(0.0f, p->maxAlpha, p->dur, p->t);
    p->y = fn_8001EBC8(2, -200.0f, 0.0f, p->dur, p->t);
    if (p->t == p->dur) {
        fn_80083B78(p);
    }
}

void fn_801AD304(LBox* p) {
    if (p->t != 0) {
        p->t--;
    }
    p->alpha = fn_8001EF30(0.0f, p->maxAlpha, p->dur, p->t);
    p->y = fn_8001EBC8(2, -200.0f, 0.0f, p->dur, p->t);
    if (p->t == 0) {
        fn_80083B78(p);
    }
}

void fn_801AD3E4(LBox* p) {
    p->t = p->dur;
    p->y = 0.0f;
    p->alpha = p->maxAlpha;
}

void fn_801AD400(LBox* p) {
    p->t = 0;
    p->y = -255.0f;
    p->alpha = 0;
}

void fn_801AD418(void* parent) {
    fn_80081050(lbl_803891A4, parent);
}

void fn_801AD428(void) {
    fn_800846BC(lbl_803891A4);
}

void fn_801AD434(void) {
    void* p = fn_80083B84(lbl_803891A4);
    if (p != NULL) {
        fn_80083DC4(p, 1);
    }
}

void fn_801AD46C(void) {
    void* p = fn_80083B84(lbl_803891A4);
    if (p != NULL) {
        fn_80083DC4(p, 2);
    }
}

void fn_801AD4A4(void) {
    void* p = fn_80083B84(lbl_803891A4);
    if (p != NULL) {
        fn_80083DC4(p, 3);
    }
}

void fn_801AD4DC(void) {
    void* p = fn_80083B84(lbl_803891A4);
    if (p != NULL) {
        fn_80083DC4(p, 4);
    }
}

void fn_801AD514(TText* p) {
    f32 w = fn_800CA3DC(fn_800D0864((const char*)p->text), -1, 1.0f);
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 930.0f, 1.0f);
    fn_8007E7DC(p->alpha);
    fn_8007E164();
    fn_80074718(p->x, p->y, p->text);
    fn_8007E154();
    fn_8007E7DC(0xFF);
    fn_8007E164();
}

void fn_801AD5A4(TText* p) {
    if (p != NULL) {
        p->state = 0;
        p->t = 0;
        if (p->x33 == 2) {
            p->x -= fn_800CA3DC(fn_800D0864((const char*)p->text), -1, 1.0f);
        }
        fn_80083B78(p);
    }
}

void fn_801AD614(TText* p) {
    u32 f;
    s16 w = p->wait;
    if (w != -1) {
        f = lbl_804CB700;
        if (*(volatile u32*)&lbl_804CB700 & 0x8001) {
            fn_80083B78(p);
            return;
        }
        if (f & 2) {
            p->state = 10;
            p->t = 0;
            return;
        }
    }
    switch ((s8)p->state) {
    case 0:
        p->t++;
        p->alpha = fn_8017F68C(0, 0.0f, 255.0f, p->t, p->fadeIn);
        if (p->t >= p->fadeIn) {
            p->state = 5;
            p->t = 0;
        }
        break;
    case 5:
        if (w != -1) {
            p->t++;
            if (p->t >= p->wait) {
                p->state = 10;
                p->t = 0;
            }
        }
        break;
    case 10:
        p->t++;
        p->alpha = fn_8017F68C(0, 255.0f, 0.0f, p->t, p->fadeOut);
        if (p->t >= p->fadeOut) {
            fn_80083B78(p);
        }
        break;
    }
}


extern u8 lbl_80389234[];
extern u8 lbl_80389210[];
typedef struct FadeArg {
    s8 id;
    int v;
} FadeArg;
extern FadeArg lbl_804CB9B0;
extern void fn_800893E4(void* cls, void* cb, void* arg);
extern void* memcpy(void* d, const void* s, u32 n);

typedef struct TText2 {
    u8 pad[0x30];
    s8 id;        /* 0x30 */
    u8 state;     /* 0x31 */
    u8 alpha;     /* 0x32 */
    u8 x33;       /* 0x33 */
    s16 t;        /* 0x34 */
    s16 fadeIn;   /* 0x36 */
    s16 wait;     /* 0x38 */
    s16 fadeOut;  /* 0x3A */
    s16 x;        /* 0x3C */
    s16 y;        /* 0x3E */
    u8 pad40[4];
    u32 text;     /* 0x44 */
    u8 x48;       /* 0x48 */
} TText2;

void fn_801ADA54(s16 x, s16 y, u32 text, int fade, int wait) {
    TText2* p = (TText2*)fn_80081050(lbl_80389234, (void*)3);
    p->x = x;
    p->y = y;
    p->text = text;
    p->fadeIn = fade / (1000.0f / 60.0f);
    p->wait = wait / (1000.0f / 60.0f);
    p->fadeOut = fade / (1000.0f / 60.0f);
    p->x33 = 1;
}

void fn_801ADB38(s16 x, s16 y, u8 mode, u32 text, int fade, int wait, int out, void* parent) {
    TText2* p = (TText2*)fn_80081050(lbl_80389210, parent);
    p->x = x;
    p->y = y;
    p->text = text;
    p->id = -1;
    p->fadeIn = fade / (1000.0f / 60.0f);
    p->wait = wait / (1000.0f / 60.0f);
    p->fadeOut = out / (1000.0f / 60.0f);
    p->x48 = 0;
    p->x33 = mode;
}

void fn_801ADC34(s8 id, s16 x, s16 y, u32 text, int fade, void* parent) {
    TText2* p = (TText2*)fn_80081050(lbl_80389210, parent);
    p->x = x;
    p->y = y;
    p->text = text;
    p->id = id;
    p->fadeIn = fade / (1000.0f / 60.0f);
    p->wait = -1;
    p->fadeOut = 0;
    p->x48 = 0;
    p->x33 = 1;
}

int fn_801ADCE4(TText2* p, FadeArg* a) {
    s8 id = a->id;
    if ((s8)p->id == id || id == -1) {
        p->state = 10;
        p->fadeOut = a->v;
    }
    return 0;
}

void fn_801ADD1C(s8 id, int ms) {
    lbl_804CB9B0.id = id;
    lbl_804CB9B0.v = ms / (1000.0f / 60.0f);
    fn_800893E4(lbl_80389210, (void*)fn_801ADCE4, &lbl_804CB9B0);
}

void fn_801ADD8C(int ms) {
    lbl_804CB9B0.id = -1;
    lbl_804CB9B0.v = ms / (1000.0f / 60.0f);
    fn_800893E4(lbl_80389210, (void*)fn_801ADCE4, &lbl_804CB9B0);
}

/* confirmation-prompt text screen, 0x210 bytes */
typedef struct CData {
    void* res;    /* 0x000 */
    u8 x4, x5;
    s16 x6;       /* 0x006 */
    s16 x8;       /* 0x008 */
    s16 xA;       /* 0x00A */
    s16 xC, xE, x10, x12, x14;
    u8 x16, x17;
    s16 x18;      /* 0x018 */
    s16 x1A, x1C;
    s16 x1E, x20, x22, x24, x26;
    char title[0x60]; /* 0x028 */
    u8 x88;       /* 0x088 */
    u8 x89;       /* 0x089 */
    s8 x8A;       /* 0x08A */
    u8 pad8B;
    s16 x8C;      /* 0x08C */
    u8 pad8E[0x94 - 0x8E];
    u8 x94;       /* 0x094 */
    u8 x95;       /* 0x095 */
    u8 pad96[2];
    const char* a[6]; /* 0x098 */
    const char* b[6]; /* 0x0B0 */
    u8 c[6];      /* 0x0C8 */
    char line[5][0x40]; /* 0x0CE */
} CData;

typedef struct CProc {
    u8 pad[0x30];
    CData* d;
} CProc;

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
extern char lbl_8036D68C[];
extern u8 lbl_803CAB38[];
extern void memset(void* p, int v, u32 n);
extern void fn_800068A0(void* res, const char* path);
#if TARGET_PC
extern FE10_PROTO char * fn_800CEC24(void);
extern FE10_PROTO char * fn_800CEB4C(void);
extern FE10_PROTO char * fn_800CF3A4(void);
extern FE10_PROTO char * fn_800CF470(void);
#else
extern int fn_800CEC24(const char* s);
extern int fn_800CEB4C(const char* s);
extern int fn_800CF3A4(const char* s);
extern int fn_800CF470(const char* s);
#endif
extern void fn_80290DDC(char* out, const char* fmt, ...);
extern void fn_80253EE4(const char* s, f32 v);
extern void fn_800CD4A4(int a);
extern void fn_800CD548(int a);
extern void fn_80006A2C(void* p);
extern void fn_80078E24(void* p);
extern void fn_802512C4(f32 v);
extern void fn_801D5DFC(void);

#pragma push
#pragma use_lmw_stmw on
void fn_801ADE00(CData* d) {
    int z = 0;
    int i;
    int n;
    const char* q;
    const char* start;
    d->line[0][0] = z;
    d->line[1][0] = z;
    d->line[2][0] = z;
    d->line[3][0] = z;
    d->line[4][0] = z;
    q = fn_800D0864(d->b[d->x6]);
    start = q;
    n = 0;
    i = 0;
    while (1) {
        if (*q == 0 || *q == '\n') {
            if (n > 0) {
                memcpy(d->line[i], start, n);
            }
            d->line[i][n] = z;
            i++;
            if (*q == 0) {
                break;
            }
            q++;
            n = 0;
            start = q;
        } else {
            q++;
            n++;
        }
    }
    d->x95 = i;
}

void fn_801AEA74(CProc* p) {
    CData* d = p->d;
    char* s;
    memset(d, 0, 0x210);
    s = lbl_8036D68C;
    d->x8C = 0xFF;
    d->a[0] = s + 0x2B;
    d->b[0] = s + 0x38;
    d->c[0] = 0;
    d->a[1] = s + 0x48;
    d->b[1] = s + 0x55;
    d->c[1] = 1;
    d->a[2] = s + 0x65;
    d->b[2] = s + 0x72;
    d->c[2] = 2;
    d->a[3] = s + 0x82;
    d->b[3] = s + 0x8F;
    d->c[3] = 3;
    d->a[4] = s + 0x9F;
    d->b[4] = s + 0xAC;
    d->c[4] = 4;
    d->a[5] = s + 0xBC;
    d->b[5] = s + 0xC9;
    d->c[5] = 5;
    d->x94 = 6;
    d->x8A = -1;
    d->x89 = d->c[d->x6];
    fn_800068A0(d, s + 0xD9);
}

#pragma pop

static inline void Cur(CData* d, s16 y) {
    d->xC = 4;
    d->xE = d->x8;
    d->x10 = d->xA;
    d->x12 = 0x31;
    d->x14 = y;
}

void fn_801AEC38(CProc* p) {
    CData* d = p->d;
    u32 held = lbl_804CB5B8->held();
    u32 rep = lbl_804CB5B8->rep();
    s16 sel = d->x6;
    if (held & 0x400) {
        fn_80253EE4(lbl_8036D68C + 0x11E, 0.0f);
        fn_80083DC4(p, 1);
        return;
    }
    if (held & 0x800) {
        fn_80253EE4(lbl_8036D68C + 0x12E, 0.0f);
        fn_800CD4A4(8);
        fn_80083DC4(p, 2);
        return;
    }
    if (rep & 0x800008) {
        d->x6 = sel - 1;
        if (d->x6 < 0) {
            d->x6 = 0;
        }
    }
    if (rep & 0x400004) {
        d->x6++;
        if (d->x6 > d->x94 - 1) {
            d->x6 = d->x94 - 1;
        }
    }
    if (sel != d->x6) {
        Cur(d, d->x6 * 0x18 + 0x78);
        fn_80253EE4(lbl_8036D68C + 0x13E, 0.0f);
        d->x8A = d->x89;
        d->x89 = d->c[d->x6];
        d->x8C = 0;
    }
}

void fn_801AEE9C(CProc* p) {
    CData* d = p->d;
    u32 held = lbl_804CB5B8->held();
    u32 rep = lbl_804CB5B8->rep();
    s16 sel = d->x18;
    if (held & 0x400) {
        if (sel == 0) {
            fn_80253EE4(lbl_8036D68C + 0x17E, 0.0f);
            fn_800CD548(d->c[d->x6] + 0x5B);
            fn_800CD4A4(0x23);
            fn_80083DC4(p, 2);
        } else {
            fn_80253EE4(lbl_8036D68C + 0x11E, 0.0f);
            fn_80083DC4(p, 0);
        }
        return;
    }
    if (held & 0x800) {
        fn_80253EE4(lbl_8036D68C + 0x12E, 0.0f);
        fn_80083DC4(p, 0);
        return;
    }
    if (rep & 0x100001) {
        d->x18 = 0;
        d->x1E = 4;
        d->x20 = d->x1A;
        d->x22 = d->x1C;
        d->x24 = 0x1BD;
        d->x26 = 0x3D;
    }
    if (rep & 0x200002) {
        d->x18 = 1;
        d->x1E = 4;
        d->x20 = d->x1A;
        d->x22 = d->x1C;
        d->x24 = 0x1FE;
        d->x26 = 0x3D;
    }
    if (sel != d->x18) {
        fn_80253EE4(lbl_8036D68C + 0x18E, 0.0f);
    }
}

void fn_801AF040(CProc* p) {
    CData* d = p->d;
    fn_80006A2C(d);
    fn_80078E24(d);
}

typedef struct PData {
    u32 x0;
    u32 x4;
    s64 t;   /* 0x08 */
    void* x10;
} PData;

typedef struct PProc {
    u8 pad[0x30];
    PData* d;
    void* x34;
} PProc;

extern void fn_801BCA5C(f32 v);
#if TARGET_PC
extern FE10_PROTO void fn_8007E374(void* a, p32arg, int c);
#else
extern void fn_8007E374(void* a, int b, int c);
#endif
extern void fn_800800D4(int a);
extern void fn_80080348(f32 a, f32 b, f32 c, f32 d);
extern void fn_80080368(f32 a, f32 b, f32 c, f32 d);
extern void fn_80080578(int a);
extern void fn_80080308(void);
extern void fn_801BCA94(void);
extern void fn_800CB3A8(f32 a, f32 b, int x, int y, int c, int d, int e, const char* fmt, ...);



void fn_801AFEB0(PProc* p);

void fn_801AF078(PProc* p) {
    PData* d = p->d;
    fn_802512C4(1000.0f);
    d->x0 = 0;
    d->x4 = 0;
    d->t = *(s64*)(lbl_803CAB38 + 0xA8);
    fn_800068A0(&d->x10, lbl_8036D68C + 0x1AA);
    fn_801D5DFC();
    p->x34 = fn_80177284((void*)fn_801AFEB0, p);
}

extern void fn_801AF104(PData* d);

extern void fn_801AF2A8(PData* d, f32 a, f32 b);

void fn_801AFEB0(PProc* p) {
    PData* d = p->d;
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 30.0f, 1.0f);
    fn_8007E164();
    fn_801AF104(d);
    fn_801AF2A8(d, 64.0f, 128.0f);
}

void fn_801AFF0C(PProc* p) {
    PData* d = p->d;
    u32 held = lbl_804CB5B8->held();
    switch (d->x0) {
    case 0:
        d->x0 = 1;
        d->x4 = 0;
        break;
    case 1:
        if ((held & 0x400) || (held & 0x800)) {
            fn_80083B78(p);
        }
        break;
    }
}

extern void fn_801D607C(void);
extern void fn_80081A90(void* p);
extern CProc* fn_80081194(void* cls, void* parent);
extern void* fn_80078CCC(u32 size, const char* tag, int arg);
extern u8 lbl_80389258[];
extern u8 lbl_803892D4[];

void fn_801AFF9C(PProc* p) {
    PData* d = p->d;
    fn_801D607C();
    if (p->x34 != NULL) {
        fn_80081A90(p->x34);
    }
    if (d->x10 != NULL) {
        fn_80006A2C(&d->x10);
    }
    fn_80078E24(d);
}

void fn_801B0000(void* parent) {
    CProc* p = fn_80081194(lbl_80389258, parent);
    p->d = (CData*)fn_80078CCC(0x210, lbl_8036D68C + 0x2A5, 0);
}

void fn_801B0054(void* parent) {
    PProc* p = (PProc*)fn_80081194(lbl_803892D4, parent);
    p->d = (PData*)fn_80078CCC(0x18, lbl_8036D68C + 0x2A5, 0);
}

void fn_801B00A8(void* unused, s16* r) {
    fn_803080DC(r[0], r[1], r[2], r[3]);
}

}
