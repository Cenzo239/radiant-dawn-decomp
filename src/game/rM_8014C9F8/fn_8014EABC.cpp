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
#if TARGET_PC
extern FE10_PROTO void fn_8007E74C(ptr32<const void>, ptr32<const void>);
#else
extern void fn_8007E74C(void (*)(void), void*);
#endif
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
extern void fn_8006074C(void*);
#if TARGET_PC
extern FE10_PROTO char * fn_8009283C(void*);
#else
extern int fn_8009283C(void*);
#endif
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
#if TARGET_PC
extern FE10_PROTO void fn_8007E374(u8*, p32arg, int);
#else
extern void fn_8007E374(u8*, int, int);
#endif
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

void fn_8014EABC(void) { fn_80006A2C(&lbl_804CB888); }



void fn_8014ECD4(f32 z, void* parent) {
    if (parent == NULL) {
        parent = (void*)3;
    }
    Fog* p = (Fog*)fn_80081050(lbl_80386D20, parent);
    if (z <= 0.0f) {
        z = 898.0f;
    }
    p->z = z;
    p->l[0].vx = -0x10;
    p->l[0].vy = 0;
    p->l[0].a0 = 0x10;
    p->l[0].a1 = 0x20;
    p->l[1].vx = -0x2C;
    p->l[1].vy = 0;
    p->l[1].a0 = 0x20;
    p->l[1].a1 = 0x60;
    fn_800068A0(&lbl_804CB888, lbl_80369C30);
}

void fn_8014ED80(f32 z, void* parent) {
    if (parent == NULL) {
        parent = (void*)3;
    }
    Fog* p = (Fog*)fn_80081050(lbl_80386D20, parent);
    if (z <= 0.0f) {
        z = 898.0f;
    }
    p->z = z;
    p->l[0].vx = -2;
    p->l[0].vy = 0;
    p->l[0].a0 = 0;
    p->l[0].a1 = 0x45;
    p->l[1].vx = -6;
    p->l[1].vy = 0;
    p->l[1].a0 = 0;
    p->l[1].a1 = 0x80;
    fn_800068A0(&lbl_804CB888, lbl_80369C30);
}

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

void fn_8014EE28(Msg* m, char c) {
    if (lbl_804CB700 & 0x800) {
        return;
    }
    m->fresh = 0;
    if (m->col <= 0x3E) {
        LINE(m, m->line)[m->col] = c;
        m->col++;
        LINE(m, m->line)[m->col] = 0;
    }
}

void fn_8014EE88(Msg* m) {
    MsgEol(m);
}

void fn_8014EEEC(Msg* m) {
    m->cur[0] = 0;
    m->b4248 = 0;
    MsgEol(m);
}

void fn_8014EF58(Msg* m) {
    MsgEol(m);
}

void fn_8014EFBC(Msg* m, const char* s) {
    if (s != NULL && fn_80291188(s, m->cur) != 0) {
        fn_802910CC(m->cur, s, 0x18);
        if (*s == 'G') {
            MsgPuts(m, lbl_80369FE8);
            MsgEol(m);
        } else {
            MsgPuts(m, lbl_80369FE8 + 6);
            MsgPuts(m, fn_800C4058(s));
            MsgEol(m);
        }
    }
}


#pragma push
#pragma use_lmw_stmw on
int fn_8014FA18(Msg* m, u8** pp) {
    u8* s = *pp;
    switch ((s8)*s) {
    case 0:
        MsgEol(m);
        return 0;
    case 1:
        *pp = s + 2;
        return 1;
    case 2:
        *pp = s + 3;
        return 1;
    case 3:
        *pp = s + 4;
        return 1;
    case 4:
        *pp = s + 1;
        fn_80148728(pp);
        return 1;
    case 5: {
        char buf[0x40];
        *pp = s + 1;
        char* t = fn_80148728(pp);
        if (t[0] == 'F' || t[1] == 'L') {
            char* n;
            int i;
            for (i = 0; i < 0x10; i++) {
                n = fn_80148728(pp);
                if (n == NULL) {
                    break;
                }
                strcpy(buf, lbl_80369FE8 + 0xC);
                fn_80291110(buf, n);
                fn_802910CC(m->names[i], buf, 0x20);
            }
        }
        return 1;
    }
    case 7:
    case 0xC:
        m->who = (s8)s[1] - 0x30;
        *pp += 3;
        return 1;
    case 8:
    case 9:
    case 0xA:
    case 0xE:
    case 0xF:
        *pp = s + 1;
        MsgEol(m);
        return 1;
    case 0xD:
    case 0x10:
    case 0x11:
        *pp = s + 1;
        return 1;
    case 0x12:
        return 1;
    default:
        return 2;
    }
}
#pragma pop

void fn_8014FC58(void);

