/* fn_8024953C: copies one save slot to another inside the save file. Round 21,
   exact. Helpers from fn_80248154.cpp (same source file); the argument is the
   {from, to} pair of signed slot numbers. */
#include "game/rS_8023FD30/types.h"
extern "C" {
extern u8* lbl_804CBFD0;
extern s32 lbl_804CBFCC;
extern const char* lbl_804CAAB0;
extern const char* lbl_804CAAB8;
extern char lbl_80372B4C[];
extern char lbl_80380940[];
extern u8 lbl_80427820[];
s32 fn_80315C6C(void*);
s32 fn_80315A5C(void*);
int fn_80290D04(char*, u32, const char*, ...);
s32 fn_80314598(char*, void*, s32);
s32 fn_80313E54(void*, s32, s32);
s32 fn_80313C94(void*, void*, s32);
s32 fn_80314818(void*);
void* fn_80079958(u32, u32);
void fn_80079978(void*);
void fn_8008A48C(void*, void*);
void fn_8024BED8(void*);
void fn_80245D00(void*, s32, u8, u8);
s64 OSGetTime(void);
void fn_8017F480(void*, void*, u32);
void fn_8026D01C(void*, void*);
void fn_8026D0F8(void*);
void fn_8024BD18(void*);
void fn_80245A74(void*, void*);
void fn_80245F9C(void*, void*);
void fn_80078E24(void*);
void fn_8017F44C(void*, s32, u32);
void fn_80245888(void*, void*);
s32 fn_8031490C(char*, void*, s32, void*, u32);
s32 fn_80313D74(void*, void*, u32);
s32 fn_80314C40(void*);
extern char lbl_80380928[];
}

struct SaveHeader {
    u64 magic;
    u32 date;
    u8 pad0C[0xC];
    u32 crc;
};

struct Reader {
    void* data;
    void* cur;
    u32 size;
    u8 own;
    u8 pad0D[3];
    void* vt;
};

static inline BOOL magicOk(SaveHeader* h, u64 m, u32 d) {
    BOOL ok = 0;
    if (h->magic == m && h->date == d) {
        ok = 1;
    }
    return ok;
}
static inline BOOL headerOk(SaveHeader* h) { return magicOk(h, 0x4645313041444154ULL, 0x20060920); }
static inline BOOL sysOk(SaveHeader* h) { return magicOk(h, 0x4645313041535953ULL, 0x20061002); }

static inline u32 crcCalc(u32* t, u8* p, int n) {
    u32 c = 0xFFFFFFFF;
    for (int i = 0; i < n; i++) {
        c = (c >> 8) ^ t[(c ^ *p++) & 0xFF];
    }
    return c ^ 0xFFFFFFFF;
}

static inline s32 slotPos(s8 s) { return s * 0x18000 + 0x4000; }
static inline s32 slotPos2(s8* s) { return *s * 0x18000 + 0x4000; }
static inline u32* crcTableNew() {
    u32* t = (u32*)fn_80079958(0x400, 0x40);
    for (u32 i = 0; i < 0x100; i++) {
        u32 c = i;
        for (int j = 0; j < 8; j++) {
            if (c & 1) {
                c = (c >> 1) ^ 0xEDB88320;
            } else {
                c = c >> 1;
            }
        }
        t[i] = c;
    }
    return t;
}
static inline BOOL crcOk(SaveHeader* h, int size) {
    u32* t = crcTableNew();
    u32 stored = h->crc;
    h->crc = 0;
    u32 got = crcCalc(t, (u8*)h, size);
    h->crc = stored;
    fn_80079978(t);
    return stored == got;
}
static inline BOOL headerCrcOk(SaveHeader* h) {
    if (!headerOk(h)) {
        return 0;
    }
    return crcOk(h, 0x18000);
}
static inline BOOL sysCrcOk(SaveHeader* h) {
    if (!sysOk(h)) {
        return 0;
    }
    return crcOk(h, 0x4000);
}
struct LoadArg {
    s8 slot;
    u8 pad01[7];
    void* dst;
};

/* One attempt to read and verify the file; err is -3 when the file system was busy. */
#define READ_FILE(pos, size, OK, CRCOK) \
        u32 info[0x24]; \
        char tmp[0x40]; \
        char name[0x40]; \
        err = fn_80315C6C(tmp); \
        if (err != 0) goto done; \
        err = fn_80315A5C(tmp); \
        if (err != 0) goto done; \
        fn_80290D04(name, 0x40, lbl_80372B4C + 0x70, lbl_804CAAB0, lbl_804CAAB8); \
        err = fn_80314598(name, info, 1); \
        if (err != 0) goto done; \
        err = fn_80313E54(info, pos, 0); \
        if (err != pos) { \
            if (err == 0) { \
                err = -8; \
            } \
            fn_80314818(info); \
            goto done; \
        } \
        err = fn_80313C94(info, buf, size); \
        if (err != size) { \
            if (err == 0) { \
                err = -8; \
            } \
            fn_80314818(info); \
            goto done; \
        } \
        err = fn_80314818(info); \
        if (err != 0) goto done; \
        if (!OK(buf)) { \
            err = -0xC; \
            goto done; \
        } \
        if (!CRCOK(buf)) { \
            err = -0x100; \
            goto done; \
        }

