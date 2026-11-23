#include "game/rE_800E5DE4/mapunit.h"
#pragma auto_inline off

extern "C" {
extern void* fn_80007F3C(void*);
#if TARGET_PC
extern FE10_PROTO void fn_80014E24(void*, const char*, void*, p32arg);
#else
extern void fn_80014E24(void*, const char*, void*, int);
#endif
extern void fn_80014F64(void*, const char*, void*);
#if TARGET_PC
extern FE10_PROTO struct GEntry20 * fn_80008110(void*, const char*);
#else
extern int fn_80008110(void*, const char*);
#endif
extern void fn_800FB9D0(void* m, void* b, void* a, void* t);
extern void fn_800FBC90(void* m, void* b, void* c, void* d);
extern void* fn_800F0AF4(int);
extern void* fn_800F0B04(const char*);
extern char* fn_800F416C(MapUnit*);
extern void* fn_8012759C(MapUnit*);
extern int fn_800F002C(void*, int);
extern void* fn_800F0CBC(void*, int, int);
#if TARGET_PC
extern FE10_PROTO ptr32<void> fn_8023F8EC(void*);
#else
extern void* fn_8023F8EC(void*);
#endif

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

static inline void* Data(MapUnit* m) {
    char* s;
    void* r;
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
#pragma use_lmw_stmw on
void fn_800F634C(MapUnit* m) {
    Model* mdl = (Model*)m->model;
    void* a = fn_80007F3C(mdl);
    void* p;
    fn_80014E24(a, 0, fn_800FB9D0, 1);
    if (fn_80008110(mdl, "m_haze")) {
        fn_80014E24(a, "m_haze1", fn_800FBC90, 1);
        fn_80014E24(a, "m_haze2", fn_800FBC90, 1);
        fn_80014E24(a, "m_light1", fn_800FBC90, 1);
        fn_80014F64(a, "m_haze1", fn_800FB9D0);
        fn_80014F64(a, "m_haze2", fn_800FB9D0);
        fn_80014F64(a, "m_light1", fn_800FB9D0);
        {void* b=0;
        p = fn_800F0CBC(Data(m), Weapon(m), 0);
        if (p) {
            b = fn_8023F8EC(p);
        }
        mdl->unk84 = b;}
    }
    mdl->owner = m;
}
#pragma use_lmw_stmw off
}
