/* Portrait id chosen by character and transform skills, 801246A4 and 8012486C. */
#include "game/rH_80112B48/unit.h"
#pragma auto_inline off
extern "C" {
extern void* fn_8010B1D8(const char*);
extern int fn_8011B77C(void*, void*);
extern char* fn_80118F8C(Person*);
extern void* lbl_804CA4E4;
extern void* lbl_804CA4E0;
extern void* lbl_804CA5A8;
#define HAS(u, s) fn_8011B77C((u)->skills, s)
#pragma pool_strings on
/* Fills the first pool slot; the original user of "IID_TORCH" is elsewhere. */
const char* dummyS() { return "IID_TORCH"; }
const char* fn_801246A4(Unit* u) {
    const char* r;
    Person* p;
    r = 0;
    p = u->person;
    if (p == fn_8010B1D8("PID_IKE")) {
        if (HAS(u, lbl_804CA4E4)) {
            r = "FID_IKE2";
        } else if (HAS(u, lbl_804CA4E0)) {
            r = *(char**)((u8*)u->person + 0x10);
        }
    } else {
        p = u->person;
        if (p == fn_8010B1D8("PID_MICAIAH")) {
            if (HAS(u, lbl_804CA4E4)) {
                r = "FID_MICAIAH3";
            } else if (HAS(u, lbl_804CA4E0)) {
                r = "FID_MICAIAH2";
            } else {
                r = *(char**)((u8*)u->person + 0x10);
            }
        } else {
            p = u->person;
            if (p == fn_8010B1D8("PID_SOTHE")) {
                if (HAS(u, lbl_804CA4E4)) {
                    r = "FID_SOTHE2";
                } else if (HAS(u, lbl_804CA4E0)) {
                    r = *(char**)((u8*)u->person + 0x10);
                }
            } else {
                p = u->person;
                if (p == fn_8010B1D8("PID_LUCHINO")) {
                    if (HAS(u, lbl_804CA5A8)) {
                        r = "FID_LUCHINO2";
                    } else {
                        r = *(char**)((u8*)u->person + 0x10);
                    }
                } else {
                    p = u->person;
                    if (p == fn_8010B1D8("PID_MEG")) {
                        if (HAS(u, lbl_804CA5A8)) {
                            r = "FID_MEG2";
                        } else {
                            r = *(char**)((u8*)u->person + 0x10);
                        }
                    } else {
                        r = *(char**)((u8*)u->person + 0x10);
                    }
                }
            }
        }
    }
    return r;
}
const char* fn_8012486C(Unit* u) {
    const char* r;
    Person* p;
    r = 0;
    p = u->person;
    if (p == fn_8010B1D8("PID_IKE")) {
        if (HAS(u, lbl_804CA4E4)) {
            r = "FID_L_IKE2";
        } else if (HAS(u, lbl_804CA4E0)) {
            r = fn_80118F8C(u->person);
        }
    } else {
        p = u->person;
        if (p == fn_8010B1D8("PID_MICAIAH")) {
            if (HAS(u, lbl_804CA4E4)) {
                r = "FID_L_MICAIAH3";
            } else if (HAS(u, lbl_804CA4E0)) {
                r = "FID_L_MICAIAH2";
            } else {
                r = fn_80118F8C(u->person);
            }
        } else {
            p = u->person;
            if (p == fn_8010B1D8("PID_SOTHE")) {
                if (HAS(u, lbl_804CA4E4)) {
                    r = "FID_L_SOTHE2";
                } else if (HAS(u, lbl_804CA4E0)) {
                    r = fn_80118F8C(u->person);
                }
            } else {
                p = u->person;
                if (p == fn_8010B1D8("PID_LUCHINO")) {
                    if (HAS(u, lbl_804CA5A8)) {
                        r = "FID_L_LUCHINO2";
                    } else {
                        r = fn_80118F8C(u->person);
                    }
                } else {
                    p = u->person;
                    if (p == fn_8010B1D8("PID_MEG")) {
                        if (HAS(u, lbl_804CA5A8)) {
                            r = "FID_L_MEG2";
                        } else {
                            r = fn_80118F8C(u->person);
                        }
                    } else {
                        r = fn_80118F8C(u->person);
                    }
                }
            }
        }
    }
    return r;
}
}