#define READ_INTO(fn2, dst) \
        { \
            Reader r; \
            fn_8008A48C(&r, buf); \
            fn2(dst, &r); \
            r.vt = lbl_80380940; \
            if (r.own) { \
                fn_80078E24(r.data); \
                r.data = 0; \
                r.own = 0; \
            } \
        }



struct SaveArg {
    s8 a;
    u8 b;
    u8 c;
    u8 pad03;
    void* d;
};

struct SysHeader {
    u8 pad00[0x10];
    s64 time;
    u8 pad18[4];
    s32 count;
    u8 pad20[0x10];
    u8 v30;
    u8 pad31[0xF];
    u32 flags;
    u8 pad44[0x2C];
    u8 v70[0x1000];
};

extern "C" SysHeader lbl_80429400;
#define WRITE_FILE(pos, buf2) \
        u32 info[0x24]; \
        char tmp[0x40]; \
        char name[0x40]; \
        err = fn_80315C6C(tmp); \
        if (err != 0) goto done; \
        err = fn_80315A5C(tmp); \
        if (err != 0) goto done; \
        fn_80290D04(name, 0x40, lbl_80372B4C + 0x70, lbl_804CAAB0, lbl_804CAAB8); \
        err = fn_8031490C(name, info, 2, work, 0x2000); \
        if (err != 0) goto done; \
        err = fn_80313E54(info, 0, 0); \
        if (err != 0) { \
            if (err == 0) { \
                err = -8; \
            } \
            fn_80314C40(info); \
            goto done; \
        } \
        err = fn_80313D74(info, buf, 0x4000); \
        if (err != 0x4000) { \
            if (err == 0) { \
                err = -8; \
            } \
            fn_80314C40(info); \
            goto done; \
        } \
        err = fn_80313E54(info, pos, 0); \
        if (err != pos) { \
            if (err == 0) { \
                err = -8; \
            } \
            fn_80314C40(info); \
            goto done; \
        } \
        err = fn_80313D74(info, buf2, 0x18000); \
        if (err != 0x18000) { \
            if (err == 0) { \
                err = -8; \
            } \
            fn_80314C40(info); \
            goto done; \
        } \
        err = fn_80314C40(info);

#pragma use_lmw_stmw on
extern "C" {
void fn_80246ADC(void*);

struct DataHeader {
    u64 magic;
    u32 date;
    u8 pad0C[0xC];
    u32 crc;
    s32 count;      /* 0x1c */
    u8 pad20[0x10];
    u8 slot;        /* 0x30 */
};

static inline void headerSeal(SaveHeader* h, int size) {
    if (headerOk(h)) {
        u32* t = crcTableNew();
        h->crc = 0;
        h->crc = crcCalc(t, (u8*)h, size);
        fn_80079978(t);
    }
}

/* Copies save slot arg->a to slot arg->b inside the save file: read, check,
   stamp the new slot number and use count, re-seal, write. Retries while the
   file system reports busy (-3). */
struct CopyArg { s8 a; s8 b; };
int fn_8024953C(CopyArg* arg) {
    SaveHeader* buf;
    void* work;
    s32 err;
    fn_80246ADC(arg);
    buf = (SaveHeader*)fn_80079958(0x18000, 0x40);
    work = fn_80079958(0x2000, 0x40);
    do {
        u32 info[0x24];
        char tmp[0x40];
        char name[0x40];
        err = fn_80315C6C(tmp);
        if (err != 0) goto done;
        err = fn_80315A5C(tmp);
        if (err != 0) goto done;
        fn_80290D04(name, 0x40, lbl_80372B4C + 0x70, lbl_804CAAB0, lbl_804CAAB8);
        err = fn_8031490C(name, info, 3, work, 0x2000);
        if (err != 0) goto done;
        err = fn_80313E54(info, arg->a * 0x18000 + 0x4000, 0);
        if (err != arg->a * 0x18000 + 0x4000) {
            if (err == 0) {
                err = -8;
            }
            fn_80314C40(info);
            goto done;
        }
        err = fn_80313C94(info, buf, 0x18000);
        if (err != 0x18000) {
            if (err == 0) {
                err = -8;
            }
            fn_80314C40(info);
            goto done;
        }
        if (!headerOk(buf)) {
            err = -0xC;
            fn_80314C40(info);
            goto done;
        }
        if (!headerCrcOk(buf)) {
            err = -0x100;
            fn_80314C40(info);
            goto done;
        }
        ((DataHeader*)buf)->slot = arg->b;
        ((DataHeader*)buf)->count++;
        headerSeal(buf, 0x18000);
        err = fn_80313E54(info, arg->b * 0x18000 + 0x4000, 0);
        if (err != arg->b * 0x18000 + 0x4000) {
            if (err == 0) {
                err = -8;
            }
            fn_80314C40(info);
            goto done;
        }
        err = fn_80313D74(info, buf, 0x18000);
        if (err != 0x18000) {
            if (err == 0) {
                err = -8;
            }
            fn_80314C40(info);
            goto done;
        }
        err = fn_80314C40(info);
    done:
        lbl_804CBFCC = err;
    } while (err == -3);
    fn_80079978(buf);
    fn_80079978(work);
    return 0;
}
}
