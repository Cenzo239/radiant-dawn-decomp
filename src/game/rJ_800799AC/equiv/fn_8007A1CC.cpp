/* Round 20, functionally equal (check_regs.py: sched): fn_8007A1CC. Self-contained. fn_800799AC.cpp with exported bodies removed plus the draft from wip/fn_80079D90.cpp. Moved (harmless): li r6,0 (constant argument) scheduled two slots earlier. */
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
void fn_800799AC(u32* table);

u32 fn_80079A6C(u32* table, const u8* data, int len);


#pragma use_lmw_stmw on

int fn_80079BE4(int fd, const char* name, void* out);

#pragma use_lmw_stmw off

int fn_80079D60(void);


void fn_80079D90(int);
void fn_80079DD8(int);

int fn_80079E00(Proc* p);

int fn_80079E5C(void);

void fn_80079E70(int r);

int fn_80079E84(const char* s);


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
int fn_80079EBC(Proc* p);

void fn_80079FC8(Proc* p);

void fn_8007A084(Proc* p);

void fn_8007A120(void);

void fn_8007A174(void);

Proc* fn_8007A1A4(Proc* parent);


static inline BOOL checkError(Proc* p) {
    if (lbl_803CD8E0.result < 0) {
        fn_80083DC4(p, 0x63);
        lbl_803CD8E0.busy = 0;
        return 1;
    }
    return 0;
}
void fn_8007A2E0(Proc* p);

Proc* fn_8007A3BC(void* data, Proc* parent);



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
Block* fn_80079CE0(Block* b, int del);

Block* fn_8007A3D8(Block* b, int del);

void* fn_8007A454(Block* b);

Block* fn_8007A45C(Block* b, int del);

void* fn_8007A4DC(Block* b);

int fn_8007A4E4(Block* b);

void* fn_8007A4F4(Block* b);


void* fn_80079940(int size, int align);
void fn_80079978(void* p);
void* fn_8007A4FC(int size);

int fn_8007A504(void* p);


extern int lbl_804CB5BC;
void fn_8007A6A8(u8* o, int v);

void fn_8007A71C(u8* o, int v);

void fn_8007A724(u8* o, int v);

int fn_8007A72C(u8* o);

void fn_8007A83C(int m);

void fn_8007A84C(int m);

int fn_8007A85C(int m);


}

#pragma use_lmw_stmw off
/* ---- from rJ_800799AC/wip/fn_80079D90.cpp ---- */
extern "C" {


void fn_8007A1CC(Proc* p) {
    if (checkError(p)) {
        return;
    }
    lbl_803CD8E0.result = fn_80079BE4(lbl_803CD8E0.fd, lbl_80362390 + 8, lbl_803CD8E0.cmdBlock);
    switch (lbl_803CD8E0.result) {
    case -4:
        fn_80081A90(p);
        break;
    default:
        lbl_803CD8E0.dirOpen = 1;
        lbl_803CD8E0.busy = 1;
        lbl_803CD8E0.result = fn_802F531C(lbl_803CD8E0.cmdBlock, lbl_803CD8E0.data, 0x26000, 0, fn_80079D90);
        if (lbl_803CD8E0.result < 0) {
            fn_80083DC4(p, 0x63);
            lbl_803CD8E0.busy = 0;
        }
        break;
    }
}
}
