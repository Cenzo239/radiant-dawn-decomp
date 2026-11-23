#include "game/rF_8017F400/types.h"

#pragma auto_inline off

extern "C" {

typedef struct LNode {
    struct LNode* prev;
    struct LNode* next;
    void* val;
} LNode;

extern u32 lbl_804CB700;
extern double fn_80295CF0(double x);

void* fn_801B45AC(void** it) {
    return *it;
}

void fn_801B45B4(void** out, u8* list) {
    *out = *(void**)(list + 8);
}

void
#if TARGET_PC
* *
#endif
fn_801B45C0(void** out, void** src) {
    *out = *src;
#if TARGET_PC
    return out;
#endif
}

u32 fn_801B45CC(void) {
    u32 a = *(volatile u32*)&lbl_804CB700;
    u32 b = *(volatile u32*)&lbl_804CB700;
    u32 r = 0;
    if (a & 0x10) {
        if (!(b & 0x20)) {
            r = 1;
        }
    }
    return r;
}

void fn_801B45F0(u32* p) {
    *p |= 2;
}

double fn_801B4600(u32 v) {
    return fn_80295CF0(v);
}

void fn_801B4638(LNode** it, u32 n) {
    for (; n != 0; n--) {
        *it = (*it)->next;
    }
}

/* cursor-unit info window */
typedef struct UWin {
    u8 pad[0x30];
    u8* unit;  /* 0x30 */
    s16 x34;   /* 0x34 */
    s16 x36;   /* 0x36 */
    u8 alpha;  /* 0x38 */
    u8 t;      /* 0x39 */
    u8 maxA;   /* 0x3A */
    u8 dur;    /* 0x3B */
    u8 pad3C[4];
    void* tex; /* 0x40 */
    s16 x44;   /* 0x44 */
    s16 x46;   /* 0x46 */
} UWin;

extern char lbl_8036DE44[];
extern u8 lbl_803CAB38[];
extern u8 lbl_803EC898[];
extern u8* lbl_804CB810;
extern u8 lbl_80389480[];
extern void fn_801C6EAC(const char* a, const char* b, char* out);
extern void* fn_8001D3EC(const char* path, int a);
#if TARGET_PC
extern FE10_PROTO void fn_8017DAD4(const char* path, ptr32<const void>, void* arg, int z);
extern FE10_PROTO void* fn_80177284(ptr32<const void>, void* arg);
#else
extern void fn_8017DAD4(const char* path, void* cb, void* arg, int z);
extern void* fn_80177284(void* cb, void* arg);
#endif
extern void fn_801B486C(void* p);
extern void fn_8001D424(void* p);
extern void fn_80083DC4(void* p, int r);
extern f32 fn_8001EF30(f32 a, f32 b, f32 c, f32 d);
extern void fn_80083B78(void* p);
extern void* fn_80081050(void* cls, void* parent);
extern void fn_800846BC(void* cls);
extern void* fn_80083B84(void* cls);
extern void fn_803080DC(int a, int b, int c, int d);

void fn_801B5794(UWin* p) {
    char path[0x60];
    fn_801C6EAC(lbl_8036DE44 + 0xD, lbl_8036DE44 + 0x26, path);
    p->tex = fn_8001D3EC(path, 0x80);
}

void fn_801B57E4(UWin* p) {
    char path[0x60];
    p->x36 = -1;
    p->alpha = 0;
    p->t = 0;
    p->maxA = 0xFF;
    p->dur = 4;
    p->x34 = 0;
    p->unit = NULL;
    p->x44 = -1;
    p->x46 = -1;
    p->tex = NULL;
    fn_801C6EAC(lbl_8036DE44 + 0xD, lbl_8036DE44 + 0x26, path);
    fn_8017DAD4(path, (void*)fn_801B5794, p, 0x80);
    fn_80177284((void*)fn_801B486C, p);
}

void fn_801B5884(UWin* p) {
    if (p->tex != NULL) {
        fn_8001D424(p->tex);
    }
    p->tex = NULL;
}

void fn_801B58C8(UWin* p) {
    p->t = 0;
    p->alpha = 0;
    p->x36 = -1;
    p->unit = NULL;
}

static inline u8* CursorUnit(void) {
    s8 y = *(f32*)(lbl_803CAB38 + 0x938);
    s8 x = *(f32*)(lbl_803CAB38 + 0x934);
    u8 id = *(lbl_803EC898 + (x + (y << 6)) + 0xD);
    if (id != 0) {
        return lbl_804CB810 + (id - 1) * 0x3F0;
    }
    return NULL;
}

void fn_801B58E4(UWin* p) {
    u8* u = CursorUnit();
    if (u != NULL) {
        p->t = p->dur;
        p->alpha = p->maxA;
        p->unit = u;
    } else {
        p->t = 0;
        p->alpha = 0;
        p->unit = NULL;
    }
}

void fn_801B5988(UWin* p) {
    u8* u = CursorUnit();
    if (u != NULL) {
        if (p->unit == NULL) {
            fn_80083DC4(p, 2);
        }
        if (p->unit != u) {
            p->x36 = -1;
        }
        p->unit = u;
    } else if (p->unit != NULL) {
        fn_80083DC4(p, 3);
    }
}

void fn_801B5A74(UWin* p) {
    u8* u = CursorUnit();
    p->unit = u;
    p->x36 = -1;
    if (u == NULL) {
        fn_80083DC4(p, 6);
    }
}

void fn_801B5B14(UWin* p) {
    if (p->t < p->dur) {
        p->t++;
    }
    p->alpha = fn_8001EF30(0.0f, p->maxA, p->dur, p->t);
    if (p->t == p->dur) {
        fn_80083B78(p);
    }
}

void fn_801B5BC8(UWin* p) {
    u8* u = CursorUnit();
    p->unit = u;
    if (u == NULL) {
        fn_80083DC4(p, 7);
    }
}

void fn_801B5C60(UWin* p) {
    if (p->t != 0) {
        p->t--;
    }
    p->alpha = fn_8001EF30(0.0f, p->maxA, p->dur, p->t);
    if (p->t == 0) {
        fn_80083B78(p);
        p->unit = NULL;
    }
}

void fn_801B5D14(void* parent) {
    fn_80081050(lbl_80389480, parent);
}

void fn_801B5D24(void) {
    fn_800846BC(lbl_80389480);
}

void fn_801B5D30(void) {
    void* p = fn_80083B84(lbl_80389480);
    if (p != NULL) {
        fn_80083DC4(p, 4);
    }
}

void fn_801B5D68(void) {
    void* p = fn_80083B84(lbl_80389480);
    if (p != NULL) {
        fn_80083DC4(p, 5);
    }
}

void fn_801B5DA0(void) {
    void* p = fn_80083B84(lbl_80389480);
    if (p != NULL) {
        fn_80083DC4(p, 7);
    }
}

int fn_801B5DD8(int* x, int* y) {
    UWin* p = (UWin*)fn_80083B84(lbl_80389480);
    if (p != NULL) {
        *x = p->x44;
        *y = p->x46;
        return 1;
    }
    return 0;
}

void fn_801B5E3C(void) { fn_803080DC(0xE0, 0x68, 0x150, 0x120); }
void fn_801B5E50(void) { fn_803080DC(0, 0x68, 0x260, 0x120); }
void fn_801B5E64(void) { fn_803080DC(0xE0, 0, 0x150, 0x1C0); }
void fn_801B5E78(void) { fn_803080DC(0, 0x60, 0x80, 0x128); }
void fn_801B5E8C(void) { fn_803080DC(0, 0, 0x78, 0x1C0); }
void fn_801B5EA0(void) { fn_803080DC(0, 0, 0x80, 0x1C0); }

}
