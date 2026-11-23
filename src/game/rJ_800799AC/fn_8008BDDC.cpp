/* video.cpp: DisplayInit. Picks the render mode from the TV format, the reset code and the
 * console settings, and arms a one-shot alarm. Names guessed (the SDK ones from behaviour).
 * The five render modes are the original table at lbl_803811D0 (values read from main.dol);
 * they are separate file statics because the code addresses them from one pooled base. */
#include "game/rJ_800799AC/types.h"

struct GXRenderModeObj {
    u32 viTVmode;
    u16 fbWidth;
    u16 efbHeight;
    u16 xfbHeight;
    u16 viXOrigin;
    u16 viYOrigin;
    u16 viWidth;
    u16 viHeight;
    u32 xFBmode;
    u8 field_rendering;
    u8 aa;
    u8 sample_pattern[12][2];
    u8 vfilter[7];
};
struct OSAlarm { u8 pad[0x30]; };

#define SAMPLE6 {{6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}}
static GXRenderModeObj sNtscInt = {0, 608, 448, 448, 27, 16, 666, 448, 1, 0, 0, SAMPLE6, {8, 8, 10, 12, 10, 8, 8}};
static GXRenderModeObj sProg = {2, 608, 448, 448, 27, 16, 666, 448, 0, 0, 0, SAMPLE6, {0, 0, 21, 22, 21, 0, 0}};
static GXRenderModeObj sPalInt = {4, 608, 448, 530, 27, 22, 666, 530, 1, 0, 0, SAMPLE6, {8, 8, 10, 12, 10, 8, 8}};
static GXRenderModeObj sEu60Int = {0x14, 608, 448, 448, 27, 16, 666, 448, 1, 0, 0, SAMPLE6, {8, 8, 10, 12, 10, 8, 8}};
static GXRenderModeObj sMpalInt = {8, 608, 448, 448, 27, 16, 666, 448, 1, 0, 0, SAMPLE6, {8, 8, 10, 12, 10, 8, 8}};

extern "C" {
extern volatile u32 lbl_804CB5F4;           /* display flags */
extern GXRenderModeObj* lbl_804CB5F8;       /* interlaced mode */
extern GXRenderModeObj* lbl_804CB5FC;       /* progressive / 60 Hz mode */
extern u32 lbl_804CBF3C;
extern OSAlarm lbl_803E4EC8;
void fn_8032FAD0(void);                      /* VIInit */
int VIGetTvFormat(void);
void OSPanic(const char* file, int line, const char* msg, ...);
void fn_80331608(void);
int fn_803315F8(void);
u32 OSGetResetCode(void);
int fn_80331388(void);
int fn_80331328(void);
u8 fn_80325984(void);                        /* SCGetProgressiveMode */
u8 fn_803258B8(void);                        /* SCGetEuRgb60Mode */
void fn_80234F1C(GXRenderModeObj*);
void fn_80317974(OSAlarm*);                  /* OSCreateAlarm */
void fn_80317BD4(OSAlarm*, s64, void (*)(void)); /* OSSetAlarm */
void fn_8008BDCC(void);
void fn_80304C74(u32* color, u32 z);         /* GXSetCopyClear */
void* fn_802356B4(void);
void fn_80304EE4(void*, int);

/* Scaffolding: sets the offsets of the file's string pool at lbl_803631B0. */
#pragma pool_strings on
#pragma readonly_strings on
void StringPool(const char** p) {
    p[0] = "video.cpp";
    p[1] = "DisplayInit: invalide TV format";
}
}

static inline void setMode(GXRenderModeObj* m) {
    lbl_804CBF3C = 0;
    fn_80234F1C(m);
}
#define BUS_CLOCK (*(u32*)0x800000F8)

