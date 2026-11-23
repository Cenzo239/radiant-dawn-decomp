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

void fn_801D0A40(const char* name) {
    fn_801D0C20(lbl_8041EEB8);
    Ev* e = (Ev*)fn_800C3BC8(NULL);
    while (e != NULL) {
        if ((int)e->kind == 0x10) {
            if (fn_80291188(name, fn_8009D948(e, e->s14)) == 0) {
                fn_801D0D58((VM*)lbl_8041EEB8, (u8*)e);
                return;
            }
        }
        e = (Ev*)fn_800C3BC8(e);
    }
}
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
void fn_801D2D88(TitleP* p) {
    fn_800893D4(p->s4C);
    MusicOut(p);
    fn_801E5890(p);
    int c = p->s50->cur;
    fn_800D56E8(p->s50);
    p->s50->cur = c;
    fn_80083B78(p);
}
void fn_801D3230(TitleP* p) {
    fn_800893D4(p->s4C);
    fn_801E5890(p);
    int c = p->s50->cur;
    fn_800D56E8(p->s50);
    p->s50->cur = c;
    fn_80083B78(p);
}

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
FE10_PROTO void * fn_80075FB4(const char*, int);
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

int fn_801D0AE0() {
    if (*(volatile u32*)&lbl_804CB878 & 0x800) {
        *(volatile u32*)&lbl_804CB878 &= ~0x800;
        return 1;
    }
    return 0;
}



struct VM {
    int stack;
    int s04;
    u8* fn;
    int pc;
    int s10;
    u8* locals;
    int* sp;
};


void fn_801D32D0(TitleP* p) {
    fn_800893D4(p->s4C);
    fn_801E5890(p);
    int c = p->s50->cur;
    fn_800D56E8(p->s50);
    p->s50->cur = c;
    fn_80083B78(p);
}

void fn_801D35E0(void* a) {
    char buf[0x20];
    fn_80290D04(buf, 0x20, lbl_8038C140, *(int*)fn_8006074C(lbl_803CAB38));
    fn_80205AE4(a, buf);
}

void fn_801D36B4(void* a) {
    char buf[0x20];
    fn_80290D04(buf, 0x20, lbl_8038C130, *(int*)fn_8006074C(lbl_803CAB38));
    fn_80205778(a, buf);
}

void fn_801D37D4(TitleP* p) {
    fn_8008939C(p->s4C);
    u8* o = (u8*)fn_801DFF2C(lbl_8038C164);
    o[0x24] = 1;
    fn_800D5448(o, p, 0);
    void* w = fn_801E5640(p, -0x1000, 0);
    if (w != NULL) F(w, void*, 0x64) = lbl_8038C150;
}

void fn_801D3B94() {
    if ((int)lbl_803CAB38[0x9D] == 0) {
        {
            u8* next;
            u32 last = F(lbl_804CB814, u32, 0x3C);
            u8* u = F(lbl_804CB814, u8*, 0x40);
            while (u != NULL) {
                next = F(u, u8*, 0xE4);
                if (fn_8011B77C(u + 0x12C, lbl_804CA4D8) != 0) fn_8011FDD8(u, 5);
                if ((u32)u == last) break;
                u = next;
            }
        }
        {
            u32 last;
            u8* u;
            u8* next;
            last = F(lbl_804CB814, u32, 0x3C);
            u = F(lbl_804CB814, u8*, 0x40);
            while (u != NULL) {
                next = F(u, u8*, 0xE4);
                if (F(u, int, 0x10C) & 0x100) fn_8011FDD8(u, 5);
                if ((u32)u == last) break;
                u = next;
            }
        }
    }
}

void fn_801D3C64(TitleP* p) {
    fn_801D607C();
    fn_800761F0(p->s44);
    fn_800761F0(p->s48);
    if (p != NULL) {
        RefObj* o = p->s54;
        if (o != NULL) {
            if (--o->refs == 0 && o != NULL) o->dtor(1);
            p->s54 = NULL;
        }
        if (p != NULL) fn_801E40B0(p, 0);
    }
    if (!(lbl_804CB700 & 0x10)) {
        fn_80250E38(6, 1.0f, 250.0f);
        Snd* s = (Snd*)fn_8024F3FC(0);
        if (s != NULL && s->v10() != 0) {
            s->v24(0x1F4);
            s->v0C();
        }
    }
    lbl_804CB700 &= 0xFFF0FFFF;
}

