/* Assorted callbacks: scroll fade, unit path buffer, marking effects, phase banner start, block switches. */
#include "game/rL_80133EB4/map3d.h"
#pragma auto_inline off
#pragma use_lmw_stmw on

extern "C" {

extern u8 lbl_803CAB38[];
extern u8 lbl_803698F0[];
extern void* lbl_804CB868;
extern void* lbl_804CB86C;
extern char lbl_80369B30[];

extern f32 fn_8017F68C(f32, f32, f32, f32, int);
extern void fn_80010788(int, int, void*, void*);
extern void fn_8013EED0(void*);
extern void fn_8017F480(void*, void*, int);
extern void fn_8013EA08(int, int, void*, f32);
extern int fn_80060780(void*);
extern void* fn_800E4060(void*, void*);
extern Mesh* fn_80135934(MapModel*, int, u32, u32);
extern void fn_801CA33C(Mesh*, int, int);
extern void fn_80272624(MapEntry18*, f32);

struct FadeP { u8 pad0[0x30]; int t; f32 v; };

void fn_8013F13C(FadeP* p) {
    p->t++;
    if (p->t <= 8) p->v = fn_8017F68C(0.0f, 1.0f, p->t, 8.0f, 6);
    fn_80010788(3, 0x91, fn_8013EED0, p);
}

void fn_8013EE5C(
#if TARGET_PC
int a, int b, fe10_rgba srcv
#else
int a, int b, void* src
#endif
) {
#if TARGET_PC
    void* src = &srcv;
#endif
    u32 buf[4];
    int i;
    for (i = 0; i < 4; i++) fn_8017F480(&buf[i], src, 4);
    fn_8013EA08((s8)a, (s8)b, buf, 1.0f);
}

void fn_8014021C(s8* p, u8* out) {
    int i;
    for (i = 0; i < p[0x100]; i++) {
        s8 dx = (p + i)[1] - p[i];
        s8 dy = (p + i)[0x41] - (p + i)[0x40];
        if (dx < 0) {
            *out++ = 1;
        } else if (dx > 0) {
            *out++ = 2;
        } else if (dy < 0) {
            *out++ = 8;
        } else if (dy > 0) {
            *out++ = 4;
        }
    }
    *out = 0x40;
}

void fn_801408C0(void* parent) {
    if (fn_80060780(lbl_803CAB38)) {
        lbl_804CB868 = fn_800E4060(lbl_803698F0, parent);
        lbl_804CB86C = fn_800E4060(lbl_803698F0 + 0xD, parent);
        *(u32*)(*(u8**)((u8*)lbl_804CB868 + 0x30) + 0x18) |= 100;
        *(u32*)(*(u8**)((u8*)lbl_804CB86C + 0x30) + 0x18) |= 100;
    }
}

static inline MapEntry18* FindEntry(MapModel* mm, Mesh* key) {
    u8* e;
    int i;
    if (key) {
        e = (u8*)mm->lights;
        for (i = 0; i < 16; i++) {
            if (*(Mesh**)(e + 0x14) == key) return &mm->lights[i];
            e += 0x18;
        }
    }
    return 0;
}

#pragma use_lmw_stmw off
} /* extern "C" */
