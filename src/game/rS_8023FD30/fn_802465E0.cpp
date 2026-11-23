#include "game/rS_8023FD30/types.h"
/* Builds the Wii save banner (title, banner texture, 8 icons) and writes it as banner.bin. */
struct Tpl { struct { u8 pad[8]; void* data; }* img; };
struct Banner { u8 pad[8]; u16 flags; u8 pad2[0x60A0 - 0xA]; u8 icon[8][0x1200]; };
extern "C" {
extern s32 lbl_804CBFCC;
extern const char* lbl_804CAAB0;
extern const char* lbl_804CAAB4;
extern char lbl_80372B4C[];
extern u8 lbl_80427820[];
extern u16 lbl_80372968[][0x20];
extern const char* lbl_80391118[];
s32 fn_80315C6C(void*);
s32 fn_80315A5C(void*);
int fn_80290D04(char*, u32, const char*, ...);
s32 fn_80313B24(char*);
s32 fn_80313A38(char*, s32, s32);
s32 fn_8031490C(char*, void*, s32, void*, u32);
s32 fn_80313D74(void*, void*, u32);
s32 fn_80314C40(void*);
void* fn_80079958(u32, u32);
void fn_80079978(void*);
int fn_80325918(void);
void* fn_8017F44C(void*, int, u32);
void* fn_8017F480(void*, void*, u32);
void fn_803162AC(void*, int, u16*, u16*);
int fn_802F6718(const char*, void*);
int fn_802F6C90(void*, void*, u32, int, int);
void fn_802F69C4(void*);
void fn_8032DAD8(void*);
Tpl* fn_8032DBEC(void*, int);
}
static inline u32 crcCalc(u32* t, u8* p, int n) {
    u32 c = 0xFFFFFFFF;
    for (int i = 0; i < n; i++) {
        c = (c >> 8) ^ t[(c ^ *p++) & 0xFF];
    }
    return c ^ 0xFFFFFFFF;
}
#define SPEED(b, n, f) ((b)->flags = (u16)(((b)->flags & ~(3 << (2 * (n)))) | ((f) << (2 * (n)))))
struct FI { u8 pad[0x34]; u32 length; u8 pad2[8]; };
extern "C" {
#pragma use_lmw_stmw on
int fn_802465E0(void*) {
    /*P*/
    u8* p;
    s32 err;
    void* work;
    u32* t;
    Banner* b;
    void* buf;
    int i;
    int k3;
    u32 sz;
    /*E*/
    u32 info[0x24];
    u16 sub[0x20];
    u16 title[0x20];
    FI fi;
    char tmp[0x40];
    char name[0x40];
    k3 = fn_80325918();
    b = (Banner*)fn_80079958(0xF0A0, 0x40);
    fn_8017F44C(b, -1, 0xF0A0);
    work = fn_80079958(0x2000, 0x40);
    t = (u32*)fn_80079958(0x400, 0x40);
    fn_8017F44C(title, 0, 0x80);
    {
        u16* s = lbl_80372968[(u8)k3];
        u16* d = title;
        for (int n = 0; n < 0x1F; n++) { if (*s == 0) break; *d = *s; s++; d++; }
    }
    fn_803162AC(b, 0, title, sub);
    if (!fn_802F6718(lbl_80391118[(u8)k3], &fi)) {
        err = -8;
        goto done;
    }
    sz = (fi.length + 0x1F) & ~0x1F;
    buf = fn_80079958(sz, 0x40);
    if (fn_802F6C90(&fi, buf, sz, 0, 2) < 0) {
        fn_80079978(buf);
        err = -8;
        goto done;
    }
    fn_802F69C4(&fi);
    fn_8032DAD8(buf);
    fn_8017F480((u8*)b + 0xA0, fn_8032DBEC(buf, 0)->img->data, 0x6000);
    for (i = 0; i < 8; i++) {
        fn_8017F480(b->icon[i], fn_8032DBEC(buf, i + 1)->img->data, 0x1200);
        switch (i) {
        case 0:
            SPEED(b, i, 3);
            break;
        case 1:
        case 7:
            SPEED(b, i, 2);
            break;
        default:
            SPEED(b, i, 1);
            break;
        }
    }
    fn_80079978(buf);
    do {
        err = fn_80315C6C(tmp);
        if (err != 0) goto done;
        err = fn_80315A5C(tmp);
        if (err != 0) goto done;
        fn_80290D04(name, 0x40, lbl_80372B4C + 0x70, lbl_804CAAB0, lbl_804CAAB4);
        err = fn_80313B24(name);
        if (err != 0 && err != -0xC) goto done;
        err = fn_80313A38(name, 0x30, 0);
        if (err != 0) goto done;
        err = fn_8031490C(name, info, 2, work, 0x2000);
        if (err != 0) goto done;
        err = fn_80313D74(info, b, 0xF0A0);
        if (err != 0xF0A0) {
            if (err == 0) {
                err = -8;
            }
            fn_80314C40(info);
            goto done;
        }
        err = fn_80314C40(info);
        if (err != 0) goto done;
        {
            u32 c;
            u32 v = 0;
            u32* q = t;
            for (int n = 0x100; n != 0; n--) {
                c = v;
                for (int j = 0; j < 8; j++) {
                    if (c & 1) {
                        c = (c >> 1) ^ 0xEDB88320;
                    } else {
                        c = c >> 1;
                    }
                }
                *q = c;
                q++;
                v++;
            }
        }
        *(u32*)(lbl_80427820 + 0x1BCC) = crcCalc(t, (u8*)b, 0xF0A0);
    done:
        lbl_804CBFCC = err;
    } while (err == -3);
    fn_80079978(b);
    fn_80079978(work);
    fn_80079978(t);
    return 0;
}
}
