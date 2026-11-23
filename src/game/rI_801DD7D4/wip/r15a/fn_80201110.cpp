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
void fn_8007E174(int, int);
void fn_8007E720(f32);
void fn_8007E74C(void*, void*);
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
extern char lbl_8036F328[];
int fn_800CA3DC(const char*, f32, int);
void fn_801E6DA0(int, int, int, const char*, ...);
void fn_80080B00(int, void*, f32);
const char* fn_80110F08(void*);
}
struct It2 { u8 p[0x16]; u16 x16; };
struct Ob { It2* x0; u8 x4, x5; };
class WU { public: virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); u32 x4; u8 p8[0xa]; s16 x12, x14, x16, x18; u8 p1a[4]; s16 x1e, x20; u8 p22[0x16]; u32 x38; u8 p3c[0x8]; Ob* x44; s16 x48; };
extern "C" void fn_80201110(WU* o) {
/*P*/
    int dd;
    s16 x;
    s16 y;
    int col;
    int yy;
    int dy;
    int fw;
    const char* s;
    s16 ww;
    int xx;
/*E*/
    o->v18();
    if (o->x44 == 0) return;
    x = o->x1e;
    y = o->x20;
    fn_8007E154();
    fn_8007E720(-1.0f);
    fn_8007E174(0, (u16)(o->x38 | 3));
    fn_8007E164();
    col = 0x31;
    if ((o->x44->x5 >> 5) & 1) col = 0x32;
    fw = (s16)FONT->v4C();
    dy = (0x20 - fn_800CB0FC(-1, 1.0f)) >> 1;
    fn_801E6DA0((s16)(x + fw), (s16)(y + dy), col, fn_80110F08(o->x44));
    s = fn_800D0864(lbl_8036F328);
    ww = (s16)((s16)(o->x16 - o->x12) - (s16)fn_800CA3DC(s, 1.0f, -1));
    dd = (0x20 - fn_800CB0FC(-1, 1.0f)) >> 1;
    xx = x + ww;
    yy = y + dd;
    fn_800CB278((s16)xx, (s16)yy, 0x1e, s);
    fn_800800D4(5);
    fn_80080508(*fn_800CD204(0x1f));
    fn_80080B00(1, fn_800CD204(0x2a), 1.0f);
    fn_80176F7C(xx - 4, yy, 0, 0, o->x48);
    fn_80080308();
    {
    int d2 = (0x20 - FONT->v50()) >> 1;
    It2* q = o->x44->x0;
    FONT->v18(x, y + d2, (u8)(q ? q->x16 : 0) + 0x81);
    }
}
