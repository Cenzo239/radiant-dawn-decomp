#include "game/rA_800068A0/types.h"

extern "C" {

/* GCamera.c: camera / viewport object (0x150 bytes); lbl_804CB080 is the
 * current camera, used when a NULL camera is passed. */

typedef f32 Mtx[3][4];
typedef f32 Mtx44[4][4];
typedef struct Vec { f32 x, y, z; } Vec;

/* Display entry registered with GCameraDispAlloc. */
typedef struct GDisp {
    struct GDisp* next; /* 0x0 */
    u8 prio;            /* 0x4 */
    u8 x5[3];
    void* func;         /* 0x8 */
    void* arg;          /* 0xC */
} GDisp;

typedef struct GCamera {
    u16 flags;          /* 0x000: bit0 = custom projection, bit2 = 4:3 aspect fix */
    u8 x2;
    u8 x3;
    f32 vpX;            /* 0x004 */
    f32 vpY;
    f32 vpW;
    f32 vpH;
    f32 vpNear;         /* 0x014 */
    f32 vpFar;          /* 0x018 */
    u16 scX;            /* 0x01C */
    u16 scY;
    u16 scW;
    u16 scH;
    Mtx44 proj;         /* 0x024 */
    Mtx44 viewProj;     /* 0x064 */
    Mtx view;           /* 0x0A4 */
    Vec pos;            /* 0x0D4 */
    Vec at;             /* 0x0E0 */
    Vec up;             /* 0x0EC */
    Vec offset;         /* 0x0F8 */
    f32 x104;
    f32 x108;
    f32 x10C;
    f32 x110;
    u8 x114[0x120 - 0x114];
    struct GDisp* disps;    /* 0x120: pool of display entries */
    u16 nDisps;         /* 0x124 */
    u16 maxDisps;       /* 0x126 */
    struct GDisp* lists[6]; /* 0x128: per-layer lists, sorted by prio */
    f32 near;           /* 0x140 */
    f32 far;            /* 0x144 */
    f32 aspect;         /* 0x148 */
    f32 fovy;           /* 0x14C */
} GCamera;

extern GCamera* lbl_804CB080;
extern char lbl_80360BEC[]; /* "" then "GCamera.c" */
extern void* fn_80078CCC(u32 size, const char* name, u32 flags);
extern void fn_80312344(Mtx src, Mtx dst);                              /* PSMTXCopy */
extern void fn_80312E5C(Mtx44 m, f32 fovy, f32 aspect, f32 n, f32 f);   /* C_MTXPerspective */
extern void fn_80312FE0(Mtx44 src, Mtx44 dst);                          /* PSMTX44Copy */
extern void fn_80313024(Mtx44 a, Mtx44 b, Mtx44 ab);                    /* PSMTX44Concat */
extern void fn_80313460(const Vec* a, const Vec* b, Vec* ab);          /* PSVECAdd */
extern void fn_80312AC0(Mtx m, const Vec* eye, const Vec* up, const Vec* at); /* C_MTXLookAt */

static inline void GCamera_UpdateProjection(GCamera* c, Mtx44 proj, BOOL custom) {
    f32 aspect;
    f32 fovy;
    if (c == NULL) {
        c = lbl_804CB080;
    }
    if (custom) {
        c->flags |= 1;
    } else {
        c->flags &= ~1;
    }
    if (proj == NULL) {
        aspect = c->aspect;
        fovy = c->fovy;
        if (c->flags & 4) {
            aspect *= 1.3333333f;
        }
        fn_80312E5C(c->proj, fovy, aspect, c->near, c->far);
    } else {
        fn_80312FE0(proj, c->proj);
    }
}

static inline void GCamera_SetScissor(GCamera* c, u16 x, u16 y, u16 w, u16 h) {
    if (c == NULL) {
        c = lbl_804CB080;
    }
    c->scX = x;
    c->scY = y;
    c->scW = w;
    c->scH = h;
}

static inline void GCamera_SetViewport(GCamera* c, f32 x, f32 y, f32 w, f32 h) {
    if (c == NULL) {
        c = lbl_804CB080;
    }
    c->vpX = x;
    c->vpY = y;
    c->vpW = w;
    c->vpH = h;
    c->vpNear = 0.0f;
    c->vpFar = 1.0f;
}

static inline void GCamera_SetNearFar(GCamera* c, f32 n, f32 f) {
    if (c == NULL) {
        c = lbl_804CB080;
    }
    c->near = n;
    c->far = f;
}

static inline void GCamera_UpdateViewProj(GCamera* c) {
    Mtx44 m;
    if (c == NULL) {
        c = lbl_804CB080;
    }
    fn_80312344(c->view, (f32(*)[4])m);
    m[3][0] = 0.0f;
    m[3][1] = 0.0f;
    m[3][2] = 0.0f;
    m[3][3] = 1.0f;
    fn_80313024(c->proj, m, c->viewProj);
}

static inline void GCamera_UpdateView(GCamera* c) {
    if (c == NULL) {
        c = lbl_804CB080;
    }
    Vec eye = c->pos;
    Vec at = c->at;
    Vec up = c->up;
    fn_80313460(&c->offset, &eye, &eye);
    fn_80313460(&c->offset, &at, &at);
    fn_80312AC0(c->view, &eye, &up, &at);
    GCamera_UpdateViewProj(c);
}

/* GCamera_Init */
void fn_8000F48C(GCamera* c) {
    if (c == NULL) {
        c = lbl_804CB080;
    }
    GCamera_SetScissor(c, 0, 0, 608, 448);
    GCamera_SetViewport(c, 0.0f, 0.0f, 608.0f, 448.0f);
    GCamera_SetNearFar(c, 2.0f, 2000.0f);
    c->flags = 2;
    c->x3 = 0;
    Vec eye = {0.0f, 0.0f, 5.0f};
    c->pos = eye;
    Vec at = {0.0f, 0.0f, 0.0f};
    c->at = at;
    Vec up = {0.0f, 1.0f, 0.0f};
    c->up = up;
    Vec ofs = {0.0f, 0.0f, 0.0f};
    c->offset = ofs;
    c->x104 = 80.0f;
    c->x108 = 0.0f;
    c->x10C = 0.0f;
    c->x110 = 0.0f;
    c->fovy = 30.0f;
    c->aspect = c->vpW / c->vpH;
    GCamera_UpdateView(c);
    GCamera_UpdateProjection(c, NULL, TRUE);
}

static inline void GCamera_ClearDisps(GCamera* c) {
    if (c == NULL) {
        c = lbl_804CB080;
    }
    if (c != NULL) {
        c->nDisps = 0;
        c->lists[0] = 0;
        c->lists[1] = 0;
        c->lists[2] = 0;
        c->lists[3] = 0;
        c->lists[4] = 0;
        c->lists[5] = 0;
    }
}

/* GCamera_Create: allocates a camera with room for maxDisps display entries and makes
 * it current. */
GCamera* fn_8000F748(s32 maxDisps) {
    GCamera* c = (GCamera*)fn_80078CCC(0x150, lbl_80360BEC, 0);
    lbl_804CB080 = c;
    fn_8000F48C(c);
    c->disps = (GDisp*)fn_80078CCC(maxDisps << 4, lbl_80360BEC, 0);
    c->maxDisps = maxDisps;
    GCamera_ClearDisps(c);
    return c;
}


/* GCamera_Copy */
void fn_8000F7F4(GCamera* src, GCamera* dst) {
    dst->flags = src->flags;
    dst->x2 = src->x2;
    dst->x3 = src->x3;
    dst->vpX = src->vpX;
    dst->vpY = src->vpY;
    dst->vpW = src->vpW;
    dst->vpH = src->vpH;
    dst->vpNear = src->vpNear;
    dst->vpFar = src->vpFar;
    dst->scX = src->scX;
    dst->scY = src->scY;
    dst->scW = src->scW;
    dst->scH = src->scH;
    dst->pos.x = src->pos.x;
    dst->pos.y = src->pos.y;
    dst->pos.z = src->pos.z;
    dst->at.x = src->at.x;
    dst->at.y = src->at.y;
    dst->at.z = src->at.z;
    dst->up.x = src->up.x;
    dst->up.y = src->up.y;
    dst->up.z = src->up.z;
    dst->offset.x = src->offset.x;
    dst->offset.y = src->offset.y;
    dst->offset.z = src->offset.z;
    dst->x104 = src->x104;
    dst->x108 = src->x108;
    dst->x10C = src->x10C;
    dst->x110 = src->x110;
    dst->near = src->near;
    dst->far = src->far;
    dst->aspect = src->aspect;
    dst->fovy = src->fovy;
    fn_80312344(src->view, dst->view);
    fn_80312FE0(src->proj, dst->proj);
    fn_80312FE0(src->viewProj, dst->viewProj);
}

/* GCamera_UpdateProjection */
void fn_8000F954(GCamera* c, Mtx44 proj, BOOL custom) {
    GCamera_UpdateProjection(c, proj, custom);
}

/* GCamera_SetScissor */
void fn_8000F9C8(GCamera* c, u16 x, u16 y, u16 w, u16 h) {
    GCamera_SetScissor(c, x, y, w, h);
}

/* GCamera_SetViewport */
void fn_8000F9E8(GCamera* c, f32 x, f32 y, f32 w, f32 h) {
    GCamera_SetViewport(c, x, y, w, h);
}

/* GCamera_SetNearFar */
void fn_8000FA18(GCamera* c, f32 n, f32 f) {
    GCamera_SetNearFar(c, n, f);
}

/* GCamera_UpdateViewProj */
void fn_8000FA30(GCamera* c) {
    GCamera_UpdateViewProj(c);
}


/* GCamera_UpdateView */
void fn_8000FA98(GCamera* c) {
    if (c == NULL) {
        c = lbl_804CB080;
    }
    Vec eye = c->pos;
    Vec at = c->at;
    Vec up = c->up;
    fn_80313460(&c->offset, &eye, &eye);
    fn_80313460(&c->offset, &at, &at);
    fn_80312AC0(c->view, &eye, &up, &at);
    fn_8000FA30(c);
}

/* GCamera_GetViewMtx */
Mtx* fn_8000FB88(void) {
    return &lbl_804CB080->view;
}

/* GCamera_GetViewProjMtx */
Mtx44* fn_8000FB94(void) {
    return &lbl_804CB080->viewProj;
}

extern double fn_80295A18(double x);                                    /* tan */
extern void fn_80313484(const Vec* a, const Vec* b, Vec* ab);          /* PSVECSubtract */
extern void fn_803134A8(const Vec* src, Vec* dst, f32 scale);          /* PSVECScale */
extern void fn_803134C4(const Vec* src, Vec* dst);                     /* PSVECNormalize */
extern void fn_8031292C(Mtx m, f32 x, f32 y, f32 z);                   /* PSMTXScale */
extern void fn_803128AC(Mtx m, f32 x, f32 y, f32 z);                   /* PSMTXTrans */
extern void fn_80312444(Mtx src, Mtx dst);                             /* PSMTXInverse? */
extern void fn_80312378(Mtx a, Mtx b, Mtx ab);                         /* PSMTXConcat */

/* GCamera_GetNearPlaneMtx: matrix mapping a unit quad onto the near plane. */
Mtx* fn_8000FBA0(GCamera* c, Mtx out) {
    Mtx tmp;
    Mtx scale;
    Mtx inv;
    Mtx trans;
    Vec eye;
    Vec at;
    Vec dir;
    f32 dist;
    f32 aspect;
    f32 h;
    f32 sx;
    f32 sy;
    if (c == NULL) {
        c = lbl_804CB080;
    }
    dist = 1.1f * c->near;
    aspect = c->aspect;
    h = dist * (f32)fn_80295A18(0.017453292f * (c->fovy / 2.0f));
    if (c->flags & 4) {
        aspect *= 1.3333333f;
    }
    sx = 0.5f * (h * aspect);
    sy = 0.6666667f * h;
    fn_80313460(&c->pos, &c->offset, &eye);
    fn_80313460(&c->at, &c->offset, &at);
    fn_80313484(&at, &eye, &dir);
    fn_803134C4(&dir, &dir);
    fn_803134A8(&dir, &dir, dist);
    fn_80313460(&eye, &dir, &dir);
    fn_8031292C(scale, sx, sy, 1.0f);
    fn_803128AC(trans, dir.x, dir.y, dir.z);
    fn_80312444(lbl_804CB080->view, inv);
    fn_80312378(inv, scale, tmp);
    fn_80312378(trans, tmp, out);
    return (Mtx*)out;
}

extern void fn_80312C34(Mtx m, f32 fovy, f32 aspect, f32 scaleS, f32 scaleT, f32 transS, f32 transT); /* C_MTXLightPerspective */
extern void fn_80312D2C(Mtx m, f32 t, f32 b, f32 l, f32 r, f32 scaleS, f32 scaleT, f32 transS, f32 transT); /* C_MTXLightOrtho */

/* GCamera_GetTexProjMtx: projection matrix for projected textures. */
Mtx* fn_8000FEA0(GCamera* c, Mtx out) {
    Mtx m;
    f32 aspect;
    f32 fovy;
    if (c == NULL) {
        c = lbl_804CB080;
    }
    aspect = c->aspect;
    fovy = c->fovy;
    if (c->flags & 4) {
        aspect *= 1.3333333f;
    }
    if (c->flags & 1) {
        fn_80312C34(m, fovy, aspect, 0.5f, -0.5f, 0.5f, 0.5f);
        fn_80312378(m, c->view, out);
    } else {
        fn_80312D2C(m, c->vpY + c->vpH, c->vpY, c->vpX, c->vpX + c->vpW, 0.5f, 0.5f, 0.5f, 0.5f);
        fn_80312378(m, c->view, out);
    }
    return (Mtx*)out;
}

extern s8 lbl_804CB084; /* 0 none, 1 = 3D, 2 = 2D */
extern u8 lbl_804CB085;
extern void fn_80312318(Mtx m);                                         /* PSMTXIdentity */
extern void fn_80312F48(Mtx44 m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f); /* C_MTXOrtho */
extern void fn_80307E48(Mtx m, u32 id);                                 /* GXLoadPosMtxImm */
extern void fn_80021784(u32 id);
extern void fn_803080DC(u32 x, u32 y, u32 w, u32 h);                    /* GXSetScissor */
extern void fn_80308090(f32 x, f32 y, f32 w, f32 h, f32 n, f32 f);      /* GXSetViewport */
extern void fn_80307D98(Mtx44 m, u32 type);                             /* GXSetProjection */
extern void fn_800109B8(void);

static inline void GCamera_SetGX(GCamera* c) {
    if (c == NULL) {
        c = lbl_804CB080;
    }
    if (c != NULL) {
        fn_803080DC(c->scX, c->scY, c->scW, c->scH);
        fn_80308090(c->vpX, c->vpY, c->vpW, c->vpH, c->vpNear, c->vpFar);
        fn_80307D98(c->proj, (c->flags & 1) ^ 1);
    }
}

#pragma auto_inline off
/* GCamera_Begin2D */
void fn_8000FF74(GCamera* c) {
    Mtx44 m;
    Mtx id;
    if (c == NULL) {
        c = lbl_804CB080;
    }
    if (c != NULL) {
        lbl_804CB084 = (c->flags & 1) ? 1 : 2;
        fn_80312F48(m, 0.0f, c->vpH, 0.0f, c->vpW, 0.0f, -1000.0f);
        fn_8000F954(c, m, FALSE);
        fn_80312318(id);
        fn_80307E48(id, 0);
        fn_80021784(0);
        fn_80312318(c->view);
        GCamera_SetGX(c);
        lbl_804CB085 = 0;
        fn_800109B8();
    }
}

/* GCamera_Begin3D */
void fn_800100C8(GCamera* c) {
    Mtx id;
    if (c == NULL) {
        c = lbl_804CB080;
    }
    if (c != NULL) {
        lbl_804CB084 = (c->flags & 1) ? 1 : 2;
        fn_8000F954(c, NULL, TRUE);
        fn_80312318(id);
        fn_80307E48(id, 0);
        fn_80021784(0);
        GCamera_SetGX(c);
        fn_8000FA98(c);
        lbl_804CB085 = 1;
        fn_800109B8();
    }
}
#pragma auto_inline reset

/* GCamera_BeginOrtho: centred orthographic projection of size w x h. */
void fn_800102AC(GCamera* c, f32 w, f32 h) {
    Mtx44 m;
    Mtx id;
    if (c == NULL) {
        c = lbl_804CB080;
    }
    if (c != NULL) {
        lbl_804CB084 = (c->flags & 1) ? 1 : 2;
        fn_80312F48(m, h / 2.0f, -h / 2.0f, -w / 2.0f, w / 2.0f, c->near, c->far);
        fn_8000F954(c, m, FALSE);
        fn_80312318(id);
        fn_80307E48(id, 0);
        fn_80021784(0);
        GCamera_SetGX(c);
        fn_8000FA98(c);
        lbl_804CB085 = 1;
        fn_800109B8();
    }
}

/* GCamera_End: back to the full-screen viewport, then redo the last Begin. */
void fn_800104DC(GCamera* c) {
    GCamera_SetViewport(c, 0.0f, 0.0f, 608.0f, 448.0f);
    GCamera_SetScissor(c, 0, 0, 608, 448);
    if (lbl_804CB084) {
        if (c == NULL) {
            c = lbl_804CB080;
        }
        if (c != NULL) {
            switch (lbl_804CB084) {
            case 1:
                fn_800100C8(c);
                break;
            case 2:
                fn_8000FF74(c);
                break;
            }
            lbl_804CB084 = 0;
        }
    }
}

extern void fn_800105AC(GCamera* c); /* GCamera_SortDisps, see wip/ */
extern void fn_8001E008(const char* file, int line, const char* msg);

static inline GDisp* GCamera_DispAlloc(int layer) {
    GCamera* c = lbl_804CB080;
    GDisp* d;
    GCamera* cl = (GCamera*)((u8*)c + layer * 4);
    d = &c->disps[c->nDisps++];
    if (c->nDisps > c->maxDisps) {
        fn_8001E008(lbl_80360BEC + 1, 0x212, lbl_80360BEC + 0xB);
    }
    d->next = NULL;
    if (cl->lists[0] == NULL) {
        cl->lists[0] = d;
    } else {
        GDisp* p;
        for (p = cl->lists[0]; p->next != NULL; p = p->next) {
        }
        p->next = d;
    }
    return d;
}

/* GCameraDispAlloc(layer, func, arg) with the default prio 0x80 */
void fn_800106AC(int layer, void* func, void* arg) {
    GDisp* d = GCamera_DispAlloc(layer);
    d->next = NULL;
    d->prio = 0x80;
    d->func = func;
    d->arg = arg;
}

#pragma use_lmw_stmw on
/* GCameraDispAlloc(layer, prio, func, arg) */
void fn_80010788(int layer, u8 prio, void* func, void* arg) {
    GDisp* d = GCamera_DispAlloc(layer);
    d->next = NULL;
    d->prio = prio;
    d->func = func;
    d->arg = arg;
}
#pragma use_lmw_stmw reset

extern void fn_80012268(void);
extern void fn_800122F0(void);
extern void fn_800119BC(GCamera* c);

/* GCamera_Draw */
void fn_8001084C(GCamera* c) {
    if (c == NULL) {
        c = lbl_804CB080;
    }
    if (c != NULL) {
        fn_80012268();
        fn_800122F0();
        lbl_804CB080 = c;
        fn_800105AC(c);
        GCamera_SetGX(c);
        fn_800119BC(c);
        GCamera_ClearDisps(c);
    }
}

/* GCamera_IncFrame */
void fn_8001093C(GCamera* c) {
    if (c == NULL) {
        c = lbl_804CB080;
    }
    if (c != NULL) {
        c->x3++;
    }
}

extern void* lbl_804CA04C;
extern u8 lbl_803B6700[0x10];

void* fn_80010960(void) {
    return lbl_804CA04C;
}

void fn_80010968(void* p) {
    if (p == NULL) {
        p = lbl_803B6700;
    }
    lbl_804CA04C = p;
}

void fn_80010980(void) {
    u8 save = lbl_804CB085;
    lbl_804CB085 = 0;
    fn_800109B8();
    lbl_804CB085 = save;
}

/* GFog (lbl_804CA04C points at the current one) */
typedef struct GXColor {
    u8 r, g, b, a;
} GXColor;

typedef struct GFog {
    u8 type;            /* 0 = off, 1..5 index into lbl_80378768 */
    u8 r, g, b;
    f32 start;
    f32 end;
} GFog;

typedef struct GXFogAdjTable {
    u16 r[10];
} GXFogAdjTable;

extern u8 lbl_804CB086;
extern u32 lbl_80378768[6]; /* GXFogType per fog type */
extern void fn_80307298(u32 type, f32 startz, f32 endz, f32 nearz, f32 farz, GXColor color); /* GXSetFog */
extern void fn_80307624(u32 enable, u16 center, GXFogAdjTable* table);   /* GXSetFogRangeAdj */
extern void fn_803074C4(GXFogAdjTable* table, u16 width, Mtx44 proj);    /* GXInitFogAdjTable */

/* GFog_Apply */
void fn_800109B8(void) {
    GFog* f = (GFog*)lbl_804CA04C;
    int type = f->type;
    if (!lbl_804CB085) {
        type = 0;
    }
    if (lbl_804CB086 != type) {
        lbl_804CB086 = type;
        if (type == 0) {
            GXColor c = {0, 0, 0, 0};
            fn_80307298(0, 10.0f, 30.0f, 1.0f, 500.0f, c);
            fn_80307624(0, 0, NULL);
        } else {
            GXFogAdjTable table;
            GXColor c = {f->r, f->g, f->b, 0xFF};
            GCamera* cam = lbl_804CB080;
            fn_80307298(lbl_80378768[type], f->start, f->end, cam->near, cam->far, c);
            fn_803074C4(&table, 0x260, cam->proj);
            fn_80307624(1, 0x130, &table);
        }
    }
}

/* GFog_Reset */
void fn_80010AB8(void) {
    GFog* f = (GFog*)lbl_804CA04C;
    f->type = 0;
    f->r = 0xFF;
    f->g = 0xFF;
    f->b = 0xFF;
    f->start = 0.0f;
    f->end = 0.0f;
}

extern void fn_80021754(GXColor c);

static inline GXColor GFog_Color(GFog* f) {
    GXColor c = {0, 0, 0, 0};
    c.r = f->r;
    c.g = f->g;
    c.b = f->b;
    return c;
}

/* GFog_SetClearColor */
void fn_80010AE4(void) {
    GFog* f = (GFog*)lbl_804CA04C;
    if (f->type == 0) {
        GXColor c0 = {0, 0, 0, 0};
        fn_80021754(c0);
    } else {
        fn_80021754(GFog_Color(f));
    }
}

/* GFog_GetColor (returned as a packed u32) */
u32 fn_80010B54(GFog* f) {
    GXColor c = {0, 0, 0, 0};
    if (f != NULL) {
        c.r = f->r;
        c.g = f->g;
        c.b = f->b;
    }
    return *(u32*)&c;
}

/* GFog_SetColor */
void fn_80010B8C(GFog* f, GXColor c) {
    if (f != NULL) {
        f->r = c.r;
        f->g = c.g;
        f->b = c.b;
    }
}

typedef struct GLight {
    u8 id;              /* 0x00 */
    u8 type;            /* 0x01: 0 = free */
    u8 x2;
    s8 link;            /* 0x03: id of the light this one was allocated for */
    GXColor color;      /* 0x04 */
    Vec pos;            /* 0x08 */
    Vec dir;            /* 0x14 */
    f32 x20;            /* 0x20 */
} GLight;

typedef struct GLightSetBody {
    GLight lights[8];
} GLightSetBody;

typedef struct GLightSet {
    u8 x0;
    u8 x1;
    GXColor ambient;    /* 0x02 */
    u8 x6[2];
    GLightSetBody body; /* 0x08 */
} GLightSet;

extern GLightSet* lbl_804CA050;
extern GLightSet lbl_803B6710[8];

/* GLightSet_Get: i < 0 means the current set */
GLightSet* fn_80010BB0(int i) {
    if (i < 0) {
        return lbl_804CA050;
    }
    if (i > 8) {
        fn_8001E008(lbl_80360BEC + 1, 0x362, lbl_80360BEC + 0xC0);
    }
    return &lbl_803B6710[i];
}

GLightSet* fn_80010C18(void) {
    return lbl_804CA050;
}

void fn_80010C20(GLightSet* s) {
    if (s == NULL) {
        s = lbl_803B6710;
    }
    lbl_804CA050 = s;
}

/* GLightSet_Copy */
void fn_80010C38(GLightSet* src, GLightSet* dst) {
    if (src == NULL || dst == NULL) {
        return;
    }
    dst->x0 = src->x0;
    dst->x1 = src->x1;
    dst->ambient.r = src->ambient.r;
    dst->ambient.g = src->ambient.g;
    dst->ambient.b = src->ambient.b;
    dst->ambient.a = src->ambient.a;
    dst->body = src->body;
}

extern Vec lbl_80360BC8; /* {0, 0, 0}, in .rodata; read as non-const so the loop reloads it */

static inline void GLight_Clear(GLight* l) {
    l->type = 0;
    l->x2 = 0;
    GXColor c = {0, 0, 0, 0};
    l->color = c;
    Vec p = lbl_80360BC8;
    l->pos = p;
    Vec d = {0.0f, 0.0f, 0.0f};
    l->dir = d;
    l->x20 = 1.0f;
    l->link = -1;
}

/* GLightSet_Init */
void fn_80010CA4(GLightSet* s) {
    GLight* l;
    int i;
    if (s == NULL) {
        s = lbl_804CA050;
    }
    GXColor amb = {0, 0, 0, 0};
    s->ambient = amb;
    s->x0 = 0;
    s->x1 = 0;
    l = s->body.lights;
    for (i = 0; i < 8; i++) {
        GLight_Clear(l);
        l->id = i;
        l++;
    }
}

/* GLightSet_FindType */
GLight* fn_80010DA4(GLightSet* s, int type) {
    int i;
    GLight* l;
    if (s == NULL) {
        s = lbl_804CA050;
    }
    l = s->body.lights;
    for (i = 0; i < 8; i++) {
        if (l->type == type) {
            return l;
        }
        l++;
    }
    return NULL;
}

/* GLightSet_Free: also frees the lights allocated for this one */
void fn_80010F94(GLightSet* s, GLight* l) {
    GLight* o;
    int i;
    if (s == NULL) {
        s = lbl_804CA050;
    }
    if (l == NULL) {
        return;
    }
    o = s->body.lights;
    for (i = 0; i < 8; i++) {
        if (o->type != 0 && o->link == l->id) {
            fn_80010F94(s, o);
        }
        o++;
    }
    s->x0 &= ~(1 << l->id);
    s->x1 &= ~(1 << l->id);
    GLight_Clear(l);
}

extern void fn_80312654(Mtx m, char axis, f32 rad);                         /* PSMTXRotRad */
extern void fn_80312A50(Mtx m, const Vec* p, const Vec* n);                 /* C_MTXReflect */
extern void fn_80312DB4(Mtx m, const Vec* src, Vec* dst);                   /* PSMTXMultVec */

/* GLightSet_Transform: rebuilds every light position from its rotation */
void fn_800110F4(GLightSet* s, Mtx m) {
    GLight* l;
    int i;
    Mtx rx;
    Mtx ry;
    Mtx rz;
    Mtx r;
    Mtx refl;
    if (s == NULL) {
        s = lbl_804CA050;
    }
    l = s->body.lights;
    for (i = 0; i < 8; i++) {
        Vec v = {0.0f, 0.0f, -1.0f};
        switch (l->type) {
        case 1:
        case 2:
        case 3:
        case 4:
            fn_80312654(rx, 'X', 0.017453292f * l->dir.x);
            fn_80312654(ry, 'Y', 0.017453292f * l->dir.y);
            fn_80312654(rz, 'Z', 0.017453292f * l->dir.z);
            fn_80312378(ry, rx, r);
            fn_80312378(rz, r, r);
            if (l->x2) {
                Vec p = {0.0f, 0.0f, 0.0f};
                Vec n = {0.0f, 1.0f, 0.0f};
                fn_80312A50(refl, &p, &n);
                fn_80312378(refl, r, r);
            }
            if (m != NULL) {
                fn_80312378(m, r, r);
            }
            fn_80312DB4(r, &v, &l->pos);
            break;
        }
        l++;
    }
}

extern u32 lbl_804CB088;

void fn_80011274(void) {
    lbl_804CB088 = 0;
}

typedef struct GXLightObj {
    u32 data[0x10];
} GXLightObj;

extern void fn_80312E08(Mtx m, const Vec* src, Vec* dst);                   /* PSMTXMultVecSR */
extern void fn_80305424(GXLightObj* lt, f32 x, f32 y, f32 z);               /* GXInitLightPos */
extern void fn_80305434(GXLightObj* lt, f32 nx, f32 ny, f32 nz);            /* GXInitLightDir */
extern void fn_80305450(GXLightObj* lt, f32 nx, f32 ny, f32 nz);            /* GXInitSpecularDir */
extern void fn_80305354(GXLightObj* lt, f32 refDist, f32 refBr, u32 func);  /* GXInitLightDistAttn */
extern void fn_803051CC(GXLightObj* lt, f32 cutoff, u32 func);              /* GXInitLightSpot */
extern void fn_803051B0(GXLightObj* lt, f32 a0, f32 a1, f32 a2, f32 k0, f32 k1, f32 k2); /* GXInitLightAttn */
extern void fn_8030555C(GXLightObj* lt, GXColor color);                     /* GXInitLightColor */
extern void fn_80305568(GXLightObj* lt, u32 id);                            /* GXLoadLightObjImm */

/* GLightSet_Load: loads every used light into GX (once per set) */
void fn_80011280(GLightSet* s) {
    GLight* l;
    BOOL scale;
    int i;
    GXColor col;
    Vec pos;
    GXLightObj lt;
    if (s == NULL) {
        s = lbl_804CA050;
    }
    if ((GLightSet*)lbl_804CB088 == s) {
        return;
    }
    lbl_804CB088 = (u32)s;
    s->x0 = 0;
    s->x1 = 0;
    l = s->body.lights;
    for (i = 0; i < 8; i++) {
        if (l->type != 0) {
            pos = l->pos;
            col = l->color;
            scale = l->x2 != 0;
            if (l->link >= 0) {
                GLight* o = &s->body.lights[l->link];
                pos = o->pos;
                col = o->color;
                scale = o->x2 != 0;
            }
            switch (l->type) {
            case 1:
            case 2:
                fn_803134A8(&pos, &pos, -10000.0f);
                fn_80312E08(lbl_804CB080->view, &pos, &pos);
                fn_80305424(&lt, pos.x, pos.y, pos.z);
                fn_80305354(&lt, 0.0f, 0.0f, 0);
                fn_803051CC(&lt, 0.0f, 0);
                s->x0 |= 1 << i;
                break;
            case 3:
            case 4:
                fn_80312E08(lbl_804CB080->view, &pos, &pos);
                fn_80305450(&lt, pos.x, pos.y, pos.z);
                fn_80305354(&lt, 0.0f, 0.0f, 0);
                fn_803051CC(&lt, 0.0f, 0);
                fn_803051B0(&lt, 0.0f, 0.0f, 1.0f, 64.0f, 0.0f, -63.0f);
                s->x1 |= 1 << i;
                break;
            case 5:
                fn_80312DB4(lbl_804CB080->view, &pos, &pos);
                fn_80305424(&lt, pos.x, pos.y, pos.z);
                fn_80305354(&lt, l->x20, 0.5f, 2);
                fn_803051CC(&lt, 30.0f, 0);
                s->x0 |= 1 << i;
                break;
            case 6:
                fn_80312E08(lbl_804CB080->view, &pos, &pos);
                fn_80305434(&lt, pos.x, pos.y, pos.z);
                fn_80305424(&lt, pos.x, pos.y, pos.z);
                fn_80305354(&lt, l->x20, 0.5f, 2);
                fn_803051CC(&lt, l->dir.x, 2);
                s->x0 |= 1 << i;
                break;
            case 7:
                fn_80312DB4(lbl_804CB080->view, &pos, &pos);
                fn_80305424(&lt, pos.x, pos.y, pos.z);
                fn_80305354(&lt, l->x20, 0.5f, 2);
                fn_803051CC(&lt, 30.0f, 0);
                s->x0 |= 1 << i;
                break;
            }
            if (scale) {
                col.r = col.r * l->x2 / 100;
                col.g = col.g * l->x2 / 100;
                col.b = col.b * l->x2 / 100;
            }
            fn_8030555C(&lt, col);
            fn_80305568(&lt, 1 << i);
        }
        l++;
    }
}

extern s8 lbl_804CA048;
extern void fn_80021BA4(int type, int src, int dst, int op);   /* blend mode */
extern void fn_800217CC(int enable);
extern void fn_80021808(int a, int b, int c, int d, int e);
extern void fn_80021860(int a, int b, int c);
extern void fn_80021FEC(int a);
extern void fn_80021FE8(int a);
extern void fn_80021B68(int a);
extern void fn_800221BC(void);
extern void fn_800220B0(void);

/* GSetDrawMode: mode < 0 re-applies the current one */
void fn_80011838(int mode) {
    if (mode < 0) {
        mode = lbl_804CA048;
    } else {
        lbl_804CA048 = mode;
    }
    switch (mode) {
    case 0:
    case 1:
        fn_80021BA4(0, 1, 0, 7);
        fn_800217CC(1);
        fn_80021808(0, 0, 1, 7, 0);
        fn_80021860(1, 3, 1);
        break;
    case 2:
        fn_80021BA4(0, 4, 5, 7);
        fn_800217CC(0);
        fn_80021808(4, 0x80, 1, 0, 0);
        fn_80021860(1, 3, 1);
        break;
    case 3:
    case 4:
    case 5:
        fn_80021BA4(1, 4, 5, 7);
        fn_800217CC(0);
        fn_80021808(4, 0, 1, 0, 0);
        fn_80021860(1, 3, 0);
        break;
    case 6:
        fn_80021808(7, 0, 1, 7, 0);
        fn_80021860(1, 3, 0);
        break;
    }
    fn_800109B8();
    fn_80021FEC(1);
    fn_80021FE8(0);
    fn_80021B68(2);
    fn_800221BC();
    fn_800220B0();
}

typedef void (*GDispFunc)(void* arg);
extern BOOL fn_8001AB10(void);
extern void fn_8001AC30(void);

/* GCamera_DrawDisps: loads the light sets, then runs each layer's list with
 * its draw mode. Layer 4 only runs when fn_8001AB10 allows it. */
void fn_800119BC(GCamera* c) {
    GLightSet* s;
    GDisp* d;
    int i;
    fn_80011274();
    for (i = 0, s = lbl_803B6710; i < 8; i++, s++) {
        fn_80011280(s);
    }
    lbl_804CB085 = 1;
    fn_80011838(0);
    for (d = c->lists[0]; d != NULL; d = d->next) {
        ((GDispFunc)d->func)(d->arg);
    }
    fn_80011838(1);
    for (d = c->lists[1]; d != NULL; d = d->next) {
        ((GDispFunc)d->func)(d->arg);
    }
    fn_80011838(2);
    for (d = c->lists[2]; d != NULL; d = d->next) {
        ((GDispFunc)d->func)(d->arg);
    }
    fn_80011838(3);
    for (d = c->lists[3]; d != NULL; d = d->next) {
        ((GDispFunc)d->func)(d->arg);
    }
    d = c->lists[4];
    if (d != NULL) {
        fn_80011838(4);
        if (fn_8001AB10()) {
            for (; d != NULL; d = d->next) {
                ((GDispFunc)d->func)(d->arg);
            }
            fn_8001AC30();
        }
    }
    fn_80011838(5);
    for (d = c->lists[5]; d != NULL; d = d->next) {
        ((GDispFunc)d->func)(d->arg);
    }
    lbl_804CB085 = 0;
    fn_80011838(6);
}

/* GCamera_ResetDisps */
void fn_80011B58(GCamera* c) {
    GCamera_ClearDisps(c);
}

extern void fn_80307BCC(f32 x, f32 y, f32 z, Mtx mtx, const f32* pm, const f32* vp, f32* sx, f32* sy, f32* sz); /* GXProject */

/* GCamera_Project: world position to screen coordinates */
void fn_80011B90(GCamera* c, Vec* p, f32* out) {
    f32 pm[7];
    f32 vp[6];
    if (c == NULL) {
        c = lbl_804CB080;
    }
    pm[0] = 0.0f;
    pm[1] = c->proj[0][0];
    pm[2] = c->proj[0][2];
    pm[3] = c->proj[1][1];
    pm[4] = c->proj[1][2];
    pm[5] = c->proj[2][2];
    pm[6] = c->proj[2][3];
    vp[0] = c->vpX;
    vp[1] = c->vpY;
    vp[2] = c->vpW;
    vp[3] = c->vpH;
    vp[4] = c->vpNear;
    vp[5] = c->vpFar;
    fn_80307BCC(p->x, p->y, p->z, c->view, pm, vp, &out[0], &out[1], &out[2]);
}

extern void fn_803133E8(Mtx44 m, const Vec* src, Vec* dst);   /* PSMTX44MultVec */
extern u32 fn_80313128(Mtx44 src, Mtx44 inv);                  /* PSMTX44Inverse */

/* GCamera_ViewProjMultVec */
void fn_80011C4C(GCamera* c, const Vec* src, Vec* dst) {
    if (c == NULL) {
        c = lbl_804CB080;
    }
    fn_803133E8(c->viewProj, src, dst);
}

/* GCamera_Unproject */
void fn_80011C60(GCamera* c, const Vec* src, Vec* dst) {
    Mtx44 inv;
    if (c == NULL) {
        c = lbl_804CB080;
    }
    fn_80313128(c->viewProj, inv);
    fn_803133E8(inv, src, dst);
}

/* GDoneRender: ring buffer of callbacks run once drawing has finished */
typedef struct GDoneEntry {
    GDispFunc func;
    void* arg;
} GDoneEntry;

extern GDoneEntry lbl_803B7050[256];
extern s16 lbl_804CB08C; /* count */
extern s16 lbl_804CB08E; /* head */
extern s16 lbl_804CB090; /* entries that are due this frame */

/* GDoneRenderEntry */
void fn_80011CBC(GDispFunc func, void* arg) {
    GDoneEntry* e;
    if (lbl_804CB08C >= 0x100) {
        fn_8001E008(lbl_80360BEC + 1, 0x616, lbl_80360BEC + 0xD9);
    }
    e = &lbl_803B7050[(lbl_804CB08E + lbl_804CB08C++) % 256];
    e->func = func;
    e->arg = arg;
}

/* GDoneRender_Run */
void fn_80011D50(void) {
    int i;
    GDoneEntry* e;
    if (lbl_804CB08C > 0) {
        for (i = 0; i < lbl_804CB090; i++) {
            e = &lbl_803B7050[(lbl_804CB08E + i) % 256];
            e->func(e->arg);
        }
        lbl_804CB08E = (lbl_804CB08E + lbl_804CB090) % 256;
        lbl_804CB08C -= lbl_804CB090;
        lbl_804CB090 = lbl_804CB08C;
    }
}

/* GDoneRender_Reset */
void fn_80011E0C(void) {
    lbl_804CB08C = 0;
    lbl_804CB08E = 0;
    lbl_804CB090 = 0;
}

/* GDoneRender_GetCount */
s32 fn_80011E20(void) {
    return lbl_804CB08C;
}

}
