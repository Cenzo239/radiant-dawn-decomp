#include "game/rS_8023FD30/types.h"

/* Small functions from the UI and save code, in address order. */

extern "C" {
void fn_8017F44C(void*, s32, u32);
s64 OSGetTime(void);
void fn_80109744(void*);
void fn_801095FC(void*);
void* fn_801E5640(void*, s32, s32);
void fn_80083DC4(void*, s32);
extern u8 lbl_803CA870[];
extern char lbl_803728A8[];
extern char lbl_80391150[];
}

class VData {
public:
    u8 pad00[0x40];
    virtual void destroy(int);
};

struct Sys0 {
    u32 v00;
    u32 v04;
    u32 v08;
    u32 v0C;
    u32 v10;
    u32 v14;
    u32 v18;
    u32 v1C;
    s64 time;
    u32 v28;
    u32 v2C;
    u8 v30;
    u8 v31;
    s8 v32;
    u8 pad33;
    u8 v34;
    u8 v35;
    u8 pad36[0xA];
    u32 v40;
    u8 v44[0x11];
    u8 v55;
    u8 pad56[0x1A];
    u8 v70[0x1000];
};

class VCall {
public:
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2C();
};

struct Sys2 {
    u32 v00;
    u32 v04;
    u32 v08;
    u32 v0C;
    u32 v10;
    u32 v14;
    u8 pad18[0x1A];
    s8 v32;
    u8 pad33[9];
    void* vt3C;
    u32 v40;
    u8 v44[0x2C];
    u8 v70[0x1000];
};

struct Hdr {
    u64 magic;
    u32 date;
};

struct Rect {
    u8 pad00[0xA];
    s16 x0;
    s16 y0;
    s16 x1;
    s16 y1;
    s16 a;
    s16 b;
    s16 c;
    s16 d;
    u8 pad1A[4];
    s16 e;
    s16 f;
};

#define ZERO_SYS(s) \
    (s)->v04 = -1; \
    (s)->v00 = -1; \
    (s)->v08 = -1; \
    (s)->v0C = -1; \
    (s)->v14 = 0; \
    (s)->v10 = 0; \
    (s)->v32 = -1; \
    (s)->v40 = 0;

extern "C" {

void fn_802414B4(VCall* v) {
    v->v24();
}

void fn_80241ED0(VData* d) {
    d->destroy(-1);
}

void fn_802420CC(void* p) {
    u8* o = (u8*)fn_801E5640(p, 0x80, 0);
    *(const char**)(o + 0x40) = lbl_803728A8;
    const char* s = lbl_803728A8 + 0x14;
    u8* q = (u8*)fn_801E5640(p, -0x1000, 0);
    if (q != 0) {
        *(const char**)(q + 0x64) = s;
    }
}

void fn_80242514(void* p) {
    switch (lbl_803CA870[0xC]) {
    case 0x80:
        break;
    case 0x81:
        fn_80083DC4(p, 6);
        break;
    }
}

BOOL fn_802450BC(Hdr* h) {
    BOOL ok = 0;
    if (h->magic == 0x4645313041535953ULL && h->date == 0x20061002) {
        ok = 1;
    }
    return ok;
}

Sys2* fn_80245C88(Sys2* s) {
    s->vt3C = lbl_80391150;
    fn_801095FC(s->v44);
    ZERO_SYS(s)
    fn_8017F44C(s->v70, -1, 0x1000);
    return s;
}

#pragma use_lmw_stmw on
void fn_80245D00(Sys0* s, u8 a, u8 b, u8 c) {
    s->v04 = 0x41444154;
    s->v00 = 0x46453130;
    s->v08 = 0x20060920;
    s->v0C = 0x11;
    s->v14 = 0;
    s->v10 = 0;
    s->v18 = 0;
    s->v1C = 0;
    s->time = OSGetTime();
    s->v2C = 0;
    s->v28 = 0;
    s->v30 = c;
    s->v31 = a;
    s->v32 = -1;
    s->v34 = 1;
    s->v35 = b;
    s->v40 = 0;
    fn_80109744(s->v44);
    s->v55 = b;
    fn_8017F44C(s->v70, -1, 0x1000);
}

#pragma use_lmw_stmw off

void fn_80245DC4(Sys2* s) {
    ZERO_SYS(s)
    fn_8017F44C(s->v70, -1, 0x1000);
}

BOOL fn_80245DFC(Hdr* h) {
    BOOL ok = 0;
    if (h->magic == 0x4645313041444154ULL && h->date == 0x20060920) {
        ok = 1;
    }
    return ok;
}

}
