#include "game/rI_801DD7D4/types.h"
#pragma auto_inline off
#pragma use_lmw_stmw on
#pragma pool_strings on
extern "C" {
void* fn_801E7A28(void*);
void* fn_801E5640(void*, int, int);
void* fn_8012E3A4(void*);
u8* fn_801E041C(const char*, const char*);
u8* fn_800D5448(void*, void*, int);
s8 fn_8012E9B4(void*, void*);
int fn_8012EA2C(void*, int);
u8 fn_8012E8BC(void*, int);
void* fn_80085EF8(int);
void fn_800D56E8(void*);
struct WV { virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c(); virtual void v50(); virtual void v54(); virtual void v58(int); };
struct H1 { u8 p[0x44]; void* x44; void* x48; };
/* Places the earlier strings of the file's pool so later offsets are right. Not original code here. */
void dummy1(const char** p) {
    *p = "MESS_SUPPORT_ASK_SELUNIT";
    *p = "";
    *p = "MESS_SUPPORT_HELP00";
    *p = "MH_SUPPORT_NOSUPPORT_NG";
    *p = "SFX_SYS_SELECT1";
    *p = "SFX_SYS_CANCEL1";
    *p = "MESS_SUPPORT_ASK_TGTUNIT";
    *p = "MESS_SUPPORT_HELP01";
    *p = "MH_SUPPORT_NOUNIT_NG";
    *p = "MH_SUPPORT_NOREL_NG";
}
static inline u8* mkD(const char* a, const char* b) { return fn_801E041C(a, b); }
static inline void setHelp(void* o, const char* const& s) {
    u8* w = (u8*)fn_801E5640(o, -0x1000, 0);
    if (w != NULL) *(const char**)(w + 0x64) = s;
}
void fn_80215688(H1* o) {
    void* c;
    void* d;
    u8* t;
    u8* m;
    c = fn_801E7A28(o->x44);
    d = fn_801E7A28(o->x48);
    t = (u8*)fn_801E5640(o, 0x80, 0);
    if (fn_8012E3A4(c) == d) {
        *(const char**)(t + 0x40) = "MESS_SUPPORT_ASK_TGTUNIT";
        u8* b = mkD("MMM_SUP_UP", "MMM_SUP_DEL");
        *(s16*)(b + 0xa) = 0x1b;
        b[0x24] = 1;
        *(s16*)(b + 0xc) = 0xe0;
        *(s16*)(b + 8) = 0x168;
        m = fn_800D5448(b, o, 0);
        s8 k = fn_8012E9B4(c, d);
        if (fn_8012EA2C(c, k) == 0 || fn_8012E8BC(c, k) == 3) {
            ((WV*)*(void**)((u8*)fn_80085EF8(m[0x40]) + 0x34))->v58(2);
            ((WV*)*(void**)((u8*)fn_80085EF8(m[0x41]) + 0x34))->v58(1);
            fn_800D56E8(m);
        }
    } else {
        *(const char**)(t + 0x40) = "MESS_SUPPORT_ASK_ON";
        u8* b = fn_801E041C(0, 0);
        *(s16*)(b + 8) = 0x180;
        *(s16*)(b + 0xa) = 0x1b;
        b[0x24] = 1;
        fn_800D5448(b, o, 0);
    }
    setHelp(o, "MESS_COMMON_HELP00");
}
}
