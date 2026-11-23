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
#if TARGET_PC
extern FE10_PROTO char * fn_80291480(const char* a, const char* b);
#else
extern BOOL fn_80291480(const char* a, const char* b);
#endif
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

f32 fn_80006CF8(void) {
    return lbl_804CA040;
}

void fn_80006D00(f32 v) {
    lbl_804CA040 = v;
}

f32 fn_80006D08(GActor* a) {
    return a->scale * fn_80006CF8();
}

/* GActor_Init */
GActor* fn_80006D18(GActor* a) {
    if (a == NULL) {
        fn_8001E008(lbl_80360AAC, 0x2B, lbl_80360AAC + 9);
    }
    a->flags = 0;
    a->parent = NULL;
    a->model = NULL;
    a->x44 = NULL;
    a->x48 = NULL;
    a->x4C = NULL;
    a->x50 = NULL;
    a->x60 = NULL;
    a->x64 = NULL;
    a->x68 = NULL;
    a->x6C = NULL;
    a->x54 = 0;
    a->x58 = 0.0f;
    a->scale = 1.0f;
    a->child = NULL;
    a->x78 = 1.0f;
    a->color.r = 0x80;
    a->color.g = 0x80;
    a->color.b = 0x80;
    a->color.a = 0xFF;
    a->x80 = 0xFF;
    a->x81 = -1;
    a->x82 = 0x80;
    a->children = NULL;
    a->x84 = 0;
    a->x88 = 0;
    a->keys[0].id = 0xFFFF;
    a->keys[0].val = 0;
    a->keys[1].id = 0xFFFF;
    a->keys[1].val = 0;
    a->keys[2].id = 0xFFFF;
    a->keys[2].val = 0;
    a->keys[3].id = 0xFFFF;
    a->keys[3].val = 0;
    fn_8001E540(a->xC, 7);
    fn_80312318(a->x10);
    return a;
}

/* GActor_New */
GActor* fn_80006E1C(void) {
    GActor* a = (GActor*)fn_80078CCC(0x9C, lbl_80360AAC + 0x24, 0);
    if (a == NULL) {
        fn_8001E008(lbl_80360AAC, 0x5D, lbl_80360AAC + 0x25);
    }
    fn_80006D18(a);
    a->flags |= 1;
    return a;
}

void fn_80006E94(GActor* a) {
    if (a == NULL) {
        fn_8001E008(lbl_80360AAC, 0x67, lbl_80360AAC + 9);
    }
    fn_80006D18(a);
}

/* GActor_Delete */
void fn_80006EE0(GActor* a) {
    fn_80007374(a);
    if (a->flags & 1) {
        fn_80078E24(a);
    }
}

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

