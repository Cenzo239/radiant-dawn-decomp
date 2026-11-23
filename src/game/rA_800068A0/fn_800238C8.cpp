#include "game/rA_800068A0/types.h"
/* Enemy-range / unit-mark selection proc: updates the help text, the info window and handles the pad. */
typedef unsigned long long u64;
extern "C" {
extern char lbl_80361118[];
extern volatile u32 lbl_804CB700;
extern u8 lbl_803EC898[];
extern u8 lbl_803CAB38[];
extern u8 lbl_803CA870[];
struct UDef { u8 x0[8]; u8 x8; };
struct Unit {
    u8 pad[0xE8];
    Unit* next;
    u8 pad2[8];
    UDef* def;
    u8 pad3[0x10];
    u64 flags;
};
struct UList { u8 pad[0xC]; Unit* c; };
extern UList* lbl_804CB814;
extern Unit* lbl_804CB100;
struct Cfg { u8 x0[0x11]; u8 b11; };
extern Cfg* fn_80060728(void*);
struct Z64 { u8 x0[0x64]; const char* s64; };
struct Proc { u8 x0[0x54]; u8 b54; };
extern Unit* fn_800677E4(void);
extern u8 fn_8010E314(int, u8);
extern Z64* fn_801E5640(void*, int, int);
extern void fn_8013F204(void);
extern void fn_8013F1C4(void);
extern void fn_80067168(Unit*);
extern void fn_80185720(void);
extern void fn_800451D4(void*, Unit*);
extern void fn_80083DC4(void*, int);
extern void fn_80114D00(void*);
extern void fn_80253EE4(const char*, f32);
class Pad {
public:
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2C();
    virtual void v30();
    virtual u32 v34();
    virtual void v38();
    virtual void v3C();
    virtual void v40();
    virtual void v44();
    virtual u32 v48();
    virtual void v4C();
    virtual int v50();
    virtual int v54();
};
extern Pad* lbl_804CB5B8;
#define MARK 0x800
static inline void setHelp(void* p, const char* const& s) {
    Z64* z = fn_801E5640(p, -0x1000, 0);
    if (z != 0) {
        z->s64 = s;
    }
}
static inline int blocked(void) {
    u32 f1 = lbl_804CB700;
    u32 f2 = lbl_804CB700;
    int r = 0;
    if ((f1 & 0x10) && !(f2 & 0x20)) {
        r = 1;
    }
    return r;
}
void fn_800238C8(Proc* p) {
    Unit* sel;
    Unit* cur;
    sel = fn_800677E4();
    if (sel != 0) {
        if (fn_8010E314(0, sel->def->x8) == 1) {
            if (!(sel->flags & MARK)) {
                { const char* s = lbl_80361118 + 0x28; setHelp(p, s); }
            } else {
                { const char* s = lbl_80361118 + 0x3E; setHelp(p, s); }
            }
        } else {
            { const char* s = lbl_80361118 + 0x54; setHelp(p, s); }
        }
    } else {
        int any = 0;
        Unit* u;
        for (u = lbl_804CB814->c; u != 0; ) {
            u64 f = u->flags;
            u = u->next;
            if (f & MARK) {
                any = 1;
                break;
            }
        }
        if (!any) {
            { const char* s = lbl_80361118 + 0x6A; setHelp(p, s); }
        } else {
            { const char* s = lbl_80361118 + 0x80; setHelp(p, s); }
        }
    }
    if (fn_80060728(lbl_803CAB38)->b11 != 2) {
        cur = fn_800677E4();
        if (cur == 0 && (lbl_804CB700 & 0x400)) {
            fn_8013F204();
        }
        if (blocked() || (!(lbl_804CB5B8->v34() & 0xF) && lbl_804CB5B8->v50() == 0 && lbl_804CB5B8->v54() == 0)) {
            if (lbl_804CB100 != cur || !(lbl_804CB700 & 0x400)) {
                lbl_804CB100 = cur;
                if (cur == 0 || cur->def->x8 == 0) {
                    if (lbl_804CB700 & 0x400) {
                        fn_8013F204();
                    }
                } else {
                    fn_80067168(cur);
                    fn_8013F1C4();
                }
            }
        }
    }
    if (blocked()) return;
    u32 in = lbl_804CB5B8->v48();
    if (sel != 0 && (in & 0x2000)) {
        fn_80185720();
        if (lbl_804CB700 & 0x400) {
            fn_8013F204();
        }
        fn_800451D4(lbl_803CA870, sel);
        p->b54 = 2;
        fn_80083DC4(p, 10);
    } else if (in & 0x400) {
        if (sel != 0 && fn_8010E314(0, sel->def->x8) == 1) {
            if (fn_80060728(lbl_803CAB38)->b11 == 2) return;
            if (!(sel->flags & MARK)) {
                sel->flags |= MARK;
                fn_80114D00(lbl_803EC898);
                fn_80067168(sel);
                fn_80253EE4(lbl_80361118 + 0x96, 0.0f);
            }
            return;
        }
        goto cancel;
    } else if (in & 0x800) {
        if (sel != 0 && fn_8010E314(0, sel->def->x8) == 1) {
            if (sel->flags & MARK) {
                sel->flags &= ~(u64)MARK;
                fn_80114D00(lbl_803EC898);
                fn_80067168(sel);
                fn_80253EE4(lbl_80361118 + 0xB1, 0.0f);
            }
        } else if (sel == 0) {
            Unit* n;
            int any;
            Unit* u;
            any = 0;
            for (u = lbl_804CB814->c; u != 0; u = n) {
                n = u->next;
                if (u->flags & MARK) {
                    u->flags &= ~(u64)MARK;
                    any = 1;
                }
            }
            if (any) {
                fn_80253EE4(lbl_80361118 + 0xB1, 0.0f);
                fn_80114D00(lbl_803EC898);
            }
        }
    } else if (in & 0x10) {
    cancel:
        if (lbl_804CB700 & 0x400) {
            fn_8013F204();
        }
        fn_80253EE4(lbl_80361118 + 0xCC, 0.0f);
        fn_80083DC4(p, 1);
    } else if (in & 0x4000) {
        if (lbl_804CB700 & 0x400) {
            fn_8013F204();
        }
        p->b54 = 2;
        fn_80083DC4(p, 5);
    }
}
}
