/* Door falling apart: spins and sinks the door mesh while it fades out. */
#include "game/rL_80133EB4/map3d.h"
struct DoorProc {
    u8 pad0[0x38];
    Mesh* m38;
    Mesh* m3c;
    u8 pad40[4];
    Mesh* m44;
    int t;
    int n;
};
extern "C" {
extern void fn_8031292C(void*, f32, f32, f32);
extern void fn_803128AC(void*, f32, f32, f32);
extern void fn_80312378(void*, void*, void*);
extern void fn_801CA434(Mesh*, void*);
extern void fn_801CA3DC(Mesh*, u8);
extern void fn_80083B78(void*);
extern f32 fn_8001EF30(f32, f32, f32, f32);
extern f64 fn_80295940(f32);
extern f64 fn_80295534(f32);
extern void fn_80312654(void*, int, f32);
void fn_8013C4A4(DoorProc* p) {
    u8 m0[0x30];
    u8 m1[0x30];
    u8 m2[0x30];
    u8 m3[0x30];
    Mesh* m = p->m38;
    
    f32 x, z, rot, ang, y;
x = m->tx; y = m->ty; z = *(f32*)((u8*)m + 0xC); rot = 0.015625f * *(s16*)((u8*)m + 0xA);
    p->t++;
    z = z + fn_8001EF30(0.0f, 1.0f, p->n, p->t);
    x += 0.01f * (f32)fn_80295940(p->t);
    y = 0.01f * (f32)fn_80295534(p->t) + y;
    fn_8031292C(m0, 0.2f, 0.2f, 0.2f);
    fn_80312654(m1, 0x58, 4.712389f);
    fn_80312378(m1, m0, m3);
    fn_803128AC(m2, -0.5f, -0.5f, 0.0f);
    fn_80312378(m2, m3, m3);
    fn_80312654(m1, 0x5A, 0.017453292f * rot);
    fn_80312378(m1, m3, m3);
    fn_803128AC(m2, 0.5f, 0.5f, 0.0f);
    fn_80312378(m2, m3, m3);
    fn_803128AC(m2, x, y, z);
    fn_80312378(m2, m3, m3);
    {
        int a = fn_8001EF30(0.0f, 255.0f, p->n, p->t);
        u8 b = 0xFF - a;
        fn_801CA434(p->m38, m3);
        fn_801CA3DC(p->m38, b);
        if (p->m44) {
            fn_801CA434(p->m44, m3);
            fn_801CA3DC(p->m44, b);
        }
        if (p->m3c) fn_801CA3DC(p->m3c, (u8)a);
    }
    if (p->t >= p->n) fn_80083B78(p);
}

}
