/* fn_801D2AC0 (round 19): self-contained copy of the helpers of rR_80175E5C/fn_801D0A40.cpp plus the function.
   The three checks are one `if (!a || !b || !c) return;` (gives the `bne next; b end` tail). */
/* Title and extras screen processes around the window sheet, event text lookup. */
#include "game/rR_80175E5C/types.h"

struct MenuP {
    u8 pad[0xA6];
    s8 cur;
};

struct RefObj {
    virtual void dtor(int);
    int refs;
};

struct TitleP {
    u8 pad[0x40];
    char* s40;
    int s44;
    int s48;
    int s4C;
    MenuP* s50;
    RefObj* s54;
};

struct Snd {
    virtual void v08();
    virtual void v0C();
    virtual int v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void v24(int);
};

extern "C" {
#if TARGET_PC
FE10_PROTO extern void *lbl_804CB6A8;
#else
extern int lbl_804CB6A8;
#endif
extern char lbl_8036EA88[];
extern u8 lbl_8041EEB8[];
extern u32 lbl_804CB700;
extern u8 lbl_8038C100[], lbl_8038C10C[], lbl_8038C150[], lbl_8038BDD0[], lbl_8038B160[], lbl_8038B0F0[];
#if TARGET_PC
FE10_PROTO void fn_800893D4(p32arg);
#else
void fn_800893D4(int);
#endif
#if TARGET_PC
FE10_PROTO p32ret fn_800D4228(char*);
#else
int fn_800D4228(char*);
#endif
void fn_800D42A0(char*);
void* fn_800D4188(const char*, void*);
void fn_800D3D00(void*, int, f32);
void fn_801E5890(void*);
void fn_800D56E8(MenuP*);
void fn_80083B78(void*);

void fn_801D0C20(void*);
void* fn_800C3BC8(void*);
const char* fn_8009D948(void*, u16);
int fn_80291188(const char*, const char*);
struct VM;
void fn_801D0D58(VM*, u8*);

struct Ev {
    u8 pad[0xC];
    u8 kind;
    u8 pad2[7];
    u16 s14;
};
void fn_801D0A40(const char* name);

}

static inline void MusicOut(TitleP* p) {
    if (p->s40 != NULL) {
        int h = fn_800D4228(p->s40);
        if (h == 0) {
            char* s = p->s40;
            if (s != NULL) fn_800D42A0(s);
            if (s != NULL) {
                p->s40 = s;
                void* a = fn_800D4188(s, p);
                fn_800D3D00(a, 2, 90.0f);
                void* b = fn_800D4188(lbl_8036EA88, a);
                fn_800D3D00(b, 2, 89.9f);
            }
        } else {
            fn_800893D4(h);
        }
    }
}

