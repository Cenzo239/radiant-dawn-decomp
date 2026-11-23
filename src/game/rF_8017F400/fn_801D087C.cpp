#include "game/rF_8017F400/types.h"
#pragma auto_inline off
extern "C" {
extern int OSDisableInterrupts(void);
extern int OSRestoreInterrupts(int);
extern u8 lbl_80380F00[];
extern u8* lbl_804CA900;
extern void* fn_8007E4C4(void*);
extern void fn_80312344(void*, void*);
extern void fn_8007E478(void*, f32);
struct Lock {
    void* vt;
    int lvl;
    Lock() { vt = lbl_80380F00; lvl = OSDisableInterrupts(); }
    ~Lock() { vt = lbl_80380F00; OSRestoreInterrupts(lvl); }
};
void fn_801D087C(void) {
    Lock l;
    u8* p = lbl_804CA900 - 0x34;
    lbl_804CA900 = p;
    fn_80312344(fn_8007E4C4(p + 0x30), p);
}
void fn_801D08E4(void) {
    Lock l;
    u8* p = lbl_804CA900;
    lbl_804CA900 = p + 0x34;
    fn_8007E478(p, *(f32*)(p + 0x30));
}
}
