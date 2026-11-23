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

void fn_8006ABFC(void* x, Widget* w) {
    u32 keys = lbl_804CB5B8->v3C();
    u8 c = w->cur;
    w->prev = c;
    if ((s8)c != 0 && (keys & 0x100001)) {
        w->cur = c - 1;
    }
    if ((s8)w->cur != (s8)*(u8*)&w->n - 1 && (keys & 0x200002)) {
        w->cur++;
    }
    if ((s8)w->cur != (s8)w->prev) {
        Widget* it = (Widget*)fn_80085EF8(w->ids[(s8)w->prev]);
        it->obj->v48(w, it);
        it = (Widget*)fn_80085EF8(w->ids[(s8)w->cur]);
        it->obj->v44(w, it);
        fn_80253EE4(lbl_80362230, 0.0f);
    }
}

int fn_8006AD0C(void) {
    return 0;
}

int fn_8006AD14(void) {
    lbl_804CA388[0] = 0;
    return 9;
}

static inline void DrawLine(f32 x, f32 y, char* s) {
    fn_800800D4(5);
    fn_80080330(x, y);
    fn_800804D4(0, 0, 0, 0xFF);
    fn_80080C24(s);
    fn_80080308();
}


void fn_8006AD24(MenuBase* m) {
    m->v90();
    fn_8007265C(0, 0);
    fn_8007E154();
    fn_8007E720(-1.0f);
    fn_8007E174(0, 0x13);
    fn_8007E164();
    int mw = (s16)m->v50();
    f32 fx = (mw - fn_800CA3DC(m->v08(), -1, 1.0f)) / 2;
    fn_800800D4(5);
    fn_80080330(fx, 24.0f);
    fn_800804D4(0, 0, 0, 0xFF);
    fn_80080C24(m->v08());
    fn_80080308();
    int mw2 = (s16)m->v50();
    fx = (mw2 - fn_800CA3DC(m->v94(), -1, 1.0f)) / 2;
    fn_800800D4(5);
    fn_80080330(fx, (s16)m->v98() + 0x18);
    fn_800804D4(0, 0, 0, 0xFF);
    fn_80080C24(m->v94());
    fn_80080308();
}

u8 fn_8006AF20(void* a, void* b, int c) {
    return c == lbl_804CA389[0];
}

void fn_8006AF38(DrawA* a, Widget* w, Widget* it) {
    int tw = fn_800CA3DC(a->v0C(), -1, 1.0f);
    f32 fx = it->x - (tw >> 1);
    int s = (s16)w->menu->v5C();
    s16 y = it->y + ((s - fn_800CB0FC(-1, 1.0f)) >> 1);
    a->v50(w);
    fn_800800D4(5);
    fn_80080330(fx, y);
    fn_800804D4(0, 0, 0, 0xFF);
    fn_80080C24(a->v18(it));
    fn_80080308();
    fn_8007E154();
    fn_8007E720(1.0f);
    fn_8007E164();
}

void* fn_8006B080(void* a, void* b, u32 c, u32 d) {
    lbl_804CA388[0] = -1;
    if (b != 0) {
        lbl_803CB7B8.fC = b;
    }
    if (c != 0) {
        lbl_804CB570.b = c;
    }
    if (d != 0) {
        lbl_804CB578.b = d;
    }
    return fn_800D5448(&lbl_803CB7B8, a, 0);
}

void fn_8006B0D4(MenuBase* m, Widget* w) {
    fn_8006A834(m, w);
    s16 tw = 0;
    s16 mx = -1;
    char* s = m->v08();
    char c;
    while ((c = *s) != 0) {
        switch (c) {
        case 0xA:
            if (tw > mx) {
                mx = tw;
            }
            s++;
            tw = 0;
            break;
        default:
            tw += fn_800CAD6C(&s, -1, 1.0f);
            break;
        }
    }
    if (tw > mx) {
        mx = tw;
    }
    m->lines[0] = ((s16)m->v50() - mx) >> 1;
}

void fn_8006B1C8(MenuBase* m) {
    m->v90();
    fn_8007265C(0, 0);
    int len = strlen(m->v08()) + 1;
    char* buf = fn_800791B0(len * 2 - len);
    char* line = buf;
    strcpy(buf, m->v08());
    f32 x = (s16)m->v48();
    f32 y = 16.0f;
    fn_8007E154();
    fn_8007E720(-1.0f);
    fn_8007E174(0, 0x13);
    fn_8007E164();
    char* p = buf;
    char c;
    while ((c = *p) != 0) {
        if (c == 0xA) {
            *p = 0;
            DrawLine(x, y, line);
            y += fn_800CB0FC(-1, 1.0f) + 2;
            line = p + 1;
        }
        p++;
    }
    DrawLine(x, y, line);
    fn_80079474(buf);
    fn_8007E154();
    fn_8007E720(1.0f);
    fn_8007E164();
}

void* fn_8006B3C4(void* a, void* b, u32 c, u32 d) {
    lbl_804CA388[0] = -1;
    if (b != 0) {
        lbl_803CB7C8.fC = b;
    }
    if (c != 0) {
        lbl_804CB570.b = c;
    }
    if (d != 0) {
        lbl_804CB578.b = d;
    }
    return fn_800D5448(&lbl_803CB7C8, a, 0);
}

