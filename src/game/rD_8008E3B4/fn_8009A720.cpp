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
#if TARGET_PC
FE10_PROTO void fn_801D0BAC(void* ctx, ptr32<const void>, p32arg);
#else
void fn_801D0BAC(void* ctx, void* stack, int n);
#endif
void fn_801D0C48(void* ctx, void* v);
#if TARGET_PC
FE10_PROTO int fn_801D0C88(void* ctx, void* v);
#else
void fn_801D0C88(void* ctx, void* v);
#endif
void fn_80081A90(void* p);
extern u8 lbl_80381940[0x14];
extern u8 lbl_803CAB38[];
u8* fn_80060728(void* p);
u32 fn_8017FA1C(void);
void* fn_801116B8(void* item);
void* fn_8010B1D8(void* x);
void fn_801130D4(void* a, void* b, int k, int v);

ScriptProc* fn_8009A720(void* entry, void* a, void* b)
{
    ScriptProc* proc = (ScriptProc*)fn_80081050(lbl_80381940, fn_8009E898());
    void* stack = fn_800791B0(0x100);
    proc->stack = stack;
    fn_801D0BAC(proc->ctx, stack, 0x40);
    proc->self = proc;
    fn_801D0C48(proc->ctx, a);
    fn_801D0C48(proc->ctx, b);
    fn_801D0C88(proc->ctx, entry);
    if (proc->running == 0) {
        fn_80081A90(proc);
    }
    return proc;
}

#pragma push
#pragma use_lmw_stmw on
ScriptProc* fn_8009A7DC(void* entry, void* a, void* b, void* c)
{
    ScriptProc* proc = (ScriptProc*)fn_80081050(lbl_80381940, fn_8009E898());
    void* stack = fn_800791B0(0x100);
    proc->stack = stack;
    fn_801D0BAC(proc->ctx, stack, 0x40);
    proc->self = proc;
    fn_801D0C48(proc->ctx, a);
    fn_801D0C48(proc->ctx, b);
    fn_801D0C48(proc->ctx, c);
    fn_801D0C88(proc->ctx, entry);
    if (proc->running == 0) {
        fn_80081A90(proc);
    }
    return proc;
}

ScriptProc* fn_8009A890(void* entry, void* a, void* b, void* c, void* d)
{
    ScriptProc* proc = (ScriptProc*)fn_80081050(lbl_80381940, fn_8009E898());
    void* stack = fn_800791B0(0x100);
    proc->stack = stack;
    fn_801D0BAC(proc->ctx, stack, 0x40);
    proc->self = proc;
    fn_801D0C48(proc->ctx, a);
    fn_801D0C48(proc->ctx, b);
    fn_801D0C48(proc->ctx, c);
    fn_801D0C48(proc->ctx, d);
    fn_801D0C88(proc->ctx, entry);
    if (proc->running == 0) {
        fn_80081A90(proc);
    }
    return proc;
}
#pragma pop

int fn_8009A954(void** p)
{
    if (p == NULL || p == NULL) {
        return 0;
    }
    if (*p != lbl_80381940) {
        return 0;
    }
    fn_80081A90(p);
    return 1;
}

#if TARGET_PC
int fn_8009A9A8(void* entry)
{
    u8 ctx[0x28];
    u8 stack[0x100];
    fn_801D0BAC(ctx, stack, 0x40);
    return fn_801D0C88(ctx, entry);
}
#else
void fn_8009A9A8(void* entry)
{
    u8 ctx[0x28];
    u8 stack[0x100];
    fn_801D0BAC(ctx, stack, 0x40);
    fn_801D0C88(ctx, entry);
}
#endif

struct BF2 { u32 top : 2; u32 rest : 30; };

int fn_8009AAB4(int x, int v)
{
    switch (x) {
    case 0:
        ((BF2*)fn_80060728(lbl_803CAB38))->top = v;
        return 1;
    default:
        return 0;
    }
}

int fn_8009AB0C(int x)
{
    switch (x) {
    case 0:
        return ((BF2*)fn_80060728(lbl_803CAB38))->top;
    default:
        return 0;
    }
}


