/* CRC32 and the NAND save-file process. */
#include "game/rJ_800799AC/proc.h"

struct SaveFile {
    u8 buf[0xA000];
    int fd;        /* 0xA000 */
    volatile int result; /* 0xA004 written by NAND callbacks */
    int size;      /* 0xA008 stat result */
    u8 padA00C[0xC];
    u8 opened;     /* 0xA018 */
    u8 dirOpen;    /* 0xA019 */
    u8 busy;       /* 0xA01A */
    u8 padA01B;
    u8 cmdBlock[0x14]; /* 0xA01C */
    u32 tick;      /* 0xA030 */
    void* data;    /* 0xA034 */
};

extern "C" {

extern SaveFile lbl_803CD8E0;
extern const char lbl_80362390[];
extern u8 lbl_803808A0[];
extern u8 lbl_803808F0[];

void fn_80083DC4(Proc* p, int label);
Proc* fn_80081050(void* script, Proc* parent);
Proc* fn_80081194(void* script, Proc* parent);
void fn_80081A90(Proc* p);
int fn_802F55B0(int fd, int index, char* name);
int fn_80291188(const char* a, const char* b);
int fn_8028E6E0(const char* a, const char* b, int n);
int fn_802F4E04(int fd, int index, void* out);
int fn_802F1C8C(int fd);
int fn_802F4318(int a, int b, int* out);
int fn_802F4A64(int fd, void* buf, void (*a)(int), void (*b)(int));
int fn_802F4224(int fd, void (*cb)(int));
int fn_802F531C(void* block, void* data, int size, int x, void (*cb)(int));
int fn_802F4FE8(void* block);
int fn_802F4C08(int fd);
u32 OSGetTick(void);

/* Build the CRC32 table */
void fn_800799AC(u32* table) {
    int i;
    int j;
    u32 c;
    for (i = 0; i < 0x100; i++) {
        c = i;
        for (j = 0; j < 8; j++) {
            if (c & 1) {
                c = (c >> 1) ^ 0xEDB88320;
            } else {
                c >>= 1;
            }
        }
        *table++ = c;
    }
}

/* CRC32 */
u32 fn_80079A6C(u32* table, const u8* data, int len) {
    u32 c = 0xFFFFFFFF;
    int i;
    for (i = 0; i < len; i++) {
        c = (c >> 8) ^ table[(c ^ data[i]) & 0xFF];
    }
    return c ^ 0xFFFFFFFF;
}

#pragma use_lmw_stmw on
/* Find a directory entry and open it */
int fn_80079BE4(int fd, const char* name, void* out) {
    struct {
        char name[0x28];
        char kind[4];
        char ext[2];
        u8 pad[0x70 - 0x2E];
    } e;
    int found = -1;
    int i;
    int r;
    for (i = 0; i < 0x7F && found < 0; i++) {
        r = fn_802F55B0(fd, i, e.name);
        switch (r) {
        case -4:
        case -10:
            break;
        case 0:
            if (fn_80291188(e.name, name) == 0 &&
                fn_8028E6E0(e.kind, lbl_80362390, 4) == 0 &&
                fn_8028E6E0(e.ext, lbl_80362390 + 5, 2) == 0) {
                found = i;
            }
            break;
        default:
            return r;
        }
    }
    if (found >= 0) {
        return fn_802F4E04(fd, found, out);
    }
    return -4;
}
#pragma use_lmw_stmw off

int fn_80079D60(void) {
    int t = 1;
    if (lbl_803CD8E0.result != -1 && lbl_803CD8E0.busy == 0) {
        t = 0;
    }
    return t;
}

void fn_80079D90(int);

void fn_80079DD8(int) {
    lbl_803CD8E0.opened = 0;
    lbl_803CD8E0.dirOpen = 0;
    lbl_803CD8E0.busy = 0;
    lbl_803CD8E0.result = -3;
}

int fn_80079E00(Proc* p) {
    if (lbl_803CD8E0.result < 0) {
        fn_80083DC4(p, 0x63);
        lbl_803CD8E0.busy = 0;
        return 1;
    }
    return 0;
}

int fn_80079E5C(void) {
    return lbl_803CD8E0.result;
}

void fn_80079E70(int r) {
    lbl_803CD8E0.result = r;
}

int fn_80079E84(const char* s) {
    return fn_80291188(s, lbl_80362390 + 0x1B2) != 0;
}

static inline BOOL isDone(void) {
    int t = 1;
    if (lbl_803CD8E0.result != -1 && lbl_803CD8E0.busy == 0) {
        t = 0;
    }
    return t;
}

static inline BOOL isOk(void) {
    int t = 0;
    if (lbl_803CD8E0.result == 0 && lbl_803CD8E0.busy == 0) {
        t = 1;
    }
    return t;
}


int fn_80079EBC(Proc* p) {
    lbl_803CD8E0.fd = 0;
    lbl_803CD8E0.opened = 0;
    lbl_803CD8E0.dirOpen = 0;
    lbl_803CD8E0.busy = 0;
    lbl_803CD8E0.result = fn_802F4318(lbl_803CD8E0.fd, 0, &lbl_803CD8E0.size);
    if (isDone()) {
        return 1;
    }
    if (!isOk()) {
        fn_80083DC4(p, 0x63);
        return 1;
    }
    return isDone();
}

void fn_80079FC8(Proc* p) {
    if (!isOk()) {
        fn_80083DC4(p, 0x63);
        return;
    }
    if (lbl_803CD8E0.size != 0x2000) {
        lbl_803CD8E0.result = -0x41;
        fn_80083DC4(p, 0x63);
        return;
    }
    lbl_803CD8E0.busy = 1;
    lbl_803CD8E0.result = fn_802F4A64(lbl_803CD8E0.fd, lbl_803CD8E0.buf, fn_80079DD8, fn_80079D90);
}

void fn_8007A084(Proc* p) {
    switch (lbl_803CD8E0.result) {
    case 0:
    case -6:
        lbl_803CD8E0.busy = 1;
        lbl_803CD8E0.result = fn_802F4224(lbl_803CD8E0.fd, fn_80079D90);
        if (lbl_803CD8E0.result < 0) {
            fn_80083DC4(p, 0x50);
        }
        break;
    }
}

void fn_8007A120(void) {
    switch (lbl_803CD8E0.result) {
    case 0:
        lbl_803CD8E0.opened = 1;
        break;
    case -6:
    case -13:
        lbl_803CD8E0.opened = 1;
        break;
    }
}

void fn_8007A174(void) {
    lbl_803CD8E0.tick = OSGetTick();
}

Proc* fn_8007A1A4(Proc* parent) {
    if (parent == 0) {
        return fn_80081050(lbl_803808A0, (Proc*)2);
    }
    return fn_80081194(lbl_803808A0, parent);
}

static inline BOOL checkError(Proc* p) {
    if (lbl_803CD8E0.result < 0) {
        fn_80083DC4(p, 0x63);
        lbl_803CD8E0.busy = 0;
        return 1;
    }
    return 0;
}

void fn_8007A2E0(Proc* p) {
    if (checkError(p)) {
        return;
    }
    if (lbl_803CD8E0.dirOpen != 0) {
        fn_802F4FE8(lbl_803CD8E0.cmdBlock);
        lbl_803CD8E0.dirOpen = 0;
    }
    if (lbl_803CD8E0.opened != 0) {
        if (lbl_803CD8E0.opened != 0) {
            fn_802F4C08(lbl_803CD8E0.fd);
            lbl_803CD8E0.opened = 0;
        }
    }
    lbl_803CD8E0.tick = OSGetTick() - lbl_803CD8E0.tick;
}

Proc* fn_8007A3BC(void* data, Proc* parent) {
    lbl_803CD8E0.data = data;
    return fn_80081194(lbl_803808F0, parent);
}


/* Small heap block object */
struct Block {
    void* p;   /* 0x00 */
    void* end; /* 0x04 */
    void* v8;  /* 0x08 */
    u8 owns;   /* 0x0C */
    u8 pad[3];
    void* vt;  /* 0x10 */
};

extern u8 lbl_80380940[];
void fn_80078E24(void* p);
void fn_80079210(void* p);

static inline void blockDtor(Block* b) {
    if (b != 0) {
        b->vt = lbl_80380940;
        if (b->owns != 0) {
            fn_80078E24(b->p);
            b->p = 0;
            b->owns = 0;
        }
    }
}

Block* fn_80079CE0(Block* b, int del) {
    if (b != 0) {
        blockDtor(b);
        if (del > 0) {
            fn_80079210(b);
        }
    }
    return b;
}

Block* fn_8007A3D8(Block* b, int del) {
    if (b != 0) {
        b->vt = lbl_80380940;
        if (b->owns != 0) {
            fn_80078E24(b->p);
            b->p = 0;
            b->owns = 0;
        }
        if (del > 0) {
            fn_80079210(b);
        }
    }
    return b;
}

void* fn_8007A454(Block* b) {
    return b->p;
}

Block* fn_8007A45C(Block* b, int del) {
    if (b != 0) {
        blockDtor(b);
        if (del > 0) {
            fn_80079210(b);
        }
    }
    return b;
}

void* fn_8007A4DC(Block* b) {
    return b->end;
}

int fn_8007A4E4(Block* b) {
    return (int)b->end - (int)b->p;
}

void* fn_8007A4F4(Block* b) {
    return b->v8;
}

void* fn_80079940(int size, int align);
void fn_80079978(void* p);

void* fn_8007A4FC(int size) {
    return fn_80079940(size, 0x40);
}

int fn_8007A504(void* p) {
    fn_80079978(p);
    return 1;
}

extern int lbl_804CB5BC;

/* Controller object fields */
void fn_8007A6A8(u8* o, int v) {
    *(int*)(o + 0xC) = v;
    *(int*)(o + 0x10) = 0;
    *(int*)(o + 0x14) = 0;
    *(int*)(o + 0x18) = 0;
    *(int*)(o + 0x1C) = 0;
    *(int*)(o + 0x20) = 0;
    *(int*)(o + 0x24) = 0;
    *(int*)(o + 0x28) = 0;
    *(int*)(o + 0x2C) = 0;
    *(int*)(o + 0x30) = 0;
    *(int*)(o + 0x34) = 0;
    *(s16*)(o + 0x44) = 0;
    *(s16*)(o + 0x46) = 0;
    *(s16*)(o + 0x48) = 0;
    *(s16*)(o + 0x4A) = 0;
    *(s16*)(o + 0x4C) = 0;
    *(s16*)(o + 0x4E) = 0;
    *(s16*)(o + 0x50) = 0;
    *(s16*)(o + 0x52) = 0;
    *(int*)(o + 0x38) = 0xC;
    *(int*)(o + 0x3C) = 4;
    *(int*)(o + 0x40) = 0x23;
    *(int*)(o + 0x54) = 0;
    *(int*)(o + 0x58) = 0;
}

void fn_8007A71C(u8* o, int v) {
    *(int*)(o + 4) = v;
}

void fn_8007A724(u8* o, int v) {
    *(int*)(o + 8) = v;
}

int fn_8007A72C(u8* o) {
    return *(int*)(o + 4);
}

void fn_8007A83C(int m) {
    lbl_804CB5BC |= m;
}

void fn_8007A84C(int m) {
    lbl_804CB5BC &= ~m;
}

int fn_8007A85C(int m) {
    return lbl_804CB5BC & m;
}

}
