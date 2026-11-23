#include "game/rG_800A3D88/types.h"

// Text widget: centre a string inside its parent window and draw it.
extern "C" {
struct WB { int x; };
class Win : public WB {
public:
    virtual int v0();
    virtual int v1();
    virtual int v2();
    virtual int v3();
    virtual int v4();
    virtual int v5();
    virtual int v6();
    virtual int v7();
    virtual int v8();
    virtual int v9();
    virtual int v10();
    virtual int v11();
    virtual int v12();
    virtual int v13();
    virtual int v14();
    virtual int v15();
    virtual int v16();
    virtual int v17();
    virtual int v18();
    virtual int v19();
    virtual int v20();
    virtual int v21();
};
struct Par { u8 p[0x3C]; Win* m3c; };
struct Box { u8 p[0x32]; s16 m32; };
class Txt {
public:
    virtual void* v0();
    virtual const char* v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18(Par*);
};
int fn_800CB0FC(int, f32);
int fn_800CA3DC(const char*, int, f32);
void fn_800800D4(int);
void fn_80080330(f32, f32);
void fn_800804D4(int, int, int, int);
void fn_80080C24(const char*);
void fn_80080308();
void fn_8007E154();
void fn_8007E720(f32);
void fn_8007E164();
void fn_800A3D88(Txt* t, Par* p, Box* b) {
    s16 h = p->m3c->v21();
    s16 y = b->m32 + ((h - fn_800CB0FC(-1, 1.0f)) >> 1);
    s16 w = p->m3c->v18();
    int x = (w - fn_800CA3DC(t->v1(), -1, 1.0f)) / 2;
    f32 fx = x;
    t->v18(p);
    fn_800800D4(5);
    fn_80080330(fx, y);
    fn_800804D4(0, 0, 0, 0xFF);
    fn_80080C24(t->v1());
    fn_80080308();
    fn_8007E154();
    fn_8007E720(1.0f);
    fn_8007E164();
}
}
