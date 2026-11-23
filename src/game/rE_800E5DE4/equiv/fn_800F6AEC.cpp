/* fn_800F6AEC: functionally equal (regs, 17 of 585 words differ in registers only). From wip/fn_800F6AEC_r14.cpp with the fn_8000866C argument corrected to -1.0f. */
/* NEAR MISS: fn_800F6AEC, registers only: k and w want r28, the third Data result r27. The checker score also counts the pool label differences. See NOTES.md round 14. */
/* fn_800F6AEC: same length and layout, 48 of 585 words differ in registers only. Everything else is right.
 * fl is r27 (r26 in the original), w is r26 (r28), and k/Data/Pick locals inside SetAnim take r26 instead of r27/r28. Declaration order of w has no effect. */
#include "game/rE_800E5DE4/mapunit.h"
#pragma auto_inline off

typedef struct AnimInfo { u8 pad[0x10]; void* v10; } AnimInfo;
typedef struct CF2 { u8 pad[0x10]; u8 b10; u8 b11; } CF2;
typedef struct CData { u8 pad[0x10]; CF2* v10; } CData;

extern "C" {
extern CData* fn_800F0AF4(int);
extern CData* fn_800F0B04(const char*);
extern char* fn_800F416C(MapUnit*);
extern void* fn_8012759C(MapUnit*);
extern int fn_800F002C(void*, int);
extern void fn_80006E94(void*);
extern char* fn_800F0B08(void*, int);
extern char* fn_800F0C18(void*);
extern char* fn_800F0BC8(void*);
extern void* fn_8023F1A4(char*, int);
extern void fn_80009090(void*, char*);
extern void fn_80009030(void*, char*);
extern char* fn_800F47FC(MapUnit*, u8);
extern void fn_800092D4(void*, char*, int);
extern void fn_80006F20(void*);
extern s16 fn_801237EC(MapUnit*);
extern int fn_801092C4(void*);
extern int fn_800F130C(void*, int, int);
extern void* fn_800F0CBC(void*, int, int);
extern void fn_80008B50(void*);
extern void fn_80008F6C(void*, void*);
extern void fn_800F5090(MapUnit*);
extern int fn_800F0994(const char*);
extern AnimInfo* fn_80007F10(void*);
extern void fn_8000866C(void*, f32);
extern int fn_80007630(void*, const char*);
extern void fn_80007ABC(void*, int);
extern void fn_800F634C(MapUnit*);
extern void fn_80008F20(void*, u8);
extern void fn_80008F54(void*, int);
extern void fn_80008F5C(void*, u8);

#pragma pool_strings on
void pool_7ba4() {
    const char* volatile s;
    s = "zmap/common.tpl"; /* 0x0 */
    s = ""; /* 0x10 */
    s = "AID_DUMMY"; /* 0x11 */
    s = "sw"; /* 0x1b */
    s = "sp"; /* 0x1e */
    s = "ja"; /* 0x21 */
    s = "ax"; /* 0x24 */
    s = "ha"; /* 0x27 */
    s = "bw"; /* 0x2a */
    s = "ar"; /* 0x2d */
    s = "rd"; /* 0x30 */
    s = "bg"; /* 0x33 */
    s = "ex"; /* 0x36 */
    s = "long"; /* 0x39 */
    s = "short"; /* 0x3e */
    s = "m_haze"; /* 0x44 */
    s = "m_haze1"; /* 0x4b */
    s = "m_haze2"; /* 0x53 */
    s = "m_light1"; /* 0x5b */
    s = "\x8d""\\\x82""\xa6"""; /* 0x64 */
    s = "\x8e""\x80""\x96""S"; /* 0x69 */
    s = "root"; /* 0x6e */
    s = ""; /* 0x73 */
}

static inline CData* Data(MapUnit* m, char*& s, CData*& r) {
    if (m->unkDA >= 0) {
        return fn_800F0AF4(m->unkDA);
    }
    s = fn_800F416C(m);
    if (s == 0 || *s == 0) {
        return fn_800F0B04("AID_DUMMY");
    }
    r = fn_800F0B04(s);
    if (r == 0) {
        r = fn_800F0B04("AID_DUMMY");
    }
    return r;
}
static inline int Weapon(MapUnit* m) {
    return m->unkD8 >= 0 ? m->unkD8 : fn_800F002C(fn_8012759C(m), 0);
}
static inline int Pick(MapUnit* m, int& v, int& ok, char*& s, CData*& r) {
    v = m->unk114;
    if (v * 100 < fn_801237EC(m) * 20) {
        ok = 1;
    } else {
        ok = fn_801092C4(m->unk110);
    }
    if (ok && fn_800F130C(Data(m, s, r), Weapon(m), 2)) {
        return 2;
    }
    return 0;
}
#define SA(k, n, PK) \
    if (m->flags & 2) { \
        PK; \
        m->unkDC = (UnitRef*)Data(m, sb##n, rb##n); \
        q##n = (u8*)m + 0x28; \
        e##n = Data(m, sc##n, rc##n); \
        p##n = fn_800F0CBC(e##n, Weapon(m), k); \
        if (p##n) { \
            fn_80008B50(q##n); \
            fn_80008F6C(q##n, p##n); \
            m->unkC7 = k; \
            fn_800F5090(m); \
        } \
    }
#define PKN(k, n) if (k < 0) k = Pick(m, v##n, ok##n, sa##n, ra##n)
#pragma pool_strings off
#pragma pool_strings on
void fn_800F6AEC(MapUnit* m, u32 fl) {
    /*P*/
    CData* d;
    void* mdl;
    u8 w;
    int k1;
    int k2;
    int k3;
    int i;
    CData* r0;
    char* s0;
    int v1;
    int ok1;
    char* sa1;
    CData* ra1;
    char* sb1;
    CData* rb1;
    char* sc1;
    CData* rc1;
    void* q1;
    const char** q;
    void* p1;
    CData* e1;
    int v2;
    int ok2;
    char* sa2;
    CData* ra2;
    char* sb2;
    CData* rb2;
    char* sc2;
    CData* rc2;
    void* q2;
    void* p2;
    CData* e2;
    int v3;
    int ok3;
    char* sa3;
    CData* ra3;
    char* sb3;
    CData* rb3;
    char* sc3;
    CData* rc3;
    void* q3;
    void* p3;
    CData* e3;
    void* qq;
    AnimInfo* aa;
/*E*/
    if (*(volatile u16*)&m->flags & 2) return;
    m->flags = (m->flags & 0xFFFE) | 2;
    {
        d = Data(m, s0, r0);
        mdl = m->model;
        m->unkDC = (UnitRef*)d;
        fl |= 0x40;
        w = m->unkF4->unk8;
        fn_80006E94(mdl);
        m->unkE0 = fn_8023F1A4(fn_800F0B08(d, -1), fl);
        fn_80009090(mdl, fn_800F0C18(d));
        fn_80009030(mdl, fn_800F0BC8(d));
        fn_800092D4(mdl, fn_800F47FC(m, w), fl);
        fn_80006F20(mdl);
        if (m->flags & 0x10) {
            if (d->v10->b10 & 8) {
                k1 = fn_800F0994("\x8d""\\\x82""\xa6""");
                SA(k1, 1, PKN(k1, 1))
            } else {
                k2 = fn_800F0994("\x8e""\x80""\x96""S");
                SA(k2, 2, PKN(k2, 2))
                if (m->flags & 2) {
                    qq = (u8*)m + 0x28;
                    aa = fn_80007F10(qq);
                    if (aa && aa->v10 == 0) fn_8000866C(qq, -1.0f);
                }
            }
            m->flags &= ~0x10;
        } else {
            SA(k3, 3, k3 = Pick(m, v3, ok3, sa3, ra3))
        }
        *(u32*)mdl |= 0x2040;
        { f32 z = 0.0f; m->offX = z; m->offY = z; m->offZ = z; }
        m->unkC6 = d->v10->b11;
        m->unkC8 = fn_80007630(mdl, "root");
        {
#pragma pool_strings off
            const char* tbl[] = {"s1", "s2", "s3", "s4"};
#pragma pool_strings on
            q = tbl;
            for (i = 0; i < 4; i++, q++) {
                m->joints[10 + i] = fn_80007630(mdl, *q);
            }
        }
        fn_80007ABC(mdl, 1);
        fn_800F634C(m);
        fn_80008F20(m->model, 0);
        fn_80008F54(mdl, 0x8E);
        fn_80008F5C(m->model, 1);
    }
}
}
