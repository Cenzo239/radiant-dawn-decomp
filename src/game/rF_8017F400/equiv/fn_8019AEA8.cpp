/* functionally equal (check_regs: regs, 168 of 4243 words differ, registers only). File menu main state machine.
   Round 18: lbl_804CB944 (current slot) is a function-local static here: the original treats it as not aliasing
   G->st / G->x16 (load hoisted over the state store, lbz shared across the store), which only a local static reproduces.
   Strict check needs --symbol-map fn_8019AEA8.symbols.json. In a port make it one shared variable again. */
/* symcheck: (a) clean. The 8 flagged blocks were the local static lbl_804CB944$20 against the original's lbl_804CB944 (name map in fn_8019AEA8.symbols.json, now read by symcheck). All 8 uses of lbl_804CB944 in the original are inside this function, so a function-local static is probably what the original has. */
#include "game/rF_8017F400/types.h"
#pragma pool_strings on
extern "C" {
void StringPool(const char** p) {
    p[0] = "FM_SELECT"; p[1] = "FM_DECIDE"; p[2] = "FM_CANCEL"; p[3] = "FM_CHECK"; p[4] = "FM_REMAIN"; p[5] = "FM_SUSPEND"; p[6] = "FM_WIIMENU";
    p[7] = "%s%s  %s%s  %s%s"; p[8] = "%s%s  %s%s"; p[9] = "SFX_SYS_MISS1"; p[10] = "SFX_SYS_SELECT1"; p[11] = "SFX_SYS_CANCEL1"; p[12] = "SFX_SYS_CURSOR_WINDOW_MOVE1";
    p[13] = "FM_Q_INHERIT"; p[14] = "FM_Q_INHERIT2"; p[15] = "FM_EXP_INHERIT"; p[16] = "FM_ERR_COMPLETE_ZERO"; p[17] = "FM_Q_SURE_INHERIT"; p[18] = "FM_Q_SURE_INHERIT_SUSPEND"; p[19] = "FE8Data.bin"; p[20] = "FM_ERR_INHERIT"; p[21] = "FM_ERR_WRONG"; p[22] = "FM_ERR_N8192"; p[23] = "FM_ERR_BROKEN"; p[24] = "FM_ERR_IO"; p[25] = "FM_ERR_NOCARD"; p[26] = "FM_ERR_NOFILE_FE8";
    p[27] = "FM_ERR_CORRUPT"; p[28] = "FM_ERR_ECC_CRIT"; p[29] = "FM_Q_FEFILE_CREATE"; p[30] = "FM_CREATING"; p[31] = "FM_CREATE_END"; p[32] = "FM_ERR_CREATE"; p[33] = "FM_ERR_OVER_DATASIZE"; p[34] = "FM_ERR_OVER_FILENUM"; p[35] = "FM_Q_START_NO_SAVE"; p[36] = "FM_EXP_START"; p[37] = "FM_INTR_DELETING"; p[38] = "SFX_SYS_SAVE_ERROR1"; p[39] = "FM_ERR_SELETE_INTR"; p[40] = "FM_SAVING"; p[41] = "SFX_SYS_SAVE_OK1"; p[42] = "FM_ERR_SAVE"; p[43] = "FM_ERR_START"; p[44] = "FM_EXP_LOAD"; p[45] = "FM_Q_SURE_INTR_DELETE"; p[46] = "FM_ERR_DELETE_INTR"; p[47] = "FM_ERR_LOAD"; p[48] = "FM_EXP_INTR"; p[49] = "FM_INTRING"; p[50] = "FM_ERR_CONTINUE"; p[51] = "FM_EXP_SAVE"; p[52] = "FM_SAVE_COMP"; p[53] = "FM_Q_SURE_SAVE"; p[54] = "FM_Q_END_SAVE_COMP"; p[55] = "FM_EXP_COPY_SRC"; p[56] = "FM_EXP_COPY_DST"; p[57] = "FM_ERR_COPY"; p[58] = "FM_EXP_DELETE"; p[59] = "FM_Q_SURE_DELETE"; p[60] = "FM_DELETING"; p[61] = "SFX_SYS_SAVE_DELETE1"; p[62] = "FM_ERR_DELETE";
}
typedef struct FMG { u32 flags; int st; int x8; u8 padc[0x14-0xC]; u8 x14; s8 x15; s8 x16; s8 x17; s8 x18; u8 pad19[0x80-0x19]; const char* msg; int x84; int x88; } FMG;
class Pad { public: virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34(); virtual void v38(); virtual u32 v3C(); virtual void v40(); virtual void v44(); virtual u32 v48(); };
extern Pad* lbl_804CB5B8;
extern FMG* lbl_804CB934;
extern void* lbl_804CB930;
extern int lbl_804CB928;
extern char lbl_804CB700[8];
extern char lbl_804CB778[8];
extern u8 lbl_803CAB38[];
#define G lbl_804CB934
#define P lbl_804CB930
#define UP 0x800008
#define DN 0x400004
extern void fn_80197928(void);
extern void fn_8024BC14(void*);
extern int fn_800C7FA0(void);
extern void fn_800C835C(int, int);
extern int fn_8019FB08(void);
extern int fn_801949E4(void);
extern void fn_8024B654(void*);
extern void* fn_801947E0(void);
extern void fn_80197BAC(void*, int);
extern void fn_80197BB4(void*, int);
extern void fn_80194834(int);
extern void fn_80083B78(void*);
extern void fn_8028392C(const char*, int, const char*, int, void*, int);
extern void fn_8014CA80(void*, u32);
extern void fn_8024B5D4(void*);
extern void fn_8024B450(int, void*);
extern int fn_8019FD14(void);
extern void fn_8024B554(void*);
extern int fn_8024B448(void);
extern void fn_800D0AE4(int, int);
extern void fn_80253EE4(const char*, f32);
extern void fn_80252984(f32);
extern void fn_801945E8(int, void*);
extern void fn_8008A068(int);
extern void fn_800CD4A4(int);
extern void fn_801958C0(void*);
extern s16 fn_8019F0F4(void);
extern void fn_800609D8(void*, int, int, u8);
extern void* fn_8024BC94(void);
extern void fn_80244D90(void*);
extern void* fn_801947EC(int);
extern void* fn_80194800(int);
extern void* fn_80194820(int);
extern void fn_8019F0FC(void*);
extern void fn_80196DC8(void*);
extern int fn_80194CB0(void);
extern int fn_80194C08(void);
extern void fn_8019F108(void*, int, int);
extern void fn_8019F1E8(void*, s16, s16, int, int);
extern void fn_8019F234(void*, int);
extern void fn_8019F260(void*, int);
extern void fn_8019F288(void*, void*, int);
extern s16 fn_8019F2F0(void*);
extern void fn_8019F2F8(void*, int);
extern s16 fn_8019F2E0(void*);
extern s16 fn_8019F2E8(void*);
extern void fn_8019F334(void*, int);
extern void fn_80196DD4(void*, int, int, int);
extern int fn_8019FC48(int);
extern int fn_8019FB10(int, int);
extern void fn_80196E14(void*, int, int);
extern void fn_801977E0(void*, s16, s16, int, int);
extern void fn_8019782C(void*, int);
extern int fn_8019F35C(void*);
extern void fn_80197858(void*, int);
extern void fn_80197880(void*, void*, int);
extern int fn_80194B58(void);
extern void fn_8024BB08(int, void*);
extern void fn_80283A58(void);
extern void fn_801972FC(void*);
extern void fn_80197918(void*);
extern s16 fn_8019F368(void);
extern void fn_80106A28(void*);
extern void fn_8024B6D4(int, int, int, void*);
extern void fn_8019F370(void*, const char*);
extern void fn_8024B764(int, void*);
extern void fn_800CD548(int);
extern int fn_8019FC74(int);
extern int fn_80194AC0(int);
extern void* fn_80194A28(int);
extern int fn_8019FBAC(void*, int);
extern int fn_8019FC40(void*);
extern void* fn_8019FC80(void*);
extern u8 fn_8019FBA4(void*);
extern int fn_8019FDA0(u8);
extern int fn_8019F39C(void*);
extern int fn_80194B60(void);
extern void fn_8024BA00(int, void*);
extern void* fn_8024BCA0(void);
extern int fn_80245DFC(void*);
extern int fn_80060728(void*);
extern int fn_8019FDA8(int);
extern void fn_80245D00(void*, int, u8, u8);
extern void fn_8024B7E8(int, void*);
extern void fn_8019FC88(void*, int);
extern u8 fn_8019FDB0(void*);
extern void fn_8019FDB8(void*, u8);
extern void fn_80245574(void*);
extern void fn_8019F3A8(void*, int);
extern void fn_8024B8F0(int, int, void*);
extern void fn_8024B86C(int, void*);
extern s16 fn_801978D8(void*);
extern s16 fn_801978E0(void*);
extern void fn_8019F50C(void*, int);

#define SND(s) fn_80253EE4(s, 0.0f)
#define EXIT() fn_80083B78(P)
/* simple cursor over windows */
#define NAVW(F, LAST, old) \
    { old = G->F; \
    if ((trig & UP) || (held & UP)) { G->F--; if (G->F < 0) { if (held & UP) G->F = LAST; else G->F = 0; } } \
    if ((trig & DN) || (held & DN)) { G->F++; if (G->F > LAST) { if (held & DN) G->F = 0; else G->F = LAST; } } }
#define NAVL(F, PRED, old) \
    { old = G->F; \
    if ((trig & UP) || (held & UP)) { do { G->F--; if (G->F < 0) { if (held & UP) G->F = 5; else { G->F = old; break; } } } while (PRED(fn_80194800(G->F))); } \
    if (trig & DN) { do { G->F++; if (G->F > 5) { if (held & DN) G->F = 0; else { G->F = old; break; } } } while (PRED(fn_80194800(G->F))); } }
#define NAVL39(F, old) \
    { old = G->F; \
    if ((trig & UP) || (held & UP)) { do { G->F--; if (G->F < 0) { if (held & UP) G->F = 5; else { G->F = old; break; } } } while (fn_8019F39C(fn_80194800(G->F)) == 0); } \
    if (trig & DN) { do { G->F++; if (G->F > 5) { if (held & DN) G->F = 0; else { G->F = old; break; } } } while (fn_8019F39C(fn_80194800(G->F)) == 0); } }
#define MOVEE(F, e, old) \
    if (old != G->F) { \
        e = fn_80194800(G->F); fn_80197880(fn_80194820(0), e, 4); \
        fn_80197858(fn_80194800(old), 0); \
        fn_80197858(fn_80194800(G->F), 1); \
        SND("SFX_SYS_CURSOR_WINDOW_MOVE1"); }
#define SELE(F, e) \
    fn_80197858(fn_80194800(G->F), 1); \
    e = fn_80194800(G->F); fn_80197880(fn_80194820(0), e, 0);
#define NZ(x) (fn_8019F35C(x) != 0)
#define EZ(x) (fn_8019F35C(x) == 0)
#define SLIDEIN(i, k, y) \
    for (i = 0, k = 0x3e; i < 6; i++, k += 0x38) { \
        y = k; \
        if (i % 2 == 0) fn_801977E0(fn_80194800(i), -0x3b0, y, 0, -1); else fn_801977E0(fn_80194800(i), 0x420, y, 0, -1); \
        fn_801977E0(fn_80194800(i), 0x38, y, 0x19, 4); \
        fn_8019782C(fn_80194800(i), 0x24); \
    }

#define ErrSt(g,s,i) do { G->st = (s); fn_801972FC(fn_80194800(lbl_804CB944)); } while (0)
void fn_8019AEA8(void) {
static int lbl_804CB944;
    u32 held = lbl_804CB5B8->v48();
    u32 trig = lbl_804CB5B8->v3C();
    int A29;
int A27;
s16 S26;
int A28;
    switch (G->st) {
    case 0: {

        fn_80197928();
        fn_8024BC14(P);
        G->st = 0xa;
        G->msg = 0;
        break;
    }
    case 0xa: {

        if (fn_800C7FA0()) fn_800C835C(2, 0xfa);
        switch (fn_8019FB08()) {
        case 0:
            if (!fn_801949E4()) { fn_8024B654(P); break; }
            switch (G->x14) {
            case 0: G->st = 0x7d0; break;
            case 1: case 2: G->st = 0x1b58; break;
            case 3: G->st = 0x1f40; break;
            case 4: G->st = 0x1388; break;
            case 5: G->st = 0xbb8; fn_80197BAC(fn_801947E0(), 1); break;
            }
            fn_80194834(1);
            break;
        case -0xc:
            switch (G->x14) {
            case 0: fn_800C835C(2, 0xfa); G->st = 0x3e8; break;
            case 1: case 4: case 5: EXIT(); break;
            }
            break;
        case -3: fn_8024BC14(P); break;
        case -4: G->st = 0x64; break;
        case -5: case -0xf: case -0x100: G->st = 0xc8; break;
        }
        break;
    }
    case 0x64: {

        G->st = 0x6e;
        fn_8028392C("FM_ERR_CORRUPT", 0, 0, 1, P, 1);
        fn_80194834(0);
        fn_8014CA80(lbl_804CB700, 0x200100);
        break;
    }
    case 0x6e: {
 break;
    }
    case 0xc8: {
 G->st = 0xd2; fn_8024B5D4(P); break;
    }
    case 0xd2: {

        G->st = 0xdc;
        fn_80194834(0);
        fn_8028392C("FM_ERR_ECC_CRIT", 0, 0, 1, P, 0);
        break;
    }
    case 0xdc: {
 G->st = 0; break;
    }
    case 0x3e8: {
 fn_80194834(2); fn_8024B450(0, P); G->st = 0x3f2; break;
    }
    case 0x3f2: {int r_3f2;

        { r_3f2 = fn_8019FB08();
        if (r_3f2 & 5) { G->st = 0x4b0; break; }
        if (r_3f2 & 0xa) { G->st = 0x4e2; break; }
        G->st = 0x44c; }
        break;
    }
    case 0x44c: {
 fn_8028392C("FM_Q_FEFILE_CREATE", 0, "SFX_SYS_SELECT1", 0, P, 2); G->st = 0x456; break;
    }
    case 0x456: {

        if (fn_8019FD14() == 1) {
            fn_80194834(0);
            fn_8028392C("FM_CREATING", 0, 0, 0, P, 1);
            fn_8024B554(P);
            G->st = 0x460;
        } else G->st = 0x578;
        break;
    }
    case 0x460: {

        if (fn_8019FB08() == 0) { fn_8028392C("FM_CREATE_END", 0, 0, 0, P, 0); G->st = 0; }
        else { fn_8028392C("FM_ERR_CREATE", 0, 0, 1, P, 1); G->st = 0x514; }
        break;
    }
    case 0x4b0: {

        fn_800D0AE4(0, fn_8024B448());
        fn_8028392C("FM_ERR_OVER_DATASIZE", 0, 0, 1, P, 1);
        G->st = 0x514;
        break;
    }
    case 0x4e2: {
 fn_8028392C("FM_ERR_OVER_FILENUM", 0, 0, 1, P, 1); G->st = 0x514; break;
    }
    case 0x514: {
 G->st = 0x51e; fn_80194834(5); break;
    }
    case 0x51e: {

        if (held & 0x400) { G->st = 0x578; SND("SFX_SYS_SELECT1"); break; }
        if (held & 0x800) { G->st = 0x528; fn_800C835C(3, 0xfa); fn_80252984(250.0f); fn_801945E8(0xf, P); }
        break;
    }
    case 0x528: {
 fn_8008A068(0xfe); break;
    }
    case 0x578: {

        G->st = 0x582;
        fn_80194834(2);
        fn_8028392C("FM_Q_START_NO_SAVE", 1, "SFX_SYS_SELECT1", 0, P, 2);
        break;
    }
    case 0x582: {

        if (fn_8019FD14() == 1) { G->st = 0x5dc; break; }
        fn_800C835C(3, 0xfa); fn_800CD4A4(0x1e); EXIT();
        break;
    }
    case 0x5dc: {
 fn_801958C0(P); G->st = 0x5e6; break;
    }
    case 0x5e6: {

        if (fn_8019F0F4() == 3) G->st = 0x5fa; else G->st = 0x5f0;
        break;
    }
    case 0x5f0: {int d_5f0;

        { d_5f0 = 0;
        switch (fn_8019F0F4()) { case 0: d_5f0 = 0; break; case 1: d_5f0 = 1; break; case 2: d_5f0 = 2; break; }
        fn_801949E4();
        fn_800609D8(lbl_803CAB38, 1, d_5f0, 1);
        fn_80244D90(fn_8024BC94());
        fn_800C835C(3, 0xfa); fn_800CD4A4(0x1d); EXIT(); }
        break;
    }
    case 0x5fa: {
 fn_800C835C(3, 0xfa); fn_800CD4A4(0x1e); EXIT(); break;
    }
    case 0x7d0: {int c_7d0;

        { A29; c_7d0;
        fn_801949E4();
        G->msg = 0;
        for (A29 = 0; A29 < 6; A29++) fn_8019F0FC(fn_801947EC(A29));
        for (A29 = 0; A29 < 6; A29++) fn_80196DC8(fn_80194800(A29));
        A29 = 0;
        c_7d0 = fn_80194CB0();
        if (fn_80194C08() > 0) { fn_8019F108(fn_801947EC(0), 0, 2); A29 = 1; }
        if (c_7d0 >= 1) { fn_8019F108(fn_801947EC(A29), A29, 1); A29++; }
        if (c_7d0 >= 1 && c_7d0 < 6) { fn_8019F108(fn_801947EC(A29), A29, 3); A29++; }
        if (c_7d0 >= 1) { fn_8019F108(fn_801947EC(A29), A29, 4); A29++; }
        if (c_7d0 < 6) { fn_8019F108(fn_801947EC(A29), A29, 0); A29++; }
        fn_8019F108(fn_801947EC(A29), A29, 5);
        G->x18 = A29 + 1;
        fn_80197BAC(fn_801947E0(), 0);
        fn_80197BB4(fn_801947E0(), 0xf);
        for (A29 = 0, A27 = 0; A29 < G->x18; A27 += 0x38, A29++) {
            S26 = 0xe6 - G->x18 * 0x1c + A27;
            if (A29 % 2 == 0) fn_8019F1E8(fn_801947EC(A29), -0x15c, S26, 0, -1); else fn_8019F1E8(fn_801947EC(A29), 0x28c, S26, 0, -1);
            fn_8019F1E8(fn_801947EC(A29), 0x98, S26, 0xf, 4);
            fn_8019F234(fn_801947EC(A29), 0x18);
        }
        if (G->x15 < 0 || G->x15 >= G->x18) G->x15 = 0;
        G->st = 0x7da;
        G->x8 = 0;
        fn_801945E8(0xf, P); }
        break;
    }
    case 0x7da: {void* w_7da;

        fn_8019F260(fn_801947EC(G->x15), 1);
        { w_7da = fn_801947EC(G->x15); fn_8019F288(fn_80194820(0), w_7da, 0); }
        fn_80194834(1);
        G->st = 0x7e4;
        break;
    }
    case 0x7e4: {u32 a_7e4; s16 x_7e4; s16 y_7e4; int old_7e4; void* w_7e4;

        { a_7e4 = held & 0x400;
        if (a_7e4 || (held & 0x800)) {
            if (fn_8019F2F0(fn_801947EC(G->x15)) == 5) fn_8019F2F8(fn_801947E0(), 0xf);
            for (A29 = 0; A29 < G->x18; A29++) {
                x_7e4 = fn_8019F2E0(fn_801947EC(A29));
                y_7e4 = fn_8019F2E8(fn_801947EC(A29));
                if (A29 % 2 == 0) fn_8019F1E8(fn_801947EC(A29), x_7e4 - 0x1f4, y_7e4, 0xf, 4); else fn_8019F1E8(fn_801947EC(A29), x_7e4 + 0x1f4, y_7e4, 0xf, 4);
                fn_8019F334(fn_801947EC(A29), 4);
            }
            fn_80196DD4(fn_80194820(0), -0x3e8, -0x3e8, 0);
        }
        if (a_7e4) { G->st = 0x7ee; SND("SFX_SYS_SELECT1"); fn_801945E8(0xf, P); break; }
        }
        if (held & 0x800) { G->st = 0x7f8; SND("SFX_SYS_CANCEL1"); fn_801945E8(0xf, P); fn_800C835C(3, 0xfa); break; }
        NAVW(x15, G->x18 - 1, old_7e4)
        if (old_7e4 != G->x15) {
            { w_7e4 = fn_801947EC(G->x15); fn_8019F288(fn_80194820(0), w_7e4, 4); }
            fn_8019F260(fn_801947EC(old_7e4), 0);
            fn_8019F260(fn_801947EC(G->x15), 1);
            SND("SFX_SYS_CURSOR_WINDOW_MOVE1");
        }
        break;
    }
    case 0x7ee: {

        switch (fn_8019F2F0(fn_801947EC(G->x15))) {
        case 0: G->st = 0xfa0; break;
        case 1: G->st = 0x1388; break;
        case 2: G->st = 0x1770; break;
        case 3: G->st = 0x2328; break;
        case 4: G->st = 0x2710; break;
        case 5: G->st = 0xbb8; break;
        }
        break;
    }
    case 0x7f8: {
 fn_800CD4A4(0x1e); EXIT(); break;
    }
    case 0xbb8: {int n_bb8; int c_bb8; int j_bb8; int k_bb8;

        { n_bb8;
        c_bb8 = fn_801949E4();
        G->msg = 0;
        for (j_bb8 = 0; j_bb8 < 6; j_bb8++) fn_8019F0FC(fn_801947EC(j_bb8));
        for (j_bb8 = 0; j_bb8 < 6; j_bb8++) fn_80196DC8(fn_80194800(j_bb8));
        n_bb8 = 0;
        if (fn_8019FC48(c_bb8)) { fn_8019F108(fn_801947EC(0), 0, 0xb); n_bb8 = 1; }
        if (fn_8019FC48(c_bb8)) { fn_8019F108(fn_801947EC(n_bb8), n_bb8, 7); n_bb8++; }
        fn_8019F108(fn_801947EC(n_bb8), n_bb8, 6); n_bb8++;
        if (fn_8019FC48(c_bb8)) { fn_8019F108(fn_801947EC(n_bb8), n_bb8, 8); n_bb8++; }
        if (fn_8019FC48(c_bb8)) { fn_8019F108(fn_801947EC(n_bb8), n_bb8, 9); n_bb8++; }
        if (fn_8019FB10(c_bb8, 4)) { fn_8019F108(fn_801947EC(n_bb8), n_bb8, 0xa); n_bb8++; }
        G->x18 = n_bb8;
        fn_80197BAC(fn_801947E0(), 1);
        fn_80197BB4(fn_801947E0(), 0xf);
        for (A29 = 0, k_bb8 = 0; A29 < G->x18; k_bb8 += 0x38, A29++) {
            S26 = 0xe6 - G->x18 * 0x1c + k_bb8;
            if (A29 % 2 == 0) fn_8019F1E8(fn_801947EC(A29), -0x15c, S26, 0, -1); else fn_8019F1E8(fn_801947EC(A29), 0x28c, S26, 0, -1);
            fn_8019F1E8(fn_801947EC(A29), 0x98, S26, 0xf, 4);
            fn_8019F234(fn_801947EC(A29), 0x18);
        }
        if (lbl_804CB928 < 0) lbl_804CB928 = 0;
        if (lbl_804CB928 >= G->x18) lbl_804CB928 = G->x18 - 1;
        G->x16 = lbl_804CB928;
        G->st = 0xbc2;
        G->x8 = 0;
        fn_801945E8(0xf, P); }
        break;
    }
    case 0xbc2: {void* w_bc2;

        fn_8019F260(fn_801947EC(G->x16), 1);
        { w_bc2 = fn_801947EC(G->x16); fn_8019F288(fn_80194820(0), w_bc2, 0); }
        fn_80194834(1);
        G->st = 0xbcc;
        break;
    }
    case 0xbcc: {s16 x_bcc; s16 y_bcc; int old_bcc; void* w_bcc;

        if (held & 0x400) {
            switch (fn_8019F2F0(fn_801947EC(G->x16))) {
            case 0xb: fn_800CD4A4(0x29); break;
            case 6: fn_800CD4A4(0x2a); break;
            case 7: fn_800CD4A4(0x25); break;
            case 8: fn_800CD4A4(0x26); break;
            case 9: fn_800CD4A4(0x27); break;
            case 0xa: fn_800CD4A4(0x28); break;
            default: SND("SFX_SYS_MISS1"); return;
            }
            fn_800C835C(3, 0xfa);
            EXIT();
            SND("SFX_SYS_SELECT1");
            fn_801945E8(0xf, P);
            break;
        }
        if (held & 0x800) {
            fn_8019F2F8(fn_801947E0(), 0xf);
            for (A29 = 0; A29 < G->x18; A29++) {
                x_bcc = fn_8019F2E0(fn_801947EC(A29));
                y_bcc = fn_8019F2E8(fn_801947EC(A29));
                if (A29 % 2 == 0) fn_8019F1E8(fn_801947EC(A29), x_bcc - 0x1f4, y_bcc, 0xf, 4); else fn_8019F1E8(fn_801947EC(A29), x_bcc + 0x1f4, y_bcc, 0xf, 4);
                fn_8019F334(fn_801947EC(A29), 4);
            }
            fn_80196DD4(fn_80194820(0), -0x3e8, -0x3e8, 0);
            G->st = 0xbd6;
            SND("SFX_SYS_CANCEL1");
            fn_801945E8(0xf, P);
            break;
        }
        NAVW(x16, G->x18 - 1, old_bcc)
        if (old_bcc != G->x16) {
            { w_bcc = fn_801947EC(G->x16); fn_8019F288(fn_80194820(0), w_bcc, 4); }
            fn_8019F260(fn_801947EC(old_bcc), 0);
            fn_8019F260(fn_801947EC(G->x16), 1);
            SND("SFX_SYS_CURSOR_WINDOW_MOVE1");
        }
        lbl_804CB928 = G->x16;
        break;
    }
    case 0xbd6: {
 G->st = 0x7d0; break;
    }
    case 0xfa0: {int k_fa0;

        for (A29 = 0; A29 < 6; A29++) fn_80196E14(fn_80194800(A29), A29, 0);
        G->x16 = -1;
        for (A29 = 0, k_fa0 = 0x3e; A29 < 6; A29++, k_fa0 += 0x38) {
            S26 = k_fa0;
            if (A29 % 2 == 0) fn_801977E0(fn_80194800(A29), -0x3b0, S26, 0, -1); else fn_801977E0(fn_80194800(A29), 0x420, S26, 0, -1);
            fn_801977E0(fn_80194800(A29), 0x38, S26, 0x19, 4);
            fn_8019782C(fn_80194800(A29), 0x24);
            if (fn_8019F35C(fn_80194800(A29)) == 0 && G->x16 == -1) G->x16 = A29;
        }
        G->st = 0xfaa;
        G->msg = "FM_EXP_START";
        fn_801945E8(0x19, P);
        break;
    }
    case 0xfaa: {void* e_faa;

        G->flags &= ~8;
        SELE(x16, e_faa)
        fn_80194834(1);
        G->st = 0xfb4;
        break;
    }
    case 0xfb4: {int old_fb4; void* e_fb4;

        if (held & 0x400) { G->st = 0xfd2; SND("SFX_SYS_SELECT1"); }
        if (held & 0x800) { G->st = 0x2ee0; SND("SFX_SYS_CANCEL1"); break; }
        NAVL(x16, NZ, old_fb4)
        MOVEE(x16, e_fb4, old_fb4)
        break;
    }
    case 0xfbe: {

        lbl_804CB944 = fn_80194B58();
        if (fn_8019FD14() == 1) {
            fn_8028392C("FM_INTR_DELETING", 0, 0, 0, P, 1);
            fn_8024BB08(0, P);
            fn_8024BB08(G->x16, P);
            G->st = 0xfc8;
        } else G->st = 0xfaa;
        break;
    }
    case 0xfc8: {

        if (fn_8019FB08() == 0) { G->st = 0xfd2; fn_80283A58(); fn_801945E8(5, P); }
        else {
            SND("SFX_SYS_SAVE_ERROR1");
            fn_8028392C("FM_ERR_SELETE_INTR", 0, 0, 1, P, 0);
            G->st = 0xfaa;
        }
        fn_801972FC(fn_80194800(lbl_804CB944));
        break;
    }
    case 0xfd2: {
 fn_80197918(P); G->st = 0xfdc; break;
    }
    case 0xfdc: {

        switch (fn_8019F368()) {
        case 0: G->st = 0xfe6; break;
        case 1: G->st = 0xff0; break;
        case 2: G->st = 0xfaa; break;
        }
        break;
    }
    case 0xfe6: {int i_fe6; int k_fe6; void* e_fe6;

        G->st = 0xff0;
        for (i_fe6 = 0, k_fe6 = 0x3e; i_fe6 < 6; i_fe6++, k_fe6 += 0x38) {
            fn_80196E14(fn_80194800(i_fe6), i_fe6, 0);
            fn_801977E0(fn_80194800(i_fe6), 0x38, k_fe6, 0, -1);
        }
        SELE(x16, e_fe6)
        G->flags &= ~2;
        G->msg = "FM_EXP_START";
        fn_801945E8(0x1e, P);
        break;
    }
    case 0xff0: {
 fn_80106A28(lbl_804CB778); fn_801958C0(P); G->st = 0xffa; break;
    }
    case 0xffa: {

        if (fn_8019F0F4() == 3) G->st = 0xfaa; else G->st = 0x1004;
        break;
    }
    case 0x1004: {

        { A29 = 0;
        switch (fn_8019F0F4()) { case 0: A29 = 0; break; case 1: A29 = 1; break; case 2: A29 = 2; break; }
        fn_801949E4();
        fn_800609D8(lbl_803CAB38, 1, A29, 1);
        if (G->flags & 8) fn_8024B6D4(G->x16, A29, G->x88, P); else fn_8024B6D4(G->x16, A29, 0, P);
        fn_8028392C("FM_SAVING", 0, 0, 0, P, 1);
        G->st = 0x100e; }
        break;
    }
    case 0x100e: {

        if (fn_8019FB08() == 0) {
            fn_80283A58();
            fn_8019F370(fn_80194800(G->x16), "SFX_SYS_SAVE_OK1");
            fn_801945E8(0x64, P);
            G->st = 0x1018;
        } else {
            SND("SFX_SYS_SAVE_ERROR1");
            fn_8028392C("FM_ERR_SAVE", 0, 0, 1, P, 0);
            G->st = 0xfaa;
        }
        break;
    }
    case 0x1018: {
 fn_8024B764(G->x16, P); G->st = 0x1022; break;
    }
    case 0x1022: {

        if (fn_8019FB08() == 0) {
            fn_800C835C(3, 0xfa); fn_800CD4A4(0x1f); fn_800CD548(G->x16); EXIT();
        } else {
            SND("SFX_SYS_SAVE_ERROR1");
            fn_8028392C("FM_ERR_START", 0, 0, 1, P, 0);
            G->st = 0xfaa;
        }
        break;
    }
    case 0x1388: {int j_1388; int i_1388;

        { A29 = fn_801949E4();
        for (j_1388 = 0; j_1388 < 6; j_1388++) fn_80196E14(fn_80194800(j_1388), j_1388, 0);
        G->x16 = fn_8019FC74(A29);
        if (G->x16 >= 0 && G->x16 < 6) { if (fn_8019F35C(fn_80194800(G->x16)) == 0) G->x16 = -1; }
        else G->x16 = -1;
        for (i_1388 = 0, A29 = 0x3e; i_1388 < 6; i_1388++, A29 += 0x38) {
            S26 = A29;
            if (i_1388 % 2 == 0) fn_801977E0(fn_80194800(i_1388), -0x3b0, S26, 0, -1); else fn_801977E0(fn_80194800(i_1388), 0x420, S26, 0, -1);
            fn_801977E0(fn_80194800(i_1388), 0x38, S26, 0x19, 4);
            fn_8019782C(fn_80194800(i_1388), 0x24);
            if (fn_8019F35C(fn_80194800(i_1388)) && G->x16 == -1) G->x16 = i_1388;
        } }
        G->st = 0x1392;
        G->msg = "FM_EXP_LOAD";
        fn_801945E8(0x19, P);
        break;
    }
    case 0x1392: {void* e_1392;

        SELE(x16, e_1392)
        fn_80194834(1);
        G->st = 0x139c;
        break;
    }
    case 0x139c: {int old_139c; void* e_139c;

        if (held & 0x400) {
            if (fn_80194AC0(G->x16) && *(s16*)((u8*)fn_80194800(G->x16) + 0x34) == 2) {
                fn_80194834(2);
                fn_8028392C("FM_Q_SURE_INTR_DELETE", 1, "SFX_SYS_SELECT1", 0, P, 2);
                G->st = 0x13a6;
                SND("SFX_SYS_SELECT1");
                break;
            }
            G->st = 0x13ba;
            SND("SFX_SYS_SELECT1");
            break;
        }
        if (held & 0x800) { G->st = 0x2ee0; SND("SFX_SYS_CANCEL1"); break; }
        NAVL(x16, EZ, old_139c)
        MOVEE(x16, e_139c, old_139c)
        break;
    }
    case 0x13a6: {

        lbl_804CB944 = G->x16;
        if (fn_8019FD14() == 1) {
            fn_8028392C("FM_INTR_DELETING", 0, 0, 0, P, 1);
            fn_8024BB08(G->x16, P);
            G->st = 0x13b0;
        } else G->st = 0x1392;
        break;
    }
    case 0x13b0: {

        if (fn_8019FB08() == 0) { fn_80283A58(); G->st = 0x13ba; break; }
        fn_8028392C("FM_ERR_DELETE_INTR", 0, 0, 1, P, 0);
        ErrSt(G, 0x1392, lbl_804CB944);
        break;
    }
    case 0x13ba: {

        if (fn_8019FBAC(fn_80194A28(G->x16), 2)) { fn_80197918(P); G->st = 0x13bf; }
        else G->st = 0x13d8;
        break;
    }
    case 0x13bf: {

        switch (fn_8019F368()) {
        case 0: G->st = 0x13c4; break;
        case 1: G->st = 0x13c9; break;
        case 2: G->st = 0x1392; break;
        }
        break;
    }
    case 0x13c4: {int i_13c4; int k_13c4; void* e_13c4;

        G->st = 0x13c9;
        for (i_13c4 = 0, k_13c4 = 0x3e; i_13c4 < 6; i_13c4++, k_13c4 += 0x38) {
            fn_80196E14(fn_80194800(i_13c4), i_13c4, 0);
            fn_801977E0(fn_80194800(i_13c4), 0x38, k_13c4, 0, -1);
        }
        SELE(x16, e_13c4)
        G->flags &= ~2;
        G->msg = "FM_EXP_LOAD";
        fn_801945E8(0x1e, P);
        break;
    }
    case 0x13c9: {
 fn_801958C0(P); G->st = 0x13ce; break;
    }
    case 0x13ce: {int d_13ce;

        { d_13ce;
        switch (fn_8019F0F4()) { case 0: d_13ce = 0; break; case 1: d_13ce = 1; break; case 2: d_13ce = 2; break; case 3: G->st = 0x1392; return; }
        { int t = fn_8019FC40(fn_80194A28(G->x16)); fn_800609D8(lbl_803CAB38, 1, d_13ce, t); }
        if (G->flags & 8) fn_8024B6D4(G->x16, d_13ce, G->x88, P); else fn_8024B6D4(G->x16, d_13ce, 0, P);
        fn_8028392C("FM_SAVING", 0, 0, 0, P, 1);
        G->st = 0x13d3; }
        break;
    }
    case 0x13d3: {

        if (fn_8019FB08() == 0) {
            fn_80283A58();
            fn_8019F370(fn_80194800(G->x16), "SFX_SYS_SAVE_OK1");
            fn_801945E8(0x64, P);
            G->st = 0x13d8;
        } else {
            fn_8028392C("FM_ERR_LOAD", 0, 0, 1, P, 0);
            G->st = 0x1392;
        }
        break;
    }
    case 0x13d8: {
 fn_8024B764(G->x16, P); G->st = 0x13e2; break;
    }
    case 0x13e2: {void* s_13e2;

        if (fn_8019FB08() == 0) {
            s_13e2 = fn_80194A28(G->x16);
            if (((*(u32*)((u8*)fn_8019FC80(s_13e2) + 0) >> 20) & 1) == 1 || fn_8019FDA0(fn_8019FBA4(s_13e2)) == 0) G->flags |= 1;
            fn_800C835C(3, 0xfa); fn_800CD4A4(0x20); fn_800CD548(G->x16); EXIT();
        } else {
            fn_8028392C("FM_ERR_LOAD", 0, 0, 1, P, 0);
            ErrSt(G, 0x1392, lbl_804CB944);
        }
        break;
    }
    case 0x1770: {int j_1770; int i_1770;

        { A29 = fn_801949E4();
        for (j_1770 = 0; j_1770 < 6; j_1770++) fn_80196E14(fn_80194800(j_1770), j_1770, 0);
        G->x16 = fn_8019FC74(A29);
        if (fn_8019F39C(fn_80194800(G->x16)) == 0) G->x16 = fn_80194B60(); }
        SLIDEIN(i_1770, A29, S26)
        G->st = 0x177a;
        G->msg = "FM_EXP_INTR";
        fn_801945E8(0x19, P);
        break;
    }
    case 0x177a: {void* e_177a;

        SELE(x16, e_177a)
        G->st = 0x1784;
        break;
    }
    case 0x1784: {int old_1784; void* e_1784;

        if (held & 0x400) {
            SND("SFX_SYS_SELECT1");
            if (*(s16*)((u8*)fn_80194800(G->x16) + 0x34) == 0 || *(s16*)((u8*)fn_80194800(G->x16) + 0x34) == 1) {
                fn_8024BA00(G->x16, P);
                G->st = 0x1798;
                break;
            }
            fn_8028392C("FM_INTRING", 0, 0, 0, P, 1);
            fn_8024BA00(G->x16, P);
            G->st = 0x178e;
            break;
        }
        if (held & 0x800) { G->st = 0x2ee0; SND("SFX_SYS_CANCEL1"); break; }
        NAVL39(x16, old_1784)
        MOVEE(x16, e_1784, old_1784)
        break;
    }
    case 0x178e: {

        if (fn_8019FB08() == 0) { fn_8024BB08(G->x16, P); G->st = 0x1798; break; }
        fn_8028392C("FM_ERR_CONTINUE", 0, 0, 1, P, 0);
        G->st = 0x2ee0;
        break;
    }
    case 0x1798: {

        fn_80283A58();
        if (fn_8019FB08() == 0) { fn_800C835C(3, 0xfa); fn_800CD4A4(0x21); fn_800CD548(G->x16); EXIT(); break; }
        fn_8028392C("FM_ERR_DELETE_INTR", 0, 0, 1, P, 0);
        G->st = 0x2ee0;
        break;
    }
    case 0x1b58: {int j_1b58;

        { A29 = fn_801949E4();
        for (j_1b58 = 0; j_1b58 < 6; j_1b58++) fn_80196E14(fn_80194800(j_1b58), j_1b58, 0);
        G->x16 = fn_8019FC74(A29);
        if (G->x16 < 0 || G->x16 >= 6) G->x16 = 0; }
        SLIDEIN(A28, A29, S26)
        if (G->x14 == 1) G->st = 0x1b62; else G->st = 0x1b5d;
        G->msg = "FM_EXP_SAVE";
        fn_80194834(1);
        fn_801945E8(0x19, P);
        break;
    }
    case 0x1b5d: {
 G->st = 0x1b62; fn_8028392C("FM_SAVE_COMP", 0, 0, 0, P, 0); break;
    }
    case 0x1b62: {void* e_1b62;

        SELE(x16, e_1b62)
        fn_80194834(1);
        G->st = 0x1b6c;
        break;
    }
    case 0x1b6c: {int old_1b6c; void* e_1b6c;

        if (held & 0x400) {
            fn_80194834(2);
            fn_8028392C("FM_Q_SURE_SAVE", 1, "SFX_SYS_SELECT1", 0, P, 2);
            G->st = 0x1b71;
            SND("SFX_SYS_SELECT1");
            break;
        }
        if (held & 0x800) { G->st = 0x1b9e; SND("SFX_SYS_CANCEL1"); break; }
        NAVW(x16, 5, old_1b6c)
        MOVEE(x16, e_1b6c, old_1b6c)
        break;
    }
    case 0x1b71: {int v_1b71;

        if (fn_80245DFC(fn_8024BCA0()) == 0) {
            v_1b71 = fn_8019FDA8(fn_80060728(lbl_803CAB38));
            fn_80245D00(fn_8024BCA0(), 0, v_1b71, (u8)G->x16);
        }
        if (fn_8019FD14() == 1) { fn_8028392C("FM_SAVING", 0, 0, 0, P, 1); G->st = 0x1b76; }
        else G->st = 0x1b62;
        break;
    }
    case 0x1b76: {s8 b_1b76;

        if (fn_8019F39C(fn_80194800(G->x16))) {
            lbl_804CB944 = G->x16; fn_8024BB08(G->x16, P);
            G->st = 0x1b80;
        } else G->st = 0x1b8a;
        break;
    }
    case 0x1b80: {

        if (fn_8019FB08() == 0) { G->st = 0x1b8a; break; }
        fn_8028392C("FM_ERR_DELETE_INTR", 0, 0, 1, P, 0);
        ErrSt(G, 0x1b62, lbl_804CB944);
        break;
    }
    case 0x1b8a: {

        if (G->x14 != 2) { fn_8024B7E8(G->x16, P); }
        else {
            fn_8019FC88(fn_8024BCA0(), 2);
            if (fn_8019FDB0(lbl_803CAB38) >= 3) fn_80245574(fn_8024BC94());
            fn_8019FDB8(lbl_803CAB38, fn_8019FDB0(lbl_803CAB38) + 1);
            fn_8024B7E8(G->x16, P);
        }
        G->st = 0x1b94;
        break;
    }
    case 0x1b94: {

        if (fn_8019FB08() == 0) {
            fn_80283A58();
            fn_8019F370(fn_80194800(G->x16), "SFX_SYS_SAVE_OK1");
            G->st = 0x1bb2;
            fn_801945E8(0x64, P);
            break;
        }
        fn_8028392C("FM_ERR_SAVE", 0, 0, 1, P, 0);
        ErrSt(G, 0x1b62, lbl_804CB944);
        break;
    }
    case 0x1b9e: {

        if (G->x14 != 2) { G->st = 0x1bb2; break; }
        G->st = 0x1ba8;
        fn_80194834(2);
        fn_8028392C("FM_Q_END_SAVE_COMP", 1, "SFX_SYS_SELECT1", 0, P, 2);
        break;
    }
    case 0x1ba8: {

        if (fn_8019FD14() == 1) G->st = 0x1bb2; else G->st = 0x1b62;
        break;
    }
    case 0x1bb2: {
 fn_800C835C(3, 0xfa); EXIT(); break;
    }
    case 0x1f40: {int j_1f40; int k_1f40;

        for (j_1f40 = 0; j_1f40 < 6; j_1f40++) fn_8019F3A8(fn_80194800(j_1f40), j_1f40);
        G->x16 = 0;
        if (G->x16 < 0 || G->x16 >= 6) G->x16 = 0;
        SLIDEIN(A29, k_1f40, S26)
        G->st = 0x1f4a;
        G->msg = "FM_EXP_SAVE";
        fn_80194834(1);
        fn_801945E8(0x19, P);
        break;
    }
    case 0x1f4a: {void* e_1f4a;

        SELE(x16, e_1f4a)
        fn_80194834(1);
        G->st = 0x1f54;
        break;
    }
    case 0x1f54: {int old_1f54; void* e_1f54;

        if (held & 0x800) { G->st = 0x1f5e; SND("SFX_SYS_CANCEL1"); break; }
        NAVW(x16, 5, old_1f54)
        MOVEE(x16, e_1f54, old_1f54)
        break;
    }
    case 0x1f5e: {
 fn_800C835C(3, 0xfa); EXIT(); break;
    }
    case 0x2328: {int i_2328;

        G->x16 = -1;
        for (A29 = 0; A29 < 6; A29++) {
            fn_80196E14(fn_80194800(A29), A29, 0);
            if (fn_8019F35C(fn_80194800(A29)) && G->x16 == -1) G->x16 = A29;
        }
        SLIDEIN(i_2328, A29, S26)
        G->st = 0x2332;
        G->msg = "FM_EXP_COPY_SRC";
        fn_801945E8(0x19, P);
        break;
    }
    case 0x2332: {void* e_2332;

        SELE(x16, e_2332)
        fn_80194834(1);
        G->st = 0x233c;
        break;
    }
    case 0x233c: {void* e_233c; int old_233c;

        if (held & 0x400) {
            G->x17 = -1;
            for (A29 = 0; A29 < 6; A29++) if (fn_8019F35C(fn_80194800(A29)) == 0 && G->x17 == -1) G->x17 = A29;
            SELE(x17, e_233c)
            G->st = 0x2346;
            SND("SFX_SYS_SELECT1");
            G->msg = "FM_EXP_COPY_DST";
            break;
        }
        if (held & 0x800) { G->st = 0x2ee0; SND("SFX_SYS_CANCEL1"); break; }
        NAVL(x16, EZ, old_233c)
        MOVEE(x16, e_233c, old_233c)
        break;
    }
    case 0x2346: {int old_2346; void* e_2346;

        if (held & 0x400) {
            fn_8028392C("FM_SAVING", 0, 0, 0, P, 1);
            fn_8024B8F0(G->x16, G->x17, P);
            G->st = 0x2350;
            SND("SFX_SYS_SELECT1");
            break;
        }
        if (held & 0x800) {
            G->st = 0x2332;
            fn_80197858(fn_80194800(G->x17), 0);
            G->msg = "FM_EXP_COPY_SRC";
            SND("SFX_SYS_CANCEL1");
            break;
        }
        NAVL(x17, NZ, old_2346)
        MOVEE(x17, e_2346, old_2346)
        break;
    }
    case 0x2350: {

        if (fn_8019FB08() == 0) {
            fn_80283A58();
            fn_8019F370(fn_80194800(G->x17), "SFX_SYS_SAVE_OK1");
            G->st = 0x235a;
            fn_801945E8(0x64, P);
            break;
        }
        fn_8028392C("FM_ERR_COPY", 0, 0, 1, P, 0);
        G->st = 0x235a;
        break;
    }
    case 0x235a: {int c_235a; void* e_235a;

        fn_80197858(fn_80194800(G->x17), 0);
        { c_235a = fn_80194CB0();
        if (c_235a >= 1 && c_235a < 6) {
            G->msg = "FM_EXP_COPY_SRC";
            G->st = 0x233c;
            { e_235a = fn_80194800(G->x16); fn_80197880(fn_80194820(0), e_235a, 4); }
            break;
        } }
        G->st = 0x2ee0;
        break;
    }
    case 0x2710: {int j_2710; int k_2710;

        G->x16 = -1;
        for (j_2710 = 0; j_2710 < 6; j_2710++) {
            fn_80196E14(fn_80194800(j_2710), j_2710, 0);
            if (fn_8019F35C(fn_80194800(j_2710)) && G->x16 == -1) G->x16 = j_2710;
        }
        SLIDEIN(A29, k_2710, S26)
        G->st = 0x271a;
        G->msg = "FM_EXP_DELETE";
        fn_801945E8(0x19, P);
        break;
    }
    case 0x271a: {void* e_271a;

        SELE(x16, e_271a)
        fn_80194834(1);
        G->st = 0x2724;
        break;
    }
    case 0x2724: {int old_2724; void* e_2724;

        if (held & 0x400) {
            fn_80194834(2);
            fn_8028392C("FM_Q_SURE_DELETE", 1, "SFX_SYS_SELECT1", 0, P, 2);
            G->st = 0x272e;
            SND("SFX_SYS_SELECT1");
            break;
        }
        if (held & 0x800) { G->st = 0x2ee0; SND("SFX_SYS_CANCEL1"); break; }
        NAVL(x16, EZ, old_2724)
        MOVEE(x16, e_2724, old_2724)
        break;
    }
    case 0x272e: {

        if (fn_8019FD14() == 1) {
            fn_8028392C("FM_DELETING", 0, 0, 0, P, 1);
            if (fn_8019F39C(fn_80194800(G->x16))) { G->st = 0x2738; fn_8024BB08(G->x16, P); break; }
            G->st = 0x2742;
            break;
        }
        G->st = 0x271a;
        break;
    }
    case 0x2738: {

        if (fn_8019FB08() == 0) { G->st = 0x2742; break; }
        fn_8028392C("FM_ERR_DELETE_INTR", 0, 0, 1, P, 0);
        G->st = 0x271a;
        fn_801972FC(fn_80194800(G->x16));
        break;
    }
    case 0x2742: {
 fn_8024B86C(G->x16, P); G->st = 0x274c; break;
    }
    case 0x274c: {

        if (fn_8019FB08() == 0) {
            fn_80283A58();
            fn_8019F370(fn_80194800(G->x16), "SFX_SYS_SAVE_DELETE1");
            G->st = 0x2756;
            fn_801945E8(0x64, P);
            break;
        }
        fn_8028392C("FM_ERR_DELETE", 0, 0, 1, P, 0);
        G->st = 0x2756;
        fn_801972FC(fn_80194800(G->x16));
        break;
    }
    case 0x2756: {void* e_2756;

        if (fn_80194CB0() >= 1) {
            fn_80197858(fn_80194800(G->x16), 0);
            G->x16 = -1;
            for (A29 = 0; A29 < 6; A29++) if (fn_8019F35C(fn_80194800(A29)) && G->x16 == -1) G->x16 = A29;
            { e_2756 = fn_80194800(G->x16); fn_80197880(fn_80194820(0), e_2756, 4); }
            fn_80197858(fn_80194800(G->x16), 1);
            G->st = 0x271a;
            break;
        }
        G->st = 0x2ee0;
        break;
    }
    case 0x2ee0: {s16 x_2ee0; s16 y_2ee0;

        for (A29 = 0; A29 < 6; A29++) {
            x_2ee0 = fn_801978D8(fn_80194800(A29));
            y_2ee0 = fn_801978E0(fn_80194800(A29));
            if (A29 % 2 == 0) fn_801977E0(fn_80194800(A29), x_2ee0 - 0x3e8, y_2ee0, 0x1e, 4); else fn_801977E0(fn_80194800(A29), x_2ee0 + 0x3e8, y_2ee0, 0x1e, 4);
            fn_8019F50C(fn_80194800(A29), 4);
        }
        fn_80196DD4(fn_80194820(0), -0x3e8, -0x3e8, 0);
        G->st = 0x7d0;
        G->msg = 0;
        fn_801945E8(0x1e, P);
        break;
    }
    }
}
}
