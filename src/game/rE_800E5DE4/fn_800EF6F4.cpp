#include "game/rE_800E5DE4/types.h"
#pragma auto_inline off
typedef struct G { u8 pad[0x30]; f32 x; f32 y; Handle* h; void* font; u8 b[8]; } G;
typedef struct UO { u8 pad[0x48B]; u8 b48B; } UO;
typedef struct GP { u8 pad[0x30]; u8 b30; u8 b31; u8 pad32[2]; int x[2]; int y; void* font; G* g[2]; Handle* h[2]; } GP;
extern "C" {
extern u8 lbl_80367458[];
extern u8 lbl_80384ED0[];
extern void* fn_8001D3B4(const char*);
extern Vec fn_800D5DC4(Handle*);
extern G* fn_80081050(void*, GP*);
static inline void SetP(G* g, f32 x, f32 y) { g->x = x; g->y = y; }
void fn_800EF6F4(GP* p, Handle* a, Handle* b, int mode) {
/*P*/
    int i;
    int cnt;
    int mn;
    int mx;
    int m2;
/*E*/
    m2 = mode;
    p->b30 = mode;
    p->b31 = 0;
    p->font = fn_8001D3B4((char*)lbl_80367458);
    p->g[0] = 0;
    p->g[1] = 0;
    p->h[0] = a;
    p->h[1] = b;
    mn = 10000;
    mx = -10000;
    cnt = 0;
    switch (m2) {
    case 0:
        for (i = 0; i < 2; i++) {
            if (p->h[i]) {
                Vec v = fn_800D5DC4(p->h[i]);
                if (mn > v.y) mn = v.y;
                if (mx < v.y) mx = v.y;
                cnt++;
            }
        }
        p->y = mx + 0x30;
        if (p->y < 0xE0) p->y = 0xE0;
        if (p->y > 0x166) p->y = 0x166;
        break;
    case 2:
        p->y = 0xA0;
        break;
    case 3:
        p->y = 0x140;
        break;
    case 1:
        p->y = 0x28;
        break;
    }
    p->x[0] = 0xBC;
    p->x[1] = 0xBC;
    if (cnt == 2) {
        if (((UO*)a->obj)->b48B) {
            p->x[0] = 0x40;
            p->x[1] = 0x138;
        } else {
            p->x[0] = 0x138;
            p->x[1] = 0x40;
        }
    }
    for (i = 0; i < 2; i++) {
        if (p->h[i]) {
            G* g = fn_80081050(lbl_80384ED0, p);
            g->y = 0.0f;
            g->x = 0.0f;
            g->h = 0;
            g->font = 0;
            g->b[0] = 0;
            g->b[1] = 0;
            g->b[2] = 0;
            g->b[3] = 0;
            g->b[4] = 0;
            g->b[5] = 0;
            g->b[6] = 0;
            g->b[7] = 0;
            p->g[i] = g;
            g->font = p->font;
            p->g[i]->h = p->h[i];
            SetP(p->g[i], p->x[i], p->y);
            p->g[i]->b[7] = 0;
        }
    }
}
}
