#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/vobj.h"
#include "game/rI_801DD7D4/rlist.h"

extern "C" {

typedef struct Seq {
    u8 pad[0x30];
    s8 x30;
    u8 pad31[3];
    RList list;
    f32 x44;
} Seq;

#pragma auto_inline off
extern s8 lbl_804CBE30;
extern char lbl_804CA958[8];
extern char lbl_804CA960[8];
extern char lbl_804CA950[8];
extern char lbl_804CA948[8];
extern char lbl_8038CBC8[];
extern char lbl_8038CBE8[];
extern char lbl_8038CC18[];
extern char lbl_8038CC80[];
extern char lbl_803CAB38[];
extern VO0N* lbl_804CB5B8;
typedef struct HelpWin { u32 flags; u8 pad[0xd8 - 4]; s16 xd8; } HelpWin;
extern HelpWin lbl_8041EB20;
void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E7B4(void);
void fn_8007E7DC(u8);
void fn_8007E7E8(int);
void* fn_80081194(void*, void*);
void fn_801A1AC4(HelpWin*, void* parent, void* text, f32, f32);
void fn_801A1CFC(HelpWin*);
void fn_80083B78(void*);
#if TARGET_PC
FE10_PROTO void fn_801C6D2C(ptr32<const void>, void*, ptr32<const void>, ptr32<const void>, int);
#else
void fn_801C6D2C(void*, void*, void*, void*, int);
#endif
void* fn_80085708(const char*);
void fn_800893C4(void*);
void fn_800893D4(void*);
u8* fn_80060728(void*);
void fn_801BA39C(void*);
void fn_80253EE4(void*, f32);
#if TARGET_PC
FE10_PROTO void fn_80020764(int, int, int, int, p32arg);
#else
void fn_80020764(int, int, int, int, int);
#endif
void fn_801E6BD8(void);

#pragma use_lmw_stmw on
void fn_801E5558(Seq* o, RObj* c, int rec) {
    LNode* n;
    LNode* e;
    if (c == NULL) {
        return;
    }
    n = o->list.next;
    e = (LNode*)&o->list.prev;
    for (; n != e; n = n->next) {
        RObj* v = n->val;
        if (v == c) {
            n->prev->next = n->next;
            n->next->prev = n->prev;
            fn_80079210(n);
            o->list.size--;
            rRelease(c);
            return;
        }
        if (rec != 0 && v->contains(c, rec)) {
            return;
        }
    }
}

#pragma use_lmw_stmw off

void fn_801E5860(void) { lbl_804CBE30++; }
void fn_801E5870(void) { lbl_804CBE30--; }
void fn_801E5880(Seq* o) { o->x30++; }
void
#if TARGET_PC
*
#endif
fn_801E5890(Seq* o) {
#if TARGET_PC
o->x30--; return o;
#else
o->x30--;
#endif
}

class SeqItem : public RObj {
public:
    virtual void v14();
    virtual void v18();
    virtual void v1C(Seq*);
    virtual void v20(Seq*);
    virtual void v24();
    virtual void v28(Seq*);
};

void fn_801E58A0(Seq* o) {
    if (lbl_804CBE30 <= 0 && o->x30 <= 0) {
        LNode* n = o->list.next;
        LNode* e = (LNode*)&o->list.prev;
        for (; n != e; n = n->next) {
            ((SeqItem*)n->val)->v1C(o);
            ((SeqItem*)n->val)->v20(o);
        }
    }
    fn_8007E154();
    fn_8007E7B4();
    fn_8007E7DC(0xff);
    fn_8007E7E8(0x80);
    fn_8007E164();
}

static inline RObj* seqBack(Seq* o) {
    return o->list.size != 0 ? o->list.prev->val : NULL;
}

void fn_801E5954(Seq* o) {
    if (seqBack(o) != NULL) {
        ((SeqItem*)seqBack(o))->v28(o);
    }
}

typedef struct ProcH { u8 pad[0x30]; f32 x30, x34; u8 pad38[0x54 - 0x38]; void* x54; } ProcH;

static inline void helpSet(HelpWin* h) {
    u32 f = lbl_8041EB20.flags;
    h->xd8 = 1;
    lbl_8041EB20.flags = f | 2;
}

static inline void helpOpen(HelpWin* h, void* parent, void* c, f32 a, f32 b) {
    fn_801A1AC4(h, parent, c, a, b);
    helpSet(h);
}


void fn_801E6AE0(void* p) {
    if (!inputBlocked()) {
        if (lbl_804CB5B8->v48() & 0xF0FFFF) {
            fn_801A1CFC(&lbl_8041EB20);
            fn_80083B78(p);
        }
    }
}

void fn_801E6B64(void* a, void* parent, f32 x, f32 y) {
    ProcH* p = (ProcH*)fn_80081194(lbl_8038CBC8, parent);
    p->x30 = x;
    p->x34 = y;
    p->x54 = a;
}

typedef struct ProcA { u8 pad[0x30]; void* x30; void* x34; } ProcA;

void fn_801E6BBC(ProcA* p) {
    fn_801C6D2C(p->x30, p, p->x34, fn_801E6BD8, 0);
}

void fn_801E6BD8(void) {
    void* p;
    fn_801E5860();
    p = fn_80085708(lbl_804CA958);
    if (p != NULL) {
        fn_800893C4(p);
    }
}

void fn_801E6C0C(void) {}

void fn_801E6C10(void) {
    void* p;
    fn_801E5870();
    p = fn_80085708(lbl_804CA960);
    if (p != NULL) {
        fn_800893D4(p);
    }
}

void fn_801E6C44(void* a, void* parent, void* c) {
    ProcA* p = (ProcA*)fn_80081194(lbl_8038CBE8, parent);
    p->x30 = a;
    p->x34 = c;
}

void fn_801E6C8C(void) {
    void* p;
    fn_801E5870();
    p = fn_80085708(lbl_804CA950);
    if (p != NULL) {
        fn_800893D4(p);
    }
}

void fn_801E6CC0(ProcA* o) {
    void* v = o->x30;
    *(void**)(fn_80060728(lbl_803CAB38) + 0x28) = v;
    fn_801BA39C(o);
}

void fn_801E6D0C(void) {
    void* p;
    fn_801E5860();
    p = fn_80085708(lbl_804CA948);
    if (p != NULL) {
        fn_800893C4(p);
    }
}

void fn_801E6D40(void) { fn_80253EE4(lbl_8038CC80, 0.0f); }

void fn_801E6D50(void* a, void* parent) {
    ProcA* p = (ProcA*)fn_80081194(lbl_8038CC18, parent);
    p->x30 = a;
}

void fn_801E6D88(void) { fn_80020764(0, 0, 0x260, 0x1c0, 0); }

typedef struct va_list_ {
    char gpr;
    char fpr;
    char reserved[2];
    char* input_arg_area;
    char* reg_save_area;
} va_list_;
typedef struct GXColor { u8 r, g, b, a; } GXColor;
void fn_80290C84(char*, const char*, va_list_*);
void fn_800800D4(int);
void fn_80080330(f32, f32);
GXColor* fn_800CD204(int);
void fn_80080508(GXColor*);
void fn_80080B00(int, GXColor*, f32);
void fn_80080C24(char*);
void fn_80080308(void);

void fn_801E6DA0(int x, int y, int col, const char* fmt, ...) {
#if TARGET_PC
    /* Host: a host va_list; fn_80290C84 (vsprintf) gets its address, as on the Wii */
    __builtin_va_list ap;
    char buf[0x100];
    __builtin_va_start(ap, fmt);
    fn_80290C84(buf, fmt, (va_list_*)&ap);
    __builtin_va_end(ap);
#else
    va_list_ ap;
    char buf[0x100];
    __builtin_va_info(&ap);
    fn_80290C84(buf, fmt, &ap);
#endif
    fn_800800D4(5);
    fn_80080330(x, y);
    {
        GXColor c = *fn_800CD204(col);
        fn_80080508(&c);
    }
    fn_80080B00(1, fn_800CD204(0x2a), 1.0f);
    fn_80080C24(buf);
    fn_80080308();
}

void fn_801E6EE8(int mode, int x, int y, int col, const char* fmt, ...) {
#if TARGET_PC
    /* Host: a host va_list; fn_80290C84 (vsprintf) gets its address, as on the Wii */
    __builtin_va_list ap;
    char buf[0x100];
    __builtin_va_start(ap, fmt);
    fn_80290C84(buf, fmt, (va_list_*)&ap);
    __builtin_va_end(ap);
#else
    va_list_ ap;
    char buf[0x100];
    __builtin_va_info(&ap);
    fn_80290C84(buf, fmt, &ap);
#endif
    fn_800800D4(mode);
    fn_80080330(x, y);
    {
        GXColor c = *fn_800CD204(col);
        fn_80080508(&c);
    }
    fn_80080B00(1, fn_800CD204(0x2a), 1.0f);
    fn_80080C24(buf);
    fn_80080308();
}

}
