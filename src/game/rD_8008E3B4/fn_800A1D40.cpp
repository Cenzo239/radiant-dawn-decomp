/* Event system helpers: 0x800A1D40..0x800A2918. */
#include "game/rD_8008E3B4/evflags.h"

#define VSLOT(n) virtual void v##n();
class PadObj3 {
public:
    VSLOT(08) VSLOT(0C)
    virtual void v10();                /* 0x10 */
    VSLOT(14) VSLOT(18) VSLOT(1C) VSLOT(20) VSLOT(24) VSLOT(28)
    virtual u32 v2C();                 /* 0x2C */
    VSLOT(30) VSLOT(34) VSLOT(38) VSLOT(3C) VSLOT(40) VSLOT(44)
    virtual u32 getTrig();             /* 0x48 */
    VSLOT(4C) VSLOT(50) VSLOT(54) VSLOT(58) VSLOT(5C) VSLOT(60) VSLOT(64) VSLOT(68)
    VSLOT(6C) VSLOT(70) VSLOT(74) VSLOT(78) VSLOT(7C) VSLOT(80)
    virtual void v84(u32 mask);        /* 0x84 */
};

extern "C" {

typedef struct EvFilter {
    s16 a;
    s16 b;
    s16 c;
    s16 d;
    s16 d2;
    u8 e;    /* 0xA */
} EvFilter;
extern EvFilter lbl_803E50B0;

extern PadObj3* lbl_804CB5B8;
extern u32 lbl_804CB700;
extern char lbl_80364B30[];
extern char lbl_80364C1C[];
extern u8 lbl_803EC898[];
extern u8 lbl_80381BF0[];
extern u8 lbl_80381C1C[];
extern u8 lbl_80381DB0[];
extern u8 lbl_80381EC8[];
extern void* lbl_804CB628;

u8* fn_800C3BC8(void* p);
void fn_800444F4(int k);
void fn_80084F0C(const char* name);
int fn_800A0330(u8* p);
int fn_800C9078(void);
int fn_800C7FE8(void);
void* fn_80085708(const char* name);
#if TARGET_PC
FE10_PROTO void* fn_80081050(void* cls, p32arg);
#else
void* fn_80081050(void* cls, int k);
#endif
void* fn_80081194(void* cls, void* parent);
void fn_80252850(int k, f32 v);
void* fn_80083B84(void* cls);
void fn_80083B78(void* p);
void fn_80083DC4(void* p, int k);
void fn_80039030(void);
void fn_8013F204(void);
void fn_80031490(void);
void fn_8012D78C(void);
void fn_80085BB0(void* p, void* f);
void fn_800A28D8(s8* p);

int fn_800A1D40(void)
{
    /*P*/
    FlagTable* q3;
    int i;
    FlagTable* q2;
    FlagTable* q;
    BOOL r;
    u32 h2;
    int i2;
    const char* name2;
    const char* name;
    BOOL r2;
    u32 h3;
    int i3;
    const char* name3;
    u32 h;
    BOOL r3;
    char* s;
/*E*/
    if (flagGet(&lbl_803CAB38, lbl_80364B30 + 0x23)) {
        fn_800444F4(3);
    } else {
        name = lbl_80364B30 + 0x3d;
        FLAG_GET_R(r, q, name, h, i);
        if (r) {
            fn_800444F4(1);
        }
    }
    name2 = lbl_80364B30 + 0x23;
    FLAG_GET_R(r2, q2, name2, h2, i2);
    if (r2) {
        goto ok;
    }
    name3 = lbl_80364B30 + 0x3d;
    FLAG_GET_R(r3, q3, name3, h3, i3);
    if (r3) {
    ok:
        s = lbl_80364B30;
        fn_80084F0C(s + 0x49);
        fn_80084F0C(s + 0x54);
        return 1;
    }
    return 0;
}

#pragma push
#pragma use_lmw_stmw on
void fn_800A20F4(void)
{
    /*P*/
    int one;
    int zero;
    int m1;
    u8* p;
/*E*/
    p = fn_800C3BC8(NULL);
    m1 = -1;
    zero = 0;
    one = 1;
    while (p != NULL) {
        if ((int)p[0xc] == 5) {
            EvFilter s = lbl_803E50B0;
            lbl_803E50B0.b = m1;
            lbl_803E50B0.a = m1;
            lbl_803E50B0.c = zero;
            if (fn_800A0330(p)) {
                s8 x = *(s16*)(p + 0x14);
                s8 y = *(s16*)(p + 0x16);
                lbl_803EC898[x + y * 0x40 + 0x400d] = one;
            }
            lbl_803E50B0.a = s.a;
            lbl_803E50B0.b = s.b;
            lbl_803E50B0.c = s.c;
            lbl_803E50B0.d = s.d;
            lbl_803E50B0.d2 = s.d2;
            lbl_803E50B0.e = s.e;
        }
        p = fn_800C3BC8(p);
    }
}
#pragma pop

static inline void set7B(u8* p)
{
    p[0x2b] = 0x7b;
}

void fn_800A2200(void)
{
    if (lbl_804CB5B8->v2C() & 0x4000) {
        int a = fn_800C9078();
        int b = fn_800C7FE8();
        if (!((u16)(b | a) & 0xd)) {
            u32 f0 = *(volatile u32*)&lbl_804CB700;
            u32 f = *(volatile u32*)&lbl_804CB700;
            if ((f0 & 0x10) && !(f & 0x400000) && !(f & 4) && fn_80085708(lbl_80364C1C) == NULL) {
                set7B((u8*)fn_80081050(lbl_80381EC8, 2));
            }
        }
    }
}

void fn_800A2348(void)
{
    fn_80252850(1, 300.0f);
    fn_80252850(2, 300.0f);
}

int fn_800A2430(const char* name)
{
    u8* q = (u8*)fn_80083B84(lbl_80381BF0);
    if (q == NULL) {
        return 0;
    }
    return fn_80291188(name, (char*)q + 0x30) == 0;
}

int fn_800A24F8(void)
{
    void* p;
    char* s;
    lbl_804CB700 = (lbl_804CB700 | 0x890) & 0xFFBFFFDF;
    p = fn_80085708(lbl_80364C1C + 0x46);
    if (p != NULL) {
        fn_80083DC4(p, 4);
    }
    s = lbl_80364C1C;
    fn_80084F0C(s + 0x14);
    fn_80084F0C(s + 0x1b);
    fn_80084F0C(s + 0x22);
    fn_80084F0C(s + 0x2d);
    fn_80084F0C(s + 0x5);
    fn_80084F0C(s + 0x38);
    fn_80039030();
    fn_8013F204();
    fn_80031490();
    fn_8012D78C();
    return 1;
}

static inline void* evParent(void)
{
    void* p;
    char* s = lbl_80364C1C;
    lbl_804CB628 = NULL;
    if ((p = fn_80085708(s + 0x2d)) == NULL && (p = fn_80085708(s + 0x5)) == NULL &&
        (p = fn_80085708(s + 0x46)) == NULL) {
        p = fn_80085708(s + 0x51);
    }
    fn_80085BB0(p, fn_800A28D8);
    return lbl_804CB628 ? lbl_804CB628 : p;
}

int fn_800A25CC(void)
{
    fn_80081194(lbl_80381C1C, evParent());
    return 1;
}

typedef struct PadSeq {
    u8 pad0[0x30];
    char* seq;  /* 0x30 */
    int s34;    /* 0x34 */
    u8 wait;    /* 0x38 */
    u8 left;    /* 0x39 */
} PadSeq;

void fn_800A26B0(PadSeq* p)
{
    u32 mask;
    lbl_804CB700 |= 0x20;
    lbl_804CB700 &= ~0x80;
    p->left--;
    lbl_804CB5B8->v10();
    if ((int)p->left != 0) {
        return;
    }
    mask = 0;
loop:
    switch (*p->seq++) {
    case 0x31: mask = 0x500005; break;
    case 0x32: mask = 0x400004; break;
    case 0x33: mask = 0x600006; break;
    case 0x34: mask = 0x100001; break;
    case 0x36: mask = 0x200002; break;
    case 0x37: mask = 0x900009; break;
    case 0x38: mask = 0x800008; break;
    case 0x39: mask = 0xA0000A; break;
    case 0x41: mask = 0x400; break;
    case 0x42: mask = 0x800; break;
    case 0x58: mask = 0x1000; break;
    case 0x59: mask = 0x2000; break;
    case 0x5a: mask = 0x10; break;
    case 0x4c: mask = 0x40; break;
    case 0x52: mask = 0x100; break;
    case 0x53: mask = 0x4000; break;
    case 0x3e: p->wait = p->wait << 1; goto loop;
    case 0x3c: p->wait = (s32)p->wait >> 1; goto loop;
    case 0: mask = 0xFFFF; break;
    case 0x5f: break;
    }
    p->left = p->wait;
    lbl_804CB5B8->v84(mask);
    if (*p->seq == 0) {
        fn_80083B78(p);
    }
}

void fn_800A2848(void)
{
    lbl_804CB700 &= ~0x20;
    lbl_804CB700 |= 0x80;
    lbl_804CB5B8->v10();
}

int fn_800A286C(char* s)
{
    PadSeq* p = (PadSeq*)fn_80081050(lbl_80381DB0, 2);
    p->seq = s;
    p->s34 = 0;
    p->wait = 0x10;
    p->left = 1;
    lbl_804CB5B8->v10();
    return 1;
}

void* fn_800A2918(void)
{
    return evParent();
}

}
