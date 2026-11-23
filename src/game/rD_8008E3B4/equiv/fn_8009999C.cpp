/* EQUIVALENT (register-only, round 19): fn_8009999C at regs level (5 words, r4/r5 swap); wip fragment made self-contained. */
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
int fn_80098AB8(char* name);

int fn_80098B2C(char* name, int x, int y, int z);

int fn_80098C54(char* name);



int fn_802501A4(char* name);
void fn_80250E38(int ch, f32 vol, f32 time);
int fn_80098CB4(char* name);


#define SE_VOL(name, vol)               \
int name(int t)                         \
{                                       \
    fn_80250E38(6, vol, t);             \
    return 1;                           \
}

int fn_80098D98(int t);







s8 fn_80252C38(char* name, f32 v);
s8 fn_80253848(char* name, Vec* pos, f32 v);
int fn_80098ED4(char* name, int v);

int fn_80098F60(char* name, int x, int y, int z, int v);



SndObj* fn_8024F484(s8 ch);
int fn_800990A4(int ch, int vol, int time);

int fn_8009916C(int ch, int t);



s8 fn_80255368(char* name, f32 v);
void fn_802568F0(char* name, f32 v);
void fn_80256A78(f32 v);
int fn_802502E0(char* name);
int fn_800991FC(char* name);

int fn_8009925C(char* name);

int fn_800992BC(int t);

int fn_800992FC(char* name);



void* fn_8013B9A8(void);
void fn_8013AB10(void* p, int v);
void fn_8013ABAC(void* p, int v);
int fn_80099350(int v);

int fn_80099398(int v);


typedef struct GameState {
    u8 pad0[0xe];
    u8 b0e;     /* 0x0E */
    u8 pad0f[2];
    u8 mode;    /* 0x11: difficulty */
} GameState;

extern u8 lbl_803CAB38[];
GameState* fn_80060728(void* t);
u8 fn_800993E0(void);

BOOL fn_8009940C(void);

BOOL fn_80099444(void);

BOOL fn_80099478(void);

BOOL fn_800994B0(void);

int fn_800994E8(int ms);


void fn_800D1D14(void* p, int a, int b);
void fn_80099524(u8* p);



int fn_800D2150(void);
extern u8 lbl_803818A8[0x14];
char* strcpy(char* dst, const char* src);
void fn_80099534(void* proc);

int fn_8009957C(char* name);


void* fn_800D25D4(void* buf, const char* path);
void fn_800D1EDC(void* p, u8 mode, int a, int b);
void fn_800D2578(void* p);
void fn_80099620(u8* proc);



int fn_800D20EC(void);
extern u8 lbl_803818E0[0x14];
void fn_8009968C(void* proc);

void fn_800996D4(void);

int fn_800996D8(void* p);



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
int fn_80099774(void);

int fn_80099808(void);

int fn_80099898(void);

int fn_8009991C(void);



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
int fn_80099A90(void);

int fn_80099B24(void);

int fn_80099B50(void);


extern u8 lbl_803E50B0[];
u8 fn_80099B90(void);



int fn_801554B4(void* unit);
void fn_8010C8EC(void* p, s8 v);
void fn_8010CA94(void* p);
void fn_800F68DC(void* unit, int v);
void fn_800F6AEC(void* unit, int v);
void fn_800F7410(void* unit, int v);
void fn_800581F4(void* parent);
int fn_80099BA0(int id);

int fn_80099BE4(void* p, int v);


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

int fn_80099D4C(void);



void fn_8005840C(int v, void* parent);
void fn_800244C4(char* s, void* parent);
char* fn_8010DE10(void* x, u8 mode);
int fn_80099D80(int v);

int fn_80099DC8(char* s);

int fn_80099E48(void* x);



void fn_8019F85C(void* parent);
void fn_8026A1CC(void* parent);
u8* fn_8024BC94(void);
int fn_802450BC(void* sys);
void fn_8024BA84(s8 v, void* parent);
f32 fn_8017F68C(int mode, f32 from, f32 to, f32 t, f32 d);
int fn_80099EEC(void);

int fn_80099F20(void);

int fn_80099FB4(int mode, int from, int to, int t, int d);



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
int fn_8009A030(int mode);

u8 fn_8009A110(void);


void fn_80061A8C(void* p, s8 a, s8 b);
void fn_80061AB8(void* p, char* v);
int fn_8009A120(int a, int b);

int fn_8009A15C(char* v);



void fn_80061D98(void* p, s8 a, s8 b);
void fn_80061DD0(void* p, char* v);
void OSReport(const char* fmt, ...);
int fn_8009A18C(void* x);

int fn_8009A1E8(int a, int b);

int fn_8009A224(char* v);

int fn_8009A254(void* x);

int fn_8009A2B0(char* s);



extern PadObj* lbl_804CB5B8;
extern u8 lbl_8038192C[0x14];
void fn_8009A310(void* proc);

int fn_8009A35C(void);

int fn_8009A39C(int ms);

int fn_8009A414(void);

int fn_8009A45C(void);



#define RET_CONST(name, v) \
int name(void)             \
{                          \
    return v;              \
}









int fn_80245DFC(void* sys);
u32 fn_8009A4DC(void);

int fn_8009A524(void);




void fn_801D0E18(void* p);
int fn_800C357C(void);
void fn_80081A90(void* proc);
void fn_8009A55C(u8* proc);



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
extern u8 lbl_80381940[0x14];
void fn_8009A5AC(ScriptProc* proc);

ScriptProc* fn_8009A5F0(void* entry);

ScriptProc* fn_8009A67C(void* entry, void* arg);


}

/* ---- from rD_8008E3B4/wip/fn_8009999C.cpp ---- */
extern "C" {
/*
 * fn_8009999C: 5 of 61 words differ, all a swap of r4/r5 (want vtable r4, zero r5). All 120
 * store orders in MemWriterInit were tried, and no order fixes this function while keeping the
 * others. Real C++ classes were much further off. Needs MemStream helpers from
 * ../fn_80098AB8.cpp.
 */
int fn_8009999C(void)
{
    MemStream s;
    u8* buf = (u8*)fn_80079958(0x18000, 0x40);
    lbl_804CB618 = buf;
    MemWriterInit(&s, buf, 0x18000);
    fn_8024C2B4(&s);
    fn_8012D78C();
    fn_8002697C(lbl_803C8E80);
    fn_8012CBF0();
    fn_80114D00(lbl_803EC898);
    fn_80063C30(lbl_803CAB38 + 0x144);
    fn_800660C4(lbl_803CB770);
    if (fn_80060754(lbl_803CAB38) != 0) {
        fn_80105704(fn_801059B0());
    }
    fn_80114D00(lbl_803EC898);
    MemStreamDtor(&s);
    return 1;
}
}
