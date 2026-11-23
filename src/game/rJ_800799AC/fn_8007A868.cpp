/* Per-frame controller probing: replaces each slot's object when the attached device changes. */
#include "game/rJ_800799AC/pad.h"

struct WiiData {
    u8 p00[0x5C];
    u8 type; /* 0x5C */
    s8 err;  /* 0x5D */
    u8 p5E[0x840 - 0x5E];
};

/* The file statics at lbl_803D7918 */
static Pad* pads[4];
static PadStatus status[4];
static WiiData data[4];

extern "C" {

extern void* lbl_80380978[];
extern void* lbl_80380A64[];
extern void* lbl_80380B50[];
extern void* lbl_80380C3C[];
extern void* lbl_80380D28[];
extern void* lbl_80380E14[];
extern void* lbl_80380F00[];
extern const u32 lbl_80362560[4];
int OSDisableInterrupts(void);
void OSRestoreInterrupts(int level);
void* fn_80079940(int size, int align);
s8 fn_80336D18(int i, u32* type);
int fn_8030CBF8(int i, void* data, int n);
void fn_8030D66C(int i);
void fn_8030AAF4(int i);
void fn_803231C0(PadStatus* s);
void fn_80322E50(u32 mask);
extern int lbl_804CB5BC;
extern Pad* lbl_804CB5B8;
void* fn_8007A4FC(int size);
int fn_8007A504(void* p);
void fn_80323064(void);
void* memset(void* p, int v, u32 n);
void SISetSamplingRate(int r);
void fn_8032FAD0(void);
void fn_80335A94(void* a, void* b);
void fn_8030D310(void);
int fn_80337348(void);

}

struct IntGuard {
    void* vt;
    int level;
    IntGuard() {
        vt = lbl_80380F00;
        level = OSDisableInterrupts();
    }
    ~IntGuard() {
        vt = lbl_80380F00;
        OSRestoreInterrupts(level);
    }
};

static inline void REPLACE(Pad*& slot, int i, void** vtbl, int kind) {
    IntGuard g;
    Pad* p;
    if (slot != 0) {
        slot->v08(1);
    }
    p = (Pad*)fn_80079940(0x5C, 0x40);
    if (p != 0) {
        *(void***)p = lbl_80380E14;
        p->f4 = 4;
        p->f8 = 4;
        p->v0C(i);
        *(void***)p = vtbl;
        p->vD0(kind);
        p->vD4(p->v14());
        fn_8030D66C(i);
        fn_8030AAF4(i);
    }
    slot = p;
}

/* The ClampStick of the SDK's PADClamp, without the dead-zone subtraction */
static inline void ClampStick(s8* px, s8* py, s8 max, s8 xy, s8 min) {
    int d;
    int signY;
    int signX;
    int y;
    int x;
    x = *px;
    y = *py;

    if (0 <= x) {
        signX = 1;
    } else {
        signX = -1;
        x = -x;
    }

    if (0 <= y) {
        signY = 1;
    } else {
        signY = -1;
        y = -y;
    }

    if (x <= min) {
        x = 0;
    }
    if (y <= min) {
        y = 0;
    }

    if (x == 0 && y == 0) {
        *px = *py = 0;
        return;
    }

    if (xy * y <= xy * x) {
        d = xy * x + (max - xy) * y;
        if (xy * max < d) {
            x = (s8)(xy * max * x / d);
            y = (s8)(xy * max * y / d);
        }
    } else {
        d = xy * y + (max - xy) * x;
        if (xy * max < d) {
            x = (s8)(xy * max * x / d);
            y = (s8)(xy * max * y / d);
        }
    }

    *px = (s8)(signX * x);
    *py = (s8)(signY * y);
}

static inline void ClampTrigger(u8* trigger, u8 min, u8 max) {
    if (*trigger <= min) {
        *trigger = 0;
    } else if (max < *trigger) {
        *trigger = max;
    }
}

