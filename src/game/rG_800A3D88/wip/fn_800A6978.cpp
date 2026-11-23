// WIP, does not match: 14 lines: name/n and j registers. Frame struct gives the stack; a plain local order may be nicer.
#include "game/rG_800A3D88/types.h"

// Preloads the camera files for one attack.
extern "C" {
struct Req { u8 p[0xC]; const char* m0c; const char* m10; const char* m14; const char* m18; void* m1c; };
struct E688 { const char* name; s16 m4[6]; };
struct E684 { u8 p[0xB]; u8 n; u8* idx; u8 p10[4]; };
struct E680 { u8 p[4]; const char* name; u8 p8[4]; };
extern char lbl_803651B0[];
extern u8* lbl_804CB680;
extern u8* lbl_804CB684;
extern u8* lbl_804CB688;
void fn_800E24F8(const char*);
u8 fn_800A6844(Req*, int);
void fn_801CDAE8();
u32 fn_80109A2C(u8**);
int fn_80291188(const char*, const char*);
int fn_80290DDC(char*, const char*, ...);
int fn_8023F9F4(const char*);
void fn_8023F1A0(const char*, int);
void* fn_800AF114();
void fn_800AEE68(void*, void*);
struct FA6978 { u8* r0; u8* r1; u8* r2; u8* r3; char buf[0x40]; };
static inline u16 Count(u8** r, u8* tbl) {
    *r = tbl;
    u16 n = fn_80109A2C(r);
    fn_80109A2C(r);
    return n;
}
static inline u8* Data(u8** r, u8* tbl) {
    *r = tbl;
    fn_80109A2C(r);
    fn_80109A2C(r);
    return *r;
}
static inline E688* Find688(FA6978* f, const char* name) {
/*P*/
const char* nm;
E688* e;
int i;
int n;
/*E*/
    nm = name;
    if (nm == NULL) return NULL;
    n = Count(&f->r2, lbl_804CB688);
    e = (E688*)Data(&f->r3, lbl_804CB688);
    for (i = 0; i < n; i++, e++) {
        if (fn_80291188(e->name, nm) == 0) return e;
    }
    return NULL;
}
static inline E684* Get684(FA6978* f, E688* e, int k) {
    if (k < 0) return NULL;
    int j = e->m4[k];
    if (j < 0) return NULL;
    return (E684*)Data(&f->r1, lbl_804CB684) + j;
}
static inline E680* Get680(FA6978* f, int j) {
    if (j < 0) return NULL;
    return (E680*)Data(&f->r0, lbl_804CB680) + j;
}
static inline const char* Exists(char* buf, const char* s) {
    fn_80290DDC(buf, lbl_803651B0 + 0x1F, s);
    if (fn_8023F9F4(buf) == 0x40000) return NULL;
    return buf;
}
#pragma use_lmw_stmw on
void fn_800A6978(Req* q, int k) {
    FA6978 f;
/*P*/
int i;
int n;
E688* e;
E684* g;
void* p;
/*E*/
    fn_800E24F8(q->m0c);
    fn_800E24F8(q->m10);
    fn_800E24F8(q->m14);
    fn_800E24F8(q->m18);
    if (fn_800A6844(q, -1) == 9) fn_801CDAE8();
    e = Find688(&f, q->m14);
    if (e != NULL) {
        g = Get684(&f, e, k);
        if (g != NULL) {
            n = g->n;
            for (i = 0; i < n; i++) {
                E680* h = Get680(&f, g->idx[i]);
                if (h != NULL) {
                    if (Exists(f.buf, h->name)) fn_8023F1A0(f.buf, 0x40);
                }
            }
        }
    }
    p = fn_800AF114();
    if (p != NULL) fn_800AEE68(p, q->m1c);
}
}
