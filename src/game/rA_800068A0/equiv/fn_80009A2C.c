/* Round 18, functionally equal (regs level): fn_80009A2C (GActor_UpdateTrail). Self-contained: fn_80006CF8.c with its exported bodies removed (the ones the original inlines are kept as static inline copies named *_inl) plus wip/fn_80009A2C.c. */
#include "game/rA_800068A0/types.h"

/* GActor.c: base actor object (size 0x9C). */
typedef struct Mtx30 {
    u8 data[0x30];
} Mtx30;

typedef f32 Mtx[3][4];

typedef struct Vec {
    f32 x, y, z;
} Vec;

typedef struct GNode {
    u8 x0[0xC];
    u32 flags;          /* 0x0C */
    u8 x10[0x70 - 0x10];
    Vec pos;            /* 0x70 */
    u8 x7C[0xBC - 0x7C];
    Mtx mtx;            /* 0xBC */
    u32 xEC_hi : 28;
    u32 mode : 4;       /* 0xEC low nibble */
    char* name;         /* 0xF0 */
} GNode;

typedef struct GModel {
    u8 x0[8];
    s32 nodeCount;
    GNode* nodes;
} GModel;

typedef struct GRes44 {
    u8 x0[0x10];
    s32 loop;           /* 0x10 */
    s32 start;          /* 0x14 */
    s32 end;            /* 0x18 */
} GRes44;

typedef struct GEntry20 {
    char* name;
    u16 flags;
    u8 x6[0x1A];
} GEntry20;

typedef struct GRes48 {
    u8 x0[0x34];
    GEntry20* entries;  /* 0x34 */
    u8 x38[0x48 - 0x38];
    void* x48;
    u16 x4C;
    u16 x4E;
    u8 x50[4];
    u16 entryCount;     /* 0x54 */
} GRes48;

typedef struct GRes50 {
    u8 x0[0xC];
    u32 flags;
} GRes50;

typedef struct GActor GActor;

typedef struct GColor {
    u8 r, g, b, a;
} GColor;

typedef struct GKey {
    u16 id;
    s16 val;
} GKey;

typedef struct GKeySet {
    u8 x0[3];
    u8 count;
    GKey keys[1];
} GKeySet;

typedef struct GChildList {
    u8 mode;
    u8 count;
    u8 x2;
    u8 x3;
    GColor color;
    GActor** items;
} GChildList;

struct GActor {
    u32 flags;          /* 0x00: bit0 = heap allocated */
    GActor* parent;     /* 0x04 */
    GColor color;       /* 0x08 */
    u8 xC[4];           /* 0x0C: initialised by fn_8001E540(.., 7) */
    u8 x10[0x30];       /* 0x10: initialised by fn_80312318 */
    struct GModel* model;   /* 0x40 */
    struct GRes44* x44;
    struct GRes48* x48;
    void* x4C;
    struct GRes50* x50;
    u32 x54;
    f32 x58;
    f32 scale;          /* 0x5C */
    struct Mtx30* x60;
    void* x64;
    u8* x68;
    u8* x6C;
    u8* x70;
    GActor* child;      /* 0x74 */
    f32 x78;
    struct GChildList* children; /* 0x7C */
    u8 x80;
    s8 x81;
    u8 x82;
    u8 x83;
    u32 x84;
    u32 x88;
    GKey keys[4];       /* 0x8C */
};

extern f32 lbl_804CA040;
extern char lbl_80360AAC[];

