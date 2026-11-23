/* Round 18, functionally equal (check_regs.py: renamed/regs): fn_80069220. Self-contained: fn_80068EC4.cpp with its exported fn_ bodies removed (originals the function inlines kept as static inline *_inl copies) plus the function. From wip/near.cpp. */
/* Menu window drawing, 80068EC4..80069B7C. */
#include "game/rO_80065D64/menu.h"
#pragma auto_inline off

struct Color { u8 r, g, b, a; };

struct MoveState { Unit* unit; u8 pad[0x20]; };
extern "C" {
extern MoveState lbl_803CA870;
extern f32 fn_800D58FC(Widget*);
extern f32 fn_8017F68C(int, f32, f32, f32, f32);
extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E5C0(f32, f32, f32, f32, f32, f32, f32, f32);
extern void fn_8007E7DC(u8);
extern void fn_8006E610(int, int, int, int, int, int);
extern void fn_8007E720(f32);
extern int fn_800CB0FC(int, f32);
extern void fn_80072ACC(int, int, int, int, int, int, int);
extern u8* fn_80085EF8(int);
extern void fn_800712E8(int, int, int);
extern Color* fn_800CD204(int);
extern void fn_80080508(Color*);
extern void fn_8007E174(int, int);
extern void fn_80193054(void);
extern void fn_80193120(void);
extern void fn_8019315C(void);
extern u8 lbl_803CAB38[];

void fn_80068EC4(void* a, Widget* w);

void fn_80068FEC(MenuBase* m, Widget* w);

void fn_80069140(void* a, Widget* w);

#pragma push
#pragma use_lmw_stmw on
static inline void ClampY(Widget* w) {
    s16 h = w->h;
    if (w->y + (h >> 1) > 0xE0) {
        w->y = (0x1C0 - h) >> 1;
    }
}

void fn_80069220(MenuBase* m, Widget* w);
#pragma pop

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
    virtual void v40();
    virtual void v44();
    virtual u32 v48();
};
extern volatile u32 lbl_804CB700;
extern Input* lbl_804CB5B8;
extern u8 lbl_8041EB20[];
extern int fn_801A2224(u8*);
extern void fn_801A1DCC(u8*, void*, f32, f32);
extern void fn_801A1F64(u8*, void*, f32, f32);
extern void fn_80253EE4(void*, f32);

static inline BOOL Blocked(void) {
    u32 f1 = lbl_804CB700;
    u32 f2 = lbl_804CB700;
    BOOL r = 0;
    if ((f1 & 0x10) && !(f2 & 0x20)) {
        r = 1;
    }
    return r;
}

void fn_80069428(MenuBase* m, Widget* w);

void fn_80069834(void);

void fn_80069838(MenuBase* m, Widget* w);

struct WItem { u8 pad[0x39]; u8 st; };

void fn_80069984(void* a, WItem* w);

class DrawA {
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
    virtual void v3C();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void* v4C(Widget*);
    virtual void v50(Widget*);
    virtual void v54(Widget*);
};
extern int fn_800CA3DC(char*, int, f32);
extern void fn_800800D4(int);
extern void fn_80080330(f32, f32);
extern void fn_80080C24(char*);
extern void fn_80080308(void);

void fn_800699DC(DrawA* a, Widget* w, Widget* it);

void fn_80069B0C(void);

void fn_80069B44(void);

void fn_80069B78(void);

extern void fn_8006E278(int, int, int);

void fn_80069B7C(MenuBase* m, Widget* w);

extern void fn_8007E4E4(f32, f32, f32, f32);
extern void fn_800720F4(void*, int, int);
extern void fn_80069F14(MenuBase*, Widget*, int, f32, f32);
extern void fn_8006A434(MenuBase*, Widget*, int, f32, f32);
extern void fn_8007309C(int, f32, f32);
extern u8 lbl_803C8E80[];
extern void** fn_80030CF4(void*);
extern void fn_800739A4(int, f32, f32);
extern void fn_800718D0(int, int, int, int, int, int);

