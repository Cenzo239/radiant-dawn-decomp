#include "game/rC2_8005259C/types.h"
#pragma use_lmw_stmw on
struct BgObj { u8 pad[0x44]; void* a44; void* a48; };
extern "C" {
extern char lbl_80361F9C[316];
extern u8 lbl_803CAB38[];
struct Opt58 { u8 pad[0x11]; u8 b11; };
Opt58* fn_80060728(void*);
void fn_80083B78(void*);
void* fn_801D5DC4(void);
int fn_8023F880(const char* s);
int fn_801D5F7C(void);
void fn_801D5DFC(void);
void* fn_80075FB4(const void* p, int n);
char* strcpy(char* d, const char* s);
}

extern "C" void fn_80058848(BgObj* o) {
    char buf[0x40];
    switch (fn_80060728(lbl_803CAB38)->b11) {
    case 0:
    case 3:
        strcpy(buf, lbl_80361F9C + 0x26);
        break;
    case 1:
        strcpy(buf, lbl_80361F9C + 0x3a);
        break;
    case 2:
        strcpy(buf, lbl_80361F9C + 0x4e);
        break;
    }
    if (fn_8023F880((const char*)fn_801D5DC4()) && fn_801D5F7C() && fn_8023F880(buf)) {
    } else {
        return;
    }
    fn_801D5DFC();
    o->a44 = fn_80075FB4(fn_801D5DC4(), 0x80);
    o->a48 = fn_80075FB4(buf, 0x80);
    fn_80083B78(o);
}
