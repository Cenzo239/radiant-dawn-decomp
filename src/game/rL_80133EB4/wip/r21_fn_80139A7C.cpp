/* fn_80139A7C (0x5D8): complete self-contained draft (round 21), the round 14 section of wip/near3.cpp unchanged.
 * Level `other`: 370 of 374 instructions, 14 masked lines, all in the quadtree set-up at the end:
 *   - the node count: the original keeps the outermost loop (`li r0,4; li r3,1; mtctr; addi r3,r3,0x15; bdnz;
 *     mulli r3,r3,0x34`) with the inner levels folded to 21; ours folds everything to `li r3,0x1144`
 *     (85 nodes * 0x34). Tried this round: a recursive `static inline int CR(int k)` (keeps the loop but calls
 *     CR(2) out of line, with inline_depth 2..30 and defer_codegen as well), a plain recursive static under
 *     auto_inline (not inlined at all), a caller-level loop over the folded inner count with int/s16 sums, a
 *     do-while form, opt_propagation off with a variable depth, opt_unroll_loops off around the helper;
 *   - the original loads the depth constant 2 twice (`li r6,2` separate from the first) and stores the first
 *     byte of two child nodes with `stbux`, ours with `stbx` plus `add`.
 * The quadtree is 4 levels deep (kinds 3..0), 85 nodes of 0x34 bytes; B3..B0 and C3..C0 stand for one recursive
 * builder and one recursive counter in the original source.
 */
