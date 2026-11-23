/* Multi-line text box layout, split from fn_8006AA70.cpp's context. */
/* Choice and text boxes, 8006AA70..8006B9CC. */
#include "game/rO_80065D64/menu.h"
#pragma auto_inline off

struct Obj8 { u32 a; u32 b; };
class DrawA {
public:
    virtual void v08();
    virtual char* v0C();
    virtual void v10();
    virtual void v14();
    virtual char* v18(Widget*);
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2C();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3C();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4C();
    virtual void v50(Widget*);
};
class Input {
public:
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2C();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual u32 v3C();
};

struct Color { u8 r, g, b, a; };
struct MsgEnt { u32 f0; const char* s; };
struct MsgTab {
    u8 pad0[0x50];
    MsgEnt e[4];   /* 50 */
    MsgEnt* t[6];  /* 70 */
    u8 o88[0x10];  /* 88 */
    u8 o98[0x10];  /* 98 */
};
extern "C" {
extern u8* fn_80085EF8(int);
extern int fn_800CB0FC(int, f32);
extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E720(f32);
extern void fn_800712E8(int, int, int);
extern void fn_80072ACC(int, int, int, int, int, int, int);
extern Input* lbl_804CB5B8;
extern char lbl_80362230[];
extern void fn_80253EE4(void*, f32);
extern s8 lbl_804CA388[1];
extern s8 lbl_804CA389[1];
extern void fn_8007265C(int, int);
extern void fn_80072944(int, int);
#if TARGET_PC
extern FE10_PROTO void fn_8007E174(p32arg, int);
#else
extern void fn_8007E174(int, int);
#endif
extern int fn_800CA3DC(char*, int, f32);
extern void fn_800800D4(int);
extern void fn_80080330(f32, f32);
extern void fn_800804D4(int, int, int, int);
extern void fn_80080C24(char*);
extern void fn_80080308(void);
extern Obj8 lbl_804CB570;
extern Obj8 lbl_804CB578;
struct Pos16 { u8 pad[0xC]; void* fC; u8 pad10[0x10]; };
extern Pos16 lbl_803CB7B8;
extern Pos16 lbl_803CB7C8;
extern Pos16 lbl_803CB7F0;
extern void* fn_800D5448(Pos16*, void*, int);
extern void fn_8006A834(MenuBase*, Widget*);
extern int fn_800CAD6C(char**, int, f32);
extern unsigned long strlen(const char*);
extern char* strcpy(char*, const char*);
extern char* fn_800791B0(int);
extern void fn_80079474(char*);
extern void fn_8007E4E4(f32, f32, f32, f32);
extern f32 fn_800D58FC(Widget*);
extern void fn_8007E7DC(u8);
extern void fn_8007E7E8(int);
extern void fn_800D4A10(void*, void*);
extern void fn_800727E4(int, int, int, int);
extern void fn_80150790(void*);
extern Color* fn_800CD204(int);
extern void fn_80080508(Color*);
extern void* fn_8009E898(void);
extern u8 lbl_803CA870[];
extern void fn_800453B4(u8*, int);
extern void fn_800312BC(void);
#define lbl_803CB7B8m (*(MsgTab*)&lbl_803CB7B8)
#define fn_800D5448b(a, b, c) ((Widget*)fn_800D5448((Pos16*)(a), (b), (c)))

void fn_8006AA70(MenuBase* m, Widget* w);

void fn_8006ABFC(void* x, Widget* w);

int fn_8006AD0C(void);

int fn_8006AD14(void);

static inline void DrawLine(f32 x, f32 y, char* s) {
    fn_800800D4(5);
    fn_80080330(x, y);
    fn_800804D4(0, 0, 0, 0xFF);
    fn_80080C24(s);
    fn_80080308();
}


void fn_8006AD24(MenuBase* m);

u8 fn_8006AF20(void* a, void* b, int c);

void fn_8006AF38(DrawA* a, Widget* w, Widget* it);

void* fn_8006B080(void* a, void* b, u32 c, u32 d);

void fn_8006B0D4(MenuBase* m, Widget* w);

void fn_8006B1C8(MenuBase* m);

void* fn_8006B3C4(void* a, void* b, u32 c, u32 d);

void fn_8006B418(MenuBase* m, Widget* w);

void fn_8006B528(MenuBase* m);

void fn_8006B73C(void* a, Widget* w);

void* fn_8006B81C(void* a, void* b, u32 c, u32 d);

void fn_8006B870(MenuBase* m, Widget* w);

void fn_8006B9CC(MenuBase* m);

void fn_8006BA04(MenuBase* m, Widget* w);

void fn_8006BB84(void*, void*);

void fn_8006BB90(MenuBase* m);

int fn_8006BB88(void);

int fn_8006BC10(void* a, void* b, Widget* it);

int fn_8006BC34(void* a, void* x);

void fn_8006BC5C(DrawA* a, Widget* w, Widget* it);

void fn_8006BDCC(const char* a, const char* b);

void fn_8006BE30(const char* a, const char* b, const char* c);

void fn_8006BEA0(const char* a, const char* b, const char* c, u8 d, u8 f, u8 g2);

void fn_8006BF64(const char* a, const char* b, const char* c, const char* d);

int fn_8006BFE0(void);

void fn_8006BFEC(s8 v);

int fn_8006BFF4(void);

int fn_8006C17C(void);

int fn_8006C18C(void);
#pragma use_lmw_stmw on
void fn_8006B870(MenuBase* m, Widget* w) {
    /*P*/
    s8 n;
    s16 tot;
    int i;
    int i2;
    int x;
    s16 y;
/*E*/
    m->rows = 0;
    n = w->n;
    tot = n * m->v5C();
    for (i = 0; i < w->n; i++) {
        s16 tw = fn_800CA3DC(((Widget*)fn_80085EF8(w->ids[i]))->obj->v0C(), -1, 1.0f);
        if (tw >= m->rows) {
            m->rows = tw;
        }
    }
    m->sC = ((s16)m->v50() - m->rows) >> 1;
    y = ((s16)m->v54() - tot) >> 1;
    m->sE = y;
    x = m->sC;
    for (i2 = 0; i2 < w->n; ) {
        u8* id = &w->ids[i2];
        ((Widget*)fn_80085EF8(*id))->x = x;
        ((Widget*)fn_80085EF8(*id))->y = y;
        i2++;
        y += (s16)m->v5C();
    }
}
#pragma use_lmw_stmw off
}
