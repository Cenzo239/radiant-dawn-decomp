#include "game/rF_8017F400/types.h"
#pragma auto_inline off
extern "C" {
/* unit list stats column: formats one stat, marked when it is at the cap */
extern int fn_80290DDC(char*, const char*, ...);
extern s16 fn_8012386C(u8*);
extern char lbl_804CA8C8[4], lbl_80389EF8[], lbl_804CA8CC[4];
extern s16 fn_80123998(u8*);
extern char lbl_804CA8C0[4], lbl_80389EEC[], lbl_804CA8C4[4];
extern s16 fn_80123AC4(u8*);
extern char lbl_804CA8B8[4], lbl_80389EE0[], lbl_804CA8BC[4];
extern s16 fn_80123BF0(u8*);
extern char lbl_804CA8B0[4], lbl_80389ED4[], lbl_804CA8B4[4];
extern s16 fn_80123D1C(u8*);
extern char lbl_804CA8A8[4], lbl_80389EC8[], lbl_804CA8AC[4];
extern s16 fn_80123DC4(u8*);
extern char lbl_804CA8A0[4], lbl_80389EBC[], lbl_804CA8A4[4];
extern s16 fn_80123EF0(u8*);
extern char lbl_804CA898[4], lbl_80389EB0[], lbl_804CA89C[4];

char* fn_801BC29C(char* buf, u8** row, int col) {
    u8* u = *row;
    u8* j = *(u8**)(u + 0xF0);
    switch (col) {
    case 0:
        return 0;
    case 1: {
        int v = fn_8012386C(u);
        if (v >= *(s8*)(j + 0x105)) fn_80290DDC(buf, lbl_80389EF8, 0x27, v, lbl_804CA8CC);
        else fn_80290DDC(buf, lbl_804CA8C8, v);
        break;
    }
    case 2: {
        int v = fn_80123998(u);
        if (v >= *(s8*)(j + 0x106)) fn_80290DDC(buf, lbl_80389EEC, 0x27, v, lbl_804CA8C4);
        else fn_80290DDC(buf, lbl_804CA8C0, v);
        break;
    }
    case 3: {
        int v = fn_80123AC4(u);
        if (v >= *(s8*)(j + 0x107)) fn_80290DDC(buf, lbl_80389EE0, 0x27, v, lbl_804CA8BC);
        else fn_80290DDC(buf, lbl_804CA8B8, v);
        break;
    }
    case 4: {
        int v = fn_80123BF0(u);
        if (v >= *(s8*)(j + 0x108)) fn_80290DDC(buf, lbl_80389ED4, 0x27, v, lbl_804CA8B4);
        else fn_80290DDC(buf, lbl_804CA8B0, v);
        break;
    }
    case 5: {
        int v = fn_80123D1C(u);
        if (v >= *(s8*)(j + 0x109)) fn_80290DDC(buf, lbl_80389EC8, 0x27, v, lbl_804CA8AC);
        else fn_80290DDC(buf, lbl_804CA8A8, v);
        break;
    }
    case 6: {
        int v = fn_80123DC4(u);
        if (v >= *(s8*)(j + 0x10A)) fn_80290DDC(buf, lbl_80389EBC, 0x27, v, lbl_804CA8A4);
        else fn_80290DDC(buf, lbl_804CA8A0, v);
        break;
    }
    case 7: {
        int v = fn_80123EF0(u);
        if (v >= *(s8*)(j + 0x10B)) fn_80290DDC(buf, lbl_80389EB0, 0x27, v, lbl_804CA89C);
        else fn_80290DDC(buf, lbl_804CA898, v);
        break;
    }
    }
    return buf;
}
}
