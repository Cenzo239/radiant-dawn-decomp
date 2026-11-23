/* Round 20, functionally equal (check_regs.py: regs): fn_801507EC. Self-contained. fn_8014EABC.cpp with exported bodies removed plus the function. Port caveat: the original loads lbl_804CB700 twice back to back (once masked for the first two tests, once raw for the loop); reproduced with a second read through a volatile cast into fl, passed to MsgPutcB/MsgPutsB. The real source is most likely plain MsgPutc/MsgEol/MsgPuts (see wip/near.cpp); undo the volatile and the B variants in a port. */
/* Fog layer process and message-log text ring, 8014EABC..8014FC6C. */
#include "game/rM_8014C9F8/types.h"

struct Color {
    u8 r, g, b, a;
};

struct Layer {
    s16 x;   /* +0 */
    s16 y;   /* +2 */
    s16 vx;  /* +4 */
    s16 vy;  /* +6 */
    u8 a0;   /* +8 */
    u8 a1;   /* +9 */
};

struct Fog : Proc {
    Layer l[2];     /* 0x30 */
    u8 pad44[0];
    f32 z;          /* 0x44 */
};

struct Msg {
    char names[0x10][0x20]; /* 0x0000 */
    char lines[0x100][0x40]; /* 0x0200 */
    int who;        /* 0x4200 */
    int last;       /* 0x4204 */
    char cur[0x18]; /* 0x4208 */
    u8 pad4220[0xC];
    int cnt;        /* 0x422C */
    int line;       /* 0x4230 */
    int col;        /* 0x4234 */
    u8 fresh;       /* 0x4238 */
    u8 pad4239;
    s16 h423A;      /* 0x423A */
    s16 scroll;     /* 0x423C */
    s8 dir;         /* 0x423E */
    s8 speed;       /* 0x423F */
    s16 alpha;      /* 0x4240 */
    s16 dalpha;     /* 0x4242 */
    void* obj;      /* 0x4244 */
    u8 b4248;       /* 0x4248 */
};

