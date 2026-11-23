#include "game/rG_800A3D88/types.h"

#pragma auto_inline off

extern "C" {

extern char lbl_803656F8[];
extern const f32 lbl_804CD3B0;
extern const f32 lbl_804CD3B8;

struct Vec {
    f32 x, y, z;
};

struct NameRec {
    u8 pad[4];
    const char* name;
};

int fn_800A7C28(const char*);
NameRec* fn_800A7CE8(int);
void fn_80290DDC(char*, const char*, ...);
u32 fn_8023F9F4(char*);
void fn_8023F1A0(char*, s32);
struct Cam { u8 pad[0xD4]; f32 d4; u8 pad2[4]; f32 dc; };
Cam* fn_8000F470();
void fn_8031292C(void*, f32, f32, f32);
void fn_803128AC(void*, f32, f32, f32);
void fn_80312378(void*, void*, void*);
void fn_80312344(void*, void*);
void fn_800081D4(void*);
void fn_80007C58(void*);
void fn_800180F0(void*);
void fn_8001AFE0(void*);
int fn_80007630(void*, const char*);
Vec fn_800076E8(void*, int);
void fn_800AFDFC(void*);
void fn_80021FE8(int);
void fn_800E2170(void*, void*);
void fn_80078E24(void*);
int fn_80008E5C(void*, int, int);
int fn_80008E88(void*, int, int);

struct Sub40 {
    u8 pad[0x30];
    u8 m30;
    u8 pad31[3];
    Vec m34;
};

struct PicP {
    u8 pad[0x30];
    u8 m30;
    u8 pad31[3];
    f32 m34;
    void* m38;
    u8* m3c;
    Sub40* m40;
    void* m44;
};

void fn_800AEC8C(PicP*);

BOOL fn_800AEE68(void* p, const char* name) {
    char buf[0x40];
    if (name == NULL) {
        return 0;
    }
    NameRec* r = fn_800A7CE8(fn_800A7C28(name));
    if (r->name == NULL) {
        return 0;
    }
    fn_80290DDC(buf, lbl_803656F8 + 0x35, r->name, r->name);
    if (fn_8023F9F4(buf) == 0x40000) {
        return 0;
    }
    fn_8023F1A0(buf, 0x2040);
    return 1;
}

static inline int FindNode(u8* m) {
    if (m != NULL) {
        int i = fn_80007630(m, lbl_803656F8 + 0x31);
        if (i >= 0) {
            return i;
        }
    }
    return -1;
}

static inline void SetPos(Sub40* o, Vec v) {
    o->m34 = v;
}

void fn_800AEEFC(PicP* p) {
    f32 m3[12], m2[12], m1[12];
    if (p->m3c != NULL && p->m30 != 0) {
        Cam* c = fn_8000F470();
        fn_8031292C(m2, p->m34, p->m34, p->m34);
        fn_803128AC(m3, c->d4, lbl_804CD3B0, c->dc);
        fn_80312378(m3, m2, m1);
        fn_80312344(m1, p->m3c + 0x10);
        fn_800081D4(p->m3c);
        fn_80007C58(p->m3c);
        fn_800180F0(p->m3c);
        fn_8001AFE0(p->m3c);
        fn_800AEC8C(p);
        int i = FindNode(p->m3c);
        if (i >= 0) {
            Vec v = fn_800076E8(p->m3c, i);
            if (p->m40 != NULL) {
                SetPos(p->m40, v);
                p->m40->m30 = 1;
            }
        }
    }
}

struct Anim2 {
    u8 pad[0x30];
    void* m30;
    void* m34;
    void* m38;
    f32 m3c_unused;
    f32 m40, m44, m48, m4c;
    u16 m50, m52, m54;
    s16 m56;
    void** m58;
};

void fn_800B0244(Anim2* a) {
    a->m30 = NULL;
    a->m34 = NULL;
    a->m40 = lbl_804CD3B8;
    a->m44 = lbl_804CD3B8;
    a->m48 = lbl_804CD3B8;
    a->m50 = 0;
    a->m52 = 0;
    a->m4c = lbl_804CD3B8;
    a->m56 = -1;
    a->m58 = NULL;
}

void fn_800B027C(Anim2* a) {
    if (a->m58 != NULL) {
        int i = 0;
        int off = 0;
        for (; i < a->m54; off += 0xA4, i++) {
            fn_800E2170(a->m38, (u8*)a->m58[0] + off + 8);
        }
        void** t = a->m58;
        if (t != NULL) {
            if (t != NULL) {
                fn_80078E24(t[0]);
                t[0] = NULL;
                fn_80078E24(t[1]);
                t[1] = NULL;
                fn_80078E24(t);
            }
            a->m58 = NULL;
        }
        a->m38 = NULL;
    }
}

void fn_800B033C(void* p) {
    fn_800AFDFC(p);
}

struct Flag8 {
    u8 pad[8];
    u16 f;
};

void fn_800B053C(void* a, Flag8* b) {
    if (b->f & 0x2000) {
        fn_80021FE8(1);
    }
}

void fn_800B0554(void* a, Flag8* b) {
    if (b->f & 0x2000) {
        fn_80021FE8(0);
    }
}

struct Mdl {
    u32 flags;
    u8 pad[0x54];
    f32 m58;
};

struct Chr {
    u8 pad[0x30];
    Mdl* m;
};

void fn_800B0BF4(Chr* c, int on) {
    Mdl* m = c->m;
    if (m != NULL) {
        if (on) {
            m->flags |= 8;
            return;
        }
        m->flags &= ~8;
    }
}

BOOL fn_800B0C28(Chr* c) {
    Mdl* m = c->m;
    if (m == NULL) {
        return 0;
    }
    if (!(m->flags & 8)) {
        return 0;
    }
    int f = m->m58;
    int a = fn_80008E5C(m, f, 3);
    int b = fn_80008E88(c->m, f, 4);
    if (a < 0) {
        return 0;
    }
    return b >= 0;
}

} // extern "C"