extern "C" {

#pragma use_lmw_stmw on
static inline void mkPad(Pad*& slot, int i) {
    Pad* p;
    if (slot != 0) {
        if (slot != 0) {
            slot->v08(1);
        }
    }
    p = (Pad*)fn_80079940(0x5C, 0x40);
    if (p != 0) {
        *(void***)p = lbl_80380E14;
        p->f4 = 4;
        p->f8 = 4;
        p->v0C(i);
        *(void***)p = lbl_80380D28;
        p->vD0(4);
        p->vD4(p->v14());
        fn_8030D66C(i);
        fn_8030AAF4(i);
    }
    slot = p;
}
void fn_8007A528(void) {
    int i;
    fn_80323064();
    memset(status, 0, 0x30);
    SISetSamplingRate(1);
    fn_8032FAD0();
    fn_80335A94(fn_8007A4FC, fn_8007A504);
    fn_8030D310();
    memset(data, 0, 0x2100);
    for (i = 0; i < 4; i++) {
        mkPad(pads[i], i);
    }
    if (fn_80337348() != 0) {
        lbl_804CB5BC |= 2;
    }
    lbl_804CB5BC |= 1;
    lbl_804CB5B8 = pads[0];
}

void fn_8007A868(void) {
u32 conn = 0;
u32 reset;
Pad** pp;
int i;
    pp = pads;
    for (i = 0; i < 4; i++, pp++) {
        (*pp)->vB0(-1);
    }
    for (i = 0; i < 4; i++) {
        u32 type = 0xFF;
        WiiData* w = &data[i];
        int n;
        w->err = fn_80336D18(i, &type);
        w->type = type;
        n = fn_8030CBF8(i, w, 0x10);
        if (w->err == 0 && n <= 0) {
            w->err = -2;
        }
        switch (w->err) {
        case 0:
            switch (w->type) {
            case 0xFB:
            case 0xFC:
            case 0xFF:
                w->type = 0;
            case 0:
                conn |= 1 << i;
                if (pads[i]->v14() != 0) {
                    REPLACE(pads[i], i, lbl_80380C3C, 0);
                }
                break;
            case 1:
                conn |= 1 << i;
                if (pads[i]->v14() != 1) {
                    REPLACE(pads[i], i, lbl_80380B50, 1);
                }
                break;
            case 2:
                conn |= 1 << i;
                if (pads[i]->v14() != 2) {
                    REPLACE(pads[i], i, lbl_80380A64, 2);
                }
                break;
            case 0xFE:
                break;
            }
            pads[i]->vB0(0);
            break;
        case -1:
            pads[i]->vB0(-1);
            break;
        case -2:
            conn |= 1 << i;
            pads[i]->vB0(-2);
            break;
        case -3:
            conn |= 1 << i;
            pads[i]->vB0(-3);
            break;
        case -4:
            conn |= 1 << i;
            pads[i]->vB0(-4);
            break;
        case -5:
        case -6:
            break;
        case -7:
            conn |= 1 << i;
            pads[i]->vB0(-5);
            break;
        }
    }
    reset = 0;
    fn_803231C0(status);
    for (i = 0; i < 4; i++) {
        PadStatus* s = &status[i];
        ClampStick(&s->stickX, &s->stickY, 72, 47, 15);
        ClampStick(&s->substickX, &s->substickY, 59, 31, 15);
        ClampTrigger(&s->triggerL, 30, 180);
        ClampTrigger(&s->triggerR, 30, 180);
        switch (s->err) {
        case 0:
            if (!(conn & (1 << i))) {
                conn |= 1 << i;
                if (pads[i]->v14() != 3) {
                    REPLACE(pads[i], i, lbl_80380978, 3);
                }
                pads[i]->vB0(0);
            }
            break;
        case -1:
            reset |= lbl_80362560[i];
            if (!(conn & (1 << i))) {
                pads[i]->vB0(-1);
            }
            break;
        case -2:
            if (!(conn & (1 << i))) {
                conn |= 1 << i;
                pads[i]->vB0(-2);
            }
            break;
        case -3:
            if (!(conn & (1 << i))) {
                conn |= 1 << i;
                pads[i]->vB0(-3);
            }
            break;
        }
    }
    if (reset != 0) {
        fn_80322E50(reset);
    }
    for (i = 0; i < 4; i++) {
        if (!(conn & (1 << i))) {
            if (pads[i]->v14() != 4) {
                REPLACE(pads[i], i, lbl_80380D28, 4);
            }
        }
    }
}

void fn_8007B2F4(void) {
    int i;
    fn_8007A868();
    for (i = 0; i < 4; i++) {
        Pad* p = pads[i];
        if (p->v14() != 4) {
            switch (p->vB4()) {
            case 0:
                switch (p->v14()) {
                case 0:
                case 1:
                case 2:
                    p->vC4(&data[i], &status[i]);
                    break;
                case 3:
                    p->vC4(&data[i], &status[i]);
                    break;
                }
                break;
            case -1:
                p->vB8();
                break;
            default:
                p->vC0();
                break;
            }
            p->vC8();
            p->vCC();
        }
    }
}

void fn_8007B458(void) {
    int i;
    fn_8007A868();
    for (i = 0; i < 4; i++) {
        Pad* p = pads[i];
        if (p->v14() != 4) {
            switch (p->vB4()) {
            case 0:
                switch (p->v14()) {
                case 0:
                case 1:
                case 2:
                    p->vC4(&data[i], &status[i]);
                    break;
                case 3:
                    p->vC4(&data[i], &status[i]);
                    break;
                }
                break;
            case -1:
                p->vB8();
                break;
            default:
                p->vC0();
                break;
            }
        }
    }
}

#pragma use_lmw_stmw off

}