extern void fn_8001E008(const char* file, int line, const char* msg);
extern void fn_8001E540(void* p, int n);
extern void fn_80312318(void* p);
extern void* fn_80078CCC(u32 size, const char* name, u32 flags);
extern void fn_80078E24(void* p);
extern void fn_80007374(GActor* a);
extern void* fn_80078D9C(u32 size, const char* name, u32 flags);
extern void* fn_80079940(u32 size, u32 align);
extern void fn_80079978(void* p);
extern s32 fn_8001CD54(void* p);
extern void fn_80312344(void* src, void* dst); /* PSMTXCopy */
extern void DCFlushRange(void* p, u32 size);
extern void fn_8001528C(GActor* a);
extern void fn_8000EC2C(GModel* p);
extern void fn_80018094(GRes48* p);
extern void fn_8001D424(void* p);
extern void fn_8000BE20(GRes44* p);
extern void fn_8001561C(GActor* a);
extern BOOL fn_8001E548(const char* a, const char* b);
extern void fn_8001D44C(void* p, Mtx m);
extern void fn_80312378(Mtx a, Mtx b, Mtx ab);
extern void fn_80312DB4(Mtx m, Vec* src, Vec* dst); /* PSMTXMultVec */
extern void fn_8001E6D0(Mtx src, Mtx dst);
extern void fn_803134C4(Vec* src, Vec* dst); /* PSVECNormalize */
extern f32 fn_80313508(Vec* v);              /* PSVECMag */
extern void fn_8000C920(GActor* a);
extern void fn_8000EC30(GNode* nodes, Mtx30* mtx, void* buf64);
extern void fn_8001C904(GActor* a);
extern void fn_8001CD78(GActor* a);
extern void fn_800158FC(GActor* a);
extern void fn_800180F0(GActor* a);
extern u8* fn_8000F470(void);
extern BOOL fn_80291480(const char* a, const char* b);
extern GKeySet* fn_80009CD0(GRes44* anim, s32 frame);
extern void fn_80017DA8(GActor* a, f32 frame);
extern s32 fn_80009FD0(GRes44* anim, s32 a, u32 id);
extern s32 fn_80009EF8(GRes44* anim, s32 a, s32 b);
extern GRes44* fn_8000BDB0(void* src, u32 x);
extern GRes48* fn_80017FD0(void* src, u32 x);
extern GModel* fn_8000EBCC(void* src, u32 x);
extern void* fn_8001D3EC(void* src, u16 x);
extern void fn_800161E0(GActor* src, GActor* dst);
extern s32 fn_80291188(const char* a, const char* b); /* strcmp */
extern void fn_80009454(GActor* a, s32 n, u8 mode); /* GActor_CreateTrail, see wip/ */
extern const Vec lbl_80360AA0;               /* {1, 1, 1} */

static inline void GActor_FreeBuf(GActor* a, void** pp) {
    if (*pp != NULL) {
        if (a->flags & 0x40000) {
            fn_80078E24(*pp);
            *pp = NULL;
        }
        if (a->flags & 0x80000) {
            fn_80079978(*pp);
        }
        fn_80078E24(*pp);
        *pp = NULL;
    }
}

f32 fn_80006CF8(void);

void fn_80006D00(f32 v);

f32 fn_80006D08(GActor* a);

/* GActor_Init */
GActor* fn_80006D18(GActor* a);

/* GActor_New */
GActor* fn_80006E1C(void);

void fn_80006E94(GActor* a);

/* GActor_Delete */
void fn_80006EE0(GActor* a);

static inline void* GActor_Alloc(GActor* a, u32 size) {
    if (a->flags & 0x40000) {
        return fn_80078D9C(size, lbl_80360AAC + 0x24, 0);
    } else if (a->flags & 0x80000) {
        return fn_80079940(size, 0x40);
    } else {
        return fn_80078CCC(size, lbl_80360AAC + 0x24, 0);
    }
}

static inline GModel* GActor_FindModel(GActor* a) {
    for (; a != NULL; a = a->parent) {
        if (a->model != NULL) {
            return a->model;
        }
    }
    return NULL;
}

static inline GRes48* GActor_Find48(GActor* a) {
    for (; a != NULL; a = a->parent) {
        if (a->x48 != NULL) {
            return a->x48;
        }
    }
    return NULL;
}

static inline GRes50* GActor_Find50(GActor* a) {
    for (; a != NULL; a = a->parent) {
        if (a->x50 != NULL) {
            return a->x50;
        }
    }
    return NULL;
}

static inline GRes44* GActor_Find44(GActor* a) {
    for (; a != NULL; a = a->parent) {
        if (a->x44 != NULL) {
            return a->x44;
        }
    }
    return NULL;
}