#include "game/rL_80133EB4/types.h"
#pragma use_lmw_stmw off
struct QT {
    u8 split, vis;
    u16 count;
    u8 pad4[0x1C - 4];
    void* a, *b;
    QT* child[4];
};
struct Cam { u8 pad[0xC]; f32 xc, x10; u8 pad14[0x148 - 0x14]; f32 x148, x14c; };
struct Grp { u8 p[0xC0]; };
struct MM {
    void* x0;
    void* x4;
    Grp* x8;
    void* xc;
    void* x10;
    void* x14;
    void* x18;
    u8 pad1c[0x50 - 0x1C];
    s16 x50, x52;
    u8 pad54[0x7C - 0x54];
    void* x7c;
    QT* x80;
    QT* x84;
    s16 x88;
    char name[0xB1 - 0x8A];
    u8 xb1;
    u8 padb2[2];
    u32 xb4;
    u8 padb8[0xC4 - 0xB8];
    f32 xc4, xc8;
    u8 padcc[4];
    f32 xd0;
};
extern "C" {
extern long long OSGetTime(void);
extern char* strcpy(char*, const char*);
extern u8 lbl_80386148[];
extern const char lbl_803694D4[];
extern u8 lbl_803EC898[];
extern void fn_8013A054(MM*);
extern void* fn_80081050(void*, int);
extern void fn_80290DDC(char*, const char*, ...);
extern void* fn_8017F37C(char*, const char*, const char*);
extern u32 fn_8023F9F4(void*);
extern void* fn_8023F1A4(void*, void*);
extern void* fn_80075D78(void*);
extern void fn_8010DB48(char*);
extern void fn_80136164(MM*);
extern void fn_80136348(MM*);
extern void fn_8013677C(MM*);
extern void fn_801369BC(MM*);
extern int fn_80076F54(char*);
extern void* fn_80077064(char*);
extern void* fn_800791B0(int);
extern void* fn_801C9FC4(Grp*, void*, char*);
extern void fn_8013608C(MM*);
extern void fn_801379F8(MM*, int);
extern void fn_801475F4(void);
extern void fn_8013AC48(MM*);
extern void fn_8013A8D8(MM*, int);
extern void fn_8013AF10(MM*);
extern Cam* fn_8000F470(void);
extern void fn_8000FA18(int, f32, f32);
extern void* fn_8001D3B4(const char*);
extern void* fn_801436DC(void*);
extern void* fn_80146A4C(void*);
extern void fn_8013A638(MM*);

static inline QT* Alloc(MM* mm, u8 kind) {
    QT* q = &mm->x84[mm->x88++];
    q->split = kind;
    q->a = 0;
    q->b = 0;
    q->count = 0;
    q->vis = 0;
    q->child[0] = 0;
    q->child[1] = 0;
    q->child[2] = 0;
    q->child[3] = 0;
    return q;
}

static inline QT* B0(MM* mm, int k) { QT* q = Alloc(mm, k); return q; }
static inline QT* B1(MM* mm, int k) { QT* q = Alloc(mm, k); if (k > 0) { for (int i = 0; i < 4; i++) q->child[i] = B0(mm, k - 1); } return q; }
static inline QT* B2(MM* mm, int k) { QT* q = Alloc(mm, k); if (k > 0) { for (int i = 0; i < 4; i++) q->child[i] = B1(mm, k - 1); } return q; }
static inline QT* B3(MM* mm, int k) { QT* q = Alloc(mm, k); if (k > 0) { for (int i = 0; i < 4; i++) q->child[i] = B2(mm, k - 1); } return q; }
static inline int C0(int k) { return 1; }
static inline int C1(int k) { int n = 1; if (k > 0) { for (int i = 0; i < 4; i++) n += C0(k - 1); } return n; }
static inline int C2(int k) { int n = 1; if (k > 0) { for (int i = 0; i < 4; i++) n += C1(k - 1); } return n; }
static inline int C3(int k) { int n = 1; if (k > 0) { for (int i = 0; i < 4; i++) n += C2(k - 1); } return n; }
int fn_80139A7C(MM* mm, const char* name, void* heap) {
    char path[0x40];
    char p2[0x40];
    char p3[0x40];
    /*P*/
    void* a;
    const char* s;
    Grp* g;
    int i;
    void* d;
    /*E*/
    OSGetTime();
    fn_8013A054(mm);
    mm->x10 = fn_80081050(lbl_80386148, 4);
    strcpy(mm->name, name);
    switch (mm->xb1) {
    case 0: {
        s = lbl_803694D4;
        fn_80290DDC(path, s + 0x167, s + 0x155, name);
        a = fn_8017F37C(path, s + 0x15B, s + 0x16D);
        if (fn_8023F9F4(a) == 0x40000) a = fn_8017F37C(path, s + 0x15B, s + 0x172);
        if (fn_8023F9F4(a) == 0x40000) return 0;
        mm->x0 = fn_8023F1A4(a, heap);
        {
            s = lbl_803694D4;
            mm->x4 = fn_80075D78(fn_8017F37C(path, s + 0x177, 0));
            mm->xd0 = 0.2f;
            fn_8010DB48(mm->name);
            fn_80136164(mm);
            *(f32*)(lbl_803EC898 + 0x1D424) = mm->xc4;
            *(f32*)(lbl_803EC898 + 0x1D428) = mm->xc8;
            fn_80136348(mm);
            fn_8013677C(mm);
            fn_801369BC(mm);
            fn_80290DDC(p2, s + 0x99, mm->name);
        }
        if (fn_80076F54(p2)) {
            d = fn_80077064(p2);
            if (mm->x50 > 0) mm->x8 = (Grp*)fn_800791B0(mm->x50 * 0xC0);
            else mm->x8 = 0;
            g = mm->x8;
            for (i = 0; i < mm->x50; i++, g++) d = fn_801C9FC4(g, d, path);
        }
        fn_8013608C(mm);
        fn_801379F8(mm, 1);
        fn_801475F4();
        break;
    }
    case 1:
    case 2:
    case 3: {
        s = lbl_803694D4;
        fn_80290DDC(path, s + 0x167, s + 0x15F, name);
        a = fn_8017F37C(path, s + 0x164, s + 0x16D);
        if (fn_8023F9F4(a) == 0x40000) a = fn_8017F37C(path, s + 0x164, s + 0x172);
        if (fn_8023F9F4(a) == 0x40000) return 0;
        mm->x0 = fn_8023F1A4(a, heap);
        {
            s = lbl_803694D4;
            mm->x4 = fn_80075D78(fn_8017F37C(path, s + 0x177, 0));
            mm->xd0 = 3.0f;
            fn_80136164(mm);
            fn_80136348(mm);
            fn_8013677C(mm);
            fn_801369BC(mm);
            fn_80290DDC(p3, s + 0x99, mm->name);
        }
        if (fn_80076F54(p3)) {
            d = fn_80077064(p3);
            if (mm->x50 > 0) mm->x8 = (Grp*)fn_800791B0(mm->x50 * 0xC0);
            else mm->x8 = 0;
            g = mm->x8;
            for (i = 0; i < mm->x50; i++, g++) d = fn_801C9FC4(g, d, path);
        }
        fn_8013608C(mm);
        break;
    }
    case 4:
        mm->x0 = 0;
        mm->x4 = 0;
        mm->x8 = 0;
        mm->xc = 0;
        mm->x50 = 0;
        mm->x52 = 0;
        mm->xd0 = 3.0f;
        break;
    }
    fn_8013AC48(mm);
    fn_8013A8D8(mm, 0);
    mm->x84 = (QT*)fn_800791B0(C3(3) * 0x34);
    mm->x88 = 0;
    mm->x80 = B3(mm, 3);
    fn_8013AF10(mm);
    {
        Cam* c = fn_8000F470();
        c->x14c = 30.0f;
        c->x148 = c->xc / c->x10;
        fn_8000FA18(0, 2.0f, 2000.0f);
    }
    {
        s = lbl_803694D4;
        fn_8023F1A4((void*)(s + 0x17F), 0);
        mm->x7c = fn_8001D3B4(s + 0x18F);
    }
    mm->x14 = fn_801436DC(mm->x10);
    mm->x18 = fn_80146A4C(mm->x10);
    fn_8013A638(mm);
    mm->xb4 |= 0x40000000;
    OSGetTime();
    return 1;
}
}
