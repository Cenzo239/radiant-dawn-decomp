#include "game/rS_8023FD30/types.h"
extern "C" {
extern u8* lbl_804CBFD0;
extern s32 lbl_804CBFCC;
extern const char* lbl_804CAAB0;
extern const char* lbl_804CAAB8;
extern char lbl_80372B4C[];
extern char lbl_80380940[];
extern u8 lbl_80429400[];
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
void fn_80246ADC(void*);
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
    u8 pad14[4];
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

#pragma use_lmw_stmw on

extern "C" {
int fn_802479A8(void) {
    void* dst = lbl_80427820;
    SaveHeader* buf = (SaveHeader*)fn_80079958(0x4000, 0x40);
    s32 err;
    do {
        READ_FILE(0, 0x4000, sysOk, sysCrcOk)
        READ_INTO(fn_80245A74, dst)
    done:
        lbl_804CBFCC = err;
    } while (err == -3);
    fn_80079978(buf);
    return 0;
}

#pragma use_lmw_stmw off
int fn_80247D88(void) {
    SaveHeader* buf = (SaveHeader*)fn_80079958(0x4000, 0x40);
    void* work = fn_80079958(0x2000, 0x40);
    s32 err;
    fn_8017F44C(buf, -1, 0x4000);
    Reader w;
    w.vt = lbl_80380928;
    w.own = 0;
    w.data = buf;
    w.cur = buf;
    w.size = 0x4000;
    fn_80245888(lbl_80427820, &w);
    if (sysOk(buf)) {
        u32* t = crcTableNew();
        buf->crc = 0;
        buf->crc = crcCalc(t, (u8*)buf, 0x4000);
        fn_80079978(t);
    }
    do {
        u32 info[0x24];
        char tmp[0x40];
        char name[0x40];
        err = fn_80315C6C(tmp);
        if (err != 0) goto done;
        err = fn_80315A5C(tmp);
        if (err != 0) goto done;
        fn_80290D04(name, 0x40, lbl_80372B4C + 0x70, lbl_804CAAB0, lbl_804CAAB8);
        err = fn_8031490C(name, info, 2, work, 0x2000);
        if (err != 0) goto done;
        err = fn_80313E54(info, 0, 0);
        if (err != 0) {
            if (err == 0) {
                err = -8;
            }
            fn_80314C40(info);
            goto done;
        }
        err = fn_80313D74(info, buf, 0x4000);
        if (err != 0x4000) {
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
    w.vt = lbl_80380940;
    if (w.own) {
        fn_80078E24(w.data);
        w.data = 0;
        w.own = 0;
    }
    return 0;
}

#pragma use_lmw_stmw on

#define LOAD_TO_HEADER(fn, pos) \
int fn(LoadArg* arg) { \
    SaveHeader* buf = (SaveHeader*)lbl_804CBFD0; \
    s32 err; \
    do { \
        READ_FILE(arg->slot * 0x18000 + pos, 0x18000, headerOk, headerCrcOk) \
        { \
            Reader r; \
            fn_8008A48C(&r, buf); \
            fn_8024BED8(&r); \
            r.vt = lbl_80380940; \
            if (r.own) { \
                fn_80078E24(r.data); \
                r.data = 0; \
                r.own = 0; \
            } \
        } \
        lbl_80427820[0x1BC9] = lbl_80429400[0x30]; \
    done: \
        lbl_804CBFCC = err; \
    } while (err == -3); \
    return 0; \
}

#define LOAD_TO_ARG(fn, pos) \
int fn(LoadArg* arg) { \
    void* dst = arg->dst; \
    SaveHeader* buf = (SaveHeader*)fn_80079958(0x18000, 0x40); \
    s32 err; \
    do { \
        READ_FILE(arg->slot * 0x18000 + pos, 0x18000, headerOk, headerCrcOk) \
        READ_INTO(fn_80245F9C, dst) \
    done: \
        lbl_804CBFCC = err; \
    } while (err == -3); \
    fn_80079978(buf); \
    return 0; \
}


/* Clears one save slot: rewrites it with 0xFF bytes. */
#define CLEAR_SLOT(fn, pos) \
int fn(LoadArg* arg) { \
    fn_80246ADC(arg); \
    void* buf = fn_80079958(0x18000, 0x40); \
    void* work = fn_80079958(0x2000, 0x40); \
    s32 err; \
    fn_8017F44C(buf, -1, 0x18000); \
    do { \
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
        err = fn_80313E54(info, arg->slot * 0x18000 + pos, 0); \
        if (err != arg->slot * 0x18000 + pos) { \
            if (err == 0) { \
                err = -8; \
            } \
            fn_80314C40(info); \
            goto done; \
        } \
        err = fn_80313D74(info, buf, 0x18000); \
        if (err != 0x18000) { \
            if (err == 0) { \
                err = -8; \
            } \
            fn_80314C40(info); \
            goto done; \
        } \
        err = fn_80314C40(info); \
    done: \
        lbl_804CBFCC = err; \
    } while (err == -3); \
    fn_80079978(buf); \
    fn_80079978(work); \
    return 0; \
}

LOAD_TO_HEADER(fn_802488B8, 0x4000)
CLEAR_SLOT(fn_802493B4, 0x4000)
LOAD_TO_ARG(fn_80249BDC, 0x4000)
LOAD_TO_HEADER(fn_80249FF4, 0x94000)
CLEAR_SLOT(fn_8024AB04, 0x94000)
LOAD_TO_ARG(fn_8024AC94, 0x94000)

int fn_8024B0B4(void) {
    SaveHeader* buf = (SaveHeader*)fn_80079958(0x4000, 0x40);
    s32 err;
    do {
        READ_FILE(0, 0x4000, sysOk, sysCrcOk)
    done:
        lbl_804CBFCC = err;
    } while (err == -3);
    fn_80079978(buf);
    return 0;
}
}