void fn_80006F20(GActor* a);

static inline void GActor_FreeChildren(GActor* a) {
    s32 i;
    GActor* c;
    if (a != NULL && a->children != NULL) {
        for (i = 0; i < a->children->count; i++) {
            c = a->children->items[i];
            fn_80006EE0(c);
            a->children->items[i] = NULL;
        }
        fn_80078E24(a->children->items);
        a->children->items = NULL;
        fn_80078E24(a->children);
        a->children = NULL;
    }
}

/* GActor_Destroy */
#pragma use_lmw_stmw on
void fn_80007374(GActor* a);
#pragma use_lmw_stmw off

static inline Mtx30* GActor_FindMtxBuf(GActor* a) {
    for (; a != NULL; a = a->parent) {
        if (a->x60 != NULL) {
            return a->x60;
        }
    }
    return NULL;
}

static inline GNode* GModel_GetNode(GModel* m, s32 idx) {
    if (idx < 0) {
        return NULL;
    }
    if (idx >= m->nodeCount) {
        return NULL;
    }
    return &m->nodes[idx];
}

/* GActor_FindNodeByName */
s32 fn_80007630(GActor* a, const char* name);

/* GActor_GetNodeWorldPos */
Vec fn_800076E8(GActor* a, s32 idx);

/* GActor_GetNodeMtx */
void fn_80007860(GActor* a, s32 idx, Mtx out);

/* GActor_GetNode */
GNode* fn_800078E4(GActor* a, s32 idx);

/* GActor_GetNodeScale */
f32 fn_8000793C(GActor* a, s32 idx);

/* GActor_SetNodeFlags */
void fn_80007A00(GActor* a, u32 mask);

/* GActor_ClearNodeFlags */
void fn_80007A5C(GActor* a, u32 mask);

#pragma use_lmw_stmw on
/* GActor_SetNodeModeAlt */
void fn_80007ABC(GActor* a, BOOL on);
#pragma use_lmw_stmw off

static inline void* GActor_Find64(GActor* a) {
    for (; a != NULL; a = a->parent) {
        if (a->x64 != NULL) {
            return a->x64;
        }
    }
    return NULL;
}

#pragma use_lmw_stmw on
/* GActor_Update */
void fn_80007C58(GActor* a);
#pragma use_lmw_stmw off

void fn_80007DE8(GActor* a);

void fn_80007E90(GActor* a);

GModel* fn_80007EE4(GActor* a);

GRes44* fn_80007F10(GActor* a);

GRes48* fn_80007F3C(GActor* a);

void* fn_80007F68(GActor* a);

GRes50* fn_80007F94(GActor* a);

u8* fn_80007FC0(GActor* a);

u8* fn_80008060(GActor* a);

u8* fn_8000808C(GActor* a);

Mtx30* fn_800080B8(GActor* a);

void* fn_800080E4(GActor* a);


f32 fn_800081B4(GActor* a);

f32 fn_800081BC(GActor* a);

/* GActor_SetMtx */
void fn_800081C4(GActor* a, Mtx m);

/* GActor_SetFrame */
void fn_8000866C(GActor* a, f32 frame);

/* GActor_SetFrameById */
BOOL fn_800087FC(GActor* a, u32 id);

/* GActor_SetScale */
void fn_800088A0(GActor* a, f32 scale);

/* GActor_PushAnim: keeps up to 4 blended animation layers in the child chain */
void fn_800088B0(GActor* a, GRes44* anim);

/* GActor_DeleteChain. Self-recursion is inlined exactly 3 levels deep in the
 * original; inline_depth(3) reproduces that. */
#pragma push
#pragma inline_depth(3)
void fn_80008A38(GActor* a);
#pragma pop

/* GActor_HasKey */
BOOL fn_80008C98(GActor* a, u16 id);

/* GActor_GetKeyValue */
s32 fn_80008CF0(GActor* a, u16 id);

/* GActor_FindKeyInList */
u16 fn_80008D48(GActor* a, const u16* list);

