/* Round 23 (r23b), exact: fn_80092F74. From equiv/fn_80092F74.cpp: the free-slot search walks a second induction
   variable, the table viewed 4*i bytes further on (`q->names[0]` is `names[i]`, as flagFindR in evflags.h does),
   stepped after the pointer in the for header. Port: plain `names[i]` is the same thing. */
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
u32 fn_80092D04(ModeArrays* m, int idx);

u32 fn_80092D88(ModeArrays* m, int idx);


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
int fn_80092E38(char* name);



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
int fn_8009317C(const char* name);


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
int fn_80093254(const char* name);



/* String pool: "E_Talk", "BGM_DEAD1", "BGM_DEAD2", ... (see NOTES.md) */
extern char lbl_80363B74[];
#if TARGET_PC
FE10_PROTO extern unsigned int lbl_804CB878;
#else
extern u32 lbl_804CB878[2];
#endif
extern u32 lbl_804CB700;
extern u8* lbl_804CB810;
extern u8 lbl_80381678[0x14];
extern u8 lbl_8038168C[0x14];
extern u8 lbl_803816A0[0x14];
extern u8 lbl_803E5064[0x24];

#if TARGET_PC
FE10_PROTO struct Proc * fn_80085708(const char* name);
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
int fn_80093328(void* ctx);

int fn_80093388(void* ctx);

int fn_800933E8(void* ctx);

int fn_8009340C(void* ctx);

BOOL fn_80093458(void);

int fn_800934A0(void* ctx, const char* str);

int fn_800934C4(void* ctx, void* p);

int fn_800934E8(void* ctx, void* p);

int fn_8009352C(int x, int y);

int fn_8009358C(int x, int y);

void fn_80093630(void* proc);


/* An inline setter keeps the constant 1 out of a callee-saved register. */
static inline void setFlag1C(u8* p)
{
    p[0x1c] = 1;
}
int fn_8009368C(void);

void fn_80093708(void* proc);

int fn_80093764(void);

int fn_800937E0(int id);



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
int fn_800938C4(void);

int fn_8009394C(void);

int fn_80093AB0(int id);


#pragma use_lmw_stmw on

int fn_80093B20(void);

#pragma use_lmw_stmw off

int fn_80093C98(int id);



#pragma use_lmw_stmw on

int fn_80093D50(int army);

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
void fn_80093E38(ProcFlags* p);

void fn_80093F68(ProcFlags* p);


typedef struct UnitItem {
    u8 data[0x28];
} UnitItem;

void fn_80111B34(UnitItem* item);
void fn_80111B64(UnitItem* item, UnitItem* src);
void fn_80111C24(UnitItem* item, int flag);
void fn_80110BB4(UnitItem* item, void* data);
void fn_8004AD18(void* a, UnitItem* item, void* proc);
void fn_8009401C(ProcFlags* p);



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
int fn_8009408C(int id, void* x);

int fn_8009419C(int id, void* x);


int fn_800626E0(FlagTable* t);
void fn_800615DC(FlagTable* t, int v);
void fn_80031984(int v, void* proc, void* unit);
void fn_80094240(UnitProc* proc);

int fn_800942A0(int v);


void fn_8025F6A0(const char* name);
void fn_8025F6A8(const char* name);
void fn_8025F6B0(const char* name);
void fn_8025FFF0(int v);
void fn_800942F0(const char* name);

int fn_800942F4(const char* name);

int fn_80094318(const char* name);

int fn_8009433C(void);


#define IsValidPtr(p) \
    (((u32)(p) >= 0x80000000 && (u32)(p) < 0x81800000) || ((u32)(p) >= 0x90000000 && (u32)(p) < 0x98000000))

void* fn_800D4228(void* p);
void fn_800D4188(void* p, void* parent);
void fn_800D42A0(void* p);
f32 fn_800D3DA8(void* p, u8 v);
int fn_80094364(void* p);

int fn_800943F0(void* p);

int fn_80094478(void* p);

int fn_800944D4(void);

int fn_800944FC(void* p, int v);



void fn_800D3D00(void* q, u8 kind, f32 v);
void fn_800D3EE0(void* q, int kind, int b, f32 x, f32 y, f32 z);
void fn_800D39D4(void* q, int v);
int fn_80094584(void* p, int kind, int val);

int fn_80094648(void* p, int kind, int b, int x, int y, int z);

int fn_8009475C(void* p, int v);



