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
int fn_800CA3DC(const char*, f32, int);
void fn_801D7A68(s16, s16, int);
}
class IC { public: virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual const char* v18(void*); virtual void v1C(); virtual int v20(); };
class AV { public: u32 x0; virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3C(); virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4C(); virtual void v50(); virtual void v54();
  virtual int v58(); virtual int v5C(); virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6C(); virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7C(); virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8C(); virtual void v90(); virtual void v94(); virtual int v98(); };
struct BV { u8 p[0x3c]; AV* x3c; };
struct EV { u8 p[0x30]; s16 x30, x32; IC* x34; u8 x38; };
class OV { public: virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3C(); virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4C(); virtual void v50(BV*, EV*); virtual void v54(BV*, EV*); };
static inline int cenA(BV* b) { s16 h = b->x3c->v5C(); return (h - fn_800CB0FC(-1, 1.0f)) >> 1; }
static inline int cenB(BV* b) { s16 h = b->x3c->v5C(); return (h - FONT->v4C()) >> 1; }
static inline int addM(int a, int b) { return a + b; }
static inline void endD(void) { fn_8007E154(); fn_8007E7E8(0x80); fn_8007E164(); }
extern "C" void fn_801DEE70(OV* o, BV* b, EV* e) {
    /*P*/
    int dx;
    int dy;
    AV* a;
    f32 x;
    f32 y;
/*E*/
    o->v50(b, e);
    ALPHA(-0.2f);
    dx = (0x100 - fn_800CA3DC(e->x34->v18(e), 1.0f, -1)) >> 1;
    dy = (0x21 - fn_800CB0FC(-1, 1.0f)) >> 1;
    a = b->x3c;
    if (e->x38 && e->x30 < (s16)a->v98()) {
        s16 t = a->v98();
        e->x30 = e->x30 + ((t - e->x30) >> 1);
    } else if (e->x30 != (s16)a->v98() - 0x20) {
        s16 t = a->v98();
        e->x30 = e->x30 + (((t - 0x20) - e->x30) >> 1);
    }
    x = e->x30;
    y = e->x32;
    fn_800800D4(5);
    fn_80080330(x + dx, y + dy);
    o->v54(b, e);
    fn_80080C24(e->x34->v18(e));
    fn_80080308();
    ALPHA(0.1f);
    fn_801D7A68(x, y, 0x10);
    endD();
}
