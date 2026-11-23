/* Streamed DVD sound reader: DVD file open, async read with a completion callback.
 * +0x0 vtable, +0xC is a thread-queue-like block, +0x18 a heap block,
 * +0x1C a buffer block, +0x20 DVDFileInfo-style reader, +0xAC archive handle, +0xC8 a heap block. */
#include "game/rN_8025EEF0/types.h"

#pragma use_lmw_stmw on

extern "C" {

void fn_80079210(void* p);
void fn_80079978(void* p);
void fn_8030EB68(void* p);
void* fn_8030EB98(void* p);
void fn_80314818(void* p);
void* fn_8031447C(void* p);
void fn_8031F324(void* q);
void fn_8031F2B4(void* p);
void fn_80314474(void* p, void* q);
int fn_802BD65C(void* p, const char* path);
#if TARGET_PC
FE10_PROTO int fn_802BD368(void* p, const char* a, void* out);
#else
int fn_802BD368(void* p, int a, void* out);
#endif
int fn_802BDA9C(void* p);
int fn_802BDAA4(void* p);
int fn_802BDAAC(void* p);
int fn_80313E54(void* p, int a, int b);
#if TARGET_PC
FE10_PROTO int fn_80313CFC(void* p, void* a, int b, void (*cb)(int, void*), void* arg);
#else
int fn_80313CFC(void* p, int a, int b, void (*cb)(int, void*), void* arg);
#endif

extern u8 lbl_80391910[];

struct ReadReq {
    u8 pad[0xB8];
    void (*cb)(int, void*);
    void* arg;
};

struct Reader {
    void* vt;
    u8 pad4[8];
    u8 mC[0xC];     /* 0x0C */
    void* m18;      /* 0x18 */
    void* m1C;      /* 0x1C */
    u8 m20[0x8C];   /* 0x20 */
    u8 mAC[0x1C];   /* 0xAC */
    void* mC8;      /* 0xC8 */
};

void fn_8025F3D0(int result, void* arg) {
    ReadReq* req = (ReadReq*)arg;
    void (*cb)(int, void*) = req->cb;
    if (cb != 0) {
        cb(result, req->arg);
    }
    fn_8031F324(fn_8031447C(req));
}

void fn_8025F41C(Reader* r) {
    r->vt = lbl_80391910;
    r->m18 = 0;
    r->m1C = 0;
    r->mC8 = 0;
}

Reader* fn_8025F43C(Reader* r, int del) {
    if (r != 0) {
        r->vt = lbl_80391910;
        if (r->mC8 != 0) {
            if (r->mC8 != 0) {
                fn_8030EB68(r->m1C);
                r->m1C = 0;
                fn_80079978(r->m18);
                r->m18 = 0;
                fn_80079978(r->mC8);
                r->mC8 = 0;
                fn_80314818(r->m20);
            }
        }
        if (del > 0) {
            fn_80079210(r);
        }
    }
    return r;
}

BOOL fn_8025F4E0(Reader* r, const char* path) {
    if (r->mC8 != 0) {
        return fn_802BD65C(r->mAC, path) >= 0;
    }
    return 0;
}

int fn_8025F520(
#if TARGET_PC
Reader* r, const char* a
#else
Reader* r, int a
#endif
) {
    u8 info[0x10];
    if (r->mC8 == 0) {
        return 0;
    }
    if (fn_802BD368(r->mAC, a, info) == 0) {
        return 0;
    }
    int v = fn_802BDAA4(info);
    return v & (fn_802BDAAC(info) != 0 ? -1 : 0);
}

BOOL fn_8025F598(
#if TARGET_PC
Reader* r, const char* id, void* dst, void (*cb)(int, void*), void* arg
#else
Reader* r, int id, int dst, void (*cb)(int, void*), void* arg
#endif
) {
    u8 info[0x10];
    fn_8031F2B4(r->mC);
    ReadReq* req = (ReadReq*)fn_8030EB98(r->m1C);
    if (req == 0) {
        return 0;
    }
    fn_80314474(req, r->mC);
    req->cb = cb;
    req->arg = arg;
    if (fn_802BD368(r->mAC, id, info) == 0) {
        return 0;
    }
    int ofs = fn_802BDA9C(info);
    int size = (fn_802BDAA4(info) + 0x1F) & ~0x1F;
    if (fn_80313E54(r->m20, ofs, 0) < 0) {
        return 0;
    }
    if (fn_80313CFC(r->m20, dst, size, fn_8025F3D0, req) < 0) {
        return 0;
    }
    return fn_802BDAAC(info) != 0;
}

}
