#include "game/rS_8023FD30/types.h"
struct SaveHeader {
    u64 magic;
    u32 date;
    u8 pad0C[0xC];
    u32 crc;
};
static inline BOOL magicOk(SaveHeader* h, u64 m, u32 d) {
    BOOL ok = 0;
    if (h->magic == m && h->date == d) {
        ok = 1;
    }
    return ok;
}
static inline BOOL sysOk(SaveHeader* h) { return magicOk(h, 0x4645313041535953ULL, 0x20061002); }
static inline u32 crcCalc(u32* t, u8* p, int n) {
    u32 c = 0xFFFFFFFF;
    for (int i = 0; i < n; i++) {
        c = (c >> 8) ^ t[(c ^ *p++) & 0xFF];
    }
    return c ^ 0xFFFFFFFF;
}
extern "C" {
extern s32 lbl_804CBFCC;
extern const char* lbl_804CAAB0;
extern const char* lbl_804CAAB4;
extern char lbl_80372B4C[];
extern u8 lbl_80427820[];
s32 fn_80315C6C(void*);
s32 fn_80315A5C(void*);
int fn_80290D04(char*, u32, const char*, ...);
s32 fn_80314598(char*, void*, s32);
s32 fn_80313C94(void*, void*, s32);
s32 fn_80314818(void*);
void* fn_80079958(u32, u32);
void fn_80079978(void*);
extern u8 lbl_8042A470[];
BOOL fn_8031F6BC(void*);
void fn_80320978(s64);
static inline bool done() { return fn_8031F6BC(lbl_8042A470) != 0; }
#pragma use_lmw_stmw on
void fn_80246494(void) {
    while (!done()) {
        s64 t = (s64)5 * ((*(u32*)0x800000F8 / 4) / 1000);
        fn_80320978(t);
    }
}

int fn_80246ADC(void* unused) {
    const char* s;
    u8* buf = (u8*)fn_80079958(0xF0A0, 0x40);
    u32* t = (u32*)fn_80079958(0x400, 0x40);
    s32 err;
    s = lbl_80372B4C;
    do {
        u32 info[0x24];
        char tmp[0x40];
        char name[0x40];
        err = fn_80315C6C(tmp);
        if (err != 0) goto done;
        err = fn_80315A5C(tmp);
        if (err != 0) goto done;
        fn_80290D04(name, 0x40, s + 0x70, lbl_804CAAB0, lbl_804CAAB4);
        err = fn_80314598(name, info, 1);
        if (err != 0) goto done;
        err = fn_80313C94(info, buf, 0xF0A0);
        if (err != 0xF0A0) {
            if (err == 0) {
                err = -8;
            }
            fn_80314818(info);
            goto done;
        }
        err = fn_80314818(info);
        if (err != 0) goto done;
        if (!sysOk((SaveHeader*)lbl_80427820)) {
            err = -0xC;
            goto done;
        }
        {
            u32 c;
            u32 i = 0;
            u32* q = t;
            for (int k = 0x100; k != 0; k--) {
                c = i;
                for (int j = 0; j < 8; j++) {
                    if (c & 1) {
                        c = (c >> 1) ^ 0xEDB88320;
                    } else {
                        c = c >> 1;
                    }
                }
                *q = c;
                q++;
                i++;
            }
        }
        if (*(u32*)(lbl_80427820 + 0x1BCC) != crcCalc(t, buf, 0xF0A0)) {
            err = -0x100;
        }
    done:
        lbl_804CBFCC = err;
    } while (err == -3);
    fn_80079978(buf);
    fn_80079978(t);
    return 0;
}
}
/* WIP: fn_80246ADC, 7 words off: the size base and string base swap (want r26 and r27, mine r27 and
   r26). fn_80246494 in the same draft is matched and lives in fn_80246494.cpp. */
