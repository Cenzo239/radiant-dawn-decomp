/* fn_80011680: light set init. Exact (round m2, m2-b): the light pointer is l = &s->body.lights[i] per iteration, not a walking pointer. */
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
void fn_8000F48C(GCamera* c);

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
GCamera* fn_8000F748(s32 maxDisps);


/* GCamera_Copy */
void fn_8000F7F4(GCamera* src, GCamera* dst);

/* GCamera_UpdateProjection */
void fn_8000F954(GCamera* c, Mtx44 proj, BOOL custom);

/* GCamera_SetScissor */
void fn_8000F9C8(GCamera* c, u16 x, u16 y, u16 w, u16 h);

/* GCamera_SetViewport */
void fn_8000F9E8(GCamera* c, f32 x, f32 y, f32 w, f32 h);

/* GCamera_SetNearFar */
void fn_8000FA18(GCamera* c, f32 n, f32 f);

/* GCamera_UpdateViewProj */
void fn_8000FA30(GCamera* c);


/* GCamera_UpdateView */
void fn_8000FA98(GCamera* c);

/* GCamera_GetViewMtx */
Mtx* fn_8000FB88(void);

/* GCamera_GetViewProjMtx */
Mtx44* fn_8000FB94(void);

extern double fn_80295A18(double x);                                    /* tan */
extern void fn_80313484(const Vec* a, const Vec* b, Vec* ab);          /* PSVECSubtract */
extern void fn_803134A8(const Vec* src, Vec* dst, f32 scale);          /* PSVECScale */
extern void fn_803134C4(const Vec* src, Vec* dst);                     /* PSVECNormalize */
extern void fn_8031292C(Mtx m, f32 x, f32 y, f32 z);                   /* PSMTXScale */
extern void fn_803128AC(Mtx m, f32 x, f32 y, f32 z);                   /* PSMTXTrans */
extern void fn_80312444(Mtx src, Mtx dst);                             /* PSMTXInverse? */
extern void fn_80312378(Mtx a, Mtx b, Mtx ab);                         /* PSMTXConcat */

/* GCamera_GetNearPlaneMtx: matrix mapping a unit quad onto the near plane. */
Mtx* fn_8000FBA0(GCamera* c, Mtx out);

extern void fn_80312C34(Mtx m, f32 fovy, f32 aspect, f32 scaleS, f32 scaleT, f32 transS, f32 transT); /* C_MTXLightPerspective */
extern void fn_80312D2C(Mtx m, f32 t, f32 b, f32 l, f32 r, f32 scaleS, f32 scaleT, f32 transS, f32 transT); /* C_MTXLightOrtho */

/* GCamera_GetTexProjMtx: projection matrix for projected textures. */
Mtx* fn_8000FEA0(GCamera* c, Mtx out);

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
void fn_8000FF74(GCamera* c);

/* GCamera_Begin3D */
void fn_800100C8(GCamera* c);
#pragma auto_inline reset

/* GCamera_BeginOrtho: centred orthographic projection of size w x h. */
void fn_800102AC(GCamera* c, f32 w, f32 h);

/* GCamera_End: back to the full-screen viewport, then redo the last Begin. */
void fn_800104DC(GCamera* c);

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
void fn_800106AC(int layer, void* func, void* arg);

#pragma use_lmw_stmw on
/* GCameraDispAlloc(layer, prio, func, arg) */
void fn_80010788(int layer, u8 prio, void* func, void* arg);
#pragma use_lmw_stmw reset

extern void fn_80012268(void);
extern void fn_800122F0(void);
extern void fn_800119BC(GCamera* c);

/* GCamera_Draw */
void fn_8001084C(GCamera* c);

/* GCamera_IncFrame */
void fn_8001093C(GCamera* c);

extern void* lbl_804CA04C;
extern u8 lbl_803B6700[0x10];

void* fn_80010960(void);

void fn_80010968(void* p);

void fn_80010980(void);

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
void fn_800109B8(void);

/* GFog_Reset */
void fn_80010AB8(void);

extern void fn_80021754(GXColor c);

static inline GXColor GFog_Color(GFog* f) {
    GXColor c = {0, 0, 0, 0};
    c.r = f->r;
    c.g = f->g;
    c.b = f->b;
    return c;
}

