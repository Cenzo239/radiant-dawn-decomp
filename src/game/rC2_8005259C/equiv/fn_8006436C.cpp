/* EQUIVALENT (regs, round 19b): fn_8006436C, input handler of the two-column item exchange screen (object O made by fn_800656BC). 
 * Strings are the function's own pool lbl_80362168 ("MW_IPTR", "MW_ISTR", "SFX_SYS_SELECT1", "SFX_SYS_CANCEL1").
 * prevOn/nextOn (fixed column) and prevIn/nextIn (current column) are the same search written two ways only to reproduce the addressing; a port can merge them. */
#pragma pool_strings on
extern "C" {
typedef unsigned char u8;
typedef signed char s8;
typedef short s16;
typedef unsigned int u32;
typedef float f32;
typedef int BOOL;
struct F { u32 f0; u32 flags; };
struct Slot { s16 x, y; u8 item[0x28]; u8 enabled, pad[3]; };
struct O {
    u8 pad[0x28]; s16 state; u8 p2a[6]; void* a; void* b; s16 x38, x3a;
    s8 side, index, oldSide, oldIndex; u8 flag, phase, x42, mode, filter, x45, p46[2]; void* child;
};
struct Win { u32 flags; u8 pad[0x40]; };
extern Slot lbl_803CB4D0[2][7];
extern Win lbl_8041EB20;
extern char lbl_8037F8F8[];
struct Pad { virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34(); virtual void v38(); virtual u32 v3C(); virtual void v40(); virtual void v44(); virtual u32 v48(); };
extern Pad* lbl_804CB5B8;
void fn_80253EE4(const char*, f32);
const char* fn_800D0864(const char*);
int fn_801A2224(void*);
void fn_801A1F64(void*, void*, f32, f32);
void fn_801A1BE0(void*, void*, void*, f32, f32);
void fn_801A23E0(int, int, const char*, void*);
void fn_801A1CFC(void*);
void fn_80083DC4(void* p, int n);
F* fn_801116B8(void*);

static inline int prevOn(int row, int i) {
    Slot* p = &lbl_803CB4D0[0][i];
    for (;; p--, i--) {
        if (i < 0) break;
        if (p[row * 7].enabled) break;
    }
    return i;
}
static inline int nextOn(int row, int i) {
    Slot* p = &lbl_803CB4D0[0][i];
    for (;; p++, i++) {
        if (i >= 7) { i = -1; break; }
        if (p[row * 7].enabled) break;
    }
    return i;
}
static inline int prevIn(int row, int i) {
    Slot* p = &lbl_803CB4D0[row][i];
    for (;; p--, i--) {
        if (i < 0) break;
        if (p->enabled) break;
    }
    return i;
}
static inline int nextIn(int row, int i) {
    Slot* p = &lbl_803CB4D0[row][i];
    for (;; p++, i++) {
        if (i >= 7) { i = -1; break; }
        if (p->enabled) break;
    }
    return i;
}
static inline void ask(O* o, int index, int side, const char* key) {
    fn_801A23E0(lbl_803CB4D0[side][index].x, lbl_803CB4D0[side][index].y + 0x28, fn_800D0864(key), o);
}
static inline BOOL usable(Slot* s) {
    BOOL c = 1;
    F* f = fn_801116B8(s->item);
    if (!(f->f0 & 0x1000000)) { if (!((s->item[5] >> 2) & 1)) c = 0; }
    return c;
}
static inline Slot* cur(O* o) { return &lbl_803CB4D0[o->side][o->index]; }

void fn_8006436C(O* o) {
    u32 btn = lbl_804CB5B8->v3C();
    u32 rep = lbl_804CB5B8->v48();
    int side;
    int index;
    index = o->index;
    side = o->side;
    int i;
    if ((btn & 0x100001) && side == 1) {
        i = prevOn(0, o->index);
        if (i < 0) i = nextOn(0, o->index);
        if (i < 0) goto end;
        o->index = i;
        o->side = 0;
    }
    if ((btn & 0x200002) && o->side == 0) {
        i = prevOn(1, o->index);
        if (i < 0) i = nextOn(1, o->index);
        if (i < 0) goto end;
        o->index = i;
        o->side = 1;
    }
    if (btn & 0x800008) {
        i = prevIn(o->side, o->index - 1);
        if (i < 0) {
            if (!(rep & 0x800008)) goto end;
            i = prevIn(o->side, 6);
        }
        o->index = i;
    }
    if (btn & 0x400004) {
        i = nextIn(o->side, o->index + 1);
        if (i < 0) {
            if (!(rep & 0x400004)) goto end;
            i = nextIn(o->side, 0);
        }
        o->index = i;
    }
    if (side != o->side || index != o->index) {
        fn_80253EE4(lbl_8037F8F8, 0.0f);
        if (fn_801A2224(&lbl_8041EB20)) {
            Slot* s = cur(o);
            fn_801A1F64(&lbl_8041EB20, s->item, s->x, s->y + 0x28);
        }
    }
end:
    rep = lbl_804CB5B8->v48();
    if (fn_801A2224(&lbl_8041EB20)) {
        if (rep & 0x2800) {
            fn_801A1CFC(&lbl_8041EB20);
        }
    } else if (rep & 0x400) {
        BOOL a = 0;
        Slot* s = cur(o);
        if (*(void**)s->item && (fn_801116B8(s->item)->flags & 4)) {
            a = 1;
        }
        if (a) {
            ask(o, o->index, o->side, "MW_IPTR");
        } else {
            BOOL b = 0;
            Slot* s2 = cur(o);
            if (*(void**)s2->item) {
                if (usable(s2)) b = 1;
            }
            if (b) {
                ask(o, o->index, o->side, "MW_ISTR");
            } else {
                fn_80083DC4(o, 1);
                fn_80253EE4("SFX_SYS_SELECT1", 0.0f);
            }
        }
    } else if (rep & 0x800) {
        fn_80083DC4(o, 2);
        fn_80253EE4("SFX_SYS_CANCEL1", 0.0f);
    } else if (rep & 0x2000) {
        Slot* s = cur(o);
        fn_801A1BE0(&lbl_8041EB20, o, s->item, s->x, s->y + 0x28);
        lbl_8041EB20.flags |= 2;
    }
}
}
