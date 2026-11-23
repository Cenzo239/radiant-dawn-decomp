/* Tail-call stubs and small procs */
#include "game/rN_8025EEF0/calls.h"

#pragma use_lmw_stmw on

extern "C" {

int fn_8025F6B8(const char* s, int mode);
int fn_8025F6A0(const char* s) { return fn_8025F6B8(s, 0); }
int fn_8025F6A8(const char* s) { return fn_8025F6B8(s, 1); }
int fn_8025F6B0(const char* s) { return fn_8025F6B8(s, 2); }

/* Rect from a stored s16 box */
struct Box { s16 x, y, w, h; };
void fn_80263B4C(void*, Box* b) { fn_803080DC(b->x, b->y, b->w, b->h); }
void fn_8026D458(void*, Box* b) { fn_803080DC(b->x, b->y, b->w, b->h); }
void fn_80272F94(void*, Box* b) { fn_803080DC(b->x, b->y, b->w, b->h); }
void fn_80287834(void*, Box* b) { fn_803080DC(b->x, b->y, b->w, b->h); }

void fn_8026A114(void) {}

#if TARGET_PC
FE10_PROTO void fn_801C6D2C(ptr32<const void>, void* b, int c, ptr32<const void>, int d);
#else
void fn_801C6D2C(void* a, void* b, int c, void (*cb)(void), int d);
#endif
void fn_801BA3D8(int a, void* b);
extern u8 lbl_804CC031;
extern u8 lbl_804CC038;
extern u8 lbl_803CAB38[];
extern u8 lbl_803CA870[];

void fn_8026A134(void) { lbl_804CC031++; }

void fn_8026A118(u8* p) { fn_801C6D2C(*(void**)(p + 0x30), p, 2, fn_8026A134, 0); }

void fn_8026A144(void) { lbl_804CC031--; }
void fn_8026A154(void) { lbl_804CC031++; }

void fn_8026A164(u8* p) {
    void* v = *(void**)(p + 0x30);
    *(void**)((u8*)fn_80060728(lbl_803CAB38) + 0x28) = v;
    fn_801BA3D8(*(*(u8**)(*(u8**)(p + 0x30) + 0xF4) + 8), p);
}

void fn_8026A1BC(void) { lbl_804CC031--; }

int fn_8010E2F4(void* p);
extern u8* lbl_804CB814;
extern u8 lbl_80391B30[];
extern u8 lbl_80391C0C[];

struct SlotMenuInit {
    u8 pad[0x30];
    void* vt;
    int m34, m38, m3C, m40, m44;
    u8 m48, m49, m4A, m4B;
    s16 m4C, m4E, m50, m52, m54, m56;
};

void* fn_8026A1CC(void* parent) {
    if (fn_8010E2F4(lbl_804CB814 + 0x60) == 0 && fn_8010E2F4(lbl_804CB814 + 0x6C) == 0 && fn_8010E2F4(lbl_804CB814 + 0x78) == 0) {
        return 0;
    }
    SlotMenuInit* m = (SlotMenuInit*)fn_80081194(lbl_80391B30, parent);
    if (m != 0) {
        m->vt = lbl_80391C0C;
        m->m34 = 0;
        m->m38 = 0;
        m->m3C = 0;
        m->m40 = 0;
        m->m44 = 0;
        m->m48 = 1;
        m->m49 = 0;
        m->m4A = 1;
        m->m4C = 0;
        m->m4E = 0;
        m->m50 = 0;
        m->m52 = 0;
        m->m54 = -0x8000;
        m->m56 = -0x8000;
    }
    return m;
}

void fn_80253EE4(void* p, f32 v);
extern u8 lbl_80391E38[];
int fn_8026A2A0(void) {
    *(int*)(lbl_803CA870 + 0x18) = 0;
    fn_80253EE4(lbl_80391E38, 0.0f);
    return 1;
}

int fn_8026A2E0(void) { return 1; }

extern char lbl_804CAAD0[8];
extern char lbl_804CAAD8[8];
extern char lbl_804CAAE0[8];
const char* fn_8026A2E8(void) { return fn_800D0864(lbl_804CAAD0); }
int fn_8026A2F0(void) {
    *(int*)(lbl_803CA870 + 0x18) = 1;
    return 5;
}
int fn_8026A308(void) { return 0; }
const char* fn_8026A310(void) { return fn_800D0864(lbl_804CAAD8); }
const char* fn_8026A318(void) { return fn_800D0864(lbl_804CAAE0); }
void fn_8026A320(void) { *(int*)(lbl_803CA870 + 0x18) = 0; }
void fn_8026A334(void) { lbl_804CC038 = 0; }

int fn_802457BC(void* p);
void fn_8026A340(void) {
    int n = fn_802457BC(fn_8024BC94());
    if (n > 6) {
        n = 6;
    }
    if (++lbl_804CC038 > n) {
        lbl_804CC038 = 0;
    }
}

extern u8 lbl_80391E80[];
extern u8 lbl_80392068[];
void* fn_8026B958(void* parent) { return fn_80081194(lbl_80391E80, parent); }
void fn_8026B968(void) {}
void fn_8026C178(void) {}
void* fn_8026C1B8(void* parent) { return fn_80081194(lbl_80392068, parent); }

void fn_8026D01C(void** p, u8* a) {
    p[0] = a;
    p[1] = a + 8;
}


void fn_8027D948(void* p);
void fn_8027DA1C(void* p);
void fn_8027DF84(void* p);
extern u8 lbl_80392988[];
void fn_8027DDD4(void* p) { fn_8027D948(p); }
void fn_8027DDFC(void* p) { fn_8027DA1C(p); }
void fn_8027E810(u8* p) {
    if (p[0x30] != 0) {
        fn_8027DF84(p);
    }
}
void* fn_8027E824(void* parent) { return fn_80081050(lbl_80392988, parent); }

}
