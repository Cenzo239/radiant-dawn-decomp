/* video.cpp: screen adjust menu teardown. Names guessed. */
#include "game/rJ_800799AC/types.h"

struct Obj { virtual ~Obj(); };
struct AdjProc {
    u8 pad[0x30];
    void* img;      /* 0x30 */
    u8 dirty;       /* 0x34 */
    void* arrow[3]; /* 0x38 */
    Obj* o44;
    Obj* o48;
    Obj* o4c;
    Obj* o50;
    Obj* o54;
    Obj* o58;
    ~AdjProc() {
        delete o4c;
        delete o50;
        delete o44;
        delete o48;
        delete o54;
        delete o58;
    }
};

extern "C" {
void fn_801795E8(void*, int);
void fn_80006A2C(void**);

void fn_8008CF20(AdjProc* p) {
    int i;
    for (i = 0; i < 3; i++) {
        fn_801795E8(p->arrow[i], 1);
    }
    if (p->img) {
        fn_80006A2C(&p->img);
    }
    p->~AdjProc();
}
}
