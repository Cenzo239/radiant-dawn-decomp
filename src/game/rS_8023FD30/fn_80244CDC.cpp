#include "game/rS_8023FD30/types.h"
extern "C" {
u8 fn_80325918(void);
u16 fn_8031C044(void);
static inline u8 lang() { return fn_8031C044() == 1; }
s8 fn_80244CDC(void) {
    int r;
    switch (fn_80325918()) {
    case 0:
        r = (fn_8031C044() != 1);
        break;
    case 1:
        r = 1;
        break;
    case 2:
        r = 2;
        break;
    case 3:
        r = 3;
        break;
    case 4:
        r = 4;
        break;
    case 5:
        r = 5;
        break;
    case 6:
        r = 6;
        break;
    default:
        r = (fn_8031C044() != 1);
        break;
    }
    return (s8)r;
}
}
