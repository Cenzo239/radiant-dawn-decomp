/* Round 20 draft, NOT at a counted level (check_regs.py: other): fn_800C358C. Self-contained, complete source. Instruction count ours 125 orig 126. What differs: one unreachable b missing (see NOTES round 18). */
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
void fn_8023F1A8(void*);
void fn_8023F7EC(const char*, u32);
int fn_80291188(const char*, const char*);
int fn_801D09F0();
void fn_8023F1A0(const char*, int);
int* fn_80075FB4(const char*, int);
void fn_800763E0(const char*);
char* strcpy(char*, const char*);
void fn_80291110(char*, const char*);
void fn_8023F880(const char*);
void* fn_80076F54(const char*);
int fn_80291480(const char*, const char*);

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
BOOL fn_800C3784(u32 a, int b);

BOOL fn_800C3840(const char* name, int mode);


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
void fn_800C3B1C();

BOOL fn_800C3A48(const char* name);

CmbCmd* fn_800C3BC8(CmbCmd* c);


static inline const char* CharFile() {
    int w = fn_801D09F0();
    const char* b = lbl_80365E0C;
    const char* s = b + 0x17;
    if (w != 0) {
        s = b;
    }
    return s;
}
void fn_800C3CF0();


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
void fn_800C3D30(CharTbl* t);

void fn_800C3DF0(CharTbl* t);


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
void fn_800C3E70(PidRec* r, char* out);

void fn_800C3EE0(PidRec* r, u32 flags);

void fn_800C3F64(PidRec* r);


static inline void* FindFile(const char* name) {
    void* r = fn_80076F54(name);
    if (r != NULL) {
        return r;
    }
    return fn_80076F54(lbl_80365E0C + 0x3A);
}
void* fn_800C3FD0(const char* name);


extern void* lbl_803E50D0[];
void* fn_800C400C(int i);

BOOL fn_800C4020(const char* s);


void* fn_800D0864(void*);
void* fn_800C4058(const char* name);


struct Slot {
    u8 pad[0x40];
    u8 id;
    u8 pad41[2];
    s8 m43;
};
void* fn_800C409C(s8 v);

void fn_800C4210();


void fn_80081A90(void*);
void fn_800C4240(Slot* s);

void fn_800C429C(Slot* s);

void fn_800C42F8(int i);

void fn_800C4348();


void fn_803080DC(u32, u32, u32, u32);
void fn_800C43B0(void* a, u32 v);


} // extern "C"


#pragma use_lmw_stmw off
/* ---- from rG_800A3D88/wip/fn_800C358C.cpp ---- */
extern "C" {
// 1 word short: original has an unreachable `b end` after the first infinite loop. Everything else matches. Needs Swap32/Swap16 from fn_800C358C.cpp.
void fn_800C358C(CmbFile* f, int swapped) {
    if (swapped) {
        for (int i = 0;; i++) {
            CmbCmd* c = f->cmds[i];
            if (c == NULL) {
                return;
            }
            if (c->name != NULL) {
                fn_80076D48(c->name, c);
            }
            continue;
            return;
        }
    } else {
        if (f->m24 != 0) {
            f->m24 += (u32)f;
        }
        if (f->cmds != NULL) {
            f->cmds = (CmbCmd**)((u32)f->cmds + (u32)f);
        }
        f->m20 = lbl_804CB6A6;
        lbl_804CB6A6 += f->m22;
        if (lbl_804CB6A6 > lbl_804CB6A4) {
            lbl_804CB6B8 = 8;
            return;
        }
        for (int i = 0;; i++) {
            if (f->cmds[i] == NULL) {
                return;
            }
            Swap32(&f->cmds[i]);
            f->cmds[i] = (CmbCmd*)((u32)f + (u32)f->cmds[i]);
            CmbCmd* c = f->cmds[i];
            Swap32(&c->name);
            Swap32(&c->name2);
            Swap16(&c->m12);
            Swap16(&c->m10);
            if (c->mc != 0) {
                u16* a = c->args;
                for (int j = 0; j < c->me; j++, a++) {
                    Swap16(a);
                }
            }
            c->file = f;
            if (c->name != NULL) {
                c->name += (u32)f;
                fn_80076D48(c->name, c);
            }
            if (c->name2 != NULL) {
                c->name2 += (u32)f;
            }
        }
    }
}
}
