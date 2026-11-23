#include "game/rT_80026898/types.h"
#pragma use_lmw_stmw on
extern "C" {
extern GameState lbl_803CAB38;
extern u8 lbl_803EC898[];
extern u8 lbl_803CB770[];
extern u8* lbl_804CB810;
extern Unit** lbl_804CB814;
extern int lbl_804CA0A0;
extern void* lbl_804CA500;
extern void* lbl_804CA58C;
extern char lbl_8037AE18[];
extern char lbl_8037DB60[];
extern char lbl_803CA9A0[];
extern char lbl_804CA0B0[8];
extern char lbl_804CA0B8[8];
extern char lbl_804CA0C0[8];
extern char* lbl_8037AB10[];
extern u8 lbl_803E9000[];
void* memset(void*, int, int);
char* strcpy(char*, const char*);
void fn_80126EB0(Unit*, s8, s8);
void fn_8010354C(Unit*, Unit*, int, int, void*);
void fn_800F39DC(Unit*);
#if TARGET_PC
FE10_PROTO void fn_80108A20(void*, Unit*, int);
#else
void* fn_80108A20(void*, Unit*, int);
#endif
int fn_8011B77C(void*, void*);
void fn_8011EED4(Unit*, Unit*, int, void*, void*);
void* fn_80066130(void*, int, int, int);
void* fn_80081194(void*, void*);
int* fn_80077064(const char*);
int fn_8012E9B4(Unit*, Unit*);
char* fn_80291314(const char*, int);
u8* fn_8024BC94(void);
u8* fn_8024BCA0(void);
int fn_80290D04(char*, int, const char*, ...);
void fn_8023F1A0(char*, int);
void fn_80250D64(int, f32, f32);
int fn_8023F880(char*);
void* fn_80075FB4(const char*, int);
void fn_80083B78(void*);
#if TARGET_PC
FE10_PROTO void fn_801030B8(Unit*, int, int, int, int, p32arg);
#else
void fn_801030B8(Unit*, int, int, int, int, int);
#endif
Unit* fn_800CFB0C(void*);
#if TARGET_PC
FE10_PROTO void fn_8010301C(Unit*, Unit*, int, int, p32arg);
#else
void fn_8010301C(Unit*, Unit*, int, int, int);
#endif
void fn_80026C44(void*, Unit*, Unit*);
void fn_8002C53C(void*, int);
void fn_8002742C(void*, int);
int fn_80060914(void*);
void fn_8010E770(Unit**);
void fn_800610A4(void*);
void fn_8011B430(void*, void*);
void fn_8011A36C(void*);
void fn_8012D620(void);
void fn_80068A58(void);
void fn_8010E41C(char*, int);
void fn_80122460(Unit*);
void* fn_80062A9C(void*, u8);
u32* fn_80060728(void*);
void fn_801657DC(void*);
void fn_80165764(void*);
void fn_801657A0(void*);
void fn_80083DC4(void*, int);
int fn_8011799C(void*, int, int);
Unit* fn_8012D2B0(int k);
Unit* fn_8012D280(u8);
void fn_800620A8(f32, f32, void*);
int fn_8006041C(void*);
void fn_80060528(void*, int, u8*, u16*, u32*);
void* fn_80287358(void);
void fn_80245614(u8*, u8*, u32, u32, int, u8, u16, int, s64);
void* fn_801059B0(void);
int fn_80105158(void*);
void fn_801053EC(void*, u8*);
void fn_80105704(void*);
void fn_8011E300(Unit*, int, int, int);
void fn_80109078(void*);
s16 fn_801237EC(Unit*);
void fn_80126D9C(Unit*, int);
void fn_80128E14(Unit*, int);
void fn_801283F8(Unit*);
void fn_80060580(void*, u8);
void fn_802512C4(f32);
void fn_80250E38(int, f32, f32);
void fn_8025095C(f32, f32);
void fn_80250A08(f32, f32);


struct Yell {
    u8 pad[0x30];
    void* a;
    void* b;
    u8* base;
    int n;
};

static inline void yellPath(Yell* p, Unit* u, char* out) {
    char* c;
    int k = (s8)fn_8012E9B4(u, u) * 0xc;
    strcpy(lbl_803CA9A0, *(char**)(p->base + k * (p->n + 1) + 8));
    c = fn_80291314(lbl_803CA9A0, 0x2f);
    if (c == 0) c = fn_80291314(lbl_803CA9A0, 0x5c);
    if (c == 0) {
        s8 l = fn_8024BC94()[0x1bc8];
        fn_80290D04(out, 0x7f, lbl_804CA0B8, l >= 0 ? lbl_8037AB10[l] : lbl_804CA0C0, lbl_803CA9A0);
    } else {
        s8 l;
        *c++ = 0;
        l = fn_8024BC94()[0x1bc8];
        fn_80290D04(out, 0x7f, lbl_804CA0B0, lbl_803CA9A0, l >= 0 ? lbl_8037AB10[l] : lbl_804CA0C0, c);
    }
    out[0x7f] = 0;
}



static inline Unit* unitAt(u8 id) {
    return id ? (Unit*)(lbl_804CB810 + (id - 1) * 0x3f0) : 0;
}

static inline void markAll(u8* m, u8* q) {
    u8 c;
    while ((c = *q) != 0xff) {
        m[c] = 1;
        q++;
    }
}

struct Group { Unit* head; u8 pad[8]; };




static inline u8* section(int i) {
    switch (i) {
    case 0: return lbl_803C8E80;
    case 1: return lbl_803C8E80 + 0x4a0;
    case 2: return lbl_803C8E80 + 0x940;
    }
    return 0;
}

struct ObjBase { int x; };
class Obj : public ObjBase {
public:
    virtual void get(int*, int*, u32*);
};
void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E4E4(f32, f32, f32, f32);
void fn_8007E7DC(u8);
void fn_80032FA8(Unit*);


void fn_80046E9C(u8* p) {
    fn_80126EB0(lbl_803CA870.unit2, *(f32*)(p + 0x30), *(f32*)(p + 0x34));
    fn_8010354C(lbl_803CA870.unit, lbl_803CA870.unit2, *(f32*)(p + 0x30), *(f32*)(p + 0x34), p);
}

void fn_80043078(void* a) {
    GameState* t = &lbl_803CAB38;
    if (t->sideOn[t->side]) {
        u8* c = (u8*)fn_80062A9C(t, t->side);
        switch (*fn_80060728(t) & 3) {
        case 0:
        case 1:
            switch (t->side) {
            case 0:
                fn_801657DC(a);
                break;
            case 3:
                if (c) {
                    if (c[4] == 1) fn_80165764(a);
                    else fn_801657DC(a);
                }
                break;
            case 1:
            case 2:
                if (t->sideOn[t->side] == 2) fn_80165764(a);
                break;
            }
            break;
        case 2:
            if (((fn_80060728(t)[1] >> 28) & 3) == 0) {
                switch (t->sideOn[t->side]) {
                case 1:
                    if (c) {
                        if (c[4] == 1) fn_80165764(a);
                        else fn_801657DC(a);
                    }
                    break;
                case 2:
                    fn_80165764(a);
                    break;
                }
            } else {
                switch (t->sideOn[t->side]) {
                case 2:
                    fn_801657A0(a);
                    break;
                case 0:
                case 1:
                default:
                    break;
                }
            }
            break;
        }
    }
}
}
