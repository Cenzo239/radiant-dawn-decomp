/* NEAR MISS: fn_80260140, 19 lines, registers only: first lookup block st/pg want r7/r6 (ours r6/r7), final DICT_PAGE pointer r28 and zero r29. */
/* Dictionary menu: restore state from the save, load files, build lists */
#include "game/rN_8025EEF0/calls.h"
#include "game/rN_8025EEF0/dict.h"

struct C4 { u8 r, g, b, a; };
struct DPg { u8 pad0[0x10]; f32 x10; f32 x14; f32 x18; int x1C; int x20; };
extern "C" {
extern f32 lbl_80391920[];
extern f32 lbl_80391930[];
extern char lbl_804CA798[8];
void* fn_80078CCC(int size, const char* name, int a);
void fn_801C6EAC(const char* a, const char* b, char* out);
void fn_800068EC(void* d, const char* s, int n);
void* fn_80075D78(const char* s);
void fn_802639D0(void);
void fn_80263E5C(void);
void fn_80264204(int page, int i, int a);
BOOL fn_8025F6B8(const char* s, int mode);
void fn_800C4A58(void* p);
void fn_800C4240(void* p);
u8* fn_80076F54(const char* s);
void fn_800C3FD0(void* p);
void* fn_800C6118(void* a, int b, int c, int d, void* e);
void* fn_800D4188(const char* s, void* p);
void* fn_80179660(void* p);
void fn_80179854(void* p, f32 v);
void fn_8017980C(void* p, int a, int b, int c);
u8* fn_800CD204(int i);
void fn_80179A58(void* p, C4 c);
void fn_801798A8(void* p, int a);
void fn_80068C58(void);
}

