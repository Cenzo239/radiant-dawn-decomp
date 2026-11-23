#include "game/rL_80133EB4/map3d.h"
#pragma use_lmw_stmw on
extern "C" {
extern u8 lbl_804CB830;
extern u8 lbl_803EC898[];
extern u32 lbl_804CB5F4;
extern MapModel* lbl_804CB860;

extern void fn_8013450C(QTNode*, QTNode*);
extern void fn_80134F90(MapModel*);
extern void fn_801CC2BC(Mesh*, int, int);
extern void fn_80010788(int, int, void*, void*);
extern void fn_80137724(void*);
extern void fn_8013531C(MapModel*);
extern u8* fn_8000F470(void);
extern void fn_80257948(Vec*, Vec*, Vec*);
extern void fn_80312318(void*, f32);
extern void fn_80312654(void*, int, f32);
extern void fn_8031292C(void*, f32, f32, f32);
extern void fn_80312344(void*, void*);
extern void fn_80312378(void*, void*, void*);
extern void fn_802727A0(void*, void*);
extern void fn_8025095C(f32,f32);
extern void fn_80250A08(f32,f32);
extern void fn_80257AC0(f32,f32);
extern void fn_80257B6C(f32,f32);
extern void fn_80257A14(f32,f32);
extern u8* fn_80010BB0(int);
extern u8* fn_80010DA4(u8*,int);
extern f32 fn_8001EF30(f32,f32,f32,f32);

struct Color{u8 r,g,b,a;};
extern Color lbl_80413BF8[];
extern Color lbl_80413BE8[];
struct Env { u8 pad[0x6a]; u8 x6a,x6b; f32 x6c,x70,x74; };

static inline f32 Lerp(u8 a,u8 b,int p){ return fn_8001EF30(a,b,100.0f,p); }
void fn_8013B2B8(MapModel* mm) {
    if (mm->flags & 0x40) {
        int total=0;
        int sum=0;
        int i;
        for(i=0;i<mm->nMesh;i++){
            Mesh* m=MeshAt(mm,i);
            if(m->group->flags&0x10000000){
                total+=0xff;
                if(!(m->flags&4)) sum+=((u8*)m)[0xcd];
            }
        }
        if(total>0){
            int p=sum*100/total;
            u8* l=fn_80010BB0(0);
            if(l){
                {Color a=lbl_80413BF8[0];Color b=lbl_80413BF8[2];
                l[2]=Lerp(a.r,b.r,p); l[3]=Lerp(a.g,b.g,p); l[4]=Lerp(a.b,b.b,p);}
                l=fn_80010DA4(l,1);
                if(l){Color a=lbl_80413BE8[0];Color b=lbl_80413BE8[2];
                l[4]=Lerp(a.r,b.r,p); l[5]=Lerp(a.g,b.g,p); l[6]=Lerp(a.b,b.b,p);}
            }
        }
    }
}

#if TARGET_PC
extern FE10_PROTO void * fn_80076F54(const char*);
#else
extern int fn_80076F54(const char*);
#endif
extern int* fn_80077064(const char*);
extern int fn_80291188(const char*, const char*);
extern char lbl_803694D4[];
extern char lbl_8036969B[];
extern char lbl_803696A2[];
extern char lbl_80369673[];
struct SndMap { char* name; u8 a, b; u8 pad[2]; f32 x, y, z; };
struct Env2 { u8 pad[0x6A]; u8 a, b; f32 x, y, z; };
extern MapModel* fn_8013B9A8(void);
extern int fn_801CA1E8(Mesh*);
extern int fn_801CA228(Mesh*);
extern int fn_801CA218(Mesh*);
extern int fn_801CA260(Mesh*);
extern void fn_801379F8(MapModel*, int);
void fn_8013BC74(void* a, int all) {
    Mesh* list[66];
    MapModel* mm = fn_8013B9A8();
    if (mm) {
        int n = 0;
        int i;
        for (i = 0; i < mm->nMesh; i++) {
            Mesh* m = MeshAt(mm, i);
            if (fn_801CA1E8(m) && fn_801CA228(m) == 0 && (all || fn_801CA218(m) == 0) && fn_801CA260(m)) {
                list[n++] = m;
                m->flags |= 8;
            }
        }
        fn_801379F8(mm, 0);
        for (i = 0; i < n; i++) list[i]->flags &= ~8;
    }
}
class QO;
struct Quake { u8 pad[0x30]; int x30, x34, x38, x3c; f32 x40; QO* x44; };
struct QB { u8 pad[0x6C]; };
class QO : public QB { public: virtual void v08(Vec*); };
extern Vec lbl_803696C0;
extern f64 fn_80295940(f32);
extern void fn_803134A8(f32, Vec*, Vec*);
extern void fn_80312654(void*, int, f32);
extern void fn_80312DB4(void*, Vec*, Vec*);
extern void* fn_8000FB88(void);
extern void fn_80312444(void*, void*);
extern u32 fn_80089ED0(void);
extern void fn_80083B78(void*);
extern f32 fn_8001EF30(f32, f32, f32, f32);
void fn_8013BEE4(Quake* q) {
    u8 m0[0x30];
    u8 m1[0x30];
    Vec v = lbl_803696C0;
    q->x3c++;
    f32 s = fn_80295940(fn_8001EF30(0.0f, 6.2831855f, q->x38, q->x3c));
    fn_803134A8(s * q->x40, &v, &v);
    fn_80312654(m0, 0x7A, 0.017453292f * q->x34);
    fn_80312DB4(m0, &v, &v);
    fn_80312444(fn_8000FB88(), m1);
    fn_80312DB4(m1, &v, &v);
    {
        Vec t = v;
        q->x44->v08(&t);
    }
    if (q->x3c >= q->x38) {
        q->x3c = 0;
        if (q->x30 > 0) q->x30--;
        if (q->x30 == 0) {
            fn_80083B78(q);
        } else {
            q->x34 = fn_80089ED0() % 360;
        }
    }
}

struct SndEnv { void* name; char* snd; u8 a, b; u8 pad[2]; Vec pos; };
#if TARGET_PC
extern FE10_PROTO char * fn_80291480(const char*, const char*);
#else
extern int fn_80291480(const char*, const char*);
#endif
extern Mesh* fn_80135934(MapModel*, int, u32, u32);
extern void fn_801CA5D4(Vec*, Mesh*);
extern void fn_8027247C(f32, void*, u8, char*, u8, Vec*, void*);
void fn_8013A8D8(MapModel* mm, void* arg) {
    SndEnv* found[0x10];
    Vec pos;
    int fire;
    char* s;
    u8* out;
    int n;
    SndEnv** w2;
    char* name;
    const char* f;
    int c;
    SndEnv* e;
    int i;
    SndEnv** w;
    int i2;
    SndEnv* e2;
    u8 b;
    Mesh* m;
    f32 vol;
    name = mm->name;
    if (name && mm->xb1 != 3) {
        w = found;
        n = 0;
        f = lbl_803694D4 + 0x19F;
        if (fn_80076F54(f)) {
            int* d = fn_80077064(f);
            c = *d;
            e = (SndEnv*)(d + 1);
            for (i = 0; i < c; i++, e++) {
                if (e->name && fn_80291188((char*)e->name, name) == 0) {
                    *w++ = e;
                    n++;
                }
            }
        }
        w2 = found;
        out = (u8*)mm->lights;
        fire = 0;
        for (i2 = 0; i2 < n; w2++, out += 0x18, i2++) {
            e2 = *w2;
            m = 0;
            vol = 1.0f;
            pos = e2->pos;
            b = e2->b;
            if (e2->snd && fn_80076F54(e2->snd)) {
                s = e2->snd;
                if ((char*)fn_80291480(s, lbl_803694D4 + 0x1AC) == s) {
                    m = fn_80135934(mm, fire++, 0x10000000, 0x10);
                    if (m == 0) continue;
                    vol = 0.0f;
                    {
                        Vec t;
                        fn_801CA5D4(&t, m);
                        pos = t;
                    }
                }
                {
                    Vec t2 = pos;
                    fn_8027247C(vol, out, e2->a, e2->snd, b, &t2, arg);
                }
                *(Mesh**)(out + 0x14) = m;
            }
        }
    }
}
}
