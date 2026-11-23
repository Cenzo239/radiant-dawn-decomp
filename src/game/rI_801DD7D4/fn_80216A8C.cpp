#include "game/rI_801DD7D4/types.h"
#pragma auto_inline off
#pragma use_lmw_stmw on
extern "C" {
struct Empty { Empty() {} char c; };
struct MslString { union { struct { u32 isLong : 1; u32 pad : 31; u32 size; char* data; } l; struct { u8 isLong : 1; u8 size : 7; char data[11]; } s; }; };
u32 strlen(const char*);
void fn_80024EFC(MslString*, u32);
MslString* fn_800250B0(MslString*, u32, u32, const char*, const char*, Empty);
void fn_80079210(void*);
void fn_80011CBC(void*, void*);
void fn_80006EE0(void* p);
#if TARGET_PC
FE10_PROTO void fn_8023F1A8(ptr32<const void>);
#else
void fn_8023F1A8(void* p);
#endif
void* fn_80006E1C(void);
void* fn_8023F1A4(const char*, int);
void fn_80009090(void*, const char*);
void fn_80009030(void*, const char*);
void fn_800090F0(void*, const char*);
void fn_80006F20(void*);
void fn_80108618(void*, void*);
extern char lbl_80371974[];
struct St { u8 p[0x64]; u32* a64; void* a68; };
static inline u32 strSize(MslString* s) { return s->l.isLong == 0 ? s->s.size : s->l.size; }
static inline char* strData(MslString* s) { return s->l.isLong == 0 ? s->s.data : s->l.data; }
static inline void strZero(MslString* s) { *(u32*)s = 0; ((u32*)s)[1] = 0; ((u32*)s)[2] = 0; }
static inline void strFree(MslString* s) { if (s->l.isLong != 0) fn_80079210(s->l.data); }
static inline void app(MslString* s, const char* p, u32 n, Empty e) { fn_800250B0(s, n, 0, p, p + strlen(p), e); }
static inline MslString* rp(MslString* s,u32 o,const char* a,const char* b,Empty e){return fn_800250B0(s,o,0,a,b,e);}
static inline MslString* rq(MslString* s,u32 o,const char* a,const char* b){Empty e; return fn_800250B0(s,o,0,a,b,e);}
static inline MslString* rq2(MslString* s,u32 o,const char* a,const char* b){return rp(s,o,a,b,Empty());}
static inline MslString* rq3(MslString* s,u32 o,const char* a,const char* b){return rq(s,o,a,b);}
static inline MslString* d1(MslString* s,u32 o,const char* a,const char* b){return rp(s,o,a,b,Empty());}
static inline MslString* d2(MslString* s,u32 o,const char* a,const char* b){return d1(s,o,a,b);}
static inline MslString* d3(MslString* s,u32 o,const char* a,const char* b){return d2(s,o,a,b);}
static inline void ap1(MslString* s,u32 o,const char* a){ d1(s,o,a,a+strlen(a)); }
static inline void ap2(MslString* s,u32 o,const char* a){ d2(s,o,a,a+strlen(a)); }
static inline void ap3(MslString* s,u32 o,const char* a){ d3(s,o,a,a+strlen(a)); }
static inline void ap0(MslString* s,u32 o,const char* a,Empty e){ fn_800250B0(s,o,0,a,a+strlen(a),e); }
static inline void w1(MslString* s,u32 o,const char* a){ ap0(s,o,a,Empty()); }
static inline void w2(MslString* s,u32 o,const char* a){ w1(s,o,a); }
static inline void w3(MslString* s,u32 o,const char* a){ w2(s,o,a); }
static inline void v1(MslString* s,u32 o,const char* a,Empty e){ ap0(s,o,a,e); }
static inline void v2(MslString* s,u32 o,const char* a,Empty e){ v1(s,o,a,e); }
void fn_8021D7E0(MslString* r, MslString* a, const char* b) {
/*P*/
    u32 n;
    u32 m;
    const char* d;
    const char* q;
/*E*/
    strZero(r);
    m = strlen(q = b);
    if (a->l.isLong == 0) { d = a->s.data; n = a->s.size; } else { d = a->l.data; n = a->l.size; }
    fn_80024EFC(r, n + m);
    { Empty e; r = fn_800250B0(r, 0, 0, d, d + n, e); }
    rp(r,n,q,q+m,Empty());
}
void fn_80216A8C(St* o, u8*** w) {
    MslString st;
/*P*/
    const char* p;
    const char* p2;
    u32 n;
    const char* p3;
    u32 n3;
    u32 n2;
    const char* b;
/*E*/
    if (o->a64 != NULL) fn_80011CBC(fn_80006EE0, o->a64);
    if (o->a68 != NULL) fn_80011CBC(fn_8023F1A8, o->a68);
    if (w != NULL && *w != NULL) {
    o->a64 = (u32*)fn_80006E1C();
    b = lbl_80371974;
    strZero(&st);
    p = b + 0xf;
    n = strlen(p);
    fn_80024EFC(&st, n);
    {Empty e; fn_800250B0(&st, 0, 0, p, p + n, e);}
    p2 = b + 0x14;
    if (st.l.isLong == 0) n2 = st.s.size; else n2 = st.l.size;
    ap0(&st,n2,p2,Empty());
    p3 = (const char*)(**w + 4);
    if (st.l.isLong == 0) n3 = st.s.size; else n3 = st.l.size;
    w1(&st,n3,p3);
    {
        MslString t;
        fn_8021D7E0(&t, &st, lbl_80371974 + 0x1b);
        o->a68 = fn_8023F1A4(strData(&t), 0);
        strFree(&t);
    }
    {
        MslString t;
        fn_8021D7E0(&t, &st, lbl_80371974 + 0x22);
        fn_80009090(o->a64, strData(&t));
        strFree(&t);
    }
    {
        MslString t;
        fn_8021D7E0(&t, &st, lbl_80371974 + 0x27);
        fn_80009030(o->a64, strData(&t));
        strFree(&t);
    }
    {
        MslString t;
        fn_8021D7E0(&t, &st, lbl_80371974 + 0x2d);
        fn_800090F0(o->a64, strData(&t));
        strFree(&t);
    }
    *o->a64 |= 0xF0210000;
    fn_80006F20(o->a64);
    fn_80108618(o->a64, w);
    strFree(&st);
    }
}
}
