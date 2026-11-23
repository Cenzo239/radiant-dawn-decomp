#include "game/rB_8002E1C4/battle.h"

struct Rec7 { u8 a, b, c, d, e; s8 f; u8 g; };
struct MapS {
    int w;
    int h;
    u8 pad8[5];
    u8 grid[64 * 64];
    u8 pad100d[0xd18e - 0x100d];
    u16 xd18e[64 * 64];
    u8 padx[0x15190 - 0xd18e - 0x2000];
    s16* dist;
};
struct Roll {
    u8 x0[0x20];
    s16 x20[0x20];
    s16 x60[0x20];
    u8 xa0, xa1, xa2, xa3, xa4;
    s8 xa5;
    u8 xa6;
    u8 padA7[0xc8 - 0xa7];
    void* xc8;
    void* xcc;
};
struct Stack { u8 data[0x28]; };
extern MapS lbl_803EC898;
#define M ((MapS*)&lbl_803EC898)
extern Roll lbl_803C8DA0;
extern const char lbl_80361338[];
extern void* lbl_804CA698;
extern "C" {
int fn_801148D8(MapS* m, int n);
void* fn_80078D9C(int n, const char* s, int k);
void fn_80078E24(void* p);
void fn_80114944(MapS* m, int n, void* p);
void fn_80114A44(MapS* m, int n, void* p);
void fn_801148CC(MapS* m, void* p);
void fn_80114B44(MapS* m, int a, int b);
void fn_80114888(MapS* m, int n);
Slot* fn_80030CF4(BU* p);
Slot* fn_80030CBC(BU* p);
ItemD* fn_801116B8(Slot* it);
int fn_801107C0(void* d, BU* u);
int fn_801107A0(void* d, BU* u);
void fn_80115DEC(MapS* m, s8 x, s8 y, u8 a, u8 b);
int fn_8028DB44(int a);
int fn_80089D68(int n);
int fn_8011B77C(void* list, void* key);
void fn_8011B430(void* list, void* key);
void fn_8011A36C(void* list);
f32 fn_80127868(BU* p);
Rec7 fn_801278B8(BU* p, f32 bio);
s16 fn_80123AC4(BU* p);
void fn_8002600C(void* log, int code, int v);
void fn_80026324(void* log, int code, int k, int v);
void fn_800275C4(Battle* b, int a, int k);
void fn_800282A0(Battle* b, BU* a, BU* d, int k);
void fn_80030988(BU* p);
void fn_8002B828(Battle* b);
void fn_8002C86C(Battle* b);
void fn_8002CD5C(Battle* b);
void fn_8002CEB0(Battle* b);
void fn_80111B34(Stack* s);
void fn_80111C24(Stack* s, int k);
void fn_80110BB4(Stack* s, void* d);
void fn_8002F05C(BU* p, Stack* it);
#define BT ((Battle*)lbl_803C8E80)

static inline int rollP(int n) {
    if (BT->f15ec & 0x4000) {
        if (lbl_803C8DA0.xa3) return 1;
        return 0;
    }
    return fn_80089D68(n);
}
static inline void rollInit(void) {
    lbl_803C8DA0.xa1 = 0;
    lbl_803C8DA0.xa2 = 0;
    lbl_803C8DA0.xa3 = 0;
    lbl_803C8DA0.xa4 = 0;
    lbl_803C8DA0.xa0 = 0;
    for (int i = 0; i < 0x20; i++) {
        lbl_803C8DA0.x0[i] = 0;
        lbl_803C8DA0.x20[i] = 0;
        lbl_803C8DA0.x60[i] = 0x3039;
    }
    lbl_803C8DA0.xa5 = -1;
    lbl_803C8DA0.xa6 = 0;
    lbl_803C8DA0.xc8 = 0;
    lbl_803C8DA0.xcc = 0;
}

void fn_8002B2AC(Battle* b, int a, int n) {
    Roll* r = &lbl_803C8DA0;
    b->f15ec |= 2;
    if (r->xa1) {
        Stack it;
        fn_80111B34(&it);
        if (r->xc8) {
            fn_80110BB4(&it, r->xc8);
            fn_8002F05C(&b->a, &it);
        }
        if (lbl_803C8DA0.xcc) {
            fn_80110BB4(&it, lbl_803C8DA0.xcc);
            fn_8002F05C(&b->b, &it);
        }
        b->f15ec |= 0x4000;
        lbl_803C8DA0.xa1 = 0;
        fn_80111C24(&it, -1);
    }
    (*(u16*)((u8*)b->a.u.u3f0 + 0x382))++;
    (*(u16*)((u8*)b->b.u.u3f0 + 0x382))++;
    fn_800275C4(b, a, 0);
    b->f15e4 = 0;
    fn_800282A0(b, &b->a, &b->b, 0);
    f32 bioA = fn_80127868(&b->a);
    fn_801278B8(&b->a, bioA);
    f32 bioB = fn_80127868(&b->b);
    {
    Rec7 s = fn_801278B8(&b->b, bioB);
    s8 f = s.f;
    if (fn_8011B77C(b->b.u.x12c, lbl_804CA698)) {
        if (fn_80030CBC(&b->b)->data) {
            if (rollP(f + fn_80123AC4(&b->b))) {
                fn_80026324(b->log, 0x3e, 0x3f, 0);
            } else {
                fn_80026324(b->log, 0x3e, 0x9b, 0);
                fn_8011B430(b->b.u.x12c, lbl_804CA698);
                fn_8011A36C(b->b.u.x12c);
            }
        }
    }
    }
    fn_8002600C(b->log, 0x72, 0);
    fn_80030988(&b->a);
    fn_80030988(&b->b);
    {
    int c = n * 4 + 1;
    int i;
    for (i = 0; i < c; i++) fn_8002B828(b);
    }
    fn_8002C86C(b);
    fn_8002CD5C(b);
    fn_8002CEB0(b);
    rollInit();
}
}
