/* fn_80138FF8 (0x96C): functionally equal at `regs` level (tools/check_regs.py, round 20; 194 words differ in
 * registers). From the round 14 draft in wip/near4.cpp, which was `other` for two reasons, both fixed here:
 *   - the adjacent-door search is now an inline (`Near`) that returns as soon as a mesh is found; `if (m) return m;`
 *     gives the original's `beq; b` pair where the old `if (m2 == 0) {...}` gave one `bne`;
 *   - the event loop steps `off0 += 8, i++` (the old order swapped the two `addi`).
 * Caveats: FIND is a macro with a label per site and the P-block holds one counter/offset/mesh set per site; both
 * come from an old register search and can be collapsed into one inline lookup in a port.
 */
/* Replays saved map events after a load: doors, roofs, breakable blocks and other switched meshes. */
#include "game/rL_80133EB4/map3d.h"
#pragma use_lmw_stmw off

struct MapEv { s8 x, y; u8 kind; u8 pad[5]; };
struct MapEvVec { MapEv* p; u8 pad4[0x10]; };
struct Emit { u8 pad0[0x14]; Mesh* mesh; };

extern "C" {
extern MapEvVec lbl_803CB770;
extern u8 lbl_803EC898[];
extern int fn_800660E8(MapEvVec*);
extern void fn_80065E4C(MapEv*, int);
extern int fn_801CA274(Mesh*, int, int);
extern void fn_801CA300(Mesh*);
extern void fn_801CA4FC(Mesh*, int);
extern void fn_801CA444(Mesh*, int);
extern void fn_801CA3E4(Mesh*, int);
extern void fn_801CA33C(Mesh*, int, int);
extern int fn_80135C44(MapModel*, Mesh*, Mesh**, int);
extern int fn_8013599C(MapModel*, int, int, u32, u32, Mesh**);
extern void fn_80272624(Emit*, f32);
extern void fn_801379F8(MapModel*, int);
extern void fn_80114D00(void*);
extern void fn_8013A638(MapModel*);
extern void fn_8012D908(void);

#define FIND(COND, M, I, O, X, Y, L) \
    for (I = mm->nMesh - 1, O = I * 0xD0; I >= 0; O -= 0xD0, I--) { \
        M = (Mesh*)((u8*)mm->mesh + O); \
        u32 f = M->group->flags; \
        if (COND) { switch (fn_801CA274(M, X, Y)) { case 0: break; default: goto L; } } \
    } \
    M = 0; \
L:
#define A(K) ((f & 0x10) == 0 && (f & K) == K)
#define B(K) ((f & K) == K)
static inline int DirBit(int i) {
    switch (i) {
    case 0: return 1;
    case 1: return 2;
    case 2: return 4;
    case 3: return 8;
    default: return 0x40;
    }
}
static inline int DirX(int d) {
    switch (d) {
    case 1: return -1;
    case 2: return 1;
    default: return 0;
    }
}
static inline int DirY(int d) {
    switch (d) {
    case 4: return 1;
    case 8: return -1;
    default: return 0;
    }
}
static inline Emit* FindEmit(MapModel* mm, Mesh* m) {
    if (m) {
        for (int i = 0; i < 16; i++) {
            if (((Emit*)&mm->lights[i])->mesh == m) return (Emit*)&mm->lights[i];
        }
    }
    return 0;
}
static inline Mesh* Near(MapModel* mm, int x, int y) {
    Mesh* m2;
    int i2;
    int off2;
    int i3;
    int x3;
    int off;
    FIND(B(0x800), m2, i2, off2, x, y, LA);
    if (m2) return m2;
    for (i3 = 0; i3 < 4; i3++) {
        int d = DirBit(i3);
        int dx = DirX(d);
        int dy = DirY(d);
        int yy = y + dy;
        int xx = x + dx;
        FIND(B(0x800), m2, x3, off, xx, yy, LB);
        if (m2) return m2;
    }
    return 0;
}
void fn_80138FF8(MapModel* mm) {
    /*P*/
    int ii1;
    int oo1;
    Mesh* mm1;
    int ii2;
    int oo2;
    Mesh* mm2;
    int ii3;
    int oo3;
    Mesh* mm3;
    int ii4;
    int oo4;
    Mesh* mm4;
    int ii5;
    int oo5;
    Mesh* mm5;
    int ii6;
    int oo6;
    Mesh* mm6;
    int ii7;
    int oo7;
    Mesh* mm7;
    int ii8;
    int oo8;
    Mesh* mm8;
    int ii9;
    int oo9;
    Mesh* mm9;
    int ii10;
    int oo10;
    Mesh* mm10;
    int ii11;
    int oo11;
    int ii12;
    int oo12;
    Mesh* mm12;
    int x3;
    int i3;
    Mesh* m2;
    int i2;
    int off2;
    int off0;
    int y;
    int off;
    Mesh* mm11;
    int x;
    int i;
/*E*/
    Mesh* buf[16];
    for (i = 0, off0 = 0; i < fn_800660E8(&lbl_803CB770); off0 += 8, i++) {
        MapEv* e = (MapEv*)((u8*)lbl_803CB770.p + off0);
        x = e->x;
        y = e->y;
        switch (e->kind) {
        case 0x24:
            FIND(A(0x40000), mm1, ii1, oo1, x, y, L1)
            if (mm1) fn_801CA300(mm1);
            break;
        case 0x21:
            FIND(B(0x1000), mm2, ii2, oo2, x, y, L2)
            if (mm2) {
                fn_801CA4FC(mm2, 0);
                m2 = Near(mm, x, y);
                mm2 = m2;
                if (mm2) {
                    int n = fn_80135C44(mm, mm2, buf, 0);
                    Mesh** p = buf;
                    for (int k = 0; k < n; k++) {
                        fn_801CA444(*p, 0);
                        p++;
                    }
                }
            }
            break;
        case 0x22:
            FIND(A(0x800), mm3, ii3, oo3, x, y, L3)
            if (mm3) {
                int n = fn_80135C44(mm, mm3, buf, 0);
                Mesh** p = buf;
                for (int k = 0; k < n; k++) {
                    fn_801CA444(*p, 0);
                    p++;
                }
            }
            break;
        case 0x23:
            FIND(A(0x200), mm4, ii4, oo4, x, y, L4)
            if (mm4) fn_801CA300(mm4);
            break;
        case 0x25:
            FIND(((f & 0x20000) == 0 && (f & 0x800) == 0x800), mm5, ii5, oo5, x, y, L5)
            if (mm5) {
                fn_801CA3E4(mm5, 0);
                FIND(B(0x20000), mm6, ii6, oo6, x, y, L6)
                if (mm6) {
                    fn_801CA300(mm6);
                    fn_801CA3E4(mm6, 1);
                }
            }
            break;
        case 0x26:
            FIND(A(0x800), mm7, ii7, oo7, x, y, L7)
            if (mm7) fn_801CA444(mm7, 0);
            break;
        case 0x27:
            FIND(B(0x10000), mm8, ii8, oo8, x, y, L8)
            if (mm8) fn_801CA444(mm8, 0);
            break;
        case 0x28:
            FIND(A(0x200), mm9, ii9, oo9, x, y, L9)
            if (mm9) fn_801CA300(mm9);
            break;
        case 0x29:
            FIND(A(0x80000), mm10, ii10, oo10, x, y, L10)
            if (mm10) fn_801CA3E4(mm10, 0);
            break;
        case 6:
            FIND(A(0x10000000), mm11, ii11, oo11, x, y, L11)
            if (mm11) {
                fn_801CA33C(mm11, 0xFF, 0);
                Emit* s = FindEmit(mm, mm11);
                if (s) fn_80272624(s, 1.0f);
            }
            break;
        case 0x12: {
            int n = fn_8013599C(mm, x, y, 0x1004200, 0x10, buf);
            Mesh** p = buf;
            for (int k = 0; k < n; k++) {
                fn_801CA3E4(*p, 0);
                p++;
            }
            break;
        }
        case 0x13:
            FIND(A(0x40000000), mm12, ii12, oo12, x, y, L12)
            if (mm12) fn_801CA3E4(mm12, 1);
            break;
        }
    }
    fn_801379F8(mm, 1);
    fn_80114D00(lbl_803EC898);
    fn_8013A638(mm);
    fn_8012D908();
    for (int j = 0; j < fn_800660E8(&lbl_803CB770); j++) {
        fn_80065E4C(&lbl_803CB770.p[j], 0);
    }
}
}

