#include "game/rA_800068A0/types.h"

/* GMaterial.c: allocators for the GX TEV stage / tex map / tex coord / tex mtx
 * / channel / indirect resources used by one material, and texture binding.
 * lbl_80360D24 is the assert string pool ("GMaterial.c" + messages). */

extern "C" {

extern char lbl_80360D24[];
extern void fn_8001E008(const char* file, int line, const char* msg);

extern u32 lbl_80378780[16]; /* GXTevStageID */
extern u32 lbl_803787C0[8];  /* GXTexMapID */
extern u32 lbl_803787E0[8];  /* GXTexCoordID */
extern u32 lbl_80378800[10]; /* texture matrix */
extern u32 lbl_80378828[4];
extern u32 lbl_80378838[4];
extern u32 lbl_80378848[4];
extern u8 lbl_804CB098;
extern u8 lbl_804CB099;
extern u8 lbl_804CB09A;
extern u8 lbl_804CB09B;
extern u8 lbl_804CB09C;
extern u8 lbl_804CB09D;
extern u8 lbl_804CB09E;

/* GMaterial_AllocTevStage */
u32 fn_80011E28(void) {
    if (lbl_804CB098 >= 0x10) {
        fn_8001E008(lbl_80360D24, 0x31, lbl_80360D24 + 0xC);
    }
    return lbl_80378780[lbl_804CB098++];
}

/* GMaterial_LastTevStage */
u32 fn_80011E80(void) {
    if (lbl_804CB098 == 0) {
        return 0x10;
    }
    return lbl_80378780[lbl_804CB098 - 1];
}

u32 fn_80011EAC(void) {
    return lbl_804CB098;
}

/* GMaterial_AllocTexMap */
u32 fn_80011EB4(void) {
    if (lbl_804CB099 >= 8) {
        fn_8001E008(lbl_80360D24, 0x55, lbl_80360D24 + 0x28);
    }
    return lbl_803787C0[lbl_804CB099++];
}

/* GMaterial_LastTexMap */
u32 fn_80011F0C(void) {
    if (lbl_804CB099 == 0) {
        return 0xFF;
    }
    return lbl_803787C0[lbl_804CB099 - 1];
}

/* GMaterial_AllocTexCoord */
u32 fn_80011F38(void) {
    if (lbl_804CB09A >= 8) {
        fn_8001E008(lbl_80360D24, 0x76, lbl_80360D24 + 0x40);
    }
    return lbl_803787E0[lbl_804CB09A++];
}

/* GMaterial_LastTexCoord */
u32 fn_80011F90(void) {
    if (lbl_804CB09A == 0) {
        return 0xFF;
    }
    return lbl_803787E0[lbl_804CB09A - 1];
}

u32 fn_80011FBC(void) {
    return lbl_804CB09A;
}

/* GMaterial_AllocTexMtx */
u32 fn_80011FC4(void) {
    if (lbl_804CB09B >= 0x3C) {
        fn_8001E008(lbl_80360D24, 0x9C, lbl_80360D24 + 0x5A);
    }
    return lbl_80378800[lbl_804CB09B++];
}

/* GMaterial_LastTexMtx */
u32 fn_8001201C(void) {
    if (lbl_804CB09B == 0) {
        return 0x3C;
    }
    return lbl_80378800[lbl_804CB09B - 1];
}

u32 fn_80012048(void) {
    if (lbl_804CB09C >= 4) {
        fn_8001E008(lbl_80360D24, 0xBB, lbl_80360D24 + 0x73);
    }
    return lbl_80378828[lbl_804CB09C++];
}

u32 fn_800120A0(void) {
    if (lbl_804CB09C == 0) {
        return 4;
    }
    return lbl_80378828[lbl_804CB09C - 1];
}

u32 fn_800120CC(void) {
    return lbl_804CB09C;
}

u32 fn_800120D4(void) {
    if (lbl_804CB09D >= 3) {
        fn_8001E008(lbl_80360D24, 0xDD, lbl_80360D24 + 0x88);
    }
    return lbl_80378838[lbl_804CB09D++];
}

u32 fn_8001212C(s32 i) {
    switch (i) {
    case 1:
        return 2;
    case 2:
        return 4;
    case 3:
        return 6;
    default:
        return 0;
    }
}

u32 fn_80012170(void) {
    if (lbl_804CB09E >= 4) {
        fn_8001E008(lbl_80360D24, 0x11B, lbl_80360D24 + 0xA0);
    }
    return lbl_80378848[lbl_804CB09E++];
}

u32 fn_800121C8(s32 i) {
    switch (i) {
    case 0:
        return 0xC;
    case 1:
        return 0xD;
    case 2:
        return 0xE;
    case 3:
        return 0xF;
    default:
        return 0xC;
    }
}

u32 fn_80012218(s32 i) {
    switch (i) {
    case 0:
        return 0x1C;
    case 1:
        return 0x1D;
    case 2:
        return 0x1E;
    case 3:
        return 0x1F;
    default:
        return 0x1C;
    }
}

extern void fn_80306B24(u32 stage);
extern void fn_80021C74(u32 n);

/* GMaterial_Reset */
void fn_80012268(void) {
    u32* p;
    int i;
    lbl_804CB098 = 0;
    lbl_804CB099 = 0;
    lbl_804CB09A = 0;
    lbl_804CB09B = 0;
    lbl_804CB09D = 0;
    lbl_804CB09E = 0;
    if (lbl_804CB09C != 0) {
        p = lbl_80378780;
        for (i = 0; i < 8; i++) {
            fn_80306B24(*p);
            p++;
        }
        fn_80021C74(0);
        lbl_804CB09C = 0;
    }
}

typedef struct GXTexObj {
    u32 data[8];
} GXTexObj;

typedef struct GXTlutObj {
    u32 data[3];
} GXTlutObj;

typedef struct GTexPair {
    void* tex;
    void* tlut;
} GTexPair;

typedef struct GTexRes {
    u32 x0;
    u32 x4;
    GTexPair* table;    /* 0x08 */
} GTexRes;

typedef struct GTexDesc {
    u16 flags;          /* bit 5: rebuild with mip off and repeat wrap */
    u16 x2;
    u16 index;          /* 0x04 */
} GTexDesc;

typedef struct GTexCache {
    GTexRes* res;
    GTexDesc* desc;
    GXTexObj obj;
} GTexCache;

extern GTexCache lbl_803B7850;

/* GMaterial_ClearTexCache */
void fn_800122F0(void) {
    lbl_803B7850.res = NULL;
    lbl_803B7850.desc = NULL;
}

extern void fn_80006A64(GTexRes* res, GXTexObj* obj, u16 index);
extern void fn_80006B84(GTexRes* res, GXTexObj* obj, GXTlutObj* tlut, u32 name, u32 index);
extern u8 fn_80305E40(GXTexObj* obj);   /* GXGetTexObjMipMap */
extern u32 fn_80305E20(GXTexObj* obj);   /* GXGetTexObjFmt */
extern u16 fn_80305E0C(GXTexObj* obj);   /* GXGetTexObjHeight */
extern u16 fn_80305DF8(GXTexObj* obj);   /* GXGetTexObjWidth */
extern void* fn_80305DEC(GXTexObj* obj); /* GXGetTexObjData */
extern void fn_80305A40(GXTexObj* obj, void* image, u16 w, u16 h, u32 fmt, u32 wrapS, u32 wrapT, u8 mip); /* GXInitTexObj */
extern void fn_80306054(GXTlutObj* tlut, u32 name); /* GXLoadTlut */

#pragma use_lmw_stmw on
/* GMaterial_GetTexObj: caches the last res/desc pair */
GXTexObj* fn_80012308(GTexRes* res, GTexDesc* desc) {
    GXTlutObj tlut;
    GXTexObj* obj;
    if (lbl_803B7850.res == res && lbl_803B7850.desc == desc) {
        return &lbl_803B7850.obj;
    }
    lbl_803B7850.res = res;
    obj = &lbl_803B7850.obj;
    lbl_803B7850.desc = desc;
    if (res != NULL) {
        fn_80006A64(res, obj, desc->index);
        if (desc->flags & 0x20) {
            fn_80305A40(obj, fn_80305DEC(obj), fn_80305DF8(obj), fn_80305E0C(obj), fn_80305E20(obj), 1, 1, fn_80305E40(obj));
        }
        if (res->table[desc->index].tlut != NULL) {
            fn_80006B84(res, obj, &tlut, 0, desc->index);
            fn_80306054(&tlut, 0);
        }
    }
    return obj;
}
#pragma use_lmw_stmw off

typedef struct GMatLayer {
    u16 flags;          /* 0x00: bit 7 keeps the stored stage */
    u8 stage;           /* 0x02 */
    u8 type;            /* 0x03 */
    u8 x4[0x1C - 4];
} GMatLayer;

typedef struct GMatHook {
    u8 type;
    u8 pad[3];
    void (*func)(void* a, void* b, struct GMaterial* m, void* d);
} GMatHook;

typedef struct GMaterial {
    u32 x0;
    u16 x4;
    u8 nLayers;         /* 0x06 */
    u8 flags;           /* 0x07 */
    u8 r, g, b;         /* 0x08 */
    u8 xB;
    u8 xC, xD, xE;
    u8 xF[0x13 - 0xF];
    u8 x13;
    GMatLayer* layers;  /* 0x14 */
    GMatHook* hooks;    /* 0x18 */
} GMaterial;

/* GMaterial_Fixup */
void fn_80012430(GMaterial* m) {
    int r = 1.25f * m->r;
    int g = 1.25f * m->g;
    int b = 1.25f * m->b;
    int i;
    if (r > 0xFF) {
        r = 0xFF;
    }
    if (g > 0xFF) {
        g = 0xFF;
    }
    if (b > 0xFF) {
        b = 0xFF;
    }
    m->r = r;
    m->g = g;
    m->b = b;
    if (m->nLayers > 1) {
        m->flags |= 0x20;
    }
    for (i = 0; i < m->nLayers; i++) {
        GMatLayer* l = &m->layers[i];
        if (l->type == 5) {
            m->flags |= 0x40;
        }
        if (l->type == 6) {
            m->flags |= 0x80;
        }
        if (l->type == 0) {
            m->flags &= ~0x20;
        }
        if (!(l->flags & 0x80)) {
            l->stage = i + 4;
        }
    }
    if (m->x4 & 0x6000) {
        m->x4 |= 8;
    }
    m->xC = 0;
    m->xD = 0;
    m->xE = 0;
    m->x13 = 0;
}

extern BOOL fn_80012F00(void* a, void* b, void* c, GMatLayer* l, void* e);
extern void fn_8001393C(void* a, void* b, void* c, GMaterial* m, void* e);

#pragma use_lmw_stmw on
/* GMaterial_SetupLayers */
void fn_800138B8(void* a, void* b, void* c, GMaterial* m, void* e) {
    GMatLayer* l;
    int i;
    i = 0;
    for (l = m->layers; i < m->nLayers; i++, l++) {
        if (l->type != 6) {
            if (!fn_80012F00(a, b, c, l, e)) {
                return;
            }
        }
    }
}

/* GMaterial_SetupAll */
void fn_80013C54(void* a, void* b, void* c, GMaterial* m, void* e) {
    int i;
    GMatLayer* l;
    i = 0;
    for (l = m->layers; i < m->nLayers; i++, l++) {
        if (l->type != 6) {
            if (!fn_80012F00(a, b, c, l, e)) {
                break;
            }
        }
    }
    fn_8001393C(a, b, c, m, e);
}
#pragma use_lmw_stmw off

extern void fn_80021B68(int mode);

/* GMaterial_SetCull: chooses the cull mode from the object and draw flags */
void fn_800140A0(u32* obj, GMaterial* m) {
    int t[3] = {1, 2, 0};
    switch ((int)(*obj & 0x18000000)) {
    case 0x08000000:
        t[0] = 2;
        t[1] = 1;
        break;
    case 0x10000000:
        t[2] = 2;
        t[1] = 2;
        t[0] = 2;
        break;
    case 0x18000000:
        t[2] = 1;
        t[1] = 1;
        t[0] = 1;
        break;
    }
    switch (*(u16*)((u8*)m + 8) & 0x1800) {
    case 0x800:
        fn_80021B68(t[0]);
        return;
    case 0x1000:
        fn_80021B68(t[1]);
        return;
    case 0x1800:
        fn_80021B68(t[2]);
        return;
    default:
        fn_80021B68(t[1]);
        return;
    }
}

#pragma use_lmw_stmw on
/* GMaterial_RunHooks1 */
BOOL fn_800146A8(u32* a, void* b, GMaterial* m, void* d) {
    int i;
    GMatHook* h;
    if (!(m->flags & 1)) {
        return FALSE;
    }
    if (*a & 0x8000) {
        return FALSE;
    }
    h = m->hooks;
    if (h == NULL) {
        return FALSE;
    }
    for (i = 0; i < 8; i++) {
        if (h->func == NULL) {
            break;
        }
        if (h->type == 1) {
            h->func(a, b, m, d);
        }
        h++;
    }
    return TRUE;
}

/* GMaterial_RunHooks2 */
BOOL fn_80014760(u32* a, void* b, GMaterial* m, void* d) {
    int i;
    GMatHook* h;
    if (!(m->flags & 2)) {
        return FALSE;
    }
    if (*a & 0x8000) {
        return FALSE;
    }
    h = m->hooks;
    if (h == NULL) {
        return FALSE;
    }
    for (i = 0; i < 8; i++) {
        if (h->func == NULL) {
            break;
        }
        if (h->type == 2) {
            h->func(a, b, m, d);
        }
        h++;
    }
    return TRUE;
}

/* GMaterial_RunHooks4 */
BOOL fn_80014818(u32* a, void* b, GMaterial* m, void* d) {
    int i;
    GMatHook* h;
    if (!(m->flags & 4)) {
        return FALSE;
    }
    if (*a & 0x8000) {
        return FALSE;
    }
    h = m->hooks;
    for (i = 0; i < 8; i++) {
        if (h->func == NULL) {
            break;
        }
        if (h->type == 4) {
            h->func(a, b, m, d);
        }
        h++;
    }
    return TRUE;
}
#pragma use_lmw_stmw off

typedef struct GMatEntry {
    const char* name;
    u16 flags;
    u8 x6[0x20 - 6];
} GMatEntry;

typedef struct GMatSet {
    u8 x0[0x34];
    GMatEntry* entries; /* 0x34 */
    u8 x38[0x54 - 0x38];
    u16 count;          /* 0x54 */
} GMatSet;

static inline BOOL NameStartsWith(const char* a, const char* b) {
    while (*a != 0) {
        if (*b == 0) {
            break;
        }
        if (*a != *b) {
            return FALSE;
        }
        a++;
        b++;
    }
    return TRUE;
}

/* GMatSet_Find: index of the first entry with the name and any mask bit */
int fn_80014D40(GMatSet* s, const char* name, u32 mask) {
    if (s != NULL) {
        GMatEntry* e = s->entries;
        int i;
        for (i = 0; i < s->count; i++, e++) {
            if (mask == 0 || (e->flags & mask)) {
                if (name == NULL || NameStartsWith(e->name, name)) {
                    return i;
                }
            }
        }
    }
    return -1;
}

/* GMatSet_Count: entries with any mask bit */
int fn_80014DE4(GMatSet* s, u32 mask) {
    int n = 0;
    if (s != NULL) {
        GMatEntry* e = s->entries;
        int i;
        for (i = 0; i < s->count; i++) {
            if (e->flags & mask) {
                n++;
            }
            e++;
        }
    }
    return n;
}

#if TARGET_PC
extern FE10_PROTO void fn_800148C0(GMatEntry* e, void* a, ptr32<const void>);
#else
extern void fn_800148C0(GMatEntry* e, void* a, void* b);
#endif
extern void fn_800149F4(GMatEntry* e, void* a);
extern GMatEntry* fn_80076F54(const char* name);

#pragma use_lmw_stmw on
/* GMatSet_ForEachName3: name NULL = all, set NULL = global lookup */
BOOL fn_80014E24(GMatSet* s, const char* name, void* a, void* b) {
    int i;
    GMatEntry* found = NULL;
    if (s != NULL && name == NULL) {
        for (i = 0; i < s->count; i++) {
            fn_800148C0(&s->entries[i], a, b);
        }
        return TRUE;
    }
    if (s == NULL) {
        found = fn_80076F54(name);
        if (found != NULL) {
            fn_800148C0(found, a, b);
        }
    } else {
        for (i = 0; i < s->count; i++) {
            GMatEntry* e = &s->entries[i];
            if (NameStartsWith(e->name, name)) {
                found = e;
                fn_800148C0(e, a, b);
            }
        }
    }
    return found != NULL;
}

/* GMatSet_ForEachName2 */
void fn_80014F64(GMatSet* s, const char* name, void* a) {
    int i;
    if (s != NULL && name == NULL) {
        for (i = 0; i < s->count; i++) {
            fn_800149F4(&s->entries[i], a);
        }
        return;
    }
    if (s == NULL) {
        fn_800149F4(fn_80076F54(name), a);
    } else {
        for (i = 0; i < s->count; i++) {
            GMatEntry* e = &s->entries[i];
            if (NameStartsWith(e->name, name)) {
                fn_800149F4(e, a);
            }
        }
    }
}
#pragma use_lmw_stmw off

/* GMatSet_Filter: hides entries failing the masks, returns the visible count */
int fn_80015070(GMatSet* s, u32 need, u32 reject) {
    int n = 0;
    GMatEntry* e = s->entries;
    int i;
    for (i = 0; i < s->count; i++, e++) {
        ((u8*)e)[7] &= ~0x10;
        if (need != 0 && !(e->flags & need)) {
            ((u8*)e)[7] |= 0x10;
        } else if (reject != 0 && (e->flags & reject)) {
            ((u8*)e)[7] |= 0x10;
        } else {
            n++;
        }
    }
    return n;
}

#if TARGET_PC
extern FE10_PROTO ptr32<void> fn_8001AAB4(void);
#else
extern void* fn_8001AAB4(void);
#endif
#if TARGET_PC
extern FE10_PROTO ptr32<void> fn_8001C8EC(void);
#else
extern void* fn_8001C8EC(void);
#endif
#if TARGET_PC
extern FE10_PROTO void fn_80020E7C(i32arg);
#else
extern void fn_80020E7C(void* p);
#endif
extern void fn_80020EEC(void);

void fn_800150F4(GMatSet* s) {
    GMatEntry* e = s->entries;
    int i = 0;
    for (; i < s->count; i++, e++) {
        if (e->flags & 0x400) {
            fn_80020E7C(fn_8001AAB4());
        }
        if (e->flags & 0x40) {
            fn_80020E7C(fn_8001C8EC());
        }
    }
}

void fn_80015174(GMatSet* s) {
    GMatEntry* e = s->entries;
    int i = 0;
    for (; i < s->count; i++, e++) {
        if (e->flags & 0x400) {
            fn_80020EEC();
        }
        if (e->flags & 0x40) {
            fn_80020EEC();
        }
    }
}

typedef struct GRelocEntry {
    u32 x0;
    u8 x4[0x20 - 4];
    u32 x20, x24, x28, x2C;
    u8 x30[4];
} GRelocEntry;

typedef struct GRelocHdr {
    u32 x0;
    u16 flags;          /* 0x04: 0x8000 = relocated */
    u16 count;          /* 0x06 */
    GRelocEntry entries[1];
} GRelocHdr;

/* GReloc_Apply */
void fn_800151EC(u32 base, GRelocHdr* h) {
    GRelocEntry* e;
    int i;
    if (h->flags & 0x8000) {
        return;
    }
    e = h->entries;
    for (i = 0; i < h->count; i++, e++) {
        if (e->x0 != 0) {
            e->x0 = e->x0 + base;
        }
        if (e->x20 != 0) {
            e->x20 = e->x20 + base;
        }
        if (e->x24 != 0) {
            e->x24 = e->x24 + base;
        }
        if (e->x28 != 0) {
            e->x28 = e->x28 + base;
        }
        if (e->x2C != 0) {
            e->x2C = e->x2C + base;
        }
    }
    h->flags |= 0x8000;
}

extern void fn_80078E24(void* p); /* free */

typedef struct GBufEntry {
    u8 x0[0xC];
    void* xC;
    void* x10;
} GBufEntry;

typedef struct GBufHdr {
    u8 x0[6];
    u16 count;
} GBufHdr;

typedef struct GBufSet {
    u8 x0[0x30];
    GBufHdr* hdr;       /* 0x30 */
    GBufEntry* entries; /* 0x34 */
} GBufSet;

typedef struct GBufOwner {
    u8 x0[0x54];
    GBufSet* set;       /* 0x54 */
} GBufOwner;

#pragma use_lmw_stmw on
/* GBufOwner_Free */
void fn_8001561C(GBufOwner* o) {
    GBufSet* set = o->set;
    if (set != NULL) {
        int i;
        GBufHdr* h;
        GBufEntry* e;
        e = set->entries;
        h = set->hdr;
        if (e != NULL) {
            for (i = 0; i < h->count; i++, e++) {
                if (e->xC != NULL) {
                    fn_80078E24(e->xC);
                    e->xC = NULL;
                }
                if (e->x10 != NULL) {
                    fn_80078E24(e->x10);
                    e->x10 = NULL;
                }
            }
            fn_80078E24(set->entries);
            set->entries = NULL;
        }
        fn_80078E24(o->set);
        o->set = NULL;
    }
}
#pragma use_lmw_stmw off

}
