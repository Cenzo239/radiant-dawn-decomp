#include "game/rB_8002E1C4/types.h"

/* Help windows drawn over a unit. Each starts from the same inlined head:
 * background frame, HP line, then the item icons of the unit's skills. */

extern const char lbl_80361390[0x200];
extern const f32 lbl_804CCCF4; /* 0.0f */
extern const f32 lbl_804CCD24; /* -1.0f */
extern const f32 lbl_804CCD28; /* 1.0f */

struct VBase { u8 pad[0x44]; };
struct VObj : VBase {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void draw(int x, int y, void* item);
};
struct WSub { u8 pad[8]; u8 b8; };
extern void* lbl_804CA4EC;
extern "C" {
extern VObj lbl_803E7290;
s16 fn_801237EC(BUnit* p);                 /* max HP */
void fn_80031ED4(int x, int y, int w, int h); /* draw frame */
void fn_8006E030(f32 a);
void fn_80074EB4(int x, int y, int w, int h);
void fn_8006E068(void);
const char* fn_800D0864(const char* key);
void fn_800CB3A8(f32 a, f32 b, s16 x, s16 y, int c, int d, int e, const char* fmt, ...);
int fn_80109174(void* list);
#if TARGET_PC
FE10_PROTO ptr32<void> fn_801091E0(void* list, int i);
#else
void* fn_801091E0(void* list, int i);
#endif
void fn_800718F0(BUnit* p, int a, int b, int c);
void fn_800718D0(int a, int x, int w, int h, u8 k, int d);
void fn_80032198(BUnit* p, int x, int y, int dhp, int showItems);
void fn_80032334(BUnit* p, int x, int y, const char* s);
void fn_80032A34(int kind, int x, int y);
void fn_80032B88(BUnit* p, int kind, int x, int y, int dhp);
s8 fn_8012401C(BUnit* p);
s8 fn_80124144(BUnit* p);
s16 fn_80123BF0(BUnit* p);
u8 fn_801076D0(BUnit* p);
u8 fn_8010779C(BUnit* p, f32 bio);
f32 fn_801072E4(BUnit* p);
f32 fn_80107444(BUnit* p);
f32 fn_801071C4(BUnit* p, s16 n);
void fn_800327D8(u8 a, int b, int c, int d);
void fn_80032CD0(BUnit* p, int a, int b, int c);
int fn_8012B120(BUnit* p, void* it);
int fn_8011F0E0(BUnit* p, void* it);
int fn_80111F5C(void* it);
void fn_80107C80(void* it, u8 c, int a, int b);
s8 fn_80123EF0(BUnit* p);
s8 fn_80122D30(BUnit* p);
s8 fn_8012269C(BUnit* p);
int fn_8011B77C(void* list, void* key);
void fn_801C6E64(f32 x, f32 y, const char* s, int a, int b, int c, int d, int e);
void fn_80032560(int x, int y, u8 k);
const char* fn_80118C44(void* job);
int fn_800CA3DC(const char* s, int n, f32 a);
void fn_800CB278(s16 x, s16 y, int c, const char* s, ...);
int fn_8007265C(int x, int y);
void fn_8007E154(void);
void fn_8007E174(void* tex, int a);
void fn_8007E164(void);
}
#define WIN_FRAME(p, h) \
    fn_800718F0(p, 0, 0, 1); \
    fn_800718D0(0, 0x24, 0x108, h, ((WSub*)p->xf4)->b8, 0x9a); \
    fn_8006E030(lbl_804CCD24); \
    fn_8006E068();
#define WIN_HP(p, x, y) \
    fn_80074EB4(x + 0x1e, y + 0x12, 0xcc, 0xa0); \
    fn_8006E068(); \
    fn_8006E030(lbl_804CCD24); \
    fn_800CB3A8(lbl_804CCD28, lbl_804CCCF4, x + 0x28, y, 9, 1, 0, lbl_80361390 + 0x11c, fn_800D0864(lbl_80361390 + 0x11f)); \
    { int v = p->x114; fn_800CB3A8(lbl_804CCD28, lbl_804CCCF4, x + 0x78, y, 1, 1, 0, lbl_80361390 + 0x125, v, fn_801237EC(p)); } \
    fn_8006E030(lbl_804CCD28);
