#include "game/rD_8008E3B4/types.h"

extern "C" {

typedef struct FlagTable {
    u8 pad0[0x10];
    u8 b10;             /* 0x10 */
    u8 b11;             /* 0x11: difficulty / mode */
    u8 pad12[0x144 - 0x12];
    char* names[0x80];  /* 0x144 */
    u32 hashes[0x80];   /* 0x344 */
    u8 bits[0x10];      /* 0x544 */
    u8 pad554[0x988 - 0x554];
} FlagTable;

extern FlagTable lbl_803CAB38;
FlagTable* fn_80060728(FlagTable* t);
u32 fn_80076D18(const char* s);        /* string hash */
int fn_80291188(const char* a, const char* b); /* strcmp */

typedef struct ModeArrays {
    u8 pad0[0x24];
    u32 a[8];   /* 0x24: modes 0 and 3 */
    u32 b[8];   /* 0x44: mode 1 */
    u32 c[8];   /* 0x64: mode 2 */
} ModeArrays;

u32 fn_80092D04(ModeArrays* m, int idx)
{
    u32* arr;
    switch (fn_80060728(&lbl_803CAB38)->b11) {
    case 3:
    case 0:
        arr = m->a;
        break;
    case 1:
        arr = m->b;
        break;
    case 2:
        arr = m->c;
        break;
    }
    return arr[idx];
}

u32 fn_80092D88(ModeArrays* m, int idx)
{
    u32* arr;
    switch (fn_80060728(&lbl_803CAB38)->b11) {
    case 3:
    case 0:
        arr = m->a;
        break;
    case 1:
        arr = m->b;
        break;
    case 2:
        arr = m->c;
        break;
    }
    return (arr + idx)[3];
}

int fn_801194FC(void* p);

typedef struct Obj90 { u8 pad[0x90]; void* p90; } Obj90;

static inline int flagFind(FlagTable* t, const char* name)
{
    u32 h = fn_80076D18(name);
    int i;
    for (i = 0; i < 0x80; i++) {
        if (h == t->hashes[i] && fn_80291188(t->names[i], name) == 0) {
            return i;
        }
    }
    return -1;
}

static inline BOOL flagSlotUsed(FlagTable* t, int i)
{
    return i >= 0 && i < 0x80 && t->names[i] != NULL;
}

static inline void flagClearBit(FlagTable* t, int i)
{
    if (i >= 0 && i < 0x80) {
        t->bits[i >> 3] &= ~(1 << (i & 7));
    }
}

int fn_80092E38(char* name)
{
    int i;
    if (flagFind(&lbl_803CAB38, name) < 0) {
        for (i = 0; i < 0x80; i++) {
            if (!flagSlotUsed(&lbl_803CAB38, i)) {
                lbl_803CAB38.names[i] = name;
                lbl_803CAB38.hashes[i] = fn_80076D18(name);
                flagClearBit(&lbl_803CAB38, i);
                break;
            }
        }
    }
    return 1;
}


static inline BOOL flagTestBit(FlagTable* t, int i)
{
    if (i < 0 || i >= 0x80) {
        return 0;
    }
    return (t->bits[i >> 3] & (1 << (i & 7))) != 0;
}

static inline BOOL flagGetBit(FlagTable* t, int i)
{
    if (i < 0 || i >= 0x80) {
        return 0;
    }
    return flagTestBit(t, i);
}

static inline BOOL flagGet(FlagTable* t, const char* name)
{
    if (name[0] == 0) {
        return 0;
    }
    return flagGetBit(t, flagFind(t, name));
}


static inline void flagSetBit3(FlagTable* t, int i)
{
    if (i < 0 || i >= 0x80) {
        return;
    }
    t->bits[i >> 3] |= (1 << (i & 7));
}

static inline void flagSetBit2(FlagTable* t, int i)
{
    if (i < 0 || i >= 0x80) {
        return;
    }
    flagSetBit3(t, i);
}

static inline void flagSetBit(FlagTable* t, int i)
{
    if (i < 0 || i >= 0x80) {
        return;
    }
    flagSetBit2(t, i);
}

int fn_8009317C(const char* name)
{
    flagSetBit(&lbl_803CAB38, flagFind(&lbl_803CAB38, name));
    return 0;
}

static inline void flagClrBit3(FlagTable* t, int i)
{
    if (i < 0 || i >= 0x80) {
        return;
    }
    t->bits[i >> 3] &= ~(1 << (i & 7));
}

static inline void flagClrBit2(FlagTable* t, int i)
{
    if (i < 0) {
        return;
    }
    flagClrBit3(t, i);
}

static inline void flagClrBit(FlagTable* t, int i)
{
    if (i < 0 || i >= 0x80) {
        return;
    }
    flagClrBit2(t, i);
}

int fn_80093254(const char* name)
{
    flagClrBit(&lbl_803CAB38, flagFind(&lbl_803CAB38, name));
    return 0;
}


/* String pool: "E_Talk", "BGM_DEAD1", "BGM_DEAD2", ... (see NOTES.md) */
extern char lbl_80363B74[];
extern u32 lbl_804CB878[2];
extern u32 lbl_804CB700;
extern u8* lbl_804CB810;
extern u8 lbl_80381678[0x14];
extern u8 lbl_8038168C[0x14];
extern u8 lbl_803816A0[0x14];
extern u8 lbl_803E5064[0x24];

#if TARGET_PC
FE10_PROTO p32ret fn_80085708(const char* name);
#else
int fn_80085708(const char* name);
#endif
void fn_8014C598(void* ctx);
void fn_8014BC80(void* ctx, void* p);
void fn_8014C2AC(void* ctx);
void fn_8014BED4(void* ctx, void* p);
void fn_8014C59C(void* ctx);
void* fn_8009E898(void);
void* fn_80081050(void* cls, void* parent);
void* fn_80081194(void* cls, void* parent);
void fn_80083B78(void* proc);
#if TARGET_PC
FE10_PROTO void fn_800D0AE4(ptr32<const void>, ptr32<const void>);
FE10_PROTO void fn_800D0B38(ptr32<const void>, void* p);
#else
void fn_800D0AE4(void* ctx, const char* str);
void fn_800D0B38(void* ctx, void* p);
#endif
#if TARGET_PC
FE10_PROTO void* fn_8010B1B4(ptr32<const void>);
#else
void* fn_8010B1B4(void* p);
#endif
void* fn_80118C44(void* p);
void fn_800620A8(FlagTable* t, f32 x, f32 y);
void fn_8012FF30(void);
int fn_8012FD80(int v);
u8* fn_800C3558(void);

static inline u8* GetUnit(u8 id)
{
    if (id != 0) {
        return lbl_804CB810 + (id - 1) * 0x3f0;
    }
    return NULL;
}

int fn_80093328(void* ctx)
{
    if (fn_80085708(lbl_80363B74) != 0) { /* "E_Talk" */
        fn_8014C598(ctx);
        return 1;
    }
    fn_8014BC80(ctx, fn_8009E898());
    return 1;
}

int fn_80093388(void* ctx)
{
    if (fn_80085708(lbl_80363B74) != 0) {
        fn_8014C2AC(ctx);
        return 1;
    }
    fn_8014BED4(ctx, fn_8009E898());
    return 1;
}

int fn_800933E8(void* ctx)
{
    fn_8014C59C(ctx);
    return 1;
}

int fn_8009340C(void* ctx)
{
    fn_8014BED4(ctx, fn_80081050(lbl_80381678, fn_8009E898()));
    return 1;
}

BOOL fn_80093458(void)
{
    if (fn_80085708(lbl_80363B74) == 0) {
        return 0;
    }
    return !(lbl_804CB878[0] & 0x10);
}

int fn_800934A0(void* ctx, const char* str)
{
    fn_800D0AE4(ctx, str);
    return 1;
}

int fn_800934C4(void* ctx, void* p)
{
    fn_800D0B38(ctx, p);
    return 1;
}

int fn_800934E8(void* ctx, void* p)
{
    fn_800D0B38(ctx, fn_80118C44(fn_8010B1B4(p)));
    return 1;
}

int fn_8009352C(int x, int y)
{
    fn_800620A8(&lbl_803CAB38, x, y);
    fn_8012FF30();
    return 1;
}

int fn_8009358C(int x, int y)
{
    if (lbl_804CB700 & 0x8001) {
        fn_800620A8(&lbl_803CAB38, x, y);
        fn_8012FF30();
        return 1;
    }
    fn_800620A8(&lbl_803CAB38, x, y);
    return 1;
}

void fn_80093630(void* proc)
{
    if (fn_8012FD80(0) == 0) {
        fn_80083B78(proc);
    } else if (lbl_804CB700 & 0x8001) {
        fn_8012FF30();
        fn_80083B78(proc);
    }
}

/* An inline setter keeps the constant 1 out of a callee-saved register. */
static inline void setFlag1C(u8* p)
{
    p[0x1c] = 1;
}

int fn_8009368C(void)
{
    if (lbl_804CB700 & 0x8001) {
        fn_8012FF30();
        return 0;
    }
    if (fn_8012FD80(0) == 0) {
        return 0;
    }
    fn_80081194(lbl_8038168C, fn_8009E898());
    setFlag1C(fn_800C3558());
    setFlag1C(lbl_803E5064);
    return 1;
}

void fn_80093708(void* proc)
{
    if (fn_8012FD80(1) == 0) {
        fn_80083B78(proc);
    } else if (lbl_804CB700 & 0x8001) {
        fn_8012FF30();
        fn_80083B78(proc);
    }
}

int fn_80093764(void)
{
    if (lbl_804CB700 & 0x8001) {
        fn_8012FF30();
        return 0;
    }
    if (fn_8012FD80(1) == 0) {
        return 0;
    }
    fn_80081194(lbl_803816A0, fn_8009E898());
    setFlag1C(fn_800C3558());
    setFlag1C(lbl_803E5064);
    return 1;
}

int fn_800937E0(int id)
{
    u8* unit = GetUnit(id);
    if (unit == NULL) {
        return 0;
    }
    return fn_8009358C(*(s8*)(unit + 0x102), *(s8*)(unit + 0x103));
}


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

extern u8* lbl_803CA870[];
typedef struct BattleState {
    u8 pad0[0xde0];
    u8 sub[0x80c];      /* 0xDE0 */
    u32 flag31 : 1;     /* 0x15EC */
    u32 flag30 : 1;
    u32 rest : 30;
    u8 pad15F0[0x58];
} BattleState;
extern BattleState lbl_803C8E80;
extern void* lbl_804CA4D8;
extern u8 lbl_803EC898[];
extern u8* lbl_804CB814;

void* fn_80119010(void* pid);
void* fn_80118FB4(void* pid);
#if TARGET_PC
FE10_PROTO void * fn_80076F54(void* ctx);
#else
int fn_80076F54(void* ctx);
#endif
u8* fn_8002C590(BattleState* p);
void fn_80252B04(f32 v);
SndObj* fn_8024F3FC(s8 ch);
int fn_8011B77C(void* list, void* skill);
void fn_80251838(s8 ch, const char* name, f32 v);
void fn_80068A4C(void);
void fn_8011E864(void* unit);
void fn_80114D00(void* map);
void fn_800D7EBC(void);
void fn_8010E41C(u8* mask, int v);
void fn_8011E300(void* unit, s8 x, s8 y, int v);
void fn_8012D588(void);
void fn_801476E8(void);
void fn_80109078(void* p);
int fn_801237EC(void* unit);
void fn_80126D9C(void* unit, s16 v);
void fn_80128E14(void* unit, int v);
void fn_801283F8(void* unit);

int fn_800938C4(void)
{
    void* ctx;
    if (lbl_803CA870[0] == NULL) {
        return 0;
    }
    ctx = fn_80119010(*(void**)(lbl_803CA870[0] + 0xec));
    if (fn_80076F54(ctx) != 0) {
        if (fn_80085708(lbl_80363B74) != 0) {
            fn_8014C2AC(ctx);
        } else {
            fn_8014BED4(ctx, fn_8009E898());
        }
    }
    return 0;
}

int fn_8009394C(void)
{
    u8* unit = fn_8002C590(&lbl_803C8E80);
    void* ctx;
    SndObj* snd;
    u8 army;
    if (unit == NULL) {
        return 0;
    }
    ctx = fn_80118FB4(*(void**)(unit + 0xec));
    if (fn_80076F54(ctx) == 0) {
        return 0;
    }
    if (fn_80085708(lbl_80363B74) != 0) {
        fn_8014C2AC(ctx);
    } else {
        fn_8014BED4(ctx, fn_8009E898());
    }
    army = (*(u8**)(unit + 0xf4))[8];
    if (army == 0 || army == 6) {
        fn_80252B04(0.0f);
        snd = fn_8024F3FC(1);
        if (snd != NULL && snd->v10() != 0) {
            snd->v24(0xfa);
            snd->v0C();
        }
        if (fn_8011B77C(unit + 0x12c, lbl_804CA4D8) != 0) {
            fn_80251838(1, lbl_80363B74 + 0x7, 0.0f); /* "BGM_DEAD1" */
        } else {
            fn_80251838(1, lbl_80363B74 + 0x11, 0.0f); /* "BGM_DEAD2" */
        }
        fn_80068A4C();
    }
    return 1;
}

int fn_80093AB0(int id)
{
    u8* unit = GetUnit(id);
    if (unit == NULL || *(void**)(unit + 0xec) == NULL) {
        return 0;
    }
    fn_8011E864(unit);
    fn_80114D00(lbl_803EC898);
    fn_800D7EBC();
    return 1;
}

#pragma use_lmw_stmw on
int fn_80093B20(void)
{
    u8 mask[12];
    u8 mask2[12];
    int i;
    u8* unit;
    u8* r;
    int j;
    fn_8010E41C(mask, 3);
    for (i = 1; i <= 0xfe; i++) {
        unit = GetUnit(i);
        if (*(void**)(unit + 0xec) != NULL && mask[(*(u8**)(unit + 0xf4))[8]]) {
            r = *(u8**)(unit + 0xf8);
            if (r != NULL && (*(u32*)(unit + 0x10c) & 2)) {
                fn_8011E300(unit, *(s8*)(unit + 0x102), *(s8*)(unit + 0x103), 1);
                if (r != NULL) {
                    *(u64*)(r + 0x108) &= ~(u64)1;
                }
            }
        }
    }
    unit = *(u8**)(lbl_804CB814 + 4);
    while (unit != NULL) {
        r = *(u8**)(unit + 0xe4);
        fn_8011E864(unit);
        unit = r;
    }
    fn_8010E41C(mask2, 3);
    for (j = 1; j <= 0xfe; j++) {
        unit = GetUnit(j);
        if (*(void**)(unit + 0xec) != NULL && mask2[(*(u8**)(unit + 0xf4))[8]]) {
            fn_8011E864(unit);
        }
    }
    fn_8012D588();
    fn_80114D00(lbl_803EC898);
    fn_801476E8();
    return 1;
}
#pragma use_lmw_stmw off

int fn_80093C98(int id)
{
    u8* unit = GetUnit(id);
    if (unit == NULL || *(void**)(unit + 0xec) == NULL) {
        return 0;
    }
    *(u64*)(unit + 0x108) &= ~0x6D19773AC1ULL;
    fn_80109078(unit + 0x110);
    fn_80126D9C(unit, fn_801237EC(unit));
    fn_80128E14(unit, 0);
    fn_801283F8(unit);
    return 1;
}


#pragma use_lmw_stmw on
int fn_80093D50(int army)
{
    u8* u = *(u8**)(lbl_804CB814 + army * 0xc);
    while (u != NULL) {
        u8 id = u[0xfc];
        u = *(u8**)(u + 0xe8);
        fn_80093C98(id);
    }
    return 1;
}
#pragma use_lmw_stmw off

typedef struct ProcFlags {
    u8 pad0[0x54];
    void* p54;
    void* p58;
    u8 pad5c[0x10];
    u32 flags;  /* 0x6C */
} ProcFlags;

int fn_800C7FA0(void);
int fn_800C9030(void);
int fn_800C7FC4(void);
int fn_800C9054(void);
void fn_800C900C(int a, int b);
void fn_800C835C(u8 a, int b);
void fn_80250E38(int a, f32 x, f32 y);
void fn_80250F0C(int a, f32 x, f32 y);

void fn_80093E38(ProcFlags* p)
{
    p->flags = 0;
    p->flags |= fn_800C7FA0();
    p->flags |= fn_800C9030() ? 2 : 0;
    p->flags |= fn_800C7FC4() ? 4 : 0;
    p->flags |= fn_800C9054() ? 8 : 0;
    if (fn_800C7FA0() != 0 || fn_800C9030() != 0) {
        fn_800C900C(2, 0x10a);
        fn_800C835C(2, 0x10a);
    } else if (fn_800C7FC4() != 0 || fn_800C9054() != 0) {
        fn_800C900C(5, 0x10a);
        fn_800C835C(5, 0x10a);
    }
    if (lbl_804CB700 & 1) {
        fn_80250E38(1, 1.0f, 266.0f);
        fn_80250F0C(1, 1.0f, 266.0f);
    }
}

void fn_80093F68(ProcFlags* p)
{
    if (p->flags & 1) {
        fn_800C835C(3, 0x10a);
    }
    if (p->flags & 2) {
        fn_800C900C(3, 0x10a);
    }
    if (p->flags & 4) {
        fn_800C835C(6, 0x10a);
    }
    if (p->flags & 8) {
        fn_800C900C(6, 0x10a);
    }
    if (lbl_804CB700 & 1) {
        fn_80250E38(1, 0.0f, 266.0f);
        fn_80250F0C(1, 0.0f, 266.0f);
    }
}

typedef struct UnitItem {
    u8 data[0x28];
} UnitItem;

void fn_80111B34(UnitItem* item);
void fn_80111B64(UnitItem* item, UnitItem* src);
void fn_80111C24(UnitItem* item, int flag);
void fn_80110BB4(UnitItem* item, void* data);
void fn_8004AD18(void* a, UnitItem* item, void* proc);

void fn_8009401C(ProcFlags* p)
{
    UnitItem a;
    UnitItem b;
    fn_80111B34(&a);
    fn_80110BB4(&a, p->p58);
    fn_80111B64(&b, &a);
    fn_8004AD18(p->p54, &b, p);
    fn_80111C24(&b, -1);
    fn_80111C24(&a, -1);
}


extern u8 lbl_803816B4[0x14];
extern u8 lbl_803816F0[0x14];
extern u8 lbl_8038172C[0x14];
void* fn_8010B228(void* x);
void* fn_8010B23C(void* x);

typedef struct UnitProc {
    u8 pad0[0x54];
    void* unit;   /* 0x54 */
    void* data;   /* 0x58 */
    u8 pad5c[4];
    int v60;      /* 0x60 */
} UnitProc;

int fn_8009408C(int id, void* x)
{
    u8* unit = GetUnit(id);
    void* d;
    UnitProc* proc;
    if (unit == NULL || *(void**)(unit + 0xec) == NULL) {
        return 0;
    }
    d = fn_8010B228(x);
    if (d == NULL) {
        return 0;
    }
    proc = (UnitProc*)fn_80081194(lbl_803816B4, fn_8009E898());
    proc->unit = unit;
    proc->data = d;
    return 1;
}

int fn_8009419C(int id, void* x)
{
    u8* unit = GetUnit(id);
    void* d;
    UnitProc* proc;
    if (unit == NULL || *(void**)(unit + 0xec) == NULL) {
        return 0;
    }
    d = fn_8010B23C(x);
    if (d == NULL) {
        return 0;
    }
    proc = (UnitProc*)fn_80081194(lbl_803816F0, fn_8009E898());
    proc->unit = unit;
    proc->data = d;
    return 1;
}

int fn_800626E0(FlagTable* t);
void fn_800615DC(FlagTable* t, int v);
void fn_80031984(int v, void* proc, void* unit);

void fn_80094240(UnitProc* proc)
{
    fn_800615DC(&lbl_803CAB38, proc->v60 + fn_800626E0(&lbl_803CAB38));
    fn_80031984(proc->v60, proc, proc->unit);
}

int fn_800942A0(int v)
{
    UnitProc* proc = (UnitProc*)fn_80081194(lbl_8038172C, fn_8009E898());
    proc->v60 = v;
    proc->unit = lbl_803CA870[0];
    return 1;
}

void fn_8025F6A0(const char* name);
void fn_8025F6A8(const char* name);
void fn_8025F6B0(const char* name);
void fn_8025FFF0(int v);

void fn_800942F0(const char* name)
{
    fn_8025F6A0(name);
}

int fn_800942F4(const char* name)
{
    fn_8025F6A8(name);
    return 1;
}

int fn_80094318(const char* name)
{
    fn_8025F6B0(name);
    return 1;
}

int fn_8009433C(void)
{
    fn_8025FFF0(0x7f);
    return 1;
}

#define IsValidPtr(p) \
    (((u32)(p) >= 0x80000000 && (u32)(p) < 0x81800000) || ((u32)(p) >= 0x90000000 && (u32)(p) < 0x98000000))

void* fn_800D4228(void* p);
void fn_800D4188(void* p, void* parent);
void fn_800D42A0(void* p);
f32 fn_800D3DA8(void* p, u8 v);

int fn_80094364(void* p)
{
    if (!IsValidPtr(p)) {
        return 0;
    }
    if (fn_800D4228(p) != NULL) {
        return 0;
    }
    fn_800D4188(p, fn_8009E898());
    return 1;
}

int fn_800943F0(void* p)
{
    if (!IsValidPtr(p)) {
        return 0;
    }
    if (fn_800D4228(p) != NULL) {
        return 0;
    }
    fn_800D4188(p, NULL);
    return 1;
}

int fn_80094478(void* p)
{
    if (!IsValidPtr(p)) {
        return 0;
    }
    fn_800D42A0(p);
    return 1;
}

int fn_800944D4(void)
{
    fn_800D42A0(NULL);
    return 1;
}

int fn_800944FC(void* p, int v)
{
    void* q;
    if (!IsValidPtr(p)) {
        return 0;
    }
    q = fn_800D4228(p);
    if (q == NULL) {
        return 0;
    }
    return fn_800D3DA8(q, v);
}


void fn_800D3D00(void* q, u8 kind, f32 v);
void fn_800D3EE0(void* q, int kind, int b, f32 x, f32 y, f32 z);
void fn_800D39D4(void* q, int v);

int fn_80094584(void* p, int kind, int val)
{
    void* q;
    f32 f;
    if (!IsValidPtr(p)) {
        return 0;
    }
    q = fn_800D4228(p);
    if (q == NULL) {
        return 0;
    }
    f = val;
    switch (kind) {
    case 5:
    case 6:
    case 7:
        f *= 0.01f;
        break;
    }
    fn_800D3D00(q, kind, f);
    return 1;
}

int fn_80094648(void* p, int kind, int b, int x, int y, int z)
{
    void* q;
    f32 fx;
    f32 fy;
    if (!IsValidPtr(p)) {
        return 0;
    }
    q = fn_800D4228(p);
    if (q == NULL) {
        return 0;
    }
    fx = x;
    fy = y;
    switch (kind) {
    case 5:
    case 6:
    case 7:
        fy *= 0.01f;
        if (x != 123456789) {
            fx *= 0.01f;
        }
        break;
    }
    fn_800D3EE0(q, kind, b, fx, fy, z);
    return 1;
}

int fn_8009475C(void* p, int v)
{
    void* q;
    if (!IsValidPtr(p)) {
        return 0;
    }
    q = fn_800D4228(p);
    if (q == NULL) {
        return 0;
    }
    fn_800D39D4(q, v);
    return 1;
}


typedef struct Sprite {
    u8 pad0[0x40];
    f32 x;    /* 0x40 */
    f32 y;    /* 0x44 */
    u8 pad48[0xc];
    f32 v54;  /* 0x54 */
    f32 v58;  /* 0x58 */
} Sprite;

int fn_800947DC(void* p, int x, int y)
{
    Sprite* q;
    if (!IsValidPtr(p)) {
        return 0;
    }
    q = (Sprite*)fn_800D4228(p);
    if (q == NULL) {
        return 0;
    }
    q->x = x;
    q->y = y;
    return 1;
}

typedef struct MoveProc {
    u8 pad0[0x30];
    f32 from58;   /* 0x30 */
    f32 to58;     /* 0x34 */
    u8 pad38[4];
    f32 fromX;    /* 0x3C */
    f32 fromY;    /* 0x40 */
    f32 from54;   /* 0x44 */
    f32 toX;      /* 0x48 */
    f32 toY;      /* 0x4C */
    f32 to54;     /* 0x50 */
    void* obj;    /* 0x54 */
    u8 pad58[8];
    int time;     /* 0x60 */
    int duration; /* 0x64 */
    int v68;      /* 0x68 */
} MoveProc;

f32 fn_8017F68C(int mode, f32 from, f32 to, f32 t, f32 d);

void fn_80094898(MoveProc* proc)
{
    Sprite* q = (Sprite*)fn_800D4228(proc->obj);
    f32 x;
    f32 y;
    f32 v54;
    f32 v58;
    if (q == NULL) {
        fn_80083B78(proc);
        return;
    }
    proc->time++;
    if (lbl_804CB700 & 0x8001) {
        proc->time = proc->duration;
    }
    x = fn_8017F68C(0, proc->fromX, proc->toX, proc->time, proc->duration);
    y = fn_8017F68C(0, proc->fromY, proc->toY, proc->time, proc->duration);
    v54 = fn_8017F68C(0, proc->from54, proc->to54, proc->time, proc->duration);
    v58 = fn_8017F68C(0, proc->from58, proc->to58, proc->time, proc->duration);
    q->x = x;
    q->y = y;
    q->v54 = v54;
    q->v58 = v58;
    if (proc->time >= proc->duration) {
        fn_80083B78(proc);
    }
}


extern u8 lbl_80381768[0x14];

int fn_80094A68(void* p, int x, int y, int dur, int v68, f32 scale)
{
    Sprite* q;
    MoveProc* proc;
    f32 fromX;
    f32 fromY;
    f32 from54;
    f32 from58;
    if (!IsValidPtr(p)) {
        return 0;
    }
    q = (Sprite*)fn_800D4228(p);
    if (q == NULL) {
        return 0;
    }
    fromX = q->x;
    fromY = q->y;
    from54 = q->v54;
    from58 = q->v58;
    if (dur <= 0) {
        dur = 1;
    }
    proc = (MoveProc*)fn_80081050(lbl_80381768, fn_8009E898());
    proc->fromX = fromX;
    proc->toX = x;
    proc->fromY = fromY;
    proc->toY = y;
    proc->from54 = from54;
    proc->to54 = scale;
    proc->from58 = from58;
    proc->to58 = scale;
    proc->time = 0;
    proc->duration = dur;
    proc->obj = p;
    proc->v68 = v68;
    return 1;
}

int fn_80094BE4(void* p, int x, int y, int pct, int dur, int v68)
{
    f32 scale = pct / 100.0f;
    return fn_80094A68(p, 304.0f - x * scale, 240.0f - y * scale, dur, v68, scale);
}

int fn_80094C80(void* p, int x, int y, int dur, int v68)
{
    return fn_80094A68(p, x, y, dur, v68, 1.0f);
}

void fn_800D3BCC(void* q, u8 v);

int fn_80094C88(void* p, int v)
{
    void* q;
    if (!IsValidPtr(p)) {
        return 0;
    }
    q = fn_800D4228(p);
    if (q == NULL) {
        return 0;
    }
    fn_800D3BCC(q, v);
    return 1;
}


#define SPRITE_CALL_U8(name, func)  \
void func(void* q, u8 v);           \
int name(void* p, int v)            \
{                                   \
    void* q;                        \
    if (!IsValidPtr(p)) {           \
        return 0;                   \
    }                               \
    q = fn_800D4228(p);             \
    if (q == NULL) {                \
        return 0;                   \
    }                               \
    func(q, v);                     \
    return 1;                       \
}

SPRITE_CALL_U8(fn_80094D08, fn_800D3C30)
SPRITE_CALL_U8(fn_80094D88, fn_800D3C90)

void fn_800D3928(void* q, f32 v);
f32 fn_800D395C(void* q);

int fn_80094E08(void* p, int v)
{
    void* q;
    if (!IsValidPtr(p)) {
        return 0;
    }
    q = fn_800D4228(p);
    if (q == NULL) {
        return 0;
    }
    fn_800D3928(q, v);
    return 1;
}

int fn_80094EA0(void* p)
{
    void* q;
    if (!IsValidPtr(p)) {
        return -1;
    }
    q = fn_800D4228(p);
    if (q == NULL) {
        return -1;
    }
    return fn_800D395C(q);
}

extern char lbl_803E5028[0x18];
char* strcpy(char* dst, const char* src);
void fn_8018454C(void* p, void* parent);
void* fn_80184648(void* p);
void fn_80184324(void* q);

int fn_80094F18(char* s)
{
    if (!IsValidPtr(s)) {
        return 0;
    }
    strcpy(lbl_803E5028, s);
    return 1;
}

int fn_80094F80(void* p)
{
    if (!IsValidPtr(p)) {
        return 0;
    }
    fn_8018454C(p, fn_8009E898());
    return 0;
}

int fn_80094FF4(void* p)
{
    void* q;
    if (!IsValidPtr(p)) {
        return 0;
    }
    q = fn_80184648(p);
    if (q == NULL) {
        return 0;
    }
    fn_80184324(q);
    return 0;
}

int fn_80095064(int x, int y)
{
    u8* q;
    if (!IsValidPtr(lbl_803E5028)) {
        return 0;
    }
    q = (u8*)fn_80184648(lbl_803E5028);
    if (q == NULL) {
        return 0;
    }
    *(f32*)(q + 0x10) = x;
    *(f32*)(q + 0x14) = y;
    return 1;
}


void fn_80183F0C(void* q, f32 x, f32 y, f32 sx, f32 sy, int dur, int mode);

int fn_80095138(int x, int y, int dur, int mode, f32 sx, f32 sy)
{
    void* q;
    int m;
    if (lbl_804CB700 & 0x8001) {
        dur = 0;
    }
    if (!IsValidPtr(lbl_803E5028)) {
        return 0;
    }
    q = fn_80184648(lbl_803E5028);
    switch (mode) {
    case 0:
        m = 0;
        break;
    case 1:
        m = 1;
        break;
    case 2:
        m = 4;
        break;
    default:
        m = 0;
        break;
    }
    fn_80183F0C(q, x, y, sx, sy, dur, m);
    return 1;
}

int fn_80095294(int x, int y, int sx, int sy, int dur, int mode)
{
    f32 fsx;
    f32 fsy;
    if (lbl_804CB700 & 0x8001) {
        dur = 0;
    }
    fsx = sx / 10000.0f;
    fsy = sy / 10000.0f;
    return fn_80095138(304.0f - x * fsx, 224.0f - y * fsy, dur, mode, fsx, fsy);
}

int fn_80095350(int x, int y, int sx, int sy, int dur, int mode)
{
    if (lbl_804CB700 & 0x8001) {
        dur = 0;
    }
    return fn_80095138(x, y, dur, mode, sx / 10000.0f, sy / 10000.0f);
}


#define WIN_CALL_INT(name, func)              \
void func(void* q, int v);                    \
int name(int v)                               \
{                                             \
    void* q;                                  \
    if (lbl_804CB700 & 0x8001) {              \
        v = 0;                                \
    }                                         \
    if (!IsValidPtr(lbl_803E5028)) {          \
        return 0;                             \
    }                                         \
    q = fn_80184648(lbl_803E5028);            \
    if (q == NULL) {                          \
        return 0;                             \
    }                                         \
    func(q, v);                               \
    return 1;                                 \
}

WIN_CALL_INT(fn_800953C4, fn_80183F74)
WIN_CALL_INT(fn_8009546C, fn_80183FB0)

typedef struct GXColor {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} GXColor;

void fn_80183944(void* q, int a, int b, int c, GXColor col, f32 v);

struct Color2 {
    GXColor c;
    Color2(u32 color)
    {
        GXColor t = { (u8)(color >> 16), (u8)(color >> 8), (u8)color, 0xff };
        c = t;
    }
};

static inline void callColor(void* q, int a, int b, int c, GXColor col, f32 v)
{
    fn_80183944(q, a, b, c, col, v);
}



/* GMap commands on the map named by lbl_803E5028 (GMapSetCurrentGID), skipped while fast-forwarding. */
#define WIN_F_CALL1(name, func)               \
void func(void* q, int v);                    \
int name(int v)                               \
{                                             \
    void* q;                                  \
    if (!IsValidPtr(lbl_803E5028)) {          \
        return 0;                             \
    }                                         \
    if (lbl_804CB700 & 0x8001) {              \
        return 0;                             \
    }                                         \
    q = fn_80184648(lbl_803E5028);            \
    if (q == NULL) {                          \
        return 0;                             \
    }                                         \
    func(q, v);                               \
    return 1;                                 \
}

#define WIN_F_CALL0(name, func)               \
void func(void* q);                           \
int name(void)                                \
{                                             \
    void* q;                                  \
    if (!IsValidPtr(lbl_803E5028)) {          \
        return 0;                             \
    }                                         \
    if (lbl_804CB700 & 0x8001) {              \
        return 0;                             \
    }                                         \
    q = fn_80184648(lbl_803E5028);            \
    if (q == NULL) {                          \
        return 0;                             \
    }                                         \
    func(q);                                  \
    return 1;                                 \
}

#define WIN_TEST1(name, func)                 \
int func(void* q, int v);                     \
int name(int v)                               \
{                                             \
    if (!IsValidPtr(lbl_803E5028)) {          \
        return 0;                             \
    }                                         \
    if (func(fn_80184648(lbl_803E5028), v)) { \
        return 1;                             \
    }                                         \
    return 0;                                 \
}

#define WIN_CALL1(name, func)                 \
void func(void* q, int v);                    \
int name(int v)                               \
{                                             \
    void* q;                                  \
    if (!IsValidPtr(lbl_803E5028)) {          \
        return 0;                             \
    }                                         \
    q = fn_80184648(lbl_803E5028);            \
    if (q == NULL) {                          \
        return 0;                             \
    }                                         \
    func(q, v);                               \
    return 1;                                 \
}

WIN_F_CALL1(fn_8009563C, fn_80183B10)
WIN_F_CALL0(fn_800956E8, fn_80183B30)
WIN_TEST1(fn_80095784, fn_80183BA8)

#if TARGET_PC
FE10_PROTO void fn_80183BC8(void* q, int a, p32arg b);
#else
void fn_80183BC8(void* q, int a, int b);
#endif

int fn_8009581C(int a, int b)
{
    void* q;
    if (!IsValidPtr(lbl_803E5028)) {
        return 0;
    }
    if (lbl_804CB700 & 0x8001) {
        return 0;
    }
    q = fn_80184648(lbl_803E5028);
    if (q == NULL) {
        return 0;
    }
    fn_80183BC8(q, a, b);
    return 1;
}

WIN_F_CALL1(fn_800958D8, fn_80183C60)
WIN_F_CALL0(fn_80095984, fn_80183C80)
WIN_TEST1(fn_80095A20, fn_80183CF4)

void fn_80183D14(void* q, int a, int b, int c, int d, BOOL e);

#pragma use_lmw_stmw on
int fn_80095AB8(int a, int b, int c, int d, int e)
{
    void* q;
    if (!IsValidPtr(lbl_803E5028)) {
        return 0;
    }
    if (lbl_804CB700 & 0x8001) {
        return 0;
    }
    q = fn_80184648(lbl_803E5028);
    if (q == NULL) {
        return 0;
    }
    fn_80183D14(q, a, b, c, d, e != 0);
    return 1;
}
#pragma use_lmw_stmw off

WIN_F_CALL1(fn_80095B8C, fn_80183E34)
WIN_F_CALL0(fn_80095C38, fn_80183E54)
WIN_TEST1(fn_80095CD4, fn_80183EA8)
WIN_CALL1(fn_80095D6C, fn_8018277C)
WIN_F_CALL1(fn_80095E04, fn_80182820)
WIN_F_CALL1(fn_80095EB0, fn_801828B8)
WIN_F_CALL1(fn_80095F5C, fn_8018295C)


#define WIN_F_CALL_BOOL(name, func)           \
void func(void* q, int a, BOOL b);            \
int name(int a, int b)                        \
{                                             \
    void* q;                                  \
    if (!IsValidPtr(lbl_803E5028)) {          \
        return 0;                             \
    }                                         \
    if (lbl_804CB700 & 0x8001) {              \
        return 0;                             \
    }                                         \
    q = fn_80184648(lbl_803E5028);            \
    if (q == NULL) {                          \
        return 0;                             \
    }                                         \
    func(q, a, b != 0);                       \
    return 1;                                 \
}

WIN_F_CALL_BOOL(fn_80096008, fn_801829F0)
WIN_F_CALL_BOOL(fn_800960CC, fn_80182A9C)

typedef struct WinEntry {
    s16 v0;
    u16 pad2;
    u16 flags4;
    u8 pad6[0xa];
} WinEntry;

void fn_80096190(UnitProc* proc)
{
    WinEntry* e = (WinEntry*)((u8*)proc->unit + 0x194);
    int i;
    for (i = 0; i < 8; i++) {
        if ((e[i].flags4 & 1) && e[i].v0 != 0) {
            return;
        }
    }
    fn_80083B78(proc);
}

extern u8 lbl_8038177C[0x14];

int fn_80096218(void)
{
    void* q;
    UnitProc* proc;
    if (!IsValidPtr(lbl_803E5028)) {
        return 0;
    }
    if (lbl_804CB700 & 0x8001) {
        return 0;
    }
    q = fn_80184648(lbl_803E5028);
    if (q == NULL) {
        return 0;
    }
    proc = (UnitProc*)fn_80081194(lbl_8038177C, fn_8009E898());
    if (proc == NULL) {
        return 0;
    }
    setFlag1C(fn_800C3558());
    setFlag1C(lbl_803E5064);
    proc->unit = q;
    return 1;
}


WIN_F_CALL1(fn_80096308, fn_80183EC8)
WIN_F_CALL1(fn_800963B4, fn_80183EEC)

void* fn_8010B094(u8 v);
#if TARGET_PC
FE10_PROTO ptr32<char> fn_800684A0(void* p);
#else
char* fn_800684A0(void* p);
#endif
void fn_802522E0(s8 ch, char* name, f32 vol, f32 b);
void fn_80068A58(void);

static inline int BgmPlay(char* name)
{
    if (!IsValidPtr(name)) {
        return 0;
    }
    if (!(lbl_804CB700 & 1)) {
        fn_802522E0(0, name, 1.0f, 0.0f);
    }
    fn_80068A58();
    return 1;
}

int fn_80096460(void)
{
    char* name = fn_800684A0(fn_8010B094(lbl_803CAB38.b10));
    if (!IsValidPtr(name)) {
        return 0;
    }
    return BgmPlay(name);
}

int fn_80096528(void)
{
    SndObj* snd = fn_8024F3FC(0);
    if (snd != NULL && snd->v10() != 0) {
        snd->v24(0x5dc);
    }
    fn_80068A4C();
    return 1;
}

void fn_8006B080(void* parent, char* s, int a, int b);
void fn_8006B81C(void* parent, char* s, int a, int b);
void fn_8006B3C4(void* parent, char* s, int a, int b);
void* fn_800A237C(void);
char* fn_800D0864(const char* s);
char* strchr(const char* s, int c);

#define MESS_CALL(name, func)                \
int name(char* s)                            \
{                                            \
    if (!IsValidPtr(s)) {                    \
        return 0;                            \
    }                                        \
    func(fn_8009E898(), s, 0, 0);            \
    setFlag1C(fn_800C3558());                \
    return 0;                                \
}

MESS_CALL(fn_80096598, fn_8006B080)
MESS_CALL(fn_8009661C, fn_8006B080)
MESS_CALL(fn_800966A0, fn_8006B81C)

int fn_80096724(char* s)
{
    if (!IsValidPtr(s)) {
        return 0;
    }
    if (strchr(fn_800D0864(s), '\n') == NULL) {
        fn_8006B080(fn_800A237C(), s, 0, 0);
    } else {
        fn_8006B3C4(fn_800A237C(), s, 0, 0);
    }
    setFlag1C(fn_800C3558());
    setFlag1C(lbl_803E5064);
    lbl_804CB700 = (lbl_804CB700 & ~0x80) | 0x400000;
    return 0;
}


int fn_800967F4(void)
{
    lbl_804CB700 &= ~0x400000;
    return 1;
}

void fn_8006BDCC(char* a, char* b);
void fn_8006BE30(char* a, char* b, char* c);
void fn_8006BEA0(char* a, char* b, char* c, int d, int e, int f);

int fn_80096808(char* a, char* b)
{
    if (!IsValidPtr(a)) {
        return 0;
    }
    if (!IsValidPtr(b)) {
        return 0;
    }
    fn_8006BDCC(a, b);
    setFlag1C(fn_800C3558());
    return 1;
}

int fn_800968A8(char* a, char* b, char* c)
{
    if (!IsValidPtr(a)) {
        return 0;
    }
    if (!IsValidPtr(b)) {
        return 0;
    }
    if (!IsValidPtr(c)) {
        return 0;
    }
    fn_8006BE30(a, b, c);
    setFlag1C(fn_800C3558());
    return 1;
}

int fn_80096980(char* a, char* b, char* c, int d, int e, int f)
{
    if (!IsValidPtr(a)) {
        return 0;
    }
    if (!IsValidPtr(b)) {
        return 0;
    }
    if (!IsValidPtr(c)) {
        return 0;
    }
    if (d < 0 || d > 3) {
        return 0;
    }
    if (e < 0 || e > 3) {
        return 0;
    }
    if (f < 0 || f > 3) {
        return 0;
    }
    fn_8006BEA0(a, b, c, d, e, f);
    setFlag1C(fn_800C3558());
    return 1;
}


void fn_8006BF64(char* a, char* b, char* c, char* d);
void fn_8006BFE0(void);
void fn_800C7B18(char* s, int v);

int fn_80096AA0(char* a, char* b, char* c, char* d)
{
    if (!IsValidPtr(a)) {
        return 0;
    }
    if (!IsValidPtr(b)) {
        return 0;
    }
    if (!IsValidPtr(c)) {
        return 0;
    }
    if (!IsValidPtr(d)) {
        return 0;
    }
    fn_8006BF64(a, b, c, d);
    setFlag1C(fn_800C3558());
    return 1;
}

void fn_80096BB0(void)
{
    fn_8006BFE0();
}

int fn_80096BB4(char* s)
{
    if (lbl_804CB700 & 0x8001) {
        return 0;
    }
    if (!IsValidPtr(s)) {
        return 0;
    }
    fn_800C7B18(s, 0);
    return 1;
}


u8* fn_800C400C(int id);
int fn_801D09F0(void);
f32 fn_801813D0(void* q, f32 x);
void fn_800C5EA4(int id, char* name, int x, int y, int flags, int a, int b);
#if TARGET_PC
FE10_PROTO void fn_800C7324(int id, int frames, p32arg);
FE10_PROTO void fn_800C755C(int id, int frames, p32arg);
#else
void fn_800C7324(int id, int frames, int v);
void fn_800C755C(int id, int frames, int v);
#endif
void fn_800C42F8(int id);
void fn_800C4348(int id);
#if TARGET_PC
FE10_PROTO void fn_800C777C(int id, int v, int frames, p32arg);
#else
void fn_800C777C(int id, int v, int frames, int w);
#endif

int fn_80096C28(int id, char* name, int x, int y, int ms, int flags)
{
    f32 fx;
    void* q;
    fn_800C400C(id);
    if (!IsValidPtr(name)) {
        return 0;
    }
    if (fn_801D09F0() == 0) {
        fx = x;
    } else {
        q = fn_80184648(lbl_803E5028);
        if (q == NULL) {
            fx = 0.7638191f * (x - 304.0f) + 304.0f;
        } else {
            fx = fn_801813D0(q, x);
        }
    }
    fn_800C5EA4(id, name, fx, y, flags | 0x80, 0, 0);
    fn_800C7324(id, ms * 60 / 1000, 0);
    return 1;
}

int fn_80096D8C(int id, int ms)
{
    fn_800C755C(id, ms * 60 / 1000, 0);
    return 1;
}

int fn_80096DD0(int id)
{
    fn_800C42F8(id);
    return 1;
}

int fn_80096DF4(int id)
{
    fn_800C4348(id);
    return 1;
}

int fn_80096E18(int id, int v, int ms)
{
    fn_800C777C(id, v, ms * 60 / 1000, 0);
    return 1;
}


typedef struct FaceProc {
    u8 pad0[0x3c];
    f32 fromX;  /* 0x3C */
    f32 fromY;  /* 0x40 */
    u8 pad44[4];
    f32 toX;    /* 0x48 */
    f32 toY;    /* 0x4C */
    u8 pad50[0x10];
    int id;     /* 0x60 */
    int mode;   /* 0x64 */
    int time;   /* 0x68 */
    int duration; /* 0x6C */
} FaceProc;

void fn_80096E5C(FaceProc* proc)
{
    u8* face = fn_800C400C(proc->id);
    if (face == NULL) {
        fn_80083B78(proc);
        return;
    }
    proc->time++;
    if (lbl_804CB700 & 0x8001) {
        proc->time = proc->duration;
    }
    *(f32*)(face + 0x38) = fn_8017F68C(proc->mode, proc->fromX, proc->toX, proc->time, proc->duration);
    *(f32*)(face + 0x3c) = fn_8017F68C(proc->mode, proc->fromY, proc->toY, proc->time, proc->duration);
    if (proc->time >= proc->duration) {
        fn_80083B78(proc);
    }
}

extern u8 lbl_80381790[0x14];

int fn_80096F70(int id, int x, int y, int ms, int mode)
{
    u8* face = fn_800C400C(id);
    FaceProc* proc;
    f32 fx;
    void* q;
    if (face == NULL) {
        return 0;
    }
    proc = (FaceProc*)fn_80081050(lbl_80381790, fn_8009E898());
    if (proc == NULL) {
        return 0;
    }
    proc->fromX = *(f32*)(face + 0x38);
    if (fn_801D09F0() == 0) {
        fx = x;
    } else {
        q = fn_80184648(lbl_803E5028);
        if (q == NULL) {
            fx = 0.7638191f * (x - 304.0f) + 304.0f;
        } else {
            fx = fn_801813D0(q, x);
        }
    }
    proc->toX = fx;
    proc->fromY = *(f32*)(face + 0x3c);
    proc->toY = y;
    proc->id = id;
    switch (mode) {
    case 0:
        proc->mode = 0;
        break;
    case 1:
        proc->mode = 1;
        break;
    case 2:
        proc->mode = 4;
        break;
    }
    proc->time = 0;
    proc->duration = ms * 60 / 1000;
    return 1;
}


BOOL fn_80097114(int id)
{
    return fn_800C400C(id) != NULL;
}

#if TARGET_PC
FE10_PROTO void fn_801ADB38(s16 a, s16 b, int c, ptr32<const void>, int e, int f, int g, void* parent);
FE10_PROTO void fn_801ADC34(s8 a, s16 b, s16 c, ptr32<const void>, int e, void* parent);
#else
void fn_801ADB38(s16 a, s16 b, int c, char* d, int e, int f, int g, void* parent);
void fn_801ADC34(s8 a, s16 b, s16 c, char* d, int e, void* parent);
#endif
void fn_801ADD1C(s8 a, int b);
void fn_801ADD8C(int a);

#pragma use_lmw_stmw on
int fn_80097140(int a, int b, int c, char* d, int e, int f, int g)
{
    if (!IsValidPtr(d)) {
        return 0;
    }
    fn_801ADB38(a, b, c, d, e, f, g, fn_8009E898());
    return 1;
}

int fn_800971E4(int a, int b, int c, char* d, int e)
{
    if (!IsValidPtr(d)) {
        return 0;
    }
    fn_801ADC34(a, b, c, d, e, fn_8009E898());
    return 1;
}
#pragma use_lmw_stmw off

int fn_80097278(int a, int b)
{
    fn_801ADD1C(a, b);
    return 1;
}

int fn_800972A0(int a)
{
    fn_801ADD8C(a);
    return 1;
}


#if TARGET_PC
FE10_PROTO void fn_801ADA54(s16 a, s16 b, i32arg name, int d, int e, ...);
#else
void fn_801ADA54(s16 a, s16 b, char* name, int d, int e, void* parent);
#endif

#pragma use_lmw_stmw on
int fn_800972C4(int a, int b, char* name, int d, int e)
{
    if (!IsValidPtr(name)) {
        return 0;
    }
    fn_801ADA54(a, b, name, d, e, fn_8009E898());
    return 1;
}
#pragma use_lmw_stmw off

int fn_80097358(int a, int ms)
{
    if (ms < 0) {
        ms = 500;
    }
    fn_800C835C(a, ms);
    return 1;
}

void fn_800C7F90(void);
int fn_800C7FF4(void);
void fn_800C86D4(u8 r, u8 g, u8 b, int a, int c);

void fn_8009738C(void)
{
    fn_800C7F90();
}

u8 fn_80097390(void)
{
    return fn_800C7FF4();
}

int fn_800973B4(int r, int g, int b, int a, int c)
{
    if (r < 0) {
        r = 0;
    }
    if (r > 0xff) {
        r = 0xff;
    }
    if (g < 0) {
        g = 0;
    }
    if (g > 0xff) {
        g = 0xff;
    }
    if (b < 0) {
        b = 0;
    }
    if (b > 0xff) {
        b = 0xff;
    }
    if (a < 0) {
        a = 500;
    }
    if (c < 0) {
        c = 500;
    }
    fn_800C86D4(r, g, b, a, c);
    return 1;
}


int fn_800C8778(void);
void fn_800C8C3C(int ms);
void fn_800C8C90(int ms);
void fn_800C8CE4(void);
int fn_800C8CF4(void);
extern u8 lbl_803817A4[0x14];

void fn_80097444(void* proc)
{
    if (fn_800C8778() == 0) {
        fn_80083B78(proc);
    }
}

int fn_80097480(void)
{
    if (fn_800C8778() != 0) {
        fn_80081194(lbl_803817A4, fn_8009E898());
        setFlag1C(fn_800C3558());
        setFlag1C(lbl_803E5064);
    }
    return 1;
}

int fn_800974D8(void)
{
    return fn_800C8778();
}

int fn_800974DC(int ms)
{
    if (ms < 0) {
        ms = 2000;
    }
    fn_800C8C3C(ms);
    return 1;
}

int fn_8009750C(int ms)
{
    if (ms < 0) {
        ms = 2000;
    }
    fn_800C8C90(ms);
    return 1;
}

int fn_8009753C(void)
{
    fn_800C8CE4();
    return 1;
}

void fn_80097560(void* proc)
{
    if (fn_800C8CF4() == 0) {
        fn_80083B78(proc);
    }
}


extern u8 lbl_803817B8[0x14];

int fn_8009759C(void)
{
    if (fn_800C8CF4() != 0) {
        fn_80081194(lbl_803817B8, fn_8009E898());
        setFlag1C(fn_800C3558());
        setFlag1C(lbl_803E5064);
    }
    return 1;
}

int fn_800975F4(void)
{
    return fn_800C8CF4();
}

void fn_80084F0C(char* s);

int fn_800975F8(char* s)
{
    if (!IsValidPtr(s)) {
        return 0;
    }
    fn_80084F0C(s);
    return 0;
}

int fn_80097654(char* s)
{
    if (!IsValidPtr(s)) {
        return 0;
    }
    return fn_80085708(s);
}

/* Parses a pad button string such as "AB2" into a button mask. */
u32 fn_80097694(const char* s)
{
    u32 mask = 0;
    for (; *s != '\0'; s++) {
        switch (*s) {
        case '2':
            mask |= 0x400004;
            break;
        case '4':
            mask |= 0x100001;
            break;
        case '6':
            mask |= 0x200002;
            break;
        case '8':
            mask |= 0x800008;
            break;
        case 'A':
            mask |= 0x400;
            break;
        case 'B':
            mask |= 0x800;
            break;
        case 'X':
            mask |= 0x1000;
            break;
        case 'Y':
            mask |= 0x2000;
            break;
        case 'Z':
            mask |= 0x10;
            break;
        case 'L':
            mask |= 0x40;
            break;
        case 'R':
            mask |= 0x100;
            break;
        case 'S':
            mask |= 0x4000;
            break;
        case '*':
            mask |= 0xffffffff;
            break;
        }
    }
    return mask;
}


#define VSLOT(n) virtual void v##n();
class PadObj {
public:
    VSLOT(00) VSLOT(01) VSLOT(02) VSLOT(03) VSLOT(04) VSLOT(05) VSLOT(06) VSLOT(07)
    VSLOT(08) VSLOT(09) VSLOT(10) VSLOT(11) VSLOT(12) VSLOT(13) VSLOT(14) VSLOT(15)
    VSLOT(16) VSLOT(17) VSLOT(18) VSLOT(19) VSLOT(20) VSLOT(21) VSLOT(22) VSLOT(23)
    VSLOT(24) VSLOT(25) VSLOT(26) VSLOT(27) VSLOT(28) VSLOT(29) VSLOT(30) VSLOT(31)
    VSLOT(32)
    virtual void setMask(u32 mask);    /* 0x8C */
    virtual void resetMask(u32 mask);  /* 0x90 */
};

extern PadObj* lbl_804CB5B8;

int fn_80097754(const char* s)
{
    lbl_804CB5B8->setMask(fn_80097694(s));
    return 0;
}

int fn_80097790(const char* s)
{
    lbl_804CB5B8->resetMask(fn_80097694(s));
    return 0;
}

/* Netuzo* commands: settings for a scripted battle. */
typedef struct NetuzoState {
    u8 b[0x20];     /* 0x00 */
    s16 h20[0x20];  /* 0x20 */
    s16 h60[0x20];  /* 0x60 */
    u8 a0;          /* 0xA0 */
    u8 a1;          /* 0xA1 */
    u8 a2;          /* 0xA2 */
    u8 a3;          /* 0xA3 */
    u8 a4;          /* 0xA4 */
    s8 a5;          /* 0xA5 */
    u8 a6;          /* 0xA6 */
    u8 padA7[0x21];
    void* items[2]; /* 0xC8 */
} NetuzoState;

extern NetuzoState lbl_803C8DA0;

static inline void NetuzoInit(void)
{
    int i;
    lbl_803C8DA0.a1 = 0;
    lbl_803C8DA0.a2 = 0;
    lbl_803C8DA0.a3 = 0;
    lbl_803C8DA0.a4 = 0;
    lbl_803C8DA0.a0 = 0;
    for (i = 0; i < 0x20; i++) {
        lbl_803C8DA0.b[i] = 0;
        lbl_803C8DA0.h20[i] = 0;
        lbl_803C8DA0.h60[i] = 12345;
    }
    lbl_803C8DA0.a5 = -1;
    lbl_803C8DA0.a6 = 0;
    lbl_803C8DA0.items[0] = NULL;
    lbl_803C8DA0.items[1] = NULL;
}

int fn_800977CC(void)
{
    NetuzoInit();
    return 1;
}

int fn_800978F0(int i, int b, int h)
{
    lbl_803C8DA0.a1 = 1;
    lbl_803C8DA0.b[i] = b;
    lbl_803C8DA0.h20[i] = h;
    lbl_803C8DA0.h60[i] = 12345;
    lbl_803C8DA0.b[i + 1] = 8;
    return 1;
}

int fn_8009792C(int i, int b, int h, int h2)
{
    lbl_803C8DA0.a1 = 1;
    lbl_803C8DA0.b[i] = b;
    lbl_803C8DA0.h20[i] = h;
    lbl_803C8DA0.h60[i] = h2;
    lbl_803C8DA0.b[i + 1] = 8;
    return 1;
}

int fn_80097964(int v)
{
    if (v != 0) {
        lbl_803C8DA0.a3 = 1;
    } else {
        lbl_803C8DA0.a3 = 0;
    }
    return 1;
}

int fn_80097998(void)
{
    lbl_803C8DA0.a2 = 1;
    return 1;
}

#if TARGET_PC
FE10_PROTO void fn_80025F88(NetuzoState* st, p32arg);
#else
void fn_80025F88(NetuzoState* st, int v);
#endif
void fn_80025FC0(NetuzoState* st, s8 v);

int fn_800979B0(int v)
{
    fn_80025F88(&lbl_803C8DA0, v);
    return 1;
}

int fn_800979E0(void)
{
    lbl_803C8DA0.a4 = 1;
    return 1;
}

int fn_800979F8(int v)
{
    fn_80025FC0(&lbl_803C8DA0, v);
    return 1;
}


int fn_80097A2C(int i, void* x)
{
    void* d = fn_8010B228(x);
    if (d == NULL) {
        return 0;
    }
    lbl_803C8DA0.items[(s8)i] = d;
    return 1;
}

void fn_80026C44(BattleState* b, void* attacker, void* defender);
void fn_8002B2AC(BattleState* b, int a, int c);
void fn_800262D8(void* p);
void fn_8002BCC4(BattleState* b);
void fn_800FBDF0(void* p);
void fn_8004984C(void* parent);

int fn_80097A88(int a, int b, int flag)
{
    u8* p;
    u8* u1 = GetUnit(a);
    u8* u2 = GetUnit(b);
    if (u1 == NULL || u2 == NULL) {
        NetuzoInit();
        return 0;
    }
    fn_80026C44(&lbl_803C8E80, u1, u2);
    fn_8002B2AC(&lbl_803C8E80, 0xf, 1);
    fn_800262D8(lbl_803C8E80.sub);
    if (flag != 0) {
        lbl_803C8E80.flag31 = 1;
        lbl_803C8E80.flag30 = 0;
    } else {
        lbl_803C8E80.flag31 = 0;
    }
    if (lbl_804CB700 & 0x8001) {
        fn_8002BCC4(&lbl_803C8E80);
        p = fn_8002C590(&lbl_803C8E80);
        if (p != NULL && *(void**)(p + 0x3f0) != NULL) {
            fn_800FBDF0(*(void**)(p + 0x3f0));
        }
        return 0;
    }
    fn_8004984C(fn_8009E898());
    setFlag1C(fn_800C3558());
    return 1;
}


/* Terrain tiles: AddTT, ClrTT, GetTT, SetFragile, SetPit, SetRock... */
typedef struct MapThing {
    s8 x;
    s8 y;
    u8 b2;
    u8 b3;
    u8 b4;
    u8 b5;
    u8 b6;
    u8 b7;
} MapThing;

extern u8 lbl_803CB770[];
MapThing* fn_800661A0(void* p, s8 x, s8 y, u8 a, u8 b);
MapThing* fn_80066130(void* p, s8 x, s8 y, u8 n);
void fn_80065E4C(MapThing* m, int v);
void fn_80065FB0(MapThing* m, int v);
void fn_8006625C(void* p, s8 x, s8 y, u8 n);
int fn_800660F0(void* p, u8 n);
void fn_800660C4(void* p);

int fn_80097CD8(int x, int y, int a, int b, int c, int d)
{
    MapThing* m = fn_800661A0(lbl_803CB770, x, y, a, b);
    if (m != NULL) {
        m->b4 = c;
        m->b5 = d;
        m->b6 = 0;
        m->b7 = 0;
        fn_80065E4C(m, 0x1e);
        return 1;
    }
    return 0;
}

int fn_80097D68(int x, int y, int n)
{
    MapThing* m = fn_80066130(lbl_803CB770, x, y, n);
    if (m != NULL) {
        fn_80065FB0(m, 0x3c);
        fn_8006625C(lbl_803CB770, x, y, n);
        return 1;
    }
    return 0;
}

u8 fn_80097DF8(int x, int y, int n)
{
    MapThing* m = fn_80066130(lbl_803CB770, x, y, n);
    if (m != NULL) {
        return m->b2;
    }
    return 0;
}

int fn_80097E48(int n)
{
    return fn_800660F0(lbl_803CB770, n);
}

int fn_80097E5C(void)
{
    fn_800660C4(lbl_803CB770);
    return 1;
}

int fn_80097E88(int x, int y, int c)
{
    MapThing* m = fn_800661A0(lbl_803CB770, x, y, 4, 0);
    m->b4 = c;
    m->b5 = c;
    m->b6 = 0;
    m->b7 = 0;
    return 1;
}


void fn_800663D8(void* p, s8 x, s8 y, u8 n, void* data);
#if TARGET_PC
FE10_PROTO void fn_800664A4(void* p, s8 x, s8 y, u8 n, p32arg);
#else
void fn_800664A4(void* p, s8 x, s8 y, u8 n, int v);
#endif

int fn_80097EEC(int x, int y, int n, void* item)
{
    fn_800663D8(lbl_803CB770, x, y, n, fn_8010B228(item));
    return 1;
}

int fn_80097F54(int x, int y)
{
    fn_800661A0(lbl_803CB770, x, y, 9, 0);
    return 1;
}

int fn_80097F98(int x, int y, int n, int v)
{
    fn_800664A4(lbl_803CB770, x, y, n, v);
    return 1;
}

int fn_80097FE0(int x, int y)
{
    fn_800661A0(lbl_803CB770, x, y, 0xb, 0);
    return 1;
}

int fn_80098024(int x, int y, int a, int b, int c)
{
    MapThing* m = fn_800661A0(lbl_803CB770, x, y, 0xe, 0);
    m->b4 = a;
    m->b5 = b;
    m->b6 = c;
    m->b7 = 0;
    return 1;
}


int fn_800980A0(int x, int y, int n)
{
    fn_800661A0(lbl_803CB770, x, y, 0xf, n);
    return 1;
}

void fn_800980E4(void* proc)
{
    if (fn_80085708(lbl_80363B74 + 0x1b) == 0) { /* "E_JyokyoMapCapture" */
        fn_80083B78(proc);
    }
}

extern u8 lbl_80381890[0x14];
void fn_801A7BB0(void);
void fn_801A7BE0(void* parent);
void fn_801A7C88(void);
void fn_801A7CCC(void);
void fn_801A7C48(void);
void fn_801A7D10(void);

int fn_8009812C(void)
{
    fn_801A7BB0();
    fn_80081194(lbl_80381890, fn_8009E898());
    setFlag1C(fn_800C3558());
    setFlag1C(lbl_803E5064);
    return 1;
}

int fn_8009817C(void)
{
    fn_801A7BE0(fn_8009E898());
    return 1;
}

#define CALL_RET1(name, func) \
int name(void)                \
{                             \
    func();                   \
    return 1;                 \
}

CALL_RET1(fn_800981A4, fn_801A7C88)
CALL_RET1(fn_800981C8, fn_801A7CCC)
CALL_RET1(fn_800981EC, fn_801A7C48)
CALL_RET1(fn_80098210, fn_801A7D10)


int fn_80098234(int ch, char* name)
{
    if (!IsValidPtr(name)) {
        return 0;
    }
    if (!(lbl_804CB700 & 1)) {
        fn_802522E0(ch, name, 1.0f, 0.0f);
    }
    if (ch == 0) {
        fn_80068A58();
    }
    return 1;
}

int fn_800982C0(int ch, char* name)
{
    if (!IsValidPtr(name)) {
        return 0;
    }
    fn_802522E0(ch, name, 1.0f, 0.0f);
    if (ch == 0) {
        fn_80068A58();
    }
    return 1;
}

int fn_80098340(int ch, char* name, int vol)
{
    if (!IsValidPtr(name)) {
        return 0;
    }
    if (!(lbl_804CB700 & 1)) {
        fn_802522E0(ch, name, vol / 100.0f, 0.0f);
    }
    if (ch == 0) {
        fn_80068A58();
    }
    return 1;
}


int fn_800983EC(int ch, int vol, int time)
{
    SndObj* snd = fn_8024F3FC(ch);
    if (snd != NULL && snd->v10() != 0) {
        snd->v38(vol / 100.0f, time);
    }
    return 1;
}

int fn_800984A4(int ch)
{
    SndObj* snd = fn_8024F3FC(ch);
    if (snd != NULL && snd->v10() != 0) {
        snd->v24(0);
    }
    if (ch == 0) {
        fn_80068A4C();
    }
    return 1;
}

int fn_80098528(int ch, char* name, int time)
{
    if (!IsValidPtr(name)) {
        return 0;
    }
    if (!(lbl_804CB700 & 1)) {
        fn_80251838(ch, name, time);
    }
    if (ch == 0) {
        fn_80068A58();
    }
    return 1;
}


int fn_800985C8(int ch, int t)
{
    SndObj* snd = fn_8024F3FC(ch);
    if (snd != NULL && snd->v10() != 0) {
        snd->v24(t);
    }
    if (ch == 0) {
        fn_80068A4C();
    }
    return 1;
}

int fn_80098658(int ch, int t)
{
    SndObj* snd = fn_8024F3FC(ch);
    if (snd != NULL && snd->v10() != 0) {
        snd->v28(t);
    }
    if (ch == 0) {
        fn_80068A4C();
    }
    return 1;
}

int fn_800986E8(int ch, int t)
{
    SndObj* snd = fn_8024F3FC(ch);
    if (snd != NULL && snd->v10() != 0) {
        snd->v2C(t);
    }
    if (ch == 0) {
        fn_80068A58();
        if (snd != NULL && snd->v10() != 0) {
            snd->v38(1.0f, t);
        }
    }
    return 1;
}


void fn_80250D64(int ch, f32 vol, f32 time);

int fn_800987D0(int t)
{
    fn_80250D64(6, 0.5f, t);
    return 1;
}

int fn_80098818(int t)
{
    fn_80250D64(6, 1.0f, t);
    return 1;
}

int fn_80098860(int t)
{
    fn_80250D64(6, 0.0f, t);
    return 1;
}

int fn_800988A8(int t)
{
    fn_80250D64(6, 1.0f, t);
    return 1;
}


int fn_800988F0(int t)
{
    fn_800988A8(t);
    fn_800986E8(0, t);
    fn_800985C8(1, t);
    fn_800985C8(2, t);
    fn_800985C8(3, t);
    return 1;
}

}