extern "C" void fn_80260140(void) {
    char name[0x80];
    char rid[0x40];
/*P*/
    int off3;
    int off4;
    int z2;
    int off2;
    int j2;
    int b;
    int c;
    f32 x2;
    int off;
    int i4;
    int i3;
    int z;
    u8* sv;
    u8* base;
    u8* u;
    DictFlags* fl;
    int i2;
    int i;
    int i0;
    int off0;
    DictState* st1;
    DictState* st2;
    DPg* pg1;
    DPg* q2;
    f32 x1;
    Dict10* e2;
    int j1;
    int a;
    int k1;
    int k2;
    int n1;
    int n2;
    int lim1;
    int lim2;
    f32 f1;
    f32 f2;
    Dict14* e1;
    int found;
    int one;
    int zero;
/*E*/
    a = 0;
    b = 0;
    c = 0;
    sv = fn_8024BC94();
    if (*(s16*)(sv + 0x18E8) != -1) a = *(s16*)(sv + 0x18E8);
    if (*(s16*)(sv + 0x18EA) != -1) b = *(s16*)(sv + 0x18EA);
    if (*(s16*)(sv + 0x18EC) != -1) c = *(s16*)(sv + 0x18EC);
    if (*(s16*)(sv + 0x18EE) != -1) lbl_804CC008->m2A = *(s16*)(sv + 0x18EE);
    if (*(s16*)(sv + 0x18F0) != -1) lbl_804CC008->m2C = *(s16*)(sv + 0x18F0);
    if (*(s16*)(sv + 0x18F2) != -1) lbl_804CC008->m44 = *(s16*)(sv + 0x18F2);
    if (*(s16*)(sv + 0x18F4) != -1) lbl_804CC008->m46 = *(s16*)(sv + 0x18F4);
    if (*(s16*)(sv + 0x18F6) != -1) lbl_804CC008->m8A = *(s16*)(sv + 0x18F6);
    lbl_804CC004->mode = 0;
    *((u8*)lbl_804CC004 + 0x70) = 0;
    *(s16*)((u8*)lbl_804CC008 + 0x88) = 0;
    lbl_804CC008->f5C = lbl_80391920[lbl_804CC008->m8A];
    lbl_804CC008->f60 = lbl_80391930[lbl_804CC008->m8A];
    lbl_804CC008->f64 = (lbl_804CC008->f5C - 0.34862384f) / 0.6513761f;
    lbl_804CC008->f68 = (lbl_804CC008->f60 - 0.3478261f) / 0.6521739f;
    lbl_804CC008->m4C = 1;
    lbl_804CC008->m4E = 0;
    lbl_804CC004->lines = (char**)fn_80078CCC(0x3C, lbl_80372C90 + 0x26, 0);
    for (i = 0, off = 0; i < 0xF; i++, off += 4) {
        *(void**)((u8*)lbl_804CC004->lines + off) = fn_80078CCC(0x50, lbl_80372C90 + 0x26, 0);
    }
    lbl_804CC008->lines = (char**)fn_80078CCC(0x10, lbl_80372C90 + 0x26, 0);
    for (i0 = 0, off0 = 0; i0 < 4; i0++, off0 += 4) {
        *(void**)((u8*)lbl_804CC008->lines + off0) = fn_80078CCC(0x1E, lbl_80372C90 + 0x26, 0);
    }
    fn_801C6EAC(lbl_80372C90 + 0x27, lbl_80372C90 + 0x40, name);
    fn_800068EC(lbl_804CC004, name, 0x2080);
    fn_801C6EAC(lbl_80372C90 + 0x45, lbl_80372C90 + 0x40, name);
    fn_800068EC(lbl_804CC008->m20, name, 0x2080);
    fn_80075D78(lbl_80372C90 + 0x58);
    z = 0;
    lbl_804CC004->list = (void**)z;
    fn_802639D0();
    fn_80263E5C();
    lbl_804CC004->page = z;
    fn_80263E5C();
    if (b != 0) {
        st1 = lbl_804CC004;
        pg1 = (DPg*)((u8*)st1 + 0x28);
        e1 = &lbl_804306E8.t1[b];
        j1 = 0;
        for (k1 = 0; k1 < ((const DictState*)st1)->listCount; k1++, j1++) {
            if (e1 == (Dict14*)st1->list[k1]) {
                found = j1;
                break;
            }
        }
        n1 = st1->listCount;
        if (j1 == n1) goto second;
        {
            lim1 = n1 - 8;

            if (found > lim1) f1 = lim1; else f1 = found;
            if (f1 < 0.0f) f1 = 0.0f;
            lim1 = n1 - 9;
            x1 = pg1->x10;
            pg1 += st1->page;
            if (f1 > (f32)lim1) f1 = lim1;
            if (f1 < 0.0f) f1 = 0.0f;
            pg1->x14 = x1;
            pg1->x18 = f1;
            pg1->x20 = 1;
            pg1->x1C = 1;
            fn_80264204(0, found, 1);
        }
    } else {
        fn_80264204(0, 0, 1);
    }
second:
    lbl_804CC004->page = 1;
    fn_80263E5C();
    if (c != 0) {
        st2 = lbl_804CC004;
        e2 = &lbl_804306E8.t4[c];
        j2 = 0;
        for (k2 = 0; k2 < ((const DictState*)st2)->listCount; k2++, j2++) {
            if (e2 == (Dict10*)st2->list[k2]) {
                found = j2;
                break;
            }
        }
        n2 = st2->listCount;
        if (j2 == n2) goto third;
        {
            lim2 = n2 - 8;

            if (found > lim2) f2 = lim2; else f2 = found;
            if (f2 < 0.0f) f2 = 0.0f;
            lim2 = n2 - 9;
            q2 = (DPg*)((u8*)lbl_804CC004 + lbl_804CC004->page * 0x24);
            x2 = *(f32*)((u8*)st2 + 0x5C);
            if (f2 > (f32)lim2) f2 = lim2;
            if (f2 < 0.0f) f2 = 0.0f;
            *(f32*)((u8*)q2 + 0x3C) = x2;
            *(f32*)((u8*)q2 + 0x40) = f2;
            *(int*)((u8*)q2 + 0x48) = 1;
            *(int*)((u8*)q2 + 0x44) = 1;
            fn_80264204(1, found, 1);
        }
    } else {
        fn_80264204(1, 0, 1);
    }
third:
    switch (lbl_804CC000->state) {
    case 0:
        lbl_804CC004->page = a;
        fn_80263E5C();
        break;
    case 1:
        lbl_804CC004->page = 0;
        fn_80263E5C();
        break;
    }
    {
        int y = a * 0x18 + 0x42;
        DictState* st = lbl_804CC004;
        st->x1E = 0x46;
        st->y20 = y;
        st->x22 = 0x46;
        st->y24 = y;
        st->t26 = 0;
        st->page = a;
    }
    lbl_804CC008->m6C = (u8*)fn_80078CCC(*lbl_80430710.cnt1, lbl_80372C90 + 0x26, 0);
    fl = &lbl_80430710;
    lbl_804CC008->m70 = (u8*)fn_80078CCC(*fl->cnt2, lbl_80372C90 + 0x26, 0);
    lbl_804CC008->m74 = (u8*)fn_80078CCC(*fl->cnt3, lbl_80372C90 + 0x26, 0);
    one = 1;
    for (i2 = 0, off2 = 0; i2 < *lbl_80430710.cnt1; off2 += 8, i2++) {
        if (fn_8025F6B8(((DictF8*)((u8*)fl->tbl1 + off2))->name, 0)) {
            lbl_804CC008->m6C[i2] = one;
        } else {
            lbl_804CC008->m6C[i2] = 0;
        }
    }
    for (i3 = 0, off3 = 0; i3 < *lbl_80430710.cnt2; off3 += 8, i3++) {
        if (fn_8025F6B8(((DictF8*)((u8*)lbl_80430710.tbl2 + off3))->name, 0)) {
            lbl_804CC008->m70[i3] = 1;
        } else {
            lbl_804CC008->m70[i3] = 0;
        }
    }
    for (i4 = 0, off4 = 0; i4 < *lbl_80430710.cnt3; off4 += 8, i4++) {
        if (fn_8025F6B8(((DictF8*)((u8*)lbl_80430710.tbl3 + off4))->name, 0)) {
            lbl_804CC008->m74[i4] = 1;
        } else {
            lbl_804CC008->m74[i4] = 0;
        }
    }
    fn_801C6EAC(lbl_80372C90 + 0x65, lbl_80372C90 + 0x8A, name);
    fn_80075D78(name);
    fn_801C6EAC(lbl_80372C90 + 0x8F, lbl_80372C90 + 0x8A, name);
    fn_80075D78(name);
    fn_80075D78(lbl_80372C90 + 0xBC);
    fn_80075D78(lbl_80372C90 + 0xDC);
    fn_80075D78(lbl_80372C90 + 0xFD);
    fn_800C4A58(lbl_804CC008->m24);
    z2 = 0;
    lbl_804CC004->m74 = (void*)z2;
    {
        DictState* pg = DICT_PAGE(lbl_804CC004, lbl_804CC004->page);
        if (lbl_804CC004->m74) {
            fn_800C4240(lbl_804CC004->m74);
            lbl_804CC004->m74 = (void*)z2;
        }
        if (lbl_804CC004->page == 0 && lbl_804CC004->mode == 1) {
            u = fn_80076F54(*(const char**)lbl_804CC004->list[pg->cur]);
            if (u) {
                fn_800C3FD0(*(void**)(u + 0x10));
                lbl_804CC004->m74 = fn_800C6118(*(void**)(u + 0x10), 0, 0, 0x640E, lbl_804CC000);
            }
        }
    }
    {
        DictState* pg = DICT_PAGE(lbl_804CC004, lbl_804CC004->page);
        if (lbl_804CC004->m7C) {
            fn_80081A90(lbl_804CC004->m7C);
            lbl_804CC004->m7C = 0;
        }
        if (lbl_804CC004->page == 1 && lbl_804CC004->mode == 1) {
            const char* s = *(const char**)((u8*)lbl_804CC004->list[pg->cur] + 0xC);
            if (s) {
                fn_80290DDC(rid, lbl_80372C90 + 0x11C, s);
                lbl_804CC004->m7C = fn_800D4188(rid, lbl_804CC000);
                {
                    u8* q = (u8*)lbl_804CC004->m7C;
                    *(f32*)(q + 0x40) = 230.0f;
                    *(f32*)(q + 0x44) = 256.0f;
                }
                *((u8*)lbl_804CC004->m7C + 0x64) = 0;
            }
        }
    }
    {
        void* p = fn_80078CCC(0x2C, lbl_804CA798, 0);
        if (p) p = fn_80179660(p);
        lbl_804CC004->m78 = p;
    }
    fn_80179854(lbl_804CC004->m78, 97.0f);
    fn_8017980C(lbl_804CC004->m78, 0xCA, 0x84, 0x104);
    fn_80179A58(lbl_804CC004->m78, *(C4*)fn_800CD204(4));
    fn_801798A8(lbl_804CC004->m78, 1);
    fn_80068C58();
}