void fn_8006B418(MenuBase* m, Widget* w) {
    fn_8006A834(m, w);
    s16 tw = 0;
    int l = 0;
    char* s = m->v08();
    char c;
    while ((c = *s) != 0) {
        switch (c) {
        case 0xA:
            m->lines[(s16)l] = ((s16)m->v50() - tw) >> 1;
            tw = 0;
            l++;
            s++;
            break;
        default:
            tw += fn_800CAD6C(&s, -1, 1.0f);
            break;
        }
    }
    m->lines[(s16)l] = ((s16)m->v50() - tw) >> 1;
}

void fn_8006B528(MenuBase* m);

void fn_8006B73C(void* a, Widget* w) {
    fn_8007E154();
    fn_8007E4E4(w->x, w->y, w->menu->v70(), 1.0f);
    fn_8007E7DC(255.99f * fn_800D58FC(w));
    int b = 0;
    if (w->b2D != 0 || w->b2E != 0) {
        b = 1;
    }
    int v = 0x58;
    if (b == 0) {
        v = 0x80;
    }
    fn_8007E7E8(v);
    fn_8007E164();
}

void* fn_8006B81C(void* a, void* b, u32 c, u32 d) {
    lbl_804CA388[0] = -1;
    if (b != 0) {
        lbl_803CB7F0.fC = b;
    }
    if (c != 0) {
        lbl_804CB570.b = c;
    }
    if (d != 0) {
        lbl_804CB578.b = d;
    }
    return fn_800D5448(&lbl_803CB7F0, a, 0);
}

void fn_8006B870(MenuBase* m, Widget* w);

void fn_8006B9CC(MenuBase* m) {
    m->v90();
    fn_8007265C(0, 0);
}

void fn_8006BA04(MenuBase* m, Widget* w) {
    s16 x = ((Widget*)fn_80085EF8(w->ids[(s8)w->cur]))->x - 0x10;
    s16 y = ((Widget*)fn_80085EF8(w->ids[(s8)w->cur]))->y;
    int h = (s16)m->v5C();
    y += (h - fn_800CB0FC(-1, 1.0f)) >> 1;
    if (w->s3A < 0) {
        w->s38 = x;
        w->s3A = y;
    } else {
        w->s38 = (w->s38 + x) / 2;
        w->s3A = (w->s3A + y) / 2;
    }
    fn_8007E154();
    fn_8007E720(-2.0f);
    fn_8007E164();
    int b = 0;
    if (w->b2D == 0 && w->b2E == 0) {
        b = 1;
    }
    fn_800712E8(w->s38, w->s3A, b);
    s16 ww = m->rows + 0x40;
    s16 hh = fn_800CB0FC(-1, 1.0f);
    fn_8007E154();
    fn_8007E720(2.9f);
    fn_8007E164();
    fn_80072ACC(w->s38 + (ww >> 1) - 0x10, w->s3A + (hh >> 1), ww, 0x18, 0x19, 0x4B, 1);
}

void fn_8006BB84(void* m, void* p) {
    fn_800D4A10(m, p);
}

void fn_8006BB90(MenuBase* m) {
    m->v90();
    int h = (s16)m->v54();
    fn_800727E4(0, 0, (s16)m->v50(), h);
}

int fn_8006BB88(void) {
    return 0;
}

int fn_8006BC10(void* a, void* b, Widget* it) {
    if (it->b39 != 0) {
        return 0x10;
    }
    lbl_804CA388[0] = it->b3A;
    return 5;
}

int fn_8006BC34(void* a, void* x) {
    fn_80150790(x);
    return 0;
}

void fn_8006BC5C(DrawA* a, Widget* w, Widget* it) {
    f32 fx = it->x;
    int s = (s16)w->menu->v5C();
    f32 fy = it->y + ((s - fn_800CB0FC(-1, 1.0f)) >> 1);
    a->v50(w);
    fn_800800D4(5);
    fn_80080330(fx, fy);
    if (it->b39 != 0) {
        Color c = *fn_800CD204(0x21);
        fn_80080508(&c);
    } else {
        fn_800804D4(0, 0, 0, 0xFF);
    }
    fn_80080C24(a->v0C());
    fn_80080308();
    fn_8007E154();
    fn_8007E720(1.0f);
    fn_8007E164();
}

void fn_8006BDCC(const char* a, const char* b);

void fn_8006BE30(const char* a, const char* b, const char* c);

void fn_8006BEA0(const char* a, const char* b, const char* c, u8 d, u8 f, u8 g2);

void fn_8006BF64(const char* a, const char* b, const char* c, const char* d);

int fn_8006BFE0(void) {
    return lbl_804CA388[0];
}

void fn_8006BFEC(s8 v) {
    lbl_804CA389[0] = v;
}

int fn_8006BFF4(void) {
    fn_800453B4(lbl_803CA870, 0);
    fn_800312BC();
    return 9;
}

int fn_8006C17C(void) {
    lbl_804CA388[0] = 0;
    return 5;
}

int fn_8006C18C(void) {
    lbl_804CA388[0] = 1;
    return 5;
}
}
