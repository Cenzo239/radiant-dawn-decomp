#include "game/rF_8017F400/types.h"
#pragma auto_inline off
#pragma pool_strings on
extern "C" {
void StringPool(const char** p) {
    p[0] = "";
    p[1] = "%s%s %s/%s%s %s%s";
    p[2] = "%s%s %s%s %s/%s%s %s%s";
    p[3] = "%s%s %s%s %s%s %s%s %s%s";
    p[4] = "%s%s %s%s %s%s %s%s";
    p[5] = "%s%s %s%s";
    p[6] = "%s%s";
    p[7] = "%s%s %s%s %s%s";
}
typedef struct CI { u8 pad[0x30]; u16 fl; s16 dir; s16 v34; s16 wait; s16 a; char buf[1]; } CI;
extern u8 lbl_803CAB38[];
extern u8 lbl_8037A1E8[];
extern u32* fn_80060728(void*);
extern const char* fn_800CEB4C(void);
extern const char* fn_800CEC24(void);
extern const char* fn_800CECFC(void);
extern const char* fn_800CEDD4(void);
extern const char* fn_800CF05C(void);
extern const char* fn_800CF134(void);
extern const char* fn_800D0864(const char*);
extern int fn_80290DDC(char*, const char*, ...);
extern void* fn_80083B84(void*);
extern void* fn_80085708(const char*);
extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E4E4(f32, f32, f32, f32);
extern void fn_8007E7DC(int);
extern void fn_801C6D9C(char*, int, int, int);
#pragma pool_strings off
static inline const char* N(int i) {
    const char* t[] = {"MBM_STAT", "MD_NOACT", "MD_ELSE_UNIT", "MD_MAPMENU", "MP_IDO", "MD_STATUS", "MD_SAVE_HANI", "MD_FREE_HANI", "MD_RTN", "MD_DECIDE", "MD_CANCEL", "MD_HLP"};
    return fn_800D0864(t[i]);
}
#pragma pool_strings on
void fn_801912E0(CI* d) {
    u32* st = fn_80060728(lbl_803CAB38);
    const char* a = fn_800CEB4C();
    const char* b = fn_800CEC24();
    const char* c = fn_800CECFC();
    const char* d2 = fn_800CEDD4();
    const char* e = fn_800CF05C();
    const char* f = fn_800CF134();
    if (((*st >> 18) & 3) == 2) return;
    switch (lbl_803CAB38[0x92C]) {
    case 0: fn_80290DDC(d->buf, ""); break;
    case 1: fn_80290DDC(d->buf, "%s%s %s/%s%s %s%s", c,N(1),a,e,N(3),f,N(0)); break;
    case 2: fn_80290DDC(d->buf, "%s%s %s%s %s/%s%s %s%s", b,N(7),c,N(1),a,e,N(3),f,N(0)); break;
    case 3: fn_80290DDC(d->buf, "%s%s %s%s %s%s %s%s %s%s", a,N(4),c,N(1),d2,N(5),e,N(3),f,N(0)); break;
    case 4: fn_80290DDC(d->buf, "%s%s %s%s %s/%s%s %s%s", c,N(1),d2,N(5),a,e,N(3),f,N(0)); break;
    case 5:
        if (*((u8*)st + 0x11) == 2) fn_80290DDC(d->buf, "%s%s %s%s %s%s %s%s", c,N(1),d2,N(5),e,N(3),f,N(0));
        else fn_80290DDC(d->buf, "%s%s %s%s %s%s %s%s %s%s", a,N(6),c,N(1),d2,N(5),e,N(3),f,N(0));
        break;
    case 6: fn_80290DDC(d->buf, "%s%s %s%s %s%s %s%s %s%s", b,N(7),c,N(1),d2,N(5),e,N(3),f,N(0)); break;
    case 7: fn_80290DDC(d->buf, "%s%s %s%s %s%s %s%s", c,N(1),d2,N(5),e,N(3),f,N(0)); break;
    case 8: fn_80290DDC(d->buf, "%s%s %s%s %s%s %s%s", c,N(1),d2,N(5),e,N(3),f,N(0)); break;
    case 9: fn_80290DDC(d->buf, "%s%s %s%s", b,N(8),a,N(9)); break;
    case 10: fn_80290DDC(d->buf, "%s%s", b,N(8)); break;
    case 11: fn_80290DDC(d->buf, "%s%s %s%s", b,N(8),d2,N(5)); break;
    case 12: fn_80290DDC(d->buf, "%s%s", a,N(9)); break;
    case 13: fn_80290DDC(d->buf, ""); break;
    case 14: fn_80290DDC(d->buf, "%s%s", d2,N(5)); break;
    case 15: fn_80290DDC(d->buf, "%s%s %s%s %s%s", b,N(10),a,N(9),d2,N(11)); break;
    case 16: fn_80290DDC(d->buf, "%s%s %s%s", b,N(10),a,N(9)); break;
    case 17: fn_80290DDC(d->buf, "%s%s %s%s %s%s", b,N(10),a,N(9),d2,N(5)); break;
    case 18: fn_80290DDC(d->buf, "%s%s %s%s", b,N(10),a,N(9)); break;
    }
    if (d->wait <= 0) {
        switch (d->dir) {
        case 0:
            d->v34++;
            if (d->v34 > 8) d->v34 = 8;
            break;
        case 1:
            d->v34--;
            if (d->v34 < 0) d->v34 = 0;
            break;
        }
        if (d->v34 != 0 || (fn_80083B84(lbl_8037A1E8) != 0 && fn_80085708("E_Event") == 0) || (d->fl & 1)) {
            d->a += 0x19;
            if (d->a > 0xFF) d->a = 0xFF;
        } else {
            d->a -= 0x19;
            if (d->a < 0) d->a = 0;
        }
    } else {
        d->wait--;
    }
    if (d->a > 0) {
        fn_8007E154();
        fn_8007E4E4(0.0f, 0.0f, 300.0f, 1.0f);
        fn_8007E7DC((u8)d->a);
        fn_8007E164();
        fn_801C6D9C(d->buf, 0xFF, 0xFF, 0);
        fn_8007E154();
        fn_8007E7DC(0xFF);
        fn_8007E164();
    }
}
}
