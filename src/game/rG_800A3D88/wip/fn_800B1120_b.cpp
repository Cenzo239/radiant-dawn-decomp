// WIP, does not match: 19/264 lines, right size. nm wants r31 and k1/b/e want r22; ours has them swapped. Moving e's body into an inline gives nm r31 but shifts the hoisted addresses by one. Replaces wip/fn_800B1120.cpp.
#include "game/rG_800A3D88/types.h"

// Battle character: load the model files named by its data entry.
extern "C" {
struct Bone { u8 p[0xC]; u32 mC; u8 p10[0xEC - 0x10]; u32 ec; };
struct MdlB { u32 flags; u8 p4[0x88 - 4]; void* m88; };
struct Data { u8 p[4]; const char* name; };
struct ChrL {
    u8 p[0x30];
    MdlB* mdl;
    void* m34;
    u8 p38[0x50 - 0x38];
    u32 m50;
    u8 p54[0x60 - 0x54];
    u8 m60;
    u8 p61[0x78 - 0x61];
    Data* data;
};
struct EyeP { u8 p[0x30]; void* m30; ChrL* m34; int m38; s8 m3c; u8 p3d[0x44 - 0x3D]; f32 m44, m48; u8 p4c[4]; s16 m50, m52, m54; u16 m56; };
extern char lbl_803657E8[];
extern const char* lbl_80382538[6];
extern u8 lbl_80382550[];
#define S(a) (lbl_803657E8 + ((a) - 0x803657E8))
long long OSGetTime();
int fn_80290DDC(char*, const char*, ...);
int fn_8023F9F4(const char*);
void fn_800B2710(ChrL*);
void* fn_8023F1A4(const char*, int);
MdlB* fn_80006E1C();
void fn_80009214(MdlB*, const char*, int);
void fn_80009274(MdlB*, const char*, int);
void fn_80006F20(MdlB*);
void fn_80009C7C(MdlB*, int);
void fn_80008F64(MdlB*, int);
void* fn_80007F3C(MdlB*);
void fn_80014E24(void*, const char*, void*, int);
void fn_800B053C(void*, void*);
void fn_800B0554(void*, void*);
void fn_800B0340(void*);
void fn_80008F54(MdlB*, int);
void fn_80008F5C(MdlB*, int);
void* fn_800A7460(Data*, const char*);
f32 fn_800A7370(Data*, const char*);
u8 fn_8001E044(f32);
void* fn_800AAD2C();
int fn_80007630(MdlB*, const char*);
void* fn_80007EE4(MdlB*);
Bone* fn_8000F3D4(void*, int);
EyeP* fn_80081050(void*, void*);
f32 fn_800A84A4(const char*);
void fn_800AFC3C(EyeP*);
void fn_800B33F4(ChrL*, int);
static inline int Flag(ChrL* c) {
    int f = 0x40;
    if (c->m50 & 0x4000000) f = 0x20;
    return f;
}
static inline const char* Nm(int i, const char** q) {
    if (i < 0 || i >= 6) return NULL;
    return *q;
}
static inline Bone* Find(ChrL* c, const char* n, int& k) {
    k = fn_80007630(c->mdl, n);
    if (k < 0) return NULL;
    return fn_8000F3D4(fn_80007EE4(c->mdl), k);
}
static inline BOOL Exists(ChrL* c, char* buf) {
    if (c->data == NULL) return 0;
    fn_80290DDC(buf, S(0x8036583B), c->data->name);
    return fn_8023F9F4(buf) != 0x40000;
}
#pragma use_lmw_stmw on
int fn_800B1120(ChrL* c) {
    char buf[0x40];
/*P*/
Bone* b;
int k1;
int i;
const char** nm;
Bone* b3;
int k2;
u32 w;
int n;
int j;
int k3;
const char** nm2;
EyeP* e;
void* eye;
/*E*/

    OSGetTime();
    if (c->data == NULL) return 0;
    if (!Exists(c, buf)) return 0;
    fn_800B2710(c);
    c->m34 = fn_8023F1A4(buf, c->m50 & 0x4000000 ? 0x20 : 0x40);
    c->mdl = fn_80006E1C();
    c->mdl->flags |= 0x800;
    c->mdl->flags |= 0x40000;
    fn_80290DDC(buf, S(0x80365873), c->data->name);
    fn_80009214(c->mdl, buf, c->m50 & 0x4000000 ? 0x20 : 0x40);
    fn_80290DDC(buf, S(0x80365881), c->data->name);
    fn_80009274(c->mdl, buf, c->m50 & 0x4000000 ? 0x20 : 0x40);
    fn_80006F20(c->mdl);
    fn_80009C7C(c->mdl, 0x100);
    fn_80008F64(c->mdl, 0xFF);
    fn_80014E24(fn_80007F3C(c->mdl), 0, fn_800B053C, 2);
    fn_80014E24(fn_80007F3C(c->mdl), 0, fn_800B0554, 4);
    c->mdl->m88 = c;
    fn_80014E24(fn_80007F3C(c->mdl), S(0x80365892), fn_800B0340, 2);
    fn_80008F54(c->mdl, 0x87);
    fn_80008F5C(c->mdl, 2);
    if (fn_800A7460(c->data, S(0x80365898))) c->m50 |= 2;
    else c->m50 &= ~2;
    c->m60 = fn_8001E044(fn_800A7370(c->data, S(0x8036589F)));
    eye = fn_800AAD2C();
    if (eye != NULL) {
        for (nm = lbl_80382538, i = 0; i < 6; i++, nm++) {
            b = Find(c, Nm(i, nm), k1);
            if (b != NULL) {
                e = fn_80081050(lbl_80382550, c);
                w = b->ec >> 20;
                e->m30 = eye;
                e->m34 = c;
                e->m44 = fn_800A84A4(S(0x803657E8));
                e->m48 = fn_800A84A4(S(0x803657F3));
                e->m54 = (int)fn_800A84A4(S(0x803657FE));
                e->m52 = (int)fn_800A84A4(S(0x80365805));
                e->m56 = w;
                n = 0;
                for (nm2 = lbl_80382538, j = 0; j < 6; j++, nm2++) {
                    if (Find(c, Nm(j, nm2), k2) != NULL) n++;
                }
                e->m3c = n;
                e->m50 = i;
                e->m38 = 0;
                fn_800AFC3C(e);
            }
        }
    }
    b3 = Find(c, S(0x803658AA), k3);
    if (b3 != NULL) b3->mC |= 0x20000000;
    fn_800B33F4(c, 0);
    OSGetTime();
    return 1;
}
}
