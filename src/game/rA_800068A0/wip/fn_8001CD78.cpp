/* fn_8001CD78: near miss, 4 of 167 words differ. The last block count must land in r26, the old "next" register, not r20. */
#include "game/rA_800068A0/types.h"
extern "C" {
typedef struct SSeg { u8 x0[0xC]; u32 data; u16 size; u8 x12; u8 x13; u16 x14; u16 x16; } SSeg;
typedef struct SEnt { SSeg* segs; u8* base; s16 count; u8 x0A[2]; u8 xC; } SEnt;
typedef struct SRes { u8 x0[0x48]; SEnt* ent; } SRes;
extern SRes* fn_80007F3C(void* a);
extern u8* fn_80007FC0(void* a);
extern void* fn_800080E4(void* a);
extern void fn_80318AE0(u32 dst, void* src, u32 n);
extern void fn_80318B04(void* dst, u32 src, u32 n);
extern void fn_80318BC8(int);
extern void fn_8001D014(u32);
extern void fn_8001D01C(u32);
extern void fn_8001D2FC(void* m, SSeg* s, void* p, u8 n);
extern void fn_8001D024(u32 a, u32 b, u16 n);
extern void fn_8001D144(u32 a, u32 b, u16 n);
#define LC(d) ((d) - 0x20000000)
#pragma use_lmw_stmw on
void fn_8001CD78(void* a) {

    void* mt;
    SEnt* e;
    u32 q2;
    SSeg* seg;
    SSeg* next;
    u32 p;
    u32 q;
    u32 rem;
    u32 off;
    int i;
    int n;
    int n2;
    u32 d2;
    u32 rem2;
    u32 b;
    u32 off2;
    u32 b2;
    u32 p2;
    u8* dst;
    u32 r2;
    u8* w2;
    u32 d;
    u32 r;
    u8* w;

    e = fn_80007F3C(a)->ent;
    dst = fn_80007FC0(a);
    seg = e->segs;
    next = seg + 1;
    fn_80318AE0(0xE0001000, e->base + seg->data, (seg->size + 0x1F) / 32);
    mt = fn_800080E4(a);
    fn_8001D014((e->xC * 0x100 + 7) << 16);
    fn_8001D01C(0x8040606);
    for (i = 0; i < e->count - 1; i++, seg++, next++) {
         {u32 x = LC(((i + 1) & 1) * 0x2000);
 u32 y = x + 0x1000; fn_80318AE0(y, e->base + next->data, (next->size + 0x1F) / 32);}
        off = (seg->data + seg->x12) / 12 * 16;
        rem = off & 0x1F;
        n = (rem + (seg->x14 + seg->x16) * 16 + 0x1F) >> 5;
        fn_8001D2FC(mt, seg, seg->x0 + 8, seg->x13);
        fn_80318BC8(1);
        d = (i & 1) * 0x2000;
        b = LC(d);
        p = b + rem;
        q = b + 0x1000;
        fn_8001D024(q + seg->x12, p, seg->x14);
        fn_8001D144(q + seg->x12, p, (u32)seg->x16 >> 1);
        r = LC(d);
        w = dst + (off & ~0x1F);
        if (n <= 0x80) {
            fn_80318B04(w, r, n & 0x7F);
        } else {
            fn_80318B04(w, r, 0);
            fn_80318B04(w + 0x1000, r + 0x1000, n - 0x80);
        }
    }
    off2 = (seg->data + seg->x12) / 12 * 16;
    rem2 = off2 & 0x1F;
    n2 = (rem2 + (seg->x14 + seg->x16) * 16 + 0x1F) >> 5;
    fn_8001D2FC(mt, seg, seg->x0 + 8, seg->x13);
    d2 = (i & 1) * 0x2000;
    b2 = LC(d2);
    p2 = b2 + rem2;
    q2 = b2 + 0x1000;
    fn_8001D024(q2 + seg->x12, p2, seg->x14);
    fn_8001D144(q2 + seg->x12, p2, (u32)seg->x16 >> 1);
    r2 = LC(d2);
    w2 = dst + (off2 & ~0x1F);
    if (n2 <= 0x80) {
        fn_80318B04(w2, r2, n2 & 0x7F);
    } else {
        fn_80318B04(w2, r2, 0);
        fn_80318B04(w2 + 0x1000, r2 + 0x1000, n2 - 0x80);
    }
}
#pragma use_lmw_stmw off2
}
