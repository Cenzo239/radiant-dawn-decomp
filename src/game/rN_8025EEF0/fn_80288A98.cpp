/* Staff roll: setup */
#include "game/rN_8025EEF0/calls.h"

extern "C" {

extern char* lbl_80392DC8[][2];
extern char lbl_80392E98[];
extern char lbl_80392EBC[];
extern char lbl_80392EA4[];
extern char lbl_80373ECC[];
void* fn_8001D3B4(const char* s);
u8* fn_8024BCA0(void);
u8* fn_8012CE54(const char* s);
const char* fn_800D0DBC(const char* s);
int fn_8029191C(const char* s);
int* fn_80077064(const char* s);

struct Roll {
    u8 pad[0x30];
    u8 m30;
    u8 pad31[7];
    u8 m38;
    u8 pad39;
    s16 m3A;
    int m3C, m40, m44, m48, m4C, m50;
    void* m54;
    s16 m58;
    u8 pad5A[6];
    s16 m60;
    u8 pad62[2];
    f32 m64;
    s16 m68;
    u8 pad6A[6];
    u64 m70;
    u8 pad78[0xC];
    void* m84;
    void* m88;
    u8 pad8C[0xC];
    u16 m98;
    u8 pad9A[2];
    int* m9C;
};

static inline BOOL hasNl(const char* s) {
    int i;
    for (i = 0; s[i] != 0; i++) {
        if (s[i] == '\n') {
            return 1;
        }
    }
    return 0;
}

void fn_80288A98(Roll* r) {
/*P*/
    int i;
    u64 total;
    s8 lang;
/*E*/
    lang = fn_8024BC94()[0x1BC8];
    r->m54 = fn_8001D3B4(lbl_80392DC8[lang][fn_801D09F0()]);
    {
        u8* sv = fn_8024BCA0();
        if (sv[0x34] >= 2) {
            r->m38 = 1;
        } else {
            r->m38 = 0;
        }
        if (sv[0x34] >= 2) {
            u8* u = fn_8012CE54(lbl_80392E98);
            BOOL b = 0;
            if (u != 0 && (*(u8**)(u + 0xF4))[8] != 6) {
                b = 1;
            }
            if (b) {
                r->m30 = 1;
                if ((s8)fn_8024BC94()[0x1BC8] == 0) {
                    r->m58 = -20;
                } else {
                    r->m58 = 0;
                }
                goto done;
            }
        }
        r->m30 = 0;
    }
done:
    {
        r->m84 = fn_80075D78(fn_800D0DBC(lbl_80373ECC));
        r->m88 = fn_80075D78(lbl_80373ECC + 0x9);
        if (r->m30 == 0) {
            r->m98 = fn_8029191C(fn_800D0864(lbl_80373ECC + 0x1B));
            r->m3C = *fn_80077064(lbl_80373ECC + 0x2F);
            r->m40 = *fn_80077064(lbl_80373ECC + 0x45);
            r->m44 = *fn_80077064(lbl_80373ECC + 0x5B);
            r->m48 = *fn_80077064(lbl_80373ECC + 0x74);
            r->m4C = *fn_80077064(lbl_80373ECC + 0x90);
            r->m50 = *fn_80077064(lbl_80373ECC + 0xAB);
        } else {
            r->m98 = fn_8029191C(fn_800D0864(lbl_80373ECC + 0x1B));
            r->m3C = *fn_80077064(lbl_80373ECC + 0xC2);
            r->m40 = *fn_80077064(lbl_80373ECC + 0xD8);
            r->m44 = *fn_80077064(lbl_80373ECC + 0xEE);
            r->m48 = *fn_80077064(lbl_80373ECC + 0x107);
            r->m4C = *fn_80077064(lbl_80373ECC + 0x123);
            r->m50 = *fn_80077064(lbl_80373ECC + 0x13E);
        }
        r->m3A = 0;
        r->m64 = *(f32*)fn_80077064(lbl_80373ECC + 0x155);
        r->m60 = *fn_80077064(lbl_80373ECC + 0x16F);
        r->m68 = *fn_80077064(lbl_80373ECC + 0x18E);
        r->m9C = fn_80077064(lbl_80373ECC + 0x1AB);
    }
    {
        total = (u64)((f32)(r->m98 * 0x20 + 0x1C0) / r->m64);
        for (i = 0; i < r->m98; i++) {
            fn_80290DDC(lbl_80392EBC, lbl_80392EA4, i);
            if (hasNl(fn_800D0864(lbl_80392EBC))) {
                total = (u64)((f32)total + 10.0f / r->m64);
            }
        }
        r->m70 = total;
    }
}

}
