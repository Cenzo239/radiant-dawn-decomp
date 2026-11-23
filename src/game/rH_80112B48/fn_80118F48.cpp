/* Support/relationship data and text helpers, 80118F48..8011A298. */
#include "game/rH_80112B48/types.h"
#pragma auto_inline off
#pragma use_lmw_stmw on

extern "C" {

extern char lbl_80368768[];
extern char lbl_803687C8[];
extern char lbl_80368F70[];
extern char lbl_80412AD8[];
extern char* fn_800D0864(void*);
extern void* fn_800C3FD0(void*);
extern char* strcpy(char*, const char*);
extern char* strchr(const char*, int);
extern char* fn_80291110(char*, const char*);
extern int fn_80291188(const char*, const char*);
extern void* fn_80077064(void*);
extern int fn_80109A50(void*);
#if TARGET_PC
/* host: returns the 32-bit value (a window offset) in w0; ptr32 widens it */
extern FE10_P32(char) fn_80109A88(void*);
#else
extern char* fn_80109A88(void*);
#endif
extern int fn_80109A18(void*);
extern void* fn_80060728(void*);
extern int fn_800607E4(void*);
extern u8 lbl_803CAB38[];
extern u32 lbl_804CB700;
int fn_801194FC(char*);

/* Reader for saves: +4 is the cursor. */
struct Reader {
    u8 pad0[4];
    u8* cur;
};

extern int fn_8008A1A0(Reader*);
extern int fn_8008A1B4(Reader*);
extern int fn_8008A1DC(Reader*);
extern void fn_8008A5AC(void*, int);
extern void fn_8008A5C0(void*, int);
extern void fn_8008A5E4(void*, int);
extern void* fn_80244470(void*, int);
extern void* fn_802447A0(void*, int);
extern void fn_8010E41C(void*, int);
extern void* fn_801059B0(void);
extern int fn_8010536C(void*, void*);
extern void* fn_8010B228(void*);
extern void* fn_8010B22C(int);
extern void* fn_8010B23C(void*);
extern void* fn_8010B1B4(int);
extern void fn_8012EAB4(void*, int, int);
extern int fn_8012E9B4(void*, void*);
extern int fn_8012C9BC(void*, void*);
extern int fn_80127650(void*, void*);
extern u8* fn_8024BC94(void);
extern u8* fn_8024BCA0(void);
#if TARGET_PC
extern FE10_PROTO char* fn_8010B384(int, ptr32<const void>);
#else
extern char* fn_8010B384(int, void*);
#endif
extern void* lbl_804CBFC8;

struct PairE {
    u8 a, b;
};

/* Character data, +0xDC is the support table (guessed). */
#if TARGET_PC
/* host: the job struct keeps the Wii layout; pointer slots are 32-bit window offsets */
struct Pair {
    FE10_P32(u8) unk0;
    u8 pad4[4];
    FE10_P32(void) unk8;
    FE10_P32(void) unkC;
    FE10_P32(void) unk10;
    FE10_P32(void) unk14;
    FE10_P32(void) unk18;
};
#else
struct Pair {
    u8* unk0;
    u8 pad4[4];
    void* unk8;
    void* unkC;
    void* unk10;
    void* unk14;
    void* unk18;
};
#endif

struct Sub {
    u8 pad0[0xE8];
    u8 c[4];
    u8 padEC[5];
    PairE e[2];
};

char* fn_80118F48(Pair* p) {
    if (p->unk8 == 0) {
        return lbl_80368768;
    } else {
        return fn_800D0864(p->unk8);
    }
}

char* fn_80118F68(Pair* p) {
    if (p->unkC == 0) {
        return lbl_80368768 + 6;
    } else {
        return fn_800D0864(p->unkC);
    }
}

void* fn_80118F8C(Pair* p) {
    return *(void**)((u8*)fn_800C3FD0(p->unk10) + 4);
}

char* fn_80118FB4(Pair* p) {
    strcpy(lbl_80412AD8, lbl_80368768 + 0x2d);
    fn_80291110(lbl_80412AD8, (char*)p->unk0 + 4);
    return lbl_80412AD8;
}

char* fn_80119010(Pair* p) {
    strcpy(lbl_80412AD8, lbl_80368768 + 0x33);
    fn_80291110(lbl_80412AD8, (char*)p->unk0 + 4);
    return lbl_80412AD8;
}

char* fn_8011906C(Pair* p) {
    strcpy(lbl_80412AD8, lbl_80368768 + 0x39);
    fn_80291110(lbl_80412AD8, (char*)p->unk0 + 4);
    return lbl_80412AD8;
}

char* fn_801190C8(Pair* a, Pair* b, int kind) {
    u8* s1;
    u8* s2;
    strcpy(lbl_80412AD8, lbl_80368768 + 0x4b);
    s1 = a->unk0 + 4;
    s2 = b->unk0 + 4;
    if ((u32)((s1[0] << 24) + ((s8)s1[1] << 16) + ((s8)s1[2] << 8) + (s8)s1[3]) <
        (u32)((s2[0] << 24) + ((s8)s2[1] << 16) + ((s8)s2[2] << 8) + (s8)s2[3])) {
        fn_80291110(lbl_80412AD8, (char*)s1);
        fn_80291110(lbl_80412AD8, lbl_80368768 + 0x52);
        fn_80291110(lbl_80412AD8, (char*)s2);
    } else {
        fn_80291110(lbl_80412AD8, (char*)s2);
        fn_80291110(lbl_80412AD8, lbl_80368768 + 0x52);
        fn_80291110(lbl_80412AD8, (char*)s1);
    }
    switch (kind) {
    case 1:
        fn_80291110(lbl_80412AD8, lbl_80368768 + 0x54);
        break;
    case 2:
        fn_80291110(lbl_80412AD8, lbl_80368768 + 0x57);
        break;
    case 3:
        fn_80291110(lbl_80412AD8, lbl_80368768 + 0x5a);
        break;
    }
    return lbl_80412AD8;
}

void fn_80119258(Sub* p, u8* c) {
    p->c[0] = c[0];
    p->c[1] = c[1];
    p->c[2] = c[2];
    p->c[3] = c[3];
}

char* fn_8011927C(char** p) {
    return strchr(*p, '_') + 1;
}

int fn_801192A8(Sub* p) {
    int r = 0;
    int i;
    for (i = 0; !r && i < 2; i++) {
        switch (p->e[i].a) {
        case 2:
        case 3:
        case 4:
            r = 1;
        }
    }
    return r;
}

void fn_801192F0(Pair* p) {
    if (p->unk10) {
        p->unk10 = fn_80077064(p->unk10);
    }
    if (p->unk14) {
        p->unk14 = fn_80077064(p->unk14);
    }
    if (p->unk18) {
        p->unk18 = fn_80077064(p->unk18);
    }
}

void fn_80119358(Sub* p, int i, u8 a, u8 b) {
    p->e[i].a = a;
    p->e[i].b = b;
}

struct Aff {
    u8 a, b, c, d;
};

extern Aff lbl_80412B18[8][8];

void fn_8011936C(void) {
    void* r;
    int n;
    Aff* e;
    int i;
    r = fn_80077064(lbl_803687C8);
    n = fn_80109A50(&r);
    e = &lbl_80412B18[0][0];
    for (i = 0; i < n; i++) {
        e->a = fn_801194FC(fn_80109A88(&r));
        e->b = fn_801194FC(fn_80109A88(&r));
        e->c = fn_80109A18(&r);
        e->d = fn_80109A18(&r);
        e++;
#if TARGET_PC
        r = (void*)((FE10_PTRINT(r) + 3) & ~3);
#else
        r = (void*)(((u32)r + 3) & ~3);
#endif
    }
}

struct Aff2 {
    u8 pad0[4];
    u8 v4, v5, v6, v7, v8, v9;
};

void fn_80119424(Aff2* d, u32 x, u32 y) {
    Aff* e;
    int i;
    int j;
    d->v9 = 0;
    d->v8 = 0;
    d->v7 = 0;
    d->v6 = 0;
    d->v5 = 0;
    d->v4 = 0;
    if (lbl_804CB700 & 0x40000) {
        return;
    }
    if (((u8*)fn_80060728(lbl_803CAB38))[0x11] == 2) {
        return;
    }
    e = &lbl_80412B18[0][0];
    for (i = 0; i < 8; i++, e += 8) {
        if (e->a == x) {
            for (j = 0; j < 8; j++, e++) {
                if (e->b == y) {
                    d->v6 = e->c;
                    d->v7 = e->d;
                    return;
                }
            }
            return;
        }
    }
}

int fn_801194FC(char* s) {
    if (s == 0) {
        return -1;
    }
    if (fn_80291188(s, lbl_803687C8 + 0xc) == 0) {
        return -1;
    }
    if (fn_80291188(s, lbl_803687C8 + 0x14) == 0) {
        return 1;
    }
    if (fn_80291188(s, lbl_803687C8 + 0x19) == 0) {
        return 2;
    }
    if (fn_80291188(s, lbl_803687C8 + 0x21) == 0) {
        return 3;
    }
    if (fn_80291188(s, lbl_803687C8 + 0x26) == 0) {
        return 4;
    }
    if (fn_80291188(s, lbl_803687C8 + 0x2c) == 0) {
        return 5;
    }
    if (fn_80291188(s, lbl_803687C8 + 0x31) == 0) {
        return 6;
    }
    if (fn_80291188(s, lbl_803687C8 + 0x37) == 0) {
        return 7;
    }
    return fn_80291188(s, lbl_803687C8 + 0x3e) ? 0 : 8;
}

char* fn_80119640(u32 k) {
    char* s;
    switch (k) {
    case 1:
        s = lbl_803687C8 + 0x45;
        break;
    case 2:
        s = lbl_803687C8 + 0x4c;
        break;
    case 3:
        s = lbl_803687C8 + 0x53;
        break;
    case 4:
        s = lbl_803687C8 + 0x5a;
        break;
    case 5:
        s = lbl_803687C8 + 0x62;
        break;
    case 6:
        s = lbl_803687C8 + 0x68;
        break;
    case 7:
        s = lbl_803687C8 + 0x70;
        break;
    case 8:
        s = lbl_803687C8 + 0x77;
        break;
    case 0:
    default:
        s = lbl_803687C8 + 0x80;
        break;
    }
    return fn_800D0864(s);
}

int fn_801196F0(u32 k) {
    switch (k) {
    case 0:
        return 0;
    case 1:
        return 6;
    case 2:
        return 8;
    case 3:
        return 7;
    case 4:
        return 3;
    case 5:
        return 5;
    case 6:
        return 4;
    case 7:
        return 1;
    case 8:
        return 2;
    }
    return 0;
}

void fn_80119760(Aff2* d) {
    d->v4 = (s8)(u8)(d->v4 + 1) >> 1;
    d->v5 = (s8)(u8)(d->v5 + 1) >> 1;
    d->v6 = (s8)(u8)(d->v6 + 1) >> 1;
    d->v7 = (s8)(u8)(d->v7 + 1) >> 1;
    d->v8 = (s8)(u8)(d->v8 + 1) >> 1;
    d->v9 = (s8)(u8)(d->v9 + 1) >> 1;
}

/* Support list: 12-byte entries with a pair of characters and a level. */
struct SupEnt {
    void* a;
    void* b;
    u8 c;
};

extern SupEnt lbl_80412C18[];
extern int lbl_804CB80C;
extern void* lbl_804CB808;

static inline u8 SupGet(void* a, void* b) {
    SupEnt* e = lbl_80412C18;
    u8 r = 0;
    int i;
    for (i = 0; i < lbl_804CB80C; i++, e++) {
        if ((a == e->a && b == e->b) || (a == e->b && b == e->a)) {
            r = e->c;
            break;
        }
    }
    return r;
}

#if TARGET_PC
/* host: RelianceData is used in place in the file: big-endian fields */
struct SupItem {
    FE10_BP32(void) pid;
    u8 flag;
    u8 val;
};

struct SupData {
    FE10_BP32(void) pid;
    FE10_BE32 count;
    SupItem e[1];
};
#else
struct SupItem {
    void* pid;
    u8 flag;
    u8 val;
};

struct SupData {
    void* pid;
    int count;
    SupItem e[1];
};
#endif

extern u8* fn_8010B1D8(void*);

void fn_801198C8(SupData* p, int n) {
    int j;
    SupData* q;
    int i;
    lbl_804CB808 = fn_80077064(lbl_803687C8 + 0x86);
    for (i = 0; i < n; i++) {
        q = p;
        for (j = 0; j < p->count; j++) {
            if (q->e[0].pid) {
                q->e[0].pid = fn_8010B1D8(q->e[0].pid);
            }
            q = (SupData*)((u8*)q + 8);
        }
#if TARGET_PC
        /* person struct +0xdc is a 32-bit pointer slot */
        *(FE10_P32(SupData)*)(fn_8010B1D8(p->pid) + 0xdc) = p;
#else
        *(SupData**)(fn_8010B1D8(p->pid) + 0xdc) = p;
#endif
        p = (SupData*)&p->e[p->count];
    }
}

struct SupCfg {
    u8 pad0[4];
    u8 v4;
    u8 v5;
    s8 v6;
    s8 v7;
    s8 v8;
    s8 v9;
    s8 vA;
};

struct UnitH {
    u8 pad0[0xEC];
    u8* ec;
};

void fn_8011996C(UnitH* a, UnitH* b, int k) {
    if (*(void**)(a->ec + 0xdc) && *(void**)(b->ec + 0xdc)) {
        SupCfg* c;
        s8 idx = fn_8012E9B4(a, b);
        if (idx >= 0) {
            int v;
            c = (SupCfg*)lbl_804CB808;
            switch (k) {
            case 0:
                if (fn_800607E4(lbl_803CAB38)) {
                    v = c->v5;
                } else {
                    v = c->v4;
                }
                break;
            case 1:
                v = c->v6;
                break;
            case 2:
                v = c->v7;
                break;
            case 3:
                v = c->v8;
                break;
            case 4:
                v = c->v9;
                break;
            case 5:
                v = c->vA;
                break;
            default:
                v = 0;
                break;
            }
            fn_8012EAB4(a, idx, (s8)v);
        }
    }
}

void fn_80119A88(UnitH* a, UnitH* b, int k) {
    if (*(void**)(a->ec + 0xdc) && *(void**)(b->ec + 0xdc)) {
        SupCfg* c;
        s8 idx = fn_8012E9B4(a, b);
        if (idx >= 0) {
            s8 idx2 = fn_8012E9B4(b, a);
            int v;
            s8 w;
            c = (SupCfg*)lbl_804CB808;
            switch (k) {
            case 0:
                if (fn_800607E4(lbl_803CAB38)) {
                    v = c->v5;
                } else {
                    v = c->v4;
                }
                break;
            case 1:
                v = c->v6;
                break;
            case 2:
                v = c->v7;
                break;
            case 3:
                v = c->v8;
                break;
            case 4:
                v = c->v9;
                break;
            case 5:
                v = c->vA;
                break;
            default:
                v = 0;
                break;
            }
            w = v;
            fn_8012EAB4(a, idx, w);
            fn_8012EAB4(b, idx2, w);
        }
    }
}

void fn_80119C48(void* w) {
    SupEnt* e;
    int i;
    fn_8008A5E4(w, lbl_804CB80C);
    e = lbl_80412C18;
    for (i = 0; i < lbl_804CB80C; i++) {
        fn_8008A5C0(w, *(u16*)((u8*)e->a + 0x1c));
        fn_8008A5C0(w, *(u16*)((u8*)e->b + 0x1c));
        fn_8008A5AC(w, e->c);
        e++;
    }
}

static inline void* SupMap(void* map, int id) {
    return fn_8010B1D8(fn_80244470(map, (u16)id));
}

void fn_80119CD8(Reader* r) {
    SupEnt* e;
    void* map = lbl_804CBFC8;
    int i;
    lbl_804CB80C = fn_8008A1DC(r);
    e = lbl_80412C18;
    for (i = 0; i < lbl_804CB80C; i++) {
        if (map) {
            e->a = SupMap(map, fn_8008A1B4(r));
            e->b = SupMap(map, fn_8008A1B4(r));
        } else {
            e->a = fn_8010B1B4((u16)fn_8008A1B4(r));
            e->b = fn_8010B1B4((u16)fn_8008A1B4(r));
        }
        e->c = fn_8008A1A0(r);
        e++;
    }
}

/* Condition list: flag + value pairs (+0x1F/+0x20/+0x21 counts). */
struct CondE {
    u8 flag;
    u8 pad[3];
    void* val;
};

struct CondS {
    u8 pad0[0x18];
    void* unk18;
    u8 pad1C[3];
    u8 unk1F;
    u8 n20;
    u8 n21;
    u8 pad22[2];
    CondE* e24;
    CondE* e28;
};

int fn_80119DC8(CondS* s, void* x) {
    int i;
    if (s->unk1F == 0) {
        return 0;
    }
    if (s->n20 == 0) {
        return 0;
    }
    for (i = 0; i < s->n20; i++) {
        if (s->e24[i].flag) {
            if (fn_80127650(x, s->e24[i].val)) {
                return 0;
            }
        } else {
            if (!fn_80127650(x, s->e24[i].val)) {
                return 0;
            }
        }
    }
    if (s->n21 == 0) {
        return 1;
    }
    for (i = 0; i < s->n21; i++) {
        if (s->e28[i].flag) {
            if (!fn_80127650(x, s->e28[i].val)) {
                return 1;
            }
        } else {
            if (fn_80127650(x, s->e28[i].val)) {
                return 1;
            }
        }
    }
    return 0;
}

struct Unit {
    u8 pad0[0xEC];
    void* ec;
    u8 padF0[4];
    u8* f4;
    u8 padF8[0x3F0 - 0xF8];
};

extern Unit* lbl_804CB810;

static inline Unit* UnitGet(int id) {
    id = (u8)id;
    if (id) {
        return &lbl_804CB810[id - 1];
    }
    return 0;
}

int fn_80119F24(CondS* s, void* x) {
    int r;
    if (!fn_80119DC8(s, x)) {
        return 0;
    }
    r = 1;
    if (s->unk18) {
        u8 tbl[4];
        int i;
        r = 0;
        fn_8010E41C(tbl, 4);
        for (i = 1; i <= 0xfe; i++) {
            Unit* u = UnitGet(i);
            if (u->ec && tbl[u->f4[8]]) {
                if ((s8)fn_8012C9BC(u, fn_8010B228(s->unk18)) >= 0) {
                    r = 1;
                    break;
                }
            }
        }
        if (!r && fn_801059B0()) {
            if (fn_8010536C(fn_801059B0(), s->unk18) >= 0) {
                r = 1;
            }
        }
    }
    return r;
}

char* fn_8011A028(char* const* p) {
    return strchr(*p, '_') + 1;
}

static inline char* MsgOr(void* m, char* def) {
    char* s;
    if (m == 0) {
        return def;
    }
    s = fn_800D0864(m);
    if (s) {
        return s;
    }
    return def;
}

static inline char* NameOf(struct Item* p);

struct Item {
    void* unk0;
    void* unk4;
    void* unk8;
    void* unkC;
    u8 pad10[8];
    void* unk18;
    u8 pad1C;
    u8 unk1D;
};

static inline char* NameOf(Item* p) {
    char* def = lbl_80368F70;
    if (p->unk4 == 0) {
        return def;
    }
    {
        char* s = fn_800D0864(p->unk4);
        if (s) {
            return s;
        }
        return def;
    }
}

char* fn_8011A054(const Item* p) {
    char* def = lbl_80368F70;
    if (p->unk4 == 0) {
        return def;
    }
    {
        char* s = fn_800D0864(p->unk4);
        if (s) {
            return s;
        }
        return def;
    }
}

char* fn_8011A0A8(const Item* p) {
    char* def = lbl_80368F70 + 0x1d;
    if (p->unk8 == 0) {
        return def;
    }
    {
        char* s = fn_800D0864(p->unk8);
        if (s) {
            return s;
        }
        return def;
    }
}

char* fn_8011A100(const Item* p) {
    char* def = lbl_80368F70 + 0x1d;
    if (p->unkC == 0) {
        return def;
    }
    {
        char* s = fn_800D0864(p->unkC);
        if (s) {
            return s;
        }
        return def;
    }
}

void* fn_8011A158(Item* p) {
    if (p->unk18 == 0) {
        return 0;
    }
    return fn_8010B228(p->unk18);
}

static inline int ItemIdx(Item* q) {
    int idx = (s8)q->unk1D;
    char* s;
    if (idx != -1) {
        return idx;
    }
    s = NameOf(q);
    if (s == 0) {
        return 0;
    }
    switch (*s) {
    case 'A':
    case 'E':
    case 'I':
    case 'O':
    case 'U':
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
        return 2;
    }
    return 1;
}

static inline char* ItemArticle(Item* q, void* x) {
    switch (fn_8024BC94()[0x1bc8]) {
    case 1:
        return fn_8010B384(ItemIdx(q), x);
    }
    return lbl_80368F70 + 0x42;
}

char* fn_8011A174(Item** p, void* x) {
    if (*p == 0) {
        return lbl_80368F70 + 0x42;
    }
    if ((int)fn_8024BC94()[0x1bc8] != 1) {
        return lbl_80368F70 + 0x42;
    }
    return ItemArticle(*p, x);
}

struct ItemRef {
    void* item;
    u8 v4;
    u8 v5;
};

void fn_8011A298(ItemRef* d, Reader* r) {
    u8* g = fn_8024BCA0();
    u32 id = (u16)fn_8008A1B4(r);
    if (id == 0xffff) {
        r->cur += 2;
        d->item = 0;
    } else {
        int v;
        if (lbl_804CBFC8) {
            d->item = fn_8010B23C(fn_802447A0(lbl_804CBFC8, id));
        } else {
            d->item = fn_8010B22C(id);
        }
        d->v4 = fn_8008A1A0(r);
        d->v5 = v = fn_8008A1A0(r);
        if (*(u32*)(g + 0xc) < 0xd && d->v4 == 1) {
            d->v5 = (u8)v & ~2;
        }
    }
}

}