void fn_80006F20(GActor* a) {
    GModel* model;
    GRes48* r48;
    GRes50* r50;
    GRes44* r44;
    s32 j;
    s32 i;
    GNode* node;

    if (a == NULL) {
        fn_8001E008(lbl_80360AAC, 0x91, lbl_80360AAC + 9);
    }
    GActor_FreeBuf(a, (void**)&a->x60);
    GActor_FreeBuf(a, &a->x64);
    GActor_FreeBuf(a, (void**)&a->x68);
    GActor_FreeBuf(a, (void**)&a->x6C);

    model = GActor_FindModel(a);
    r48 = GActor_Find48(a);
    r50 = GActor_Find50(a);
    r44 = GActor_Find44(a);

    if (model != NULL) {
        a->x60 = (Mtx30*)GActor_Alloc(a, model->nodeCount * 0x30);
        i = 0;
        j = 0;
        node = model->nodes;
        for (; i < model->nodeCount; i++, node++) {
            fn_80312344(node->mtx, (u8*)a->x60 + j);
            j += 0x30;
        }
    }
    if (r48 != NULL && r48->x48 != NULL) {
        s32 n = fn_8001CD54(r48->x48);
        s32 size;
        a->x64 = GActor_Alloc(a, model->nodeCount * 0x30);
        size = n * 2;
        a->x68 = GActor_Alloc(a, size);
        DCFlushRange(a->x64, model->nodeCount * 0x30);
        DCFlushRange(a->x68, size);
    }
    if (r50 != NULL && (r50->flags & 1)) {
        u32 n6 = r48->x4C * 6;
        u32 n3 = r48->x4E * 3;
        a->x6C = (u8*)GActor_Alloc(a, n6 + n3);
        a->x70 = a->x6C + n6;
    }
    if (r44 != NULL) {
        a->x58 = r44->start;
    }
    fn_8001528C(a);
}

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
void fn_80007374(GActor* a) {
    if (a == NULL) {
        fn_8001E008(lbl_80360AAC, 0xD8, lbl_80360AAC + 9);
    }
    if (a->parent != NULL && a->parent->child == a) {
        a->parent->child = NULL;
    }
    if (a->child != NULL) {
        fn_80006EE0(a->child);
        a->child = NULL;
    }
    if (a->children != NULL) {
        GActor_FreeChildren(a);
        a->children = NULL;
    }
    GActor_FreeBuf(a, (void**)&a->x60);
    GActor_FreeBuf(a, &a->x64);
    GActor_FreeBuf(a, (void**)&a->x68);
    GActor_FreeBuf(a, (void**)&a->x6C);
    if (a->model != NULL) {
        fn_8000EC2C(a->model);
    }
    if (a->x48 != NULL) {
        fn_80018094(a->x48);
    }
    if (a->x4C != NULL) {
        fn_8001D424(a->x4C);
    }
    if (a->x44 != NULL) {
        fn_8000BE20(a->x44);
    }
    fn_8001561C(a);
    a->x64 = NULL;
    a->x60 = NULL;
    a->x68 = NULL;
    a->x6C = NULL;
    a->model = NULL;
    a->x48 = NULL;
    a->x4C = NULL;
    a->x44 = NULL;
    a->x54 = 0;
}
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
s32 fn_80007630(GActor* a, const char* name) {
    GModel* model = GActor_FindModel(a);
    GNode* node = model->nodes;
    s32 i;
    if (name != NULL) {
        for (i = 0; i < model->nodeCount; i++, node++) {
            if ((node->flags & 0x80000000) && fn_8001E548(node->name, name)) {
                return i;
            }
        }
    }
    return -1;
}

/* GActor_GetNodeWorldPos */
Vec fn_800076E8(GActor* a, s32 idx) {
    GNode* node;
    Mtx30* buf;
    Mtx anim;
    Mtx local;
    Mtx m;

    if (a == NULL) {
        fn_8001E008(lbl_80360AAC, 0x130, lbl_80360AAC + 9);
    }
    {
    Vec v = {0};
    node = GModel_GetNode(GActor_FindModel(a), idx);
    if (node != NULL) {
        buf = GActor_FindMtxBuf(a);
        fn_8001D44C(a->xC, local);
        fn_80312344(&buf[idx], anim);
        if (node->flags & 0x80) {
            v.x = node->pos.x;
            v.y = node->pos.y;
            v.z = node->pos.z;
        } else {
            v.x = 0.0f;
            v.y = 0.0f;
            v.z = 0.0f;
        }
        fn_80312378(local, anim, m);
        fn_80312DB4(m, &v, &v);
    }
    return v;
    }
}

/* GActor_GetNodeMtx */
void fn_80007860(GActor* a, s32 idx, Mtx out) {
    Mtx30* buf = GActor_FindMtxBuf(a);
    fn_8001D44C(a->xC, out);
    fn_80312378(out, (void*)&buf[idx], out);
}

/* GActor_GetNode */
GNode* fn_800078E4(GActor* a, s32 idx) {
    return GModel_GetNode(GActor_FindModel(a), idx);
}

/* GActor_GetNodeScale */
f32 fn_8000793C(GActor* a, s32 idx) {
    Mtx30* buf = GActor_FindMtxBuf(a);
    Vec v;
    Mtx m;
    fn_8001D44C(a->xC, m);
    fn_80312378(m, (void*)&buf[idx], m);
    fn_8001E6D0(m, m);
    v = lbl_80360AA0;
    fn_803134C4(&v, &v);
    fn_80312DB4(m, &v, &v);
    return fn_80313508(&v);
}

/* GActor_SetNodeFlags */
void fn_80007A00(GActor* a, u32 mask) {
    GModel* model = GActor_FindModel(a);
    GNode* node;
    s32 i;
    if (model == NULL) {
        return;
    }
    node = model->nodes;
    for (i = 0; i < model->nodeCount; i++, node++) {
        node->flags |= mask;
    }
}

