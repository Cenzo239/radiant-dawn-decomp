/* Dictionary (help "DF_*" terms): tables loaded from dictionaryF.bin and flag bits in the
 * save data block returned by fn_8024BC94. */
#include "game/rN_8025EEF0/types.h"

#pragma use_lmw_stmw on

extern "C" {

u8* fn_8024BC94(void);
#if TARGET_PC
FE10_PROTO char * fn_80291480(const char* s, const char* t);
#else
int fn_80291480(const char* s, const char* t);
#endif
int fn_80291188(const char* s, const char* t);

extern char lbl_80372C90[];

struct DictEnt { u32 bit; const char* name; };
struct DictF {
    int* cnt1; DictEnt* tbl1;
    int* cnt2; DictEnt* tbl2;
    int* cnt3; DictEnt* tbl3;
    int* cnt4; DictEnt* tbl4;
};
extern DictF lbl_80430710;

static inline BOOL bitTest(u32* p, u32 bit) {
    while (bit >= 0x20) { bit -= 0x20; p++; }
    return (*p & (1 << bit)) != 0;
}
static inline void bitSet(u32* p, u32 bit) {
    while (bit >= 0x20) { bit -= 0x20; p++; }
    *p |= (1 << bit);
}
static inline void bitClear(u32* p, u32 bit) {
    while (bit >= 0x20) { bit -= 0x20; p++; }
    *p &= ~(1 << bit);
}

/* mode 0 test, 1 set, 2 clear */
BOOL fn_8025F6B8(const char* s, int mode) {
    int n1;
    int n3;
    DictEnt* e1;
    DictEnt* e2;
    int n4;
    int i1;
    int i2;
    int i4;
    int i3;
    DictEnt* e3;
    int n2;
    DictEnt* e4;

    u8* save = fn_8024BC94();

    if (fn_80291480(s, lbl_80372C90) == 0) {
        if (fn_80291480(s, lbl_80372C90 + 8) != 0) goto t2;
        if (fn_80291480(s, lbl_80372C90 + 0x10) != 0) goto t2;
        if (fn_80291480(s, lbl_80372C90 + 0x16) != 0) goto t2;
        if (fn_80291480(s, lbl_80372C90 + 0x1E) == 0) goto end;
        goto last;
    }
    i1 = 0;
    e1 = lbl_80430710.tbl1;
    n1 = *lbl_80430710.cnt1;
    for (; i1 < n1; e1++, i1++) {
        if (fn_80291188(s, e1->name) == 0) {
            switch (mode) {
            case 0: return bitTest((u32*)(save + 0x18B4), e1->bit);
            case 1: bitSet((u32*)(save + 0x18B4), e1->bit); return 1;
            case 2: bitClear((u32*)(save + 0x18B4), e1->bit); return 1;
            }
        }
    }
t2:
    i2 = 0;
    e2 = lbl_80430710.tbl2;
    n2 = *lbl_80430710.cnt2;
    for (; i2 < n2; e2++, i2++) {
        if (fn_80291188(s, e2->name) == 0) {
            switch (mode) {
            case 0: return bitTest((u32*)(save + 0x18C8), e2->bit);
            case 1: bitSet((u32*)(save + 0x18C8), e2->bit); return 1;
            case 2: bitClear((u32*)(save + 0x18C8), e2->bit); return 1;
            }
        }
    }
    i3 = 0;
    e3 = lbl_80430710.tbl3;
    n3 = *lbl_80430710.cnt3;
    for (; i3 < n3; e3++, i3++) {
        if (fn_80291188(s, e3->name) == 0) {
            switch (mode) {
            case 0: return bitTest((u32*)(save + 0x18D4), e3->bit);
            case 1: bitSet((u32*)(save + 0x18D4), e3->bit); return 1;
            case 2: bitClear((u32*)(save + 0x18D4), e3->bit); return 1;
            }
        }
    }
last:
    i4 = 0;
    e4 = lbl_80430710.tbl4;
    n4 = *lbl_80430710.cnt4;
    for (; i4 < n4; e4++, i4++) {
        if (fn_80291188(s, e4->name) == 0) {
            switch (mode) {
            case 0: return bitTest((u32*)(save + 0x18E0), e4->bit);
            case 1: bitSet((u32*)(save + 0x18E0), e4->bit); return 1;
            case 2: bitClear((u32*)(save + 0x18E0), e4->bit); return 1;
            }
        }
    }
end:
    return 0;
}

void fn_8025FFF0(u32 bit) {
    bitSet((u32*)(fn_8024BC94() + 0x18B4), bit);
}

}
