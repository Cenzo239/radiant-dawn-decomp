#include "game/rG_800A3D88/types.h"

#pragma auto_inline off

extern "C" {

extern const char* lbl_80382650[][2];
extern u8 lbl_80382688[];
extern u8 lbl_803826D8[];
extern u8 lbl_80382728[];
extern u8 lbl_80382778[];
extern u8 lbl_80382790[];
extern const f32 lbl_804CD4B8;
extern void* lbl_804CB6B4;
extern void* lbl_804CB6B8;

struct Save1 { u8 pad[0x1BC8]; u8 lang; };
Save1* fn_8024BC94();
int fn_801D09F0();
void fn_8023F1A0(const char*, int);
void* fn_8001D3EC(const char*, int);
void fn_8001D424(void*);
void* fn_80081194(void*, void*);
void* fn_80081050(void*, void*);
void fn_800C242C(void*);
void fn_800C283C(void*);
f32 fn_8017F68C(int, f32, f32, f32, f32);
void fn_80083B78(void*);

static inline const char* TitleFile() {
    int lang = (s8)fn_8024BC94()->lang;
    return lbl_80382650[lang][fn_801D09F0()];
}

struct Title {
    u8 pad[0x30];
    s16 x, y, m34;
    u8 m36, m37, m38, m39;
    s16 m3a, m3c;
    u8 pad3e[2];
    f32 m40;
    u8 m44;
    u8 pad45[3];
    void* m48;
    u8 m4c;
    u8 pad4d[3];
    s16 m50, m52;
    void* m54;
    void* m58;
    s16 m5c;
    u8 pad5e[2];
    void* m60;
    void* m64;
};

/* Tween process for a u8 field */
struct TweenB {
    u8 pad[0x30];
    int mode;
    u8* p;
    u8 from, to;
    u8 pad3a[2];
    u32 t, n;
};

/* Tween process for an s16 field */
struct TweenS {
    u8 pad[0x30];
    int mode;
    s16* p;
    s16 from, to;
    u32 t, n;
};

void fn_800C1220(Title* t) {
    t->x = 0;
    t->y = 0;
    t->m34 = 0xC8;
    t->m36 = 0;
    t->m37 = 0;
    t->m3a = 0;
    t->m3c = 0;
    t->m40 = lbl_804CD4B8;
    t->m44 = 0;
    t->m38 = 0;
    t->m48 = NULL;
    t->m4c = 0;
    t->m52 = 0;
    t->m50 = 0;
    t->m58 = NULL;
    t->m54 = NULL;
    t->m5c = 0;
    t->m60 = NULL;
    t->m64 = NULL;
    t->m39 = 0;
}

void fn_800C1280(Title* t) {
    fn_8023F1A0(TitleFile(), 0x40);
    switch (t->m37) {
    case 0:
        t->x = -0x5E;
        t->y = 0x19;
        break;
    case 1:
        if (t->m39 == 0) {
            t->x = 0x1D4;
            t->y = 0x19;
        } else {
            t->x = 0x1D8;
            t->y = 0x130;
        }
        break;
    }
}

void fn_800C1340(Title* t) {
    t->m64 = fn_8001D3EC(TitleFile(), 0x40);
}

void fn_800C229C(Title* t) {
    if (t->m64 != NULL) {
        fn_8001D424(t->m64);
    }
}

void fn_800C1220(Title*);

Title* fn_800C22B0(u8 a, void* parent) {
    Title* t = (Title*)fn_80081050(lbl_80382688, parent == NULL ? (void*)3 : parent);
    if (t != NULL) {
        fn_800C1220(t);
    }
    t->m37 = a;
    return t;
}

void fn_800C2310() {
    fn_8023F1A0(TitleFile(), 0);
}

struct Title2 {
    u8 pad[0x30];
    s16 m30;
    u8 m32, m33;
    void* m34;
    void* m38;
    u8 m3c, m3d;
    s16 m3e, m40, m42, m44, m46, m48, m4a, m4c;
    u8 pad4e[2];
    void* m50;
};

void fn_800C2364(Title2* t) {
    t->m50 = fn_8001D3EC(TitleFile(), 0x40);
}

void fn_800C23C8(Title2* t) {
    TweenB* p = (TweenB*)fn_80081194(lbl_80382778, t);
    p->mode = 0;
    p->p = &t->m32;
    p->from = t->m32;
    p->to = 0xFF;
    p->t = 0;
    p->n = 0xC;
}

void fn_800C2D60(Title2* t) {
    switch (t->m33) {
    case 0:
        fn_800C242C(t);
        break;
    case 1:
        fn_800C283C(t);
        break;
    }
}

void fn_800C2D88(Title2* t) {
    TweenB* p = (TweenB*)fn_80081194(lbl_80382778, t);
    p->mode = 0;
    p->p = &t->m32;
    p->from = t->m32;
    p->to = 0;
    p->t = 0;
    p->n = 0xE;
}

void fn_800C2DE8(Title2* t) {
    if (t->m50 != NULL) {
        fn_8001D424(t->m50);
    }
}

void fn_800C2DFC(void* parent) {
    Title2* t = (Title2*)fn_80081050(lbl_803826D8, parent == NULL ? (void*)3 : parent);
    if (t != NULL) {
        t->m30 = 0xC8;
        t->m32 = 0;
        t->m40 = -1;
        t->m3e = -1;
        t->m44 = -1;
        t->m42 = -1;
        t->m48 = -1;
        t->m46 = -1;
        t->m4c = -1;
        t->m4a = -1;
        t->m38 = NULL;
        t->m34 = NULL;
        t->m3d = 0;
        t->m3c = 0;
        t->m50 = NULL;
        t->m33 = 0;
    }
}

struct Title3 {
    u8 pad[0x30];
    s16 x, y, m34;
    u8 m36, m37, m38;
    u8 pad39[3];
    void* m3c;
    void* m40;
};

void fn_800C2E84(Title3* t) {
    fn_8023F1A0(TitleFile(), 0x40);
    switch (t->m37) {
    case 0:
        t->x = -0x54;
        t->y = 0x17A;
        break;
    case 1:
        t->x = 0x1EC;
        t->y = 0x17A;
        break;
    }
}

void fn_800C2F24(Title3* t) {
    t->m40 = fn_8001D3EC(TitleFile(), 0x40);
}

void fn_800C32EC(Title3* t) {
    if (t->m40 != NULL) {
        fn_8001D424(t->m40);
    }
}

Title3* fn_800C3300(u8 a, void* parent) {
    Title3* t = (Title3*)fn_80081050(lbl_80382728, parent == NULL ? (void*)3 : parent);
    if (t != NULL) {
        t->x = 0;
        t->y = 0;
        t->m34 = 0xC8;
        t->m36 = 0;
        t->m37 = 0;
        t->m38 = 0;
        t->m3c = NULL;
        t->m40 = NULL;
    }
    t->m37 = a;
    return t;
}

void fn_800C3374(TweenB* w) {
    int v;
    int m = w->mode;
    if (++w->t > w->n) {
        w->t = w->n;
    }
    if (w->t == 0) {
        v = w->from;
    } else {
        u32 n = w->n;
        if (w->t == n) {
            v = w->to;
        } else {
            v = fn_8017F68C(m, (f32)w->from, (f32)w->to, (f32)w->t, (f32)n);
        }
    }
    *w->p = v;
    if (w->t == w->n) {
        fn_80083B78(w);
    }
}

void fn_800C3460(TweenS* w) {
    int v;
    int m = w->mode;
    if (++w->t > w->n) {
        w->t = w->n;
    }
    if (w->t == 0) {
        v = w->from;
    } else {
        u32 n = w->n;
        if (w->t == n) {
            v = w->to;
        } else {
            v = fn_8017F68C(m, (f32)w->from, (f32)w->to, (f32)w->t, (f32)n);
        }
    }
    *w->p = v;
    if (w->t == w->n) {
        fn_80083B78(w);
    }
}

void* fn_800C3558() {
    return lbl_804CB6B4;
}

void fn_800C3560(void* v) {
    lbl_804CB6B4 = v;
}

struct Fl { u8 pad[0x1F]; u8 m1f; };

void fn_800C3568(void* v) {
    ((Fl*)lbl_804CB6B4)->m1f = 1;
    lbl_804CB6B4 = v;
}

void* fn_800C357C() {
    return lbl_804CB6B8;
}

void fn_800C3584(void* v) {
    lbl_804CB6B8 = v;
}

#define TWEEN_B(t, field, target, zero, cnt)                  \
    {                                                         \
        TweenB* p = (TweenB*)fn_80081194(lbl_80382778, t);    \
        p->mode = zero;                                       \
        p->p = &(t)->field;                                   \
        p->from = (t)->field;                                 \
        p->to = target;                                       \
        p->t = zero;                                          \
        p->n = cnt;                                           \
    }

#define TWEEN_X(t, target, zero, cnt)                         \
    {                                                         \
        TweenS* q = (TweenS*)fn_80081194(lbl_80382790, t);    \
        q->mode = 4;                                          \
        q->p = &(t)->x;                                       \
        q->from = (t)->x;                                     \
        q->to = target;                                       \
        q->t = zero;                                          \
        q->n = cnt;                                           \
    }

void fn_800C13A4(Title* t) {
    int z = 0;
    int n = 0xC;
    TWEEN_B(t, m36, 0xFF, z, n);
    switch (t->m37) {
    case 0:
        TWEEN_X(t, 0x16, z, n);
        break;
    case 1:
        if (t->m39 == 0) {
            TWEEN_X(t, 0x160, z, n);
        } else {
            TWEEN_X(t, 0x140, z, n);
        }
        break;
    }
}


void fn_800C2F88(Title3* t) {
    int z = 0;
    int n = 0xC;
    TWEEN_B(t, m36, 0xFF, z, n);
    switch (t->m37) {
    case 0:
        TWEEN_X(t, 0x10, z, n);
        break;
    case 1:
        TWEEN_X(t, 0x188, z, n);
        break;
    }
}


} // extern "C"
