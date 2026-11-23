/* Game startup and shutdown: archive load lists, restart/reset state.
 * Sits before the original region start, same TU family as 0x800CD06C.. */
#include "game/rK_800CF8BC/types.h"

#pragma pool_strings on

/* Sets the string pool at lbl_80366184 in its original order. */
const char* sPool[11];
void poolOrder() {
    sPool[0] = "RID_MASK";
    sPool[1] = "FE10Conversation.cms";
    sPool[2] = "s/rect.bin";
    sPool[3] = "FE10Data.cms";
    sPool[4] = "FE10Anim.cms";
    sPool[5] = "FE10Effect.cms";
    sPool[6] = "dictionaryF.bin";
    sPool[7] = "FE10Growth.cms";
    sPool[8] = "mess/%s%s";
    sPool[9] = "common.m";
    sPool[10] = "SND_GROUP_FE";
}

struct Sub {
    void* vt;
    void* p4;
};
struct LangHost {
    u8 pad[0x1BC8];
    u8 lang;
};
struct GameState {
    u8 pad[0x60];
    int state;  /* 0x60 */
    int next;   /* 0x64 */
};
struct SaveHdr {
    u32 mode : 30;
    u32 kind : 2;
    u8 pad4[6];
    u8 xA;
};
struct SaveData {
    u8 pad[0xC];
    u8 xC;
    u8 padD[0x9A - 0xD];
    s8 x;
    s8 y;
};
struct ChapReq {
    u8 pad[0x36];
    u8 chapter;
    u8 kind;
};
struct AObjB {
    u8 pad[0x44];
};
class AObj : public AObjB {
public:
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual int v20(int, int, int, int*);
};

extern u8 lbl_80383024[];
extern u8 lbl_80383108[];
extern u8 lbl_80383118[];
extern u8 lbl_80383130[];
extern u8 lbl_80383140[];
extern u8 lbl_803832E0[];
extern SaveData lbl_803CAB38;
extern SaveData lbl_803CA870;
extern u8 lbl_803CB770[];
extern u8 lbl_803E7290[];
extern u8 lbl_803E72D8[];
extern const char* lbl_80383960[][2];
extern const char* lbl_8037AB10[];
extern char lbl_804CA0C0[8];
extern u8 lbl_804CB6C0[8];
extern void* lbl_804CB704;
extern void* lbl_804CB708;

