/* Button prompt strings: each function picks a "#Pxxx" glyph sequence for the
 * attached controller type. fn_8007A85C(1) distinguishes the two Wii layouts. */
#include "game/rK_800CF8BC/types.h"

#pragma pool_strings on

extern int lbl_804CA478;
extern "C" int fn_8007A85C(int);

#define PROMPT(name, a, b, c, d)                                               \
    extern "C" const char* name() {                                            \
        int t = lbl_804CB5B8->v18();                                           \
        switch (t) {                                                           \
        case 4:                                                                \
        case 5:                                                                \
            break;                                                             \
        default:                                                               \
            lbl_804CA478 = lbl_804CB5B8->v18();                                \
        }                                                                      \
        switch (lbl_804CA478) {                                                \
        case 0:                                                                \
        case 1:                                                                \
            return fn_8007A85C(1) ? a : b;                                     \
        case 3:                                                                \
            return c;                                                          \
        case 2:                                                                \
        case 4:                                                                \
        case 5:                                                                \
            return d;                                                          \
        default:                                                               \
            return " ";                                                        \
        }                                                                      \
    }

#define PROMPT1(name, a, c, d)                                                 \
    extern "C" const char* name() {                                            \
        int t = lbl_804CB5B8->v18();                                           \
        switch (t) {                                                           \
        case 4:                                                                \
        case 5:                                                                \
            break;                                                             \
        default:                                                               \
            lbl_804CA478 = lbl_804CB5B8->v18();                                \
        }                                                                      \
        switch (lbl_804CA478) {                                                \
        case 0:                                                                \
        case 1:                                                                \
            fn_8007A85C(1);                                                    \
            return a;                                                          \
        case 3:                                                                \
            return c;                                                          \
        case 2:                                                                \
        case 4:                                                                \
        case 5:                                                                \
            return d;                                                          \
        default:                                                               \
            return " ";                                                        \
        }                                                                      \
    }

PROMPT(fn_800CEB4C, "#P063", "#P060", "#P020", "#P040")
PROMPT(fn_800CEC24, "#P062", "#P061", "#P021", "#P041")
PROMPT(fn_800CECFC, "#P061+#P063", "#P06A", "#P022", "#P042")
PROMPT(fn_800CEDD4, "#P061+#P062", "#P073", "#P023", "#P043")
PROMPT(fn_800CEEAC, "#P061+#P060", "#P063+#P060", "#P024#P025", "#P044#P045")
PROMPT(fn_800CEF84, "#P073", "#P063+#P061", "#P026#P027", "#P046#P047")
PROMPT(fn_800CF05C, "#P060", "#P063+#P062", "#P028#P029", "#P049")
PROMPT(fn_800CF134, "#P06A", "#P062", "#P02A", "#P04A")
PROMPT1(fn_800CF20C, "#P06B", "#P02B", "#P04B")
PROMPT1(fn_800CF2D8, "#P06B", "#P02C", "#P04C")
PROMPT1(fn_800CF3A4, "#P075", "#P02D", "#P04D")
PROMPT1(fn_800CF470, "#P076", "#P02E", "#P04E")
PROMPT1(fn_800CF53C, "#P077", "#P02F", "#P04F")
PROMPT(fn_800CF608, "#P061+#P06B", "#P063+#P06B", "#P030", "#P050")
PROMPT(fn_800CF6E0, "#P061+#P075", "#P063+#P075", "#P031", "#P051")
PROMPT(fn_800CF7B8, "#P061+#P076", "#P063+#P076", "#P030", "#P052")
