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
#if TARGET_PC
extern FE10_PROTO void fn_8007E174(p32arg, int);
#else
extern void fn_8007E174(int, int);
#endif
extern void fn_80193054(void);
extern void fn_80193120(void);
extern void fn_8019315C(void);
extern u8 lbl_803CAB38[];

void fn_80068EC4(void* a, Widget* w) {
    f32 t = fn_8017F68C(5, 0.0f, 1.0f, fn_800D58FC(w), 1.0f);
    fn_8007E154();
    fn_8007E5C0(w->x, w->y, w->menu->v70(), w->w / 2, w->h / 2, t, t, 0.0f);
    fn_8007E7DC(255.99f * fn_800D58FC(w));
    fn_8007E164();
}

void fn_80068FEC(MenuBase* m, Widget* w) {
    m->v90();
    fn_8006E610(0, 0, w->w, w->h + 0xC, 0, 0);
    if (w->s3A >= 5) {
        fn_8007E154();
        fn_8007E720(-0.1f);
        fn_8007E164();
        int a = 0;
        if (w->b2D == 0 && w->b2E == 0) {
            a = 1;
        }
        fn_80072ACC((s16)m->v50() / 2, w->s3A + fn_800CB0FC(-1, 1.0f) / 2, (int)(0.9f * (s16)m->v50()), 0x18, 0x19, 0x4B, a);
        fn_8007E154();
        fn_8007E720(0.1f);
        fn_8007E164();
    }
}

void fn_80069140(void* a, Widget* w) {
    s16 x = ((Widget*)fn_80085EF8(w->ids[(s8)w->cur]))->x;
    s16 y = ((Widget*)fn_80085EF8(w->ids[(s8)w->cur]))->y;
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
}

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

void fn_80069834(void) {}

void fn_80069838(MenuBase* m, Widget* w) {
    m->v90();
    fn_8006E610(0, 0, w->w, w->h + 0xC, 0, 0);
    if (w->s3A >= 5) {
        fn_8007E154();
        fn_8007E720(-0.1f);
        fn_8007E164();
        int a = 0;
        if (w->b2D == 0 && w->b2E == 0) {
            a = 1;
        }
        fn_80072ACC(w->s38 + ((s16)m->v58() >> 1), w->s3A + (fn_800CB0FC(-1, 1.0f) >> 1), (int)(0.9f * (s16)m->v58()), 0x18, 0x19, 0x4B, a);
        fn_8007E154();
        fn_8007E720(0.1f);
        fn_8007E164();
    }
}

struct WItem { u8 pad[0x39]; u8 st; };

void fn_80069984(void* a, WItem* w) {
    if (w->st == 2) {
        Color c = *fn_800CD204(0);
        fn_80080508(&c);
    }
}

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

void fn_800699DC(DrawA* a, Widget* w, Widget* it) {
    int tw = fn_800CA3DC(it->obj->v18(it), -1, 1.0f);
    int d = ((s16)w->menu->v58() - tw) / 2;
    a->v50(w);
    fn_800800D4(5);
    fn_80080330(it->x + d, it->y);
    a->v54(it);
    fn_80080C24(it->obj->v18(it));
    fn_80080308();
}

void fn_80069B0C(void) {
    fn_8007E154();
    fn_8007E720(-1.0f);
    fn_8007E174(0, 0x13);
    fn_8007E164();
}

void fn_80069B44(void) {
    lbl_803CAB38[0x92C] = 0xF;
    fn_80193054();
    fn_80193120();
}

void fn_80069B78(void) {
    fn_8019315C();
}

extern void fn_8006E278(int, int, int);

void fn_80069B7C(MenuBase* m, Widget* w) {
    int n = w->n;
    m->v90();
    fn_8006E278(0, 0, n * (s16)m->v5C() + 0x34);
    if (w->s3A >= 5) {
        fn_8007E154();
        fn_8007E720(-0.1f);
        fn_8007E164();
        int a = 0;
        if (w->b2D == 0 && w->b2E == 0) {
            a = 1;
        }
        fn_80072ACC((s16)m->v50() / 2, w->s3A + fn_800CB0FC(-1, 1.0f) / 2, (int)(0.9f * (s16)m->v50()), 0x17, 0x19, 0x4B, a);
        fn_8007E154();
        fn_8007E720(0.1f);
        fn_8007E164();
    }
}

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

void fn_8006A128(MenuUnit* m) {
    m->unit = lbl_803CA870.unit;
}

void fn_8006A138(void) {}

void fn_8006A13C(MenuBase* m, Widget* w) {
    fn_80069CE4(m, w, 1);
}

extern void fn_80027228(u8*, Unit*, void*);
extern void fn_80107C80(void*, int, int, int);
#if TARGET_PC
extern FE10_PROTO void fn_801080CC(void*, int, int, int, p32arg);
#else
extern void fn_801080CC(void*, int, int, int, int);
#endif
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