void fn_8014FC6C(Msg* m) {
    int i;
    m->alpha += m->dalpha;
    if (m->alpha > 0xFF) {
        m->alpha = 0xFF;
    }
    if (m->alpha < 0) {
        m->alpha = 0;
    }
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 17.0f, 1.0f);
    fn_8007E174(NULL, 0x10);
    fn_8007E7DC(m->alpha);
    fn_8007E164();
    fn_800800D4(1);
    fn_800803F0(16.0f, 43.0f, 592.0f, 434.0f);
    fn_800804D4(0, 0, 0, 0xE0);
    fn_80080308();
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 16.0f, 1.0f);
    fn_8007E174(NULL, 0x13);
    fn_8007E74C(fn_8014FC58, NULL);
    fn_8007E164();
    for (i = 0; i < 0x10; i++) {
        int n = m->line - i - m->scroll / 25;
        char* s;
        int y;
        if (n < 0) {
            break;
        }
        s = LINE(m, n);
        y = m->scroll % 25 + (0x191 - i * 25);
        if (s[0] == '-') {
            if (s[1] == 'F') {
                char buf[0x20];
                fn_800800D4(5);
                fn_80080330(48.0f, y + 6);
                fn_80080508(*fn_800CD204(0xD));
                fn_80290DDC(buf, lbl_80369FE8 + 0x11, fn_80291314(s, '*') + 1);
                fn_80080C24(buf);
                fn_80080308();
            }
        } else {
            int d = 0;
            if (*(u32*)s == 0x23463031) {
                d = -4;
            }
            fn_800800D4(6);
            fn_80080330(72.0f, y + d);
            fn_80080C24(s);
            fn_80080308();
        }
    }
    fn_8007E154();
    fn_8007E7B4();
    fn_8007E164();
    if (m->obj != NULL) {
        fn_80179A7C(m->obj, (u8)m->alpha);
        fn_80179888(m->obj, m->h423A - m->scroll);
        fn_80179A84(m->obj);
    }
    fn_8007E154();
    fn_8007E7DC(0xFF);
    fn_8007E164();
}

void fn_8014FC58(void) { fn_803080DC(0, 0x33, 0x260, 0x177); }

void fn_801503AC(Msg* m) {
    int moved = 0;
    int v;
    if (lbl_804CB5B8->v34() & 8) {
        if (m->dir > 0 || m->speed == 0) {
            m->dir = 1;
            moved = 1;
            m->speed++;
        }
    }
    if (lbl_804CB5B8->v34() & 4) {
        if (m->dir < 0 || m->speed == 0) {
            m->dir = -1;
            moved = 1;
            m->speed++;
        }
    }
    v = lbl_804CB5B8->v54() / 6;
    if (v != 0) {
        moved = 1;
        m->speed = v < 0 ? -v : v;
        m->dir = v < 0 ? -1 : 1;
    }
    if (!moved) {
        m->speed--;
    }
    if (m->speed > 0xC) {
        m->speed = 0xC;
    }
    if (m->speed < 0) {
        m->speed = 0;
    }
    m->scroll += m->speed * m->dir;
    if (m->scroll > m->h423A) {
        m->scroll = m->h423A;
        m->speed = 0;
    }
    if (m->scroll < 0) {
        m->scroll = 0;
        m->speed = 0;
    }
}

void fn_8015055C(Msg* m) {
    m->alpha = 0;
    m->dalpha = 0x20;
    m->speed = 0;
    m->dir = 0;
    m->scroll = 0;
    m->h423A = (Min(m->line, 0x100) - 0xF) * 0x19;
    if (m->h423A < 0) {
        m->h423A = 0;
    }
    if (m->b4248 != 0) {
        fn_800068A0(m->pad4220 + 8, lbl_80369FE8 + 0x14);
        m->scroll = m->h423A;
    }
    if (m->h423A != 0) {
        void* o = fn_80078CCC(0x2C, lbl_804CA798, 0);
        if (o != NULL) {
            o = fn_80179660(o);
        }
        m->obj = o;
        fn_8017980C(o, 0x240, 0x36, 0x174);
        fn_80179854(m->obj, 10.0f);
        fn_8017985C(m->obj, m->h423A + 0x177);
        fn_80179864(m->obj, 0x177);
    } else {
        m->obj = NULL;
    }
}

void fn_80150668(void) {
    if (lbl_80413F10.b4248 != 0) {
        fn_8014FF44(&lbl_80413F10);
    } else {
        fn_8014FC6C(&lbl_80413F10);
    }
}

void fn_80150684(Proc* p) {
    fn_801503AC(&lbl_80413F10);
    if (lbl_804CB5B8->v48() & 0x810) {
        lbl_80413F10.dalpha = -0x20;
        p->sleep = 8;
        fn_80083B78(p);
    } else if (lbl_804CB700 & 3) {
        fn_80081A90(p);
    }
}

void fn_80150710(void) { fn_8015055C(&lbl_80413F10); }

void fn_8015071C(void) {
    if (lbl_80413F10.b4248 != 0) {
        fn_80006A2C(lbl_80413F10.pad4220 + 8);
    }
    if (lbl_80413F10.obj != NULL) {
        delete (Del*)lbl_80413F10.obj;
    }
    lbl_80413F10.obj = NULL;
}

void fn_80150790(void* parent) { fn_80081194(lbl_80386DB8, parent); }

void fn_801507A0(void* a, void* parent) {
    fn_8014F288(&lbl_80413F10, a);
    fn_80081194(lbl_80386DB8, parent);
}



void fn_80150990(void) {
    int i;
    lbl_80413F10.line = 0;
    lbl_80413F10.col = 0;
    lbl_80413F10.fresh = 0;
    for (i = 0; i < 0x100; i++) {
        LINE(&lbl_80413F10, i)[0] = 0;
    }
}

}
