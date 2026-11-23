/* fn_8017D428 (round 18): NOT at regs level (class other), 235 of 236 instructions. The setup, the whole wave simulation loop and the
   epilogue match. In the texture write loop the original adds (i>>2)*16 + (i&3) first and then the row term, and keeps a dead
   'srawi r3,j,2' in the outer loop; ours adds the row term first. About 35 spellings of the index tried (locals, inlines, u16/struct
   indexing, shifts, / and %). Functionally the same code. */
/* Screen filter process: blur, cross-fade, glow, zoom, depth of field, wave. */
typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;
typedef float f32;
#include "game/rR_80175E5C/strpool.h"
#define FIFOF (*(volatile f32*)0xCC008000)
#define F(p, t, o) (*(t*)((u8*)(p) + (o)))

struct C4 { u8 r, g, b, a; };

struct Filter {
    u8* base;
    int a;
    int b;
    int c;
    int d;
    u8 pad14[0x24 - 0x14];
    u8 mode;
    u8 a1;
    u8 a2;
    u8 n;
    s16 x28;
    u8 x2a;
    C4 col;
};

extern "C" {
extern char lbl_804CB8CA;
extern void* lbl_804CB8CC;
extern u8 lbl_80387B88[], lbl_80387BB0[], lbl_80387C38[];
void fn_803031CC();
void fn_80302B80(int, int);
void fn_80303200(int, int, int, int, int);
void fn_80021C34(u8);
void fn_80021B2C(int);
void fn_80021A08(int, int, int, int, int, int, int);
void fn_80021BF4(u8);
void fn_80021CB4(int, int, int, int);
void fn_80021860(int, int, int);
void fn_80021B68(int);
void fn_80021BA4(int, int, int, int);
void fn_80304314(int, int, int);
void fn_80011838(int);
void fn_80305A40(void*, void*, u16, u16, int, int, int, int);
void fn_80305C94(void*, int, int, f32, f32, f32, int, int, int);
void fn_80022254(void*, int);
void fn_80021E20(int, int, int, int, int);
void fn_80021D18(int, int, int, int, int, int);
void fn_80021E8C(int, int, int, int, int);
void fn_80021D9C(int, int, int, int, int, int);
void fn_80307F10(void*, int, int);
void fn_80021F7C(int, int, int, int);
void fn_80012268();
int fn_80011EB4();
int fn_80011F38();
int fn_80011E28();
int fn_80011EAC();
int fn_80011FBC();
int fn_80011FC4();
int fn_80012048();
void fn_80306EA0(int, C4);
void fn_80021FF0(int, int);
void fn_8000FF74(int);
void fn_800104DC(int);
void fn_8001F4D8(int, int, int, int, int, int, void*, int, int);
void fn_8001F5B8(int, int, int, int, int, int, void*, int, C4*, void*, u16);
int fn_80007630(void*, const char*);
int fn_8030585C(int, int, int, int, int);
void fn_80020E7C(int);
void* fn_80020E74();
void* fn_80078D9C(int, const char*, int);
void DCFlushRange(void*, int);
void fn_8017F464(void*, u32, int);
void fn_80021958(int, C4);
void fn_800218A8(int, C4);
void fn_80021C74(int);
void fn_80306B6C(int, int, int, int, int);
void fn_8001E51C(void*);
void fn_803067E0(int, void*, s8);
void fn_80306A38(int, int, int);
void fn_80306934(int, int, int);
void fn_80306B24(int);
void fn_8031292C(void*, f32, f32, f32);
u32 fn_80089ED0();
void* fn_80007F3C(void*);
void fn_80014E24(void*, const char*, void*, int);
void* fn_800893E4(void*, void*, void*);
void fn_8017D838(void* p, void* arg);
void fn_8017D84C(void*);
void* fn_80081194(void*, void*);
void* fn_80081050(void*, void*);
char* strcpy(char*, const char*);
void fn_800CB278(int, int, int, const char*, ...);
void fn_8007E4E4(f32, f32, f32, f32);
void* fn_80010BB0(void*);
void* fn_80010DA4(void*, int);
void* fn_80010E38(void*, int);
void fn_80081A90(void*);
void fn_8007E154();
void fn_8007E164();
void fn_8007E174(void* tex, u16 flags);
void fn_800800D4(int mode);
void fn_80080308();
void fn_80080388(f32 x, f32 y, f32 w, f32 h);
void fn_80080578(int);
void fn_80080940(C4 a, C4 b, C4 c, C4 d);

static inline void Pos(f32 x, f32 y, f32 z) {
    FIFOF = x;
    FIFOF = y;
    FIFOF = z;
}
static inline void Tc(f32 s, f32 t) {
    FIFOF = s;
    FIFOF = t;
}

static inline void Konst(u8 a) {
    C4 c;
    c.r = a;
    c.g = a;
    c.b = a;
    c.a = a;
    fn_80306EA0(0, c);
}
void fn_8017B160(int x, int y, int w, int h, int tw, int th, void* tex, int fmt, u8 a, u8 add);

void fn_8017C2F4(void* a);


static inline const C4& White() {
    C4 c = {0xFF, 0xFF, 0xFF, 0xFF};
    return c;
}
void fn_8017CD80(void* a);

void fn_8017D1DC(u8* o);

void fn_8017D84C(void* a);

void fn_8017DAD4(const char* name, int a, void* parent, int b);

void fn_8017DC24(f32 r, f32 g, f32 t, int lo, int hi);

void fn_8017E25C(u8* o);

void fn_8017E9E0(u8* o);

}


