/* fn_800CD5F4: exact since the round 21 regs review (was regs, 10 words). Helpers from fn_800CCF84.cpp (exported bodies removed), body from wip/fn_800CCF84.cpp.
   symcheck: (c) fixed. fn_800620A8 is (SaveData*, f32, f32); the draft declared it (f32, f32) and left a conversion temporary in r3,
   so the callee would have written the cursor position through a wild pointer. wip/fn_800CCF84.cpp still has the old prototype. */
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
void fn_800620A8(SaveData*, f32, f32);
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
Sub* fn_800CCF84(Sub* p, int f);

Sub* fn_800CCFF8(Sub* p, int f);


#define SetState(v)                             \
    {                                           \
        GameState* g = fn_80083B84(lbl_803832E0); \
        g->state = (v);                         \
    }

void* fn_800CD104();

void* fn_800CD1CC();

void fn_800CD4A4(int s);

void fn_800CD548(int s);

void fn_800CD8D4();

int fn_800CD920();

void fn_800CDADC();


static inline const char* langDir() {
    s8 l = fn_8024BC94()->lang;
    return l >= 0 ? lbl_8037AB10[l] : lbl_804CA0C0;
}
void fn_800CDB98();

void fn_800CDCEC();

void fn_800CDE60();

}

/* ---- from rK_800CF8BC/wip/fn_800CCF84.cpp ---- */
extern "C" {
/* Near miss from fn_800CCF84.cpp, same declarations.
 * fn_800CD5F4: the old "r3/r4 swap" in the fn_800620A8 argument block was the missing first argument. */
static inline SaveData* XY(SaveData* s) { return s; }
void fn_800CD5F4() {
    ChapReq* r = fn_8024BCA0();
    fn_8023FC0C();
    fn_80150990();
    switch (r->kind) {
    case 0:
        break;
    case 10:
        fn_80060728(&lbl_803CAB38)->kind = 1;
        fn_80061584(&lbl_803CAB38, r->chapter);
        fn_8006132C(&lbl_803CAB38);
    case 4:
    case 9:
        SetState(0xB);
        break;
    case 11:
        fn_80044654();
        fn_80061098();
        fn_8024BCAC();
        SetState(0xE);
        break;
    case 5:
    case 6:
    case 7:
        fn_80044654();
        fn_80061098();
        fn_8024BCAC();
        SetState(0x14);
        break;
    case 1:
    case 12:
        fn_80044654();
        fn_80061098();
        fn_8024BCAC();
        if (fn_801D3FFC() == 0) {
            fn_8012CC80();
            SetState(0x11);
        } else {
            fn_800620A8(&lbl_803CAB38, lbl_803CAB38.x, lbl_803CAB38.y);
            fn_8012FF30();
            SetState(0x18);
        }
        break;
    case 2:
    case 13:
        fn_80044654();
        fn_80061098();
        fn_8024BCAC();
        SetState(0x19);
        break;
    case 3:
        r->kind = 4;
        fn_8012CBF0();
        SetState(0xB);
        break;
    case 8:
        SetState(0x15);
        break;
    }
    fn_801097FC(fn_80060728(&lbl_803CAB38));
}
}
