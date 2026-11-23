/* EQUIVALENT (regs, round 19b): fn_80063DFC, draw routine of the two-column item exchange screen (object O made by fn_800656BC). */
extern "C" {
typedef unsigned char u8;
typedef signed char s8;
typedef short s16;
typedef float f32;
struct Slot { s16 x, y; u8 item[0x28]; u8 enabled, pad[3]; };
struct O {
    u8 pad[0x28]; s16 state; u8 p2a[6]; void* a; void* b; s16 x38, x3a;
    s8 side, index, oldSide, oldIndex; u8 flag, phase, x42, mode, filter, x45, p46[2]; void* child;
};
extern Slot lbl_803CB4D0[2][7];
extern u8 lbl_8041EB20[];
f32 fn_8017F68C(f32 a, f32 b, f32 c, f32 d, int e);
void fn_8017A188(void* p);
void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E4E4(f32, f32, f32, f32);
void fn_8007E7DC(u8);
void fn_8007E720(f32);
void fn_800720F4(void*, int, int);
void fn_800718D0(int, int, int, int, int, int);
void* fn_8012B120(void*, void*);
void fn_80107C80(void*, void*, int, int);
int fn_801A2224(void*);
void fn_800712E8(int, int, int);
void fn_800715B0(int, int);
void fn_80072ACC(int, int, int, int, int, int, int);

/* The step count 5 is a local so that 1.0f / 5 is computed at run time, as in the original. */
static inline f32 frac(int cur) { int total = 5; return 1.0f / total * cur; }
static inline void setZ(f32 z) { fn_8007E154(); fn_8007E720(z); fn_8007E164(); }
static inline void setTint(f32 r, f32 t) {
    fn_8007E154();
    fn_8007E4E4(r, 52.0f, 120.0f, 1.0f);
    fn_8007E7DC((int)(255.99f * t));
    fn_8007E164();
}

void fn_80063DFC(O* o) {
    f32 t;
    int n = o->state + 1;
    void* u;
    Slot* p;
    int i;
    s16 sx, sy;
    switch (o->phase) {
    case 0: t = 1.0f; break;
    case 1: t = frac(5 - n); break;
    case 2: t = frac(n); break;
    default: t = 0.0f; break;
    }
    fn_8017F68C(0.0f, 1.0f, t, 1.0f, 5);
    if (o->x42 == 1) {
        fn_8017A188(o->child);
    }
    setTint(308.0f, t);
    u = o->b;
    fn_800720F4(u, 0, 0);
    fn_800718D0(0xc, 0x69, 0x10a, 0xdc, 0, o->x45);
    setZ(-1.0f);
    for (i = 0, p = lbl_803CB4D0[1]; i < 7; i++, p++) {
        u8* it = p->item;
        if (*(void**)it) {
            fn_80107C80(it, fn_8012B120(u, *(void**)it), p->x - 0x12a, p->y);
        }
    }
    setTint(10.0f, t);
    u = o->a;
    fn_800720F4(u, 0, 0);
    fn_800718D0(0xc, 0x69, 0x10a, 0xdc, 0, o->x45);
    setZ(-1.0f);
    for (i = 0, p = lbl_803CB4D0[0]; i < 7; i++, p++) {
        u8* it = p->item;
        if (*(void**)it) {
            fn_80107C80(it, fn_8012B120(u, *(void**)it), p->x, p->y);
        }
    }
    fn_8007E154();
    fn_8007E7DC(0xff);
    fn_8007E164();
    if (o->phase == 0) {
        setZ(-1.0f);
        if (o->x38 < 0) {
            o->x38 = lbl_803CB4D0[o->side][o->index].x;
            o->x3a = lbl_803CB4D0[o->side][o->index].y;
        } else {
            o->x38 = (o->x38 + lbl_803CB4D0[o->side][o->index].x) / 2;
            o->x3a = (o->x3a + lbl_803CB4D0[o->side][o->index].y) / 2;
        }
        sx = lbl_803CB4D0[o->oldSide][o->oldIndex].x;
        sy = lbl_803CB4D0[o->oldSide][o->oldIndex].y;
        setZ(-5.0f);
        fn_800712E8(o->x38, o->x3a, fn_801A2224(lbl_8041EB20) == 0);
        setZ(5.0f);
        if (o->flag == 1) {
            fn_800715B0(sx, sy);
            setZ(1.0f);
            fn_80072ACC(sx + 0x75, sy + 0xd, 0xef, 0x18, 0x19, 0x4b, 0);
            setZ(-1.0f);
        }
        setZ(1.0f);
        fn_80072ACC(lbl_803CB4D0[o->side][o->index].x + 0x75, o->x3a + 0xd, 0xef, 0x18, 0x19, 0x4b, 1);
        setZ(-1.0f);
    }
}
}
