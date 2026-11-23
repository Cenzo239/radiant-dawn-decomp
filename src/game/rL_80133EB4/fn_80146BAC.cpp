#include "game/rL_80133EB4/map3d.h"
#pragma auto_inline off
#pragma use_lmw_stmw on
extern "C" {
struct WeatherP {
    u8 pad0[0x30];
    u8 x30, x31, x32, x33, x34, pad35;
    s16 x36;
    f32 x38, x3c, x40;
    u8 pad44[4];
    Vec dir;      /* 0x48 */
    Vec lo;       /* 0x54 */
    Vec hi;       /* 0x60 */
    f32 x6c, x70;
    u8 pad74[4];
    u8 x78, x79, x7a, pad7b;
    void* x7c;
};
struct Layer {
    u8 pad0[0x30];
    f32 x30;
    f32 x34;
    void* x38;
};
struct Particle { void* n; void* p; u8 pad[0x18]; };
struct ParticleList { Particle* a; Particle** b; Particle** c; void* d; void* e; int f; int g; };
struct RainP {
    u8 pad0[0x30];
    u8 x30; s8 x31; u8 x32, pad33;
    f32 x34;
    void* x38;
    ParticleList* x3c;
};
static u8 s80386490[0x24];
static u8 s803864B4[0x24];
static u8 s803864D8[0x20];
static u8 s803864F8[0x24];
static u8 s8038651C[0x24];
static u8 s80386540[0x20];
extern u8 lbl_80369AF8[];
extern char lbl_80369B0D[];
extern char lbl_804CA72C[8];
extern char lbl_804CA728[4];
extern char lbl_804CA724[4];
extern void* fn_80083B84(void*);
extern void* fn_80081050(void*, void*);
extern void* fn_8001D3B4(void*);
extern void fn_80082230(void*);
extern MapModel* fn_8013B9A8(void);
#if TARGET_PC
extern FE10_PROTO void fn_80135F90(MapModel*, p32arg, void*, int, int, p32arg);
#else
extern void fn_80135F90(MapModel*, int, void*, int, int, int);
#endif
extern void fn_801444B8(void);
extern void fn_801461D8(void*);
extern void fn_8014531C(RainP*);
extern void fn_80144888(void*);
extern void* fn_800E4060(const char*, void*);
extern int fn_8013B664(MapModel*);
extern void* fn_80078CCC(int, const char*, int);
extern void DCFlushRange(void*, u32);
extern void fn_803134A8(f32, Vec*, Vec*);

struct W1 { u8 pad0[0x30]; f32 x30; f32 x34; void* x38; };
struct WD { u8 pad0[0x30]; u8 x30; };
struct WF { u8 pad0[0x30]; u8* x30; };

void fn_80146BAC(WeatherP* w, int kind) {
    if (w->x31 != kind) {
        fn_80082230(w);
        w->x31 = kind;
        if (w->x32 == 0) {
            switch (kind = (u8)kind) {
            case 1:
            case 2:
            {
                W1* a = (W1*)fn_80081050(s80386490, w);
                WeatherP* b = (WeatherP*)fn_80083B84(s80386540);
                b->x3c = 0.1f;
                b->dir.x = 0.1f;
                b->dir.y = 0.05f;
                b->dir.z = 0.0f;
                b->x34 = 0;
                a->x30 = 0.0f;
                a->x34 = 0.0f;
                a->x38 = fn_8001D3B4(lbl_80369AF8);
                fn_80135F90(fn_8013B9A8(), 0, (void*)fn_801444B8, 0, 0x40E0, 2);
                break;
            }
            case 4:
                { void* q = fn_80081050(s803864F8, w); fn_801461D8(q); WeatherP* b = (WeatherP*)fn_80083B84(s80386540); b->x34 = 0x80; }
                break;
            case 5:
                { void* q = fn_80081050(s803864F8, w); fn_801461D8(q); WeatherP* b = (WeatherP*)fn_80083B84(s80386540); b->x34 = 0x40; }
                break;
            case 6:
                { void* q = fn_80081050(s803864F8, w); fn_801461D8(q); WeatherP* b = (WeatherP*)fn_80083B84(s80386540); b->x34 = 0xFF; }
                break;
            case 7:
            case 8:
            case 9:
            case 0x13:
            {
                RainP* r = (RainP*)fn_80081050(s803864D8, w);
                r->x30 = kind;
                fn_8014531C(r);
                break;
            }
            case 0xB:
            {
                WD* d = (WD*)fn_80081050(s803864B4, w);
                d->x30 = 0;
                fn_80144888(d);
                break;
            }
            }
        } else {
            switch (kind = (u8)kind) {
            case 4:
                { void* q = fn_80081050(s803864F8, w); fn_801461D8(q); WeatherP* b = (WeatherP*)fn_80083B84(s80386540); b->x34 = 0x80; }
                break;
            case 5:
                { void* q = fn_80081050(s803864F8, w); fn_801461D8(q); WeatherP* b = (WeatherP*)fn_80083B84(s80386540); b->x34 = 0x40; }
                break;
            case 6:
                { void* q = fn_80081050(s803864F8, w); fn_801461D8(q); WeatherP* b = (WeatherP*)fn_80083B84(s80386540); b->x34 = 0xFF; }
                break;
            case 7:
            case 8:
            case 9:
            case 0x13:
            {
                RainP* r = (RainP*)fn_80081050(s803864D8, w);
                r->x30 = kind;
                fn_8014531C(r);
                break;
            }
            case 0xB:
            {
                WD* d = (WD*)fn_80081050(s803864B4, w);
                d->x30 = 0;
                fn_80144888(d);
                break;
            }
            case 0xC:
            case 0x14:
            {
                WF* f = (WF*)fn_80081050(s8038651C, w);
                u8* e = (u8*)fn_800E4060((char*)lbl_80369AF8 + 0x15, f);
                f->x30 = e;
                if (e) {
                    *(s16*)(*(u8**)(e + 0x30) + 8) = 800;
                    *(u32*)(*(u8**)(f->x30 + 0x30) + 0x18) |= 4;
                    *(u32*)(*(u8**)(f->x30 + 0x30) + 0x18) &= ~0x8000;
                }
                break;
            }
            }
        }
        {
            MapModel* mm = fn_8013B9A8();
            if (mm) {
                int v = fn_8013B664(mm);
                switch (w->x31) {
                case 0x13:
                    w->x34 = v * 0xFF / 100;
                    break;
                default:
                    break;
                }
            }
        }
    }
}


struct DriftP {
    u8 pad0[0x30];
    u8 x30, pad31[3];
    f32 u[2];
    f32 pad3c0;
    /* placeholder */
};
struct DP2 { u8 pad0[0x34]; f32 a0; f32 a1; f32 b0; f32 b1; Vec cam; void* tex; };
extern u8* fn_8000F470(void);
extern int fn_80068D74(void);
#if TARGET_PC
extern FE10_PROTO void fn_80011B90(p32arg, Vec*, Vec*);
#else
extern void fn_80011B90(int, Vec*, Vec*);
#endif
extern void fn_8007E154(void);
extern void fn_8007E4E4(f32, f32, f32, f32);
#if TARGET_PC
extern FE10_PROTO void fn_8007E374(void*, p32arg, int);
#else
extern void fn_8007E374(void*, int, int);
#endif
extern void fn_8007E164(void);
extern void fn_800800D4(int);
#if TARGET_PC
extern FE10_PROTO void fn_80080910(ptr32<const void>, ptr32<const void>);
#else
extern void fn_80080910(void*, void*);
#endif
extern void fn_80080308(void);
extern void fn_801445E8(void*);
struct PNode { PNode* n; PNode* p; u8 x8[0x18]; };
struct PL { PNode** a; PNode** b; PNode** c; PNode* d; PNode* e; int f; };
struct RP2 { u8 pad0[0x30]; u8 x30, x31, x32, pad33; f32 x34; void* x38; PL* x3c; };
extern void fn_80145078(RP2*, WeatherP*);
extern int fn_80144BAC(void*, Vec*, u8);
extern void fn_80010788(int, int, void*, void*);
extern void fn_80144CD0(void*);
#if TARGET_PC
/* Host: fe10/gekko.h */
static inline void OSInitFastCast(void) { fe10_fastcast_init(); }
#else
static inline void OSInitFastCast(void) {
    asm {
        li r3, 4
        oris r3, r3, 4
        mtspr 0x392, r3
        li r3, 5
        oris r3, r3, 5
        mtspr 0x393, r3
        li r3, 6
        oris r3, r3, 6
        mtspr 0x394, r3
        li r3, 7
        oris r3, r3, 7
        mtspr 0x395, r3
    }
}
#endif
static inline PNode* Next(PL* l, PNode* q) {
    if (q == 0) return l->d;
    return q->n;
}
void fn_80145704(RP2* r) {
    int i;
    int n = 1;
    WeatherP* w = (WeatherP*)fn_80083B84(s80386540);
    if (w->x30 && (w->x32 || fn_80068D74())) {
        OSInitFastCast();
        if (r->x32) n = 0x3C;
        r->x32 = 0;
        for (i = 0; i < n; i++) {
            {
                int j;
                for (j = 0; j < w->x33; j++) fn_80145078(r, w);
            }
            {
                PNode* q = 0;
                while ((q = Next(r->x3c, q)) != 0) {
                    if (fn_80144BAC(q->x8, &w->dir, w->x34) == 0) {
                        PL* l = r->x3c;
                        if (q) {
                            if (q->n) q->n->p = q->p;
                            if (q->p) q->p->n = q->n;
                            if (q == l->d) l->d = q->n;
                            if (q == l->e) l->e = q->p;
                            *--l->c = q;
                            l->f--;
                        }
                    }
                }
            }
        }
        fn_80010788(3, 0x9B, (void*)fn_80144CD0, r);
    }
}
extern int fn_80011F38(void);
extern int fn_80011E28(void);
extern int fn_80011EB4(void);
extern int fn_80011FC4(void);
extern void fn_80019D9C(void*);
#if TARGET_PC
extern FE10_PROTO void fn_8000FEA0(p32arg, void*);
#else
extern void fn_8000FEA0(int, void*);
#endif
extern void fn_80312378(void*, void*, void*);
extern void fn_800F8810(void*);
extern void fn_80022254(void*, int);
extern void fn_80307F10(void*, int, int);
extern void fn_80021F7C(int, int, int, int);
extern void fn_80021CB4(int, int, int, int);
extern void fn_80021E20(int, int, int, int, int);
extern void fn_80021D18(int, int, int, int, int, int);
extern void fn_80021E8C(int, int, int, int, int);
extern void fn_80021D9C(int, int, int, int, int, int);
extern void fn_80021808(int, int, int, int, int);
void fn_80142C44(void) {
    u8 tex[0x20];
    u8 view[0x30];
    u8 cam[0x30];
    int b;
    int a;
    int c;
    int d;
    a = fn_80011F38();
    b = fn_80011E28();
    c = fn_80011EB4();
    d = fn_80011FC4();
    fn_80019D9C(cam);
    fn_8000FEA0(0, view);
    fn_80312378(view, cam, view);
    fn_800F8810(tex);
    fn_80022254(tex, c);
    fn_80307F10(view, d, 0);
    fn_80021F7C(a, 0, 0, d);
    fn_80021CB4(b, a, c, 4);
    fn_80021E20(b, 0xF, 0xF, 0xF, 0);
    fn_80021D18(b, 0, 0, 0, 1, 0);
    fn_80021E8C(b, 7, 6, 4, 0);
    fn_80021D9C(b, 1, 0, 0, 1, 0);
    fn_80021808(4, 0, 1, 0, 0);
}
struct GXC4 { u8 r, g, b, a; };
extern void* fn_80007F10(void*);
extern void fn_80305A40(void*, void*, int, int, int, int, int, int);
extern void fn_80305C94(void*, int, int, int, int, int, f32, f32, f32);
extern int fn_80012170(void);
extern int fn_800121C8(int);
extern void fn_80306EA0(int, GXC4);
extern void fn_80021FF0(int, int);
#if TARGET_PC
extern FE10_PROTO void fn_80141334(p32arg);
#else
extern void fn_80141334(int);
#endif
extern int fn_80011E80(void);
void fn_80143180(void* arg) {
    u8 tex[0x20];
    u8 m0[0x30];
    u8 m1[0x30];
    MapModel* mm = fn_8013B9A8();
    if (mm) {
        u8* o = (u8*)mm->x10;
        o = *(u8**)((u8*)mm + 0x14);
        if (o && ((u8*)mm)[0x57]) {
            int b, a, c, d, e, f;
            fn_80007F10(arg);
            fn_80019D9C(m0);
            fn_8000FEA0(0, m1);
            fn_80312378(m1, m0, m1);
            fn_80305A40(tex, *(void**)(o + 0x3C), 0x130, 0x1C0, 4, 0, 0, 0);
            fn_80305C94(tex, 1, 1, 0, 0, 0, 0.0f, 0.0f, 0.0f);
            a = fn_80011F38();
            b = fn_80011E28();
            c = fn_80011EB4();
            d = fn_80011FC4();
            e = fn_80012170();
            f = fn_800121C8(e);
            {
                u8 v = ((u8*)mm)[0x57];
                GXC4 col;
                col.r = v;
                col.g = v;
                col.b = v;
                col.a = v;
                fn_80306EA0(e, col);
            }
            fn_80021FF0(b, f);
            fn_80307F10(m1, d, 0);
            fn_80021F7C(a, 0, 0, d);
            fn_80022254(tex, c);
            fn_80021CB4(b, a, c, 4);
            fn_80021E20(b, 0, 8, 0xE, 0xF);
            fn_80021D18(b, 0, 0, 0, 1, 0);
            fn_80021E8C(b, 7, 7, 7, 0);
            fn_80021D9C(b, 0, 0, 0, 1, 0);
            if (((u8*)mm)[0x60] & 2) fn_80141334(b);
        }
    }
}

extern Vec lbl_80369994;
#if TARGET_PC
extern FE10_PROTO void fn_800138B8(void*, void*, void*, p32arg, p32arg);
#else
extern void fn_800138B8(void*, void*, void*, int, int);
#endif
extern void fn_80313484(Vec*, Vec*, Vec*);
extern f32 fn_80313508(Vec*);
extern void fn_803134C4(Vec*, Vec*);
#if TARGET_PC
extern FE10_PROTO void fn_800125A8(void*, void*, void*, p32arg);
extern FE10_PROTO void fn_80013CF0(void*, void*, p32arg);
#else
extern void fn_800125A8(void*, void*, void*, int);
extern void fn_80013CF0(void*, void*, int);
#endif
extern void fn_800140A0(void*, void*);
void fn_80143054(void* a, void* b, int c, int d) {
    u8 m[0x30];
    void* e = fn_80007F10(a);
    MapModel* mm;
    fn_80019D9C(m);
    fn_800138B8(a, e, b, c, d);
    mm = fn_8013B9A8();
    if (mm && *(void**)((u8*)mm + 0x14)) {
        if (((u8*)mm)[0x60] & 1) {
            fn_80141334(fn_80011E80());
        }
        {
            u8* cam = fn_8000F470();
            Vec v = lbl_80369994;
            fn_80313484((Vec*)(cam + 0xE0), (Vec*)(cam + 0xD4), &v);
            if (fn_80313508(&v) > 0.0f) {
                fn_803134C4(&v, &v);
                if (v.y < 0.0f) v.y *= -1.0f;
            }
            fn_800125A8(a, e, b, c);
            fn_80013CF0(a, b, c);
            fn_800140A0(a, b);
        }
    }
}
struct SnowP {
    u8 pad0[0x30];
    u8 x30; s8 x31; u8 x32; u8 pad33;
    u16 x34, x36;
    s8 x38;
    u8 pad39[3];
    void* x3c;
    void* x40;
    s16* x44;
    u8* x48;
};
extern u8 lbl_803EC898[];
extern int fn_80007630(void*, const char*);
extern u8* fn_800080B8(void*);
extern char lbl_80369B08[];
extern Vec lbl_80369AA4;
extern Vec lbl_80369AB0;
extern void fn_8031292C(void*, f32, f32, f32);
extern void fn_80312DB4(void*, Vec*, Vec*);
extern void* fn_800791B0(int);
extern u32 fn_80089ED0(void);
void fn_801461D8(void* s_) { SnowP* s = (SnowP*)s_;
    WeatherP* w = (WeatherP*)fn_80083B84(s80386540);
    u8 mtx[0x30];
    s->x30 = 1;
    s->x38 = -1;
    s->x36 = 0x100;
    s->x34 = 0x100;
    s->x32 = 0x10;
    switch (w->x32) {
    case 0:
        w->lo.x = -8.0f;
        w->lo.y = 0.01f;
        w->lo.z = -8.0f;
        w->hi.x = *(int*)lbl_803EC898 + 8;
        w->hi.y = 0.01f;
        w->hi.z = *(int*)(lbl_803EC898 + 4) + 8;
        s->x31 = 1;
        break;
    case 1:
    case 2:
    case 3:
    case 4:
        w->lo.x = -32.0f;
        w->lo.y = 0.01f;
        w->lo.z = -32.0f;
        w->hi.x = 32.0f;
        w->hi.y = 0.01f;
        w->hi.z = 32.0f;
        s->x31 = 5;
        break;
    }
    {
        void* o = w->x7c;
        if (o) {
            int k = fn_80007630(o, (char*)lbl_80369AF8 + 0x10);
            if (k >= 0) {
                u8* tbl = fn_800080B8(o);
                {
                    Vec a = lbl_80369AA4;
                    w->lo = a;
                }
                {
                    Vec a = lbl_80369AB0;
                    w->hi = a;
                }
                fn_8031292C(mtx, 1.0f / s->x31, 1.0f / s->x31, 1.0f / s->x31);
                fn_80312378(mtx, tbl + k * 0x30, mtx);
                fn_80312DB4(mtx, &w->lo, &w->lo);
                fn_80312DB4(mtx, &w->hi, &w->hi);
            }
        }
    }
    s->x3c = fn_8001D3B4(lbl_80369AF8);
    s->x40 = fn_800791B0((s->x34 << 3) * 6);
    {
        u32 a, b;
        s16* q;
        int i;
        s->x44 = (s16*)fn_800791B0(((s->x36 << 1)) * 6);
        q = s->x44;
        a = (int)(256.0f * (w->hi.x - w->lo.x));
        b = (int)(256.0f * (w->hi.z - w->lo.z));
        for (i = 0; i < s->x36 * 2; i += 2) {
            u32 r = fn_80089ED0();
            q[0] = q[3] = r % a;
            r = fn_80089ED0();
            q[2] = q[5] = r % b;
            r = fn_80089ED0();
            q[1] = r % 0x300;
            q[4] = q[1] + 0x100;
            q += 6;
        }
    }
    DCFlushRange(s->x44, s->x36 * 0xC);
    s->x48 = (u8*)fn_800791B0(s->x32 * 8);
    {
        int i;
        for (i = 0; i < s->x32; i++) {
            *(f32*)(s->x48 + i * 8 + 4) = -1.0f;
        }
    }
}
}
