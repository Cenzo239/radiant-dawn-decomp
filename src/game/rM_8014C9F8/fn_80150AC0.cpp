/* Talk window: text lines, fades, page advance. 80150AC0..801520C0. */
#include "game/rM_8014C9F8/win.h"
#pragma auto_inline off

extern "C" {

extern void* fn_80079150(int);
extern void fn_80079210(void*);
extern void fn_80079474(void*);
extern void fn_80081194b(void*);
extern u8 lbl_80386DF0[];
extern u8 lbl_80386E00[];
extern u8 lbl_80386E1C[];
extern u8 lbl_80386E38[];
extern u8 lbl_80386E50[];
extern u8 lbl_80386E68[];
extern u8 lbl_80386E80[];
extern u8 lbl_803CAB38[];
extern char lbl_8036A080[];
extern void* lbl_804CB8A8;
extern Proc* fn_800811E4(void*, void*);
extern u32* fn_80060728(void*);
extern void* fn_800D4188(void*, void*);
extern void fn_800D3BCC(void*, int);
extern void fn_800D3C90(void*, int);
extern void fn_80253EE4(char*, f32);
extern void fn_803080DC(int, int, int, int);
extern void fn_801D0940(int, int, int, int);
extern void fn_80150790(void*);
extern void DCFlushRange(void*, u32);

class Pad5B8 {
public:
    virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2C(); virtual void v30(); virtual u32 v34();
    virtual void v38(); virtual void v3C(); virtual void v40(); virtual void v44();
    virtual u32 v48();
};
extern Pad5B8* lbl_804CB5B8;

void fn_80150AC0(Win* w, s16 x, s16 y) {
    w->x = x;
    w->y = y;
}
void fn_80150ACC(Win* w, s8 v) { w->lineH = v; }
void fn_80150AD4(Win* w, s8 v) { w->rows = v; }
void fn_80150ADC(Win* w, s16 v) { w->w = v; }
void fn_80150AE4(Win* w, u8 v) { w->speed = v; }
void fn_80150AEC(Win* w, void* o, s16 x, s16 y) {
    w->obj = o;
    w->objx = x;
    w->objy = y;
}
void fn_80150AFC(Win* w, int x, int y) {
    if (x >= 0) {
        w->objx = x;
    }
    if (y >= 0) {
        w->objy = y;
    }
}
void fn_80150B18(Win* w, u8 v) { w->style = v; }


void fn_80150B4C(Win* w) {
    w->lineH = 0x1C;
    w->rows = 4;
    w->head = 0;
    w->tail = 0;
    w->reveal = 0;
    w->speed = w->lineH / 4;
    w->style = 1;
    w->b57 = 0;
    w->x = 0x20;
    w->y = 0x20;
    w->w = 400;
    w->h = w->lineH * w->rows;
    w->alpha = 0;
    w->bright = 0xFF;
    Color c = {0xFF, 0xFF, 0xFF, 0xFF};
    w->col = c;
}

Win* fn_80150BE8(Win* w) {
    int i;
    fn_80150B4C(w);
    for (i = 0; i < 8; i++) {
        TLine* l = (TLine*)fn_80079150(0x44);
        if (l != NULL) {
            l->clear();
        }
        w->lines[i] = l;
    }
    return w;
}

void fn_80150C68(Win* w) {
    int i;
    for (i = 0; i < 8; i++) {
        fn_80079210(w->lines[i]);
        w->lines[i] = NULL;
    }
}

void fn_80151328(void* unused, s16* r) {
    if (lbl_804CB878.has(0x200000)) {
        fn_801D0940(r[0], r[1], r[2], r[3]);
    } else {
        fn_803080DC(r[0], r[1], r[2], r[3]);
    }
}

void fn_80151360(Win* w, u8 c) {
    if (!(lbl_804CB878.has(0x100000))) {
        TLine* l = w->lines[w->tail % w->rows];
        *l->end++ = c;
        *l->end = 0;
    }
}

void fn_801513B0(Win* w) {
    w->tail++;
    if (w->tail > 0x60) {
        w->tail -= 0x40;
        w->head -= 0x40;
    }
}

BOOL fn_801513E4(Win* w) {
    return w->tail - w->head >= w->rows;
}

void
#if TARGET_PC
*
#endif
fn_80151414(void* p) {
#if TARGET_PC
return fn_80081050(lbl_80386DF0, p);
#else
fn_80081050(lbl_80386DF0, p);
#endif
}

void fn_80151424(WinFade* f) {
    f->c++;
    f->win->col.a = fn_8017F68C(0, f->a, f->b, f->c, f->d);
    if (f->c >= f->d) {
        fn_80083B78(f);
    }
}

static inline void WinClear(Win* w) {
    int i;
    for (i = 0; i < w->rows; i++) {
        if (w->lines[i] != NULL) {
            w->lines[i]->clear();
        }
    }
    w->head = 0;
    w->tail = 0;
    w->reveal = 0;
}

void fn_801514E8(WinFade* f) {
    f->win->col.a = 0xFF;
    WinClear(f->win);
}

void fn_80151548(Win* w, void* parent) {
    lbl_804CB878.w &= ~0x200;
    if (lbl_804CB700.has(3)) {
        WinClear(w);
    } else {
        WinFade* f = (WinFade*)fn_80081194(lbl_80386E00, parent);
        f->win = w;
        f->a = 0xFF;
        f->b = 0;
        f->c = 0;
        f->d = 0x10;
    }
}

static inline void WinNext(Win* w) {
    TLine* l = w->lines[w->head % w->rows];
    l->clear();
    w->head++;
    w->reveal = 0;
}

void fn_80151600(WinFade* f) {
    if (f->c != 0) {
        WinClear(f->win);
    } else {
        WinNext(f->win);
    }
}



void fn_80151818(Win* w, void* parent) {
    if (lbl_804CB700.has(3)) {
        WinNext(w);
    } else {
        WinFade* f = (WinFade*)fn_80081194(lbl_80386E1C, parent);
        u8 sp = w->speed;
        f->b = sp;
        f->a = w->lineH;
        f->win = w;
        f->sleep = sp;
        f->c = 0;
    }
}

void fn_801518C4(Win* w, void* parent) {
    lbl_804CB878.w &= ~0x200;
    if (lbl_804CB700.has(3)) {
        WinClear(w);
    } else {
        int n = w->tail + 1 - w->head;
        if (n != 0) {
            if (n > 4) {
                n = 4;
            }
            WinFade* f = (WinFade*)fn_80081194(lbl_80386E1C, parent);
            int t = n * w->speed;
            f->b = t;
            f->a = w->lineH * n;
            f->win = w;
            f->sleep = t;
            f->c = 1;
        }
    }
}

void fn_801519B8(WinFade* f) {
    fn_8014D220(&lbl_804CB878);
    if (f->b != 0) {
        f->b--;
    }
    if (fn_80148634() != 0 || (lbl_804CB878.has(4)) || f->b == 1) {
        if (!(lbl_804CB878.has(0x10000))) {
            fn_80253EE4(lbl_8036A080, 0.0f);
        }
        if (f->win != NULL) {
            fn_800D3C90((void*)f->c, 8);
        }
        fn_80083B78(f);
        lbl_804CB878.w = (lbl_804CB878.w & ~0x200) | 0x800;
    } else if (!(lbl_804CB700.has(0x10)) && (lbl_804CB5B8->v48() & 0x10)) {
        fn_80150790(f);
    }
}

void fn_80151AA0(Win* w, void* parent, int arg) {
    if (lbl_804CB700.has(3)) {
        return;
    }
    if (*(volatile u32*)&lbl_804CB878.w & 0x100000) {
        lbl_804CB878.w &= ~0x100000;
    } else {
        struct P : Proc {
            void* obj;
            s16 x, y;
            int arg;
            u8* sub;
        };
        s16 x;
        s16 y;
        P* p;
        void* o;
        p = (P*)fn_80081194(lbl_80386E38, parent);
        o = w->obj;
        y = w->objy;
        x = w->objx;
        p->obj = o;
        p->x = x;
        p->y = y;
        p->arg = arg;
        if (o != NULL) {
            u8* s = (u8*)fn_800D4188(o, p);
            p->sub = s;
            *(f32*)(s + 0x40) = x;
            *(f32*)(s + 0x44) = y;
            fn_800D3BCC(p->sub, 8);
        }
    }
}

void fn_80151B94(WinFade* f) {
    fn_8014D220(&lbl_804CB878);
    f->a++;
    if (f->a > f->b || (lbl_804CB700.has(3))) {
        fn_80083B78(f);
        if (f->d == 0) {
            WinClear(f->win);
        }
    } else {
        f->win->alpha = fn_8017F68C(0, f->c, f->d, f->a, f->b);
    }
}

void fn_80151CC4(Win* w, void* parent) {
    if (!(lbl_804CB700.has(3))) {
        WinFade* f = (WinFade*)fn_800811E4(lbl_80386E50, parent);
        f->win = w;
        f->c = w->alpha;
        f->d = 0xFF;
        f->a = 0;
        f->b = 8;
    }
}

void fn_80151D28(Win* w, void* parent) {
    if (lbl_804CB700.has(3)) {
        w->alpha = 0;
    } else {
        WinFade* f = (WinFade*)fn_800811E4(lbl_80386E50, parent);
        f->win = w;
        f->c = w->alpha;
        f->d = 0;
        f->a = 0;
        f->b = 8;
    }
}

void fn_80151D94(Proc* p) {
    fn_8014D220(&lbl_804CB878);
    fn_80148634();
    if ((lbl_804CB878.has(0x200)) || (lbl_804CB700.has(3))) {
        fn_80083B78(p);
    }
}

void fn_80151EC4(Proc* p) {
    fn_8014D220(&lbl_804CB878);
    if (lbl_804CB700.has(3)) {
        fn_80083B78(p);
    }
}

void fn_80151F08(void* a, void* parent, s16 t) {
    if (!(lbl_804CB700.has(3))) {
        Proc* p = fn_80081194(lbl_80386E80, parent);
        p->sleep = t;
    }
}




struct Dissolve : Proc {
    u8* tex;    /* 0x30 */
    s16* order; /* 0x34 */
    int left;   /* 0x38 */
    int pos;    /* 0x3C */
};

#pragma push
#pragma use_lmw_stmw on
void fn_80151F4C(Dissolve* d) {
    int i;
    for (i = 0; i < 8; i++) {
        d->tex[d->order[d->pos++]] = 0xFF;
    }
    DCFlushRange(d->tex, 0x200);
    if (--d->left == 0) {
        fn_80083B78(d);
    }
}

#pragma pop

void fn_80152080(Dissolve* d) {
    fn_80079474(d->order);
    fn_80079474(d->tex);
    lbl_804CB8A8 = NULL;
}

extern u8 lbl_80386E8C[];
extern void* fn_800791B0(int);
extern int fn_80089C88(int);




extern void fn_80021BF4(int);
extern void fn_80022158(int, int, int);
extern void fn_80021C34(int);
extern void fn_80312D2C(f32, f32, f32, f32, f32, f32, f32, f32, void*);
extern void fn_80307F10(void*, int, int);
extern void fn_80021F7C(int, int, int, int);
extern void fn_80021BA4(int, int, int, int);
extern void fn_80021CB4(int, int, int, int);
extern void fn_80021E20(int, int, int, int, int);
extern void fn_80021D18(int, int, int, int, int, int);
extern void fn_80021E8C(int, int, int, int, int);
extern void fn_80021D9C(int, int, int, int, int, int);
extern void fn_80306FD8(int, int, int, int, int);
extern void fn_80305A40(void*, void*, int, int, int, int, int, int);
extern void fn_80305C94(void*, f32, f32, f32, int, int, int, int, int);
extern void fn_80022254(void*, int);

void fn_80150CC4(u32 flag) {
    char mtx[0x30];
    char tex[0x20];
    if (!(flag & 0x1000)) {
        fn_80021BF4(1);
        fn_80022158(1, 0, 0);
    } else {
        fn_80021C34(2);
        fn_80312D2C(-8.0f, 8.0f, -16.0f, 16.0f, 0.5f, 0.5f, 0.5f, 0.5f, mtx);
        fn_80307F10(mtx, 0x21, 1);
        fn_80021F7C(1, 1, 0, 0x21);
        fn_80021F7C(0, 1, 4, 0x1E);
        fn_80021BA4(1, 4, 5, 0);
        fn_80021BF4(2);
        fn_80021CB4(0, 0, 0, 4);
        fn_80021E20(0, 0xF, 0xF, 0xF, 0xA);
        fn_80021D18(0, 0, 0, 0, 1, 0);
        fn_80021E8C(0, 7, 4, 5, 7);
        fn_80021D9C(0, 0, 0, 0, 1, 0);
        fn_80022158(1, 0, 1);
        fn_80306FD8(1, 0, 0, 0, 0);
        fn_80021CB4(1, 1, 1, 0xFF);
        fn_80021E20(1, 0xF, 0xF, 0xF, 0);
        fn_80021D18(1, 0, 0, 0, 1, 0);
        fn_80021E8C(1, 7, 4, 0, 7);
        fn_80021D9C(1, 0, 0, 0, 1, 0);
        if (lbl_804CB8A8 != NULL) {
            fn_80305A40(tex, ((void**)lbl_804CB8A8)[0x30 / 4], 0x20, 0x10, 1, 1, 1, 0);
            fn_80305C94(tex, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0);
            fn_80022254(tex, 1);
        }
    }
}

extern void* fn_800C409C(int);
extern u8 fn_8014C83C(void);
extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E4E4(f32, f32, f32, f32);
extern void fn_8007E84C(int);
extern void fn_8007E7DC(u8);
extern void fn_8007E7E8(u8);
extern void fn_8007E174(void*, int);
#if TARGET_PC
extern FE10_PROTO void fn_8007E74C(ptr32<const void>, ptr32<const void>);
extern FE10_PROTO void fn_8007E780(ptr32<const void>, ptr32<const void>);
#else
extern void fn_8007E74C(void*, void*);
extern void fn_8007E780(void*, void*);
#endif
extern void fn_802291A8(int, int, int, const Color&, const Color&);
extern void fn_800800D4(int);
extern void fn_80080ABC(int, f32);
extern void fn_80080B70(int, f32);
extern void fn_80080B00(int, void*, f32);
extern void* fn_800CD204(int);
extern int fn_8007E9BC(int);
extern void fn_80080330(f32, f32);
extern void fn_800804D4(u8, u8, u8, u8);
extern void fn_80080C24(const char*);
extern void fn_80080308(void);
extern void fn_8007E7F4(void);
extern Color lbl_804CA7A0;
extern Color lbl_804CA7A4;

static inline Color WA(u8 r, u8 g, u8 b, u8 a) {
    Color c;
    c.r = r;
    c.g = g;
    c.b = b;
    c.a = a;
    return c;
}

static inline void Rect4(s16* r, s16 x, s16 y, s16 x2, s16 y2) {
    r[0] = x;
    r[1] = y;
    r[2] = x2;
    r[3] = y2;
}



}
