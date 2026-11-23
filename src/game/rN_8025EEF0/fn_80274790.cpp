/* Conversation room: layout and topic lists */
#include "game/rN_8025EEF0/room.h"

#pragma use_lmw_stmw on

#define ST ((ConvSt*)lbl_804CC06C)

extern "C" {

int fn_80275330(void);
int fn_80275598(void);
void* fn_8010B100(const char* s);
const char* fn_800929AC(void* u);
const char* fn_8009285C(void* u);
void* fn_8010B1D8(const char* s);
const char* fn_80118C44(void* u);
char* strcpy(char* a, const char* b);
#if TARGET_PC
FE10_PROTO int fn_8024016C(void* e, ptr32<const void>);
#else
int fn_8024016C(void* e, const char* s);
#endif
int fn_80240140(void* e);

void fn_80274790(int a, f32 b) {
    roomData()->m1C = curF();
    roomData()->m1E = b;
    roomData()->m20 = roomData()->m22 = a;
}

void fn_80274A14(void) {
    roomData()->m44 = 0x170;
    roomData()->m46 = 0xDA;
    roomData()->m40 = -roomData()->m44 / 2;
    roomData()->m42 = -roomData()->m46 / 2;
    switch (roomData()->m24[0]) {
    case 0:
        roomData()->m30 = 1;
        break;
    case 1:
        roomData()->m30 = 2;
        break;
    }
    roomData()->m54 = 5;
}

int fn_80274E00(void) {
    int r = 0;
    switch (roomData()->m30) {
    case 1:
        r = fn_80275330();
        break;
    case 2:
        r = fn_80275598();
        break;
    }
    if (r == 0) {
        return 0;
    }
    roomData()->m44 = 0x1B0;
    roomData()->m46 = 0xF8;
    roomData()->m40 = -roomData()->m44 / 2;
    roomData()->m42 = -roomData()->m46 / 2;
    roomData()->m54 = 5;
    roomData()->m30 = 3;
    setCurS(0);
    setCurF(0.0f);
    return 1;
}

int fn_80275330(void) {
    int off;
    ConvSt* st;
    int i;
    {
        void* u = fn_8010B100(ST->names[curS()]);
        fn_80290DDC(ST->text, lbl_8037359C + 0x29, fn_8009285C(u), fn_800929AC(u));
    }
    ST->count = 0;
    for (i = 0, off = 0; (st = ST), i < st->n; off += 0x30, i++) {
        int idx = curS();
        st = ST;
        u8* e = st->tbl + off;
        if (fn_80291188(*(char**)e, st->names[idx]) == 0) {
            if (st->count >= 0x27) {
                break;
            }
            st->items[st->count] = e;
            ST->count++;
        }
    }
    if (st->count == 0) {
        return 0;
    }
    return 1;
}

int fn_80275598(void) {
int off2;
int i2;
    const char* name;
    int off;
    int i;
    {
        int idx = curS();
        name = ST->names2[idx];
    }
    if (fn_80291188(name, lbl_8037359C + 0x2F) != 0) {
        strcpy(ST->text, fn_80118C44(fn_8010B1D8(name)));
        ST->count = 0;
        for (i = 0, off = 0; i < ST->n; off += 0x30, i++) {
            int idx = curS();
            if (fn_8024016C(ST->tbl + off, ST->names2[idx]) != 0) {
                if (ST->count >= 0x27) {
                    break;
                }
                ST->items[ST->count] = ST->tbl + off;
                ST->count++;
            }
        }
        if (ST->count == 0) {
            return 0;
        }
        return 1;
    }
    strcpy(ST->text, fn_800D0864(lbl_8037359C + 0x35));
    ST->count = 0;
    for (i2 = 0, off2 = 0; i2 < ST->n; off2 += 0x30, i2++) {
        if (fn_80240140(ST->tbl + off2) == 0) {
            if (ST->count >= 0x27) {
                break;
            }
            ST->items[ST->count] = ST->tbl + off2;
            ST->count++;
        }
    }
    if (ST->count == 0) {
        return 0;
    }
    return 1;
}

}
