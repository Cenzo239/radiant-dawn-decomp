/* Dictionary menu: relation chart draw and teardown */
#include "game/rN_8025EEF0/dict.h"
#include "game/rN_8025EEF0/prim2d.h"

#pragma use_lmw_stmw on

extern "C" {

void fn_8007E5C0(f32 x, f32 y, f32 z, f32 a, f32 b, f32 sx, f32 sy, f32 c);
void fn_80266024(void);
void fn_802652DC(void* e, int a);
void fn_80265574(void* e);
void fn_80265840(void* a, void* b, int c);
void fn_8026654C(void);
void fn_8026697C(void);
void fn_802662EC(void);
void fn_800712E8(int x, int y, int a);
void fn_800C4AA8(void* p);
void fn_800C4240(void* p);
void fn_80263B64(void);
void fn_800763E0(const char* s);
void fn_801C6EAC(const char* a, const char* b, char* out);
void fn_80068C08(void);
extern int* lbl_804CC00C;


class DtorObj28 {
public:
    u8 pad[0x28];
    virtual void v08(); virtual void v0C(); virtual void v10();
    virtual void dtor(int del);
};

void fn_802636F0(void) {
    char buf[0x84];
    int ofs;
    int ofs2;
    int i2;
    int i;

    u8* save = fn_8024BC94();
    *(s16*)(save + 0x18EE) = lbl_804CC008->m2A;
    *(s16*)(save + 0x18F0) = lbl_804CC008->m2C;
    *(s16*)(save + 0x18EE) = lbl_804CC008->m44;
    *(s16*)(save + 0x18F0) = lbl_804CC008->m46;
    *(s16*)(save + 0x18F6) = lbl_804CC008->m8A;
    *(s16*)(save + 0x18E8) = lbl_804CC004->page;
    DtorObj28* o = (DtorObj28*)lbl_804CC004->m78;
    if (o != 0) {
        o->dtor(1);
    }
    fn_80006A2C(lbl_804CC004);
    fn_80006A2C(lbl_804CC008->m20);
    fn_800C4AA8(lbl_804CC008->m24);
    i = 0;
    ofs = 0;
    do {
        if (*(void**)((u8*)lbl_804CC004->lines + ofs) != 0) {
            fn_80078E24(*(void**)((u8*)lbl_804CC004->lines + ofs));
            *(void**)((u8*)lbl_804CC004->lines + ofs) = 0;
            *(void**)((u8*)lbl_804CC004->lines + ofs) = 0;
        }
        i++;
        ofs += 4;
    } while (i < 0xF);
    FREE_FIELD(lbl_804CC004, lines);
    i2 = 0;
    ofs2 = 0;
    do {
        if (*(void**)((u8*)lbl_804CC008->lines + ofs2) != 0) {
            fn_80078E24(*(void**)((u8*)lbl_804CC008->lines + ofs2));
            *(void**)((u8*)lbl_804CC008->lines + ofs2) = 0;
            *(void**)((u8*)lbl_804CC008->lines + ofs2) = 0;
        }
        i2++;
        ofs2 += 4;
    } while (i2 < 4);
    FREE_FIELD(lbl_804CC008, lines);
    fn_80078E24(lbl_804CC008->m6C);
    lbl_804CC008->m6C = 0;
    fn_80078E24(lbl_804CC008->m70);
    lbl_804CC008->m70 = 0;
    fn_80078E24(lbl_804CC008->m74);
    lbl_804CC008->m74 = 0;
    fn_80263B64();
    if (lbl_804CC00C != 0) {
        fn_800761F0(lbl_804CC00C);
        lbl_804CC00C = 0;
    }
    fn_800763E0(lbl_80372C90 + 0x58);
    fn_801C6EAC(lbl_80372C90 + 0x65, lbl_80372C90 + 0x8A, buf);
    fn_800763E0(buf);
    fn_801C6EAC(lbl_80372C90 + 0x8F, lbl_80372C90 + 0x8A, buf);
    fn_800763E0(buf);
    fn_800763E0(lbl_80372C90 + 0xBC);
    fn_800763E0(lbl_80372C90 + 0xDC);
    fn_800763E0(lbl_80372C90 + 0xFD);
    if (lbl_804CC004->m74 != 0) {
        fn_800C4240(lbl_804CC004->m74);
        lbl_804CC004->m74 = 0;
    }
    FREE_FIELD(lbl_804CC004, list);
    fn_80078E24(lbl_804CC000->m34);
    lbl_804CC000->m34 = 0;
    fn_80078E24(lbl_804CC000->m38);
    lbl_804CC000->m38 = 0;
    lbl_804CC000 = 0;
    lbl_804CC004 = 0;
    lbl_804CC008 = 0;
    fn_80068C08();
}

}
