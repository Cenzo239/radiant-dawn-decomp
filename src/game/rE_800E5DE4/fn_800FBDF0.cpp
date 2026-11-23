/* fn_800F491C (17 of 158 words), fn_800F4B94 (7 of 157), fn_800F4E08 (15 of 160): registers only. These three are the same inline, which fn_800F6AEC also expands.
 * The original gives the Pick locals r30/r29 (Data1 r30); this version gives them the same register as k. */
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
extern int fn_8011B77C(void*, void*);
extern void* lbl_804CA58C;

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
#define SETANIM(m, k) \
    if (!(m->flags & 2)) return; \
    if (k < 0) k = Pick(m, v, ok, s1, r1); \
    m->unkDC = (UnitRef*)Data(m, s2, r2); \
    q = (u8*)m + 0x28; \
    e = Data(m, s3, r3); \
    p = fn_800F0CBC(e, Weapon(m), k); \
    if (p) { \
        fn_80008B50(q); \
        fn_80008F6C(q, p); \
        m->unkC7 = k; \
        fn_800F5090(m); \
    }

void fn_800FBDF0(MapUnit* m) {
    /*P*/
    int k;
    int v;
    int ok;
    char* s1;
    CData* r1;
    char* s2;
    CData* r2;
    char* s3;
    CData* r3;
    void* q;
    void* p;
    CData* e;
    /*E*/
    if (fn_8011B77C((u8*)m + 0x12c, lbl_804CA58C)) {
        k = fn_800F0994("\x8e""\x80""\x96""S");
        SETANIM(m, k)
    } else {
        m->flags |= 0x20;
    }
}
}
