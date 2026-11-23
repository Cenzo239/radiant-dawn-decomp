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
extern char lbl_8036ED60[];
extern u8 lbl_8041EB20[0x100];
int fn_800CA3DC(const char*, f32, int);
void fn_80080B70(int, f32);
void fn_80080B00(int, void*, f32);
void fn_801A1DCC(void*, void*, f32, f32);
int fn_801A2224(void*);
void fn_80253EE4(const char*, f32);
}
class AV { public: void* x0; virtual int v8(); virtual int vC(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C(); virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34(); virtual int v38(); virtual int v3C(); virtual int v40(); virtual int v44(); virtual int v48(); virtual int v4C(); virtual int v50(); virtual int v54(); virtual int v58(); virtual int v5C(); virtual int v60(); virtual int v64(); virtual int v68(); virtual int v6C(); virtual int v70(); virtual int v74(); virtual int v78(); virtual int v7C(); virtual int v80(); virtual int v84(); virtual int v88(); virtual int v8C(); virtual int v90(); virtual int v94(); virtual int v98(); virtual int v9C(); virtual int vA0(); virtual int vA4(); virtual int vA8(); virtual int vAC(); virtual int vB0(); virtual int vB4(); virtual int vB8(); virtual int vBC(); virtual u32 vC0(int); virtual int vC4(); virtual int vC8(); virtual int vCC(); virtual int vD0(); 
  u8 p8[0x18]; const char* x20; };
static inline const char* txt(AV* o) {
    if (o->x20) return fn_800D0864(o->x20);
    return lbl_8036ED60 + 0x10;
}
extern "C" void fn_801DF530(AV* o) {
    /*P*/
    int hh;
    int a;
    s16 a2;
    int h1;
    const char* s;
    f32 x;
    f32 y;
/*E*/
    o->vD0();
    if (txt(o)) {
        fn_8007E154();
        fn_8007E720(-1.0f);
        fn_8007E174(0, 0x13);
        fn_8007E164();
        s = txt(o);
        a = (s16)o->v50() / 2;
        x = a - fn_800CA3DC(s, 1.0f, -1) / 2;
        h1 = (s16)o->vCC();
        a2 = (h1 - fn_800CB0FC(-1, 1.0f)) / 2;
        {
        hh = (s16)o->vC4();
        int dd = hh - (s16)o->vCC();
        y = dd + a2;
        }
        fn_800800D4(5);
        fn_80080330(x, y);
        fn_80080508(*fn_800CD204((u8)o->vB4()));
        if ((u8)o->vC0(1)) {
            fn_80080ABC(1, 2.0f);
        } else if ((u8)o->vC0(2)) {
            fn_80080B70(1, 1.0f);
        } else if ((u8)o->vC0(4)) {
            fn_80080B00(1, fn_800CD204(0x2a), 1.0f);
        }
        fn_80080C24(txt(o));
        fn_80080308();
    }
    fn_8007E154();
    fn_8007E7E8(0x80);
    fn_8007E164();
}

extern "C" {
extern char lbl_804CA944[4];
extern char lbl_804CA940[4];
unsigned long strlen(const char*);
char* strcpy(char*, const char*);
char* fn_8029135C(char*, const char*);
#if TARGET_PC
/* Host: __alloca is __builtin_alloca (mwcc_compat.h) */
#else
void* __alloca(unsigned int);
#endif
}
static inline f32 yOf(AV* o, int a) { s16 h7 = o->vC4(); int dd = h7 - (s16)o->vCC(); return dd + a; }
static inline f32 xOf(AV* o, const char* s) { s16 h7 = o->v50(); return (h7 - fn_800CA3DC(s, 1.0f, -1)) >> 1; }
extern "C" void fn_801E0B68(AV* o) {
    /*P*/
    char* s;
    f32 y;
    int a;
    s16 h;
    s16 hh;
    int hi;
    f32 x;
    char* buf;
/*E*/
    o->vD0();
    if (txt(o)) {
        buf = (char*)__alloca(strlen(txt(o)) + 1);
        strcpy(buf, txt(o));
        fn_8007E154();
        fn_8007E720(-1.0f);
        fn_8007E174(0, 0x13);
        fn_8007E164();
        h = o->vCC();
        a = (h - fn_800CB0FC(-1, 1.0f)) >> 1;
        hh = o->vC4();
        {
        int dd = hh - (s16)o->vCC();
        y = dd + a;
        }
        s = fn_8029135C(buf, lbl_804CA944);
        while (s) {
            hi = (s16)o->v50();
            x = (hi - fn_800CA3DC(s, 1.0f, -1)) >> 1;
            fn_800800D4(5);
            fn_80080330(x, y);
            fn_80080508(*fn_800CD204((u8)o->vB4()));
            if ((u8)o->vC0(1)) {
                fn_80080ABC(1, 2.0f);
            } else if ((u8)o->vC0(2)) {
                fn_80080B70(1, 1.0f);
            } else if ((u8)o->vC0(4)) {
                fn_80080B00(1, fn_800CD204(0x2a), 1.0f);
            }
            fn_80080C24(s);
            fn_80080308();
            y += (f32)(s16)o->vCC();
            s = fn_8029135C(0, lbl_804CA940);
        }
    }
    fn_8007E154();
    fn_8007E7E8(0x80);
    fn_8007E164();
}
