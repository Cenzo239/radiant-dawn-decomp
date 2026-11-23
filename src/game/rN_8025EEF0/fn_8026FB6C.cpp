/* Base-conversation menus and small destructor helpers. */
#include "game/rN_8025EEF0/types.h"

#pragma use_lmw_stmw on

extern "C" {

void* fn_80081194(void* cls, void* parent);
void* fn_80078CCC(int size, const char* name, int a);
void fn_80078E24(void* p);
void fn_80079210(void* p);
void fn_80179710(void* p, int a);
#if TARGET_PC
FE10_PROTO void fn_803080DC(int x, int y, int w, int h);
#else
int fn_803080DC(int x, int y, int w, int h);
#endif
void fn_802525A0(int a, f32 v);
void fn_80251838(int a, const char* s, f32 v);
void* fn_80077064(const char* s);
#if TARGET_PC
FE10_PROTO p32ret fn_8012CE54(p32arg);
FE10_PROTO p32ret fn_8010B1D8(p32arg);
#else
int fn_8012CE54(int a);
int fn_8010B1D8(int a);
#endif
void fn_800A1BC8(void* a, void* b);
int fn_800A1CB8(void* a);
void* fn_80075D78(const char* s);
u8* fn_8024BC94(void);
void fn_800068A0(void* p, const char* s);
int fn_8023F880(const char* s);
void fn_8023F1A0(const char* s, int a);
void fn_80083B78(void* p);
#if TARGET_PC
FE10_PROTO void* fn_8024F484(ptr32<const void>);
#else
void* fn_8024F484(void* p);
#endif
void fn_8009E554(void* a, void* b);

extern u8 lbl_80392520[];
extern char lbl_8037340C[];
extern u8* lbl_804CC040;
extern u8* lbl_804CC044;
extern char lbl_8039280C[];
extern char lbl_803927E8[];
extern char lbl_803927D4[];
extern char lbl_803927C0[];
extern char lbl_803927AC[];
extern char lbl_80392798[];
extern char lbl_80392784[];
extern char lbl_80392774[];
extern const char* lbl_80392590[];
extern u8 lbl_80392648[];
extern u8 lbl_8039282C[];
extern u8 lbl_8039281C[];

void fn_8026FB6C(void* parent) {
    lbl_804CC040 = (u8*)fn_80081194(lbl_80392520, parent);
    *(void**)(lbl_804CC040 + 0x30) = fn_80078CCC(0x170, lbl_8037340C + 0xC1, 0);
    lbl_804CC044 = *(u8**)(lbl_804CC040 + 0x30);
}

void* fn_8026FBC8(void* p, int del) {
    if (p != 0) {
        fn_80179710(p, 0);
        if (del > 0) {
            fn_80078E24(p);
        }
    }
    return p;
}

int fn_8026FC20(void) { return 0; }
int fn_8026FC28(void) { return 1; }
int fn_8026FC30(void) { return 0; }

void fn_8026FD38(void*, int v) {
    fn_802525A0(1, v);
}

void fn_8026FD78(void* parent) { fn_8009E554(lbl_8039282C, parent); }

void fn_8026FD88(u8* p) { *(int*)(p + 0x40) ^= 1; }

struct Ent2C { int id; u8 pad[0x24]; u8 last; u8 pad29[3]; };

struct EntTbl { u32 n; Ent2C e[1]; };
BOOL fn_8026FD98(u8* p) {
    Ent2C* e;
    u32* tbl;
    int a;
    int b;
    u32 i;

    tbl = (u32*)fn_80077064(lbl_8039280C);
    i = *(u32*)(p + 0x3C);
    a = 0;
    b = 0;
    e = &((EntTbl*)tbl)->e[i];
    for (; i < *tbl; e++, i++) {
        a = fn_8012CE54(e->id);
        if (a != 0) {
            break;
        }
        if (e->last != 0) {
            b = fn_8010B1D8(e->id);
            break;
        }
    }
    BOOL r = 0;
    if (a != 0 || b != 0) {
        r = 1;
    }
    return r;
}

struct UnitBox { u8 pad[0xEC]; void* mEC; u8 padF0[8]; UnitBox* mF8; void* mFC; };

void fn_802713A0(u8* p) {
    UnitBox* u = *(UnitBox**)(p + *(int*)(p + 0x40) * 4 + 0x60);
    void* a;
    if (u == 0) {
        return;
    }
    if (u->mF8 != 0) {
        a = u->mF8->mEC;
    } else {
        a = u->mFC;
    }
    if (a == 0) {
        return;
    }
    fn_800A1BC8(a, p);
}

int fn_802713E4(u8* p) {
    UnitBox* u = *(UnitBox**)(p + *(int*)(p + 0x40) * 4 + 0x60);
    void* a;
    if (u == 0) {
        return 0;
    }
    if (u->mF8 != 0) {
        a = u->mF8->mEC;
    } else {
        a = u->mFC;
    }
    if (a == 0) {
        return 0;
    }
    return fn_800A1CB8(a);
}

void* fn_80271E4C(void* p, int del) {
    if (p != 0) {
        if (del > 0) {
            fn_80079210(p);
        }
    }
    return p;
}

void* fn_80271E8C(u8* p, int del) {
    if (p != 0) {
        if (p + 0x14 != 0 && *(u32*)(p + 0x14) >> 31) {
            fn_80079210(*(void**)(p + 0x1C));
        }
        if (del > 0) {
            fn_80079210(p);
        }
    }
    return p;
}

void fn_802720BC(void* parent) { fn_8009E554(lbl_8039281C, parent); }

void fn_802720CC(u8* p) {
    *(void**)(p + 0x30) = fn_80075D78(lbl_803927E8);
    *(void**)(p + 0x34) = fn_80075D78(lbl_80392590[(s8)fn_8024BC94()[0x1BC8]]);
    fn_800068A0(p + 0x38, lbl_803927D4);
}

void fn_80272138(void* p) {
    if (fn_8023F880(lbl_803927C0) != 0) {
        if (fn_8023F880(lbl_80392590[(s8)fn_8024BC94()[0x1BC8]]) != 0) {
            if (fn_8023F880(lbl_803927AC) != 0) {
                fn_80083B78(p);
            }
        }
    }
}

void fn_802721B8(void) {
    fn_8023F1A0(lbl_80392798, 0);
    fn_8023F1A0(lbl_80392590[(s8)fn_8024BC94()[0x1BC8]], 0);
    fn_8023F1A0(lbl_80392784, 0);
}

void fn_80272218(void*, int v) {
    fn_80251838(1, lbl_80392774, v);
}

void* fn_802723C4(void* p, int del) {
    if (p != 0) {
        if (del > 0) {
            fn_80079210(p);
        }
    }
    return p;
}

struct ConvRoom {
    u8 pad[0x30];
    int m30, m34, m38, m3C, m40, m44, m48, m4C, m50, m54, m58, m5C, m60, m64, m68, m6C;
};

void fn_80272404(void* parent) {
    ConvRoom* r = (ConvRoom*)fn_80081194(lbl_80392648, parent);
    if (r != 0) {
        r->m30 = 0;
        r->m34 = 0;
        r->m38 = 0;
        r->m3C = 0;
        r->m40 = 0;
        r->m44 = 0;
        r->m48 = 0;
        r->m50 = 0;
        r->m58 = 0;
        r->m60 = 0;
        r->m68 = 0;
        r->m4C = 0;
        r->m54 = 0;
        r->m5C = 0;
        r->m64 = 0;
        r->m6C = 0;
    }
}


/* Conversation-room menu lookups. Two different procs own the same data. */
#if TARGET_PC
FE10_PROTO struct Proc * fn_80085708(const char* s);
FE10_PROTO int fn_80245368(p32arg, p32arg);
#else
int fn_80085708(const char* s);
int fn_80245368(int a, int b);
#endif
extern char lbl_8037359C[];
extern u8* lbl_804CC06C;
extern u8* lbl_804CC074;

static inline BOOL isProc(const char* s) { return fn_80085708(s) != 0; }

static inline u8* roomData(void) {
    if (isProc(lbl_8037359C)) {
        return lbl_804CC06C + 0x108;
    }
    if (isProc(lbl_8037359C + 0x13)) {
        return lbl_804CC074 + 0xC;
    }
    return 0;
}

u8* fn_80272A14(void) { return roomData(); }
u8* fn_80272A8C(void) { return roomData() + 0x24; }
u8* fn_80272B08(void) { return roomData() + 4; }
int fn_80272B84(void) {
    s16* t = (s16*)(roomData() + 0x24);
    return t[*(s16*)(roomData() + 0x30)];
}
int fn_80272E3C(int a) {
    if (isProc(lbl_8037359C)) {
        return fn_80245368(*(int*)(lbl_804CC06C + 8), a);
    }
    if (isProc(lbl_8037359C + 0x13)) {
        return fn_80245368(*(int*)lbl_804CC074, a);
    }
    return 0;
}

void fn_80272C68(int v) {
    s16* t = (s16*)(roomData() + 0x24);
    t[*(s16*)(roomData() + 0x30)] = v;
}
f32 fn_80272D58(void) {
    f32* t = (f32*)(roomData() + 4);
    return t[*(s16*)(roomData() + 0x30)];
}

}
