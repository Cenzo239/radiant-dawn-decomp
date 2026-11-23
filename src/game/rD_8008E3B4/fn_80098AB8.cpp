#include "game/rD_8008E3B4/script.h"

#define VSLOT(n) virtual void v##n();
class PadObj {
public:
    VSLOT(00) VSLOT(01) VSLOT(02) VSLOT(03) VSLOT(04) VSLOT(05) VSLOT(06) VSLOT(07)
    VSLOT(08) VSLOT(09) VSLOT(10) VSLOT(11) VSLOT(12) VSLOT(13) VSLOT(14) VSLOT(15)
    virtual u32 getTrig();             /* 0x48 */
    VSLOT(17) VSLOT(18) VSLOT(19) VSLOT(20) VSLOT(21) VSLOT(22) VSLOT(23)
    VSLOT(24) VSLOT(25) VSLOT(26) VSLOT(27) VSLOT(28) VSLOT(29) VSLOT(30) VSLOT(31)
    VSLOT(32)
    virtual void setMask(u32 mask);    /* 0x8C */
    virtual void resetMask(u32 mask);  /* 0x90 */
};

class SndObj {
public:
    virtual void v08();
    virtual void v0C();
    virtual int v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void v24(int v);
    virtual void v28(int v);
    virtual void v2C(int v);
    virtual void v30();
    virtual void v34();
    virtual void v38(f32 vol, f32 time);
};

