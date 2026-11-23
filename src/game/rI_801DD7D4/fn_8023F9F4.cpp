/* fn_8023F9F4: state of a named file: the entry's flags when it is known and not flagged 0x40000;
   otherwise 0 when the name is in the third (pending) list or exists on disc (fn_802F63A8 >= 0),
   else 0x40000 (missing). */
#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/vobj.h"
#pragma auto_inline off
struct FE { u8 p[0x50]; volatile u32 flags; };
extern "C" {
FE* fn_802BC2A4(void*, FE*);
FE* fn_8023DCC0(const char*);
int fn_8025F4E0(FE*, const char*);
int fn_802F63A8(const char*);
extern u8 lbl_80425490[0xC];
extern u8 lbl_8042549C[0x1C];
#pragma use_lmw_stmw on
u32 fn_8023F9F4(const char* name) {
    FE* a;
    VO0N* k;
    FE* found;
    u32 r = 0x40000;
    FE* e = fn_8023DCC0(name);
    u32 f;
    if (e == NULL) f = 0x40000; else f = e->flags;
    if (!(f & 0x40000)) {
        r = f;
    } else {
        found = NULL;
        k = (VO0N*)lbl_8042549C;
        k->v08();
        for (a = fn_802BC2A4(lbl_80425490, NULL); a != NULL; a = fn_802BC2A4(lbl_80425490, a)) {
            if (fn_8025F4E0(a, name)) { found = a; break; }
        }
        k->v10();
        if (found != NULL) {
            r = 0;
        } else if (fn_802F63A8(name) >= 0) {
            r = 0;
        }
    }
    return r;
}
}
