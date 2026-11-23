/* Map-position helpers and PersonData-style getters, 80118B20..80118F00. */
#include "game/rH_80112B48/types.h"
#pragma auto_inline off

extern "C" {

extern char* fn_800D0864(void*);
extern char* fn_800C4058(void*);
#if TARGET_PC
extern FE10_PROTO void * fn_80076F54(void*);
extern FE10_PROTO void fn_8011843C(void*, Vec*, Vec*, ptr32<const void>, ptr32<const void>, f32, f32);
#else
extern int fn_80076F54(void*);
extern void fn_8011843C(void*, Vec*, Vec*, void*, void*, f32, f32);
#endif
extern void fn_8031356C(Vec*, Vec*, Vec*);
extern void fn_8001EACC(Vec*, Vec*, Vec*);
extern f32 fn_80113F00(void*, f32, f32);
extern void* memset(void*, int, u32);
extern f32 lbl_804CDCB8;
extern f32 lbl_804CDCC0;

Vec* fn_80118B20(void* o, Vec* ret, void* x, void* y, f32 fx, f32 fy) {
    Vec a;
    Vec b;
    Vec c;
    Vec k;
    fn_8011843C(o, &a, &b, x, y, fx, fy);
    fn_8031356C(&a, &b, &c);
    k.x = lbl_804CDCB8;
    k.y = lbl_804CDCB8;
    k.z = lbl_804CDCC0;
    fn_8001EACC(&k, &c, ret);
    return ret;
}

Vec fn_80118B94(void* o, s8 x, s8 y) {
    Vec v;
    v.x = 0.5f + (f32)x;
    v.y = 0.5f + (f32)y;
    v.z = fn_80113F00(o, (f32)x, (f32)y);
    return v;
}

struct Info {
    char* name;
    void* unk4;
    void* unk8;
    void* unkC;
    void* unk10;
};

char* fn_80118C44(Info* p) {
    if (p->unk4) {
        return fn_800D0864(p->unk4);
    }
    if (fn_80076F54(p->unk10)) {
        return fn_800C4058(p->unk10);
    }
    return p->name;
}

char* fn_80118CA4(Info* p) {
    if (p->unk8) {
        return fn_800D0864(p->unk8);
    }
    if (p->unk4) {
        return fn_800D0864(p->unk4);
    }
    if (fn_80076F54(p->unk10)) {
        return fn_800C4058(p->unk10);
    }
    return p->name;
}

char* fn_80118D1C(Info* p) {
    return fn_800D0864(p->unkC);
}

struct Slot {
    u8* item;
    u8 uses;
    u8 flags;
};

static inline void SlotInit(Slot* s, u8* item, u8 uses, u8 flags) {
    s->item = item;
    s->uses = uses;
    s->flags = flags;
    if (item) {
        s->flags |= (item[0x20] == 0);
    }
}

struct JobA {
    u8 pad0[0x22];
    u8 a[8];
    u8 b[8];
    u8 pad32[0x4C - 0x32];
    Slot slots[18];
    u8 padDC[0xFC - 0xDC];
};

u8* fn_80118DE8(Info* p) {
    return (u8*)p->name + 4;
}

char* fn_80118F00(Info* p) {
    if (fn_80076F54(p->unk4)) {
        return fn_800D0864(p->unk4);
    }
    return p->name;
}

}