extern "C" {

void fn_80253EE4(char* name, f32 v);
void fn_802549C4(char* name, Vec* pos, f32 v);
void fn_80255060(char* name, f32 v);
f32 fn_801142F0(void* map, f32 x, f32 y);

int fn_80098AB8(char* name)
{
    if (!IsValidPtr(name)) {
        return 0;
    }
    if (lbl_804CB700 & 3) {
        return 0;
    }
    fn_80253EE4(name, 0.0f);
    return 1;
}

int fn_80098B2C(char* name, int x, int y, int z)
{
    Vec pos;
    Vec tmp;
    if (!IsValidPtr(name)) {
        return 0;
    }
    if (lbl_804CB700 & 3) {
        return 0;
    }
    pos.x = 0.5f + x;
    pos.y = 0.5f + y;
    pos.z = z;
    if (z <= -1000) {
        pos.z = fn_801142F0(lbl_803EC898, x, y);
    }
    tmp = pos;
    fn_802549C4(name, &tmp, 0.0f);
    return 1;
}

int fn_80098C54(char* name)
{
    if (!IsValidPtr(name)) {
        return 0;
    }
    fn_80255060(name, 0.0f);
    return 1;
}


int fn_802501A4(char* name);
void fn_80250E38(int ch, f32 vol, f32 time);

int fn_80098CB4(char* name)
{
    if (!IsValidPtr(name)) {
        return 0;
    }
    if (lbl_804CB700 & 3) {
        return 0;
    }
    return fn_802501A4(name);
}

#define SE_VOL(name, vol)               \
int name(int t)                         \
{                                       \
    fn_80250E38(6, vol, t);             \
    return 1;                           \
}

SE_VOL(fn_80098D08, 0.5f)
SE_VOL(fn_80098D50, 1.0f)

int fn_80098D98(int t)
{
    if (t < 0) {
        t = 0;
    }
    if (lbl_804CB700 & 3) {
        t = 0;
    }
    fn_80250E38(6, 0.0f, t);
    return 1;
}

SE_VOL(fn_80098DFC, 1.0f)
SE_VOL(fn_80098E44, 1.2f)
SE_VOL(fn_80098E8C, 1.0f)


s8 fn_80252C38(char* name, f32 v);
s8 fn_80253848(char* name, Vec* pos, f32 v);

int fn_80098ED4(char* name, int v)
{
    if (!IsValidPtr(name)) {
        return -1;
    }
    if (lbl_804CB700 & 1) {
        return -1;
    }
    return fn_80252C38(name, v);
}

int fn_80098F60(char* name, int x, int y, int z, int v)
{
    Vec pos;
    Vec tmp;
    if (!IsValidPtr(name)) {
        return -1;
    }
    if (lbl_804CB700 & 1) {
        return -1;
    }
    pos.x = 0.5f + x;
    pos.y = 0.5f + y;
    pos.z = z;
    if (z <= -1000) {
        pos.z = fn_801142F0(lbl_803EC898, x, y);
    }
    tmp = pos;
    return fn_80253848(name, &tmp, v);
}


SndObj* fn_8024F484(s8 ch);

int fn_800990A4(int ch, int vol, int time)
{
    SndObj* snd;
    if (ch < 0) {
        return 0;
    }
    snd = fn_8024F484(ch);
    if (snd != NULL && snd->v10() != 0) {
        snd->v38(vol / 100.0f, time);
    }
    return 1;
}

int fn_8009916C(int ch, int t)
{
    SndObj* snd;
    if (ch < 0) {
        return 0;
    }
    snd = fn_8024F484(ch);
    if (snd != NULL && snd->v10() != 0) {
        snd->v24(t);
        return 1;
    }
    return 0;
}


s8 fn_80255368(char* name, f32 v);
void fn_802568F0(char* name, f32 v);
void fn_80256A78(f32 v);
int fn_802502E0(char* name);

int fn_800991FC(char* name)
{
    if (!IsValidPtr(name)) {
        return -1;
    }
    return fn_80255368(name, 0.0f);
}

int fn_8009925C(char* name)
{
    if (!IsValidPtr(name)) {
        return -1;
    }
    fn_802568F0(name, 0.0f);
    return 1;
}

int fn_800992BC(int t)
{
    fn_80256A78(t);
    return 1;
}

int fn_800992FC(char* name)
{
    if (!IsValidPtr(name)) {
        return 0;
    }
    if (lbl_804CB700 & 3) {
        return 0;
    }
    return fn_802502E0(name);
}


void* fn_8013B9A8(void);
#if TARGET_PC
FE10_PROTO void fn_8013AB10(void* p, p32arg);
FE10_PROTO void fn_8013ABAC(void* p, p32arg);
#else
void fn_8013AB10(void* p, int v);
void fn_8013ABAC(void* p, int v);
#endif

int fn_80099350(int v)
{
    void* p = fn_8013B9A8();
    if (p == NULL) {
        return 0;
    }
    fn_8013AB10(p, v);
    return 1;
}

int fn_80099398(int v)
{
    void* p = fn_8013B9A8();
    if (p == NULL) {
        return 0;
    }
    fn_8013ABAC(p, v);
    return 1;
}

typedef struct GameState {
    u8 pad0[0xe];
    u8 b0e;     /* 0x0E */
    u8 pad0f[2];
    u8 mode;    /* 0x11: difficulty */
} GameState;

extern u8 lbl_803CAB38[];
GameState* fn_80060728(void* t);

u8 fn_800993E0(void)
{
    return fn_80060728(lbl_803CAB38)->mode;
}

BOOL fn_8009940C(void)
{
    return fn_80060728(lbl_803CAB38)->mode == 3;
}

BOOL fn_80099444(void)
{
    return fn_80060728(lbl_803CAB38)->mode == 0;
}

BOOL fn_80099478(void)
{
    return fn_80060728(lbl_803CAB38)->mode == 1;
}

BOOL fn_800994B0(void)
{
    return fn_80060728(lbl_803CAB38)->mode == 2;
}

/* Milliseconds to frames. */
int fn_800994E8(int ms)
{
    return ms / 16.666666f;
}

void fn_800D1D14(void* p, int a, int b);

void fn_80099524(u8* p)
{
    fn_800D1D14(p + 0x30, 0, 1);
}


int fn_800D2150(void);
extern u8 lbl_803818A8[0x14];
char* strcpy(char* dst, const char* src);

void fn_80099534(void* proc)
{
    if (fn_800D2150() == 0 || (lbl_804CB700 & 1)) {
        fn_80083B78(proc);
    }
}

int fn_8009957C(char* name)
{
    u8* proc;
    if (!IsValidPtr(name)) {
        return 0;
    }
    if (lbl_804CB700 & 1) {
        return 0;
    }
    proc = (u8*)fn_80081194(lbl_803818A8, fn_8009E898());
    strcpy((char*)(proc + 0x30), name);
    setFlag1C(fn_800C3558());
    return 1;
}

void* fn_800D25D4(void* buf, const char* path);
void fn_800D1EDC(void* p, u8 mode, int a, int b);
void fn_800D2578(void* p);

void fn_80099620(u8* proc)
{
    u8 buf[0x80];
    u8 mode = fn_80060728(lbl_803CAB38)->b0e;
    fn_800D1EDC(fn_800D25D4(buf, lbl_80363B74 + 0x2e), mode, 0, 0); /* "Movie/chapter.thp" */
    fn_800D2578(*(void**)(proc + 0x54));
}


int fn_800D20EC(void);
extern u8 lbl_803818E0[0x14];

void fn_8009968C(void* proc)
{
    if (fn_800D20EC() == 0 || (lbl_804CB700 & 1)) {
        fn_80083B78(proc);
    }
}

void fn_800996D4(void)
{
}

int fn_800996D8(void* p)
{
    u8* proc;
    if (!IsValidPtr(p)) {
        return 0;
    }
    if (lbl_804CB700 & 1) {
        return 0;
    }
    proc = (u8*)fn_80081194(lbl_803818E0, fn_8009E898());
    *(void**)(proc + 0x54) = p;
    setFlag1C(fn_800C3558());
    return 1;
}


/* Memory stream used for the temporary save buffer. The vtable pointer sits after the
 * data members (MWCC layout); ctor/dtor are written out by hand. */
typedef struct MemStream {
    u8* base;     /* 0x00 */
    u8* cur;      /* 0x04 */
    u32 size;     /* 0x08 */
    u8 owned;     /* 0x0C */
    void* vtbl;   /* 0x10 */
} MemStream;

extern u8 lbl_80380928[];  /* MemWriter vtable */
extern u8 lbl_80380940[];  /* MemStream vtable */
extern u8* lbl_804CB618;   /* save buffer */

void* fn_80079958(u32 size, int align);
void fn_80079978(void* p);
void fn_80078E24(void* p);
void fn_8012D38C(MemStream* s);
void fn_8012CBF0(void);
void fn_8012D78C(void);
void fn_8008A48C(MemStream* s, void* buf);
void fn_8012D3EC(MemStream* s);
void fn_80113370(void);
void fn_8012D620(void);
void fn_8012D908(void);

static inline void MemWriterInit(MemStream* s, u8* buf, u32 size)
{
    s->vtbl = lbl_80380928;
    s->owned = 0;
    s->base = buf;
    s->cur = buf;
    s->size = size;
}

static inline void MemStreamDtor(MemStream* s)
{
    s->vtbl = lbl_80380940;
    if (s->owned) {
        fn_80078E24(s->base);
        s->base = NULL;
        s->owned = 0;
    }
}

int fn_80099774(void)
{
    MemStream s;
    u8* buf = (u8*)fn_80079958(0x18000, 0x40);
    lbl_804CB618 = buf;
    MemWriterInit(&s, buf, 0x18000);
    fn_8012D38C(&s);
    fn_8012CBF0();
    MemStreamDtor(&s);
    return 1;
}

int fn_80099808(void)
{
    MemStream s;
    u8* buf = (u8*)fn_80079958(0x18000, 0x40);
    lbl_804CB618 = buf;
    MemWriterInit(&s, buf, 0x18000);
    fn_8012D38C(&s);
    MemStreamDtor(&s);
    return 1;
}

int fn_80099898(void)
{
    MemStream s;
    fn_8012D78C();
    fn_8008A48C(&s, lbl_804CB618);
    fn_8012D3EC(&s);
    fn_80113370();
    fn_8012D620();
    fn_8012D908();
    fn_80079978(lbl_804CB618);
    lbl_804CB618 = NULL;
    MemStreamDtor(&s);
    return 1;
}

int fn_8009991C(void)
{
    MemStream s;
    fn_8012D78C();
    fn_8008A48C(&s, lbl_804CB618);
    fn_8012D3EC(&s);
    fn_8012D620();
    fn_8012D908();
    fn_80079978(lbl_804CB618);
    lbl_804CB618 = NULL;
    MemStreamDtor(&s);
    return 1;
}


extern u8 lbl_803C8E80[0x1648];
extern u8 lbl_803CB770[];
void fn_8024C2B4(MemStream* s);
void fn_8024C434(MemStream* s);
void fn_8002697C(void* battle);
void fn_80114D00(void* map);
void fn_80063C30(void* p);
void fn_800660C4(void* p);
int fn_80060754(void* p);
void* fn_801059B0(void);
void fn_80105704(void* p);
void fn_801097FC(void* p);


int fn_80099A90(void)
{
    MemStream s;
    fn_80063C30(lbl_803CAB38 + 0x144);
    fn_8012D78C();
    fn_8008A48C(&s, lbl_804CB618);
    fn_8024C434(&s);
    fn_801097FC(fn_80060728(lbl_803CAB38));
    fn_80079978(lbl_804CB618);
    lbl_804CB618 = NULL;
    MemStreamDtor(&s);
    return 1;
}

int fn_80099B24(void)
{
    fn_8012D78C();
    fn_8012D620();
    fn_8012D908();
    return 1;
}

int fn_80099B50(void)
{
    fn_8012D78C();
    fn_8002697C(lbl_803C8E80);
    fn_8012CBF0();
    fn_80114D00(lbl_803EC898);
    return 1;
}

extern u8 lbl_803E50B0[];

u8 fn_80099B90(void)
{
    return lbl_803E50B0[0xa];
}


int fn_801554B4(void* unit);
void fn_8010C8EC(void* p, s8 v);
void fn_8010CA94(void* p);
void fn_800F68DC(void* unit, int v);
void fn_800F6AEC(void* unit, int v);
void fn_800F7410(void* unit, int v);
void fn_800581F4(void* parent);

int fn_80099BA0(int id)
{
    u8* unit = GetUnit(id);
    if (unit == NULL || *(void**)(unit + 0xec) == NULL) {
        return 0;
    }
    return fn_801554B4(unit);
}

int fn_80099BE4(void* p, int v)
{
    if (!IsValidPtr(p)) {
        return 0;
    }
    fn_8010C8EC(p, v);
    fn_8010CA94(p);
    return 1;
}

#define ARMY_EACH(name, func)                         \
int name(int army)                                    \
{                                                     \
    u8* u = *(u8**)(lbl_804CB814 + army * 0xc);       \
    u8* next;                                         \
    while (u != NULL) {                               \
        next = *(u8**)(u + 0xe8);                     \
        func(u, 0);                                   \
        u = next;                                     \
    }                                                 \
    return 1;                                         \
}

ARMY_EACH(fn_80099C5C, fn_800F68DC)
ARMY_EACH(fn_80099CAC, fn_800F6AEC)
ARMY_EACH(fn_80099CFC, fn_800F7410)

int fn_80099D4C(void)
{
    fn_800581F4(fn_8009E898());
    setFlag1C(fn_800C3558());
    return 1;
}


void fn_8005840C(int v, void* parent);
void fn_800244C4(char* s, void* parent);
char* fn_8010DE10(void* x, u8 mode);

int fn_80099D80(int v)
{
    fn_8005840C(v, fn_8009E898());
    setFlag1C(fn_800C3558());
    return 1;
}

int fn_80099DC8(char* s)
{
    if (!IsValidPtr(s)) {
        return 0;
    }
    fn_800244C4(s, fn_8009E898());
    setFlag1C(fn_800C3558());
    return 1;
}

int fn_80099E48(void* x)
{
    return fn_80099DC8(fn_8010DE10(x, fn_80060728(lbl_803CAB38)->mode));
}


void fn_8019F85C(void* parent);
void fn_8026A1CC(void* parent);
u8* fn_8024BC94(void);
int fn_802450BC(void* sys);
void fn_8024BA84(s8 v, void* parent);
f32 fn_8017F68C(int mode, f32 from, f32 to, f32 t, f32 d);

int fn_80099EEC(void)
{
    fn_8019F85C(fn_8009E898());
    setFlag1C(fn_800C3558());
    return 1;
}

int fn_80099F20(void)
{
    fn_8026A1CC(fn_8009E898());
    setFlag1C(fn_800C3558());
    return 1;
}


/* intplGetValue */
int fn_80099FB4(int mode, int from, int to, int t, int d)
{
    return fn_8017F68C(mode, from, to, t, d);
}


typedef struct SysFlags {
    u8 pad0[0x40];
    u32 pad40 : 26;
    u32 f20 : 1;
    u32 f10 : 1;
    u32 f08 : 1;
    u32 rest : 3;
} SysFlags;

SysFlags* fn_8024BCA0(void);
void fn_800444F4(int v);
void fn_80084F0C(char* s);
void fn_800846BC(void* p);
extern u8 lbl_803873C8[];

int fn_8009A030(int mode)
{
    SysFlags* sf = fn_8024BCA0();
    u8 v = 0;
    switch (mode) {
    case 1:
        v = 5;
        sf->f08 = 1;
        sf->f10 = 0;
        sf->f20 = 0;
        break;
    case 2:
        v = 6;
        sf->f08 = 0;
        sf->f10 = 1;
        sf->f20 = 0;
        break;
    case 3:
        v = 7;
        sf->f08 = 0;
        sf->f10 = 0;
        sf->f20 = 1;
        break;
    default:
        sf->f08 = 0;
        sf->f10 = 0;
        sf->f20 = 0;
        break;
    }
    lbl_803CAB38[0x9c] = v;
    fn_800444F4(2);
    fn_80084F0C(lbl_80363B74 + 0x40); /* "E_BMapPlph" */
    fn_800846BC(lbl_803873C8);
    return 1;
}

u8 fn_8009A110(void)
{
    return lbl_803CAB38[0x9e];
}

void fn_80061A8C(void* p, s8 a, s8 b);
void fn_80061AB8(void* p, char* v);

int fn_8009A120(int a, int b)
{
    fn_80061A8C(lbl_803CAB38, a, b);
    return 1;
}

int fn_8009A15C(char* v)
{
    fn_80061AB8(lbl_803CAB38, v);
    return 1;
}


void fn_80061D98(void* p, s8 a, s8 b);
void fn_80061DD0(void* p, char* v);
void OSReport(const char* fmt, ...);

int fn_8009A18C(void* x)
{
    fn_80061AB8(lbl_803CAB38, fn_8010DE10(x, fn_80060728(lbl_803CAB38)->mode));
    return 1;
}

int fn_8009A1E8(int a, int b)
{
    fn_80061D98(lbl_803CAB38, a, b);
    return 1;
}

int fn_8009A224(char* v)
{
    fn_80061DD0(lbl_803CAB38, v);
    return 1;
}

int fn_8009A254(void* x)
{
    fn_80061DD0(lbl_803CAB38, fn_8010DE10(x, fn_80060728(lbl_803CAB38)->mode));
    return 1;
}

int fn_8009A2B0(char* s)
{
    if (!IsValidPtr(s)) {
        return 0;
    }
    OSReport(s);
    return 1;
}


extern PadObj* lbl_804CB5B8;
extern u8 lbl_8038192C[0x14];

void fn_8009A310(void* proc)
{
    if (lbl_804CB5B8->getTrig() & 0xfff0) {
        fn_80083B78(proc);
    }
}

int fn_8009A35C(void)
{
    fn_80081194(lbl_8038192C, fn_8009E898());
    setFlag1C(fn_800C3558());
    return 1;
}

int fn_8009A39C(int ms)
{
    return ms / 16.666666f;
}


int fn_8009A414(void)
{
    lbl_804CB5B8->setMask(0xfff0);
    lbl_804CB700 |= 0x2000;
    return 1;
}

int fn_8009A45C(void)
{
    lbl_804CB5B8->resetMask(0xfff0);
    lbl_804CB700 &= ~0x2000;
    return 1;
}


#define RET_CONST(name, v) \
int name(void)             \
{                          \
    return v;              \
}

RET_CONST(fn_8009A4A4, 0)
RET_CONST(fn_8009A4AC, 0)
RET_CONST(fn_8009A4B4, 0)
RET_CONST(fn_8009A4BC, 1)
RET_CONST(fn_8009A4C4, 0)
RET_CONST(fn_8009A4CC, 1)
RET_CONST(fn_8009A4D4, 0)

int fn_80245DFC(void* sys);

u32 fn_8009A4DC(void)
{
    u8* sf = (u8*)fn_8024BCA0();
    if (fn_80245DFC(sf) != 0) {
        return *(u32*)(sf + 0x40) & 1;
    }
    return 0;
}

int fn_8009A524(void)
{
    *(u32*)(fn_8024BC94() + 0x20) |= 0x20;
    return 1;
}

RET_CONST(fn_8009A554, 0)

void fn_801D0E18(void* p);
#if TARGET_PC
FE10_PROTO void * fn_800C357C(void);
#else
int fn_800C357C(void);
#endif
void fn_80081A90(void* proc);

void fn_8009A55C(u8* proc)
{
    fn_801D0E18(proc + 0x30);
    if (*(int*)(proc + 0x3c) == 0 || fn_800C357C() == 0) {
        fn_80081A90(proc);
    }
}


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
void fn_801D0C88(void* ctx, void* v);
extern u8 lbl_80381940[0x14];

void fn_8009A5AC(ScriptProc* proc)
{
    if (proc->stack != NULL) {
        fn_80079474(proc->stack);
        proc->stack = NULL;
    }
}

ScriptProc* fn_8009A5F0(void* entry)
{
    ScriptProc* proc = (ScriptProc*)fn_80081050(lbl_80381940, fn_8009E898());
    void* stack = fn_800791B0(0x100);
    proc->stack = stack;
    fn_801D0BAC(proc->ctx, stack, 0x40);
    proc->self = proc;
    fn_801D0C88(proc->ctx, entry);
    if (proc->running == 0) {
        fn_80081A90(proc);
    }
    return proc;
}

ScriptProc* fn_8009A67C(void* entry, void* arg)
{
    ScriptProc* proc = (ScriptProc*)fn_80081050(lbl_80381940, fn_8009E898());
    void* stack = fn_800791B0(0x100);
    proc->stack = stack;
    fn_801D0BAC(proc->ctx, stack, 0x40);
    proc->self = proc;
    fn_801D0C48(proc->ctx, arg);
    fn_801D0C88(proc->ctx, entry);
    if (proc->running == 0) {
        fn_80081A90(proc);
    }
    return proc;
}

}
