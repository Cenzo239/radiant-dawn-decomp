/* Round 20, functionally equal (check_regs.py: sched): fn_80161A54. Self-contained. Parent file with its exported fn_ bodies removed plus the fragment from wip/near.cpp, use_lmw_stmw set from the original. Moved (harmless): prologue only, the parameter copies (mr), li 0 and addi r3,r1,0x10 are interleaved differently with the register saves. */
/* AI: boss script commands (CP_*), 80160728..80161CD0. */
#include "game/rM_8014C9F8/ai.h"
#pragma auto_inline off

struct AiCmd {
    int op;
    int a;
    int b;
    int c;
    int d;
    u32 fl;
    u32 x;
    u32 y;
    u32 z;
    u32 w;
};

struct Fn4 {
    void* vt;
    Unit* u;
    u32 x;
    u8 k;
};

struct AiActX {
    u8 pad[0x18];
    int arg[4];  /* 0x18 */
};

extern "C" {

extern u8* fn_80076F54(u32);
extern u32 fn_80077064(u32);
extern int fn_80155090(void*, void*, char*, u8);
extern char lbl_8036AED8[];
extern u8 lbl_803872B8[];
extern u8 lbl_803872C8[];
int fn_80160728(Unit* u, AiCmd* c);

int fn_801607BC(Unit* u, AiCmd* c);

int fn_80160850(Unit* u, AiCmd* c);

int fn_801608E4(Unit* u, AiCmd* c);

int fn_80160978(Unit* u, AiCmd* c);

int fn_80160A0C(Unit* u, AiCmd* c);

int fn_80160B10(Unit* u, AiCmd* c);

int fn_80160C18(Unit* u, AiCmd* c);

int fn_80160D20(Unit* u, AiCmd* c);

int fn_80160E28(Unit* u, AiCmd* c);

int fn_80160EB0(Unit* u, AiCmd* c);

int fn_80160F38(Unit* u, AiCmd* c);


#define FOR_SIDE0(n)                               \
    {                                              \
        u8 tbl[0xC];                               \
        int i;                                     \
        fn_8010E41C(tbl, 0);                       \
        for (i = 1; i <= 0xFE; i++) {              \
            Unit* v = UnitGet(i);                  \
            if (v->person && tbl[v->team[8]]) {    \
                n++;                               \
            }                                      \
        }                                          \
    }

int fn_80160FC0(Unit* u);





extern void fn_80076D48(char*, void*);
extern int fn_80161A54(Unit*, AiCmd*);
extern int fn_801612B4(Unit*, AiCmd*);
extern int fn_80161684(Unit*, AiCmd*);
void fn_80161BA4(void);


extern void fn_80167704(u8*);
extern void fn_8010CC50(void*, s8*, s8*);
extern void fn_80166720(Unit*);
extern u8* fn_80060728(void*);
extern u8 lbl_803CAB38[];
extern void* lbl_803870A8[];
extern void* lbl_803870F8[][0x10];
void* fn_80161D98(void);


}

#pragma use_lmw_stmw off
/* ---- from build/tmp/r20small/rM/frag_fn_80161A54.cpp ---- */
extern "C" {
/* from fn_80160728.cpp */
int fn_80161A54(Unit* u, AiCmd* c) {
    u8* p;
    int n = 0;
    FOR_SIDE0(n);
    if (n > 0x46) {
        return 0;
    }
    p = fn_80076F54(c->y);
    fn_80160610(0x5A, u->x, (s8)*(u8*)&u->y, NULL, 0, 0, -1, 0, 0);
    ((AiActX*)&lbl_803CA870)->arg[0] = p[0];
    return 0;
}
}
