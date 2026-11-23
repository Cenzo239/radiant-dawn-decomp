/* Controller polling. */
#include "game/rJ_800799AC/pad.h"

struct PadData {
    Pad* pads[4];        /* 0x00 */
    u8 status[4][0xC];   /* 0x10 */
    u8 data[4][0x840];   /* 0x40 */
};

extern "C" {

extern PadData lbl_803D7918;
void fn_8007A868(void);

/* Update key repeat */
void fn_8007B6A4(Pad* p) {
    p->press = p->repeat = p->v48();
    if (p->v34() != 0 && p->prev == p->v34()) {
        if (--p->repDelay == 0) {
            p->press |= p->v34();
            p->repDelay = p->vDC();
        }
        if (--p->repRate == 0) {
            p->repeat |= p->v34();
            p->repRate = p->vDC() >> 1;
        }
    } else {
        p->repDelay = p->repRate = p->vD8();
    }
    if (p->rumble > 0 && --p->rumble == 0) {
        p->vAC();
    }
}

/* Latch the raw state into held, applying the disable mask */
void fn_8007B830(Pad* p) {
    int hi;
    int lo;
    p->prev = p->held;
    p->held = p->raw;
    if (p->v94(0xFFFFFFFF) != 0) {
        p->held &= ~p->flags2;
        if (p->v94(0x100000) != 0 && p->axis[0] < 0) {
            p->axis[0] = 0;
        }
            if (p->v94(0x200000) != 0 && p->axis[0] > 0) {
            p->axis[0] = 0;
        }
            if (p->v94(0x400000) != 0 && p->axis[1] < 0) {
            p->axis[1] = 0;
        }
            if (p->v94(0x800000) != 0 && p->axis[1] > 0) {
            p->axis[1] = 0;
        }
            if (p->v94(0x1000000) != 0 && p->axis[2] < 0) {
            p->axis[2] = 0;
        }
            if (p->v94(0x2000000) != 0 && p->axis[2] > 0) {
            p->axis[2] = 0;
        }
            if (p->v94(0x4000000) != 0 && p->axis[3] < 0) {
            p->axis[3] = 0;
        }
            if (p->v94(0x8000000) != 0 && p->axis[3] > 0) {
            p->axis[3] = 0;
        }
            if (p->v94(0x40) != 0 && p->axis[4] > 0) {
            p->axis[4] = 0;
        }
            if (p->v94(0x80) != 0 && p->axis[5] > 0) {
            p->axis[5] = 0;
        }
            if (p->v94(0x100) != 0 && p->axis[6] > 0) {
            p->axis[6] = 0;
        }
            if (p->v94(0x200) != 0 && p->axis[7] > 0) {
            p->axis[7] = 0;
        }
        }
    hi = p->vE0();
    lo = -hi;
    if (p->v50() < lo) {
        p->held |= 0x100000;
    }
    if (p->v50() > hi) {
        p->held |= 0x200000;
    }
    if (p->v54() < lo) {
        p->held |= 0x400000;
    }
    if (p->v54() > hi) {
        p->held |= 0x800000;
    }
    if (p->v58() < lo) {
        p->held |= 0x1000000;
    }
    if (p->v58() > hi) {
        p->held |= 0x2000000;
    }
    if (p->v5C() < lo) {
        p->held |= 0x4000000;
    }
    if (p->v5C() > hi) {
        p->held |= 0x8000000;
    }
}

/* Accumulate one PADStatus sample into the raw state */
int fn_8007BCA4(Pad* p, PadStatus* s) {
    u32 old = p->raw;
    if (s->err != 0) {
        return 0;
    }
    if (s->button & 1) {
        p->raw |= 1;
    }
    if (s->button & 2) {
        p->raw |= 2;
    }
    if (s->button & 4) {
        p->raw |= 4;
    }
    if (s->button & 8) {
        p->raw |= 8;
    }
    if (s->button & 0x10) {
        p->raw |= 0x10;
    }
    if (s->button & 0x40) {
        p->raw |= 0x40;
    }
    if (s->button & 0x20) {
        p->raw |= 0x100;
    }
    if (s->button & 0x100) {
        p->raw |= 0x400;
    }
    if (s->button & 0x200) {
        p->raw |= 0x800;
    }
    if (s->button & 0x400) {
        p->raw |= 0x1000;
    }
    if (s->button & 0x800) {
        p->raw |= 0x2000;
    }
    if (s->button & 0x1000) {
        p->raw |= 0x4000;
    }
    p->axis[0] += s->stickX;
    p->axis[1] += s->stickY;
    p->axis[2] += s->substickX;
    p->axis[3] += s->substickY;
    p->axis[4] += s->triggerL;
    p->axis[6] += s->triggerR;
    return old != p->raw || s->stickX != 0 || s->stickY != 0 || s->substickX != 0 || s->substickY != 0 ||
           s->triggerL != 0 || s->triggerR != 0;
}

extern int lbl_804CB5BC;
void fn_803234A0(int chan, int cmd);
void fn_80337248(int chan, int cmd);
int fn_80337348(void);
void fn_80079978(void* p);
extern void* lbl_80380978[];
extern void* lbl_80380A64[];
extern void* lbl_80380B50[];

/* Pad::Rumble, base version */
void fn_8007C06C(Pad* p, int t) {
    if (p->vA4() != 0 && (lbl_804CB5BC & 2) && t > 0) {
        fn_803234A0(p->chan, 1);
        p->rumble = t;
    }
}

/* Read a GameCube pad sample */
void fn_8007C0E4(Pad* p, u8* wii, PadStatus* s) {
    p->rawPrev = p->raw;
    p->vBC();
    if (s->button & 0x1) {
        p->raw |= 0x1;
    }
    if (s->button & 0x2) {
        p->raw |= 0x2;
    }
    if (s->button & 0x4) {
        p->raw |= 0x4;
    }
    if (s->button & 0x8) {
        p->raw |= 0x8;
    }
    if (s->button & 0x10) {
        p->raw |= 0x10;
    }
    if (s->button & 0x40) {
        p->raw |= 0x40;
    }
    if (s->button & 0x20) {
        p->raw |= 0x100;
    }
    if (s->button & 0x100) {
        p->raw |= 0x400;
    }
    if (s->button & 0x200) {
        p->raw |= 0x800;
    }
    if (s->button & 0x400) {
        p->raw |= 0x1000;
    }
    if (s->button & 0x800) {
        p->raw |= 0x2000;
    }
    if (s->button & 0x1000) {
        p->raw |= 0x4000;
    }
    if (*(u32*)(wii + 0x60) & 0x800) {
        p->raw |= 0x30000;
    }
    if (*(u32*)wii & 0x8000) {
        p->raw |= 0x10000;
    }
    p->axis[0] = s->stickX;
    p->axis[1] = s->stickY;
    p->axis[2] = s->substickX;
    p->axis[3] = s->substickY;
    p->axis[4] = s->triggerL;
    p->axis[5] = 0;
    p->axis[6] = s->triggerR;
    p->axis[7] = 0;
    p->vD4(p->v14());
}

/* Destructor of the Wii Remote pad */
Pad* fn_8007C30C(Pad* p, int del) {
    if (p != 0) {
        *(void***)p = lbl_80380978;
        p->vAC();
        if (del > 0) {
            fn_80079978(p);
        }
    }
    return p;
}

void fn_8007C374(Pad* p) {
    fn_803234A0(p->chan, 0);
    fn_80337248(p->chan, 0);
    p->rumble = 0;
}

void fn_8007C3BC(Pad* p, int t) {
    if (p->vA4() != 0 && (lbl_804CB5BC & 2) && t > 0) {
        switch (p->v18()) {
        case 3:
            fn_803234A0(p->chan, 1);
            break;
        default:
            if (!(lbl_804CB5BC & 4)) {
                fn_80337248(p->chan, 1);
            }
            break;
        }
        p->rumble = t;
    }
}

int fn_8007C468(Pad* p) {
    switch (p->v18()) {
    case 3:
        return 1;
    default:
        return fn_80337348() != 0;
    }
}

int fn_8007C304(void) {
    return 0x4140;
}

int fn_8007CA68(void) {
    return 0x30140;
}

Pad* fn_8007CA74(Pad* p, int del) {
    if (p != 0) {
        *(void***)p = lbl_80380A64;
        p->vAC();
        if (del > 0) {
            fn_80079978(p);
        }
    }
    return p;
}

int fn_8007CADC(void) {
    return -1;
}

void fn_8007CAE4(Pad* p) {
    fn_803234A0(p->chan, 0);
    fn_80337248(p->chan, 0);
    p->rumble = 0;
}

void fn_8007CB2C(Pad* p, int t) {
    if (p->vA4() != 0 && (lbl_804CB5BC & 2) && t > 0) {
        switch (p->v18()) {
        case 3:
            fn_803234A0(p->chan, 1);
            break;
        default:
            fn_80337248(p->chan, 1);
            break;
        }
        p->rumble = t;
    }
}

int fn_8007CBCC(Pad* p) {
    switch (p->v18()) {
    case 3:
        return 1;
    default:
        return fn_80337348() != 0;
    }
}


Pad* fn_8007D418(Pad* p, int del) {
    if (p != 0) {
        *(void***)p = lbl_80380B50;
        p->vAC();
        if (del > 0) {
            fn_80079978(p);
        }
    }
    return p;
}

void fn_8007D480(Pad* p) {
    fn_803234A0(p->chan, 0);
    fn_80337248(p->chan, 0);
    p->rumble = 0;
}

void fn_8007D4C8(Pad* p, int t) {
    if (p->vA4() != 0 && (lbl_804CB5BC & 2) && t > 0) {
        switch (p->v18()) {
        case 3:
            fn_803234A0(p->chan, 1);
            break;
        default:
            fn_80337248(p->chan, 1);
            break;
        }
        p->rumble = t;
    }
}

int fn_8007D568(Pad* p) {
    switch (p->v18()) {
    case 3:
        return 1;
    default:
        return fn_80337348() != 0;
    }
}

extern void* lbl_80380C3C[];

Pad* fn_8007DDB4(Pad* p, int del) {
    if (p != 0) {
        *(void***)p = lbl_80380C3C;
        p->vAC();
        if (del > 0) {
            fn_80079978(p);
        }
    }
    return p;
}

void fn_8007DE1C(Pad* p) {
}

int fn_8007DE20(Pad* p) {
    return 0;
}

void fn_8007DE28(Pad* p) {
    p->vB8();
    p->v10();
}

Pad* fn_8007DE74(Pad* p, int del) {
    if (p != 0 && del > 0) {
        fn_80079978(p);
    }
    return p;
}

int fn_8007DEB4(Pad* p) {
    return p->v68();
}

int fn_8007DEC4(Pad* p) {
    return p->v60();
}

int fn_8007DED4(Pad* p) {
    return p->v40();
}

}
