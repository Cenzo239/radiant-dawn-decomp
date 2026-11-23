/* fn_800DFD3C: near miss, registers only: FIFO base 0xCC008000 should be r6 with the alpha byte in r5 (ours swaps), which also moves li r3,-1. */
/* Tile highlight quad draw callback (names guessed). */
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned int u32;
typedef float f32;
typedef f32 Mtx[3][4];
struct HiProc {
    u8 pad[0x30];
    s16 x, y;
    u8 r, g, b, a;
    u8 pad38[8];
    f32 z[4];
};
#define GXF (*(volatile f32*)0xCC008000)
#define GXB (*(volatile u8*)0xCC008000)
extern "C" {
void fn_803031CC();
void fn_80302B80(int, int);
void fn_80303200(int, int, int, int, int);
void fn_80021B2C(int);
void fn_80021A08(int, int, int, int, int, int, int);
void fn_80021BF4(int);
void fn_80021EF8(int, int);
void fn_80021CB4(int, int, int, int);
void fn_80021C34(int);
void fn_80021F7C(int, int, int, int);
void fn_80021B68(int);
void fn_803128AC(Mtx, f32, f32, f32);
f32 (*fn_8000FB88())[4];
void fn_80312378(f32 (*)[4], Mtx, Mtx);
void fn_80307E48(Mtx, int);
void fn_80021784(int);
void fn_80021BA4(int, int, int, int);
void fn_80304314(int, int, int);
void fn_80011838(int);

static inline void pos3(f32 x, f32 y, f32 z) {
    GXF = x;
    GXF = y;
    GXF = z;
}
static inline void col4(u8 r, u8 g, u8 b, u8 a) {
    GXB = r;
    GXB = g;
    GXB = b;
    GXB = a;
}

void fn_800DFD3C(HiProc* p) {
    Mtx m;
    fn_803031CC();
    fn_80302B80(9, 1);
    fn_80302B80(0xB, 1);
    fn_80303200(0, 9, 1, 4, 0);
    fn_80303200(0, 0xB, 1, 5, 0);
    fn_80021B2C(1);
    fn_80021A08(4, 0, 0, 1, 0, 0, 2);
    fn_80021BF4(1);
    fn_80021EF8(0, 4);
    fn_80021CB4(0, 0xFF, 0xFF, 4);
    fn_80021C34(0);
    fn_80021F7C(0, 1, 4, 0x3C);
    fn_80021B68(0);
    fn_803128AC(m, 0.0f, 0.0f, -0.02f);
    fn_80312378(fn_8000FB88(), m, m);
    fn_80307E48(m, 0);
    fn_80021784(0);
    fn_80021BA4(1, 4, 1, 0);
    fn_80304314(0x98, 0, 4);
    pos3(p->x, p->y, p->z[0]);
    col4(p->r, p->g, p->b, p->a);
    pos3(p->x + 1, p->y, p->z[1]);
    col4(p->r, p->g, p->b, p->a);
    pos3(p->x, p->y + 1, p->z[2]);
    col4(p->r, p->g, p->b, p->a);
    pos3(p->x + 1, p->y + 1, p->z[3]);
    col4(p->r, p->g, p->b, p->a);
    fn_80011838(-1);
}
}