/* GActor_ClearNodeFlags */
void fn_80007A5C(GActor* a, u32 mask) {
    GModel* model = GActor_FindModel(a);
    GNode* node;
    s32 i;
    if (model == NULL) {
        return;
    }
    node = model->nodes;
    for (i = 0; i < model->nodeCount; i++, node++) {
        node->flags &= ~mask;
    }
}

#pragma use_lmw_stmw on
/* GActor_SetNodeModeAlt */
void fn_80007ABC(GActor* a, BOOL on) {
    GModel* model = GActor_FindModel(a);
    GNode* node;
    s32 i;
    if (model != NULL) {
        node = model->nodes;
        for (i = 0; i < model->nodeCount; i++, node++) {
            if (on) {
                switch (node->mode) {
                case 1: node->mode = 7; break;
                case 2: node->mode = 8; break;
                case 3: node->mode = 9; break;
                case 4: node->mode = 10; break;
                case 5: node->mode = 11; break;
                case 6: node->mode = 12; break;
                }
            } else {
                switch (node->mode) {
                case 7: node->mode = 1; break;
                case 8: node->mode = 2; break;
                case 9: node->mode = 3; break;
                case 10: node->mode = 4; break;
                case 11: node->mode = 5; break;
                case 12: node->mode = 6; break;
                }
            }
        }
    }
}
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
void fn_80007C58(GActor* a) {
    GModel* model;
    GRes48* r48;
    GRes50* r50;
    Mtx30* mtx;
    void* buf64;
    if (a == NULL) {
        fn_8001E008(lbl_80360AAC, 0x1D2, lbl_80360AAC + 9);
    }
    if (a->x60 != NULL) {
        model = GActor_FindModel(a);
        GActor_Find44(a);
        r48 = GActor_Find48(a);
        r50 = GActor_Find50(a);
        mtx = GActor_FindMtxBuf(a);
        buf64 = GActor_Find64(a);
        fn_8000C920(a);
        fn_8000EC30(model->nodes, mtx, buf64);
        if (r50 != NULL) {
            fn_8001C904(a);
        }
        if (r48 != NULL && r48->x48 != NULL) {
            fn_8001CD78(a);
        }
        if (a->x54 != 0) {
            fn_800158FC(a);
        }
    }
}
#pragma use_lmw_stmw off

void fn_80007DE8(GActor* a) {
    GRes48* r48;
    void* save48;
    u32 save54;
    if (a == NULL) {
        fn_8001E008(lbl_80360AAC, 0x1F7, lbl_80360AAC + 9);
    }
    r48 = GActor_Find48(a);
    save48 = r48->x48;
    save54 = a->x54;
    r48->x48 = NULL;
    a->x54 = 0;
    fn_80007C58(a);
    r48->x48 = save48;
    a->x54 = save54;
}

void fn_80007E90(GActor* a) {
    if (a == NULL) {
        fn_8001E008(lbl_80360AAC, 0x20C, lbl_80360AAC + 9);
    }
    fn_80007C58(a);
    fn_800180F0(a);
}

GModel* fn_80007EE4(GActor* a) {
    for (; a != NULL; a = a->parent) {
        if (a->model != NULL) {
            return a->model;
        }
    }
    return NULL;
}

GRes44* fn_80007F10(GActor* a) {
    for (; a != NULL; a = a->parent) {
        if (a->x44 != NULL) {
            return a->x44;
        }
    }
    return NULL;
}

GRes48* fn_80007F3C(GActor* a) {
    for (; a != NULL; a = a->parent) {
        if (a->x48 != NULL) {
            return a->x48;
        }
    }
    return NULL;
}

void* fn_80007F68(GActor* a) {
    for (; a != NULL; a = a->parent) {
        if (a->x4C != NULL) {
            return a->x4C;
        }
    }
    return NULL;
}

GRes50* fn_80007F94(GActor* a) {
    for (; a != NULL; a = a->parent) {
        if (a->x50 != NULL) {
            return a->x50;
        }
    }
    return NULL;
}