extern "C" void fn_8008BDDC(void) {
    BOOL alarm;
    fn_8032FAD0();
    switch (VIGetTvFormat()) {
    case 0:
        lbl_804CB5F8 = &sNtscInt;
        lbl_804CB5FC = &sProg;
        lbl_804CB5F4 |= 0x10000;
        break;
    case 1:
        lbl_804CB5F8 = &sPalInt;
        lbl_804CB5FC = &sProg;
        lbl_804CB5F4 |= 0x20000;
        break;
    case 5:
        lbl_804CB5F8 = &sEu60Int;
        lbl_804CB5FC = &sProg;
        lbl_804CB5F4 |= 0x40000;
        break;
    case 2:
        lbl_804CB5F8 = &sMpalInt;
        lbl_804CB5FC = &sProg;
        lbl_804CB5F4 |= 0x80000;
        break;
    default:
        OSPanic("video.cpp", 0xf6, "DisplayInit: invalide TV format");
        break;
    }
    alarm = 0;
    fn_80331608();
    if (lbl_804CB5F4 & 0x10000) {
        if (!(OSGetResetCode() >> 31) || (OSGetResetCode() & 2)) {
            if (fn_80331388() && fn_80325984() == 1) {
                alarm = fn_80331328() != 2;
                setMode(lbl_804CB5FC);
                lbl_804CB5F4 |= 0x40;
            } else {
                setMode(lbl_804CB5F8);
                lbl_804CB5F4 &= ~0x40;
            }
            lbl_804CB5F4 |= 0x30;
        } else {
            if (OSGetResetCode() & 1) {
                setMode(lbl_804CB5FC);
                lbl_804CB5F4 |= 0x40;
            } else {
                setMode(lbl_804CB5F8);
                lbl_804CB5F4 &= ~0x40;
            }
            lbl_804CB5F4 |= 0x30;
        }
    } else if (lbl_804CB5F4 & 0x80000) {
        if (!(OSGetResetCode() >> 31) || (OSGetResetCode() & 2)) {
            if (fn_80331388() && fn_80325984() == 1) {
                setMode(lbl_804CB5FC);
                lbl_804CB5F4 |= 0x40;
            } else {
                setMode(lbl_804CB5F8);
                lbl_804CB5F4 &= ~0x40;
            }
            lbl_804CB5F4 |= 0x30;
        } else {
            if (OSGetResetCode() & 1) {
                setMode(lbl_804CB5FC);
                lbl_804CB5F4 |= 0x40;
            } else {
                setMode(lbl_804CB5F8);
                lbl_804CB5F4 &= ~0x40;
            }
            lbl_804CB5F4 |= 0x30;
        }
    } else if (lbl_804CB5F4 & 0x60000) {
        if (!(OSGetResetCode() >> 31) || (OSGetResetCode() & 0x20)) {
            if (fn_80331388() && fn_80325984() == 1) {
                setMode(lbl_804CB5FC);
                lbl_804CB5F4 |= 0x40;
                lbl_804CB5F4 &= ~0x100;
            } else if (fn_803258B8() == 1) {
                lbl_804CBF3C = 0;
                fn_80234F1C(lbl_804CB5FC = &sEu60Int);
                lbl_804CB5F4 &= ~0x40;
                lbl_804CB5F4 |= 0x100;
            } else {
                setMode(lbl_804CB5F8);
                lbl_804CB5F4 &= ~0x40;
                lbl_804CB5F4 &= ~0x100;
            }
            lbl_804CB5F4 |= 0x30;
        } else {
            if (OSGetResetCode() & 1) {
                setMode(lbl_804CB5FC);
                lbl_804CB5F4 |= 0x40;
                lbl_804CB5F4 &= ~0x100;
            } else if (!(OSGetResetCode() & 0x10)) {
                lbl_804CBF3C = 0;
                fn_80234F1C(lbl_804CB5FC = &sEu60Int);
                lbl_804CB5F4 &= ~0x40;
                lbl_804CB5F4 |= 0x100;
            } else {
                setMode(lbl_804CB5F8);
                lbl_804CB5F4 &= ~0x40;
                lbl_804CB5F4 &= ~0x100;
            }
            lbl_804CB5F4 |= 0x30;
        }
    }
    if (fn_803315F8()) {
        lbl_804CB5F4;
    }
    if (alarm && (lbl_804CB5F4 & 0x40)) {
        lbl_804CB5F4 |= 0x1000000;
        fn_80317974(&lbl_803E4EC8);
        {
            f32 t = BUS_CLOCK / 4 / 1000;
            t *= 1666.6666f;
            fn_80317BD4(&lbl_803E4EC8, t, fn_8008BDCC);
        }
    }
    {
        u32 c = 0;
        fn_80304C74(&c, 0xFFFFFF);
    }
    fn_80304EE4(fn_802356B4(), 1);
}
