#ifndef RL_MAP3D_H
#define RL_MAP3D_H
#include "game/rL_80133EB4/types.h"

/* The map's 3D model. Names are guesses from behaviour. */
struct MapGroup {
    u8 pad0[0xB8];
    u32 flags;      /* 0xB8 */
    u8 padBC[4];
};

/* One map block, 0xD0 bytes. Quadtree nodes chain them through next. */
struct Mesh {
    u8 flags;         /* 0x00: 4 hidden, 0x20 culled, 0x40 ... */
    s8 tx, ty;        /* 0x01 tile position */
    u8 pad3;
    s8 x0, y0, x1, y1; /* 0x04 tile bounds */
    u8 pad8[8];
    MapGroup* group;  /* 0x10 */
    u8 pos14[0xB0 - 0x14];
    f32 minx, miny, minz; /* 0xB0 */
    f32 maxx, maxy, maxz; /* 0xBC */
    Mesh* next;       /* 0xC8 */
    u8 padCC[4];
};

struct QTNode;

struct MapEntry18 {
    u8 pad0[0x18];
};

struct MapModel {
    u8 pad0[4];
    void* x04;       /* 0x04 */
    MapGroup* group; /* 0x08 */
    Mesh* mesh;      /* 0x0C */
    void* x10;       /* 0x10 */
    u8 pad14[0x3C - 0x14];
    Mesh* x3c[4];    /* 0x3C */
    u8 x4c, x4d, x4e;
    u8 pad4F;
    s16 nGroup;      /* 0x50 */
    s16 nMesh;       /* 0x52 */
    u8 pad54[0x80 - 0x54];
    QTNode* quad;    /* 0x80 */
    u8 pad84[0x8A - 0x84];
    char name[0xAA - 0x8A]; /* 0x8A */
    u8 version;      /* 0xAA */
    u8 xab, xac, xad, xae, xaf, xb0, xb1; /* 0xAB */
    u8 padB2[2];
    u32 flags;       /* 0xB4 */
    u8 xb8, xb9, xba, xbb;
    u8 padBC[8];
    f32 xc4;         /* 0xC4 */
    f32 xc8;         /* 0xC8 */
    u8 padCC[4];
    f32 scale;       /* 0xD0 */
    u8 padD4[0xE4 - 0xD4];
    u8 xe4[0x114 - 0xE4]; /* 0xE4 matrix */
    MapEntry18 lights[16];  /* 0x114 */
};

class Pad {
public:
    virtual int v08();
    virtual int v0C();
    virtual int v10();
    virtual int v14();
    virtual int v18();
    virtual int v1C();
    virtual int v20();
    virtual int v24();
    virtual int v28();
    virtual int v2C();
    virtual int v30();
    virtual int v34();
    virtual int v38();
    virtual int v3C();
    virtual int v40();
    virtual int v44();
    virtual int v48();
    virtual int v4C();
    virtual int v50();
    virtual int v54();
    virtual int v58();
    virtual int v5C();
    virtual int v60();
    virtual int v64();
    virtual int v68();
    virtual int v6C();
    virtual int v70();
    virtual int v74();
    virtual int v78();
    virtual int v7C();
    virtual int v80();
    virtual int v84();
    virtual int v88();
    virtual int v8C();
    virtual int v90();
    virtual int v94();
    virtual int v98();
    virtual int v9C();
    virtual int vA0();
    virtual int vA4();
    virtual int vA8(int);
    virtual int vAC();
};
extern "C" Pad* lbl_804CB5B8;

static inline Mesh* MeshAt(MapModel* mm, int i) { return &mm->mesh[i]; }

#endif