u8* fn_80007FC0(GActor* a) {
    u8* buf;
    for (; a != NULL; a = a->parent) {
        if (a->x68 != NULL) {
            buf = a->x68;
            goto found;
        }
    }
    return NULL;
found:
    if (fn_8000F470()[3] & 1) {
        buf += fn_8001CD54(GActor_Find48(a)->x48) & ~3;
    }
    return buf;
}

u8* fn_80008060(GActor* a) {
    for (; a != NULL; a = a->parent) {
        if (a->x6C != NULL) {
            return a->x6C;
        }
    }
    return NULL;
}

u8* fn_8000808C(GActor* a) {
    for (; a != NULL; a = a->parent) {
        if (a->x70 != NULL) {
            return a->x70;
        }
    }
    return NULL;
}

Mtx30* fn_800080B8(GActor* a) {
    for (; a != NULL; a = a->parent) {
        if (a->x60 != NULL) {
            return a->x60;
        }
    }
    return NULL;
}

void* fn_800080E4(GActor* a) {
    for (; a != NULL; a = a->parent) {
        if (a->x64 != NULL) {
            return a->x64;
        }
    }
    return NULL;
}


f32 fn_800081B4(GActor* a) {
    return a->x58;
}

f32 fn_800081BC(GActor* a) {
    return a->x78;
}

/* GActor_SetMtx */
void fn_800081C4(GActor* a, Mtx m) {
    fn_80312344(m, a->x10);
}

/* GActor_SetFrame */
void fn_8000866C(GActor* a, f32 frame) {
    GRes44* anim = GActor_Find44(a);
    GKeySet* ks;
    if (anim != NULL) {
        a->flags &= ~2;
        if (frame < 0.0f || frame > anim->end) {
            frame = anim->end;
            a->flags |= 2;
        }
        if (frame < anim->start) {
            frame = anim->start;
        }
        a->keys[0].id = 0xFFFF;
        a->keys[0].val = 0;
        a->keys[1].id = 0xFFFF;
        a->keys[1].val = 0;
        a->keys[2].id = 0xFFFF;
        a->keys[2].val = 0;
        a->keys[3].id = 0xFFFF;
        a->keys[3].val = 0;
        ks = fn_80009CD0(anim, frame);
        if (ks != NULL) {
            s32 i;
            for (i = 0; i < ks->count; i++) {
                a->keys[i].id = ks->keys[i].id;
                a->keys[i].val = ks->keys[i].val;
            }
        }
        a->x58 = frame;
        fn_80017DA8(a, frame);
    }
}

/* GActor_SetFrameById */
BOOL fn_800087FC(GActor* a, u32 id) {
    s32 idx;
    if (id == 0xFFFF) {
        return 0;
    }
    idx = fn_80009FD0(GActor_Find44(a), -1, id);
    if (idx < 0) {
        return 0;
    }
    fn_8000866C(a, idx);
    return 1;
}

/* GActor_SetScale */
void fn_800088A0(GActor* a, f32 scale) {
    if (a == NULL) {
        return;
    }
    a->scale = scale;
}

/* GActor_PushAnim: keeps up to 4 blended animation layers in the child chain */
void fn_800088B0(GActor* a, GRes44* anim) {
    s32 n;
    GActor* c;
    GActor* prev;
    GActor* last;
    if (a == NULL) {
        fn_8001E008(lbl_80360AAC, 0x3D6, lbl_80360AAC + 0x42);
    }
    n = 1;
    for (c = a; (c = c->child) != NULL;) {
        n++;
    }
    if (n == 4) {
        prev = a;
        last = a;
        while (last->child != NULL) {
            prev = last;
            last = last->child;
        }
        if (prev != last) {
            fn_80006EE0(last);
            prev->child = NULL;
        }
    }
    c = fn_80006E1C();
    {
        GActor* tmp = a->child;
        a->child = c;
        c->child = tmp;
    }
    c->x58 = a->x58;
    c->scale = a->scale;
    c->x78 = a->x78;
    c->x44 = a->x44;
    c->parent = a;
    c->flags = (c->flags | (a->flags & 0x34)) & ~2;
    fn_80312344(a->x10, c->x10);
    a->x78 = 0.0f;
    a->scale = 1.0f;
    a->x44 = anim;
    fn_8000866C(a, 0.0f);
}

/* GActor_DeleteChain. Self-recursion is inlined exactly 3 levels deep in the
 * original; inline_depth(3) reproduces that. */