void* fn_801D3D78(void* parent) {
    u8* p = (u8*)fn_80081194(lbl_8038B160, parent);
    if (p != NULL) {
        fn_801E4094(p);
        F(p, int, 0x40) = 0;
        F(p, int, 0x44) = 0;
        F(p, int, 0x48) = 0;
        F(p, int, 0x4C) = 0;
        F(p, int, 0x50) = 0;
        F(p, int, 0x54) = 0;
    }
    fn_80081050(lbl_8038B0F0, p);
    return p;
}



int fn_801D44AC() { return (fn_801E71B4() == 0) ? 2 : 0; }
int fn_801D45FC() { return (fn_801E7164() == 0) ? 2 : 0; }
int fn_801D5398() { return (fn_801E7024() == 0) ? 2 : 0; }

void fn_801D5454(void* a, void* b) {
    void* w = fn_801E5640(fn_80083B84(lbl_8038B160), -0x1000, 0);
    if (w != NULL) F(w, void*, 0x64) = lbl_8038BDD0;
    fn_801DDDF8(a, b);
}

#pragma push
#pragma auto_inline off
void fn_801D5DFC() {
    if (lbl_804CBE0C++ == 0) {
        s8 lang = fn_8024BC94()[0x1BC8];
        fn_800068EC(&lbl_804CBDF8, (const char*)lbl_8038C1F0[lang][fn_801D09F0()], 0x2080);
        fn_800068EC(&lbl_804CBDFC, lbl_8036ECF8, 0x2080);
        fn_800068EC(&lbl_804CBE00, lbl_8036ECF8 + 0x15, 0x2080);
        fn_800068EC(&lbl_804CBE04, (const char*)lbl_8038C228[(s8)fn_8024BC94()[0x1BC8]], 0x2080);
        fn_800068EC(&lbl_804CBE08, lbl_8036ECF8 + 0x25, 0x2080);
    }
}
#pragma pop

void fn_801D5EC8() {
    s8 lang = fn_8024BC94()[0x1BC8];
    fn_8023F1A0((const char*)lbl_8038C1F0[lang][fn_801D09F0()], 0x2080);
    fn_8023F1A0(lbl_8036ECF8, 0x2080);
    fn_8023F1A0(lbl_8036ECF8 + 0x15, 0x2080);
    fn_8023F1A0((const char*)lbl_8038C228[(s8)fn_8024BC94()[0x1BC8]], 0x2080);
    fn_8023F1A0(lbl_8036ECF8 + 0x25, 0x2080);
    fn_800E24F8(lbl_8036ECF8 + 0x3A);
    fn_800E24F8(lbl_8036ECF8 + 0x45);
}

#pragma use_lmw_stmw on
int fn_801D5F7C() {
    int r = 0, d = 0, c = 0, b = 0;
    s8 lang = fn_8024BC94()[0x1BC8];
    if (fn_8023F880((const char*)lbl_8038C1F0[lang][fn_801D09F0()]) != 0 && fn_8023F880(lbl_8036ECF8) != 0) b = 1;
    if (b != 0 && fn_8023F880(lbl_8036ECF8 + 0x15) != 0) c = 1;
    if (c != 0 && fn_8023F880((const char*)lbl_8038C228[(s8)fn_8024BC94()[0x1BC8]]) != 0) d = 1;
    if (d != 0 && fn_8023F880(lbl_8036ECF8 + 0x25) != 0) r = 1;
    return r;
}
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
TITLE_END(fn_801D2EB4)
TITLE_END(fn_801D2FE0)
TITLE_END(fn_801D3104)

void fn_801D3ED0() {
    TitleP* p = (TitleP*)fn_80083B84(lbl_8038B160);
    if (p != NULL) {
        fn_801FBF08(p);
        MusicOut(p);
        fn_801E5870();
    }
    if (0.0f != F(fn_8025121C(6), f32, 0x10)) fn_80250E38(6, 0.0f, 500.0f);
    int v = fn_80068528(fn_8006074C(lbl_803CAB38));
    if (fn_8024F7EC(v) != 0) fn_80251838(0, v, 500.0f);
}


}
