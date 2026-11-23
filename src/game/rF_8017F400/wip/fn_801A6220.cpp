#include "game/rF_8017F400/types.h"
#pragma auto_inline off
#pragma pool_strings on
extern "C" {
void StringPool(const char** p) {
    p[0] = "%7d"; p[1] = "%s%s %s%s"; p[2] = "MD_TOMAP"; p[3] = "MD_LEADER"; p[4] = "MD_CUR"; p[5] = "MD_RTN"; p[6] = "E_TutEvent"; p[7] = "MCTTUT00_0"; p[8] = "MCTTUT00_1"; p[9] = "MCTTUT00_2"; p[10] = "%3d"; p[11] = "%02d"; p[12] = ":"; p[13] = "%s"; p[14] = "MP_LV"; p[15] = "%2d"; p[16] = "MP_HP"; p[17] = "/%3d";
}
struct C4 { u8 r, g, b, a; };
struct TexH { u16 x0, x2; };
struct Vec3 { f32 x, y, z; };
class IconFont {
public:
    u8 pad[0x44];
    virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14();
    virtual void draw(int x, int y, int id);
};
struct ItemDef { u8 pad[0x16]; u16 x16; };
struct ItemRef { ItemDef* d; };
struct UDef { u8 pad[0xE1]; u8 xE1; };
struct Unit { u8 pad[0xEC]; UDef* xEC; void* xF0; u8 pF4[0xA]; s8 xFE; u8 pFF[0x15]; s8 x114; u8 p115[3]; u8 x118; };
struct Sel { int x0; u8 p4[0x10]; Unit* u; };
typedef struct OData { u8 pad[0xC]; void* arch; u8 p10[0x310]; Sel* x320; u8 p324[0x10]; void* x334; u8 p338; u8 x339; } OData;
extern OData* lbl_804CB964;
extern u8 lbl_803E7290[];
extern char lbl_8036D22C[];
extern void fn_801A3FF8(void* p);
extern void fn_801BCA5C(f32);
extern void fn_801BCA94(void);
extern void* fn_80006A0C(void*, int);
extern const u8* fn_800CD204(int);
extern void fn_801BC88C(void* a, int b, C4* c, int d, u32 fl, f32 f1, f32 f2, f32 f3, f32 f4, f32 f5, f32 f6, f32 f7, f32 f8);
extern void fn_80070688(f32, f32, f32, f32);
extern void fn_80074EB4(int, int, int, int);
extern const char* fn_80118C44(void*);
extern const char* fn_80118F00(void*);
extern int fn_80290DDC(char*, const char*, ...);
extern void fn_800CB278(s16, s16, int, const char*, ...);
extern int fn_801196F0(u8);
extern const char* fn_800D0864(const char*);
extern s16 fn_801237EC(Unit*);
extern ItemRef* fn_8012759C(Unit*);
extern const char* fn_80110F08(ItemRef*);
extern Vec3 fn_800FB178(Unit*, f32);
extern void fn_80312654(void*, int, f32);
extern void fn_80312DB4(void*, Vec3*, Vec3*);
extern void fn_8031292C(void*, f32, f32, f32);
extern void fn_803128AC(void*, f32, f32, f32);
extern void fn_80312378(void*, void*, void*);
extern void fn_80312344(void*, void*);
extern void fn_80008F20(void*, u8);
extern void fn_80008F64(void*, int);
extern void fn_800081D4(void*);
extern void fn_80007C58(void*);
extern void fn_800F629C(Unit*, void*);
extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E174(int, int);
extern void fn_8007E4E4(f32, f32, f32, f32);
extern void fn_8007E7DC(int);
extern void fn_800800D4(int);
extern void fn_80080910(void (*)(void*), void*);
extern void fn_80080308(void);
extern void fn_800F7E40(int);

static inline void F(int tile, u8 a, int x, int y, f32 w, f32 h) {
    C4 c;
    C4 t;
    const u8* cp = fn_800CD204(1);
    c.r = cp[0]; c.g = cp[1]; c.b = cp[2]; c.a = a;
    TexH* q = *(TexH**)fn_80006A0C(lbl_804CB964->arch, tile);
    f32 tw = q->x2;
    f32 th = q->x0;
    *(u32*)&t = *(u32*)&c;
    fn_801BC88C(lbl_804CB964->arch, tile, &t, 0x11, 0, x, y, x + w, y + h, 0.0f, 0.0f, tw, th);
}
static inline void G(int tile, int x, int y, f32 sc) {
    C4 c;
    C4 t;
    const u8* cp = fn_800CD204(1);
    c.r = cp[0]; c.g = cp[1]; c.b = cp[2]; c.a = 0xFF;
    TexH* q = *(TexH**)fn_80006A0C(lbl_804CB964->arch, tile);
    f32 tw = q->x2;
    f32 th = q->x0;
    *(u32*)&t = *(u32*)&c;
    fn_801BC88C(lbl_804CB964->arch, tile, &t, 0x11, 0, x, y, tw * sc + x, th * sc + y, 0.0f, 0.0f, tw, th);
}

static inline u8 Cls(Unit* u) { u8 b = u->x118; if ((s8)b == -1) return u->xEC->xE1; return b; }
void fn_801A6220(f32 x, f32 y) {
    char buf[0x40];
    u8 m0[0x30];
    u8 m1[0x30];
    u8 m2[0x30];
    u8 m3[0x30];
    u8 m4[0x30];
    u8 m5[0x30];
/*P*/
    int xi;
    void* def;
    int w;
    int h;
    int i;
    int yi;
    Unit* u;
    Sel* sel;
    ItemRef* it;
/*E*/
    sel = lbl_804CB964->x320;
    if (sel == 0) return;
    if (sel->u == 0) return;
    fn_801BCA5C(-1.0f);
    xi = (int)x;
    yi = (int)(17.0f + y);
    {
    u16 tile = sel->x0 + 0xB;
    w = 0x150; h = 0x90;
    F(tile, 0xC4, xi, yi, w, h);
    }
    fn_801BCA5C(-1.0f);
    fn_80070688(xi, yi, w, h);
    u = sel->u;
    def = u->xEC;
    fn_801BCA5C(-1.0f);
    for (i = 0; i < 4; i++) fn_80074EB4(xi + 0xC, yi + 0x28 + i * 0x1C, 200, 160);
    fn_801BCA5C(-1.0f);
    fn_801BCA94();
    fn_80290DDC(buf, "%s", fn_80118C44(def));
    fn_800CB278(xi + 0x2A, yi + 0x14, 1, buf);
    {
    ((IconFont*)lbl_803E7290)->draw(xi + 0x12, yi + 0x14, fn_801196F0(Cls(u)));
    }
    fn_801BCA94();
    fn_80290DDC(buf, "%s", fn_80118F00(u->xF0));
    fn_800CB278(xi + 0x12, yi + 0x30, 1, buf);
    fn_800CB278(xi + 0x12, yi + 0x4C, 9, fn_800D0864("MP_LV"));
    fn_800CB278(xi + 0x32, yi + 0x4C, 1, "%2d", u->xFE);
    fn_800CB278(xi + 0x56, yi + 0x4C, 9, fn_800D0864("MP_HP"));
    fn_800CB278(xi + 0x72, yi + 0x4C, 1, "%3d", u->x114);
    fn_800CB278(xi + 0x9E, yi + 0x4C, 0xC, "/%3d", fn_801237EC(u));
    if (fn_8012759C(u)) {
        it = fn_8012759C(u);
        fn_80290DDC(buf, "%s", fn_80110F08(it));
        fn_800CB278(xi + 0x2A, yi + 0x68, 1, buf);
        ((IconFont*)lbl_803E7290)->draw(xi + 0x12, yi + 0x68, (u8)(it->d ? it->d->x16 : 0) + 0x81);
    }
    {
    int y2;
    int x2;
    x2 = (int)(4.0f + x);
    y2 = (int)y;
    G(0xF, x2, y2, 1.0f);
    {
    int ww = 0x128, hh = 0x18;
    F(0x10, 0xFF, x2 + 0x10, y2, ww, hh);
    }
    G(0x11, x2 + 0x138, y2, 1.0f);
    fn_801BCA5C(-1.0f);
    G(0x12, x2 + 0x10, y2 + 6, 1.0f);
    {
    Vec3 v = fn_800FB178(u, 1.0f);
    f32 fy, fx;
    fy = v.y;
    fn_80312654(m0, 0x7A, 0.0f);
    fn_80312DB4(m0, &v, &v);
    fx = v.x;
    fn_8031292C(m1, 4.0f, 4.0f, 4.0f);
    fn_80312654(m3, 0x78, 3.141592f);
    fn_80312654(m4, 0x79, 0.5235988f);
    fn_80312654(m5, 0x78, 0.5235988f);
    fn_803128AC(m2, (f32)(x2 + 0x104) + fx, (f32)(y2 + 0x82) + fy, 120.0f);
    fn_80312378(m3, m1, m0);
    fn_80312378(m4, m0, m0);
    fn_80312378(m5, m0, m0);
    fn_80312378(m2, m0, m0);
    }
    }
    fn_80312344(m0, (u8*)lbl_804CB964->x334 + 0x10);
    fn_80008F20(lbl_804CB964->x334, lbl_804CB964->x339);
    fn_80008F64(lbl_804CB964->x334, 0xFF);
    fn_800081D4(lbl_804CB964->x334);
    fn_80007C58(lbl_804CB964->x334);
    fn_800F629C(u, lbl_804CB964->x334);
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 120.0f, 1.0f);
    fn_8007E174(0, 0x410);
    fn_8007E7DC(0xFF);
    fn_8007E164();
    fn_800800D4(0xB);
    fn_80080910(fn_801A3FF8, lbl_804CB964->x334);
    fn_80080308();
    fn_800F7E40(0x32);
    fn_801BCA5C(5.0f);
}
}