int fn_8009ABE0(int army)
{
    u8* u = *(u8**)(lbl_804CB814 + army * 0xc);
    while (u != NULL) {
        u8* next = *(u8**)(u + 0xe8);
        u8* it = u + 0x1bc;
        int i;
        for (i = 0; i < 7; i++, it += 0x28) {
            if (it == NULL || *(void**)it == NULL) {
                break;
            }
            if (*(u32*)((u8*)fn_801116B8(it) + 4) & 0x11) {
                u8* d = *(u8**)it;
                it[4] = d != NULL ? d[0x1b] : 0;
            }
        }
        u = next;
    }
    return 1;
}

int fn_8009AD3C(void* a, void* b, int v)
{
    void* x = fn_8010B1D8(a);
    void* y = fn_8010B1D8(b);
    if (x == NULL) {
        return 0;
    }
    if (y == NULL) {
        return 0;
    }
    if (v > 0x7f) {
        v = 0x7f;
    }
    if (v < -0x80) {
        v = -0x80;
    }
    fn_801130D4(x, y, 1, (s8)v);
    return 1;
}

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
#if TARGET_PC
FE10_PROTO void fn_8000BF68(void* p, p32arg);
FE10_PROTO void fn_8000C3C4(void* p, p32arg);
#else
void fn_8000BF68(void* p, int v);
void fn_8000C3C4(void* p, int v);
#endif
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
#if TARGET_PC
FE10_PROTO void fn_8023F1A8(ptr32<const void>);
#else
void fn_8023F1A8(void* p);
#endif
void fn_800E4548(void);
#if TARGET_PC
FE10_PROTO void fn_80044AF0(void* cls, p32arg);
#else
void fn_80044AF0(void* cls, int k);
#endif
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

void* fn_8009C464(void* parent)
{
    return fn_8009E554(lbl_80364968, parent);
}

void* fn_8009C4BC(void* parent)
{
    return fn_80081194(lbl_80381960, parent);
}

void fn_8009C574(void* proc)
{
    if (lbl_804CB5B8->getTrig() & 0xFFF0) {
        fn_80083B78(proc);
    }
}

int fn_8009C5C4(void)
{
    fn_80272404(fn_8009E898());
    setFlag1C(fn_800C3558());
    return 1;
}

int fn_8009C5F8(void)
{
    fn_8028A4C0(fn_8009E898());
    setFlag1C(fn_800C3558());
    return 1;
}

static inline void clr54(u8* p)
{
    *(int*)(p + 0x54) = 0;
}

int fn_8009C62C(void)
{
    clr54((u8*)fn_80081194(lbl_803819D8, fn_8009E898()));
    setFlag1C(fn_800C3558());
    return 1;
}

int fn_8009C674(void)
{
    fn_8027F84C(fn_8009E898());
    setFlag1C(fn_800C3558());
    return 1;
}

int fn_8009C6A8(void)
{
    fn_80287188(fn_8009E898());
    setFlag1C(fn_800C3558());
    return 1;
}

/* Fixes the string pool order. */
void rD12_strpool_8009C76C(void)
{
    const char* volatile s;
    s = "ex1"; s = "ex2"; s = "%s%s";
}

void fn_8009C76C(MovieProc* p)
{
    void* x;
    u8* a;
    if (p->model == NULL || *(void**)(p->model + 0x44) == NULL) {
        return;
    }
    fn_80312318(p->model + 0x10);
    fn_800081D4(p->model);
    fn_80007C58(p->model);
    fn_8000BF68(p->model, 0);
    fn_8000C3C4(p->model, 0);
    p->flags &= ~1;
    a = *(u8**)(p->model + 0x44);
    if (a != NULL && *(f32*)(p->model + 0x58) >= (f32)*(int*)(a + 0x18)) {
        p->flags |= 1;
    }
    if (fn_80008EB4(p->model)) {
        fn_800F199C(p->model, p);
        fn_800F1820(p->model, p);
        fn_800F15AC(p->model, -10000.0f, -10000.0f, -10000.0f);
        x = NULL;
        if (fn_80008C98(p->model, 0x50)) {
            x = fn_801790F4(p->model, "ex1", "ex2", p);
        }
        if (x != NULL) {
            fn_80177A5C(x, p->model);
        }
        if (fn_80008C98(p->model, 0x51)) {
            fn_80179180();
            fn_80009974(p->model);
        }
    }
    if (lbl_804CB5B8->getTrig() & 0x10) {
        p->flags ^= 2;
    }
}

