/* Round 20, functionally equal (check_regs.py: sched): fn_80075714. Self-contained. fn_8006E278.cpp with exported bodies removed plus the draft from wip/near2.cpp. Moved (harmless): in cases 1 and 3 the original emits addi x; addi y; li id, ours li id; addi y; addi x (three independent register updates). The switch jump table is compiler generated and not reference-checked. */
/* Window and menu sprite drawing built on fn_8006E098: frames, bars, unit panels, range stats. */
#include "game/rO_80065D64/types.h"
#pragma auto_inline off
struct Tex {
    u32 d[8];
    u16 w;
    u16 h;
};
extern "C" {
extern void* lbl_804CB58C;
extern void fn_80006A64(void*, Tex*, u16);
extern u16 fn_80305DF8(Tex*);
extern u16 fn_80305E0C(Tex*);
extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E174(Tex*, int);
extern void fn_8007E720(f32);
extern void fn_8007E4E4(f32, f32, f32, f32);
extern void fn_8007E7DC(int);
extern void fn_800800D4(int);
extern void fn_80080330(f32, f32);
extern void fn_80080388(f32, f32, f32, f32);
extern void fn_80080410(f32, f32, f32, f32);
extern void fn_800804D4(int, int, int, int);
extern void fn_80080C24(int);
extern void fn_80080308(void);
extern Tex fn_8006E098(int x, int y, int w, int h, int u0, int v0, int u1, int v1, int color, u8 alpha, u16 id, int flags);

static inline void TexLoad(Tex* t, u16 id) {
    fn_80006A64(lbl_804CB58C, t, id);
    t->w = fn_80305DF8(t);
    t->h = fn_80305E0C(t);
}

static inline Tex Spr(int x, int y, int w, int h, int color, u8 alpha, u16 id, int flags) {
    Tex t;
    TexLoad(&t, id);
    fn_8007E154();
    fn_8007E174(&t, 0x11);
    fn_8007E164();
    if (w == -1) {
        w = t.w;
    }
    if (h == -1) {
        h = t.h;
    }
    return fn_8006E098(x, y, w, h, 0, 0, t.w, t.h, color, alpha, id, flags);
}

static inline Tex Spr3(int x, int y, int color, u8 alpha, u16 id, int flags) {
    Tex t0;
    TexLoad(&t0, id);
    int w = t0.w;
    int h = t0.h;
    Tex t;
    TexLoad(&t, id);
    fn_8007E154();
    fn_8007E174(&t, 0x11);
    fn_8007E164();
    if (w == -1) {
        w = t.w;
    }
    if (h == -1) {
        h = t.h;
    }
    return fn_8006E098(x, y, w, h, 0, 0, t.w, t.h, color, alpha, id, flags);
}
void fn_80072488(int x, int y, int a, int b, int f, int s);

void fn_80072EE0(int x, int y, int w);


#if TARGET_PC
extern FE10_PROTO u8 fn_801076D0(void*);
#else
extern u8 fn_801076D0(int);
#endif
#pragma use_lmw_stmw on
#pragma use_lmw_stmw off

extern void fn_80071C30(int, int);
extern int fn_801246A4(void*);
extern void* fn_800C6210(int, int);
extern void* fn_8007E4C4(int);
extern int fn_8028C1A0(f32);
extern void fn_8007E74C(void (*)(int, int), int);
extern void fn_800C4DDC(int, int, int, void*);
extern void fn_8007E7B4(void);
extern char* fn_80118C44(int);
extern char* fn_80118F00(int);
extern u8 fn_80126B0C(u8*);
extern char* strcpy(char*, const char*);
extern void fn_800C429C(void*);
void fn_80071C44(u8*, int, int, int);
extern int fn_80127A90(u8*);
extern int fn_8011B8A4(u8*);
extern int fn_80290DDC(char*, const char*, ...);
extern int fn_800CA3DC(f32, const char*, int);
extern void fn_801C6DA0(f32, f32, int, const char*);
extern char lbl_803622BC[];
void fn_800722B8(u8* u, int x, int y);

void fn_8006E278(int x, int y, int h);


#pragma use_lmw_stmw on

void fn_80074EB4(int x, int y, int w, u8 a);

#pragma use_lmw_stmw off

extern void fn_801BCA94(int);
extern int* fn_80030CBC(int);
extern int fn_8012BA20(int, int);
extern int fn_80291188(const char*, const char*);
extern void fn_800CB3A8(f32, f32, s16, s16, int, int, int, const char*, ...);
void fn_80073374(int u, const char* name, int cur, int max, u32 f, u32 g, f32 x, f32 y);


extern char* fn_800D0864(int);
extern void fn_801BCA5C(f32);
#pragma use_lmw_stmw off

void fn_80074718(int x, int y, int mid);


#pragma use_lmw_stmw on

void fn_80074A64(int x, int y, u8 a, int k);

#pragma use_lmw_stmw off

void fn_800718F0(u8* u, int x, int y, int f);


class DB { u8 pad[0x44]; };
class Drawer : public DB {
public:
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual void v18(int, int, int);
};
extern u8 lbl_803E7290[];
static inline int Icon(u16* p, u32 m, f32 x, f32 y, int id) {
    if (*p & m) {
        ((Drawer*)lbl_803E7290)->v18(x, y, id);
        return 1;
    }
    return 0;
}
void fn_80073688(u16* p, f32 x, f32 y);

void fn_80071C44(u8* u, int x, int y, int id);


#pragma use_lmw_stmw on

void fn_80075124(int x, int y, int w, int h);

#pragma use_lmw_stmw off

void fn_80070C64(f32 x, f32 y, f32 w, f32 h);


extern s16 fn_801237EC(u8*);
void fn_800720F4(u8* u, int x, int y);


extern s64 OSGetTime(void);
extern s64 fn_8028C418(s64, s64);
extern s64 fn_8028C634(s64, s64);
extern f32 fn_8028C764(s64);
extern double fn_80295940(double);
extern double fn_80295534(double);
extern int fn_8017F990(int, int);
void fn_8006F1B4(int x, int y, int f);

void fn_8006F6A4(int x, int y, int f);


extern int fn_801D09F0(void);
extern void* lbl_804CB580;
extern u8 lbl_803C8E80[];
extern int* fn_80030CF4(u8*);
extern u32* fn_801116B8(int*);
extern u8 fn_801107C0(int, u8*);
extern u8 fn_801107A0(int, u8*);
static inline void Spr3Z(int x, int y, int color, u8 alpha, u16 id, int& w, int& z) {
    Tex t0;
    TexLoad(&t0, id);
    w = t0.w;
    int h = t0.h;
    Tex t;
    TexLoad(&t, id);
    fn_8007E154();
    fn_8007E174(&t, 0x11);
    fn_8007E164();
    if (w == -1) {
        w = t.w;
    }
    if (h == -1) {
        h = t.h;
    }
    fn_8006E098(x, y, w, h, 0, 0, t.w, t.h, color, alpha, id, z = 0);
}
void fn_80073374(int u, const char* name, int cur, int max, u32 f, u32 g, f32 x, f32 y);
void fn_80073688(u16* p, f32 x, f32 y);
void fn_8007309C(int k, f32 x, f32 y);

void fn_8006FED4(f32 x, f32 y, f32 w, f32 h);

void fn_80070688(f32 x, f32 y, f32 w, f32 h);

}

#pragma use_lmw_stmw on
/* ---- from rO_80065D64/wip/near2.cpp ---- */
extern "C" {
/* Round 11 near misses, not compiled. Helpers: Spr3 in fn_8006E278.cpp; GrowOf, PICK, GetD, SetD in fn_8006C2D0.cpp. */

/* 4 to 6 of 88 words differ: in cases 1 and 3 the original has addi x; addi y; li id. The compiler always
   emits li id; addi y; addi x, whatever the statement order, parameter types or inline form. */
void fn_80075714(
#if TARGET_PC
int x, int y, void* k
#else
int x, int y, int k
#endif
) {
    int id;
    int v = fn_801076D0(k);
    if (v == 2) {
        return;
    }
    switch (v) {
    case 0:
        id = 0x30;
        break;
    case 4:
        id = 0x33;
        break;
    case 1:
        x = x + 4;
        y = y + 4;
        id = 0x31;
        break;
    case 3:
        x = x + 4;
        y = y + 4;
        id = 0x32;
        break;
    case 2:
    default:
        break;
    }
    Spr3(x, y, 1, 0xFF, id, 0);
    //
}
}
