/* Title-card banner process, event message display flags, 8014C9F8..8014D370. */
#include "game/rM_8014C9F8/types.h"
#pragma auto_inline off

struct Banner : Proc {
    char str[0x20];  /* 0x30 */
    u32 id;          /* 0x50 */
    s16 x;           /* 0x54 */
    s16 y;           /* 0x56 */
    u8 fadeFrom;     /* 0x58 */
    u8 fadeTo;       /* 0x59 */
    u8 fadeCur;      /* 0x5A */
    u8 fadeLen;      /* 0x5B */
    u8 alpha;        /* 0x5C */
    u8 width;        /* 0x5D */
};

struct Fade : Proc {
    u8* target;      /* 0x30 */
    u8 from;         /* 0x34 */
    u8 to;           /* 0x35 */
    u8 cur;          /* 0x36 */
    u8 len;          /* 0x37 */
};

struct Saved {
    u32 w;
    u16 h;
};

extern "C" {

extern u32 lbl_804CB700;
extern Saved lbl_804CB878;
extern u8 lbl_80386C80[];
extern u8 lbl_80386CBC[];
extern char lbl_80369C20[];
#if TARGET_PC
FE10_PROTO extern void *lbl_804CB888;
#else
extern u8 lbl_804CB888[];
#endif
extern char lbl_80369C30[];
class Pad5B8 {
public:
    virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34();
    virtual void v38(); virtual void v3C(); virtual void v40(); virtual void v44();
    virtual u32 v48();
};
extern Pad5B8* lbl_804CB5B8;

extern void fn_80079210(void*);
extern void fn_80079474(void*);
extern void fn_800068A0(void*, char*);
extern void fn_80006A2C(void*);
extern f32 fn_8017F68C(int, f32, f32, f32, f32);
#if TARGET_PC
extern FE10_PROTO char* fn_800C4058(p32arg);
#else
extern char* fn_800C4058(u32);
#endif
extern int fn_800CA3DC(char*, int, f32);
extern char* strcpy(char*, const char*);
#if TARGET_PC
extern FE10_PROTO int fn_80291188(const char*, const char*);
#else
extern int fn_80291188(u32, u32);
#endif

struct Blk {
    u32 a;
    u32 owned : 1;
    u32 b : 31;
    u32 c;
    void* d;
};

Blk* fn_8014C9F8(Blk* p, int del) {
    if (p != NULL) {
        if ((u8*)p + 4 != NULL && p->owned) {
            fn_80079210(p->d);
        }
        if (del > 0) {
            fn_80079210(p);
        }
    }
    return p;
}

void fn_8014CA64(u32* p, u32 m) { *p &= ~m; }
u32 fn_8014CA74(u32* p, u32 m) { return *p & m; }
void fn_8014CA80(u32* p, u32 m) { *p |= m; }
void fn_8014CA90(u32* p, u32 m) { *p ^= m; }
void fn_8014CAA0(u8* p, u32 m) { *(u32*)(p + 0x48) &= ~m; }
void fn_8014CAB0(u8* p, u32 m) { *(u32*)(p + 0x48) |= m; }
void fn_8014CAC0(void* p) { fn_8008319C(p); }
void fn_8014CAC4(u8* p, u8 v) { p[0x64] = v; }
void fn_8014CACC(u8* p) { p[0x57] = 1; }
void fn_8014CAD8(u8* p) { p[0x57] = 0; }
f32 fn_8014CAE4(void) { return 16.666666f; }

void fn_8014CAEC(Banner* b) {
    b->fadeFrom = 0;
    b->fadeTo = 0xFF;
    b->fadeCur = 0;
    b->fadeLen = 8;
    b->sleep = 8;
}

void fn_8014CB10(Banner* b) {
    b->fadeFrom = fn_8017F68C(0, b->fadeFrom, b->fadeTo, b->fadeCur, b->fadeLen);
    b->fadeTo = 0;
    b->fadeCur = 0;
    b->fadeLen = 8;
    b->sleep = 8;
}

void fn_8014CBB8(Banner* b) { b->fadeCur++; }

void fn_8014CEBC(u32 id, int x, int y, void* parent) {
    Banner* b = (Banner*)fn_80083B84(lbl_80386C80);
    if (b != NULL) {
        if (b->id == id && b->x == x && b->y == y) {
            return;
        }
        fn_80081A90(b);
    }
    if (!(lbl_804CB878.w & 0x40)) {
        b = (Banner*)fn_80081050(lbl_80386C80, parent);
        b->id = id;
        strcpy(b->str, fn_800C4058(id));
        b->x = x;
        b->y = y;
        b->width = fn_800CA3DC(b->str, -1, 1.0f);
    }
}

void fn_8014CF98(void) {
    Proc* p;
    if (lbl_804CB878.w & 0x40) {
        return;
    }
    p = fn_80083B84(lbl_80386C80);
    if (p != NULL) {
        if (lbl_804CB700 & 3) {
            fn_80081A90(p);
        } else {
            fn_80083B78(p);
        }
    }
}



u32 fn_8014D070(
#if TARGET_PC
const char* id
#else
u32 id
#endif
) {
    Banner* b;
    if (lbl_804CB878.w & 0x40) {
        return 0;
    }
    b = (Banner*)fn_80083B84(lbl_80386C80);
    if (b == NULL) {
        return 0;
    }
#if TARGET_PC
    return fn_80291188(id, (const char*)fe10_p32(b->id)) == 0;
#else
    return fn_80291188(id, b->id) == 0;
#endif
}

void fn_8014D0DC(Fade* f) {
    f->cur++;
    int v = fn_8017F68C(0, f->from, f->to, f->cur, f->len);
    u8* t = f->target;
    if (v > 0xFF) {
        v = 0xFF;
    }
    if (v < 0) {
        v = 0;
    }
    t[0x41] = v;
    if (f->cur == f->len) {
        fn_80083B78(f);
    }
}

void fn_8014D1AC(u8* target, u32 to) {
    u8 from = target[0x41];
    if (from != to) {
        Fade* f = (Fade*)fn_80081050(lbl_80386CBC, target);
        f->target = target;
        f->cur = 0;
        f->len = 4;
        f->from = from;
        f->to = to;
    }
}


void fn_8014D220(u32* p) {
    u32 v = p[0];
    int on;
    Banner* b;
    if (v & 8) {
        return;
    }
    if (v & 0x2000) {
        return;
    }
    if (v & 0x30000) {
        return;
    }
    if (lbl_804CB700 & 4) {
        return;
    }
    if (!(lbl_804CB5B8->v48() & 0x800)) {
        return;
    }
    if (fn_80085708(lbl_80369C20) != NULL) {
        return;
    }
    if (lbl_804CB700 & 3) {
        on = 0;
    } else {
        b = (Banner*)fn_80083B84(lbl_80386C80);
        if (b == NULL) {
            on = 0;
        } else if (b->alpha == 0 || b->alpha == 0xFF) {
            on = 0;
        } else {
            on = 1;
        }
    }
    if (on == 0 && *(u16*)(p + 1) >= 3) {
        p[0] |= 4;
    }
}

void fn_8014D310(u32* p) {
    u32 t = lbl_804CB878.w >> 1 & 1;
    p[0] = 0;
    if (t) {
        lbl_804CB878.w |= 2;
    }
    *(u16*)(p + 1) = 0;
    lbl_804CB700 &= ~0x8002;
}

void fn_8014D350(u32* p) { *p &= ~0x130; }
void fn_8014D364(u32* p) { *p = 0; }

}
