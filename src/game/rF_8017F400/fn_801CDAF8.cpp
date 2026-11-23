#include "game/rF_8017F400/types.h"
#pragma auto_inline off
extern "C" {
typedef struct Vec3 { f32 x, y, z; } Vec3;
typedef struct Pt { f32 x, y, z; } Pt;
extern char lbl_8036EA00[];
extern void* fn_800B5784(void*, int);
extern void* fn_800C0A6C(void*);
typedef struct NA { u8 pad[0xC4]; struct { u8 pad[8]; u16 x8; }* xC4; } NA;
typedef struct MA { u8 pad[0x30]; NA* n; } MA;
extern MA* fn_800E3810(void*, void*);
extern f32 fn_800A7370(void*, const char*);
extern f32 fn_800A84A4(const char*);
extern Pt fn_800B377C(void*, int);
extern void fn_800E48AC(void*, f32, f32, f32);
extern f32 fn_8001E064(int);
extern void fn_800E49AC(void*, f32);
typedef struct UA { u8 pad[0x58]; s16 x58; u8 pad5A[0x1E]; void* x78; } UA;
void fn_801CDAF8(UA* u) {
    if (u) {
        void* a = fn_800B5784(u, -1);
        if (a) {
            void* b = fn_800C0A6C(a);
            if (b) {
                MA* m = fn_800E3810(b, u);
                if (m) {
                    f32 h = fn_800A7370(u->x78, lbl_8036EA00 + 0x16);
                    f32 o = fn_800A84A4(lbl_8036EA00 + 0x1B);
                    Pt p = fn_800B377C(u, -1);
                    if (m->n->xC4->x8 & 0x80) {
                        o = 0.0f;
                        h = o;
                    }
                    fn_800E48AC(m, p.x, h + o, p.z);
                    fn_800E49AC(m, fn_8001E064(u->x58));
                }
            }
        }
    }
}
#if TARGET_PC
extern FE10_PROTO ptr32<void> fn_80011F0C(void);
#else
extern void* fn_80011F0C(void);
#endif
extern void fn_80305A40(void*, void*, int, int, int, int, int, int);
extern void fn_80305C94(void*, int, int, int, int, int, f32, f32, f32);
#if TARGET_PC
extern FE10_PROTO void fn_80022254(void*, ptr32<const void>);
#else
extern void fn_80022254(void*, void*);
#endif
extern u32 fn_80011E80(void);
extern u32 fn_80011F90(void);
#if TARGET_PC
extern FE10_PROTO void fn_80021CB4(u32, u32, ptr32<const void>, int);
#else
extern void fn_80021CB4(u32, u32, void*, int);
#endif
extern void fn_80021EF8(u32, int);
#if TARGET_PC
extern FE10_PROTO ptr32<void> fn_80011FC4(void);
#else
extern void* fn_80011FC4(void);
#endif
extern void fn_8031292C(void*, f32, f32, f32);
extern void fn_803128AC(void*, f32, f32, f32);
extern void fn_80312378(void*, void*, void*);
#if TARGET_PC
extern FE10_PROTO void fn_80307F10(void*, ptr32<const void>, int);
#else
extern void fn_80307F10(void*, void*, int);
#endif
#if TARGET_PC
extern FE10_PROTO void fn_80021F7C(u32, int, int, ptr32<const void>);
#else
extern void fn_80021F7C(u32, int, int, void*);
#endif
typedef struct PU { u8 pad[0x34]; u8 x34; u8 pad35; s16 x36; u8 pad38[2]; s16 x3A; s16 x3C; u8 x3E, x3F; s8 x40; u8 pad41[0x1F]; void* x60; } PU;
typedef struct NH { u8 pad[0x88]; PU* x88; } NH;
void fn_801CDC14(NH* n) {
    PU* p = n->x88;
    void* tx = fn_80011F0C();
    if (p->x60) {
        u8 obj[0x20];
        u8 m2[0x30];
        u8 m1[0x30];
        u8 m0[0x30];
        u32 a, b;
        fn_80305A40(obj, p->x60, 0x80, 0x20, 6, 0, 0, 0);
        fn_80305C94(obj, 1, 1, 0, 0, 0, 0.0f, 0.0f, 0.0f);
        fn_80022254(obj, tx);
        a = fn_80011E80();
        b = fn_80011F90();
        fn_80021CB4(a, b, tx, 4);
        fn_80021EF8(a, 0);
        if (p->x3A > 0x130) {
            void* q = fn_80011FC4();
            fn_8031292C(m1, -1.0f, 1.0f, 1.0f);
            fn_803128AC(m2, 1.0f, 0.0f, 0.0f);
            fn_80312378(m2, m1, m0);
            fn_80307F10(m0, q, 1);
            fn_80021F7C(b, 1, 4, q);
        }
    }
}
extern void* fn_800E4278(const char*, void*);
extern char* strcpy(char*, const char*);
extern void fn_800E48C8(void*, Pt*);
extern void fn_800E465C(void*, void*);
extern void fn_801CE010(void* p, void* arg);
extern void fn_801CE068(void* p);
extern void fn_801CE174(void* p);
extern void fn_801CE130(void* p);
typedef struct MX { u8 pad[4]; s16 x4; u8 pad6[0x92]; void* x98; void* x9C; void* xA0; } MX;
typedef struct PS { u8 pad[0x30]; MX* x30; u8 x34; u8 pad35; s16 x36; u8 pad38[2]; s16 x3A; s16 x3C; u8 x3E, x3F; char x40[0x20]; int x60; } PS;
extern void fn_8007E154(void);
#if TARGET_PC
extern FE10_PROTO void fn_8007E174(p32arg, int);
#else
extern void fn_8007E174(int, int);
#endif
extern void fn_8007E164(void);
extern void fn_800800D4(int);
extern void fn_80080388(f32, f32, f32, f32);
extern void fn_800804D4(u8, u8, u8, u8);
extern void fn_80080578(int);
extern void fn_80080308(void);
}
