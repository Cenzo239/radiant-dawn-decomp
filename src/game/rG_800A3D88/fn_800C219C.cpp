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









void fn_800C1220(Title*);





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













struct Title3 {
    u8 pad[0x30];
    s16 x, y, m34;
    u8 m36, m37, m38;
    u8 pad39[3];
    void* m3c;
    void* m40;
};

















struct Fl { u8 pad[0x1F]; u8 m1f; };







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







void fn_800C219C(Title* t) {
    int z = 0;
    int n = 0xE;
    TweenB* p = (TweenB*)fn_80081194(lbl_80382778, t);
    p->mode = z;
    u8* a = &t->m36;
    p->p = a;
    p->from = *a;
    p->to = z;
    p->t = z;
    p->n = n;
    switch (t->m37) {
    case 0:
        TWEEN_X(t, -0x5E, z, n);
        break;
    case 1:
        TWEEN_X(t, 0x1D4, z, n);
        break;
    }
}

void fn_800C31EC(Title3* t) {
    int z = 0;
    int n = 0xE;
    TweenB* p = (TweenB*)fn_80081194(lbl_80382778, t);
    p->mode = z;
    u8* a = &t->m36;
    p->p = a;
    p->from = *a;
    p->to = z;
    p->t = z;
    p->n = n;
    switch (t->m37) {
    case 0:
        TWEEN_X(t, -0x54, z, n);
        break;
    case 1:
        TWEEN_X(t, 0x1EC, z, n);
        break;
    }
}

}
