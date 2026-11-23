/* Unit pair tables read from a data file, 8011F1A8, 8011F2F0. */
#include "game/rH_80112B48/unit.h"
#pragma auto_inline off

extern "C" {
extern int fn_8011B77C(void*, void*);
extern char lbl_80369010[];
extern void* lbl_804CA588;
extern u8 lbl_80380940[];
extern char* strcpy(char*, const char*);
extern char* fn_8029113C(char*, const char*, u32);
extern char* fn_80118DE8(Person*);
extern void* fn_80076F54(const char*);
extern void fn_80078E24(void*);

struct Rd {
    void* buf;
    u8 pad4[8];
    u8 owned;
    u8 padD[3];
    void* vt;
    u8 pad14[4];
    ~Rd() {
        vt = lbl_80380940;
        if (owned) {
            fn_80078E24(buf);
            buf = 0;
            owned = 0;
        }
    }
};
struct Rec {
    void* p;
    u8 b4;
    u8 pad5[3];
};
extern void fn_8008A48C(Rd*, void*);
extern u32 fn_8008A1DC(Rd*);
extern void fn_8008A43C(Rd*, u32, Rec*);

BOOL fn_8011F1A8(Unit* a, Unit* b) {
    char name[0x40];
    void* p;
    if (fn_8011B77C(b->skills, lbl_804CA588)) {
        return 0;
    }
    strcpy(name, lbl_80369010 + 0x16);
    fn_8029113C(name, fn_80118DE8(a->person), 0x39);
    name[0x3f] = 0;
    p = fn_80076F54(name);
    if (p) {
        Rd r;
        Rec rec;
        fn_8008A48C(&r, p);
        fn_8008A1DC(&r);
        fn_8008A43C(&r, 8, &rec);
        while (rec.p) {
            if (b->person == rec.p) {
                return 0;
            }
            fn_8008A43C(&r, 8, &rec);
        }
    }
    return 1;
}

BOOL fn_8011F2F0(Unit* a, Unit* b) {
    char name[0x40];
    void* p;
    strcpy(name, lbl_80369010 + 0x16);
    fn_8029113C(name, fn_80118DE8(a->person), 0x39);
    name[0x3f] = 0;
    p = fn_80076F54(name);
    if (p) {
        Rd r;
        Rec rec;
        fn_8008A48C(&r, p);
        fn_8008A1DC(&r);
        fn_8008A43C(&r, 8, &rec);
        while (rec.p) {
            if (b->person == rec.p) {
                if (rec.b4) {
                    break;
                }
                return 0;
            }
            fn_8008A43C(&r, 8, &rec);
        }
    }
    return 1;
}

}
