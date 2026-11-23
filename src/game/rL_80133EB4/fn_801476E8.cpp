#include "game/rL_80133EB4/map3d.h"
#pragma auto_inline off
#pragma use_lmw_stmw on
extern "C" {
extern u8 lbl_804CB870, lbl_804CB871, lbl_804CB830;
extern s16 lbl_804CB872, lbl_804CB874;
extern u8* lbl_80413F00[];
extern u8 lbl_80413EA0[];
extern u8 lbl_803EC898[];
extern u8 lbl_804CA734;
extern char lbl_80369BA8[];
extern void DCFlushRange(void*, u32);
extern void fn_8017F464(void*, int, int);
extern void* fn_80078D9C(int, const char*, int);
extern void fn_80078E24(void*);
extern int fn_8011799C(void*, int, int);
extern void fn_80312D2C(void*, f32, f32, f32, f32, f32, f32, f32, f32);
extern void fn_803128AC(void*, f32, f32, f32);
extern void fn_80019D9C(void*);
extern void fn_80312378(void*, void*, void*);
extern int fn_80011E28(void);
extern int fn_80011F38(void);
extern int fn_80011EB4(void);
extern int fn_80011FC4(void);
extern void fn_80022254(void*, int);
extern void fn_80307F10(void*, int, int);
extern void fn_80021F7C(int, int, int, int);
extern void fn_80021CB4(int, int, int, int);
extern void fn_80021E20(int, int, int, int, int);
extern void fn_80021D18(int, int, int, int, int, int);
extern void fn_80021E8C(int, int, int, int, int);
extern void fn_80021D9C(int, int, int, int, int, int);

void fn_801478F4(u8* src);

int fn_801476E8(void) {
    if (lbl_804CB870 == 0) return 0;
    lbl_804CB871 = (u8)(lbl_804CB871 + 1) % 3;
    if (lbl_804CB830 == 0) {
        fn_801478F4(0);
    } else {
        u8* b = (u8*)fn_80078D9C(-lbl_804CB874 * lbl_804CB872, lbl_80369BA8, 0);
        u32 c = (lbl_804CA734 << 8) + lbl_804CA734 + (lbl_804CA734 << 16) + (lbl_804CA734 << 24);
        switch (lbl_804CB830) {
        case 1:
        case 2:
        {
            int x;
            int y;
            u8* p;
            fn_8017F464(b, c, lbl_804CB874 * lbl_804CB872);
            p = b + lbl_804CB872;
            for (y = 1; y < lbl_804CB874 - 1; y++) {
                p++;
                for (x = 1; x < lbl_804CB872 - 1; x++, p++) {
                    if ((lbl_803EC898 + 0x200D)[(s8)(y - 1) * 0x40 + (s8)(x - 1)]) *p = 0xFF;
                }
                p++;
            }
            break;
        }
        case 3:
        {
            u8* p;
            int y;
            fn_8017F464(b, c, lbl_804CB874 * lbl_804CB872);
            p = b + lbl_804CB872;
            for (y = 1; y < lbl_804CB874 - 1; y++) {
                int x;
                p++;
                for (x = 1; x < lbl_804CB872 - 1; x++, p++) {
                    if (fn_8011799C(lbl_803EC898, (s8)(x - 1), (s8)(y - 1))) *p = 0xFF;
                }
                p++;
            }
            break;
        }
        }
        fn_801478F4(b);
        fn_80078E24(b);
    }
    return 1;
}


void fn_80147B58(void) {
    u8 trans[0x30];
    u8 proj[0x30];
    u8 mtx[0x30];
    int a, b, c, d;
    if (lbl_804CB830 == 0) return;
    fn_80312D2C(proj, 64.0f, -64.0f, -64.0f, 64.0f, 0.5f, 0.5f, 0.5f, 0.5f);
    fn_803128AC(trans, -63.0f, -63.0f, 0.0f);
    fn_80019D9C(mtx);
    fn_80312378(trans, mtx, mtx);
    fn_80312378(proj, mtx, mtx);
    a = fn_80011E28();
    b = fn_80011F38();
    c = fn_80011EB4();
    d = fn_80011FC4();
    fn_80022254(lbl_80413EA0 + lbl_804CB871 * 0x20, c);
    fn_80307F10(mtx, d, 1);
    fn_80021F7C(b, 1, 0, d);
    fn_80021CB4(a, b, c, 4);
    switch (lbl_804CB830) {
    case 1:
        fn_80021E20(a, 0xF, 0, 8, 0xF);
        fn_80021D18(a, 0, 0, 0, 1, 0);
        break;
    case 2:
        fn_80021E20(a, 0xC, 0xF, 8, 0);
        fn_80021D18(a, 0, 0, 0, 1, 0);
        break;
    case 3:
        fn_80021E20(a, 0xF, 0, 8, 0xF);
        fn_80021D18(a, 0, 0, 0, 1, 0);
        break;
    }
    fn_80021E8C(a, 7, 7, 7, 0);
    fn_80021D9C(a, 0, 0, 0, 1, 0);
}

void fn_80147EF4(int k) {
    u8* a = lbl_80413F00[(lbl_804CB871 + 2) % 3];
    u8* b = lbl_80413F00[(lbl_804CB871 + 1) % 3];
    u8* d = lbl_80413F00[lbl_804CB871];
    int m = 0x80 - k;
    int i;
    for (i = 0; i < 0x80; i++) {
        int j;
        for (j = 0; j < 0x40; j++) {
            *d++ = ((*a & 0xF) * k + (*b & 0xF) * m >> 7) + (((*a & 0xF0) * k + (*b & 0xF0) * m >> 7) & 0xF0);
            a++;
            b++;
        }
    }
    DCFlushRange(lbl_80413F00[lbl_804CB871], 0x2000);
}

extern u8 lbl_803CAB38[];
extern char lbl_80369B30[];
extern void* fn_8006074C(void*);
extern int fn_8024F7EC_(const char*);
extern s8 fn_8024F7EC(const char*);
extern int fn_80068424(void*, u8);
class Snd { public: virtual int v08(); virtual int v0C(); virtual int v10(); };
extern Snd* fn_8024F3FC(int);
#if TARGET_PC
extern FE10_PROTO void fn_80251838(int, p32arg, float);
#else
extern void fn_80251838(f32, int, int);
#endif
extern void* fn_800E3810(const char*, void*);
extern void fn_800E4904(void*, int, void*);
extern void fn_80147148(void*);
struct PhaseP { u8 pad[0x30]; int x30, x34; f32 x38, x3c; int pad40; int x44, x48; u8* x4c; };
void fn_8014715C(PhaseP* p) {
    void* m = fn_8006074C(lbl_803CAB38);
    const char* s;
    p->x30 = 0;
    p->x34 = 0;
    p->x38 = 0.0f;
    p->x3c = 0.0f;
    p->x44 = 0xF;
    p->x48 = 0x1E;
    if (fn_8024F7EC(lbl_80369B30 + 0x3F) == -1) {
        int k = fn_80068424(m, lbl_803CAB38[0x11]);
        if (k) {
            int i;
            for (i = 1; i < 4; i++) {
                Snd* o = fn_8024F3FC((s8)i);
                if (o == 0 || o->v10() == 0) {
                    fn_80251838(0.0f, (s8)i, k);
                    break;
                }
            }
        }
    }
    switch (lbl_803CAB38[0x11]) {
    case 0: s = lbl_80369B30; break;
    case 1: s = lbl_80369B30 + 0x10; break;
    case 2: s = lbl_80369B30 + 0x1F; break;
    case 3: s = lbl_80369B30 + 0x2E; break;
    default: s = 0; break;
    }
    p->x4c = (u8*)fn_800E3810(s, p);
    if (p->x4c) {
        fn_800E4904(p->x4c, 0, p);
        *(void**)(*(u8**)(p->x4c + 0x30) + 0xA0) = (void*)fn_80147148;
    }
}

struct Unit10 { u8 pad0[0x33]; u8 x33; u8 pad34[0xEC-0x34]; void* xec; u8 padf0[4]; u8* xf4; u8 padf8[0x10C-0xF8]; u32 x10c; u8 pad110[0x3F0-0x110]; };
extern Unit10* lbl_804CB810;
extern void fn_80083B78(void*);
extern f32 fn_8001EF30(f32, f32, f32, f32);
extern void fn_800F3F08(Unit10*, int);
extern void* memset(void*, int, u32);
extern u32 lbl_804CA730;
extern const u8 lbl_804CE140[2];
static inline Unit10* UnitAt(int i) {
    return i != 0 ? &lbl_804CB810[i - 1] : 0;
}
struct FadeP { u8 pad[0x60]; int x60; };
static inline void Mark(u8* on, u8* q) {
    while (*q != 0xFF) { on[*q] = 1; q++; }
}
void fn_8014830C(FadeP* p) {
    p->x60++;
    u8 list[2] = {1, 0xFF};
    u8 on[0xB];
    memset(on, (u8)lbl_804CA730, 0xB);
    Mark(on, list);
    {
        int i;
        for (i = 1; i <= 0xFE; i++) {
            Unit10* u = UnitAt((u8)i);
            if (u->xec && on[u->xf4[8]] && (u->x10c & 0x200)) {
                int a;
                if (u->x10c & 0x40) {
                    if (u->x33 == 0) continue;
                    a = fn_8001EF30(255.0f, 0.0f, 16.0f, p->x60);
                } else {
                    if ((s32)u->x33 == 0xFF) continue;
                    a = fn_8001EF30(0.0f, 255.0f, 16.0f, p->x60);
                }
                fn_800F3F08(u, a);
            }
        }
    }
    if (p->x60 == 0x10) fn_80083B78(p);
}
}
