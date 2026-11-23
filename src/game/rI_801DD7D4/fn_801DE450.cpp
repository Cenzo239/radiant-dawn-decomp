/* fn_801DE450: draws one menu entry: optional icon, then its label centred in the menu width. */
#include "game/rI_801DD7D4/types.h"
#pragma auto_inline off
extern "C" {
int fn_800CB0FC(f32, int);
int fn_800CA3DC(f32, const char*, int);
void fn_800800D4(int);
void fn_80080330(f32, f32);
void fn_80080C24(const char*);
void fn_80080308(void);
void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E7E8(int);
}
struct Ent;
class EntI { public: virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual const char* v18(Ent*); virtual int v1C(); virtual int v20(); };
struct Ent { u8 p[0x30]; s16 x30, x32; EntI* x34; };
struct Met { int a0; virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C(); virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34(); virtual int v38(); virtual int v3C(); virtual int v40(); virtual int v44(); virtual int v48(); virtual int v4C(); virtual int v50(); virtual int v54(); virtual int v58(); virtual int v5C(); };
struct Menu { u8 p[0x3c]; Met* x3c; };
struct Icons { u8 p[0x44]; virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual void v18(int, int, int); virtual int v1C(); virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34(); virtual int v38(); virtual int v3C(); virtual int v40(); virtual int v44(); virtual int v48(); virtual int v4C(); };
extern "C" Icons lbl_803E7290;
static inline Icons* icons() { return &lbl_803E7290; }
class Dr { public: virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C(); virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34(); virtual int v38(); virtual int v3C(); virtual int v40(); virtual int v44(); virtual int v48(); virtual int v4C(); virtual int v50(); virtual int v54(Menu*, Ent*); };
extern "C" void fn_801DE450(Dr* o, Menu* a, Ent* b) {
    int iw;
    int dy;
    int iy;
    s16 h;
    s16 tw;
    f32 x, y;
    o->v50();
    if (b->x34->v20()) iw = icons()->v4C(); else iw = 0;
    h = a->x3c->v5C();
    dy = (h - fn_800CB0FC(1.0f, -1)) >> 1;
    h = a->x3c->v5C();
    iy = (h - icons()->v4C()) >> 1;
    tw = fn_800CA3DC(1.0f, b->x34->v18(b), -1);
    x = b->x30 + (((s16)a->x3c->v58() - (tw + iw)) >> 1);
    y = b->x32;
    fn_800800D4(5);
    fn_80080330(x + iw, y + dy);
    o->v54(a, b);
    fn_80080C24(b->x34->v18(b));
    fn_80080308();
    if (b->x34->v20()) {
        icons()->v18((int)x, (int)(y + iy), b->x34->v20());
    }
    fn_8007E154();
    fn_8007E7E8(0x80);
    fn_8007E164();
}
