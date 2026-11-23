/* fn_801959A0 (0x1428): exact (round m7) with fn_801959A0.symbols.json
   (check_func.py --symbol-map fn_801959A0.symbols.json --strict-references).
   Lever: the memory stream on the stack is a real class hierarchy instead of a struct with hand-written vtable
   stores: MB (buffer, vtable lbl_80380940, constructor `own = 0`, destructor frees an owned buffer), MB2 : MB
   (vtable lbl_80380928, constructor sets own/p/q/n/z) and SS holding an MB2 with its own vptr after it (vtable
   lbl_80388858). The base constructor's dead `own = 0` creates the zero before the derived vtable address, which
   gives the original registers (vtable r4, zero r5); the destructors are inlined at the end of the block. */
/* Round 17: 2 words. Loop y as 0x3e + ib*0x38 fixed the slot loop; an SInit(&st, buf, 0x1000) inline fixed the Stream registers. Left: store order vt before p. */
/* File menu: save-data inherit state machine. The statics s_c1..s_b2 stand in for lbl_8041C9F8 and neighbours, as in fn_80196E14.cpp. */
#include "game/rF_8017F400/types.h"
#pragma inline_max_size(4000)
extern "C" {
typedef struct SInfo { u8 pad[0x28]; s64 time; u8 x30[4]; u8 x34, x35, x36, x37; u8 pad38[8]; u32 x40; } SInfo;
typedef struct SEnt { s16 flags; s16 x2; s16 x4; u8 pad6[0x14-6]; s16 x14; u8 pad16[0x1a-0x16]; s16 x1a; u8 pad1c[0x26-0x1c]; s16 x26; int x28, x2c, x30; s16 x34; s16 x36; char x38[0x40]; f32 x78; } SEnt;
static u8 s_c1[0x10]; static u8 s_b1[0x1070]; static u8 s_c2[0x10]; static u8 s_b2[0x1070];
extern s8 lbl_804CB938;
extern s8 lbl_804CB939;
extern int lbl_804CBFCC;
extern char lbl_804CB778[8];
extern void* memset(void*, int, u32);
extern char* strcpy(char*, const char*);
extern void fn_80245C88(void*);
extern void fn_8019FAC8(void*, int);
extern void __register_global_object(void*, void*, void*);
extern void fn_8024B978(int, void*, int);
extern void fn_8024BB8C(int, void*, int);
extern void fn_80246494(void);
extern int fn_80067FE8(int);
extern void* fn_80106A6C(void*, int);
extern int fn_80105B88(void*);
extern int fn_80105BBC(void*);
extern void fn_80105DC0(void*, int*, int*, int*);
extern void* fn_80105DB8(void*);
extern int fn_80105F94(void*);
extern char lbl_803889DC[], lbl_803889CC[], lbl_803889BC[], lbl_803889AC[], lbl_803889A0[], lbl_80388994[], lbl_80388988[], lbl_8038897C[], lbl_80388970[], lbl_80388964[], lbl_80388958[], lbl_8038894C[], lbl_80388940[], lbl_80388934[], lbl_80388928[];
#define OS_BUS_CLOCK (*(u32*)0x800000F8)
static inline SInfo* Sv1(int slot) {
    if (!lbl_804CB938) {
        fn_80245C88(s_b1);
        __register_global_object(s_b1, fn_8019FAC8, s_c1);
        lbl_804CB938 = 1;
    }
    fn_8024B978(slot, s_b1, 0);
    fn_80246494();
    if (lbl_804CBFCC == 0) return (SInfo*)(s_b1);
    return 0;
}
static inline SInfo* Sv2(int slot) {
    if (!lbl_804CB939) {
        fn_80245C88(s_b2);
        __register_global_object(s_b2, fn_8019FAC8, s_c2);
        lbl_804CB939 = 1;
    }
    fn_8024BB8C(slot, s_b2, 0);
    fn_80246494();
    if (lbl_804CBFCC == 0) return (SInfo*)(s_b2);
    return 0;
}
static inline void P2(SEnt* e) { void* p = fn_80106A6C(lbl_804CB778, e->x4);
        if (p == 0) return;
        if (fn_80105B88(p) == 0) return;
        e->flags |= 4;
        if (fn_80105BBC(p)) e->flags |= 8;
        e->x26 = *((u8*)p + 0x64);
        fn_80105DC0(p, &e->x28, &e->x2c, &e->x30);
        if (e->x28 >= 0x63) { e->x28 = 0x63; e->x2c = 0x3b; e->x30 = 0x3b; }
        e->x34 = *((u8*)p + 0x66);
        e->x36 = (u8)fn_80105F94(fn_80105DB8(p)) - 1;
        if (e->x36 < 0) e->x36 = 0;
        if (e->x26 == 0x20) e->flags |= 0x10; }
static inline void Fill(SEnt* e) {
    if (e->x2 == 0) {
        SInfo* s = Sv1(e->x4);
        SInfo* s2 = Sv2(e->x4);
        if (s == 0) return;
        e->flags |= 4;
        if (s2) { e->flags |= 8; s = s2; }
        e->x26 = s->x36;
        switch (s->x37) {
        case 3: e->flags |= 0x40; break;
        case 1: strcpy(e->x38, lbl_803889DC); break;
        case 2:
            if (s->x40 & 8) strcpy(e->x38, lbl_803889CC);
            else if (s->x40 & 0x10) strcpy(e->x38, lbl_803889BC);
            else if (s->x40 & 0x20) strcpy(e->x38, lbl_803889AC);
            else if (s->x40 & 0x40) {
                switch (e->x26) {
                case 0x32: strcpy(e->x38, lbl_803889A0); break;
                case 0x34: strcpy(e->x38, lbl_80388994); break;
                case 0x33:
                default: strcpy(e->x38, lbl_80388988); break;
                }
            } else strcpy(e->x38, lbl_8038897C);
            break;
        case 5: strcpy(e->x38, lbl_80388970); break;
        case 6: strcpy(e->x38, lbl_80388964); break;
        case 7: strcpy(e->x38, lbl_80388958); break;
        case 9:
            if (e->x26 != 0x37) { e->x26 = (u8)fn_80067FE8(e->x26); strcpy(e->x38, lbl_8038894C); }
            else e->x38[0] = 0;
            break;
        case 8:
            if (s->x40 & 8) strcpy(e->x38, lbl_80388940);
            else if (s->x40 & 0x10) strcpy(e->x38, lbl_80388934);
            else if (s->x40 & 0x20) strcpy(e->x38, lbl_80388928);
            else e->x38[0] = 0;
            break;
        default: e->x38[0] = 0; break;
        }
        {
        u32 sec = s->time / (OS_BUS_CLOCK / 4);
        e->x30 = sec % 60;
        e->x2c = (sec / 60) % 60;
        e->x28 = sec / 3600;
        if (e->x28 > 0x63) { e->x28 = 0x63; e->x2c = 0x3b; e->x30 = 0x3b; }
        }
        e->x34 = s->x35;
        e->x36 = s->x34 - 1;
        if (s->x40 & 4) e->flags |= 0x10;
    } else {
        P2(e);
    }
}

typedef struct FMRect { s16 flags; s16 x2; s16 x4; s16 x6; s16 x8; s16 xa; s16 xc; s16 xe; s16 x10; s16 x12; s16 x14; s16 x16; s16 x18; } FMRect;
typedef struct FM { u32 flags; u8 pad4[0x17-4]; s8 sel; u8 pad18[0x1c-0x18]; int mode; u8 pad20[0x80-0x20]; const char* text; u8 pad84[0x88-0x84]; void* x88; u8 pad8c[0x1a0-0x8c]; SEnt ent[6]; u8 pad[0x4b0-0x1a0-0x7c*6]; FMRect cur; } FM;
struct Pad { virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34(); virtual void v38(); virtual u32 v3C(); virtual void v40(); virtual void v44(); virtual u32 v48(); };
extern Pad* lbl_804CB5B8;
extern FM* lbl_804CB934;
extern s16 lbl_804CB93C;
extern s16 lbl_804CB93E;
extern s16 lbl_804CC0CC;
extern u8 lbl_803886D8[0x14];
extern const char lbl_8036C5E8[0x3D0];
extern void fn_80106A28(void*);
extern void fn_801060FC(void*, void*, int);
extern int fn_80079E5C(void);
extern void fn_802839C4(const char*, const char*, int, const char*, const char*, const char*, int, void*, int);
extern void fn_8028392C(const char*, int, const char*, int, void*, int);
extern void fn_80283A58(void);
extern u8* fn_80081194(void*, void*);
extern void fn_800C835C(int, int);
extern void fn_80083B78(void*);
extern void fn_80253EE4(const char*, f32);
extern u32 fn_8026C1C8(void*, const char*, void*);
extern void fn_80078E24(void*);
extern u8 lbl_80388858[], lbl_80380928[], lbl_80380940[];
#define STR(n) (lbl_8036C5E8 + (n))
struct Stream { void* p; void* q; int n; u8 own; void* vt; int z; void* vt2; };
class MB { public: void* p; void* q; int n; u8 own; virtual void v0(); MB() { own = 0; } ~MB() { if (own) { fn_80078E24(p); p = 0; own = 0; } } };
class MB2 : public MB { public: int z; virtual void v0(); MB2(void* b, int n_) { own = 0; p = b; q = b; n = n_; z = 0; } ~MB2() {} };
class SS { public: MB2 buf; virtual void v0(); SS(void* b, int n_) : buf(b, n_) {} ~SS() {} };

static inline void Wait(void* proc, f32 end) { u8* p = fn_80081194(lbl_803886D8, proc); *(f32*)(p + 0x30) = 0.0f; *(f32*)(p + 0x34) = end; }
static inline void Clr(void) {
    lbl_804CB934->ent[0].flags = 0; lbl_804CB934->ent[1].flags = 0; lbl_804CB934->ent[2].flags = 0; lbl_804CB934->ent[3].flags = 0; lbl_804CB934->ent[4].flags = 0; lbl_804CB934->ent[5].flags = 0;
}
static inline void CurMove(FMRect* c, int x, int y, int d) {
    c->xc = c->x8 ;
}
#define CURHIDE { FMRect* c = &lbl_804CB934->cur; c->xa = c->x6; c->xc = c->x8; c->xe = -1000; c->x10 = -1000; c->x14 = 0; c->x12 = 0; c->x6 = -1000; c->x8 = -1000; c->flags |= 1; }
void fn_801959A0(void* proc) {
    /*P*/
    u32 rep;
    u32 trig;
    SEnt* e;
    int ofs;
    int i;
    u8* q;
    FMRect* m;
    int yy;
    int i2;
    int ofs3;
/*E*/
    trig = lbl_804CB5B8->v48();
    rep = lbl_804CB5B8->v3C();
    switch (lbl_804CB93C) {
    case 0:
        fn_80106A28(lbl_804CB778);
        fn_801060FC(lbl_804CB778, proc, 0);
        lbl_804CB93C = 10;
        break;
    case 10:
        switch (fn_80079E5C()) {
        case 0: lbl_804CB93C = 0x14; break;
        case -1: lbl_804CB93C = 0; break;
        case -2: lbl_804CB93C = 400; break;
        case -0x42: case -0xd: case -6: lbl_804CB93C = 0x1a4; break;
        case -5: lbl_804CB93C = 0x1ae; break;
        case -0x41: lbl_804CB93C = 0x19a; break;
        case -4: case -3: lbl_804CB93C = 0x46; break;
        default: lbl_804CB93C = 0x46; break;
        }
        break;
    case 0x14: {
        int i;
        lbl_804CB93C = 0x46;
        for (i = 0; i < 5; i++) {
            u8* p = (u8*)fn_80106A6C(lbl_804CB778, i);
            if (p && fn_80105B88(p) && p[0x64] == 0x20) { lbl_804CB93C = 0x1e; break; }
        }
        fn_80106A28(lbl_804CB778);
        break;
    }
    case 0x1e:
        lbl_804CB934->mode = 2;
        fn_802839C4(STR(0xad), STR(0xba), 1, STR(0x71), STR(0x71), STR(0x81), 0, proc, 2);
        lbl_804CB93C = 0x28;
        break;
    case 0x28:
        switch (lbl_804CC0CC) {
        case 1: lbl_804CB93C = 0x32; Wait(proc, 5.0f); break;
        case 2: lbl_804CB93C = 0x46; break;
        default: lbl_804CB93C = 0x50; break;
        }
        break;
    case 0x32:
        fn_800C835C(7, 500);
        lbl_804CB93E = 0;
        lbl_804CB93C = 0x3c;
        break;
    case 0x3c:
        Clr();
        CURHIDE
        lbl_804CB93C = 100;
        lbl_804CB934->flags |= 2;
        Wait(proc, 30.0f);
        break;
    case 0x46:
        fn_80106A28(lbl_804CB778);
        lbl_804CB93E = 1;
        fn_80083B78(proc);
        break;
    case 0x50:
        fn_80106A28(lbl_804CB778);
        lbl_804CB93E = 2;
        fn_80083B78(proc);
        break;
    case 100:
        Clr();
        lbl_804CB934->flags |= 4;
        lbl_804CB93C = 0x6e;
        lbl_804CB934->text = 0;
        CURHIDE
        break;
    case 0x6e:
        Clr();
        lbl_804CB93C = 0x78;
        fn_80106A28(lbl_804CB778);
        fn_801060FC(lbl_804CB778, proc, 0);
        break;
    case 0x78:
        switch (fn_80079E5C()) {
        case 0: lbl_804CB93C = 0x82; break;
        case -1: lbl_804CB93C = 0x6e; break;
        case -3: lbl_804CB93C = 600; break;
        case -2: lbl_804CB93C = 0x262; break;
        case -0x41: lbl_804CB93C = 0x26c; break;
        case -0x42: case -0xd: case -6: lbl_804CB93C = 0x276; break;
        case -5: lbl_804CB93C = 0x280; break;
        case -4: lbl_804CB93C = 0x28a; break;
        }
        break;
    case 0x82: {
        i = 0;
        ofs = 0;
        for (; i < 5; i++, ofs += 0x7c) {
            e = (SEnt*)((u8*)lbl_804CB934->ent + ofs);
            memset(e, 0, 0x7c);
            e->x4 = i;
            e->x2 = 1;
            e->x14 = 0;
            e->x78 = 0.0f;
            e->x1a = 0xff;
            e->flags = 1;
            Fill(e);
        }
        { int y; int ofs2; int ib;
        lbl_804CB934->sel = -1;
        {
            ib = 0;
            for (; ib < 5; ib++) { y = 0x3e + ib * 0x38;
                if (ib % 2 == 0) {
                    m = (FMRect*)&lbl_804CB934->ent[ib];
                    m->xc = m->x8; m->xe = m->xa; m->x10 = -0x3b0; m->x12 = y; m->x18 = 0; m->x16 = 0; m->x8 = -0x3b0; m->xa = y; m->flags |= 1;
                } else {
                    m = (FMRect*)&lbl_804CB934->ent[ib];
                    m->xc = m->x8; m->xe = m->xa; m->x10 = 0x420; m->x12 = y; m->x18 = 0; m->x16 = 0; m->x8 = 0x420; m->xa = y; m->flags |= 1;
                }
                m = (FMRect*)&lbl_804CB934->ent[ib];
                m->xc = m->x8; m->xe = m->xa; m->x10 = 0x38; m->x12 = y; m->x18 = 0x19; m->x16 = 0x19; m->x14 = 4; m->flags |= 1;
                {
                    SEnt* e2 = &lbl_804CB934->ent[ib];
                    e2->x1a = 0; *(s16*)((u8*)e2 + 0x1c) = 0; *(s16*)((u8*)e2 + 0x1e) = 0xff; *(s16*)((u8*)e2 + 0x22) = 0x24; *(s16*)((u8*)e2 + 0x20) = 0x24;
                }
                if ((lbl_804CB934->ent[ib].flags & 0x10) && lbl_804CB934->sel == -1) lbl_804CB934->sel = ib;
            }
        }
        }
        lbl_804CB93C = 0x87;
        lbl_804CB934->text = STR(0xc8);
        lbl_804CB934->mode = 1;
        Wait(proc, 25.0f);
        break;
    }
    case 0x87:
        if (lbl_804CB934->sel == -1) {
            lbl_804CB93C = 600;
            fn_8028392C(STR(0xd7), 0, 0, 1, proc, 1);
        } else {
            lbl_804CB934->ent[lbl_804CB934->sel].flags |= 2;
            {
                FMRect* c = &lbl_804CB934->cur;
                s16 y = ((FMRect*)&lbl_804CB934->ent[lbl_804CB934->sel])->xa + 0x1a;
                s16 x = ((FMRect*)&lbl_804CB934->ent[lbl_804CB934->sel])->x8 - 0x10;
                c->xa = c->x6; c->xc = c->x8; c->xe = x; c->x10 = y; c->x14 = 0; c->x12 = 0; c->x6 = x; c->x8 = y; c->flags |= 1;
            }
            lbl_804CB93C = 0x8c;
        }
        break;
    case 0x8c:
        if (trig & 0x400) {
            lbl_804CB93C = 0x96;
            fn_80253EE4(STR(0x71), 0.0f);
            lbl_804CB934->mode = 2;
            fn_8028392C(STR(0xec), 0, STR(0x71), 0, proc, 2);
        } else if (trig & 0x800) {
            lbl_804CB93C = 0xa0;
            fn_80253EE4(STR(0x81), 0.0f);
            lbl_804CB934->mode = 2;
            fn_8028392C(STR(0xfe), 1, STR(0x71), 0, proc, 2);
        } else {
            int old = lbl_804CB934->sel;
            if ((rep & 0x800008) || (trig & 0x800008)) {
                do {
                    lbl_804CB934->sel--;
                    if (lbl_804CB934->sel < 0) {
                        if (trig & 0x800008) lbl_804CB934->sel = 4; else { lbl_804CB934->sel = old; break; }
                    }
                } while (!(lbl_804CB934->ent[lbl_804CB934->sel].flags & 0x10));
            }
            if (rep & 0x400004) {
                do {
                    lbl_804CB934->sel++;
                    if (lbl_804CB934->sel > 4) {
                        if (trig & 0x400004) lbl_804CB934->sel = 0; else { lbl_804CB934->sel = old; break; }
                    }
                } while (!(lbl_804CB934->ent[lbl_804CB934->sel].flags & 0x10));
            }
            if (old != lbl_804CB934->sel) {
                int s = lbl_804CB934->sel;
                s16 y = ((FMRect*)&lbl_804CB934->ent[s])->xa + 0x1a;
                s16 x = ((FMRect*)&lbl_804CB934->ent[s])->x8 - 0x10;
                FMRect* c = &lbl_804CB934->cur;
                c->xa = c->x6; c->xc = c->x8; c->xe = x; c->x10 = y; c->x14 = 4; c->x12 = 4; c->flags |= 1;
                lbl_804CB934->ent[old].flags &= ~2;
                lbl_804CB934->ent[lbl_804CB934->sel].flags |= 2;
                fn_80253EE4(STR(0x91), 0.0f);
            }
        }
        break;
    case 0x96:
        if (lbl_804CC0CC == 1) {
            SS st(lbl_804CB934->x88, 0x1000);
            if (fn_8026C1C8(&st, STR(0x118), fn_80106A6C(lbl_804CB778, lbl_804CB934->sel)) == 1) {
                lbl_804CB93C = 200;
                lbl_804CB934->flags |= 8;
                lbl_804CB934->flags &= ~4;
            } else {
                lbl_804CB93C = 0x87;
                lbl_804CB934->mode = 1;
                fn_8028392C(STR(0x124), 0, 0, 1, proc, 0);
            }
        } else {
            lbl_804CB934->mode = 1;
            lbl_804CB93C = 0x87;
        }
        break;
    case 0xa0:
        if (lbl_804CC0CC == 1) { lbl_804CB93C = 200; lbl_804CB934->flags &= ~8; }
        else { lbl_804CB93C = 0x87; lbl_804CB934->mode = 1; }
        break;
    case 200:
        fn_80106A28(lbl_804CB778);
        lbl_804CB93C = 0xd2;
        lbl_804CB934->flags &= ~4;
        Wait(proc, 5.0f);
        break;
    case 0xd2:
        fn_80083B78(proc);
        fn_800C835C(7, 500);
        break;
    case 400: fn_8028392C(STR(0x133), 0, 0, 1, proc, 1); lbl_804CB93C = 500; break;
    case 0x19a: fn_8028392C(STR(0x140), 0, 0, 1, proc, 1); lbl_804CB93C = 500; break;
    case 0x1a4: fn_8028392C(STR(0x14d), 0, 0, 1, proc, 1); lbl_804CB93C = 500; break;
    case 0x1ae: fn_8028392C(STR(0x15b), 0, 0, 1, proc, 1); lbl_804CB93C = 500; break;
    case 500: lbl_804CB93C = 0x1fe; lbl_804CB934->mode = 3; break;
    case 0x1fe:
        if (trig & 0x400) { fn_80283A58(); lbl_804CB93C = 0; }
        else if (trig & 0x800) { fn_80283A58(); lbl_804CB93C = 0x46; }
        break;
    case 600: fn_8028392C(STR(0x165), 0, 0, 1, proc, 1); lbl_804CB93C = 700; break;
    case 0x262: fn_8028392C(STR(0x133), 0, 0, 1, proc, 1); lbl_804CB93C = 700; break;
    case 0x26c: fn_8028392C(STR(0x140), 0, 0, 1, proc, 1); lbl_804CB93C = 700; break;
    case 0x276: fn_8028392C(STR(0x14d), 0, 0, 1, proc, 1); lbl_804CB93C = 700; break;
    case 0x280: fn_8028392C(STR(0x15b), 0, 0, 1, proc, 1); lbl_804CB93C = 700; break;
    case 0x28a: fn_8028392C(STR(0x173), 0, 0, 1, proc, 1); lbl_804CB93C = 700; break;
    case 700: lbl_804CB93C = 0x2c6; lbl_804CB934->mode = 4; break;
    case 0x2c6:
        if (trig & 0x400) { fn_80283A58(); lbl_804CB93C = 0x6e; }
        else if (trig & 0x800) { fn_80283A58(); lbl_804CB93C = 200; }
        break;
    }
}
}
