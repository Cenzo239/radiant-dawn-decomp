/* Relation chart: per-frame input, zoom, scroll and cursor */
#include "game/rN_8025EEF0/calls.h"
#include "game/rN_8025EEF0/dict.h"

extern "C" {
extern f32 lbl_80391920[];
extern f32 lbl_80391930[];
f32 fn_8017F68C(f32 a, f32 b, f32 c, f32 d, int e);
int fn_800C7F90(void);
void fn_80253EE4(const char* s, f32 v);
f64 fn_80295CF0(f64 v);
void fn_80036654(int a, int b, int c, int d);
void fn_80264034(int i);
void fn_80039030(void);
}
class P2 {
public:
    virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2C(); virtual void v30();
    virtual u32 v34();
    virtual void v38();
    virtual u32 v3C();
    virtual void v40(); virtual void v44();
    virtual u32 v48();
    virtual void v4C();
    virtual int v50(); virtual int v54(); virtual int v58(); virtual int v5C();
};
#define PAD ((P2*)lbl_804CB5B8)
struct ChS {
    void* m0; u8 pad4[0x26];
    s16 x2A; s16 x2C;
    u8 pad2E[0x16];
    s16 x44; s16 x46;
    u8 pad48[4];
    s16 x4C; s16 x4E; s16 x50; s16 x52;
    f32 f54, f58, f5C, f60, f64, f68;
    u8 pad6C[0xC];
    f32 f78, f7C, f80, f84;
    s16 x88; s16 x8A;
};
struct Node { u8 pad0[0xC]; s16 xC; s16 xE; };
#define CH ((ChS*)lbl_804CC008)