extern "C" {
void fn_801D2D88(TitleP* p);

void fn_801D3230(TitleP* p);


#define F(p, t, o) (*(t*)((u8*)(p) + (o)))
extern u32 lbl_804CB878;
extern u8 lbl_803CAB38[];
extern void* lbl_804CB814;
extern char* lbl_804CA4D8;
void fn_8011FDD8(void*, int);
int fn_8011B77C(void*, char*);
#if TARGET_PC
FE10_PROTO void fn_8008939C(p32arg);
#else
void fn_8008939C(int);
#endif
void* fn_801DFF2C(void*);
extern u8 lbl_8038C164[];
void* fn_800D5448(void*, void*, int);
void* fn_801E5640(void*, int, int);
void* fn_8006074C(void*);
void fn_80290D04(char*, int, void*, ...);
void fn_80205AE4(void*, char*);
void fn_80205778(void*, char*);
extern u8 lbl_8038C140[], lbl_8038C130[];
void fn_801D607C();
#if TARGET_PC
FE10_PROTO void fn_800761F0(p32arg);
#else
void fn_800761F0(int);
#endif
void fn_801E40B0(void*, int);
void fn_80250E38(int, f32, f32);
void* fn_8024F3FC(int);
void* fn_80081194(void*, void*);
void fn_801E4094(void*);
void fn_80081050(void*, void*);
void fn_801DDDF8(void*, void*);
void* fn_80083B84(void*);
void fn_801FBF08(void*);
void fn_801E5870();
const char* fn_801D5DC4();
void fn_801D5DFC();
int fn_801D5F7C();
int fn_8023F880(const char*);
void* fn_80060728(void*);
char* strcpy(char*, const char*);
#if TARGET_PC
FE10_PROTO p32ret fn_80075FB4(const char*, int);
#else
int fn_80075FB4(const char*, int);
#endif
extern char lbl_8038C0EC[], lbl_8038C0D8[], lbl_8038C0C4[];
void* fn_8025121C(int);
int fn_80068528(void*);
#if TARGET_PC
FE10_PROTO s8 fn_8024F7EC(p32arg);
FE10_PROTO void fn_80251838(int, p32arg, f32);
#else
s8 fn_8024F7EC(int bgm);
void fn_80251838(int, int, f32);
#endif
u8* fn_8024BC94();
int fn_801D09F0();
void fn_800068EC(void*, const char*, int);
void fn_8023F1A0(const char*, int);
void fn_800E24F8(const char*);
extern void* lbl_8038C1F0[][2];
extern void* lbl_8038C228[];
extern char lbl_8036ECF8[];
extern int lbl_804CBE0C;
extern void* lbl_804CBDF8, *lbl_804CBDFC, *lbl_804CBE00, *lbl_804CBE04, *lbl_804CBE08;
u8 fn_801E71B4();
u8 fn_801E7164();
u8 fn_801E7024();
int fn_801D0AE0();




struct VM {
    int stack;
    int s04;
    u8* fn;
    int pc;
    int s10;
    u8* locals;
    int* sp;
};
void fn_801D32D0(TitleP* p);

void fn_801D35E0(void* a);

void fn_801D36B4(void* a);

void fn_801D37D4(TitleP* p);

void fn_801D3B94();

void fn_801D3C64(TitleP* p);

void* fn_801D3D78(void* parent);

int fn_801D44AC();

int fn_801D45FC();

int fn_801D5398();

void fn_801D5454(void* a, void* b);


#pragma push
#pragma auto_inline off

void fn_801D5DFC();

#pragma pop

void fn_801D5EC8();


#pragma use_lmw_stmw on

int fn_801D5F7C();

#pragma use_lmw_stmw off

void fn_801E5880(void*);
#if TARGET_PC
FE10_PROTO void fn_800893C4(p32arg);
#else
void fn_800893C4(int);
#endif
void fn_801C6D98(int, int, f32, f32);


#define TITLE_END(name) \
void name(TitleP* p) { \
    fn_800893D4(p->s4C); \
    MusicOut(p); \
    fn_801E5890(p); \
    int c = p->s50->cur; \
    fn_800D56E8(p->s50); \
    p->s50->cur = c; \
    fn_80083B78(p); \
}

void fn_801D3ED0();



}

/* ---- from rR_80175E5C/wip/fn_801D0A40.cpp ---- */
extern "C" {


/* fn_801D2AC0: 18 of 60 words differ */
static inline int Chk(const char* b) { if (fn_8023F880(b)) return 1; return 0; }
void fn_801D2AC0(TitleP* p) {
    char buf[0x40];
    switch (*(u8*)((u8*)fn_80060728(lbl_803CAB38) + 0x11)) {
    case 3:
    case 0:
        strcpy(buf, lbl_8038C0EC);
        break;
    case 1:
        strcpy(buf, lbl_8038C0D8);
        break;
    case 2:
        strcpy(buf, lbl_8038C0C4);
        break;
    }
    if (fn_801D5F7C() == 0 || fn_8023F880(fn_801D5DC4()) == 0 || fn_8023F880(buf) == 0) return;
        fn_801D5DFC();
        p->s44 = fn_80075FB4(fn_801D5DC4(), 0x80);
        p->s48 = fn_80075FB4(buf, 0x80);
        fn_80083B78(p);
}
}