extern "C" {
void fn_80006A2C(void*);
void fn_80079210(void*);
int fn_801D09F0();
GameState* fn_80083B84(void*);
void fn_80067EE8();
u32 OSGetResetCode();
LangHost* fn_8024BC94();
void* fn_80075FB4(const char*, int);
void fn_8023F1A0(const char*, int);
void fn_8009CF5C();
void fn_80165718();
void fn_800C3CF0(void*);
void fn_800C9F0C();
void fn_8006DECC();
void fn_80290D04(char*, int, const char*, ...);
void fn_8012CB70();
void fn_8009CF6C();
void fn_8014C838();
void fn_8000F748(int);
void fn_80011680();
void fn_80010AB8();
void fn_80109B18(const char*, const char*, const char*, const char*);
void fn_80165728();
void fn_801C864C();
void fn_801C9E98();
void fn_800C3D30(void*);
void fn_800C4210();
void fn_800C7850();
void fn_800C9FA4();
void fn_8006DF48();
void fn_80263AB4();
void fn_80075D78(const char*);
void fn_80066070(void*);
void fn_80068A58();
SaveHdr* fn_80060728(SaveData*);
ChapReq* fn_8024BCA0();
void fn_8023FC0C();
void fn_80150990();
void fn_80061584(SaveData*, int);
void fn_8006132C(SaveData*);
void fn_80044654();
void fn_80061098();
void fn_8024BCAC();
int fn_801D3FFC();
void fn_8012CC80();
void fn_800620A8(void* t, f32, f32);
void fn_8012FF30();
void fn_8012CBF0();
void fn_801097FC(SaveHdr*);
void fn_802512C4(f32);
void fn_8025095C(f32, f32);
void fn_80250A08(f32, f32);
void fn_80250D64(s8, f32, f32);
void fn_80250E38(s8, f32, f32);
void fn_80250F0C(s8, f32, f32);
void fn_80250FE0(s8, f32, f32);
void fn_80257C18(void*);
int fn_800CD7F4(void*);

Sub* fn_800CCF84(Sub* p, int f) {
    if (p) {
        if (p) {
            p->vt = lbl_80383024;
            if (p->p4) {
                fn_80006A2C(&p->p4);
            }
        }
        if (f > 0) {
            fn_80079210(p);
        }
    }
    return p;
}

Sub* fn_800CCFF8(Sub* p, int f) {
    if (p) {
        if (p) {
            p->vt = lbl_80383024;
            if (p->p4) {
                fn_80006A2C(&p->p4);
            }
        }
        if (f > 0) {
            fn_80079210(p);
        }
    }
    return p;
}

#define SetState(v)                             \
    {                                           \
        GameState* g = fn_80083B84(lbl_803832E0); \
        g->state = (v);                         \
    }

void* fn_800CD104() {
    return fn_801D09F0() ? lbl_80383118 : lbl_80383108;
}

void* fn_800CD1CC() {
    return fn_801D09F0() ? lbl_80383140 : lbl_80383130;
}

void
#if TARGET_PC
*
#endif
fn_800CD4A4(int s) {
#if TARGET_PC
    GameState* g = fn_80083B84(lbl_803832E0);
    g->state = s;
    return g;
#else
    fn_80083B84(lbl_803832E0)->state = s;
#endif
}

void fn_800CD548(int s) {
    fn_80083B84(lbl_803832E0)->next = s;
}

void fn_800CD8D4() {
    switch (lbl_803CA870.xC) {
    case 0:
        fn_80067EE8();
        SetState(0xB);
        break;
    default:
        break;
    }
}

int fn_800CD920() {
    if ((OSGetResetCode() >> 31) == 0) {
        return 0;
    }
    return !(OSGetResetCode() & 0x10000);
}

void fn_800CDADC() {
    s8 lang = fn_8024BC94()->lang;
    lbl_804CB704 = fn_80075FB4(lbl_80383960[lang][fn_801D09F0()], 0xC20);
    lbl_804CB708 = fn_80075FB4("s/rect.bin", 0xC20);
}

static inline const char* langDir() {
    s8 l = fn_8024BC94()->lang;
    return l >= 0 ? lbl_8037AB10[l] : lbl_804CA0C0;
}

void fn_800CDB98() {
    char buf[0x40];
    fn_8009CF5C();
    fn_8023F1A0("FE10Data.cms", 0xC20);
    fn_8023F1A0("FE10Anim.cms", 0xC20);
    fn_8023F1A0("FE10Effect.cms", 0xC20);
    fn_80165718();
    fn_800C3CF0(lbl_804CB6C0);
    fn_800C9F0C();
    fn_8006DECC();
    ((AObj*)lbl_803E7290)->v08();
    ((AObj*)lbl_803E72D8)->v08();
    {
        s8 lang = fn_8024BC94()->lang;
        fn_8023F1A0(lbl_80383960[lang][fn_801D09F0()], 0xC20);
    }
    fn_8023F1A0("s/rect.bin", 0xC20);
    fn_8023F1A0("dictionaryF.bin", 0xC00);
    fn_8023F1A0("FE10Growth.cms", 0xCA0);
    fn_8023F1A0("FE10Conversation.cms", 0xCA0);
    fn_80290D04(buf, 0x40, "mess/%s%s", langDir(), "common.m");
    fn_8023F1A0(buf, 0xC00);
}

void fn_800CDCEC() {
    char buf[0x40];
    fn_8012CB70();
    fn_8009CF6C();
    fn_8014C838();
    fn_8000F748(0x400);
    fn_80011680();
    fn_80010AB8();
    fn_80109B18("FE10Data.cms", "FE10Anim.cms", "FE10Effect.cms", "FE10Growth.cms");
    fn_80165728();
    fn_801C864C();
    fn_801C9E98();
    fn_800C3D30(lbl_804CB6C0);
    fn_800C4210();
    fn_800C7850();
    fn_800C9FA4();
    fn_8006DF48();
    ((AObj*)lbl_803E7290)->v0C();
    ((AObj*)lbl_803E72D8)->v0C();
    {
        s8 lang = fn_8024BC94()->lang;
        lbl_804CB704 = fn_80075FB4(lbl_80383960[lang][fn_801D09F0()], 0xC20);
    }
    lbl_804CB708 = fn_80075FB4("s/rect.bin", 0xC20);
    fn_80263AB4();
    fn_80290D04(buf, 0x40, "mess/%s%s", langDir(), "common.m");
    fn_80075D78(buf);
    fn_80066070(lbl_803CB770);
    fn_80068A58();
    fn_80060728(&lbl_803CAB38)->xA = 0x40;
}

void fn_800CDE60() {
    int i;
    fn_802512C4(0.0f);
    fn_8025095C(0.0f, 0.0f);
    fn_80250A08(0.0f, 0.0f);
    for (i = 0; i < 8; i++) {
        fn_80250D64(i, 1.0f, 0.0f);
        fn_80250E38(i, 1.0f, 0.0f);
        fn_80250F0C(i, 1.0f, 0.0f);
        fn_80250FE0(i, 1.0f, 0.0f);
    }
    fn_80257C18(fn_800CD7F4);
}
}
