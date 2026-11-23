#include "game/rF_8017F400/types.h"

#pragma auto_inline off

extern "C" {

typedef struct MFlags {
    u32 pad0 : 11;
    u32 b11 : 1;
    u32 pad12 : 7;
    u32 b19 : 1;
    u32 b20 : 1;
    u32 pad21 : 1;
    u32 b22 : 1;
    u32 pad23 : 4;
    u32 b27 : 1;
    u32 pad28 : 4;
} MFlags;

typedef struct MInner {
    u8 pad[0xB8];
    union {
        MFlags f;
        u32 w;
    };
} MInner;

typedef struct MOuter {
    u8 pad[0x10];
    MInner* in;
} MOuter;

typedef struct MRect {
    u8 x0;
    u8 pad1[3];
    u8 x4, x5, x6, x7;
} MRect;

extern void* fn_80007F3C(void* p);
#if TARGET_PC
#if TARGET_PC
extern FE10_PROTO int fn_80014E24(void* a, const char*, void*, void*);
#else
extern FE10_PROTO void fn_80014E24(void* a, p32arg, p32arg, p32arg);
#endif
#if TARGET_PC
extern FE10_PROTO void fn_80014F64(void* a, const char*, void*);
#else
extern FE10_PROTO void fn_80014F64(void* a, p32arg, p32arg);
#endif
#else
extern void fn_80014E24(void* a, int b, int c, int d);
extern void fn_80014F64(void* a, int b, int c);
#endif
extern void fn_8000866C(void* p, f32 v);
extern void fn_80007C58(void* p);
extern void* fn_8013B9A8(void);
extern void fn_8013B2B8(void* p);
extern void fn_8013B8D0(void* p);
extern void fn_80008F10(void* p, u8 r, u8 g, u8 b);
extern void fn_80008F20(void* p, u8 a);
extern void fn_80312344(void* a, void* b);

#if TARGET_PC
int fn_801CA138(u8* p, const char* a, void* b, void* c) {
    return fn_80014E24(fn_80007F3C(p + 4), a, b, c);
}
#else
void fn_801CA138(u8* p, int a, int b, int c) {
    fn_80014E24(fn_80007F3C(p + 4), a, b, c);
}
#endif

void fn_801CA190(
#if TARGET_PC
u8* p, const char* a, void* b
#else
u8* p, int a, int b
#endif
) {
    fn_80014F64(fn_80007F3C(p + 4), a, b);
}

u32 fn_801CA1D8(MOuter* m) {
    return m->in->f.b22;
}

u32 fn_801CA1E8(MOuter* m) {
    MInner* in = m->in;
    if (in->w & 0x10) {
        return 0;
    }
    if (in->w & 0x800) {
        return 1;
    }
    return in->f.b19;
}

u32 fn_801CA218(MOuter* m) {
    return m->in->f.b19;
}

u32 fn_801CA228(MOuter* m) {
    MInner* in = m->in;
    if (in->w & 0x10) {
        return 0;
    }
    return in->f.b11;
}

BOOL fn_801CA248(MRect* r) {
    return (r->x0 & 0xC) != 0;
}

BOOL fn_801CA260(MRect* r) {
    return (r->x0 & 0xC) == 0;
}

BOOL fn_801CA274(MRect* r, int x, int y) {
    if (x >= (s8)r->x4 && x <= (s8)r->x6 && y >= (s8)r->x5 && y <= (s8)r->x7) {
        return TRUE;
    }
    return FALSE;
}

void fn_801CA2C4(u8* p) {
    fn_8000866C(p + 0x14, 0.0f);
    fn_80007C58(p + 0x14);
}

void fn_801CA300(u8* p) {
    fn_8000866C(p + 0x14, -1.0f);
    fn_80007C58(p + 0x14);
}

void fn_801CA33C(u8* p, u8 a, int b) {
    p[0xCD] = a;
    if (b != 0) {
        void* m = fn_8013B9A8();
        if (m != NULL) {
            fn_8013B2B8(m);
            fn_8013B8D0(m);
        }
    }
}

void fn_801CA388(
#if TARGET_PC
u8* p, fe10_rgba cv
#else
u8* p, u8* c
#endif
) {
#if TARGET_PC
    u8* c = (u8*)&cv;
#endif
    u8* t = p + 0x14;
    fn_80008F10(t, c[0], c[1], c[2]);
    fn_80008F20(t, c[3]);
}

void fn_801CA3DC(u8* p, u8 a) {
    fn_80008F20(p + 0x14, a);
}

void fn_801CA3E4(MRect* r, int a) {
    if (a != 0) {
        r->x0 &= ~4;
    } else {
        r->x0 |= 4;
    }
}

void fn_801CA40C(MRect* r, int a) {
    if (a != 0) {
        r->x0 |= 0x40;
    } else {
        r->x0 &= ~0x40;
    }
}

void fn_801CA434(u8* p, void* a) {
    fn_80312344(a, p + 0x24);
}

}
