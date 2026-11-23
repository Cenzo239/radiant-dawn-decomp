#include "game/rG_800A3D88/types.h"

// Script bytecode (.cmb) container and script command table. A .cmb file holds a
// header with a table of command records; numbers are big-endian on disk except
// for files with the byte-swapped flag.

#pragma auto_inline off

extern "C" {

struct CmbCmd {
    const char* name;
    const char* name2;
    struct CmbFile* file;
    s8 mc;
    u8 md;
    s8 me;
    u8 pad_f;
    s16 m10;
    u16 m12;
    u16 args[1];
};

struct CmbFile {
    char magic[4];
    char title[0x18];
    CmbFile* next;
    u16 m20;
    u16 m22;
    u32 m24;
    CmbCmd** cmds;
};

extern CmbFile* lbl_804CB6A0;
extern u16 lbl_804CB6A4;
extern u16 lbl_804CB6A6;
extern void* lbl_804CB6A8;
extern s16 lbl_804CB6AC;
extern s16 lbl_804CB6AE;
extern CmbCmd* lbl_804CB6B0;
extern u32 lbl_804CB6B8;
extern char lbl_80365E0C[];

void fn_80076D48(const char*, CmbCmd*);
void fn_80077174(const char*);
void* fn_80079940(u32, int);
void fn_8017F44C(void*, int, u32);
u32 fn_8023F7B8(const char*);
CmbFile* fn_8023F1A4(const char*, int);
#if TARGET_PC
FE10_PROTO void fn_8023F1A8(ptr32<const void>);
#else
void fn_8023F1A8(void*);
#endif
void fn_8023F7EC(const char*, u32);
int fn_80291188(const char*, const char*);
int fn_801D09F0();
void fn_8023F1A0(const char*, int);
int* fn_80075FB4(const char*, int);
void fn_800763E0(const char*);
char* strcpy(char*, const char*);
void fn_80291110(char*, const char*);
#if TARGET_PC
FE10_PROTO int fn_8023F880(const char*);
#else
void fn_8023F880(const char*);
#endif
void* fn_80076F54(const char*);
#if TARGET_PC
FE10_PROTO char * fn_80291480(const char*, const char*);
#else
int fn_80291480(const char*, const char*);
#endif

static inline void Swap32(void* v) {
    u8* p = (u8*)v;
    u8 a, b, c;
    c = p[2];
    b = p[1];
    a = p[0];
    p[0] = p[3];
    p[1] = c;
    p[2] = b;
    p[3] = a;
}

static inline void Swap16(void* v) {
    u8* p = (u8*)v;
    u8 a = p[0];
    p[0] = p[1];
    p[1] = a;
}

void fn_800C358C(CmbFile*, int);

BOOL fn_800C3784(u32 a, int b) {
    lbl_804CB6A4 = a;
    lbl_804CB6B8 = 0;
    lbl_804CB6A0 = NULL;
    lbl_804CB6A6 = 0;
    lbl_804CB6A8 = fn_80079940(a * 4, 0x40);
    if (lbl_804CB6A8 == NULL) {
        lbl_804CB6B8 = 4;
        return 0;
    }
    lbl_804CB6AC = b;
    lbl_804CB6AE = 0;
    u32 sz = b * 16;
    lbl_804CB6B0 = (CmbCmd*)fn_80079940(sz, 0x40);
    fn_8017F44C(lbl_804CB6B0, 0, sz);
    if (lbl_804CB6B0 == NULL) {
        lbl_804CB6B8 = 4;
        return 0;
    }
    return 1;
}

BOOL fn_800C3840(const char* name, int mode) {
    u32 flag = (fn_8023F7B8(name) >> 22) & 1;
    CmbFile* f = fn_8023F1A4(name, mode);
    if (flag == 0) {
        u8* p = (u8*)f;
        Swap32(p + 0x18);
        Swap32(p + 0x1C);
        Swap16(p + 0x22);
        Swap32(p + 0x24);
        Swap32(p + 0x28);
    }
    lbl_804CB6B8 = 0;
    CmbFile* h = lbl_804CB6A0;
    if (h == NULL) {
        lbl_804CB6A0 = f;
    } else {
        CmbFile* n;
        while ((n = h->next) != NULL) {
            h = n;
        }
        h->next = f;
    }
    fn_800C358C(f, flag);
    fn_8023F7EC(name, 0x400000);
    return 1;
}

static inline void UnregCmds(CmbFile* f) {
    for (int i = 0;; i++) {
        CmbCmd* c = f->cmds[i];
        if (c == NULL) {
            break;
        }
        if (c->name != NULL) {
            fn_80077174(c->name);
        }
    }
}

void fn_800C3B1C() {
    for (CmbFile* f = lbl_804CB6A0; f != NULL; f = f->next) {
        if (f->magic[0] == 'c' && f->magic[1] == 'm' && f->magic[2] == 'b' && f->magic[3] == 'S') {
            f->magic[3] = ' ';
            for (int i = 0;; i++) {
                CmbCmd* c = f->cmds[i];
                if (c == NULL) {
                    break;
                }
                if (c->name != NULL) {
                    fn_80076D48(c->name, c);
                }
            }
        }
    }
}

BOOL fn_800C3A48(const char* name) {
    CmbFile* f;
    if (name == NULL || *name == 0) {
        f = lbl_804CB6A0;
        CmbFile* n;
        while ((n = f->next) != NULL) {
            f = n;
        }
        if (f == NULL) {
            return 0;
        }
    } else {
        for (f = lbl_804CB6A0; f != NULL; f = f->next) {
            if (fn_80291188(f->title, name) == 0) {
                goto found;
            }
        }
        return 0;
    }
found:
    f->magic[3] = 'S';
    for (int i = 0;; i++) {
        CmbCmd* c = f->cmds[i];
        if (c == NULL) {
            break;
        }
        if (c->name != NULL) {
            fn_80077174(c->name);
        }
    }
    return 1;
}

CmbCmd* fn_800C3BC8(CmbCmd* c) {
    if (c == NULL) {
        return lbl_804CB6A0->cmds[0];
    }
    CmbFile* f = c->file;
    CmbCmd* n = f->cmds[c->m10 + 1];
    if (n != NULL) {
        return n;
    }
    for (f = f->next; f != NULL; f = f->next) {
        if (f->magic[3] != 'S') {
            break;
        }
    }
    if (f == NULL) {
        return NULL;
    }
    return f->cmds[0];
}

static inline const char* CharFile() {
    int w = fn_801D09F0();
    const char* b = lbl_80365E0C;
    const char* s = b + 0x17;
    if (w != 0) {
        s = b;
    }
    return s;
}

void fn_800C3CF0() {
    fn_8023F1A0(CharFile(), 0xC20);
}

struct CharEntry {
    const char* name;
    u8 pad[0x20 - 4];
    u16 flags;
    u8 pad22[0x30 - 0x22];
};

struct CharTbl {
    int n;
    u32 base;
};

void fn_800C3D30(CharTbl* t) {
    int* h = fn_80075FB4(CharFile(), 0x20);
    t->n = h[0];
    t->base = h[1];
    CharEntry* e;
    int off;
    int i;
    i = 0;
    off = 0;
    for (; i < t->n; off += 0x30, i++) {
        e = (CharEntry*)(t->base + off);
        fn_80076D48(*(const char**)(t->base + off), (CmbCmd*)e);
        if (e->flags & 4) {
            fn_80076D48(*(const char**)((u8*)e + 4), (CmbCmd*)e);
        }
    }
}

void fn_800C3DF0(CharTbl* t) {
    {
        int w = fn_801D09F0() == 0;
        const char* b = lbl_80365E0C;
        const char* s = b + 0x17;
        if (w) {
            s = b;
        }
        fn_800763E0(s);
    }
    int* h = fn_80075FB4(CharFile(), 0x20);
    t->n = h[0];
    t->base = h[1];
}

struct PidRec {
    u8 pad[0xC];
    const char* pid;
};

static inline const char* PathFmt() {
    int w = fn_801D09F0();
    const char* b = lbl_80365E0C;
    const char* s = b + 0x34;
    if (w != 0) {
        s = b + 0x29;
    }
    return s;
}

static inline void MakePath2(PidRec* r, char* out) {
    char tmp[0x40];
    strcpy(tmp, PathFmt());
    fn_80291110(tmp, r->pid);
    strcpy(out, tmp);
}

void fn_800C3E70(PidRec* r, char* out) {
    MakePath2(r, out);
}

void fn_800C3EE0(PidRec* r, u32 flags) {
    char out[0x40];
    MakePath2(r, out);
    fn_8023F1A0(out, (u16)(flags & ~0x40) | 0x80);
}

#if TARGET_PC
int fn_800C3F64(PidRec* r) {
    char out[0x40];
    MakePath2(r, out);
    return fn_8023F880(out);
}
#else
void fn_800C3F64(PidRec* r) {
    char out[0x40];
    MakePath2(r, out);
    fn_8023F880(out);
}
#endif

static inline void* FindFile(const char* name) {
    void* r = fn_80076F54(name);
    if (r != NULL) {
        return r;
    }
    return fn_80076F54(lbl_80365E0C + 0x3A);
}

void* fn_800C3FD0(const char* name) {
    return FindFile(name);
}

extern void* lbl_803E50D0[];

void* fn_800C400C(int i) {
    return lbl_803E50D0[i];
}

BOOL fn_800C4020(const char* s) {
    return fn_80291480(s, lbl_80365E0C + 0x44) != 0;
}

void* fn_800D0864(void*);

void* fn_800C4058(const char* name) {
    return fn_800D0864(*(void**)((u8*)FindFile(name) + 8));
}

struct Slot {
    u8 pad[0x40];
    u8 id;
    u8 pad41[2];
    s8 m43;
};

void* fn_800C409C(s8 v) {
    int k = v;
    if (k < 0) {
        return NULL;
    }
    void** t;
    Slot* s;
    int i;
    t = lbl_803E50D0;
    i = 0;
    for (; i < 8; t++, i++) {
        s = (Slot*)*t;
        if (s != NULL && k == s->m43) {
            return lbl_803E50D0[i];
        }
    }
    return NULL;
}

void fn_800C4210() {
    lbl_803E50D0[0] = NULL;
    lbl_803E50D0[1] = NULL;
    lbl_803E50D0[2] = NULL;
    lbl_803E50D0[3] = NULL;
    lbl_803E50D0[4] = NULL;
    lbl_803E50D0[5] = NULL;
    lbl_803E50D0[6] = NULL;
    lbl_803E50D0[7] = NULL;
}

void fn_80081A90(void*);

void fn_800C4240(Slot* s) {
    if (s != NULL) {
        void** p = &lbl_803E50D0[s->id];
        if (*p != NULL) {
            fn_80081A90(*p);
        }
        *p = NULL;
    }
}

void fn_800C429C(Slot* s) {
    if (s != NULL) {
        void** p = &lbl_803E50D0[s->id];
        if (*p != NULL) {
            fn_80081A90(*p);
        }
        *p = NULL;
    }
}

void fn_800C42F8(int i) {
    if (lbl_803E50D0[i] != NULL) {
        fn_80081A90(lbl_803E50D0[i]);
    }
    lbl_803E50D0[i] = NULL;
}

void fn_800C4348() {
    void* z = NULL;
    void** t = lbl_803E50D0;
    for (int i = 0; i < 8; i++, t++) {
        if (*t != NULL) {
            fn_80081A90(*t);
        }
        *t = z;
    }
}

void fn_803080DC(u32, u32, u32, u32);

void fn_800C43B0(void* a, u32 v) {
    fn_803080DC(v >> 16, 0, v & 0xFFFF, 0x1E0);
}

} // extern "C"