/* GFog_SetClearColor */
void fn_80010AE4(void);

/* GFog_GetColor (returned as a packed u32) */
u32 fn_80010B54(GFog* f);

/* GFog_SetColor */
void fn_80010B8C(GFog* f, GXColor c);

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
GLightSet* fn_80010BB0(int i);

GLightSet* fn_80010C18(void);

void fn_80010C20(GLightSet* s);

/* GLightSet_Copy */
void fn_80010C38(GLightSet* src, GLightSet* dst);

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
void fn_80010CA4(GLightSet* s);

/* GLightSet_FindType */
GLight* fn_80010DA4(GLightSet* s, int type);

/* GLightSet_Free: also frees the lights allocated for this one */
void fn_80010F94(GLightSet* s, GLight* l);

extern void fn_80312654(Mtx m, char axis, f32 rad);                         /* PSMTXRotRad */
extern void fn_80312A50(Mtx m, const Vec* p, const Vec* n);                 /* C_MTXReflect */
extern void fn_80312DB4(Mtx m, const Vec* src, Vec* dst);                   /* PSMTXMultVec */

/* GLightSet_Transform: rebuilds every light position from its rotation */
void fn_800110F4(GLightSet* s, Mtx m);

extern u32 lbl_804CB088;

void fn_80011274(void);

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
void fn_80011280(GLightSet* s);

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
void fn_80011838(int mode);

typedef void (*GDispFunc)(void* arg);
extern BOOL fn_8001AB10(void);
extern void fn_8001AC30(void);

/* GCamera_DrawDisps: loads the light sets, then runs each layer's list with
 * its draw mode. Layer 4 only runs when fn_8001AB10 allows it. */
void fn_800119BC(GCamera* c);

/* GCamera_ResetDisps */
void fn_80011B58(GCamera* c);

extern void fn_80307BCC(f32 x, f32 y, f32 z, Mtx mtx, const f32* pm, const f32* vp, f32* sx, f32* sy, f32* sz); /* GXProject */

/* GCamera_Project: world position to screen coordinates */
void fn_80011B90(GCamera* c, Vec* p, f32* out);

extern void fn_803133E8(Mtx44 m, const Vec* src, Vec* dst);   /* PSMTX44MultVec */
extern u32 fn_80313128(Mtx44 src, Mtx44 inv);                  /* PSMTX44Inverse */

/* GCamera_ViewProjMultVec */
void fn_80011C4C(GCamera* c, const Vec* src, Vec* dst);

/* GCamera_Unproject */
void fn_80011C60(GCamera* c, const Vec* src, Vec* dst);

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
void fn_80011CBC(GDispFunc func, void* arg);

/* GDoneRender_Run */
void fn_80011D50(void);

/* GDoneRender_Reset */
void fn_80011E0C(void);

/* GDoneRender_GetCount */
s32 fn_80011E20(void);

}

extern "C" {
/* fn_80011680 (GLight_InitAll): fn_80010CA4 (GLightSet_Init) inlined over the 8 sets.
 * InitSet is a flat copy of fn_80010CA4 with the two Vec temporaries in sibling
 * inlines: that reproduces the original stack slots (amb, c, d, p). */
static inline void setPos(GLight* l) { Vec p = lbl_80360BC8; l->pos = p; }
static inline void setDir(GLight* l) { Vec d = {0.0f, 0.0f, 0.0f}; l->dir = d; }
static inline void InitSet(GLightSet* s) {
    GLight* l;
    int i;
    if (s == NULL) {
        s = lbl_804CA050;
    }
    GXColor amb = {0, 0, 0, 0};
    s->ambient = amb;
    s->x0 = 0;
    s->x1 = 0;
    for (i = 0; i < 8; i++) {
        l = &s->body.lights[i];
        l->type = 0;
        l->x2 = 0;
        GXColor c = {0, 0, 0, 0};
        l->color = c;
        setPos(l);
        setDir(l);
        l->x20 = 1.0f;
        l->link = -1;
        l->id = i;
    }
}

void fn_80011680(void) {
    int i;
    for (i = 0; i < 8; i++) {
        InitSet(&lbl_803B6710[i]);
    }
    lbl_804CA050 = lbl_803B6710;
}

}
