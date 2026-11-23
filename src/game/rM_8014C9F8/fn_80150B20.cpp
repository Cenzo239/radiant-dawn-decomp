/* Talk window: set the text colour (colour passed by value). 80150B20. */
#include "game/rM_8014C9F8/win.h"

extern "C" {

void fn_80150B20(Win* w, Color c) {
    w->col = c;
    c.a = 255;
}

}
