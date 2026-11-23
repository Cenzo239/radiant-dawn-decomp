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
struct Sl { int x; u8 p[0x24]; };
struct Pg { u8 p[0x1bc]; Sl e[7]; };
struct Li { u8 p[0x4c]; u8 x4c; u8 x4d; u8 p4e[2]; s16 x50; u8 p52[0xa]; Pg* x5c; int x60; };

int fn_801E9A30(Li* o) {
    int r = -1;
    Sl* e = o->x5c->e;
    int i;
    for (i = 0; i < 7; i++) {
        if (e[i].x == 0) { r = i; break; }
    }
    return r;
}
#define BODY(STEP) \
        e = o->x5c->e; \
        b = 0; \
        if (*(int*)((char*)e + ind) == 0) { \
          if (o->x60 == 1) { \
            k = i; \
            if (k == 0 || e[(u32)(k - 1)].x != 0) b = 1; \
          } \
        } else b = 1; \
        if (b) { res = i; break; }
void fn_801E9B58(Li* o, Pg* p) {
/*P*/
    int i;
    BOOL b;
    int res;
    int ind;
    s16 k;
    Sl* e;
/*E*/
    o->x5c = p;
    i = 0;
    res = -1;
    for (ind = 0; i < 7; i++, ind += 0x28) { BODY() }
    o->x50 = res;
}
int fn_801E9914(Li* o, int i) {
/*P*/
    BOOL b;
    int ind;
    s16 k;
    Sl* e;
    int res;
/*E*/
    res = -1;
    for (ind = i * 0x28; i >= 0; i--, ind -= 0x28) { BODY() }
    return res;
}
int fn_801E999C(Li* o, int i) {
/*P*/
    BOOL b;
    int ind;
    s16 k;
    Sl* e;
    int res;
/*E*/
    res = -1;
    if (i < 0) i = 0;
    for (ind = i * 0x28; i < 7; i++, ind += 0x28) { BODY() }
    return res;
}
}