extern "C" void fn_80262744(void) {
/*P*/
    f32 k;
    int i;
    u32 pr;
    ChS* c;
    void* old;
    Node* n;
    f32 rx;
    f32 ry;
    f32 a;
    f32 b;
    f32 a2;
    f32 b2;
    f32 l;
    f32 ux;
    f32 uy;
    f32 l2;
    f32 ux2;
    f32 uy2;
    f32 sx;
    f32 sy;
    ChS* e;
    u32 rp;
    int x;
    int ox;
    int y;
    int oy;
    int dx;
    f32 m0;
    f32 m1;
    f32 k2;
    ChS* e2;
    f32 ia;
    f32 ib;
    DictState* st;
    ChS* e3;
    int cx;
    int cy;
    int nx;
    int ny;
/*E*/
    pr = PAD->v48();
    PAD->v3C();
    rp = PAD->v34();
    c = CH;
    if (c->x88 > 0) {
        c->x88 = c->x88 - 1;
        CH->f5C = fn_8017F68C(CH->f78, CH->f7C, 20 - CH->x88, 20.0f, 1);
        CH->f60 = fn_8017F68C(CH->f80, CH->f84, 20 - CH->x88, 20.0f, 1);
        CH->f64 = (CH->f5C - 0.34862384f) / 0.6513761f;
        CH->f68 = (CH->f60 - 0.3478261f) / 0.6521739f;
    }
    if ((pr & 0x800) && CH->x88 == 0) {
        if (fn_800C7F90()) return;
        fn_80083DC4(lbl_804CC000, 3);
        fn_80253EE4(lbl_80372C90 + 0x133, 0.0f);
        return;
    }
    if ((pr & 0x2000) && CH->x88 == 0) {
        if (fn_800C7F90()) return;
        if (CH->x4C == 0) {
            CH->x4C = 1;
        } else {
            CH->x4C = 0;
        }
    }
    if ((pr & 0x40) && CH->x88 == 0) {
        CH->f78 = CH->f5C;
        CH->f80 = CH->f60;
        CH->x8A = CH->x8A + 1;
        if (CH->x8A >= 4) CH->x8A = 0;
        CH->f7C = lbl_80391920[CH->x8A];
        CH->f84 = lbl_80391930[CH->x8A];
        CH->x88 = 0x14;
    }
    {
        a = PAD->v50();
        b = PAD->v54();
        l = fn_80295CF0(a * a + b * b);
        if (l >= 8.0f) {
            ux = a / l;
            uy = b / l;
            rx = a - 8.0f * ux;
            ry = b - 8.0f * uy;
        } else {
            rx = 0.0f;
            ry = rx;
            if (rp & 0x200002) rx = 50.0f;
            if (rp & 0x100001) rx = -50.0f;
            if (rp & 0x800008) ry = 50.0f;
            if (rp & 0x400004) ry = -50.0f;
        }
    }
    {
        {
            a2 = PAD->v58();
            b2 = PAD->v5C();
            l2 = fn_80295CF0(a2 * a2 + b2 * b2);
            if (l2 >= 8.0f) {
                ux2 = a2 / l2;
                uy2 = b2 / l2;
                sx = a2 - 8.0f * ux2;
                sy = b2 - 8.0f * uy2;
            } else {
                sx = 0.0f;
                sy = sx;
            }
        }
        if (rx == 0.0f && ry == 0.0f) {
            e = CH;
            k = e->f64;
            x = e->x44;
            ox = CH->x44;
            y = e->x46;
            oy = CH->x46;
            if (0.0f != k) {
                m0 = (0.2f * e->f5C) / k;
                m1 = (0.2f * e->f60) / e->f68;
            } else {
                m0 = 0.0f;
                m1 = m0;
            }
            x += (int)(sx * m0);
            y -= (int)(sy * m1);
            if (x < 0) x = 0;
            if (x > 0x470) x = 0x470;
            if (y < 0) y = 0;
            if (y > 0x348) y = 0x348;
            dx = x - ox;
            y -= oy;
            c->x2A = (f32)dx * e->f5C + (f32)c->x2A;
            c->x2C = (f32)y * CH->f60 + (f32)c->x2C;
            CH->x44 = CH->x44 + dx;
            CH->x46 = CH->x46 + y;
        }
    }
    {
        k2 = (rp & 0x1000) ? 0.3f : 0.15f;
        e2 = CH;
        ia = 1.0f / e2->f5C;
        ib = 1.0f / e2->f60;
        c->x2A = c->x2A + (int)(rx * (ia * k2));
        c->x2C = c->x2C - (int)(ry * (ib * k2));
    }
    if (c->x2A < 0x20) c->x2A = 0x20;
    if (c->x2A > 0x6D0) c->x2A = 0x6D0;
    if (c->x2C < 0) c->x2C = 0;
    if (c->x2C > 0x4B8) c->x2C = 0x4B8;
    if (c->x2A - CH->x44 <= 0x50) CH->x44 = c->x2A - 0x50;
    if (c->x2A - CH->x44 >= 0x238) CH->x44 = c->x2A - 0x238;
    if (c->x2C - CH->x46 <= 0x28) CH->x46 = c->x2C - 0x28;
    if (c->x2C - CH->x46 >= 0x12A) CH->x46 = c->x2C - 0x12A;
    if (CH->x44 < 0) CH->x44 = 0;
    if (CH->x44 > 0x470) CH->x44 = 0x470;
    if (CH->x46 < 0) CH->x46 = 0;
    if (CH->x46 > 0x348) CH->x46 = 0x348;
    {
        old = CH->m0;
        st = lbl_804CC004;
        e3 = CH;
        for (i = 0; i < st->listCount; i++) {
            n = (Node*)st->list[i];
            if (n->xC < 0) continue;
            {
                cx = (f32)c->x2A * e3->f5C - (f32)e3->x44 * e3->f64;
                cy = (f32)c->x2C * e3->f60 - (f32)e3->x46 * e3->f68;
                nx = (f32)n->xC * e3->f5C - (f32)e3->x44 * e3->f64;
                ny = (f32)n->xE * e3->f60 - (f32)e3->x46 * e3->f68;
                if (cx >= nx && (f32)cx <= (f32)nx + 68.0f * e3->f5C
                    && (f32)cy >= (f32)ny - 16.0f * e3->f60
                    && (f32)cy <= (f32)ny + 70.0f * e3->f60) {
                    fn_80036654(nx, ny, (int)(68.0f * e3->f5C), (int)(83.0f * e3->f60));
                    if (CH->x4E == 0) {
                        CH->x4E = 1;
                        CH->x52 = 0;
                    }
                    CH->m0 = n;
                    if ((pr & 0x400) && CH->x88 == 0 && fn_800C7F90() == 0) {
                        fn_80264034(i);
                        fn_80083DC4(lbl_804CC000, 2);
                        fn_80253EE4(lbl_80372C90 + 0x123, 0.0f);
                    }
                    break;
                }
            }
        }
    }
    if (i == lbl_804CC004->listCount) {
        if (CH->x4E == 1) {
            CH->x4E = 0;
            CH->x52 = 0;
        }
        CH->m0 = 0;
        fn_80039030();
    }
    if ((old == 0 && CH->m0 != 0) || (CH->m0 != 0 && old != CH->m0)) {
        fn_80253EE4(lbl_80372C90 + 0x15F, 0.0f);
    }
}
