/* near miss: fn_801CC5CC, 16 words: t0/t1 want f24/f25 swapped; K (0.015625f) wants a higher FP register than the first conversion. Declarations in ../fn_801CC06C.cpp. Declaration order from sw.py. */
typedef struct Mt { f32 m[3][4]; } Mt;
extern void fn_8031292C(f32, f32, f32, Mt*);
extern void fn_80312654(f32, Mt*, int);
extern void fn_80312344(Mt*, void*);
extern u8* fn_8012FCD0(void);
extern f32 fn_8001ECE4(int, f32, f32, f32, f32);
extern void fn_801CCA38(MObj*, f32);
static inline f32 Fx(int v) { return 0.015625f * (f32)v; }
static inline f32 Fy(f32 k, int v) { return k * (f32)v; }
static inline f32 Px(int i, int f) { f32 fr = Fx(f); return (f32)i + fr; }
static inline void PosOf(MObj* o, Vc& v) { f32 a = Fx(o->xCE); f32 x1=(f32)o->x1; f32 b = Fx(o->xCF); f32 y1=(f32)o->x2; v.z = Fx(o->xA); v.x = x1 + a; v.y = y1+b; }
void fn_801CC5CC(MObj* o, f32 dx, f32 dy, f32 dz, f32 dr) {
    MDef* d;
    u8* m;
    Mt r0, r2, r1, r3;
/*P*/
    f32 s;
    f32 x;
    f32 y;
    f32 h;
    f32 a;
    f32 hs;
    f32 o1;
    f32 o2;
    f32 x1;
    f32 y1;
    f32 p2;
    f32 p1;
    f32 e;
    f32 h0;
    f32 o3;
/*E*/
    m = (u8*)fn_8013B9A8();
    d = o->def;
    if (m == 0) {
        m = (u8*)fn_8013B9A8();
        if (m == 0) return;
    }
    {
    o1 = 0.015625f * (f32)o->xCE;
    x1 = (f32)o->x1;
    o2 = 0.015625f * (f32)o->xCF;
    y1 = (f32)o->x2;
    o3 = 0.015625f * (f32)o->xA;
    e = o->xC;
    p1 = x1 + o1;
    p2 = y1 + o2;
    h0 = dz + e;
    x = dx + p1;
    y = dy + p2;
    s = 5.0f * *(f32*)(m + 0xD0);
    a = dr + o3;
    h = -h0;
    hs = 0.5f * s;
    }
    switch (m[0xB1]) {
    case 0:
        if (d->fl & 0x40) {
            u8* q = fn_8012FCD0();
            if (q != 0) {
                Vc t = *(Vc*)(q + 0x38);
                x = t.x;
                y = t.y;
            }
        }
        break;
    case 1: case 2: case 3:
        break;
    }
    fn_8031292C(*(f32*)(m + 0xD0), *(f32*)(m + 0xD0), *(f32*)(m + 0xD0), &r0);
    if (1.0f != 0.015625f * (f32)o->x3) {
        f32 t0 = 0.015625f * (f32)o->x3;
        f32 t1 = t0;
        f32 px, pz;
        if (d->fl & 0x10000000) t1 = fn_8001ECE4(2, 0.0f, 1.0f, 1.0f, t0);
        px = (f32)((u8*)d)[0xBC] * hs;
        pz = (f32)((u8*)d)[0xBD] * hs;
        fn_803128AC(-px, 0.0f, -pz, &r3);
        fn_8031292C(t0, t1, t0, &r2);
        fn_80312378(&r2, &r3, &r2);
        fn_803128AC(px, 0.0f, pz, &r3);
        fn_80312378(&r3, &r2, &r2);
        fn_80312378(&r2, &r0, &r0);
    }
    if (o->x0 & 1) {
        f32 px = (f32)((u8*)d)[0xBC] * s;
        fn_8031292C(-1.0f, 1.0f, 1.0f, &r2);
        fn_803128AC(px, 0.0f, 0.0f, &r3);
        fn_80312378(&r3, &r2, &r2);
        fn_80312378(&r2, &r0, &r0);
    }
    fn_803128AC(-hs, 0.0f, -hs, &r3);
    fn_80312654(0.0174532924f * a, &r1, 0x59);
    fn_80312378(&r1, &r3, &r1);
    fn_803128AC(hs, 0.0f, hs, &r3);
    fn_80312378(&r3, &r1, &r1);
    fn_80312378(&r1, &r0, &r0);
    fn_803128AC(x * s, h * s, y * s, &r3);
    fn_80312378(&r3, &r0, &r0);
    fn_80312378(m + 0xE4, &r0, &r0);
    fn_80312344(&r0, (u8*)o + 0x24);
    if (m[0x56] != 0) fn_801CCA38(o, *(f32*)(m + 0x58));
    else fn_801CCA38(o, 0.0f);
}
