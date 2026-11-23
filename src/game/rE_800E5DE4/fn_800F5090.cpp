#include "game/rE_800E5DE4/mapunit.h"
#pragma auto_inline off

extern "C" {
extern void* lbl_804CA5A8;
extern void* fn_8012759C(void* u);
extern int fn_800F002C(void*, int);
extern int fn_80007630(void*, const char*);
extern int fn_8011B77C(void*, void*);

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

static inline void AddJ(MapUnit* m, void* mdl, const char* s) {
    int k = fn_80007630(mdl, s);
    if (k >= 0) {
        int i;
        for (i = 0; i < 10; i++) {
            if (m->joints[i] < 0) break;
            if (k == m->joints[i]) return;
        }
        m->joints[m->nJoints++] = k;
    }
}
static inline void ClrF(void* mdl, u32 f) {
    u32* q = (u32*)mdl;
    if (q) *q &= ~f;
}
void fn_800F5090(MapUnit* m) {
    if (m->flags & 2) {
        int w;
        void* mdl = m->model;
        w = m->unkD8 >= 0 ? m->unkD8 : fn_800F002C(fn_8012759C(m), 0);
        {
            int i;
            m->nJoints = 0;
            for (i = 0; i < 10; i++) m->joints[i] = -1;
        }
        if (w != 1) AddJ(m, mdl, "sw");
        if (w != 2) AddJ(m, mdl, "sp");
        if (w != 3) AddJ(m, mdl, "ja");
        if (w != 4) AddJ(m, mdl, "ax");
        if (w != 5) AddJ(m, mdl, "ha");
        if (w != 6) {
            AddJ(m, mdl, "bw");
            AddJ(m, mdl, "ar");
        }
        if (w != 7) AddJ(m, mdl, "rd");
        if (w != 8) AddJ(m, mdl, "bg");
        if (m->flags & 0x800) {
            AddJ(m, mdl, "sw");
            AddJ(m, mdl, "sp");
            AddJ(m, mdl, "ja");
            AddJ(m, mdl, "ax");
            AddJ(m, mdl, "ha");
            AddJ(m, mdl, "bw");
            AddJ(m, mdl, "ar");
            AddJ(m, mdl, "rd");
            AddJ(m, mdl, "bg");
            AddJ(m, mdl, "ex");
        }
        if (fn_8011B77C((u8*)m + 0x12c, lbl_804CA5A8)) {
            AddJ(m, mdl, "long");
        } else {
            AddJ(m, mdl, "short");
        }
        ClrF(m->model, 0x10);
        ClrF(m->model, 8);
        ClrF(m->model, 0x20);
        m->flags &= ~0xE010;
    }
}
}