extern "C" {

class Pad5B8 {
public:
    virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2C(); virtual void v30();
    virtual u32 v34();
    virtual void v38(); virtual void v3C(); virtual void v40(); virtual void v44();
    virtual u32 v48();
    virtual void v4C(); virtual void v50();
    virtual int v54();
};
extern Pad5B8* lbl_804CB5B8;
class Del {
public:
    u8 pad[0x28];
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual ~Del();
};
extern Msg lbl_80413F10;
extern u8 lbl_80386DB8[];
extern char lbl_804CA798[8];
extern void fn_803080DC(int, int, int, int);
extern void* fn_80078CCC(int, char*, int);
extern void* fn_80179660(void*);
extern void fn_8017980C(void*, int, int, int);
extern void fn_80179854(void*, f32);
extern void fn_8017985C(void*, int);
extern void fn_80179864(void*, int);
extern void fn_8014F288(Msg*, void*);
extern void fn_8007E7DC(u8);
extern void fn_8007E174(void*, int);
extern void fn_800803F0(f32, f32, f32, f32);
extern void fn_800804D4(int, int, int, int);
extern void fn_8007E74C(void (*)(void), void*);
extern void fn_80080330(f32, f32);
extern Color* fn_800CD204(int);
extern void fn_80080508(Color);
extern char* fn_80291314(const char*, int);
extern int fn_80290DDC(char*, const char*, ...);
extern void fn_80080C24(const char*);
extern void fn_8007E7B4(void);
extern void fn_80179A7C(void*, int);
extern void fn_80179888(void*, int);
extern void fn_80179A84(void*);
extern char* fn_80148728(u8**);
extern char* strcpy(char*, const char*);
extern char* fn_80291110(char*, const char*);
extern void* fn_8006074C(void*);
extern int fn_8009283C(void*);
extern u8 lbl_803CAB38[];
extern void fn_8014FF44(Msg*);
extern u32 lbl_804CB700;
extern u8* lbl_804CB888;
extern char lbl_80369C30[];
extern u8 lbl_80386D20[];
extern Color lbl_804CE218;
extern Color lbl_804CE21C;
extern Color lbl_804CE220;
extern Color lbl_804CE224;
extern char lbl_80369FE8[];

extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E4E4(f32, f32, f32, f32);
extern void fn_8007E374(u8*, int, int);
extern void fn_800800D4(int);
extern void fn_80080388(f32, f32, f32, f32);
extern void fn_800803C8(f32, f32, f32, f32);
extern void fn_80080308(void);
extern void fn_80080578(int);
extern void fn_80080940(Color, Color, Color, Color);
extern void fn_800068A0(void*, char*);
extern void fn_80006A2C(void*);
extern int fn_80291188(const char*, const char*);
extern char* fn_802910CC(char*, const char*, u32);
extern char* fn_800C4058(const char*);

static inline Color WithA(u8 a) {
    Color c = {0xFF, 0xFF, 0xFF, a};
    return c;
}

static inline int Min(int a, int b) { return a < b ? a : b; }
void fn_8014EABC(void);

void fn_8014ECD4(f32 z, void* parent);

void fn_8014ED80(f32 z, void* parent);


#define LINE(m, n) ((m)->lines[((n) + 0x100) & 0xFF])

static inline void MsgPutc(Msg* m, u8 c) {
    if (!(lbl_804CB700 & 0x800)) {
        m->fresh = 0;
        if (m->col <= 0x3E) {
            LINE(m, m->line)[m->col] = c;
            m->col++;
            LINE(m, m->line)[m->col] = 0;
        }
    }
}

static inline void MsgEol(Msg* m) {
    if (m->fresh == 0) {
        LINE(m, m->line)[m->col] = 0;
        m->col = 0;
        m->line++;
        LINE(m, m->line)[0] = 0;
        m->fresh = 1;
        m->cnt++;
    }
}

static inline void MsgPuts(Msg* m, const char* s) {
    if (!(lbl_804CB700 & 0x800)) {
        while (*s != 0) {
            MsgPutc(m, *s++);
        }
    }
}
void fn_8014EE28(Msg* m, char c);

void fn_8014EE88(Msg* m);

void fn_8014EEEC(Msg* m);

void fn_8014EF58(Msg* m);

void fn_8014EFBC(Msg* m, const char* s);



#pragma push
#pragma use_lmw_stmw on

int fn_8014FA18(Msg* m, u8** pp);

#pragma pop

void fn_8014FC58(void);
void fn_8014FC6C(Msg* m);

void fn_8014FC58(void);

void fn_801503AC(Msg* m);

void fn_8015055C(Msg* m);

void fn_80150668(void);

void fn_80150684(Proc* p);

void fn_80150710(void);

void fn_8015071C(void);

void fn_80150790(void* parent);

void fn_801507A0(void* a, void* parent);

void fn_80150990(void);


}

#pragma use_lmw_stmw off

static inline void MsgPutcB(Msg* m, u8 c, u32 q) {
    if (!q) {
        m->fresh = 0;
        if (m->col <= 0x3E) {
            LINE(m, m->line)[m->col] = c;
            m->col++;
            LINE(m, m->line)[m->col] = 0;
        }
    }
}
static inline void MsgPutsB(Msg* m, const char* s, u32 fl) {
    if (!(lbl_804CB700 & 0x800)) {
        while (*s != 0) {
            MsgPutcB(m, *s++, fl & 0x800);
        }
    }
}
/* ---- from build/tmp/r20small/rM/frag_fn_801507EC.cpp ---- */
extern "C" {
/* from fn_8014EABC.cpp */
void fn_801507EC(void) {
    char buf[0x50]; u32 fl;
    void* g = fn_8006074C(lbl_803CAB38);
    fn_80290DDC(buf, lbl_80369FE8 + 0x27, fn_8009283C(g));
    fl = *(volatile u32*)&lbl_804CB700; MsgPutc(&lbl_80413F10, ' ');
    MsgEol(&lbl_80413F10);
    MsgPutsB(&lbl_80413F10, buf, fl);
}
}
