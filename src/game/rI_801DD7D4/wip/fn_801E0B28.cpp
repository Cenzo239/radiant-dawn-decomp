/* wip near misses for fn_801E0B28.cpp (whole file kept so declarations stay together):
   fn_801E1454: 8 of 82 words differ
   fn_801E2104: size 0xF8, want 0x100; 1 wrong reference(s); 12 of 62 words differ
   fn_801E1BB0: 3 of 15 words differ
   fn_801E1BEC: 6 of 16 words differ
*/
#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/vobj.h"
#pragma auto_inline off

extern "C" {

void fn_80079210(void*);
int fn_800D0864(int);
void fn_801D7014(int, int, int, int, int);
void fn_801D772C(int, int, int);
void fn_801D8DBC(int, int, int);
void fn_801D8F10(int, int, int);
void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E174(int, int);
void fn_8007E720(f32);
void fn_8007E74C(void*, void*);
void fn_8007E7B4(void);
int fn_800CB0FC(int, f32);
void fn_801E6DA0(int, int, int, const char*, ...);
void fn_800800D4(int);
void fn_80080388(f32, f32, f32, f32);
void fn_80080508(void*);
void fn_80080308(void);
void fn_803080DC(int, int, int, int);

extern char lbl_8038C950[];
extern char lbl_8038C960[];
extern char lbl_8038C9A8[];
extern char lbl_8038C98C[];
extern char lbl_8038C970[];
extern char lbl_8036ED78[];
extern char lbl_8038C294[];

typedef struct GXColor { u8 r, g, b, a; } GXColor;

void* fn_801E0B28(void* p, int del) {
    if (p != NULL && del > 0) {
        fn_80079210(p);
    }
    return p;
}

int fn_801E0EC0(void) { return 0x40; }
int fn_801E0EC8(void) { return 0x1c; }
int fn_801E0ED0(void) { return 0x86; }

void* fn_801E0ED8(void* p, int del) {
    if (p != NULL && del > 0) {
        fn_80079210(p);
    }
    return p;
}

s16 fn_801E0F18(VO4* o) {
    int w = o->v50();
    w = (s16)(w - (s16)o->v48() * 2);
    return w / (s16)o->vA4();
}

s16 fn_801E0FA0(u8* o) { return *(s16*)(o + 0x20); }

typedef struct LL { u8 pad[0xa4]; s8 n; } LL;

s16 fn_801E0FA8(VO4* o, LL* l) {
    s16 w = o->vA4();
    return (w + l->n - 1) / w;
}

void* fn_801E0FFC(void) { return lbl_8038C950; }
void* fn_801E1008(void) { return lbl_8038C960; }
int fn_801E1014(void) { return 0x80; }
int fn_801E101C(void) { return 0x44; }
void* fn_801E1024(void) { return lbl_8038C9A8; }
u8 fn_801E1030(u8* o) { return o[0xc]; }
u8 fn_801E1038(u8* o, u8 m) { return o[0xd] & m; }
void fn_801E1044(u8* o, u8 v) { o[4] = v; }
int fn_801E104C(void) { return 0; }
u8 fn_801E1054(u8* o) { return o[4]; }
u8 fn_801E105C(u8* o) { return o[4]; }
void* fn_801E1064(void) { return lbl_8038C98C; }
void* fn_801E1070(void) { return lbl_8038C970; }

class Lbl : public VO0 {
public:
    u8 pad4[0x6];
    s16 xa, xc, xe, x10;
    s16 x12, x14, x16, x18;
    u8 pad1a[4];
    s16 x1e, x20;
    GXColor x22;
    u8 pad26[0x38 - 0x26];
    u32 x38;
    u8 pad3c[4];
    int x40;
    s16 x44;
    u8 pad46[2];
    s16 x48, x4a, x4c, x4e;
    u8 pad50[0x61 - 0x50];
    u8 x61;
    u8 pad62[0x68 - 0x62];
    s16 x68;
    u8 pad6a[0x89 - 0x6a];
    u8 x89;
    u8 pad8a[0x90 - 0x8a];
    s16 x90;
};

void fn_801E107C(Lbl* o) {
    o->v14();
    fn_801D7014(0, 0, (s16)(o->xe - o->xa), (s16)(o->x10 - o->xc), 0x10);
}

void fn_801E13BC(VO0* o, int a) {
    o->v30();
    o->v34(a);
}

void fn_801E1418(VO0* o) {
    o->v14();
    fn_801D772C(0, 0, 0x10);
}

void fn_801E2204(Lbl*, s16*, s16*);
typedef struct Rect16 { s16 x, y, w, h; } Rect16;
void fn_801E2104(void*, Rect16*);

static inline void rectSet(Lbl* o, s16 a, s16 b, s16 c, s16 d) {
    o->x48 = a;
    o->x4a = b;
    o->x4c = c;
    o->x4e = d;
}

void fn_801E1454(Lbl* o) {
    const char* s;
    s16 x;
    s16 y;
    o->v18();
    x = o->x1e;
    s = (const char*)(int)o->x44;
    y = o->x20;
    y = y + (((int)s - fn_800CB0FC(-1, 1.0f)) >> 1);
    s = o->x40 ? (const char*)fn_800D0864(o->x40) : lbl_8036ED78;
    if (s != NULL) {
        rectSet(o, 0, 0, o->x16 - o->x12, o->x18 - o->x14);
        fn_801E2204(o, &o->x48, &o->x48);
        fn_801E2204(o, &o->x4c, &o->x4c);
        fn_8007E154();
        fn_8007E74C(fn_801E2104, &o->x48);
        fn_8007E720(-1.0f);
        fn_8007E174(0, (u16)(o->x38 | 3));
        fn_8007E164();
        fn_801E6DA0(x, y, 0x1f, s);
        fn_8007E154();
        fn_8007E7B4();
        fn_8007E164();
    }
}

const char* fn_801E159C(VO0* o) {
    if (o->v3C()) {
        return (const char*)fn_800D0864(o->v3C());
    }
    return lbl_8036ED78;
}

void fn_801E1600(VO0* o) {
    o->v14();
    fn_801D8DBC(0, 0, 0x10);
}

void fn_801E17FC(VO0* o, int a) {
    o->v48(a);
    o->v4C(a);
}

void fn_801E1858(VO0* o) {
    o->v14();
    fn_801D8F10(0, 0, 0x10);
}

void* fn_801E1AD8(void* p, int del) {
    if (p != NULL && del > 0) {
        fn_80079210(p);
    }
    return p;
}

void* fn_801E1B18(void* p, int del) {
    if (p != NULL && del > 0) {
        fn_80079210(p);
    }
    return p;
}

int fn_801E1B58(u8* o) { return *(int*)(o + 0x44); }
int fn_801E1B60(void) { return 0x20; }
void* fn_801E1B68(u8* o) { return o + 0x40; }
int fn_801E1B70(void) { return 0x20; }
void fn_801E1B78(u8* o, int v) { *(int*)(o + 0x44) = v; }

void fn_801E1B80(u8* o, GXColor* c) {
    if ((GXColor*)(o + 0x40) != c) {
        *(GXColor*)(o + 0x40) = *c;
    }
}

static inline s16 lblW(Lbl* o) { return o->xe - o->xa; }
static inline s16 lblH(Lbl* o) { return o->x10 - o->xc; }
static inline void lblSet(Lbl* o, s16 a, s16 b, s16 c, s16 d, s16 e, s16 f) {
    o->x12 = a;
    o->x14 = b;
    o->x16 = c;
    o->x18 = d;
    o->x1e = e;
    o->x20 = f;
}

void fn_801E1BB0(Lbl* o) {
    lblSet(o, 0x20, 0, o->xe - o->xa, o->x10 - o->xc, 0, 0);
}

void fn_801E1BEC(Lbl* o) {
    lblSet(o, 0, 0, o->xe - o->xa, o->x10 - o->xc, 0x18, 4);
}

void fn_801E1C2C(Lbl* o) {
    lblSet(o, 2, 8, lblW(o) - 2, lblH(o) - 8, 0x10, 0);
}

void* fn_801E1C80(void* p, int del) {
    if (p != NULL && del > 0) {
        fn_80079210(p);
    }
    return p;
}

void fn_801E1CC0(Lbl* o, int a) {
    if (*(s16*)&o->x40 > 0 && o->x44 != a) {
        if (a < o->x44) {
            o->x61 = 0;
            o->x68 = 1;
        } else {
            o->x89 = 0;
            o->x90 = 1;
        }
        o->x44 = a;
    }
}

s16 fn_801E1F10(Lbl* o) { return o->x18 - o->x14; }
s16 fn_801E1F24(Lbl* o) { return o->xe - o->xa; }

void* fn_801E1F38(u8* p, int del) {
    if (p != NULL) {
        if (p != NULL) {
            VO0* a = (VO0*)(p + 0x7c);
            if (a != NULL) {
                if (a != NULL) {
                    *(void**)(p + 0x7c) = lbl_8038C294;
                    a->v10();
                }
            }
            a = (VO0*)(p + 0x54);
            if (a != NULL) {
                if (a != NULL) {
                    *(void**)(p + 0x54) = lbl_8038C294;
                    a->v10();
                }
            }
        }
        if (del > 0) {
            fn_80079210(p);
        }
    }
    return p;
}

void fn_801E1FE0(Lbl* o) {
    o->v18();
    fn_8007E154();
    fn_8007E174(0, (u16)(o->x38 | 2));
    fn_8007E164();
    fn_800800D4(1);
    fn_80080388(0.0f, 0.0f, (s16)(o->x16 - o->x12), (s16)(o->x18 - o->x14));
    {
        GXColor c = o->x22;
        fn_80080508(&c);
    }
    fn_80080308();
}

void* fn_801E20C4(void* p, int del) {
    if (p != NULL && del > 0) {
        fn_80079210(p);
    }
    return p;
}


static inline s16 clampRect(s16 v) {
    if (v < 0) return 0;
    if (v > 0x7ff) return 0x7ff;
    return v;
}

void fn_801E2104(void* a, Rect16* src) {
    Rect16 r = *src;
    r.x = r.x < 0 ? 0 : r.x > 0x7ff ? 0x7ff : r.x;
    r.y = r.y < 0 ? 0 : r.y > 0x7ff ? 0x7ff : r.y;
    r.w = r.w < 0 ? 0 : r.w > 0x7ff ? 0x7ff : r.w;
    r.h = r.h < 0 ? 0 : r.h > 0x7ff ? 0x7ff : r.h;
    {
        s16 w = r.w - r.x;
        s16 h = r.h - r.y;
        fn_803080DC(r.x, r.y, w, h);
    }
}

void fn_801E2DF0(void) {}
void fn_801E2DF4(void) {}
void fn_801E2DF8(void) {}
void fn_801E2DFC(void) {}

}
