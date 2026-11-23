#include "game/rP_80105B04/rp.h"
/* Table start-up: open the bin blocks, relocate headers, run the table loaders. */
struct RdBase { void* buf; u8 a[8]; u8 own; };
class RdV : public RdBase {
public:
    virtual void v0();
    virtual void v1();
    virtual void** at();
};
#if TARGET_PC
/* Host: stream object as MemStream/Block (rD/rJ, TARGET_PC): vt at +0x20 */
struct RdS {
    void* buf;
    u8 a[0x10];
    u8 own;
    void* vt;
    u8 b[4];
};
#else
struct RdS {
    void* buf;
    u8 a[8];
    u8 own;
    void* vt;
    u8 b[4];
};
#endif
extern "C" {
extern char lbl_80367F68[];
extern u8 lbl_80380940[];
void* fn_80077064(const char*);
void fn_8008A48C(void*, void*);
u32 fn_8008A1DC(void*);
void* fn_80076F54(void*);
void fn_80078E24(void*);
#if TARGET_PC
/* MWCC places the vptr after the base data (+0x10), clang at +0; call vtable slot 2
   (at(), fn_8007A4DC) of the data vtable directly. It returns the stream cursor, which
   points at big-endian 32-bit pointer fields in the file. */
#define AT(r) ((bptr32<void>*)((void* (*)(RdS*))((void**)(r).vt)[2])(&(r)))
#else
#define AT(r) (((RdV*)&(r))->at())
#endif
void fn_8010AF44(void) {
    RdS r;
    void* v;
    u32 n;
    u32 i;
    fn_8008A48C(&r, fn_80077064(lbl_80367F68 + 0xAF));
    n = fn_8008A1DC(&r);
    for (i = 0; i < n; i++) {
        v = fn_80076F54(*AT(r));
        *AT(r) = v;
        fn_8008A1DC(&r);
        {
            void* p = *AT(r);
            while (p) {
                v = fn_80076F54(p);
                *AT(r) = v;
                fn_8008A1DC(&r);
                fn_8008A1DC(&r);
                p = *AT(r);
            }
        }
        fn_8008A1DC(&r);
    }
    r.vt = lbl_80380940;
    if (r.own) {
        fn_80078E24(r.buf);
        r.buf = 0;
        r.own = 0;
    }
}

void* fn_80075FB4(const char*, int);
void fn_80109DF8(void);
void fn_8010A2FC(void);
void fn_8010A958(void);
void fn_801198C8(u8*, u32);
void fn_8011D17C(void);
#if TARGET_PC
void fn_80076D48(p32arg, void*);
#else
void fn_80076D48(u32, void*);
#endif
void fn_80112C84(void);
void fn_80112980(void);
void fn_8011936C(void);
void fn_801221E4(void);
extern void* lbl_804CB780; extern void* lbl_804CB784; extern void* lbl_804CB788; extern void* lbl_804CB78C;
extern u8* lbl_804CB7AC; extern u32 lbl_804CB7A8; extern u8* lbl_804CB7B4; extern u8* lbl_804CB7D8; extern u8* lbl_804CB7B0;
extern u8* lbl_804CB7BC; extern int lbl_804CB7B8; extern void* lbl_804CB7C0; extern void* lbl_804CB7C4;
extern u8* lbl_804CB7CC; extern int lbl_804CB7C8; extern u32 lbl_804CB7D0; extern void** lbl_804CB7D4;
extern u8* lbl_804CB7E0; extern u32 lbl_804CB7DC; extern u8* lbl_804CB7E4;
#define BE32(p) ((p[0] << 24) + (p[1] << 16) + (p[2] << 8) + p[3])
void fn_80109B18(const char* a, const char* b, const char* c, const char* d) {
    RdS r;
    int i;
    u8* p;
    int i2;
    u8* q;
    u8* e;
    lbl_804CB780 = fn_80075FB4(a, 0x20);
    lbl_804CB784 = fn_80075FB4(b, 0x20);
    lbl_804CB788 = fn_80075FB4(c, 0x20);
    lbl_804CB78C = fn_80075FB4(d, 0xA0);
    fn_80077064(lbl_80367F68);
    e = (u8*)fn_80077064(lbl_80367F68 + 0xD);
    { u8* o = e + 4; u32 v = BE32(e); lbl_804CB7AC = o; lbl_804CB7A8 = v; }
    fn_80109DF8();
    fn_8010A2FC();
    fn_8010A958();
    e = (u8*)fn_80077064(lbl_80367F68 + 0x17);
{ u32 v = BE32(e); lbl_804CB7B4 = e + 4; fn_801198C8(lbl_804CB7B4, v); }
    lbl_804CB7D8 = (u8*)fn_80077064(lbl_80367F68 + 0x24) + 4;
    lbl_804CB7B0 = (u8*)fn_80077064(lbl_80367F68 + 0x2F) + 4;
    fn_8011D17C();
    e = (u8*)fn_80077064(lbl_80367F68 + 0x3B);
    p = e + 4;
    i = 0;
    { u16 v = (e[0] << 8) + e[1]; lbl_804CB7BC = p; lbl_804CB7B8 = v; }
    for (; i < lbl_804CB7B8; i++, p += 0x14) {
#if TARGET_PC
        fn_80076D48(fe10_ld32(p), p);
#else
        fn_80076D48(*(u32*)p, p);
#endif
    }
    lbl_804CB7C0 = fn_80077064(lbl_80367F68 + 0x4A);
    lbl_804CB7C4 = fn_80077064(lbl_80367F68 + 0x59);
    e = (u8*)fn_80077064(lbl_80367F68 + 0x68);
    q = e + 4;
    i2 = 0;
    { u32 v = BE32(e); lbl_804CB7CC = q; lbl_804CB7C8 = v; }
    for (; i2 < lbl_804CB7C8; i2++, q += 0x18) {
#if TARGET_PC
        fn_80076D48(fe10_ld32(q + 4), q);
#else
        fn_80076D48(*(u32*)(q + 4), q);
#endif
    }
    fn_8008A48C(&r, fn_80077064(lbl_80367F68 + 0x73));
    lbl_804CB7D0 = fn_8008A1DC(&r);
#if TARGET_PC
    lbl_804CB7D4 = (void**)AT(r);
#else
    lbl_804CB7D4 = AT(r);
#endif
    r.vt = lbl_80380940;
    if (r.own) {
        fn_80078E24(r.buf);
        r.buf = 0;
        r.own = 0;
    }
    e = (u8*)fn_80077064(lbl_80367F68 + 0x7F);
    { u8* o = e + 4; u32 v = BE32(e); lbl_804CB7E0 = o; lbl_804CB7DC = v; }
    lbl_804CB7E4 = (u8*)fn_80077064(lbl_80367F68 + 0x89) + 4;
    fn_80112C84();
    fn_80112980();
    fn_8011936C();
    fn_801221E4();
    fn_8010AF44();
}
}