/* fn_8017D428: wave filter step. Reads the "waveB" joint for speed/scale/damping, runs one step of a
   32x32 wave simulation on two height fields (wrap-around neighbours, clamped edges) and writes the
   result as an IA8-style 4x4-block texture, then swaps the two texture buffers. */
extern "C" {
struct WVec { f32 x, y, z; };
u8* fn_800080B8(void*);
void fn_80312DB4(void*, WVec*, WVec*);
void fn_8017F4A0(void*, void*, int);
extern const WVec lbl_8036B468;

void fn_8017D428(u8* o) {
    f32 pa[0x400];
    f32 pb[0x400];
    int j;
    int i;
    int n = fn_80007630(F(o, void*, 0x30), "waveB");
    if (n >= 0) {
        WVec v = lbl_8036B468;
        fn_80312DB4(fn_800080B8(F(o, void*, 0x30)) + n * 0x30, &v, &v);
        F(o, int, 0x34) = (int)v.x;
        F(o, f32, 0x38) = 32.0f * v.y;
        F(o, f32, 0x3C) = v.z;
    }
    fn_8017F4A0(pa, F(o, void*, 0x40), 0x1000);
    fn_8017F4A0(pb, F(o, void*, 0x44), 0x1000);
    DCFlushRange(pa, 0x1000);
    DCFlushRange(pb, 0x1000);
    for (j = 0; j < 0x20; j++) {
        for (i = 0; i < 0x20; i++) {
            f32 sa = 0.0f;
            f32 sb = 0.0f;
            int k = i + j * 0x20;
            int jm = j - 1;
            int jp;
            int im;
            int ip;
            if (jm < 0) jm = 0x1F;
            jp = j + 1;
            if (jp > 0x1F) jp = 0;
            im = i - 1;
            if (im < 0) im = 0x1F;
            ip = i + 1;
            if (ip > 0x1F) ip = 0;
            sa += F(o, f32, 0x3C) * pa[i + jm * 0x20];
            sb += F(o, f32, 0x3C) * pb[i + jm * 0x20];
            sa += F(o, f32, 0x3C) * pa[ip + j * 0x20];
            sb += F(o, f32, 0x3C) * pb[ip + j * 0x20];
            sa += F(o, f32, 0x3C) * pa[im + j * 0x20];
            sb += F(o, f32, 0x3C) * pb[im + j * 0x20];
            sa += F(o, f32, 0x3C) * pa[i + jp * 0x20];
            sb += F(o, f32, 0x3C) * pb[i + jp * 0x20];
            sa -= 4.0f * (F(o, f32, 0x3C) * pa[k]);
            sb -= 4.0f * (F(o, f32, 0x3C) * pb[k]);
            F(o, f32*, 0x48)[k] += sa;
            F(o, f32*, 0x4C)[k] += sb;
            F(o, f32*, 0x40)[k] += F(o, f32, 0x3C) * F(o, f32*, 0x48)[k];
            F(o, f32*, 0x44)[k] += F(o, f32, 0x3C) * F(o, f32*, 0x4C)[k];
            if (i == 0 || i == 0x1F) F(o, f32*, 0x40)[k] = 0.0f;
            if (j == 0 || j == 0x1F) F(o, f32*, 0x44)[k] = 0.0f;
        }
    }
    {
        u8* t = F(o, u8*, 0x58);
        u8* d = F(o, u8*, 0x5C);
        for (j = 0; j < 0x20; j++) {
            for (i = 0; i < 0x20; i++) {
                int k = i + j * 0x20;
                u8* q = d + (((j >> 2) * 0x80 + (j & 3) * 4) + ((i >> 2) * 0x10 + (i & 3))) * 2;
                int a = (int)(127.0f * (1.0f + F(o, f32*, 0x40)[k]));
                int b = (int)(127.0f * (1.0f + F(o, f32*, 0x44)[k]));
                q[0] = a;
                q[1] = b;
            }
        }
        DCFlushRange(d, 0x800);
        F(o, u8*, 0x5C) = t;
        F(o, u8*, 0x58) = d;
    }
}
}
