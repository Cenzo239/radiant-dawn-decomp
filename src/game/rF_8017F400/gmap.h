#ifndef RF_8017F400_GMAP_H
#define RF_8017F400_GMAP_H
#include "game/rF_8017F400/types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* world-map ("gmap") curve file loaded from gmap/curve/%s.bin */
typedef struct GMapCurveData {
    u8 pad0[4];
    char name[0x18]; /* 0x04 */
    s32 count;       /* 0x1C */
    u8 pad20[0xC];
    void* points;    /* 0x2C, fixed up to point at +0x30 */
} GMapCurveData;

typedef struct GMapCurve {
    s16 pos;              /* 0x0 */
    s16 unk2;             /* 0x2 */
    u16 flags;            /* 0x4: 1 = in use, 2 = visible?, 4 = ? */
    s16 unk6;             /* 0x6 */
    s16 unk8;             /* 0x8 */
    s16 unkA;             /* 0xA */
    GMapCurveData* data;  /* 0xC */
} GMapCurve;

/* entry of the gmap table at lbl_80387D10 (16 bytes) */
typedef struct GMapInfo {
    const char* id;    /* 0x0 "GID_xxxx" */
    u8 pad4[4];
    const char* mess;  /* 0x8 */
    const char* rect;  /* 0xC */
} GMapInfo;

typedef struct GMapEntA {
    s8 state;     /* 0x0 */
    u8 pad[3];
    void* proc;   /* 0x4 */
} GMapEntA;

typedef struct GMapEntB {
    u8 unk0;      /* 0x0 */
    s8 state;     /* 0x1 */
    u8 unk2;      /* 0x2 */
    u8 alpha;     /* 0x3 */
    u8 pad4[4];
    void* model;  /* 0x8 */
} GMapEntB;

/* process that owns a GMap; index into lbl_804CB908 at +0x30 */
typedef struct GMapProc {
    u8 pad[0x30];
    u8 idx;       /* 0x30 */
} GMapProc;

typedef struct GMapEntC {
    u8 flags;     /* 0x0 */
    s8 state;     /* 0x1 */
    s16 x;        /* 0x2 */
    s16 dur;      /* 0x4 */
    u8 unk6;      /* 0x6 */
    u8 unk7;      /* 0x7 */
} GMapEntC;

typedef struct GMap {
    void* tpl;             /* 0x000 */
    void* tpl2;            /* 0x004 */
    u8 pad8[0x4];
    u8 idx;                /* 0x00C */
    u8 padD[0x3];
    f32 view[4];           /* 0x010 */
    f32 width;             /* 0x020 */
    f32 height;            /* 0x024 */
    u8 alpha;              /* 0x028 */
    u8 pad29[3];
    u32 unk2C;             /* 0x02C */
    GMapInfo* info;        /* 0x030 */
    GMapEntA a[20];        /* 0x034 */
    GMapEntB b[10];        /* 0x0D4 */
    GMapEntC c[9];         /* 0x14C */
    GMapCurve curves[8];   /* 0x194 */
    s16 fadeOn;            /* 0x214 */
    s16 fadeTimer;         /* 0x216 */
    s16 fadeDur;           /* 0x218 */
    s16 fadeAlpha;         /* 0x21A */
    void* proc21C;         /* 0x21C */
    char tplName[0x28];    /* 0x220 */
    GMapProc* proc;        /* 0x248 */
    s16 alphaTimer;        /* 0x24C */
    s16 alphaDur;          /* 0x24E */
    u8 alphaFrom;          /* 0x250 */
    u8 alphaTo;            /* 0x251 */
    s16 viewTimer;         /* 0x252 */
    s16 viewDur;           /* 0x254 */
    u8 pad256[2];
    f32 viewLerp[4][2];    /* 0x258: {from, to} */
} GMap;

extern const char lbl_8036BA4C[]; /* gmap string pool */
extern GMap* lbl_804CB908[2];     /* active gmaps */
extern GMapInfo lbl_80387D10[];   /* gmap table */
extern int fn_80290DDC(char* buf, const char* fmt, ...); /* sprintf */
extern int fn_80291188(const char* a, const char* b);    /* strcmp */
extern void* fn_8023F1A4(const char* path, int arg);     /* load file */
#if TARGET_PC
extern FE10_PROTO void fn_8023F1A8(ptr32<const void>);                     /* free file */
#else
extern void fn_8023F1A8(void* file);                     /* free file */
#endif

#ifdef __cplusplus
}
#endif
#endif