struct MenuUnit { u8 pad[8]; Unit* unit; };

static inline int IdOf(u8* q) {
    if (q != 0) {
        return q[0x13];
    }
    return 0x13;
}

void fn_80069CE4(MenuBase* m, Widget* w, int f);

void fn_80069F14(MenuBase* m, Widget* w, int c, f32 x, f32 y);

void fn_8006A128(MenuUnit* m);

void fn_8006A138(void);

void fn_8006A13C(MenuBase* m, Widget* w);

extern void fn_80027228(u8*, Unit*, void*);
extern void fn_80107C80(void*, int, int, int);
extern void fn_801080CC(void*, int, int, int, int);
extern void fn_8011A0A8(void*);
extern void fn_800722B8(void*, int, int);
extern void fn_8007265C(int, int);
extern void fn_800804D4(int, int, int, int);
extern s8 lbl_804CA389[1];
extern u8 lbl_8037A1E8[];
extern u8* fn_80083B84(void*);
extern void fn_80192FD4(u8*);

class DrawB {
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
    virtual void v3C();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void* v4C(Widget*);
    virtual void v50(void*);
    virtual void v54(Widget*);
    virtual void* v58(Unit*, int, Widget*);
    virtual void** v5C(Widget*);
};

int fn_8006A144(DrawB* a, Widget* w, Widget* x);

void fn_8006A19C(DrawB* a, void* x, Widget* it);

Inv* fn_8006A210(void* x, Widget* it);

void fn_8006A230(MenuUnit* m);

void fn_8006A240(MenuBase* m, Widget* w);

void fn_8006A434(MenuBase* m, Widget* w, int c, f32 x, f32 y);

void fn_8006A648(DrawB* a, void* x, Widget* it);

void fn_8006A6D8(DrawB* a, Widget* x);

struct Skill { u8* data; u32 b; };

static inline Skill* SkillAt(Unit* u, int i) {
    return (Skill*)(u->skills + i * 8);
}

Skill* fn_8006A70C(void* x, Unit* u, u8 k);

void* fn_8006A7C8(DrawB* a, Widget* it);

void fn_8006A7EC(void* x, Widget* m);

void fn_8006A834(MenuBase* m, Widget* w);

void fn_8006A950(MenuBase* m);

void fn_8006C028(MenuBase* m, Widget* w);

}

#pragma use_lmw_stmw on
extern "C" {
/* from fn_80068EC4.cpp: 6 of 130 words differ */
void fn_80069220(MenuBase* m, Widget* w) {
    int n = w->n;
    if (n <= 10) {
        w->x = 400;
        w->w = 0x78;
        m->cols = n;
        m->rows = 1;
        ClampY(w);
    } else {
        int dx, dy, x0, y0;
        int ox, oy, px, r, k, c;
        m->cols = (n + 1) >> 1;
        m->rows = 2;
        int t = 400 - m->v58();
        w->x = t + 0x20;
        w->w = m->v58() + 0x78;
        y0 = m->cols * m->v5C();
        int hh = m->v4C();
        w->h = hh + y0;
        dx = m->v58();
        dy = m->v5C();
        x0 = m->v48();
        y0 = m->v4C();
        ClampY(w);
        dy = (s16)dy;
        x0 = (s16)x0;
        dx = (s16)dx;
        r = 0;
        k = 0;
        ox = 0;
        for (; r < m->rows && k < n; r++) {
            px = x0 + ox;
            c = 0;
            oy = 0;
            for (; c < m->cols && k < n; c++) {
                Widget* it = (Widget*)fn_80085EF8(w->ids[k]);
                it->x = px;
                int yy = y0 + oy;
                oy += dy;
                k++;
                it->y = yy;
            }
            ox += dx;
        }
    }
}


}
