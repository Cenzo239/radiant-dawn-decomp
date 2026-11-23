#include "game/rF_8017F400/types.h"

#pragma auto_inline off

extern "C" {

extern void fn_80006A2C(void* handle); /* release resource handle */
extern void* fn_80081194(void* cls, void* parent); /* create process with parent */

typedef struct Struct801855C8 {
    u8 pad[0x60];
    void* res; /* 0x60 */
} Struct801855C8;

void fn_801855C8(Struct801855C8* p)
{
    if (p->res != NULL) {
        fn_80006A2C(&p->res);
    }
}

typedef struct Flags80060728 {
    u32 pad : 23;
    u32 flag : 1;
    u32 rest : 8;
} Flags80060728;

typedef struct Struct8008D750 {
    u8 pad[0x120];
    void* unk120;
    void* unk124;
} Struct8008D750;

extern u8 lbl_803CAB38[];
extern u8 lbl_80388010[]; /* process class */
extern Flags80060728* fn_80060728(void* p);
extern Struct8008D750* fn_8008D750(void);

void fn_801855E0(void* parent)
{
    if (fn_80060728(lbl_803CAB38)->flag != 1 && fn_8008D750()->unk120 != NULL && fn_8008D750()->unk124 != NULL) {
        if (fn_80081194(lbl_80388010, parent) == NULL) {
            return;
        }
    }
}

extern void fn_801AD418(void* p);
extern void fn_801B5D14(void* p);
extern void fn_80192F78(void* p);
extern void fn_80280DF8(void* p);
extern void fn_801AD428(void);
extern void fn_801B5D24(void);
extern void fn_80192FC8(void);
extern void fn_80280E5C(void);
extern void fn_801AD434(void);
extern void fn_801B5D30(void);
extern void fn_80192FD4(void);
extern void fn_80280E68(void);
extern void fn_801AD46C(void);
extern void fn_801B5D68(void);
extern void fn_80193014(void);
extern void fn_80280EA4(void);
extern void fn_801AD4DC(void);
extern void fn_801B5DA0(void);
extern void fn_801930DC(void);
extern void fn_80280EE0(void);

/* subsystem fan-out: init / ... for four subsystems */
void fn_80185658(void* p)
{
    fn_801AD418(p);
    fn_801B5D14(p);
    fn_80192F78(p);
    fn_80280DF8(p);
}

void fn_8018569C(void)
{
    fn_801AD428();
    fn_801B5D24();
    fn_80192FC8();
    fn_80280E5C();
}

void fn_801856C8(void)
{
    fn_801AD434();
    fn_801B5D30();
    fn_80192FD4();
    fn_80280E68();
}

void fn_801856F4(void)
{
    fn_801AD46C();
    fn_801B5D68();
    fn_80193014();
    fn_80280EA4();
}

void fn_80185720(void)
{
    fn_801AD4DC();
    fn_801B5DA0();
    fn_801930DC();
    fn_80280EE0();
}

extern int fn_8017FA1C(void); /* frame counter */
extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E4E4(f32 a, f32 b, f32 c, f32 d);
#if TARGET_PC
extern FE10_PROTO void fn_8007E374(void* tex, p32arg, int b);
#else
extern void fn_8007E374(void* tex, int a, int b);
#endif
extern void fn_800800D4(int a);
extern void fn_80080388(f32 x0, f32 y0, f32 x1, f32 y1);
extern void fn_80080410(f32 u0, f32 v0, f32 u1, f32 v1);
extern void fn_8008031C(f32 z);
extern void fn_80080308(void);
extern void fn_800804D4(int r, int g, int b, int a);

typedef struct Struct8018574C {
    u8 pad[0x30];
    void* tex;   /* 0x30 */
    int scroll;  /* 0x34 */
} Struct8018574C;

/* draw scrolling full-screen background (608x480) */
void fn_8018574C(Struct8018574C* p)
{
    p->scroll = fn_8017FA1C() & 0x3FF;
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 900.0f, 1.0f);
    fn_8007E374(p->tex, 0, 0);
    fn_8007E164();
    fn_800800D4(1);
    fn_80080388(0.0f, 0.0f, 608.0f, 480.0f);
    fn_80080410(0.0f, (1.0f / 1024.0f) * p->scroll, 1.0f, (1.0f / 1024.0f) * p->scroll + 0.9375f);
    fn_8008031C(8.0f);
    fn_80080308();
    fn_8007E154();
    fn_8007E374(p->tex, 1, 0x30);
    fn_8007E164();
    fn_800800D4(1);
    fn_80080388(0.0f, 0.0f, 608.0f, 480.0f);
    fn_800804D4(0x32, 0x32, 0x32, 0);
    fn_8008031C(-2.0f);
    fn_80080308();
}

void fn_80185874(Struct8018574C* p)
{
    fn_80006A2C(&p->tex);
}

}
