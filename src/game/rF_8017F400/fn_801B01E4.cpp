#include "game/rF_8017F400/types.h"

#pragma auto_inline off

extern "C" {

typedef struct Names1 { const char* a[5][6]; } Names1;
typedef struct Names2 { const char* a[6][2]; } Names2;

typedef struct Lang {
    u8 pad[0x1BC8];
    u8 lang;
} Lang;

typedef struct Save {
    u8 pad[0x11];
    u8 x11;
} Save;

extern Names1 lbl_8036DA88;
extern Names2 lbl_8036DC60;
extern u8 lbl_803CAB38[];
extern Lang* fn_8024BC94(void);
extern Save* fn_80060728(void* p);
extern void fn_8023F1A0(const char* path, int a);
extern int fn_801D09F0(void);
extern int fn_8023F880(const char* path);
extern void* fn_80075D78(const char* path);
extern void fn_800068A0(void* res, const char* path);
extern void fn_80083B78(void* p);

/* picture list and shared state */
struct E { E() {} char c; };

typedef struct LData {
    void* res;  /* 0x00 */
    void* x4;   /* 0x04 */
    u8 pad8[0x18 - 8];
    void* x18;  /* 0x18 */
    int x1C;
    int x20;
    int x24;
    int x28;
    int x2C;
    u8 pad30[0x38 - 0x30];
    int x38;
    int x3C;
    int x40;
    int x44;
    int x48;
    int x4C;
    int x50;
    int x54;
    int x58;
    int x5C;
    int x60;
} LData;

extern LData* lbl_804CB9BC;
extern void* lbl_804CB9B8;
extern int lbl_804CB9C0;
extern int lbl_804CB9C4;
extern int lbl_804CB9C8;
extern void fn_801B3B3C(void* p, E e);
extern void fn_801B3E68(void* p, E e);
extern void fn_801B4280(void* p, E e);
extern void fn_801B05F8(void);

static inline const char* Name1(void) {
    Names1 t = lbl_8036DA88;
    int lang = (s8)fn_8024BC94()->lang;
    return t.a[fn_80060728(lbl_803CAB38)->x11][lang];
}

static inline const char* Name2(void) {
    Names2 t = lbl_8036DC60;
    int w = fn_801D09F0();
    return t.a[(s8)fn_8024BC94()->lang][w];
}

void fn_801B01E4(void) {
    if (!fn_8023F880(Name1()) || !fn_8023F880(Name2())) return;
    lbl_804CB9BC->x4 = fn_80075D78(Name1());
    fn_800068A0(lbl_804CB9BC, Name2());
    fn_80083B78(lbl_804CB9B8);
}


}
