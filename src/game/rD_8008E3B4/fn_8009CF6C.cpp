/* Script system startup, global flags, event caller: 0x8009CF6C..0x8009E7CC. */
#include "game/rD_8008E3B4/types.h"

extern "C" {

typedef struct FlagTable {
    u8 pad0[0x144];
    char* names[0x80];  /* 0x144 */
    u32 hashes[0x80];   /* 0x344 */
    u8 bits[0x10];      /* 0x544 */
    u8 pad554[0x988 - 0x554];
} FlagTable;

extern FlagTable lbl_803CAB38;
u32 fn_80076D18(const char* s);        /* string hash */
int fn_80291188(const char* a, const char* b); /* strcmp */

extern u32 lbl_804CB700;
extern char lbl_80364A70[];
extern char lbl_80364B30[];
extern u8 lbl_80381B58[];
extern u8 lbl_80381B80[];
extern u8 lbl_80379FA8[];
extern u8 lbl_80379F58[];
extern u8 lbl_8037DB60[];
extern u8 lbl_803C8DA0[];
extern u8 lbl_803CA870[];
extern u32 lbl_804CB620;
extern u32 lbl_804CB624;

/* Three 0x24-byte script contexts at 0x803E5040. */
static u8 sCtx0[0x24];
static u8 sCtx1[0x24];
static u8 sCtx2[0x24];

void fn_800C3784(int a, int b);
void fn_801D0B20(void* ctx, int n);
void fn_800C3560(void* ctx);
void fn_80091E38(void);
void fn_8009AE54(void);
void fn_800A35E0(void);
void fn_80181318(void);
void fn_800E1048(void);
void fn_8009CEA4(void);
void fn_801D0B08(void);
void fn_800C3840(const char* name, int k);
u8* fn_800C3558(void);
#if TARGET_PC
FE10_PROTO void * fn_800C357C(void);
#else
int fn_800C357C(void);
#endif
void fn_801D0C88(void* ctx, void* v);
void* fn_800C3BC8(void* p);
void fn_80256A78(f32 v);
void* fn_80083B84(void* cls);
void fn_800846BC(void* cls);
void fn_800C900C(int a, int b);
void fn_80250E38(int k, f32 a, f32 b);
void fn_80250F0C(int k, f32 a, f32 b);
void fn_80250FE0(int k, f32 a, f32 b);
void fn_80250D64(int k, f32 a, f32 b);
u8* fn_80251174(int k);
u8* fn_8025121C(int k);
void* fn_80076F54(void* p);
void* fn_80081194(void* cls, void* parent);
void* fn_80081050(void* cls, void* parent);
void fn_801D0D58(void* ctx, void* p);
void fn_801D0E18(void* ctx);
void fn_80081A90(void* p);
void* fn_80085708(const char* name);
void fn_80084F0C(const char* name);
void fn_800C3568(void* ctx);
void fn_8012FCB0(void);
void fn_8012FCC0(void);
void fn_800450A4(void* p);
void fn_800A248C(void);
void* fn_800A2918(void);
void fn_80083DC4(void* p, int k);

static inline int flagFind(FlagTable* t, const char* const& name)
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

static inline void flagRegist(char* name)
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

static inline int flagFindR(FlagTable*& q, const char* name, u32& h)
{
    int k;
    h = fn_80076D18(name);
    q = &lbl_803CAB38;
    for (k = 0; k < 0x80; k++, q = (FlagTable*)((u32*)q + 1)) {
        if (h == q->hashes[0] && fn_80291188(q->names[0], name) == 0) {
            return k;
        }
    }
    return -1;
}

void fn_8009CF6C(void)
{
    int i;
    fn_800C3784(0x20, 0x300);
    fn_801D0B20(sCtx0, 0x80);
    fn_801D0B20(sCtx1, 0x80);
    fn_801D0B20(sCtx2, 0x80);
    fn_800C3560(sCtx0);
    fn_80091E38();
    fn_8009AE54();
    fn_800A35E0();
    fn_80181318();
    fn_800E1048();
    fn_8009CEA4();
    fn_801D0B08();
    fn_800C3840(lbl_80364A70, 0);
    for (i = 0; i < 0x80; i++) {
        lbl_803CAB38.names[i] = NULL;
        lbl_803CAB38.hashes[i] = 0;
    }
    for (i = 0; i < 0x10; i++) {
        lbl_803CAB38.bits[i] = 0;
    }
    flagRegist(lbl_80364A70 + 0x14);
    flagRegist(lbl_80364A70 + 0x20);
    flagRegist(lbl_80364A70 + 0x2c);
    flagRegist(lbl_80364A70 + 0x38);
    flagRegist(lbl_80364A70 + 0x45);
    flagRegist(lbl_80364A70 + 0x52);
    flagRegist(lbl_80364A70 + 0x5f);
    flagRegist(lbl_80364A70 + 0x6c);
    fn_801D0C88(fn_800C3558(), lbl_80364A70 + 0x79);
}

static inline s16 rd16(u8* p)
{
    int t = p[0] << 8;
    t += p[1];
    return t;
}

static inline int rd32(u8* p)
{
    int a = p[0] << 24;
    a += p[1] << 16;
    a += p[2] << 8;
    a += p[3];
    return a;
}

#pragma push
#pragma use_lmw_stmw on
void* fn_8009D958(u8* obj, const char* name)
{
    /*P*/
    u8* p;
    int run;
    char* s;
    int v;
    /*E*/
    v = 0;
    run = 1;
    p = *(u8**)(obj + 4);
    while (run) {
        u8 op = *p++;
        switch (op) {
        case 0:
            run = 0;
            break;
        case 0x1: case 0x3: case 0x5: case 0x7: case 0x9: case 0xb: case 0xd: case 0xf:
        case 0x11: case 0x13: case 0x15: case 0x17: case 0x19: case 0x37: case 0x41:
            p += 1;
            break;
        case 0x2: case 0x4: case 0x6: case 0x8: case 0xa: case 0xc: case 0xe: case 0x10:
        case 0x12: case 0x14: case 0x16: case 0x18: case 0x1a: case 0x3a: case 0x3b: case 0x3c:
        case 0x3d: case 0x3e:
            p += 2;
            break;
        case 0x1b: case 0x40:
            p += 4;
            break;
        case 0x1c:
            v = *p++;
            break;
        case 0x1d:
            v = rd16(p);
            p += 2;
            break;
        case 0x1e:
            v = rd32(p);
            p += 4;
            break;
        case 0x38: {
            s16 k = rd16(p);
            p += 3;
            s = *(char**)(*(u8**)(obj + 8) + 0x24);
            if (fn_80291188(name, s + k) == 0) {
                return s + v;
            }
            break;
        }
        }
    }
    return NULL;
}

void* fn_8009DA7C(int x, int y)
{
    /*P*/
    const char* name;
    u32 h;
    FlagTable* q;
    int i;
    u8* p;
/*E*/
    p = (u8*)fn_800C3BC8(NULL);
    while (p != NULL) {
        if ((int)p[0xc] == 5 && (s8)x == *(s16*)(p + 0x14) && (s8)y == *(s16*)(p + 0x16)) {
            BOOL r;
            name = *(char**)(*(u8**)(p + 8) + 0x24) + *(u16*)(p + 0x1a);
            if (*name == 0) {
                r = 0;
            } else {
                i = flagFindR(q, name, h);
                r = flagGetBit(&lbl_803CAB38, i);
            }
            if (!r) {
                return fn_8009D958(p, lbl_80364A70 + 0x8b);
            }
        }
        p = (u8*)fn_800C3BC8(p);
    }
    return NULL;
}
#pragma pop

void fn_8009DF90(void)
{
    flagSetBit(&lbl_803CAB38, flagFind(&lbl_803CAB38, lbl_80364B30));
    lbl_804CB700 |= 1;
    fn_80256A78(0.0f);
}

static inline BOOL flagGet2(FlagTable* t, const char* const& name)
{
    if (name[0] == 0) {
        return 0;
    }
    return flagGetBit(t, flagFind(t, name));
}

int fn_8009E080(void)
{
    /*P*/
    FlagTable* q;
    u32 h;
    const char* name;
    int i;
/*E*/
    if ((lbl_804CB700 & 1) == 0) {
        if (!flagGet2(&lbl_803CAB38, lbl_80364B30)) {
            if (fn_80083B84(lbl_80381B58) == NULL) {
                return 0;
            }
        }
    }
    fn_800846BC(lbl_80381B58);
    name = lbl_80364B30;
    i = flagFindR(q, name, h);
    flagClrBit(&lbl_803CAB38, i);
    lbl_804CB700 &= ~1;
    fn_800C900C(0, 0);
    fn_80250E38(1, 1.0f, 266.0f);
    fn_80250F0C(1, 1.0f, 266.0f);
    fn_80250FE0(1, 1.0f, 266.0f);
    return 1;
}

static inline void eventStop(void)
{
    int* p = (int*)fn_800C3558();
    u8 v = 0;
    p[8] = v;
    lbl_803C8DA0[0xa1] = v;
}

void fn_8009E3D4(void)
{
    flagClrBit(&lbl_803CAB38, flagFind(&lbl_803CAB38, lbl_80364B30));
    lbl_804CB700 &= ~1;
    fn_800C900C(0, 0);
    fn_80250E38(1, 1.0f, 266.0f);
    fn_80250F0C(1, 1.0f, 266.0f);
    fn_80250FE0(1, 1.0f, 266.0f);
    if (1.0f != *(f32*)(fn_80251174(6) + 0x10)) {
        fn_80250D64(6, 1.0f, 266.0f);
    }
    if (1.0f != *(f32*)(fn_8025121C(6) + 0x10)) {
        fn_80250E38(6, 1.0f, 266.0f);
    }
    eventStop();
}

struct RunBits { u32 pad : 29; u32 b4 : 1; u32 b2 : 1; u32 b1 : 1; };

static inline void clrRun1(void)
{
    lbl_804CB700 &= ~1;
}

#pragma push
#pragma use_lmw_stmw on
void fn_8009E554(void* a, void* parent)
{
    /*P*/
    const char* name;
    FlagTable* q;
    void* x;
    void* p;
    u32 h;
    int i;
/*E*/
    x = fn_80076F54(a);
    if (x != NULL) {
        p = fn_80081194(lbl_80381B80, parent);
        name = lbl_80364B30;
        i = flagFindR(q, name, h);
        flagClrBit(&lbl_803CAB38, i);
        clrRun1();
        ((RunBits*)&lbl_804CB700)->b4 = 0;
        *(void**)(fn_800C3558() + 0x20) = p;
        fn_801D0D58(fn_800C3558(), x);
        fn_801D0E18(fn_800C3558());
        if (fn_800C357C() == 0) {
            eventStop();
            fn_80081A90(p);
        }
    }
}
#pragma pop

void fn_8009E694(int stop)
{
    void* p = fn_80083B84(lbl_80381B80);
    if (p != NULL) {
        if (stop) {
            eventStop();
        }
        fn_80081A90(p);
    }
}

void fn_8009E704(void)
{
    u8* p;
    lbl_804CB700 |= 0x10;
    p = (u8*)fn_80083B84(lbl_80379FA8);
    lbl_804CB620 = p != NULL ? *(u32*)(p + 4) : 0;
    if (p == NULL) {
        fn_80081050(lbl_80379F58, fn_80081194(lbl_80379FA8, fn_80085708(lbl_80364B30 + 0xc)));
    }
    p = (u8*)fn_80083B84(lbl_8037DB60);
    lbl_804CB624 = p != NULL ? *(u32*)(p + 4) : 0;
    fn_80084F0C(lbl_80364B30 + 0x1b);
    fn_800C3568(sCtx2);
    fn_8012FCB0();
}

void fn_8009E7CC(void)
{
    u8* p;
    fn_800450A4(lbl_803CA870);
    fn_800A248C();
    lbl_804CB700 &= 0xFFBFF76F;
    p = (u8*)fn_80083B84(lbl_80379FA8);
    if (lbl_804CB620) {
        *(u32*)(p + 4) = lbl_804CB620;
    } else {
        fn_800846BC(lbl_80379FA8);
    }
    if (lbl_804CB624) {
        u8* q = (u8*)fn_80081194(lbl_8037DB60, p);
        *(u32*)(q + 4) = lbl_804CB624;
    }
    fn_800C3568(sCtx0);
    fn_80083DC4(fn_80081194(lbl_80381B80, fn_800A2918()), 0);
    fn_8012FCC0();
}

}
