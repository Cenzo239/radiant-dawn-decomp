/* Random-order list (soundroom.bin): setup */
#include "game/rN_8025EEF0/calls.h"

struct ListItem { const char* name; s16 x; s16 y; s16 s; };
struct ListE2 { const char* name; const char* b; };
struct ListSt {
    void* tex;
    void* tex2;
    int* file;
    int n;
    int m10;
    ListItem* items;
    ListE2* e2;
    int m1C;
    int m20;
    int m24;
    int m28;
    u8 pad2C[4];
    int m30;
    void* m34;
    const char* m38;
    const char* m3C;
    s16 m40, m42;
    void* bar;
    char txt[0x100];
    f32 m148;
    s16 m14C, m14E, m150;
    s16 pad152;
    s16 m154, m156, m158, m15A, m15C, m15E, m160, m162, m164, m166, m168, m16A, m16C, m16E;
};
struct Bar { u8 pad[0x28]; void* vt; };

extern "C" {

extern ListSt* lbl_804CC044;
extern void* lbl_804CC040;
extern char lbl_8037340C[];
extern char lbl_804CAB10[8];
extern char lbl_80392578[];
u8* fn_800D4228(const char* s);
u8* fn_800D4188(const char* s, void* p);
void fn_800D3990(u8* p);
void fn_80179660(void* p);
void fn_8017985C(void* p, int a);
void fn_80179864(void* p, int a);
void fn_801798A8(void* p, int a);
void fn_801C6EAC(const char* a, const char* b, char* c);
void fn_800068A0(void* a, char* b);
void fn_800068EC(void* a, const char* b, int c);
s16 fn_8024F3C8(const char* s);
int fn_802454C8(void* s, int a);
void fn_8026D63C(void);

void fn_8026F630(void) {
    char buf[0x60];
/*P*/
    int i;
    int off;
    Bar* b;
    ListItem* e;
    void* sv;
/*E*/
    int z = 0;
    lbl_804CC044->m20 = -1;
    lbl_804CC044->m24 = z;
    lbl_804CC044->m28 = -1;
    lbl_804CC044->m40 = 0xFF;
    lbl_804CC044->m42 = 0xFF;
    lbl_804CC044->m14E = z;
    lbl_804CC044->m14C = z;
    lbl_804CC044->m148 = z;
    lbl_804CC044->m150 = z;
    lbl_804CC044->m154 = -100;
    lbl_804CC044->m156 = -100;
    lbl_804CC044->m16A = z;
    lbl_804CC044->m16C = z;
    lbl_804CC044->m162 = 0x68;
    lbl_804CC044->m164 = 0x90;
    lbl_804CC044->m166 = 400;
    lbl_804CC044->m168 = 0xE0;
    lbl_804CC044->m16E = z;
    lbl_804CC044->file = (int*)fn_80075D78(lbl_8037340C + 0x81);
    {
        int* fp = lbl_804CC044->file;
        ListItem* it;
        int j;
        lbl_804CC044->n = *fp++;
        lbl_804CC044->items = (ListItem*)fp;
        it = (ListItem*)fp;
        for (j = 0; j < lbl_804CC044->n; j++, it++) {
        }
        lbl_804CC044->m10 = *(int*)it;
        lbl_804CC044->e2 = (ListE2*)((int*)it + 1);
    }
    lbl_804CC044->m1C = 0;
    {
        e = &lbl_804CC044->items[lbl_804CC044->m1C];
        fn_800D4188(e->name, lbl_804CC040);
    }
    lbl_804CC044->m38 = e->name;
    fn_800D3990(fn_800D4228(lbl_804CC044->m38));
    {
        f32 y = e->y;
        f32 x = e->x;
        u8* m = fn_800D4228(lbl_804CC044->m38);
        *(f32*)(m + 0x40) = x;
        *(f32*)(m + 0x44) = y;
        *(f32*)(m + 0x48) = -700.0f;
    }
    {
        f32 s = (f32)e->s / 100.0f;
        u8* m = fn_800D4228(lbl_804CC044->m38);
        *(f32*)(m + 0x54) = s;
        *(f32*)(m + 0x58) = s;
    }
    lbl_804CC044->m3C = 0;
    {
        b = (Bar*)fn_80078CCC(0x2C, lbl_804CAB10, 0);
        if (b != 0) {
            fn_80179660(b);
            b->vt = lbl_80392578;
        }
        lbl_804CC044->bar = b;
    }
    fn_8017985C(lbl_804CC044->bar, lbl_804CC044->m10 * 0x1C);
    fn_80179864(lbl_804CC044->bar, 0xC4);
    fn_801798A8(lbl_804CC044->bar, 1);
    fn_801C6EAC(lbl_8037340C + 0x8F, lbl_8037340C + 0xAA, buf);
    fn_800068A0(lbl_804CC044, buf);
    lbl_804CC044->tex2 = 0;
    if (fn_801D09F0() != 0) {
        fn_800068EC(&lbl_804CC044->tex2, lbl_8037340C + 0xAF, 0x80);
    }
    lbl_804CC044->m158 = 4;
    lbl_804CC044->m15A = lbl_804CC044->m154;
    lbl_804CC044->m15C = lbl_804CC044->m156;
    lbl_804CC044->m15E = lbl_804CC044->m162 + 0x16;
    lbl_804CC044->m160 = lbl_804CC044->m164 + 0xE + (lbl_804CC044->m24 - lbl_804CC044->m14E) * 0x1C;
    sv = fn_8024BC94();
    lbl_804CC044->m30 = 0;
    i = 0;
    off = 0;
    for (; i < lbl_804CC044->m10; off += 8, i++) {
        if (fn_802454C8(sv, fn_8024F3C8(*(const char**)((u8*)lbl_804CC044->e2 + off)))) {
            lbl_804CC044->m30++;
        }
    }
    if (lbl_804CC044->m30 != 0) {
        lbl_804CC044->m34 = fn_80078CCC(lbl_804CC044->m30, lbl_8037340C + 0xC1, 0);
    } else {
        lbl_804CC044->m34 = 0;
    }
    fn_8026D63C();
}

}