typedef struct Sprite {
    u8 pad0[0x40];
    f32 x;    /* 0x40 */
    f32 y;    /* 0x44 */
    u8 pad48[0xc];
    f32 v54;  /* 0x54 */
    f32 v58;  /* 0x58 */
} Sprite;
int fn_800947DC(void* p, int x, int y);


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
void fn_80094898(MoveProc* proc);



extern u8 lbl_80381768[0x14];
int fn_80094A68(void* p, int x, int y, int dur, int v68, f32 scale);

int fn_80094BE4(void* p, int x, int y, int pct, int dur, int v68);

int fn_80094C80(void* p, int x, int y, int dur, int v68);


void fn_800D3BCC(void* q, u8 v);
int fn_80094C88(void* p, int v);



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




void fn_800D3928(void* q, f32 v);
f32 fn_800D395C(void* q);
int fn_80094E08(void* p, int v);

int fn_80094EA0(void* p);


extern char lbl_803E5028[0x18];
char* strcpy(char* dst, const char* src);
void fn_8018454C(void* p, void* parent);
void* fn_80184648(void* p);
void fn_80184324(void* q);
int fn_80094F18(char* s);

int fn_80094F80(void* p);

int fn_80094FF4(void* p);

int fn_80095064(int x, int y);



void fn_80183F0C(void* q, f32 x, f32 y, f32 sx, f32 sy, int dur, int mode);
int fn_80095138(int x, int y, int dur, int mode, f32 sx, f32 sy);

int fn_80095294(int x, int y, int sx, int sy, int dur, int mode);

int fn_80095350(int x, int y, int sx, int sy, int dur, int mode);



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





#if TARGET_PC
FE10_PROTO void fn_80183BC8(void* q, int a, p32arg);
#else
void fn_80183BC8(void* q, int a, int b);
#endif
int fn_8009581C(int a, int b);






void fn_80183D14(void* q, int a, int b, int c, int d, BOOL e);

#pragma use_lmw_stmw on

int fn_80095AB8(int a, int b, int c, int d, int e);

#pragma use_lmw_stmw off










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




typedef struct WinEntry {
    s16 v0;
    u16 pad2;
    u16 flags4;
    u8 pad6[0xa];
} WinEntry;
void fn_80096190(UnitProc* proc);


extern u8 lbl_8038177C[0x14];
int fn_80096218(void);






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
int fn_80096460(void);

int fn_80096528(void);


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

int fn_80096724(char* s);

int fn_800967F4(void);


void fn_8006BDCC(char* a, char* b);
void fn_8006BE30(char* a, char* b, char* c);
void fn_8006BEA0(char* a, char* b, char* c, int d, int e, int f);
int fn_80096808(char* a, char* b);

int fn_800968A8(char* a, char* b, char* c);

int fn_80096980(char* a, char* b, char* c, int d, int e, int f);



void fn_8006BF64(char* a, char* b, char* c, char* d);
void fn_8006BFE0(void);
void fn_800C7B18(char* s, int v);
int fn_80096AA0(char* a, char* b, char* c, char* d);

void fn_80096BB0(void);

int fn_80096BB4(char* s);



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
int fn_80096C28(int id, char* name, int x, int y, int ms, int flags);

int fn_80096D8C(int id, int ms);

int fn_80096DD0(int id);

int fn_80096DF4(int id);

int fn_80096E18(int id, int v, int ms);



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
void fn_80096E5C(FaceProc* proc);


extern u8 lbl_80381790[0x14];
int fn_80096F70(int id, int x, int y, int ms, int mode);

BOOL fn_80097114(int id);


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

int fn_80097140(int a, int b, int c, char* d, int e, int f, int g);

int fn_800971E4(int a, int b, int c, char* d, int e);

#pragma use_lmw_stmw off

int fn_80097278(int a, int b);

int fn_800972A0(int a);



#if TARGET_PC
FE10_PROTO void fn_801ADA54(s16 a, s16 b, ptr32<const void>, int d, int e);
#else
void fn_801ADA54(s16 a, s16 b, char* name, int d, int e, void* parent);
#endif

#pragma use_lmw_stmw on

int fn_800972C4(int a, int b, char* name, int d, int e);

#pragma use_lmw_stmw off

int fn_80097358(int a, int ms);


void fn_800C7F90(void);
int fn_800C7FF4(void);
void fn_800C86D4(u8 r, u8 g, u8 b, int a, int c);
void fn_8009738C(void);

u8 fn_80097390(void);

int fn_800973B4(int r, int g, int b, int a, int c);



int fn_800C8778(void);
void fn_800C8C3C(int ms);
void fn_800C8C90(int ms);
void fn_800C8CE4(void);
int fn_800C8CF4(void);
extern u8 lbl_803817A4[0x14];
void fn_80097444(void* proc);

