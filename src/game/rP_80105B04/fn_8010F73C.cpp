#include "game/rP_80105B04/rp.h"
/* String-to-enum tables over strcmp (fn_80291188). */
extern "C" {
extern char lbl_803680E8[];
int fn_80291188(const char* a, const char* b);

int fn_8010F73C(const char* s) {
    char* t = lbl_803680E8;
    if (fn_80291188(s, t + 0x3f) == 0) return 0x0;
    if (fn_80291188(s, t + 0x45) == 0) return 0x1;
    if (fn_80291188(s, t + 0x4b) == 0) return 0x2;
    if (fn_80291188(s, t + 0x4f) == 0) return 0x3;
    if (fn_80291188(s, t + 0x53) == 0) return 0x4;
    if (fn_80291188(s, t + 0x59) == 0) return 0x5;
    if (fn_80291188(s, t + 0x5e) == 0) return 0x6;
    if (fn_80291188(s, t + 0x64) == 0) return 0x7;
    if (fn_80291188(s, t + 0x6c) == 0) return 0x8;
    if (fn_80291188(s, t + 0x71) == 0) return 0x9;
    if (fn_80291188(s, t + 0x77) == 0) return 0xa;
    if (fn_80291188(s, t + 0x7c) == 0) return 0xb;
    if (fn_80291188(s, t + 0x80) == 0) return 0xd;
    if (fn_80291188(s, t + 0x89) == 0) return 0xe;
    if (fn_80291188(s, t + 0x8e) == 0) return 0xf;
    if (fn_80291188(s, t + 0x92) == 0) return 0x10;
    if (fn_80291188(s, t + 0x97) == 0) return 0x11;
    if (fn_80291188(s, t + 0xa1) == 0) return 0x12;
    return fn_80291188(s, t + 0xa9) ? 0 : 5;
}
int fn_801109FC(const char* s) {
    char* t;
    if (s == 0) return 0x8000;
    t = lbl_803680E8;
    if (fn_80291188(s, t + 0x537) == 0) return 0x1;
    if (fn_80291188(s, t + 0x541) == 0) return 0x2;
    if (fn_80291188(s, t + 0x54a) == 0) return 0x4;
    if (fn_80291188(s, t + 0x556) == 0) return 0x8;
    if (fn_80291188(s, t + 0x561) == 0) return 0x10;
    if (fn_80291188(s, t + 0x56c) == 0) return 0x20;
    if (fn_80291188(s, t + 0x577) == 0) return 0x40;
    if (fn_80291188(s, t + 0x582) == 0) return 0x80;
    if (fn_80291188(s, t + 0x58e) == 0) return 0x100;
    if (fn_80291188(s, t + 0x598) == 0) return 0x200;
    if (fn_80291188(s, t + 0x5a3) == 0) return 0x400;
    if (fn_80291188(s, t + 0x5ad) == 0) return 0x800;
    return fn_80291188(s, t + 0x5b7) ? 0x8000 : 0x1000;
}
int fn_801112A8(const char* s);
}
