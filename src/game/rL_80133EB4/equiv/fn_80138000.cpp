/* fn_80138000: functionally equal (regs level per tools/check_regs.py; registers differ from the original). Tile height refresh over a rectangle. From wip/near3.cpp with the declarations of fn_8013B74C.cpp (bodies stripped). */
/* symcheck: (a) block 7: r0/r3 used the other way round as temporaries; the leftover in r3 only looks live because r3 counts as a return value and the function is void (clean with --ret=none). */
#include "game/rL_80133EB4/map3d.h"
#pragma use_lmw_stmw on
struct N { s16 v[4]; void* x8; };
struct Mp { u8 p[0x20000]; };
struct Rain { u8 pad[0x44]; u8* x44; u8* x48; u8* x4c; f32* x50; f32* x54; f32* x58; f32* x5c; };
extern "C" {
extern const char lbl_803694D4[];
extern Mp lbl_803EC898;
extern u8 lbl_803699B0[];
extern void fn_80290DDC(char*, const char*, ...);
extern int fn_80076F54(char*);
extern void* fn_80077064(char*);
extern u8 fn_8011D1E4(void*);
extern Mesh* fn_80135934(MapModel*, int, u32, u32);
extern void fn_801CA33C(Mesh*, int, int);
extern void fn_80272624(void*, f32);
extern int fn_8030585C(int, int, int, int, int);
extern u8* fn_80078D9C(u32, void*, int);
extern void DCFlushRange(void*, u32);
extern void fn_8017F464(void*, int, u32);
extern u32 fn_80089ED0(void);

#define H(q) (*(s16*)((u8*)(q) + 0x15422))
#define L(q) (*(s16*)((u8*)(q) + 0x1D42C))
#pragma use_lmw_stmw off
static inline MapEntry18* FindE(MapModel* mm, Mesh* m) {
    if (m) {
        MapEntry18* e = mm->lights;
        for (int i = 0; i < 16; e++, i++) {
            if (*(Mesh**)((u8*)e + 0x14) == m) return &mm->lights[i];
        }
    }
    return 0;
}
int fn_8013B74C(MapModel* mm, int pct);
u32 fn_801436EC(Rain* r);
}


#pragma use_lmw_stmw on
/* ---- fn_80138000 ---- */
extern "C" {
/* ===== fn_80138000: 45 words, lis base must take r18 below the params ===== */
void fn_80138000(MapModel* mm, int x0, int y0, int x1, int y1, int both) {
    char path[0x40];
/*P*/
    u16* ids;
    N* nodes;
    int ofs;
    u8* row;
    u16* q;
    int x;
    N* n;
/*E*/
    u8* base = (u8*)lbl_803694D4;
    fn_80290DDC(path, (char*)base + 0x13B, mm->name);
    if (fn_80076F54(path)) {
        nodes = (N*)fn_80077064(path);
        fn_80290DDC(path, (char*)base + 0x148, mm->name);
        ids = (u16*)fn_80077064(path);
        base = (u8*)&lbl_803EC898;
        for (; y0 <= y1; y0++) {
            ofs = (s8)y0 * 0x40;
            row = base + ofs;
            x = x0;
            q = &ids[x0 + y0 * mm->x4c];
            for (; x <= x1; x++) {
                n = &nodes[*q++];
                u8 m = fn_8011D1E4(n->x8);
                int xx = (s8)x;
                row[0x100D + xx] = m;
                u8* b = base + (xx + ofs) * 8;
                s16 v = n->v[0];
                H(b) = v;
                if (both) L(b) = v;
                u8* b1 = b + 2;
                v = n->v[1];
                H(b1) = v;
                if (both) L(b1) = v;
                u8* b2 = b + 4;
                v = n->v[2];
                H(b2) = v;
                if (both) L(b2) = v;
                u8* b3 = b + 6;
                v = n->v[3];
                H(b3) = v;
                if (both) L(b3) = v;
            }
        }
    }
}
}