s32 fn_80008E28(GActor* a, u32 id);

s32 fn_80008E5C(GActor* a, s32 x, s32 y);

s32 fn_80008E88(GActor* a, s32 x, u32 id);

/* GActor_HasAnyKey */
BOOL fn_80008EB4(GActor* a);

/* GActor_SetColor */

#define fn_80008F10 fn_80008F10_inl
static inline void fn_80008F10(GActor* a, s32 r, s32 g, s32 b) {
    a->color.r = r;
    a->color.g = g;
    a->color.b = b;
}

/* GActor_SetAlpha */

#define fn_80008F20 fn_80008F20_inl
static inline void fn_80008F20(GActor* a, u8 alpha) {
    a->color.a = alpha;
    if (alpha != 0xFF) {
        a->flags |= 0x100;
    } else {
        a->flags &= ~0x100;
    }
}

void fn_80008F4C(GActor* a, GActor* parent);

void fn_80008F54(GActor* a, u8 v);

void fn_80008F5C(GActor* a, s8 v);

void fn_80008F64(GActor* a, u8 v);

/* GActor_SetAnimRes */
void fn_80008F6C(GActor* a, void* src);

void fn_80009030(GActor* a, void* src);

void fn_80009090(GActor* a, void* src);

void fn_800090F0(GActor* a, void* src);

void fn_80009150(GActor* a, void* src, u32 x);

void fn_80009214(GActor* a, void* src, u32 x);

void fn_80009274(GActor* a, void* src, u32 x);

void fn_800092D4(GActor* a, void* src, u32 x);

/* GActor_CopyPose */
void fn_80009334(GActor* src, GActor* dst);


#pragma use_lmw_stmw on
/* GActor_ResetTrail */
void fn_800096E4(GActor* a, s32 n);

/* GActor_ResetTrailMode1 */
void fn_800097B0(GActor* a, s32 n);
#pragma use_lmw_stmw off

/* GActor_SetTrailColor */

#define fn_8000987C fn_8000987C_inl
static inline void fn_8000987C(GActor* a, const GColor* c) {
    GChildList* list;
    s32 i;
    if (a == NULL || (list = a->children) == NULL) {
        return;
    }
    list->color = *c;
    for (i = 0; i < list->count; i++) {
        s32 al = a->color.a - (a->color.a * i) / list->x2;
        al = al * c->a / 255;
        fn_80008F20(list->items[i], al);
        fn_80008F10(list->items[i], c->r, c->g, c->b);
    }
}

#pragma use_lmw_stmw on
/* GActor_DeleteTrail */
void fn_80009974(GActor* a);
#pragma use_lmw_stmw off


/* GActor_FindNodeByName2 */
s32 fn_80009BC8(GActor* a, const char* name);

/* GActor_SetEntryFlags */
void fn_80009C7C(GActor* a, u16 mask);
static inline void fd(GActor* a, GRes48** r) {
    for (; a != NULL; a = a->parent) {
        if (a->x48 != NULL) {
            *r = a->x48;
            return;
        }
    }
    *r = NULL;
}
#pragma use_lmw_stmw on
GEntry20* fn_80008110(GActor* a, const char* name);
#pragma use_lmw_stmw off

/* fn_80009A2C (GActor_UpdateTrail): near miss, 36 of 103 words differ, all
 * volatile-register numbering inside the inlined fn_8000987C (theirs uses
 * one register more: list in r5, i in r3). Same issue as wip/fn_80009454.c.
 * Needs ../fn_80006CF8.c. */
/* GActor_UpdateTrail */
void fn_80009A2C(GActor* a) {
    GChildList* list;
    s32 i;
    if (a == NULL || (list = a->children) == NULL) {
        return;
    }
    for (i = list->count - 1; i >= 0; i--) {
        fn_80009334(i == 0 ? a : list->items[i - 1], list->items[i]);
    }
    {
        GColor col = list->color;
        fn_8000987C(a, &col);
    }
    if (list->x2 < list->count) {
        list->x2++;
    }
}