#define WIN_ITEMS(p, y) \
    fn_8006E030(lbl_804CCD24); \
    for (i = 0; i < fn_80109174(&p->x110); i++) { \
        ((VObj*)&lbl_803E7290)->draw(0xd8, y, fn_801091E0(&p->x110, i)); \
    } \
    fn_8006E030(lbl_804CCD28);
#define WIN_HEAD(p, h) \
    WIN_FRAME(p, h) \
    WIN_HP(p, 0, 0x34) \
    WIN_ITEMS(p, 0x34)

extern "C" {
void fn_80032B88(BUnit* p, int kind, int x, int y, int dhp) {
    int hp;
    hp = dhp + p->x114;
    if (hp > fn_801237EC(p)) hp = fn_801237EC(p);
    if (hp < 0) hp = 0;
    fn_80031ED4(x + 0x16, y - 4, 0xde, 0x20);
    fn_8006E030(lbl_804CCD24);
    fn_80074EB4(x + 0x1e, y + 0x12, 0xcc, 0xa0);
    fn_8006E068();
    fn_8006E030(lbl_804CCD24);
    fn_800CB3A8(lbl_804CCD28, lbl_804CCCF4, x + 0x28, y, 9, 1, 0, lbl_80361390 + 0x11c, fn_800D0864(lbl_80361390 + 0x11f));
    fn_800CB3A8(lbl_804CCD28, lbl_804CCCF4, x + 0x78, y, 1, 1, 0, lbl_80361390 + 0x125, hp, fn_801237EC(p));
    fn_8006E030(lbl_804CCD28);
    fn_80032A34(kind, x, y);
    fn_8006E030(lbl_804CCD28);
}

void fn_80032FA8(BUnit* p) {
    int i;
    fn_800718F0(p, 0, 0, 1);
    fn_800718D0(0, 0x24, 0x108, 0x36, ((WSub*)p->xf4)->b8, 0x9a);
    fn_8006E030(lbl_804CCD24);
    fn_8006E068();
    WIN_HP(p, 0, 0x34)
    WIN_ITEMS(p, 0x34)
}

void fn_8003311C(BUnit* p, int dhp) {
    int i;
    WIN_HEAD(p, 0x70)
    fn_8006E068();
    fn_80032198(p, 0, 0x6c, dhp, 1);
}

void fn_800332B8(BUnit* p, int dhp) {
    int i;
    WIN_HEAD(p, 0x70)
    fn_8006E068();
    fn_80032198(p, 0, 0x6c, dhp, 0);
}

void fn_80033454(BUnit* p) {
    int i;
    WIN_HEAD(p, 0x70)
    fn_8006E068();
    fn_80031ED4(0x16, 0x68, 0xde, 0x20);
    fn_8006E030(lbl_804CCD24);
    fn_80074EB4(0x1e, 0x7e, 0xcc, 0xa0);
    fn_8006E068();
    fn_8006E030(lbl_804CCD24);
    fn_800CB3A8(lbl_804CCD28, lbl_804CCCF4, 0x28, 0x6c, 9, 1, 0, lbl_80361390 + 0x11c, fn_800D0864(lbl_80361390 + 0x11f));
    { int v = p->x114; fn_800CB3A8(lbl_804CCD28, lbl_804CCCF4, 0x78, 0x6c, 1, 1, 0, lbl_80361390 + 0x125, v, fn_801237EC(p)); }
}

void fn_80033930(BUnit* p) {
    int i;
    WIN_HEAD(p, 0x56)
    fn_8006E068();
    fn_800CB3A8(lbl_804CCD28, lbl_804CCCF4, 0x28, 0x50, 9, 1, 0, lbl_80361390 + 0x11c, fn_800D0864(lbl_80361390 + 0x190));
    fn_800CB3A8(lbl_804CCD28, lbl_804CCCF4, 0x78, 0x50, 1, 1, 0, lbl_80361390 + 0x184, fn_8012401C(p));
}

void fn_80033B18(BUnit* p) {
    int i;
    WIN_HEAD(p, 0x56)
    fn_8006E068();
    fn_800CB3A8(lbl_804CCD28, lbl_804CCCF4, 0x28, 0x50, 9, 1, 0, lbl_80361390 + 0x11c, fn_800D0864(lbl_80361390 + 0x199));
    fn_800CB3A8(lbl_804CCD28, lbl_804CCCF4, 0x78, 0x50, 1, 1, 0, lbl_80361390 + 0x184, fn_80124144(p));
}

void fn_80033D00(BUnit* p, const char* key) {
    int i;
    WIN_HEAD(p, 0x94)
    fn_80032334(p, 0, 0x50, fn_800D0864(key));
}

void fn_800341A0(BUnit* p) {
    u8 buf[8];
    int y;
    int k;
    u8* bb;
    Item* it;

        Item* q;
    u8* b;
    int i;

    fn_800718F0(p, 0, 0, 0);
    it = p->arr1bc;
    b = buf;
    q = it;
    for (i = 0; i < 7; i++) {
        if (q->data == 0) break;
        *b = fn_8012B120(p, q->data);
        q++;
        b++;
    }
    fn_800718D0(0, 0x24, 0x108, i * 0x1c + 0x18, ((WSub*)p->xf4)->b8, 0x9a);
    fn_8006E030(lbl_804CCD24);
    bb = buf;
    y = 0x34;
    for (k = 0; k < 7;) {
        if (it == 0 || it->data == 0) break;
        fn_80107C80(it, *bb, 0x1c, y);
        k++;
        y += 0x1c;
        it++;
        bb++;

    }
}

void fn_80034294(BUnit* p, BUnit* o) {
    u8 buf[8];
    int y;
    int k;
    u8* bb;
    Item* it;

        Item* q;
    u8* b;
    int i;

    fn_800718F0(p, 0, 0, 1);
    it = p->arr1bc;
    b = buf;
    q = it;
    for (i = 0; i < 7; i++) {
        if (q->data == 0) break;
        *b = fn_8011F0E0(o, q);
        q++;
        b++;
    }
    fn_800718D0(0, 0x24, 0x108, i * 0x1c + 0x18, ((WSub*)p->xf4)->b8, 0x9a);
    fn_8006E030(lbl_804CCD24);
    bb = buf;
    y = 0x34;
    for (k = 0; k < 7;) {
        if (it == 0 || it->data == 0) break;
        fn_80107C80(it, *bb, 0x1c, y);
        k++;
        y += 0x1c;
        it++;
        bb++;

    }
}

void fn_80034390(BUnit* p) {
    u8 buf[8];
    int y;
    int k;
    u8* bb;
    Item* it;

        Item* q;
    u8* b;
    int i;

    fn_800718F0(p, 0, 0, 1);
    it = p->arr1bc;
    b = buf;
    q = it;
    for (i = 0; i < 7; i++) {
        if (q->data == 0) break;
        *b = fn_80111F5C(q);
        q++;
        b++;
    }
    fn_800718D0(0, 0x24, 0x108, i * 0x1c + 0x18, ((WSub*)p->xf4)->b8, 0x9a);
    fn_8006E030(lbl_804CCD24);
    bb = buf;
    y = 0x34;
    for (k = 0; k < 7;) {
        if (it == 0 || it->data == 0) break;
        fn_80107C80(it, *bb, 0x1c, y);
        k++;
        y += 0x1c;
        it++;
        bb++;

    }
}

void fn_80034484(BUnit* p, int v) {
    int i;
    WIN_HEAD(p, 0x6c)
    fn_8006E068();
    fn_800CB3A8(lbl_804CCD28, lbl_804CCCF4, 0x28, 0x50, 1, 1, 0, lbl_80361390 + 0x1a0, fn_800D0864(lbl_80361390 + 0x199), fn_80124144(p));
    fn_800CB3A8(lbl_804CCD28, lbl_804CCCF4, 0x92, 0x50, 1, 1, 0, lbl_80361390 + 0x1a0, fn_800D0864(lbl_80361390 + 0x1b0), v);
    fn_800CB3A8(lbl_804CCD28, lbl_804CCCF4, 0x28, 0x6c, 1, 1, 0, lbl_80361390 + 0x1a0, fn_800D0864(lbl_80361390 + 0x13d), fn_80123BF0(p));
}

void fn_80034964(BUnit* p, int v) {
    int i;
    WIN_HEAD(p, 0x56)
    fn_8006E068();
    fn_800CB3A8(lbl_804CCD28, lbl_804CCCF4, 0x28, 0x50, 1, 1, 0, lbl_80361390 + 0x1a0, fn_800D0864(lbl_80361390 + 0x1b0), v);
}

void fn_80034B28(BUnit* p) {
    int i;
    WIN_HEAD(p, 0x36)
    WIN_ITEMS(p, 0x34)
}

void fn_80034CF8(BUnit* p) {
    WIN_FRAME(p, 0x70)
    fn_800327D8(fn_801076D0(p), 0, 0x34, 0);
    fn_8006E068();
    f32 bio = fn_801071C4(p, fn_801072E4(p));
    fn_800327D8(fn_8010779C(p, bio), 0, 0x6c, 1);
}

void fn_80034DB8(BUnit* p) {
    WIN_FRAME(p, 0x70)
    fn_800327D8(fn_801076D0(p), 0, 0x34, 0);
    fn_8006E068();
    f32 bio = fn_801071C4(p, fn_80107444(p));
    fn_800327D8(fn_8010779C(p, bio), 0, 0x6c, 1);
}

void fn_80034E78(BUnit* p) {
    WIN_FRAME(p, 0x70)
    fn_80032CD0(p, 0, 0x34, -1);
    fn_8006E068();
    fn_80032CD0(p, 0, 0x6c, 0x1e);
}

void fn_80034F08(BUnit* p, int dhp) {
    int i;
    WIN_HEAD(p, 0x70)
    fn_8006E068();
    fn_80032198(p, 0, 0x6c, dhp, 0);
}

void fn_800350A4(BUnit* p, int dhp) {
    int v;
    WIN_FRAME(p, 0x70)
    v = fn_801076D0(p);
    WIN_HP(p, 0, 0x34)
    fn_80032A34(v, 0, 0x34);
    fn_8006E068();
    f32 bio = fn_801071C4(p, fn_801072E4(p));
    fn_80032B88(p, fn_8010779C(p, bio), 0, 0x6c, dhp);
}

void fn_80035218(int x, int y, const char* a, const char* b, const char* c) {
    int w = fn_8007265C(x, y);
    fn_8007E154();
    fn_8007E174(0, 0x13);
    fn_8007E164();
    if (a) {
        const char* s = fn_800D0864(a);
        fn_800CB278(x + (w - fn_800CA3DC(s, -1, lbl_804CCD28)) / 2, y + 0x16, 2, s);
    }
    if (b) {
        const char* s = fn_800D0864(b);
        fn_800CB278(x + (w - fn_800CA3DC(s, -1, lbl_804CCD28)) / 2, y + 0x38, 8, s);
    }
    if (c) {
        c = fn_800D0864(c);
        fn_800CB278(x + (w - fn_800CA3DC(c, -1, lbl_804CCD28)) / 2, y + 0x50, 8, c);
    }
}

}
