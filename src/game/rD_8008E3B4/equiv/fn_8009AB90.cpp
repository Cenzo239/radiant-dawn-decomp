/* EQUIVALENT (register-only, round 19): fn_8009AB90 at regs level (1 word: fmuls operand order); round 12 fragment made self-contained. */
/* Script commands and procs, 0x8009A720..0x8009CE68. */
#include "game/rD_8008E3B4/script.h"

class PadObj2 {
public:
#define VSLOT(n) virtual void v##n();
    VSLOT(00) VSLOT(01) VSLOT(02) VSLOT(03) VSLOT(04) VSLOT(05) VSLOT(06) VSLOT(07)
    VSLOT(08) VSLOT(09) VSLOT(10) VSLOT(11) VSLOT(12) VSLOT(13) VSLOT(14) VSLOT(15)
    virtual u32 getTrig();             /* 0x48 */
    VSLOT(17) VSLOT(18) VSLOT(19) VSLOT(20) VSLOT(21) VSLOT(22) VSLOT(23)
    VSLOT(24) VSLOT(25) VSLOT(26) VSLOT(27) VSLOT(28) VSLOT(29) VSLOT(30) VSLOT(31)
    VSLOT(32)
    virtual void setMask(u32 mask);    /* 0x8C */
    virtual void resetMask(u32 mask);  /* 0x90 */
};

extern "C" {

extern PadObj2* lbl_804CB5B8;

typedef struct ScriptProc {
    u8 pad0[0x30];
    u8 ctx[0xc];   /* 0x30: script context */
    int running;   /* 0x3C */
    u8 pad40[0x10];
    void* self;    /* 0x50 */
    void* stack;   /* 0x54 */
} ScriptProc;

void fn_80079474(void* p);
void* fn_800791B0(u32 size);
void fn_801D0BAC(void* ctx, void* stack, int n);
void fn_801D0C48(void* ctx, void* v);
void fn_801D0C88(void* ctx, void* v);
void fn_80081A90(void* p);
extern u8 lbl_80381940[0x14];
extern u8 lbl_803CAB38[];
u8* fn_80060728(void* p);
u32 fn_8017FA1C(void);
void* fn_801116B8(void* item);
void* fn_8010B1D8(void* x);
void fn_801130D4(void* a, void* b, int k, int v);
ScriptProc* fn_8009A720(void* entry, void* a, void* b);


#pragma push
#pragma use_lmw_stmw on

ScriptProc* fn_8009A7DC(void* entry, void* a, void* b, void* c);

ScriptProc* fn_8009A890(void* entry, void* a, void* b, void* c, void* d);

#pragma pop

int fn_8009A954(void** p);

void fn_8009A9A8(void* entry);


struct BF2 { u32 top : 2; u32 rest : 30; };
int fn_8009AAB4(int x, int v);

int fn_8009AB0C(int x);

int fn_8009ABE0(int army);

int fn_8009AD3C(void* a, void* b, int v);


#pragma pool_strings on
typedef struct MovieProc {
    u8 pad0[0x30];
    u8* model;  /* 0x30 */
    void* res;  /* 0x34 */
    u16 flags;  /* 0x38 */
} MovieProc;

extern u8 lbl_80364968[];
extern u8 lbl_80381960[];
extern u8 lbl_803819D8[];
extern u8 lbl_80381A18[];
extern u8 lbl_80381A3C[];
extern char lbl_803649D4[];
void* fn_8009E554(void* cls, void* parent);
void fn_80083B78(void* proc);
void* fn_80083B84(void* cls);
void fn_80272404(void* p);
void fn_8028A4C0(void* p);
void fn_8027F84C(void* p);
void fn_80287188(void* p);
void fn_80312318(void* p);
void fn_800081D4(void* p);
void fn_80007C58(void* p);
void fn_8000BF68(void* p, int v);
void fn_8000C3C4(void* p, int v);
int fn_80008EB4(void* p);
void fn_800F199C(void* m, void* p);
void fn_800F1820(void* m, void* p);
void fn_800F15AC(void* m, f32 x, f32 y, f32 z);
int fn_80008C98(void* m, int k);
void* fn_801790F4(void* m, const char* a, const char* b, void* p);
void fn_80177A5C(void* x, void* m);
void fn_80179180(void);
void fn_80009974(void* m);
void* fn_8013B9A8(void);
void fn_8013B974(void);
void fn_8000BE20(void* p);
void fn_80006EE0(void* p);
void fn_8023F1A8(void* p);
void fn_800E4548(void);
void fn_80044AF0(void* cls, int k);
void fn_8023FC00(void);
int fn_80290DDC(char* buf, const char* fmt, ...);
void* fn_8023F1A4(char* name, int k);
void* fn_8023F1A0(char* name, int k);
u8* fn_80006E1C(void);
void* fn_80017F10(char* name);
void* fn_8000EB68(char* name);
void* fn_8001D3B4(char* name);
void* fn_8000BD3C(char* name);
void fn_80006F20(void* m);
void fn_8013B920(int k);
void fn_80139A7C(void* p, int a, int b);
void fn_8000866C(void* m, f32 v);
void fn_8014C64C(void);
void* fn_8009C464(void* parent);

void* fn_8009C4BC(void* parent);

void fn_8009C574(void* proc);

int fn_8009C5C4(void);

int fn_8009C5F8(void);


static inline void clr54(u8* p)
{
    *(int*)(p + 0x54) = 0;
}
int fn_8009C62C(void);

int fn_8009C674(void);

int fn_8009C6A8(void);


/* Fixes the string pool order. */
void rD12_strpool_8009C76C(void)
{
    const char* volatile s;
    s = "ex1"; s = "ex2"; s = "%s%s";
}
void fn_8009C76C(MovieProc* p);

void fn_8009C990(MovieProc* p);

void fn_8009CA24(void* proc);

int fn_8009CA68(void);


static inline void mkPath(char* buf, const char* name, const char* ext)
{
    fn_80290DDC(buf, "%s%s", name, ext);
}
int fn_8009CAF4(char* name);

int fn_8009CC50(char* name);

int fn_8009CD1C(char* name);

int fn_8009CDF8(void);

int fn_8009CE68(int v0);


}

/* ---- from build/tmp/r19hpbs/frag_dab90.cpp ---- */
extern "C" {
/* fn_8009AB90 (from ../fn_8009A720.cpp): 1 of 19 words: want fmuls f0,f1,f0 (same open puzzle as fn_8009A3D8). Needs fn_8017FA1C. */
int fn_8009AB90(void)
{
    return (int)(16.666666f * fn_8017FA1C());
}
}