void fn_8009C990(MovieProc* p)
{
    if (fn_8013B9A8()) {
        fn_8013B974();
    }
    if (p->model != NULL && *(void**)(p->model + 0x44) != NULL) {
        fn_8000BE20(*(void**)(p->model + 0x44));
        *(void**)(p->model + 0x44) = NULL;
    }
    if (p->model != NULL) {
        fn_80006EE0(p->model);
    }
    if (p->res != NULL) {
        fn_8023F1A8(p->res);
    }
    p->res = NULL;
    p->model = NULL;
    p->flags = 0;
    fn_800E4548();
}

void fn_8009CA24(void* proc)
{
    if (fn_80083B84(lbl_80381A18)) {
        fn_80083B78(proc);
    }
}

int fn_8009CA68(void)
{
    if (lbl_804CB700 & 0x8001) {
        return 0;
    }
    lbl_804CB5B8->setMask(0xBFE0);
    lbl_804CB700 |= 0x4000;
    fn_80044AF0(lbl_80381A18, 3);
    fn_80081194(lbl_80381A3C, fn_8009E898());
    setFlag1C(fn_800C3558());
    return 1;
}

static inline void mkPath(char* buf, const char* name, const char* ext)
{
    fn_80290DDC(buf, "%s%s", name, ext);
}

int fn_8009CAF4(char* name)
{
    char buf[0x40];
    MovieProc* p;
    u8* q;
    if (lbl_804CB700 & 0x8001) {
        return 0;
    }
    p = (MovieProc*)fn_80083B84(lbl_80381A18);
    if (p != NULL) {
        fn_8023FC00();
        mkPath(buf, name, ".cmp");
        p->res = fn_8023F1A4(buf, 0);
        p->model = fn_80006E1C();
        mkPath(buf, name, ".gs");
        *(void**)(p->model + 0x48) = fn_80017F10(buf);
        mkPath(buf, name, ".g");
        *(void**)(p->model + 0x40) = fn_8000EB68(buf);
        mkPath(buf, name, ".tpl");
        *(void**)(p->model + 0x4c) = fn_8001D3B4(buf);
        fn_80006F20(p->model);
        *(u32*)p->model |= 0x20;
        fn_8013B920(4);
        q = (u8*)fn_8013B9A8();
        fn_80139A7C(q, 0, 0);
        *(void**)(*(u8**)(q + 0x18) + 0x7c) = p->model;
    }
    return 1;
}

int fn_8009CC50(char* name)
{
    char buf[0x40];
    MovieProc* p;
    if (lbl_804CB700 & 0x8001) {
        return 0;
    }
    p = (MovieProc*)fn_80083B84(lbl_80381A18);
    if (p != NULL && p->model != NULL) {
        if (p->model != NULL && *(void**)(p->model + 0x44) != NULL) {
            fn_8000BE20(*(void**)(p->model + 0x44));
            *(void**)(p->model + 0x44) = NULL;
        }
        mkPath(buf, name, ".ga");
        *(void**)(p->model + 0x44) = fn_8000BD3C(buf);
        fn_8000866C(p->model, 0.0f);
        fn_8023FC00();
    }
    return 1;
}

int fn_8009CD1C(char* name)
{
    char buf[0x40];
    if (lbl_804CB700 & 0x8001) {
        return 0;
    }
    if (fn_80083B84(lbl_80381A18)) {
        mkPath(buf, name, ".ga");
        fn_8023F1A0(buf, 0);
    }
    return 1;
}

int fn_8009CDF8(void)
{
    void* p;
    fn_8014C64C();
    p = fn_80083B84(lbl_80381A18);
    if (p != NULL) {
        fn_80081A90(p);
        setFlag1C(fn_800C3558());
    }
    lbl_804CB5B8->resetMask(0xFFF0);
    lbl_804CB700 &= ~0x4000;
    return 1;
}

int fn_8009CE68(int v0)
{
    s8 v = v0;
    *(s8*)(fn_80060728(lbl_803CAB38) + 0x23) = v;
    return 1;
}

}
