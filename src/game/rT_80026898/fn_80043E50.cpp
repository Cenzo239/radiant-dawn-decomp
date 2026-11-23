/* Map music selection per frame (names guessed). */
#include "game/rT_80026898/types.h"
typedef struct FlagTable {
    u8 pad0[0x11];
    u8 b11;             /* 0x11 */
    u8 pad12[0x144 - 0x12];
    char* names[0x80];  /* 0x144 */
    u32 hashes[0x80];   /* 0x344 */
    u8 bits[0x10];      /* 0x544 */
    u8 pad554[0x988 - 0x554];
} FlagTable;
struct BgmT { const char* name; };
class Bgm {
public:
    virtual void v8();
    virtual void vC();
    virtual int v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void v24(int);
    virtual void v28(int);
    virtual void v2C(int);
    virtual void v30();
    virtual int v34();
    virtual void v38(f32, f32);
    u8 pad4[8];
    BgmT* c;
};
extern "C" {
extern FlagTable lbl_803CAB38;
extern char lbl_80361684[0xbc];
extern int lbl_804CB2D0;
u32 fn_80076D18(const char*);
int fn_80291188(const char*, const char*);
u8* fn_8006074C(void*);
int fn_80068A64();
#if TARGET_PC
FE10_PROTO ptr32<const char> fn_80068424(u8*, u8);
FE10_PROTO ptr32<const char> fn_80068398(u8*, u8);
#else
const char* fn_80068424(u8*, u8);
const char* fn_80068398(u8*, u8);
#endif
void fn_80252418(const char*, f32);
#if TARGET_PC
FE10_PROTO struct Proc * fn_80085708(const char*);
#else
int fn_80085708(const char*);
#endif
Bgm* fn_8024F3FC(int);
void fn_80251838(int, const char*, f32);
int fn_8024F7EC(const char*);
int fn_8024F92C(const char*);

static inline int flagFind(FlagTable* t, const char* name) {
    u32 h = fn_80076D18(name);
    int i;
    for (i = 0; i < 0x80; i++) {
        if (h == t->hashes[i] && fn_80291188(t->names[i], name) == 0) {
            return i;
        }
    }
    return -1;
}
static inline bool flagTestBit(FlagTable* t, int i) {
    if (i < 0 || i >= 0x80) {
        return false;
    }
    return t->bits[i >> 3] & (1 << (i & 7));
}
static inline bool flagGetBit(FlagTable* t, int i) {
    if (i < 0 || i >= 0x80) {
        return false;
    }
    return flagTestBit(t, i);
}
static inline bool flagGet(FlagTable* t, const char* const& name) {
    if (name[0] == 0) {
        return false;
    }
    return flagGetBit(t, flagFind(t, name));
}
static inline bool Has(const char* s) { return (s8)fn_8024F7EC(s) != -1; }

void fn_80043E50() {
    /*P*/
    const char* name;
    u8* ch;
    Bgm* o;
    /*E*/
    ch = fn_8006074C(&lbl_803CAB38);
    if (fn_80068A64()) {
        name = fn_80068424(fn_8006074C(&lbl_803CAB38), lbl_803CAB38.b11);
        fn_80252418(name, 400.0f);
        return;
    }
    if (fn_80085708(lbl_80361684 + 8)) {
        name = lbl_80361684 + 0x13;
        lbl_804CB2D0 = 10;
    } else {
        if (lbl_804CB2D0 > 0) {
            lbl_804CB2D0--;
            return;
        }
        name = fn_80068398(ch, lbl_803CAB38.b11);
    }
    if (!flagGet(&lbl_803CAB38, lbl_80361684 + 0x1E)) {
        o = fn_8024F3FC(0);
        if (!o || !o->v10()) {
            fn_80251838(0, name, 0.0f);
            return;
        }
        if (fn_80291188(o->c->name, name)) {
            o->v24(1000);
            o->vC();
            return;
        }
    }
    {
        int k = (s8)fn_8024F7EC(name);
        if (k == -1) return;
        o = fn_8024F3FC(k);
    }
    if (Has(fn_80068424(fn_8006074C(&lbl_803CAB38), lbl_803CAB38.b11)) == 1 || (s8)fn_8024F92C(lbl_80361684 + 0x2A) != -1 || (s8)fn_8024F92C(lbl_80361684 + 0x3B) != -1) {
        if (o && !o->v34()) {
            o->v28(200);
        }
    } else {
        if (o && o->v34()) {
            o->v2C(1000);
            o->v38(1.0f, 1000.0f);
        }
    }
}
}
