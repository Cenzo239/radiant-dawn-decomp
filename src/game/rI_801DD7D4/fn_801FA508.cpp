typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef unsigned long long u64;
typedef float f32;
typedef int BOOL;
#define TRUE 1
#define FALSE 0
#define NULL 0
extern "C" {
extern u32 lbl_804CB700;
extern char lbl_803E7290[];
extern char lbl_803C8E80[];
struct C4 { u8 r, g, b, a; };
int fn_800CB0FC(int, f32);
void fn_8007E154(void);
void fn_8007E164(void);
#if TARGET_PC
FE10_PROTO void fn_8007E174(p32arg, int);
#else
void fn_8007E174(int, int);
#endif
void fn_8007E720(f32);
#if TARGET_PC
FE10_PROTO void fn_8007E74C(ptr32<const void>, ptr32<const void>);
#else
void fn_8007E74C(void*, void*);
#endif
void fn_8007E7B4(void);
void fn_800800D4(int);
void fn_80080308(void);
void fn_80080330(f32, f32);
void fn_80080ABC(int, f32);
void fn_80080C24(const char*);
void fn_80176EA8(int, int, int, const char*);
void fn_801D8ADC(int, int, int, int);
const char* fn_800D0864(const char*);
void fn_800CB3A8(int x, int y, int a, int b, int c, f32 s, f32 t, const char* f, ...);
void fn_800CB278(int, int, int, const char*, ...);
C4* fn_800CD204(int i);
void fn_80080508(C4);
void fn_80176F7C(int, int, int, int, int);
u32* fn_801E2204(void*, void*, void*);
void fn_801E2104(void* p, void* arg);
}
struct DB { u8 pad[0x44]; };
class DV : public DB {
public:
    virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14();
    virtual int v18(int, int, int);
    virtual int v1C(); virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34();
    virtual int v38(); virtual int v3C(); virtual int v40(); virtual int v44(); virtual int v48();
    virtual int v4C(); virtual int v50();
};
#define FONT ((DV*)lbl_803E7290)
class WV { public: virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual int v30(); virtual int v34(); };
static inline void ALPHA(f32 f) { fn_8007E154(); fn_8007E720(f); fn_8007E164(); }

extern "C" {
extern u8 lbl_803CA870[0x10];
#define G0 (*(void**)lbl_803CA870)
extern char lbl_804CA990[8];
int fn_80127520(void*);
void fn_80129CB8(void*, int);
void fn_80102C6C(void*, void*, int, int, int);
void fn_801EA538(void*, void*);
int fn_801E999C(void*, int);
int fn_801E9A30(void*);
void fn_801E5734(void*, void*);
s16* fn_801E2204x(void*, void*, void*);
u32* fn_801E2204y(void*, void*, void*);
struct RO { u8 p[0x1e]; s16 x1e, x20; u8 p2[0x36]; s16 x58[12]; };
struct RM { virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual int v30(); virtual int v34(); };
struct LL { u8 p[0x4c]; u8 x4c; u8 x4d; u8 p4e[2]; s16 x50; u8 p52[2]; s16 x54, x56; };
struct Bx { u8 p[0x40]; int x40, x44; };
struct OO { u8 p[0x44]; Bx* x44; u8 p48[4]; LL* x4c; u8 p50[4]; u8* x54; Bx* x58; };
#define CLEAR_MENU(o) \
    if (fn_80127520(lbl_803CA870) < 0) fn_80129CB8(lbl_803CA870, -1);
static inline void refresh(void* g) {
    if ((s8)fn_80127520(g) < 0) fn_80129CB8(g, -1);
}
static inline void setA(Bx* b, const int& v) { b->x40 = v; b->x44 = v; if (v == 0) b->x40 = v; }
void fn_801FA508(OO* o) {
    if ((s8)fn_80127520(G0) < 0) fn_80129CB8(G0, -1);
    if (G0) fn_80102C6C(G0, lbl_804CA990, 4, 0, 0);
    if (o->x44 && o->x44->x40) fn_801EA538(o->x44, (void*)o->x44->x40);
    {
    int z = 0;
    o->x54[0x51] = z;
    {
    LL* l = o->x4c;
    l->x50 = fn_801E999C(l, 0);
    }
    {Bx* b = o->x58; b->x40 = z; b->x44 = z; if (!b->x40) b->x40 = z;}
    }
}
void fn_801FAC44(OO* o) {
    if ((s8)fn_80127520(G0) < 0) fn_80129CB8(G0, -1);
    if (G0) fn_80102C6C(G0, lbl_804CA990, 4, 0, 0);
    if (o->x44 && o->x44->x40) fn_801EA538(o->x44, (void*)o->x44->x40);
    {
    int z = 0;
    LL* l = o->x4c;
    l->x4c = z;
    l->x50 = fn_801E999C(l, 0);
    {Bx* b = o->x58; b->x40 = z; b->x44 = z; if (!b->x40) b->x40 = z;}
    }
}

}