#pragma push
#pragma inline_depth(3)
void fn_80008A38(GActor* a) {
    if (a != NULL) {
        if (a->child != NULL) {
            fn_80008A38(a->child);
            a->child = NULL;
        }
        fn_80007374(a);
        if (a->flags & 1) {
            fn_80078E24(a);
        }
    }
}
#pragma pop

/* GActor_HasKey */
BOOL fn_80008C98(GActor* a, u16 id) {
    GKey* k = a->keys;
    s32 i;
    for (i = 0; i < 4; i++, k++) {
        if (k->id == id) {
            return 1;
        }
    }
    return 0;
}

/* GActor_GetKeyValue */
s32 fn_80008CF0(GActor* a, u16 id) {
    GKey* k = a->keys;
    s32 i;
    for (i = 0; i < 4; i++, k++) {
        if (k->id == id) {
            return k->val;
        }
    }
    return -1;
}

/* GActor_FindKeyInList */
u16 fn_80008D48(GActor* a, const u16* list) {
    s32 i;
    for (i = 0; i < 4; i++) {
        u16 id = a->keys[i].id;
        if (id != 0xFFFF) {
            const u16* p;
            for (p = list; *p != 0xFFFF; p++) {
                if (*p == id) {
                    return id;
                }
            }
        }
    }
    return 0xFFFF;
}

s32 fn_80008E28(GActor* a, u32 id) {
    return fn_80009FD0(GActor_Find44(a), -1, id);
}

s32 fn_80008E5C(GActor* a, s32 x, s32 y) {
    return fn_80009EF8(GActor_Find44(a), x, y);
}

s32 fn_80008E88(GActor* a, s32 x, u32 id) {
    return fn_80009FD0(GActor_Find44(a), x, id);
}

/* GActor_HasAnyKey */
BOOL fn_80008EB4(GActor* a) {
    s32 i;
    for (i = 0; i < 4; i++) {
        if (a->keys[i].id != 0xFFFF) {
            return 1;
        }
    }
    return 0;
}

/* GActor_SetColor */
void fn_80008F10(GActor* a, s32 r, s32 g, s32 b) {
    a->color.r = r;
    a->color.g = g;
    a->color.b = b;
}

/* GActor_SetAlpha */
void fn_80008F20(GActor* a, u8 alpha) {
    a->color.a = alpha;
    if (alpha != 0xFF) {
        a->flags |= 0x100;
    } else {
        a->flags &= ~0x100;
    }
}

void fn_80008F4C(GActor* a, GActor* parent) {
    a->parent = parent;
}

void fn_80008F54(GActor* a, u8 v) {
    a->x82 = v;
}

void fn_80008F5C(GActor* a, s8 v) {
    a->x81 = v;
}

void fn_80008F64(GActor* a, u8 v) {
    a->x80 = v;
}

/* GActor_SetAnimRes */
void fn_80008F6C(GActor* a, void* src) {
    GRes44* old = a->x44;
    GRes44* anim = fn_8000BDB0(src, 0);
    if (anim != a->x44) {
        a->x44 = anim;
        if (a->scale < 0.0f) {
            fn_8000866C(a, anim->end);
        } else {
            fn_8000866C(a, anim->start);
        }
    }
    if (old != NULL) {
        fn_8000BE20(old);
    }
}

void fn_80009030(GActor* a, void* src) {
    GRes48* old = a->x48;
    GRes48* r = fn_80017FD0(src, 0);
    if (r != a->x48) {
        a->x48 = r;
    }
    if (old != NULL) {
        fn_80018094(old);
    }
}

void fn_80009090(GActor* a, void* src) {
    GModel* old = a->model;
    GModel* r = fn_8000EBCC(src, 0);
    if (r != a->model) {
        a->model = r;
    }
    if (old != NULL) {
        fn_8000EC2C(old);
    }
}

void fn_800090F0(GActor* a, void* src) {
    void* old = a->x4C;
    void* r = fn_8001D3EC(src, 0);
    if (r != a->x4C) {
        a->x4C = r;
    }
    if (old != NULL) {
        fn_8001D424(old);
    }
}

