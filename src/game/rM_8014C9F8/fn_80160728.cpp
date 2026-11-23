/* AI: boss script commands (CP_*), 80160728..80161CD0. */
#include "game/rM_8014C9F8/ai.h"
#pragma auto_inline off

struct AiCmd {
    int op;
    int a;
    int b;
    int c;
    int d;
    u32 fl;
    u32 x;
    u32 y;
    u32 z;
    u32 w;
};

struct Fn4 {
    void* vt;
    Unit* u;
    u32 x;
    u8 k;
};

struct AiActX {
    u8 pad[0x18];
    int arg[4];  /* 0x18 */
};

extern "C" {

#if TARGET_PC
extern FE10_PROTO u8* fn_80076F54(p32arg);
extern FE10_PROTO p32ret fn_80077064(p32arg);
#else
extern u8* fn_80076F54(u32);
extern u32 fn_80077064(u32);
#endif
extern int fn_80155090(void*, void*, char*, u8);
extern char lbl_8036AED8[];
extern u8 lbl_803872B8[];
extern u8 lbl_803872C8[];

int fn_80160728(Unit* u, AiCmd* c) {
    fn_80160610(0x50, u->x, (s8)*(u8*)&u->y, NULL, 0, 0, -1, 0, 0);
    u8* p = fn_80076F54(c->y);
    AiActX* a = (AiActX*)&lbl_803CA870;
    a->arg[0] = p[0];
    a->arg[1] = p[1];
    a->arg[2] = p[2];
    a->arg[3] = p[3];
    return 0;
}

int fn_801607BC(Unit* u, AiCmd* c) {
    fn_80160610(0x51, u->x, (s8)*(u8*)&u->y, NULL, 0, 0, -1, 0, 0);
    u8* p = fn_80076F54(c->y);
    AiActX* a = (AiActX*)&lbl_803CA870;
    a->arg[0] = p[0];
    a->arg[1] = p[1];
    a->arg[2] = p[2];
    a->arg[3] = p[3];
    return 0;
}

int fn_80160850(Unit* u, AiCmd* c) {
    fn_80160610(0x52, u->x, (s8)*(u8*)&u->y, NULL, 0, 0, -1, 0, 0);
    u8* p = fn_80076F54(c->y);
    AiActX* a = (AiActX*)&lbl_803CA870;
    a->arg[0] = p[0];
    a->arg[1] = p[1];
    a->arg[2] = p[2];
    a->arg[3] = p[3];
    return 0;
}

int fn_801608E4(Unit* u, AiCmd* c) {
    fn_80160610(0x5E, u->x, (s8)*(u8*)&u->y, NULL, 0, 0, -1, 0, 0);
    u8* p = fn_80076F54(c->y);
    AiActX* a = (AiActX*)&lbl_803CA870;
    a->arg[0] = p[0];
    a->arg[1] = p[1];
    a->arg[2] = p[2];
    a->arg[3] = p[3];
    return 0;
}

int fn_80160978(Unit* u, AiCmd* c) {
    fn_80160610(0x5F, u->x, (s8)*(u8*)&u->y, NULL, 0, 0, -1, 0, 0);
    u8* p = fn_80076F54(c->y);
    AiActX* a = (AiActX*)&lbl_803CA870;
    a->arg[0] = p[0];
    a->arg[1] = p[1];
    a->arg[2] = p[2];
    a->arg[3] = p[3];
    return 0;
}

int fn_80160A0C(Unit* u, AiCmd* c) {
    u32 x;
    if (c->y != 0) {
        x = fn_80077064(c->y);
    } else {
        x = 0;
    }
    Fn4 f3;
    Fn4 f2;
    Fn2 f1;
    Fn2 g;
    void* s;
    f1.u = u;
    f1.vt = lbl_80387308;
    f3.u = u;
    f3.vt = lbl_803872C8;
    f3.x = x;
    f3.k = 3;
    f2.u = u;
    f2.vt = lbl_803872B8;
    f2.x = x;
    f2.k = 1;
    if (x == 0) {
        s = &f1;
    } else {
        s = &f3;
        if (c->fl & 1) {
            s = &f2;
        }
    }
    g.vt = lbl_80387338;
    lbl_804183F0.flags |= 2;
    g.u = u;
    fn_80155090(s, &g, lbl_8036AED8 + 0x0, 0x53);
    lbl_804183F0.flags &= ~2;
    return 0;
}

int fn_80160B10(Unit* u, AiCmd* c) {
    u32 x;
    if (c->y != 0) {
        x = fn_80077064(c->y);
    } else {
        x = 0;
    }
    Fn4 f3;
    Fn4 f2;
    Fn2 f1;
    Fn2 g;
    void* s;
    f1.u = u;
    f1.vt = lbl_80387308;
    f3.u = u;
    f3.vt = lbl_803872C8;
    f3.x = x;
    f3.k = 3;
    f2.u = u;
    f2.vt = lbl_803872B8;
    f2.x = x;
    f2.k = 1;
    if (x == 0) {
        s = &f1;
    } else {
        s = &f3;
        if (c->fl & 1) {
            s = &f2;
        }
    }
    g.vt = lbl_80387338;
    lbl_804183F0.flags |= 2;
    g.u = u;
    fn_80155090(s, &g, lbl_8036AED8 + 0xB, 0x54);
    lbl_804183F0.flags &= ~2;
    return 0;
}

int fn_80160C18(Unit* u, AiCmd* c) {
    u32 x;
    if (c->y != 0) {
        x = fn_80077064(c->y);
    } else {
        x = 0;
    }
    Fn4 f3;
    Fn4 f2;
    Fn2 f1;
    Fn2 g;
    void* s;
    f1.u = u;
    f1.vt = lbl_80387308;
    f3.u = u;
    f3.vt = lbl_803872C8;
    f3.x = x;
    f3.k = 3;
    f2.u = u;
    f2.vt = lbl_803872B8;
    f2.x = x;
    f2.k = 1;
    if (x == 0) {
        s = &f1;
    } else {
        s = &f3;
        if (c->fl & 1) {
            s = &f2;
        }
    }
    g.vt = lbl_80387338;
    lbl_804183F0.flags |= 2;
    g.u = u;
    fn_80155090(s, &g, lbl_8036AED8 + 0x16, 0x55);
    lbl_804183F0.flags &= ~2;
    return 0;
}

int fn_80160D20(Unit* u, AiCmd* c) {
    u32 x;
    if (c->y != 0) {
        x = fn_80077064(c->y);
    } else {
        x = 0;
    }
    Fn4 f3;
    Fn4 f2;
    Fn2 f1;
    Fn2 g;
    void* s;
    f1.u = u;
    f1.vt = lbl_80387308;
    f3.u = u;
    f3.vt = lbl_803872C8;
    f3.x = x;
    f3.k = 3;
    f2.u = u;
    f2.vt = lbl_803872B8;
    f2.x = x;
    f2.k = 1;
    if (x == 0) {
        s = &f1;
    } else {
        s = &f3;
        if (c->fl & 1) {
            s = &f2;
        }
    }
    g.vt = lbl_80387338;
    lbl_804183F0.flags |= 2;
    g.u = u;
    fn_80155090(s, &g, lbl_8036AED8 + 0x21, 0x60);
    lbl_804183F0.flags &= ~2;
    return 0;
}

int fn_80160E28(Unit* u, AiCmd* c) {
    s8* p = (s8*)fn_80076F54(c->y);
    fn_80160610(0x5B, u->x, (s8)*(u8*)&u->y, NULL, 0, 0, -1, 0, 0);
    ((AiActX*)&lbl_803CA870)->arg[0] = p[0];
    return 0;
}

int fn_80160EB0(Unit* u, AiCmd* c) {
    s8* p = (s8*)fn_80076F54(c->y);
    fn_80160610(0x5D, u->x, (s8)*(u8*)&u->y, NULL, 0, 0, -1, 0, 0);
    ((AiActX*)&lbl_803CA870)->arg[0] = p[0];
    return 0;
}

int fn_80160F38(Unit* u, AiCmd* c) {
    s8* p = (s8*)fn_80076F54(c->y);
    fn_80160610(0x5C, u->x, (s8)*(u8*)&u->y, NULL, 0, 0, -1, 0, 0);
    ((AiActX*)&lbl_803CA870)->arg[0] = p[1];
    return 0;
}

#define FOR_SIDE0(n)                               \
    {                                              \
        u8 tbl[0xC];                               \
        int i;                                     \
        fn_8010E41C(tbl, 0);                       \
        for (i = 1; i <= 0xFE; i++) {              \
            Unit* v = UnitGet(i);                  \
            if (v->person && tbl[v->team[8]]) {    \
                n++;                               \
            }                                      \
        }                                          \
    }

int fn_80160FC0(Unit* u) {
    int n = 0;
    FOR_SIDE0(n);
    if (n > 0x32) {
        return 0;
    }
    fn_80160610(0x56, u->x, (s8)*(u8*)&u->y, NULL, 0, 0, -1, 0, 0);
    return 0;
}




extern void fn_80076D48(char*, void*);
extern int fn_80161A54(Unit*, AiCmd*);
extern int fn_801612B4(Unit*, AiCmd*);
extern int fn_80161684(Unit*, AiCmd*);

void fn_80161BA4(void) {
    fn_80076D48(lbl_8036AED8 + 0x31, (void*)fn_80160728);
    fn_80076D48(lbl_8036AED8 + 0x42, (void*)fn_801607BC);
    fn_80076D48(lbl_8036AED8 + 0x55, (void*)fn_80160850);
    fn_80076D48(lbl_8036AED8 + 0x68, (void*)fn_801608E4);
    fn_80076D48(lbl_8036AED8 + 0x7E, (void*)fn_80160978);
    fn_80076D48(lbl_8036AED8 + 0x92, (void*)fn_80160A0C);
    fn_80076D48(lbl_8036AED8 + 0xA4, (void*)fn_80160B10);
    fn_80076D48(lbl_8036AED8 + 0xB8, (void*)fn_80160C18);
    fn_80076D48(lbl_8036AED8 + 0xCC, (void*)fn_80160D20);
    fn_80076D48(lbl_8036AED8 + 0xE1, (void*)fn_80160E28);
    fn_80076D48(lbl_8036AED8 + 0xF4, (void*)fn_80160EB0);
    fn_80076D48(lbl_8036AED8 + 0x106, (void*)fn_80160F38);
    fn_80076D48(lbl_8036AED8 + 0x11A, (void*)fn_80160FC0);
    fn_80076D48(lbl_8036AED8 + 0x12C, (void*)fn_80161A54);
    fn_80076D48(lbl_8036AED8 + 0x13F, (void*)fn_801612B4);
    fn_80076D48(lbl_8036AED8 + 0x152, (void*)fn_80161684);
}

extern void fn_80167704(u8*);
extern void fn_8010CC50(void*, s8*, s8*);
extern void fn_80166720(Unit*);
extern u8* fn_80060728(void*);
extern u8 lbl_803CAB38[];
extern void* lbl_803870A8[];
extern void* lbl_803870F8[][0x10];

void* fn_80161D98(void) {
    int i = ((AiActX*)&lbl_803CA870)->arg[0];
    void* r = NULL;
    if (i >= 0 && (u32)i < 0x10) {
        r = lbl_803870F8[fn_80060728(lbl_803CAB38)[0x11]][i];
    }
    return r;
}

}
