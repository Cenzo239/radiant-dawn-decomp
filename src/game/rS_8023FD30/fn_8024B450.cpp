#include "game/rS_8023FD30/types.h"

/* Save-file worker thread starters. One thread (sThread) and one arg block are shared; each
   starter fills the arg, creates the thread on a job function, starts a waiting proc when
   given a parent, then resumes the thread. The statics reproduce the pooled base. */
struct JobArg {
    u8 a;
    u8 b;
    u8 c;
    u8 pad;
    s32 d;
    s32 e;
    s32 f;
};

static u8 sHeader[0x10];         /* +0x0000 lbl_80427810 */
static u8 sData0[0x1BE0];        /* +0x0010 lbl_80427820 */
static u8 sData1[0x1070];        /* +0x1BF0 lbl_80429400 */
static u8 sThread[0x318];        /* +0x2C60 lbl_8042A470 */
static u8 sStack[0x4000];        /* +0x2F78 */
static JobArg sArg;              /* +0x6F78 */

void rS_saveKeep(void** p) {
    p[0] = sHeader;
    p[1] = sData0;
    p[2] = sData1;
}

extern "C" {

extern char lbl_803910F0[];
void fn_8031FC48(void*, void*, void*, void*, s32, s32, s32);
void fn_803202B0(void*);
void fn_80081194(void*, void*);

#define JOB_DECL(name) void name(void*);

JOB_DECL(fn_80246568)
JOB_DECL(fn_80246E0C)
JOB_DECL(fn_80246E68)
JOB_DECL(fn_80247578)
JOB_DECL(fn_802479A8)
JOB_DECL(fn_80248154)
JOB_DECL(fn_802488B8)
JOB_DECL(fn_80248CCC)
JOB_DECL(fn_802493B4)
JOB_DECL(fn_8024953C)
JOB_DECL(fn_80249BDC)
JOB_DECL(fn_80249FF4)
JOB_DECL(fn_8024A410)
JOB_DECL(fn_8024AB04)
JOB_DECL(fn_8024AC94)
JOB_DECL(fn_8024B0B4)

#define JOB_RUN(job) \
    fn_8031FC48(sThread, job, &sArg, sStack + 0x4000, 0x4000, 0x18, 1); \
    if (parent != 0) { \
        fn_80081194(lbl_803910F0, parent); \
    } \
    fn_803202B0(sThread);

void fn_8024B450(s32 a, void* parent) {
    *(s32*)&sArg = a;
    JOB_RUN(fn_80246568)
}

void fn_8024B4D4(void* parent) { JOB_RUN(fn_80246E0C) }
void fn_8024B554(void* parent) { JOB_RUN(fn_80246E68) }
void fn_8024B5D4(void* parent) { JOB_RUN(fn_80247578) }
void fn_8024B654(void* parent) { JOB_RUN(fn_802479A8) }

void fn_8024B6D4(u8 a, u8 c, s32 d, void* parent) {
    sArg.a = a;
    sArg.c = c;
    sArg.d = d;
    JOB_RUN(fn_80248154)
}

#define JOB_A(addr, job) \
    void fn_##addr(u8 a, void* parent) { \
        sArg.a = a; \
        JOB_RUN(job) \
    }

JOB_A(8024B764, fn_802488B8)
JOB_A(8024B7E8, fn_80248CCC)
JOB_A(8024B86C, fn_802493B4)

void fn_8024B8F0(u8 a, u8 b, void* parent) {
    sArg.a = a;
    sArg.b = b;
    JOB_RUN(fn_8024953C)
}

void fn_8024B978(u8 a, s32 e, void* parent) {
    sArg.a = a;
    sArg.e = e;
    JOB_RUN(fn_80249BDC)
}

JOB_A(8024BA00, fn_80249FF4)
JOB_A(8024BA84, fn_8024A410)
JOB_A(8024BB08, fn_8024AB04)

void fn_8024BB8C(u8 a, s32 e, void* parent) {
    sArg.a = a;
    sArg.e = e;
    JOB_RUN(fn_8024AC94)
}

void fn_8024BC14(void* parent) { JOB_RUN(fn_8024B0B4) }

}
