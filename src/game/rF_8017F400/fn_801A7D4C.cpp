#include "game/rF_8017F400/types.h"

#pragma auto_inline off

extern "C" {

class Pad {
public:
    virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34();
    virtual void v38(); virtual void v3C(); virtual void v40(); virtual void v44();
    virtual u32 held(); /* +0x48 */
};

class Snd {
public:
    virtual void v08(); virtual void v0C();
    virtual int isOk(); /* +0x10 */
    virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20();
    virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30();
    virtual void v34();
    virtual void fade(f32 a, f32 b); /* +0x38 */
};

/* class change / level up screen: per-unit stat display, 0x14C bytes */
typedef struct UData {
    u32 x0, x4, x8, xC; /* 0x00 */
    u32 mode;      /* 0x10 */
    u8* unit;      /* 0x14 */
    void* res;     /* 0x18 */
    u8 stat[11];   /* 0x1C */
    u8 diff[10];   /* 0x27 */
    u8 pad31[3];
    f32 scale[10]; /* 0x34 */
    u32 x5C, x60, x64;
    u8 x68;
    u8 pad69[3];
    u32 x6C;       /* 0x6C */
    u8 buf[0xC8];  /* 0x70 */
    f32 x138;      /* 0x138 */
    u32 x13C;      /* 0x13C */
    u8 x140;       /* 0x140 */
    u8 pad141[3];
    void* x144;    /* 0x144 */
    void* x148;    /* 0x148 */
} UData;

typedef struct UProc {
    u8 pad[0x30];
    UData* d; /* 0x30 */
} UProc;

typedef struct BsDiff {
    u8 pad[0xC];
    u8 v[10];
    u8 pad16[2];
} BsDiff;

typedef struct UNode {
    u8 pad[8];
    s16 x8;
    u8 padA[0x9C - 0xA];
    void* cb; /* 0x9C */
} UNode;

typedef struct UModel {
    u8 pad[0x30];
    UNode* node;
} UModel;

extern char lbl_8036D360[];
extern Pad* lbl_804CB5B8;
extern u8 lbl_80388F9C[];
extern u8 lbl_80388FD8[];
extern void memset(void* p, int v, u32 n);
extern void fn_801C6EAC(const char* a, const char* b, char* out);
extern void fn_8023F1A0(const char* path, int a);
extern u8 fn_8012246C(void* u);
extern u8 fn_801224BC(void* u);
extern u8 fn_8012250C(void* u);
extern u8 fn_8012255C(void* u);
extern u8 fn_801225AC(void* u);
extern u8 fn_801225FC(void* u);
extern u8 fn_8012264C(void* u);
extern u8 fn_8012269C(void* u);
extern u8 fn_8012401C(void* u);
extern u8 fn_801226EC(void* u);
extern void fn_80193404(BsDiff* out);
extern void* fn_80193198(void);
extern void* fn_8012486C(void* u);
extern void* fn_800C3FD0(void* a);
extern void fn_800C3EE0(void* a, int b);
extern int fn_800AE654(void);
extern int fn_8023F880(const char* path);
extern int fn_800C3F64(void* a);
extern void fn_800068A0(void* res, const char* path);
extern void* fn_800C6210(void* a, int b);
extern void fn_80083B78(void* p);
extern void fn_800E24F8(const char* s);
extern void fn_800E4B20(void* p, int a);
extern UModel* fn_800E3E38(const char* s, void* parent);
extern void fn_800E48AC(UModel* m, f32 x, f32 y, f32 z);
extern void fn_80253EE4(const char* s, f32 v);
extern Snd* fn_8024F3FC(int id);
extern void fn_801A7FDC(UProc* p);
extern void fn_800C429C(void* p);
extern void fn_80006A2C(void* p);
extern void fn_80078E24(void* p);
extern void* fn_80078CCC(u32 size, const char* tag, int arg);
extern UProc* fn_80081194(void* cls, void* parent);
extern void fn_803080DC(int a, int b, int c, int d);

void fn_801A7D4C(UData* d) {
    char path[0x60];
    BsDiff diff;
    u8* unit = d->unit;
    d->x0 = 0;
    d->x4 = 0;
    d->x8 = 0;
    d->xC = 0;
    d->x68 = 0;
    d->x13C = *(u32*)(unit + 0xF0);
    d->x138 = 1.0f;
    d->x6C = 0;
    memset(d->buf, 0, 0xC8);
    fn_801C6EAC(lbl_8036D360, lbl_8036D360 + 0x13, path);
    fn_8023F1A0(path, 0);
    d->stat[0] = unit[0xFE];
    d->stat[1] = fn_8012246C(unit);
    d->stat[2] = fn_801224BC(unit);
    d->stat[3] = fn_8012250C(unit);
    d->stat[4] = fn_8012255C(unit);
    d->stat[5] = fn_801225AC(unit);
    d->stat[6] = fn_801225FC(unit);
    d->stat[7] = fn_8012264C(unit);
    d->stat[8] = fn_8012269C(unit);
    d->stat[9] = fn_8012401C(unit);
    d->stat[10] = fn_801226EC(unit);
    fn_80193404(&diff);
    d->diff[0] = diff.v[0];
    d->diff[1] = diff.v[1];
    d->diff[2] = diff.v[2];
    d->diff[3] = diff.v[3];
    d->diff[4] = diff.v[4];
    d->diff[5] = diff.v[5];
    d->diff[6] = diff.v[6];
    d->diff[7] = diff.v[7];
    d->diff[8] = diff.v[8];
    d->diff[9] = diff.v[9];
    d->scale[0] = 1.0f;
    d->scale[1] = 1.0f;
    d->scale[2] = 1.0f;
    d->scale[3] = 1.0f;
    d->scale[4] = 1.0f;
    d->scale[5] = 1.0f;
    d->scale[6] = 1.0f;
    d->scale[7] = 1.0f;
    d->scale[8] = 1.0f;
    d->scale[9] = 1.0f;
    d->x5C = 0;
    d->x60 = 0;
    d->x64 = 0;
    if (fn_80193198() != NULL) {
        d->x144 = fn_8012486C(fn_80193198());
    } else {
        d->x144 = fn_8012486C(d->unit);
    }
    fn_800C3EE0(fn_800C3FD0(d->x144), 0);
    if (fn_800AE654() != 0) {
        d->x140 = 3;
    } else {
        d->x140 = 0;
    }
}

void fn_801A7F4C(UProc* p) {
    UData* d = p->d;
    char path[0x60];
    fn_801C6EAC(lbl_8036D360, lbl_8036D360 + 0x13, path);
    if (fn_8023F880(path) != 0) {
        if (fn_800C3F64(fn_800C3FD0(d->x144)) != 0) {
            fn_800068A0(&d->res, path);
            d->x148 = fn_800C6210(d->x144, 0);
            fn_80083B78(p);
        }
    }
}

void fn_801A9DAC(void) {
    char* s = lbl_8036D360;
    fn_800E24F8(s + 0x6C);
    fn_800E24F8(s + 0x3D);
    fn_800E24F8(s + 0x5E);
}

void fn_801A9DF0(UProc* m) {
    if (lbl_804CB5B8->held() & 0xFFF0) {
        fn_800E4B20(m, -1);
        ((UNode*)m->d)->cb = NULL;
    }
}

void fn_801A9E4C(UProc* p) {
    UData* d = p->d;
    UModel* m;
    fn_801A7D4C(d);
    m = fn_800E3E38(lbl_8036D360 + 0x6C, p);
    fn_800E48AC(m, 304.0f, 224.0f, 0.0f);
    m->node->x8 = 10;
    m->node->cb = (void*)fn_801A9DF0;
    fn_80253EE4(lbl_8036D360 + 0x78, 0.0f);
    {
        Snd* snd = fn_8024F3FC((s8)d->x140);
        if (snd != NULL && snd->isOk() != 0) {
            snd->fade(0.5f, 50.0f);
        }
    }
    d->res = NULL;
}

void fn_801A9F34(UProc* p) {
    fn_801A7FDC(p);
}

void fn_801A9F38(UProc* p) {
    UData* d = p->d;
    Snd* snd = fn_8024F3FC((s8)d->x140);
    if (snd != NULL && snd->isOk() != 0) {
        snd->fade(1.0f, 1000.0f);
    }
    if (d->x148 != NULL) {
        fn_800C429C(d->x148);
    }
    if (d->res != NULL) {
        fn_80006A2C(&d->res);
    }
    fn_80078E24(d);
}

void fn_801A9FE0(UProc* p) {
    UData* d = p->d;
    fn_801A7D4C(d);
    d->res = NULL;
}

void fn_801AA018(UProc* p) {
    fn_801A7FDC(p);
}

void fn_801AA01C(UProc* p) {
    UData* d = p->d;
    if (d->x148 != NULL) {
        fn_800C429C(d->x148);
    }
    if (d->res != NULL) {
        fn_80006A2C(&d->res);
    }
    fn_80078E24(d);
}

void fn_801AA070(void* unit, void* parent) {
    UProc* p = fn_80081194(lbl_80388F9C, parent);
    p->d = (UData*)fn_80078CCC(0x14C, lbl_8036D360 + 0x89, 0);
    p->d->unit = (u8*)unit;
    p->d->mode = 0;
}

void fn_801AA0DC(void* unit, void* parent) {
    UProc* p = fn_80081194(lbl_80388FD8, parent);
    p->d = (UData*)fn_80078CCC(0x14C, lbl_8036D360 + 0x89, 0);
    p->d->unit = (u8*)unit;
    p->d->mode = 1;
}

void fn_801AA148(void* unit, void* parent) {
    UProc* p = fn_80081194(lbl_80388FD8, parent);
    p->d = (UData*)fn_80078CCC(0x14C, lbl_8036D360 + 0x89, 0);
    p->d->unit = (u8*)unit;
    p->d->mode = 2;
}

void fn_801AA1B4(void* unused, s16* r) {
    fn_803080DC(r[0], r[1], r[2], r[3]);
}

}
