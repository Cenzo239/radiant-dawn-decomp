/* EXACT (round m9, m9-s): fn_801BB334, a unit's sort key for list column `col` (0 key, 1 count of filled skill slots, 2 affinity, 3 other unit's value). Self-contained from equiv/fn_801BB334.cpp; fix: locals declared `Slot* s; SkillD* d; int i;` and the loop tail written `s++, i++` (r6/r5 swap of i and d, then the addi slot order). */
#include "game/rF_8017F400/types.h"
#pragma auto_inline off
extern "C" {
typedef struct SkillD { u8 pad[0x1F]; u8 x1F; } SkillD;
typedef struct Slot { SkillD* p; u8 pad[4]; } Slot;
typedef struct UEc { u8 pad[0xE1]; s8 xE1; u8 padE2[4]; u16 xE6; u8 padE8[4]; u16 xEC; u8 padEE[0x16]; s8 x104; } UEc;
typedef struct U {
    u8 pad[0xEC];
    UEc* ec;
    UEc* xF0;
    u8 padF4[4];
    U* xF8;
    u8 padFC[2]; s8 xFE; u8 padFF[0xD];
    u32 flags;
    struct { u8 d[4]; } x110;
    s8 x114; u8 pad115[3]; s8 x118;
    u8 pad119[0x13];
    Slot x12C[18];
} U;
typedef struct Row { U* u; u8 pad[4]; void* x8; U* xC; U* x10; u16 x14; u8 x16; u8 x17; u8 x18, x19, x1A, x1B; } Row;

extern void* fn_80118F00(UEc*);
extern const char* fn_800D0864(const char*);
extern const char* fn_80118C44(UEc*);
extern int fn_80290DDC(char*, const char*, ...);
extern char lbl_80389B48[], lbl_80389B3C[], lbl_80389B30[];
extern char lbl_80389BA0[], lbl_80389B94[];
extern char lbl_804CA804[4], lbl_804CA800[4];
extern char lbl_80389BC0[], lbl_80389BAC[];
extern void fn_801B5EB4(int, int, void*, f32, f32);

static inline int SortKey(U* u) {
    int k;
    u32 f;
    if (u == NULL) return 0;
    f = u->flags;
    k = -(int)u->ec->xE6;
    if (f & 0x200000) k -= 2000;
    if (f & 0x10) k -= 1000;
    if (f & 0x400000) k += 1000;
    if (f & 0x10000) k += 2000;
    return k;
}
int fn_801BA664(void* self, Row* e, int col);

const void* fn_801BA760(void* self, Row* e, int col);

char* fn_801BA8C0(char* buf, Row* e, int col);


#define CELLEND *a = 0; *c = 0x38; *d = *b + 0x14

void fn_801BA994(void* self, int col, int* a, int* b, int* c, int* d);

const char* fn_801BA9E0(void* self, int col);

int fn_801BAA04(void* self, Row* e, int col);

void fn_801BAAA4(void* self, int col, int* a, int* b, int* c, int* d);

void fn_801BB26C(void* self, int col, int* a, int* b, int* c, int* d);

void fn_801BB818(void* self, int col, int* a, int* b, int* c, int* d);

void fn_801BBA8C(void* self, int col, int* a, int* b, int* c, int* d);

void fn_801BBDE4(void* self, int col, int* a, int* b, int* c, int* d);


struct IconBase { u8 d[0x44]; };
class IconFont : public IconBase {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4(int x, int y, int id);
};
extern u8 lbl_803E7290[];
extern u8 lbl_803E72D8[];
#define ICONS ((IconFont*)lbl_803E7290)
#define ICONS2 ((IconFont*)lbl_803E72D8)

extern int fn_8012C250(U* u, int i);
extern const char* fn_801113DC(int);
extern char lbl_804CA834[4], lbl_804CA830[4], lbl_804CA82C[4], lbl_804CA828[4], lbl_804CA824[4], lbl_804CA820[4], lbl_804CA81C[4], lbl_804CA818[4], lbl_804CA814[4], lbl_804CA810[4], lbl_804CA80C[4], lbl_804CA808[4];
extern char lbl_80389CC4[], lbl_80389CB0[], lbl_80389C9C[], lbl_80389C88[], lbl_80389C74[], lbl_80389C60[], lbl_80389C4C[], lbl_80389C38[], lbl_80389C24[], lbl_80389C10[], lbl_80389BFC[], lbl_80389BE8[], lbl_80389BD4[];
extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E4E4(f32 x, f32 y, f32 z, f32 w);
extern void fn_8007E374(void* tex, int a, int b);
extern void fn_8007E74C(void* cb, s16* r);
extern void fn_8007E7DC(int a);
extern u16 fn_800CEABC(int);
extern void fn_801B5E64(void);
extern void fn_801B5E3C(void);
extern int fn_801196F0(int);
extern U* fn_8012E3A4(U*);
extern s8 fn_8012E9B4(U*, U*);
extern u8 fn_8012E8A0(U*, int);
extern int fn_80109174(void*);
extern int fn_801091E0(void*, int);
extern void fn_80291110(char*, char*);
extern char lbl_804CA844[4], lbl_804CA840[4], lbl_804CA838[8];
extern char lbl_80389D4C[], lbl_80389D40[], lbl_80389CD8[];
const char* fn_801BAB7C(void* self, int col);

int fn_801BAC38(void* self, Row* e, int col);


#define WL(i, s) fn_80290DDC(buf, s, fn_801113DC((s16)fn_8012C250(u, i))); break

char* fn_801BAD90(char* buf, Row* e, int col);

void fn_801BAFF4(void* self, void* tex, f32 x, f32 y);


static inline s8 Aff(U* u) { s8 v = u->x118; if (v == -1) v = u->ec->xE1; return v; }
static inline BOOL SlotOK(Slot* s) {
    if (s == NULL) return 0;
    if (s->p == NULL) return 0;
    return s->p->x1F != 0;
}
static inline BOOL SOK(Slot* s) { return s && s->p && s->p->x1F; }
static inline BOOL SOK2(Slot* s) { return s->p && s->p->x1F; }
static inline SkillD* G(Slot* s) { return s->p; }
static inline u8 X1F(SkillD* s) { return s->x1F; }
static inline u8 X(Slot* s) { if (s) { SkillD* d = s->p; if (d) return d->x1F; } return 0; }
int fn_801BB8B8(void* self, Row* e, int col);

char* fn_801BB958(char* buf, Row* e, int col);

extern s8 fn_8012408C(void*);
extern s8 fn_8012401C(void*);
extern s8 fn_80124144(void*);
int fn_801BBBA4(void* self, Row* e, int col);


extern char lbl_804CA874[4], lbl_804CA870[4], lbl_804CA868[8], lbl_804CA860[8], lbl_804CA858[8], lbl_804CA854[4], lbl_804CA850[4], lbl_804CA84C[4], lbl_804CA848[4];
extern char lbl_80389D94[];
char* fn_801BBC84(char* buf, Row* e, int col);

int fn_801BBECC(void* self, Row* e, int col);

extern const char* fn_8010F5E0(void*);
extern char lbl_80389E3C[], lbl_804CA894[4], lbl_804CA88C[8], lbl_804CA888[4], lbl_804CA880[8], lbl_804CA87C[4], lbl_804CA878[4];
char* fn_801BBF8C(char* buf, Row* e, int col);

void fn_801BC094(void* self, int col, int* a, int* b, int* c, int* d);

extern char lbl_80389F94[], lbl_80389F80[], lbl_80389F6C[], lbl_80389F54[], lbl_80389F40[], lbl_80389F2C[], lbl_80389F18[], lbl_80389F04[];
const char* fn_801BC130(void* self, int col);

extern s16 fn_8012386C(U*), fn_80123998(U*), fn_80123AC4(U*), fn_80123BF0(U*), fn_80123D1C(U*), fn_80123DC4(U*), fn_80123EF0(U*);
int fn_801BC1B0(void* self, Row* e, int col);

void fn_801BC548(void* self, int col, int* a, int* b, int* c, int* d);

extern u8 fn_80126B0C(U*);
extern s16 fn_801237EC(U*);
int fn_801BC654(void* self, Row* e, int col);

extern char lbl_804CA8EC[4], lbl_804CA8E4[8], lbl_804CA8E0[4], lbl_804CA8DC[4], lbl_804CA8D8[4], lbl_804CA8D0[8], lbl_80389FA8[];
const char* fn_801BC740(char* buf, Row* e, int col);


static inline void Txt(int px, int r5, const void* s, f32 x, f32 y) { fn_801B5EB4(2, r5, (void*)s, 32.0f + (x + (f32)px), y); }
}

/* ---- from rF_8017F400/wip/fn_801BA664.cpp ---- */
extern "C" {
/* near misses; take the declarations from ../fn_801BA664.cpp */
int fn_801BB334(void* self, Row* e, int col) {
    int r = 0;
    U* u = e->u;
    switch (col) {
    case 0:
        return SortKey(u);
    case 1: {
Slot* s; SkillD* d; int i;
        for (i = 0, s = u->x12C; i < 18; s++, i++) { if (s && (d = s->p) && d->x1F) r++; }
        return r; }
    case 2:
        return Aff(u);
    case 3: {
        U* o = fn_8012E3A4(u);
        if (o) return fn_8012E8A0(o, fn_8012E9B4(o, u));
    }
    }
    return 0;
}
}