int fn_80097480(void);

int fn_800974D8(void);

int fn_800974DC(int ms);

int fn_8009750C(int ms);

int fn_8009753C(void);

void fn_80097560(void* proc);



extern u8 lbl_803817B8[0x14];
int fn_8009759C(void);

int fn_800975F4(void);


void fn_80084F0C(char* s);
int fn_800975F8(char* s);

int fn_80097654(char* s);

u32 fn_80097694(const char* s);



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
int fn_80097754(const char* s);

int fn_80097790(const char* s);


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
int fn_800977CC(void);

int fn_800978F0(int i, int b, int h);

int fn_8009792C(int i, int b, int h, int h2);

int fn_80097964(int v);

int fn_80097998(void);


#if TARGET_PC
FE10_PROTO void fn_80025F88(NetuzoState* st, p32arg);
#else
void fn_80025F88(NetuzoState* st, int v);
#endif
void fn_80025FC0(NetuzoState* st, s8 v);
int fn_800979B0(int v);

int fn_800979E0(void);

int fn_800979F8(int v);

int fn_80097A2C(int i, void* x);


void fn_80026C44(BattleState* b, void* attacker, void* defender);
void fn_8002B2AC(BattleState* b, int a, int c);
void fn_800262D8(void* p);
void fn_8002BCC4(BattleState* b);
void fn_800FBDF0(void* p);
void fn_8004984C(void* parent);
int fn_80097A88(int a, int b, int flag);



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
int fn_80097CD8(int x, int y, int a, int b, int c, int d);

int fn_80097D68(int x, int y, int n);

u8 fn_80097DF8(int x, int y, int n);

int fn_80097E48(int n);

int fn_80097E5C(void);

int fn_80097E88(int x, int y, int c);



void fn_800663D8(void* p, s8 x, s8 y, u8 n, void* data);
#if TARGET_PC
FE10_PROTO void fn_800664A4(void* p, s8 x, s8 y, u8 n, p32arg);
#else
void fn_800664A4(void* p, s8 x, s8 y, u8 n, int v);
#endif
int fn_80097EEC(int x, int y, int n, void* item);

int fn_80097F54(int x, int y);

int fn_80097F98(int x, int y, int n, int v);

int fn_80097FE0(int x, int y);

int fn_80098024(int x, int y, int a, int b, int c);

int fn_800980A0(int x, int y, int n);

void fn_800980E4(void* proc);


extern u8 lbl_80381890[0x14];
void fn_801A7BB0(void);
void fn_801A7BE0(void* parent);
void fn_801A7C88(void);
void fn_801A7CCC(void);
void fn_801A7C48(void);
void fn_801A7D10(void);
int fn_8009812C(void);

int fn_8009817C(void);


#define CALL_RET1(name, func) \
int name(void)                \
{                             \
    func();                   \
    return 1;                 \
}

int fn_80098234(int ch, char* name);

int fn_800982C0(int ch, char* name);

int fn_80098340(int ch, char* name, int vol);

int fn_800983EC(int ch, int vol, int time);

int fn_800984A4(int ch);

int fn_80098528(int ch, char* name, int time);

int fn_800985C8(int ch, int t);

int fn_80098658(int ch, int t);

int fn_800986E8(int ch, int t);



void fn_80250D64(int ch, f32 vol, f32 time);
int fn_800987D0(int t);

int fn_80098818(int t);

int fn_80098860(int t);

int fn_800988A8(int t);

int fn_800988F0(int t);


}

/* ---- from build/tmp/r19hpbs/frag_2f74.cpp ---- */
extern "C" {
/*
 * fn_80092F74: 8 of 68 words differ, all a swap of r4/r5 (want counter r4, slot pointer r5).
 * Same flag helpers as fn_80092E38 in ../fn_80092D04.cpp.
 */
static inline BOOL flagSlotUsedQ(FlagTable* q, int i)
{
    return i >= 0 && i < 0x80 && q->names[0] != NULL;
}
int fn_80092F74(char* name)
{
    int i;
    FlagTable* q;
    if (flagFind(&lbl_803CAB38, name) < 0) {
        for (i = 0x7f, q = (FlagTable*)((u32*)&lbl_803CAB38 + 0x7f); i >= 0; q = (FlagTable*)((u32*)q - 1), i--) {
            if (!flagSlotUsedQ(q, i)) {
                lbl_803CAB38.names[i] = name;
                lbl_803CAB38.hashes[i] = fn_80076D18(name);
                break;
            }
        }
    }
    return 1;
}
}
