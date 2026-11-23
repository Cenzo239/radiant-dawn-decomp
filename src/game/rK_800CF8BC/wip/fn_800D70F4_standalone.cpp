/* Standalone reproduction of the saved round-15 near match.
 * Check: python3 -I tools/check_func.py src/game/rK_800CF8BC/wip/fn_800D70F4_standalone.cpp -v
 * Still differs by two instruction words; not a matching source.
 */
/* Battle effect pops for triangle attacks, guardian and support (names guessed). */
typedef signed char s8;
typedef unsigned char u8;
typedef unsigned int u32;
typedef int BOOL;
#pragma use_lmw_stmw on

struct C4 { u8 r, g, b, a; };
struct Glob {
    u8 pad0[0x3F0];
    u32 u3F0;
    u8 pad3F4[0x48B - 0x3F4];
    u8 b48B;
    u8 pad48C[0x49C - 0x48C];
    u32 u49C;
    u8 pad4A0[0x890 - 0x4A0];
    u32 u890;
    u8 pad894[0xD30 - 0x894];
    u32 uD30;
    u8 padD34[0x15EC - 0xD34];
    u32 fl;
    u32 u15F0;
    u32 u15F4;
};
struct Item { u32 w0; u8 pad4[0xC]; const char* o10; };
struct Pop { u8 pad[0x30]; int x; int y; int k; u8 pad3C[4]; int t; C4 col; };
struct PU { u8 pad[0x102]; s8 x; s8 y; };

extern "C" {
extern u8 lbl_803C8E80[];
extern char lbl_8036651C[];
extern u8 lbl_80383FF8[];
extern const char* lbl_804CA65C;
extern const char* lbl_804CA660;
extern const char* lbl_804CA664;
extern const char* lbl_804CA6B8;
Item* fn_8010B23C(const char*);
int fn_80124A4C(void*, u32, u32*);
int fn_80124BC0(void*, u32*);
void* fn_800E3A10(const char*, void*);
void fn_800E5878(void*, u32);
void fn_800E5884(void*, u32, u32);
Pop* fn_80081194(void*, void*);
const char* fn_8011A054(Item*);
int fn_8013B9B0();
void fn_801CE2F4(const char*, int, int);
const char* fn_800D0864(const char*);
void fn_8010301C(u32, u32, int, int, void*);
void fn_8009F630(void*);

static inline void ChatMsg(Glob* g, const char* s) {
    if (g) {
        int t = fn_8013B9B0();
        if (g->b48B) {
            fn_801CE2F4(s, 9, t);
        } else {
            fn_801CE2F4(s, 10, t);
        }
    }
}

/* fn_800D70F4: 2 words: li of the counter schedules after addi r31; see fn_800D6EE4.cpp for declarations. */
static inline int fn_800D70F4_i(void* p) {
    Glob* g = (Glob*)lbl_803C8E80;
    u32 u[4];
    /*P*/
    u32 u3;
    int i;
    const char* s;
    u32* q;
/*E*/
    if (!(g->fl & 0x1000)) {
        return 0;
    }
    u[0] = g->u3F0;
    u[1] = g->u15F0;
    u[2] = g->u15F4;
    u3 = g->u890;
    u[3] = u3;
    if (u[0] == 0) {
        return 0;
    }
    if (u[1] == 0) {
        return 0;
    }
    if (u[2] == 0) {
        return 0;
    }
    if (u3 == 0) {
        return 0;
    }
    for (i = 0, q = u; i < 3; i++, q++) {
        void* m;
        fn_8010301C(*q, u3, 0x18, 0, p);
        m = fn_800E3A10(lbl_8036651C + 0x3A, p);
        if (m) {
            fn_800E5884(m, *q, u3);
        }
    }
    s = fn_800D0864(lbl_8036651C + 0x47);
    ChatMsg((Glob*)lbl_803C8E80, s);
    fn_8009F630(p);
    return 1;
}
int fn_800D70F4(void* p) { return fn_800D70F4_i(p); }

}
