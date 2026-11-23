#include "game/rS_8023FD30/types.h"
/* Root save data: one constructor, written out in three places. The point and functor spellings
   differ per function only to get the original stack slots. */
struct Pt { s16 a, b; };
struct SaveS {
    u32 v0;
    u32 v4;
    u32 v8;
    u32 vC;
    u32 v10;
    u32 v14;
    u8 pad18[0x32 - 0x18];
    s8 v32;
    u8 pad33[0x40 - 0x33];
    u32 v40;
    u8 pad44[0x70 - 0x44];
    u8 a70[0x1000];
};
#define SYS_RESET(y) \
    (y).v4 = -1; \
    (y).v0 = -1; \
    (y).v8 = -1; \
    (y).vC = -1; \
    (y).v14 = 0; \
    (y).v10 = 0; \
    (y).v32 = -1; \
    (y).v40 = 0;
class LogE {
public:
    void clear();
    u8 pad[0x18];
};
struct SaveR {
    u32 magic0;
    u32 magic1;
    u32 v8;
    u32 vC;
    u32 v10;
    u32 v14;
    u32 pad18[2];
    u32 v20;
    u32 v24;
    u32 pad28;
    u32 v2C;
    u32 v30;
    u32 v34;
    u32 v38;
    const char* names[0x300];
    u32 hashes[0x300];
    u8 bits[0x60];
    u32 v189C;
    u32 v18A0;
    u32 v18A4;
    u32 v18A8;
    u32 v18AC;
    u32 v18B0;
    u32 v18B4;
    u32 v18B8;
    u32 v18BC;
    u32 v18C0;
    u32 v18C4;
    u32 v18C8;
    u32 v18CC;
    u32 v18D0;
    u32 v18D4;
    u32 v18D8;
    u32 v18DC;
    u32 v18E0;
    u32 v18E4;
    s16 v18E8;
    s16 v18EA;
    s16 v18EC;
    Pt p18EE;
    Pt p18F2;
    s16 v18F6;
    LogE log[30];
    u8 v1BC8;
    s8 v1BC9;
};
extern "C" {
extern SaveR lbl_80427820;
extern SaveS lbl_80429400;
extern void* lbl_804CBFD0;
extern s32 lbl_804CBFCC;
void* fn_80079940(u32, u32);
void fn_8017F44C(void*, s32, u32);
extern const char* lbl_804CAAB0;
extern const char* lbl_804CAAB4;
extern const char* lbl_804CAAB8;
extern char lbl_80372B4C[];
s32 fn_80315C6C(void*);
s32 fn_80315A5C(void*);
int fn_80290D04(char*, u32, const char*, ...);
s32 fn_80313B24(char*);
void fn_801E74CC(void);
u8 fn_80244D88(void);
}
struct MF {
    void (LogE::*pm)();
    MF(void (LogE::*p)()) { pm = p; }
    void operator()(LogE& x) { (x.*pm)(); }
};
static inline void forAll(LogE* b, LogE* e, MF f) {
    for (; b != e; b++) {
        f(*b);
    }
}
static inline void fill(u8* p) { for (int i = 0; i < 0x60; i++) { p[i] = 0; } }
static inline void setNone(Pt* d) { Pt a = {-1, -1}; *d = a; }
static inline void setNone2(Pt* d) { setNone(d); }
static const Pt sNoPt = { -1, -1 };
static const Pt sNoPt2 = { -1, -1 };
static inline void setP(Pt* d, Pt v) { *d = v; }
#define PTS_A(X) setNone2(&(X).p18EE); setNone(&(X).p18F2);
#define PTS_B(X) setP(&(X).p18EE, sNoPt); setP(&(X).p18F2, sNoPt2);
#define FOR_A(X) forAll((X).log, (X).log + 30, MF(&LogE::clear));
#define FOR_B(X) { MF m(&LogE::clear); forAll((X).log, (X).log + 30, m); }
#define ROOT_INIT(X, PTS, FOR) \
    (X).magic1 = -1; \
    (X).magic0 = -1; \
    (X).v8 = -1; \
    (X).vC = -1; \
    (X).v14 = 0; \
    (X).v10 = 0; \
    (X).v20 = 0; \
    (X).v24 = 0; \
    (X).v2C = 0; \
    (X).v30 = 0; \
    (X).v34 = 0; \
    (X).v38 = 0; \
    { \
        int i; \
        for (i = 0; i < 0x300; i++) { \
            (X).names[i] = 0; \
            (X).hashes[i] = 0; \
        } \
    } \
    { \
        fill((X).bits); \
    } \
    (X).v18A0 = 0; \
    (X).v18A4 = 0; \
    (X).v18A8 = 0; \
    (X).v18AC = 0; \
    (X).v18B4 = 0; \
    (X).v18B8 = 0; \
    (X).v18BC = 0; \
    (X).v18C0 = 0; \
    (X).v18C8 = 0; \
    (X).v18CC = 0; \
    (X).v18D4 = 0; \
    (X).v18D8 = 0; \
    (X).v18E0 = 0; \
    (X).v18E4 = 0; \
    (X).v18E8 = -1; \
    (X).v18EA = -1; \
    (X).v18EC = -1; \
    PTS(X) \
    (X).v18F6 = -1; \
    fn_801E74CC(); \
    FOR(X) \
    (X).v1BC8 = fn_80244D88(); \
    (X).v1BC9 = -1;

extern "C" {
void fn_80244D90(SaveR* s) {
    ROOT_INIT(*s, PTS_A, FOR_A)
}

void fn_80246100(void) {
    ROOT_INIT(lbl_80427820, PTS_B, FOR_B)
    SYS_RESET(lbl_80429400)
    fn_8017F44C(lbl_80429400.a70, -1, 0x1000);
    lbl_804CBFD0 = fn_80079940(0x18000, 0x40);
    lbl_804CBFCC = 0;
}
int fn_80247578(void) {
    SaveR* s = &lbl_80427820;
    SaveS* y = &lbl_80429400;
    ROOT_INIT(*s, PTS_B, FOR_B)
    SYS_RESET(*y)
    fn_8017F44C(y->a70, -1, 0x1000);
    s32 err;
    do {
        char tmp[0x40];
        char name[0x40];
        err = fn_80315C6C(tmp);
        if (err != 0) goto done;
        err = fn_80315A5C(tmp);
        if (err != 0) goto done;
        fn_80290D04(name, 0x40, lbl_80372B4C + 0x70, lbl_804CAAB0, lbl_804CAAB8);
        err = fn_80313B24(name);
        if (err == 0 || err == -0xC) {
            do {
                char name2[0x40];
                char tmp2[0x40];
                err = fn_80315C6C(tmp2);
                if (err != 0) goto done2;
                err = fn_80315A5C(tmp2);
                if (err != 0) goto done2;
                fn_80290D04(name2, 0x40, lbl_80372B4C + 0x70, lbl_804CAAB0, lbl_804CAAB4);
                err = fn_80313B24(name2);
            done2:
                lbl_804CBFCC = err;
            } while (err == -3);
        }
    done:
        lbl_804CBFCC = err;
    } while (err == -3);
    return 0;
}
}
