/* fn_801B1DF8: register five script commands with the 4-word state at lbl_803CAB38+0xF0 saved and restored around them.
 * Save (vtable lbl_8037F7E0 stored by hand, empty destructor keeps it in memory) and Refs stand in for the real saver class. */
#include "game/rF_8017F400/types.h"
#pragma use_lmw_stmw on
extern "C" {
typedef struct GSt { u8 pad[0xF0]; int v[4]; } GSt;
extern GSt lbl_803CAB38;
extern u8 lbl_8037F7E0[];
extern char lbl_8036DCE0[];
extern void* fn_800C3558(void);
extern void fn_801D0C88(void*, const char*);
struct Refs { int* a; int* b; int* c; int* d; };
struct Save {
    void* vt;
    int v[4];
    Save() { v[0] = 0; v[1] = 0; v[2] = 0; v[3] = 0; }
    ~Save() {}
};
static inline void Reg(const char* s) { fn_801D0C88(fn_800C3558(), s); }
void fn_801B1DF8(void) {
    Refs q; q.a = lbl_803CAB38.v; q.b = q.a + 1; q.c = q.a + 2; q.d = q.a + 3;
    Save s;
    s.vt = lbl_8037F7E0;
    s.v[0] = *q.a; s.v[1] = *q.b; s.v[2] = *q.c; s.v[3] = *q.d;
    Reg(lbl_8036DCE0 + 0xD1);
    Reg(lbl_8036DCE0 + 0xD8);
    Reg(lbl_8036DCE0 + 0xE0);
    Reg(lbl_8036DCE0 + 0xEA);
    Reg(lbl_8036DCE0 + 0xF9);
    *q.a = s.v[0]; *q.b = s.v[1]; *q.c = s.v[2]; *q.d = s.v[3];
}
}