void fn_80009150(GActor* a, void* src, u32 x) {
    GRes44* old = a->x44;
    GRes44* anim = fn_8000BDB0(src, x);
    if (anim != a->x44) {
        a->x44 = anim;
        if (a->scale < 0.0f) {
            fn_8000866C(a, anim->end);
        } else {
            fn_8000866C(a, anim->start);
        }
    }
    if (old != NULL) {
        fn_8000BE20(old);
    }
}

void fn_80009214(GActor* a, void* src, u32 x) {
    GRes48* old = a->x48;
    GRes48* r = fn_80017FD0(src, x);
    if (r != a->x48) {
        a->x48 = r;
    }
    if (old != NULL) {
        fn_80018094(old);
    }
}

void fn_80009274(GActor* a, void* src, u32 x) {
    GModel* old = a->model;
    GModel* r = fn_8000EBCC(src, x);
    if (r != a->model) {
        a->model = r;
    }
    if (old != NULL) {
        fn_8000EC2C(old);
    }
}

void fn_800092D4(GActor* a, void* src, u32 x) {
    void* old = a->x4C;
    void* r = fn_8001D3EC(src, x);
    if (r != a->x4C) {
        a->x4C = r;
    }
    if (old != NULL) {
        fn_8001D424(old);
    }
}

/* GActor_CopyPose */
void fn_80009334(GActor* src, GActor* dst) {
    GModel* model;
    s32 i;
    if (src == NULL || dst == NULL) {
        return;
    }
    model = GActor_FindModel(src);
    for (i = 0; i < model->nodeCount; i++) {
        fn_80312344(&src->x60[i], &dst->x60[i]);
    }
    if (src->x64 != NULL && dst->x64 != NULL) {
        for (i = 0; i < model->nodeCount; i++) {
            fn_80312344(&((Mtx30*)src->x64)[i], &((Mtx30*)dst->x64)[i]);
        }
        fn_8001CD78(dst);
    }
    fn_80312344(src->x10, dst->x10);
    if (src->x54 != 0) {
        fn_800161E0(src, dst);
    }
    dst->x58 = src->x58;
}


#pragma use_lmw_stmw on
/* GActor_ResetTrail */
void fn_800096E4(GActor* a, s32 n) {
    if (a != NULL) {
        GActor_FreeChildren(a);
        fn_80009454(a, n, 0);
    }
}

/* GActor_ResetTrailMode1 */
void fn_800097B0(GActor* a, s32 n) {
    if (a != NULL) {
        GActor_FreeChildren(a);
        fn_80009454(a, n, 1);
    }
}
#pragma use_lmw_stmw off

/* GActor_SetTrailColor */
void fn_8000987C(GActor* a, const GColor* c) {
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
void fn_80009974(GActor* a) {
    s32 i;
    if (a == NULL || a->children == NULL) {
        return;
    }
    for (i = 0; i < a->children->count; i++) {
        fn_80006EE0(a->children->items[i]);
        a->children->items[i] = NULL;
    }
    fn_80078E24(a->children->items);
    a->children->items = NULL;
    fn_80078E24(a->children);
    a->children = NULL;
}
#pragma use_lmw_stmw off


/* GActor_FindNodeByName2 */
s32 fn_80009BC8(GActor* a, const char* name) {
    s32 n;
    GModel* model = GActor_FindModel(a);
    GNode* node = model->nodes;
    s32 i;
    if (name != NULL) {
        n = model->nodeCount;
        for (i = 0; i < n; i++, node++) {
            if (node->name != NULL && fn_80291188(node->name, name) == 0) {
                return i;
            }
        }
    }
    return -1;
}

/* GActor_SetEntryFlags */
void fn_80009C7C(GActor* a, u16 mask) {
    GRes48* r = GActor_Find48(a);
    GEntry20* e = r->entries;
    s32 i;
    for (i = 0; i < r->entryCount; i++, e++) {
        e->flags |= mask;
    }
}
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
GEntry20* fn_80008110(GActor* a, const char* name) {

    u16 n;
    GRes48* r;
    s32 i;
    GEntry20* e;

    fd(a, &r);
    if (name != NULL) {
        n = r->entryCount;
        for (i = 0; i < n; i++) {
            e = &r->entries[i];
            if (e->name != NULL && fn_80291480(e->name, name)) {
                return e;
            }
        }
    }
    return NULL;
}
#pragma use_lmw_stmw off
