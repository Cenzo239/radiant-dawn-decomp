/* r20 wip, self-contained (wip/fn_801CDAF8.cpp + declarations of fn_801CDAF8.cpp via mkself.py), still `other`:
   two instructions short (94 of 96): the original builds the position Vec3 at 0x8 (zero words, then the two floats, then a word copy to the argument slot 0x14) and adds `row * 0x24` to y with a `mulli`; ours builds it at 0x14 and copies to 0x8. */
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
void fn_801CDAF8(UA* u);

extern void* fn_80011F0C(void);
extern void fn_80305A40(void*, void*, int, int, int, int, int, int);
extern void fn_80305C94(void*, int, int, int, int, int, f32, f32, f32);
extern void fn_80022254(void*, void*);
extern u32 fn_80011E80(void);
extern u32 fn_80011F90(void);
extern void fn_80021CB4(u32, u32, void*, int);
extern void fn_80021EF8(u32, int);
extern void* fn_80011FC4(void);
extern void fn_8031292C(void*, f32, f32, f32);
extern void fn_803128AC(void*, f32, f32, f32);
extern void fn_80312378(void*, void*, void*);
extern void fn_80307F10(void*, void*, int);
extern void fn_80021F7C(u32, int, int, void*);
typedef struct PU { u8 pad[0x34]; u8 x34; u8 pad35; s16 x36; u8 pad38[2]; s16 x3A; s16 x3C; u8 x3E, x3F; s8 x40; u8 pad41[0x1F]; void* x60; } PU;
typedef struct NH { u8 pad[0x88]; PU* x88; } NH;
void fn_801CDC14(NH* n);

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
extern void fn_8007E174(int, int);
extern void fn_8007E164(void);
extern void fn_800800D4(int);
extern void fn_80080388(f32, f32, f32, f32);
extern void fn_800804D4(u8, u8, u8, u8);
extern void fn_80080578(int);
extern void fn_80080308(void);
}

/* ---- from rF_8017F400/wip/fn_801CDAF8.cpp ---- */
extern "C" {
/* near misses; take the declarations from ../fn_801CDAF8.cpp */
void fn_801CE2F4(const char* s, u32 f, void* parent) {
    int i;
    PS* p;
    int y = 0;
    int z = 0;
    int x = 0;
    if (f & 1) x = 0;
    if (f & 2) x = 0x260;
    if (f & 8) y = 0x50;
    if (f & 4) { y = 0x190; z = 1; }
    if (f) {
        i = 0;
        p = (PS*)fn_800E4278(lbl_8036EA00 + 0x2A, parent);
        p->x60 = i;
        p->x30->x98 = (void*)fn_801CE068;
        p->x30->x9C = (void*)fn_801CE174;
        p->x30->xA0 = (void*)fn_801CE130;
        strcpy(p->x40, s);
        p->x3A = x;
        p->x3C = y;
        p->x3E = z;
        p->x3F = i;
        p->x34 = 1;
        p->x30->x4 = 4;
        p->x36 = i;
        {
            int yy = p->x3C + i * 0x24;
            int xx = p->x3A;
            Pt a;
            *(int*)&a.x = i; *(int*)&a.y = i; *(int*)&a.z = i;
            a.x = xx;
            a.y = yy;
            {
            Pt b = a;
            Pt c = b;
            fn_800E48C8(p, &c);
            }
        }
        fn_800E465C((void*)fn_801CE010, p);
    }
}
}
