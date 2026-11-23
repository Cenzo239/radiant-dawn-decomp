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
void fn_8007E7E8(int);
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
void fn_801D820C(s16, s16, int, int, int, int);
}
class OW { public: virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(void*); u32 x4; u8 p8[0x34]; void* x3c; u32 x40; };
struct KB2 { u8 p[0x2d]; u8 x2d, x2e; u8 p2f[5]; int x34; struct { u8 p[8]; void* x8; }* x38; };
static inline BOOL idle(OW* o, KB2* c) { BOOL r = 0; if (c->x2d == 0 && c->x2e == 0 && o->x3c != 0) r = 1; return r; }
static inline void* top(KB2* c) { return c->x34 != 0 ? c->x38->x8 : 0; }
extern "C" void fn_801FFCBC(OW* o, KB2* c) {
    /*P*/
    u32 i;
    f32 x;
    f32 y;
    f32 st;
    /*E*/
    o->v18(c);
    x = 0.0f;
    y = x;
    st = 20.0f;
    for (i = 0; (int)i < 12; i++) {
        int tex;
        int on;
        ALPHA(0.01f);
        switch (i) {
        case 0: tex = 0xb; break;
        case 1: tex = 0xc; break;
        case 2: tex = 0xd; break;
        case 3: tex = 0xe; break;
        case 4: tex = 0xf; break;
        case 5: tex = 0x11; break;
        case 6: tex = 0x12; break;
        case 7: tex = 0x13; break;
        case 8: tex = 0x14; break;
        case 9: tex = 0x15; break;
        case 10: tex = 0x16; break;
        case 11: tex = 0x17; break;
        default: tex = 0xb; break;
        }
        on = 0;
        if (idle(o, c)) { void* k = o->x3c; if (top(c) == k) on = 1; }
        fn_801D820C(x, y, tex, i == o->x40, on, 0x10);
        x += st;
    }
}
