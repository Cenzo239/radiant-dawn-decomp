/* functionally equal (check_regs: regs, 79 of 1396 words, registers only).
   Conversation room (E_ConversationRoomFe8): support pair list draw. Round 18, written from the asm;
   same skeleton as fn_80277E10 (wip). */
#include "game/rN_8025EEF0/roomdraw.h"

extern "C" {
extern s8 lbl_804CC098;
extern RC lbl_804CC0A0;
int fn_80291188(const char* a, const char* b);
const char* fn_800D0864(const char* id);

struct Fe8Item {
    char* a;        /* 0x00 first unit */
    char* b;        /* 0x04 second unit */
    int f8;
    int fC;
    int f10;
    int f14;
    int f18;
    int f1C;
    int k20;        /* flag ids for the C / B / A conversations */
    int k24;
    int k28;
};
struct Fe8St {
    void* flags;
    int n;
    Fe8Item* items;
    Room room;
};
#define ST ((Fe8St*)lbl_804CC074)

static inline int roomFlag(int k) {
    if (isProc(lbl_8037359C)) {
        return fn_80245368(((ConvSt*)lbl_804CC06C)->m8, k);
    }
    if (isProc(lbl_8037359C + 0x13)) {
        return fn_80245368(*(void**)lbl_804CC074, k);
    }
    return 0;
}
/* true when every pair this unit belongs to has its first conversation seen */
static inline BOOL allSeen(const char* nm) {
    int i;
    for (i = 0; i < ST->n; i++) {
        Fe8Item* e = &ST->items[i];
        if (fn_80291188(nm, e->a) == 0 || fn_80291188(nm, e->b) == 0) {
            if (roomFlag(e->k20) == 0) return 0;
        }
    }
    return 1;
}
static inline void pB(int x, int y, f32 w, f32 h, int i) {
    GXC c;
    GXC t;
    f32 w2;
    f32 h2;
    { const u8* p = fn_800CD204(1); c.r = p[0]; c.g = p[1]; c.b = p[2]; c.a = 0xFF; }
    texSize(i, w2, h2);
    { void* tx = roomTex();
    *(u32*)&t = *(u32*)&c;
    fn_801BC88C(x, y, x + w, y + h, 0.0f, 0.0f, w2, h2, tx, i, &t, 0x11, 0); }
}

void fn_8027970C(void) {
    int x;
    int y;
    int w;
    int h;
    int i;
    int tx;
    x = roomData()->m40;
    y = roomData()->m42;
    w = roomData()->m44;
    h = roomData()->m46;
    if (roomData()->m54 > 0) {
        roomData()->m54--;
        roomData()->m50 = fn_8017F68C(0.0f, 1.0f, 5 - roomData()->m54, 5.0f, 0);
    }
    fn_8007E154();
    fn_8007E4E4(roomData()->m48, roomData()->m4C, 100.0f, roomData()->m50);
    fn_8007E164();
    fn_801BCA5C(-1.0f);
    pB(x + 4, y + 3, w - 8, h - 6, 0xC);
    fn_801BCA5C(-1.0f);
    fn_80070688(x, y, w, h);
    fn_801BCA5C(-1.0f);
    if (!lbl_804CC098) {
        lbl_804CC098 = 1;
    }
    {
        f32 hh = 196.0f * roomData()->m50;
        int yy = (int)(roomData()->m4C - hh * 0.5f);
        lbl_804CC0A0.x = 0;
        lbl_804CC0A0.y = yy;
        lbl_804CC0A0.w = 0x260;
        lbl_804CC0A0.h = (int)hh;
    }
    fn_8007E154();
    fn_8007E74C(fn_80272F94, &lbl_804CC0A0);
    fn_8007E164();
    {
    f32 sc;
    f32 fr;
    sc = roomData()->m14;
    fr = sc - (f32)(int)sc;
    for (i = 0; i < 8; i++) {
        tx = x + 0xC;   /* inside the loop: hoisted after the pool base, as in the original */
        int ty = (int)(28.0f * ((f32)i - fr) + (f32)(y + 0x1C));
        int n = (int)(sc + (f32)i);
        Fe8Item* it;
        int b;
        u8 c;
        int px;
        BOOL r;
        if (n >= ST->n) break;
        fn_80074EB4(tx, ty + 0x12, 0x180, 0x80);
        fn_801BCA5C(-1.0f);
        px = tx + 8;
        it = &ST->items[n];
        b = roomFlag(it->k28) != 0;
        r = allSeen(it->a);
        c = 0x14;
        if (!r) c = b;
        fn_800CB3A8(px, ty, c, 1, 0, 1.0f, 0.0f, fn_800D0864(it->a));
        px = fn_800CA3DC(fn_800D0864(it->a), -1, 1.0f) + px + 6;
        fn_800CB3A8(px, ty, b, 1, 0, 1.0f, 0.0f, lbl_8037359C + 0x46);
        px = fn_800CA3DC(fn_800D0864(lbl_8037359C + 0x46), -1, 1.0f) + px + 6;
        r = allSeen(it->b);
        c = 0x14;
        if (!r) c = b;
        fn_800CB3A8(px, ty, c, 1, 0, 1.0f, 0.0f, fn_800D0864(it->b));
        px = tx + 0x168;
        if (it->fC) {
            fn_800CB3A8(px, ty, roomFlag(it->k20) != 0, 1, 0, 1.0f, 0.0f, lbl_8037359C + 0x48);
            px -= 0x1A;
        }
        if (it->f8) {
            fn_800CB3A8(px, ty, roomFlag(it->k20) != 0, 1, 0, 1.0f, 0.0f, lbl_8037359C + 0x48);
            px -= 0x1A;
        }
        if (it->f14) {
            fn_800CB3A8(px, ty, roomFlag(it->k24) != 0, 1, 0, 1.0f, 0.0f, lbl_8037359C + 0x4A);
            px -= 0x1A;
        }
        if (it->f10) {
            fn_800CB3A8(px, ty, roomFlag(it->k24) != 0, 1, 0, 1.0f, 0.0f, lbl_8037359C + 0x4A);
            px -= 0x1A;
        }
        if (it->f1C) {
            fn_800CB3A8(px, ty, roomFlag(it->k28) != 0, 1, 0, 1.0f, 0.0f, lbl_8037359C + 0x4C);
            px -= 0x1A;
        }
        if (it->f18) {
            fn_800CB3A8(px, ty, roomFlag(it->k28) != 0, 1, 0, 1.0f, 0.0f, lbl_8037359C + 0x4C);
        }
        fn_801BCA5C(1.0f);
    }
    }
    fn_8007E154();
    fn_8007E7B4();
    fn_8007E164();
    fn_801BCA5C(-1.0f);
    fn_80072ACC(x + 0x82, roomData()->m34 + 0xC, 0xEC, 0x17, 0x19, 0x64, 1);
    fn_801BCA5C(-1.0f);
    fn_800712E8(roomData()->m32, roomData()->m34, 1);
    fn_801BCA5C(2.0f);
    fn_8017980C(roomData()->m58, (int)((f32)(x + w - 0x16) + roomData()->m48), (int)((f32)(y + 0xC) + roomData()->m4C), h - 0x18);
    fn_80179888(roomData()->m58, (int)(28.0f * curF()));
    fn_8017985C(roomData()->m58, ST->n * 0x1C);
    fn_80179864(roomData()->m58, 0xC4);
    fn_80179A7C(roomData()->m58, (u8)*(s16*)(lbl_804CC074 + 0xEC));
    fn_80179854(roomData()->m58, 95.0f);
    if (1.0f == roomData()->m50) {
        fn_80179A84(roomData()->m58);
    }
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 100.0f, 1.0f);
    fn_8007E164();
}

}