int fn_8006A144(DrawB* a, Widget* w, Widget* x) {
    Unit* u = ((MenuUnit*)w->menu)->unit;
    fn_80027228(lbl_803C8E80, u, a->v4C(x));
    return 0;
}

void fn_8006A19C(DrawB* a, void* x, Widget* it) {
    a->v50(x);
    fn_80107C80(a->v4C(it), ((WItem*)it)->st == 0, it->x, it->y);
}

Inv* fn_8006A210(void* x, Widget* it) {
    return &((MenuUnit*)it->parent->menu)->unit->inv[it->b3A];
}

void fn_8006A230(MenuUnit* m) {
    m->unit = lbl_803CA870.unit;
}

void fn_8006A240(MenuBase* m, Widget* w) {
    f32 t = fn_800D58FC(w);
    int a = 0;
    w->y = a;
    w->x = a;
    int al = 255.0f * t;
    fn_8007E154();
    fn_8007E7DC(al);
    fn_8007E4E4(0.0f, 0.0f, m->v70(), 1.0f);
    fn_8007E164();
    fn_800722B8(((MenuUnit*)m)->unit, 16.0f * t + 16.0f, 0x23);
    fn_8006A434(m, w, ((MenuUnit*)m)->unit->team[8], 16.0f * t + 28.0f, 140.0f);
    if (w->s3A >= 5) {
        fn_8007E154();
        fn_8007E720(-0.1f);
        fn_8007E164();
        if (w->b2D == 0 && w->b2E == 0) {
            a = 1;
        }
        fn_80072ACC((s16)m->v50() / 2 + 0x2E, w->s3A + (s16)m->v5C() / 2, (int)(f32)(s16)m->v50(), 0x18, 0x19, 0x4B, a);
        fn_8007E154();
        fn_8007E720(0.1f);
        fn_8007E164();
    }
}

void fn_8006A434(MenuBase* m, Widget* w, int c, f32 x, f32 y);

void fn_8006A648(DrawB* a, void* x, Widget* it) {
    a->v50(x);
    BOOL s = ((WItem*)it)->st == 0;
    void** p = a->v5C(it);
    if (p != 0 && *p != 0) {
        fn_801080CC(p, s, it->x, it->y, 0);
    }
}

void fn_8006A6D8(DrawB* a, Widget* x) {
    fn_8011A0A8(*a->v5C(x));
}

struct Skill { u8* data; u32 b; };

static inline Skill* SkillAt(Unit* u, int i) {
    return (Skill*)(u->skills + i * 8);
}

Skill* fn_8006A70C(void* x, Unit* u, u8 k) {
    int i;
    for (i = 0; i < 0x12; i++) {
        Skill* s = SkillAt(u, i);
        if (s != 0 && s->data != 0 && s->data[0x1F] != 0) {
            if (k-- == 0) {
                return s;
            }
        }
    }
    return 0;
}

void* fn_8006A7C8(DrawB* a, Widget* it) {
    return a->v58(((MenuUnit*)it->parent->menu)->unit, it->b3A, it);
}

void fn_8006A7EC(void* x, Widget* m) {
    u8* par = (u8*)m->parent;
    u8* f = fn_80083B84(lbl_8037A1E8);
    if (par == f) {
        fn_80192FD4(f);
    }
    lbl_804CA389[0] = -1;
}

void fn_8006A834(MenuBase* m, Widget* w);

void fn_8006A950(MenuBase* m) {
    m->v90();
    fn_8007265C(0, 0);
    fn_8007E154();
    fn_8007E720(-1.0f);
    fn_8007E174(0, 0x13);
    fn_8007E164();
    int mw = (s16)m->v50();
    f32 fx = (mw - fn_800CA3DC(m->v08(), -1, 1.0f)) / 2;
    fn_800800D4(5);
    fn_80080330(fx, 32.0f);
    fn_800804D4(0, 0, 0, 0xFF);
    fn_80080C24(m->v08());
    fn_80080308();
}

void fn_8006C028(MenuBase* m, Widget* w) {
    m->v90();
    fn_8006E610(0, 0, w->w, w->h + 0xC, 0, 0);
    if (w->s3A >= 5) {
        fn_8007E154();
        fn_8007E720(-0.1f);
        fn_8007E164();
        int a = 0;
        if (w->b2D == 0 && w->b2E == 0) {
            a = 1;
        }
        fn_80072ACC((s16)m->v50() / 2, w->s3A + fn_800CB0FC(-1, 1.0f) / 2, (int)(0.9f * (s16)m->v50()), 0x18, 0x19, 0x4B, a);
        fn_8007E154();
        fn_8007E720(0.1f);
        fn_8007E164();
    }
}

}
