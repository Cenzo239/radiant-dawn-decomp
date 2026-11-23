/* symcheck: r21 review, flag was an artefact. fn_8001AB10: (a) stale r5 before fn_80304C74 (reads r3, r4). See
   docs/SCHED_REVIEW.md. */
/* Round 20, functionally equal (check_regs.py: sched): fn_8001AB10. Self-contained. fn_80017D6C.c with exported bodies removed plus the draft from wip/fn_8001AB10.c. Moved (harmless): the four byte stores that unpack the colour word into a stack GXColor and the argument setup (subi r4, addi r3) between them are interleaved differently. */
#include "game/rA_800068A0/types.h"

/* GActor continuation: animation drivers, display-list hooks, and the
 * resource loaders that relocate GMatSet pointers. */

typedef struct GColor { u8 r, g, b, a; } GColor;

typedef struct GChan {
    f32 a, b;
    u8 pad[0xC];
} GChan;

typedef struct GAnimInfo {
    u8 pad[6];
    u16 n;
} GAnimInfo;

typedef struct GAnimState {
    u8 pad[0x30];
    GAnimInfo* info;
    GChan* chans;
} GAnimState;

typedef struct GA {
    u32 flags;       /* 0x00 */
    u32 x4;
    u8 r, g, b, a;   /* 0x08 */
    u8 pad0C[0x54 - 0xC];
    GAnimState* x54; /* 0x54 */
    u8 pad58[4];
    f32 x5C;         /* 0x5C */
    u8 pad60[0x7C - 0x60];
    void* x7C;       /* 0x7C */
    u8 pad80[2];
    u8 x82;          /* 0x82 */
} GA;

extern void fn_80010788(int, u8, void*, void*);
extern void fn_80017B08(GA*);

#pragma push
#pragma auto_inline off

void fn_80017D6C(GA* a);

void fn_80017D94(GA* a);

#pragma pop

void fn_80017DA8(GA* a, f32 v);


typedef struct GRes44 {
    u8 x0[0x14];
    s32 start;
    s32 end;
} GRes44;

extern GRes44* fn_80007F10(GA*);
extern f32 fn_800081B4(GA*);
extern f32 fn_80006D08(GA*);
extern void fn_800081D4(GA*);
extern void fn_800158FC(GA*);
extern void fn_800088A0(GA*, f32);
extern void fn_8000866C(GA*, f32);
void fn_80017DF0(GA* a);


typedef struct GReloc {
    u32 a, b;
} GReloc;

typedef struct GMatSet {
    u8 pad[0x34];
    u8* entries;
    u8 pad38[0x48 - 0x38];
    GReloc* reloc;
    u8 pad4C[0x54 - 0x4C];
    u16 count;
} GMatSet;

extern u32 fn_8023F7B8(void*);
extern GMatSet* fn_80075FB4(void*, int);
extern void fn_80012430(void*);
extern void fn_800150F4(GMatSet*);
GMatSet* fn_80017F10(void* id);

GMatSet* fn_80017FD0(void* id, int f);


typedef struct GRes48 {
    u8 pad[0x3C];
    void* x3C;
    void* x40;
    void* x44;
} GRes48;

extern GRes48* fn_80007F3C(GA*);
extern void fn_800183F0(GA*);
extern void fn_80018434(GA*);
extern void fn_80018478(GA*);
void fn_800180F0(GA* a);


extern void fn_8001A4E8(GA*);
extern void fn_8001A9B4(GA*);
extern void fn_8001B194(GA*);
extern int fn_80018208(GA*, int);
extern void fn_80018888(GA*, int);
extern void fn_8001A218(int, GA*);
void fn_8001A610(GA* a);

void fn_8001A9B4(GA* a);

void fn_8001AA84(GA* a);

void fn_8001B194(GA* a);

void fn_8001B254(GA* a);

asm void fn_8001D014(u32 x);

asm void fn_8001D01C(u32 x);

f32 fn_8001E010(s8 x);

int fn_8001E044(f32 x);

int fn_8001E094(f32 x);


typedef struct FVec { f32 x, y, z; } FVec;
typedef struct SVec { s16 x, y, z; } SVec;

static inline f32 fx2f(s16 v) { return 0.0078125f * v; }
void fn_8001E0B4(FVec* o, const SVec* s);


typedef unsigned long long u64;
typedef union U { struct { s16 x, y, z; } s; u64 v; } U;
typedef struct S6 { s16 x, y, z; } S6;
static inline s16 f2fx(f32 v) { return 128.0f * v; }
S6 fn_8001E144(const FVec* p);


extern int lbl_804CB0A8;
extern int lbl_804CB0AC;
extern int lbl_804CB0B0;
extern void fn_80079978(int);
extern int fn_80079940(int, int);
extern void DCFlushRange(int, int);

void fn_80020E7C(int size);

extern void fn_80011C4C(int, FVec*, FVec*);
int fn_800215D4(const FVec* a, const FVec* b, FVec* mn, FVec* mx);


extern void fn_803031CC(void);
extern void fn_80302B80(int, int);
extern void fn_80303200(int, int, int, int, int);
extern void fn_80021B2C(int);
extern void fn_80021A08(int, int, int, int, int, int, int);
extern void fn_80021958(int, GColor);
extern void fn_80021BF4(int);
extern void fn_80021CB4(int, int, int, int);
extern void fn_80021EF8(int, int);
extern void fn_80021C34(int);
extern void fn_80021F7C(int, int, int, int);
extern void fn_80021C74(int);
extern void fn_80306B24(int);
extern void fn_80304314(int, int, int);

#define GXFIFO_S16 (*(volatile s16*)0xCC008000)

void fn_80022B54(s16 z, int w, int h);


typedef struct LinkList { u8 x0; u8 pad; u8 n; u8 pad3[5]; GA** items; } LinkList;
typedef struct GA7C { u8 pad[0x7C]; LinkList* list; } GA7C;
extern void fn_80015070(GRes48*, int, int);

#pragma use_lmw_stmw on

void fn_8001A4E8(GA* a);

#pragma use_lmw_stmw off

extern u8* fn_80020E74(void);
extern int fn_8030585C(int, int, int, int, int);
extern int fn_80020EFC(void);
extern void fn_80304C74(GColor*, u32);
extern void fn_8001F4D8(int, int, int, int, int, int, void*, int, u8);
extern u32 fn_8002177C(void);

static inline void setClear(u32 v) {
    GColor c;
    c.a = v;
    c.r = v >> 24;
    c.g = v >> 16;
    c.b = v >> 8;
    fn_80304C74(&c, 0xFFFFFF);
}

int fn_8001AB10(void);

#pragma use_lmw_stmw off
/* ---- from rA_800068A0/wip/fn_8001AB10.c ---- */
/* fn_8001AB10: near miss, 8 of 72 words differ. Depends on types and helpers from ../fn_80017D6C.c; goes there in address order. */
int fn_8001AB10(void) {
    u8* buf = fn_80020E74();
    u8* p = buf + fn_8030585C(0x130, 0xE0, 6, 0, 0);
    if (buf == 0) {
        return 0;
    }
    {
        int sz = fn_8030585C(0x130, 0xE0, 6, 0, 0);
        sz += fn_8030585C(0x260, 0x1C0, 6, 0, 0);
        if (sz > fn_80020EFC()) {
            return 0;
        }
    }
    {
        u32 z = 0;
        fn_80304C74((GColor*)&z, 0xFFFFFF);
    }
    fn_8001F4D8(0, 0, 0x260, 0x1C0, -1, -1, p, 6, 1);
    setClear(fn_8002177C());
    return 1;
}