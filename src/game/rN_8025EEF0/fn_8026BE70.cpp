/* Base-menu loaders, the bonus-exp reader, misc procs. */
#include "game/rN_8025EEF0/calls.h"

#pragma use_lmw_stmw on

extern "C" {

int fn_800E272C(const char* s);
void fn_800E24F8(const char* s);
extern char lbl_803921F0[], lbl_803921E4[], lbl_803921D8[], lbl_803921C4[], lbl_803921B0[], lbl_8039219C[], lbl_8039218C[];
extern char lbl_80392160[], lbl_80392154[], lbl_80392148[], lbl_80392134[], lbl_80392120[], lbl_8039210C[], lbl_803920FC[];
extern const char* lbl_80391FA0[][2];
extern char lbl_8039216C[], lbl_803920DC[];

void fn_8026BE70(void* p) {
    if (fn_800E272C(lbl_803921F0) == 0) return;
    if (fn_800E272C(lbl_803921E4) == 0) return;
    if (fn_800E272C(lbl_803921D8) == 0) return;
    if (fn_800E272C(lbl_803921C4) == 0) return;
    if (fn_800E272C(lbl_803921B0) == 0) return;
    if (fn_800E272C(lbl_8039219C) == 0) return;
    if (fn_800E272C(lbl_8039218C) == 0) return;
    int lang = (s8)fn_8024BC94()[0x1BC8];
    if (fn_8023F880(lbl_80391FA0[lang][fn_801D09F0()]) == 0) return;
    if (fn_8023F880(lbl_8039216C) == 0) return;
    fn_80083B78(p);
}

void fn_8026BF7C(void) {
    fn_800E24F8(lbl_80392160);
    fn_800E24F8(lbl_80392154);
    fn_800E24F8(lbl_80392148);
    fn_800E24F8(lbl_80392134);
    fn_800E24F8(lbl_80392120);
    fn_800E24F8(lbl_8039210C);
    fn_800E24F8(lbl_803920FC);
    int lang = (s8)fn_8024BC94()[0x1BC8];
    fn_8023F1A0(lbl_80391FA0[lang][fn_801D09F0()], 0);
    fn_8023F1A0(lbl_803920DC, 0x2080);
}

int fn_800CD4DC(void);
void fn_80252418(const char* s, f32 v);
void fn_80250D64(int a, f32 b, f32 c);
extern char lbl_803922D8[];
extern u8 lbl_804CAB08;

void fn_8026C034(u8* p) {
    switch (fn_800CD4DC()) {
    case 7:
    case 0x30:
        break;
    default:
        fn_80252418(lbl_803922D8, 250.0f);
        fn_80250D64(6, 1.0f, 250.0f);
        break;
    }
    if (*(int*)(p + 0x4C) != 0) {
        fn_80006A2C(p + 0x4C);
    }
    lbl_804CAB08 = 0;
}

int fn_800D2150(void);
void fn_8026C0B0(void* p) {
    if (lbl_804CB5B8->v48() & 0x4400) {
        fn_80083B78(p);
    } else if (fn_800D2150() == 0) {
        fn_80083DC4(p, 0);
    }
}

void fn_800D1D14(const char* s, int a, int b);
extern char lbl_803920B8[], lbl_803920CC[];
void fn_8026C118(void) {
    if (*(u32*)(fn_8024BC94() + 0x20) & 0x20) {
        fn_800D1D14(lbl_803920CC, 0, 1);
    } else {
        fn_800D1D14(lbl_803920B8, 0, 1);
    }
    fn_800CD4A4(5);
}

extern u8 lbl_80391FD8[];
struct Proc54 { u8 pad[0x4C]; int m4C; int m50; u8 m54; };
void fn_8026C17C(void* parent) {
    Proc54* p = (Proc54*)fn_80081194(lbl_80391FD8, parent);
    p->m4C = 0;
    p->m50 = 0;
    p->m54 = 0;
}

/* Byte stream over a file, with an owned buffer. Stack object. */
struct Reader { u8* buf; u8* cur; int size; u8 own; void* vt; };
extern u8 lbl_80380940[];
void fn_8008A48C(Reader* r, void* a);
u32 fn_8008A1DC(Reader* r);

static inline void readerDtor(Reader* r) {
    r->vt = lbl_80380940;
    if (r->own) {
        fn_80078E24(r->buf);
        r->buf = 0;
        r->own = 0;
    }
}

BOOL fn_8026C650(void*, void* a) {
    Reader r;
    fn_8008A48C(&r, a);
    r.cur += 0x40;
    if (fn_8008A1DC(&r) != 0x4645384A) {
        readerDtor(&r);
        return 0;
    }
    r.cur += 8;
    if (fn_8008A1DC(&r) != 0x4000) {
        readerDtor(&r);
        return 0;
    }
    fn_8008A1DC(&r);
    r.cur += 0x1C;
    readerDtor(&r);
    return 1;
}

extern u8* lbl_804CC044;
extern u8* lbl_804CC040;
void* fn_800D4228(void* p);
#if TARGET_PC
FE10_PROTO int fn_8024F3C8(p32arg);
#else
int fn_8024F3C8(int a);
#endif
int fn_802454C8(void* a, int b);
#if TARGET_PC
FE10_PROTO int fn_80089C88(ptr32<const void>);
#else
int fn_80089C88(void* a);
#endif

void fn_8026D63C(void) {
    int i;
    int ofs;
    int n;
    u8* save;
    int a;
    save = fn_8024BC94();
    if (*(int*)(lbl_804CC044 + 0x30) != 0) {
        *(int*)(lbl_804CC044 + 0x2C) = 0;
        n = 0;
        i = 0;
        ofs = 0;
        for (; i < *(int*)(lbl_804CC044 + 0x10); ofs += 8, i++) {
            int id = (s16)fn_8024F3C8(*(int*)(*(u8**)(lbl_804CC044 + 0x18) + ofs));
            if (fn_802454C8(save, id) != 0) {
                (*(u8**)(lbl_804CC044 + 0x34))[n] = i;
                n++;
            }
        }
        for (i = 0; i < 1000; i++) {
            a = fn_80089C88(*(void**)(lbl_804CC044 + 0x30));
            int b = fn_80089C88(*(void**)(lbl_804CC044 + 0x30));
            u8* t = *(u8**)(lbl_804CC044 + 0x34);
            u8 tmp = t[a];
            t[a] = t[b];
            (*(u8**)(lbl_804CC044 + 0x34))[b] = tmp;
        }
    }
}

struct Pad28 { u8 pad[0x28]; };
class DtorObj : public Pad28 {
public:
    virtual void v08(); virtual void v0C(); virtual void v10();
    virtual void dtor(int del);
};

void fn_8026FA9C(void) {
    if (*(void**)(lbl_804CC044 + 0x34) != 0) {
        fn_80078E24(*(void**)(lbl_804CC044 + 0x34));
        *(void**)(lbl_804CC044 + 0x34) = 0;
        *(void**)(lbl_804CC044 + 0x34) = 0;
    }
    if (*(void**)(lbl_804CC044 + 0x3C) != 0 && fn_800D4228(*(void**)(lbl_804CC044 + 0x3C)) != 0) {
        fn_80081A90(fn_800D4228(*(void**)(lbl_804CC044 + 0x3C)));
    }
    fn_80081A90(fn_800D4228(*(void**)(lbl_804CC044 + 0x38)));
    DtorObj* o = *(DtorObj**)(lbl_804CC044 + 0x44);
    if (o != 0) {
        o->dtor(1);
    }
    fn_80006A2C(lbl_804CC044);
    fn_800761F0(*(void**)(lbl_804CC044 + 8));
    fn_80078E24(*(void**)(lbl_804CC040 + 0x30));
    *(void**)(lbl_804CC040 + 0x30) = 0;
}


/* Attack-preview unit proc: fades with fn_8017F68C */
void fn_800A947C(void* scene);
#if TARGET_PC
FE10_PROTO void* fn_800A7528(p32arg);
FE10_PROTO p32ret fn_800A8008(p32arg);
FE10_PROTO int fn_800A67EC(p32arg);
#else
void* fn_800A7528(int a);
int fn_800A8008(int a);
int fn_800A67EC(int a);
#endif
void fn_800AAB14(void* a, int b);
void fn_800AAB8C(void* a, int b);
#if TARGET_PC
FE10_PROTO void fn_800AA548(void* a, p32arg, int c);
FE10_PROTO void fn_800AE8F4(void* a, p32arg);
#else
void fn_800AA548(void* a, int b, int c);
void fn_800AE8F4(void* a, int b);
#endif
void fn_800B1120(void* a);
void fn_800B1540(void* a, int b);
void fn_800B4744(void* a, int b, int c);
void fn_800B54DC(void* a, int b);
void fn_800B08B0(void* a);
void fn_800A95F4(void* a);
void fn_800A4B00(void* a, void* b);
#if TARGET_PC
FE10_PROTO void* fn_800A8324(p32arg);
#else
void* fn_800A8324(int a);
#endif
void fn_800A4420(void* a, void* b, int c);
void fn_800A5D34(void* a, int b);
void fn_8014BC80(const char* s, void* b);
#if TARGET_PC
FE10_PROTO void* fn_8010B200(p32arg);
#else
void* fn_8010B200(int a);
#endif

struct IntroScene {
    u8 pad[0x30];
    void* m30;
    void* m34;
    u8 pad38[4];
    void* m3C;
    u8* m40;
    u8* m44;
    u8 pad48[4];
    u8 m4C;
    u8 pad4D[9];
    u8 m56;
    u8 pad57[9];
    s16 m60, m62;
    u8 pad64[2];
    s16 m66;
    void* m68;
    u8 pad6C[8];
    int* m74;
    u8 pad78[4];
    void* m7C;
};

void fn_8026AF24(IntroScene* p) {
    int z;
    int v;
    void* u;
    fn_800A947C(p);
    u = fn_800A7528(p->m74[1]);
    if (u == 0) {
        fn_80083DC4(p, 2);
        return;
    }
    {
        int b = fn_800A8008(p->m74[9]);
        v = -1;
        if (b != 0) {
            v = fn_800A67EC(b);
        }
    }
    z = 0;
    p->m4C = z;
    fn_800AAB14(p->m30, 3);
    fn_800AAB8C(p->m30, 1);
    fn_800AA548(p->m30, p->m74[3], p->m56);
    fn_800AE8F4(p->m34, p->m74[4]);
    *(void**)(p->m40 + 0x78) = u;
    *(u32*)(p->m40 + 0x50) |= 0x4000000;
    fn_800B1120(p->m40);
    fn_800B1540(p->m40, 0);
    p->m40[0x57] = p->m56;
    fn_800B4744(p->m40, v, 0);
    fn_800B54DC(p->m40, -1);
    *(int*)(p->m40 + 0x80) = z;
    fn_800B08B0(p->m3C);
    fn_800A95F4(p);
    p->m44[0x76] = p->m56;
    p->m44[0x75] = z;
    fn_800A4B00(p->m44, p->m40);
    fn_800A4420(p->m44, fn_800A8324(p->m74[8]), -1);
    fn_800A5D34(p->m44, 1);
    fn_8014BC80(fn_800D0864((const char*)p->m74[7]), p->m7C);
    lbl_804CB878 |= 0x2000;
    p->m66 = z;
    p->m60 = z;
    p->m62 = p->m74[10];
    p->m68 = fn_8010B200(p->m74[2]);
}

class VDel { public: virtual void dtor(int del); };

void fn_80272260(u8* p) {
    if (p != 0) {
        if (*(void**)(p + 0x30) != 0) {
            fn_800761F0(*(void**)(p + 0x30));
            *(void**)(p + 0x30) = 0;
        }
        if (*(void**)(p + 0x34) != 0) {
            fn_800761F0(*(void**)(p + 0x34));
            *(void**)(p + 0x34) = 0;
        }
        if (*(void**)(p + 0x38) != 0) {
            fn_80006A2C(p + 0x38);
        }
        int i;
        int z;
        i = 0;
        z = 0;
        do {
            VDel* o;
#define DEL(off) o = *(VDel**)(p + off); if (o != 0) { if (o != 0) o->dtor(1); }
            DEL(0x48)
            DEL(0x50)
            DEL(0x58)
            DEL(0x60)
            DEL(0x68)
            i++;
            *(int*)(p + 0x48) = z;
            *(int*)(p + 0x50) = z;
            *(int*)(p + 0x58) = z;
            *(int*)(p + 0x60) = z;
            *(int*)(p + 0x68) = z;
            p += 4;
        } while (i < 2);
    }
}

}
