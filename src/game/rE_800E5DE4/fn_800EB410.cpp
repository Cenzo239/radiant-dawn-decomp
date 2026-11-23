// Register the event-process classes in their original order.
// Initialized descriptor words and pointers reproduce the data pool at
// 0x80384300; separate statics retain the original base-relative addressing.
extern "C" {
extern char lbl_80366F90[];
extern char lbl_80366FA0[];
extern char lbl_80366FB0[];
extern char lbl_80366FBC[];
extern char lbl_80366FCC[];
extern char lbl_80366FD8[];
extern char lbl_80366FE8[];
extern char lbl_80366FF8[];
extern char lbl_80367004[];
extern char lbl_80367014[];
extern char lbl_80367020[];
extern char lbl_80367030[];
extern char lbl_8036703C[];
extern char lbl_8036704C[];
extern char lbl_80367058[];
extern char lbl_80367064[];
extern char lbl_80367070[];
extern char lbl_804CD990[];
void fn_8009F3F0(void* p);
#if TARGET_PC
FE10_PROTO void fn_800A026C(ptr32<const void>);
#else
void fn_800A026C(void* p);
#endif
void fn_800D6A44(void* p);
void fn_800D6A64();
void fn_800D6C28(void* p);
void fn_800D6C38();
void fn_800E5F60(void* p);
void fn_800E5FE0(void* p);
void fn_800E607C(void* p);
void fn_800E6198(void* p);
void fn_800E61BC(void* p);
void fn_800E628C(void* p);
void fn_800E6334(void* p);
void fn_800E63E8(void* p);
void fn_800E64D0(void* p);
void fn_800E6594(void* p);
void fn_800E6D04(void* p);
void fn_800E6E1C(void* p);
void fn_800E7174(void* p);
void fn_800E72A8(void* p);
void fn_800E7440(void* p);
void fn_800E7558(void* p);
void fn_800E7790(void* p);
void fn_800E7AD8(void* p);
void fn_800E7BD0(void* p);
void fn_800E7CC4(void* p);
void fn_800E7E70(void* p);
void fn_800E7FC0(void* p);
void fn_800E801C(void* p);
void fn_800E8304(void* p);
#if TARGET_PC
FE10_PROTO void fn_800E83BC(struct EvProc *);
#else
void fn_800E83BC();
#endif
void fn_800E8658(void* p);
void fn_800E871C(void* p);
#if TARGET_PC
FE10_PROTO void fn_800E8834(struct EvProc *);
#else
void fn_800E8834();
#endif
void fn_800E89F0(void* p);
void fn_800E8B70(void* p);
void fn_800E8D84(void* p);
void fn_800E92C8(void* p);
void fn_800E99AC(void* p);
void fn_800E9B28(void* p);
void fn_800E9CAC(void* p);
void fn_800E9D38(void* p);
void fn_800EA224(void* p);
void fn_800EA3DC(void* p);
void fn_800EA3F8(void* p);
void fn_800EA408(void* p);
void fn_800EAD10(void* p);
void fn_800EAEA4(void* p);
void fn_800EAF9C(void* p);
void fn_800EAFDC(void* p);
void fn_800EB048(void* p);
void fn_800EB274(void* p);
void fn_800EB3C8(void* p);
void fn_800EE77C();
void fn_800EFBCC();
void fn_800EFC04();
void fn_800EFFE8();
void fn_800F001C();
void fn_80104F18();
#if TARGET_PC
FE10_PROTO void fn_801774DC(ptr32<const void>, int a);
#else
void fn_801774DC(void* p, int a);
#endif
void fn_80194524(void* p);
void fn_800846BC(void*);
// Original address: 0x80384300.
static void* descriptor000[] = {
    (void*)0x2003,
    (void*)lbl_80366F90,
    (void*)0x2004,
    (void*)fn_800E61BC,
    (void*)0x100A,
    (void*)0x200F,
    (void*)fn_800E6334,
    (void*)0x1110,
    (void*)0x200F,
    (void*)fn_800E6D04,
    (void*)0x0,
    (void*)0x0
};
// Original address: 0x80384330.
static void* descriptor030[] = {
    (void*)0x2003,
    (void*)lbl_80366FA0,
    (void*)0x2004,
    (void*)fn_800E61BC,
    (void*)0x100A,
    (void*)0x200F,
    (void*)fn_800E6334,
    (void*)0x200F,
    (void*)fn_800F001C,
    (void*)0x200F,
    (void*)fn_800EE77C,
    (void*)0x1110,
    (void*)0x200F,
    (void*)fn_800E6594,
    (void*)0x200F,
    (void*)fn_800E6E1C,
    (void*)0x2014,
    (void*)fn_800EFFE8,
    (void*)0x1E2016,
    (void*)fn_801774DC,
    (void*)0x200F,
    (void*)fn_800EFBCC,
    (void*)0x2014,
    (void*)fn_800EFC04,
    (void*)0x631001,
    (void*)0x0,
    (void*)0x2003,
    (void*)lbl_80366FB0,
    (void*)0x2004,
    (void*)fn_800E61BC,
    (void*)0x100A,
    (void*)0x200F,
    (void*)fn_800F001C,
    (void*)0x200F,
    (void*)fn_800EE77C,
    (void*)0x1110,
    (void*)0x200F,
    (void*)fn_800E6594,
    (void*)0x200F,
    (void*)fn_800E7174,
    (void*)0x2014,
    (void*)fn_800EFFE8,
    (void*)0x1E2016,
    (void*)fn_801774DC,
    (void*)0x200F,
    (void*)fn_800EFBCC,
    (void*)0x2014,
    (void*)fn_800EFC04,
    (void*)0x631001,
    (void*)0x0
};
// Original address: 0x803843F8.
static void* descriptor0F8[] = {
    (void*)0x2003,
    (void*)lbl_80366FBC,
    (void*)0x2004,
    (void*)fn_800E61BC,
    (void*)0x100A,
    (void*)0x200F,
    (void*)fn_800E6334,
    (void*)0x1110,
    (void*)0x200F,
    (void*)fn_800E72A8,
    (void*)0x631001,
    (void*)0x0
};
// Original address: 0x80384428.
static void* descriptor128[] = {
    (void*)0x2003,
    (void*)lbl_80366FCC,
    (void*)0x2004,
    (void*)fn_800E61BC,
    (void*)0x100A,
    (void*)0x200F,
    (void*)fn_800E6334,
    (void*)0x200F,
    (void*)fn_800E5F60,
    (void*)0x1110,
    (void*)0x200F,
    (void*)fn_800E5FE0,
    (void*)0x201A,
    (void*)fn_800E607C,
    (void*)0x200F,
    (void*)fn_800E72A8,
    (void*)0x200F,
    (void*)fn_800E6198,
    (void*)0x200F,
    (void*)fn_80194524,
    (void*)0x2014,
    (void*)fn_80104F18,
    (void*)0x631001,
    (void*)0x0
};
// Original address: 0x80384488.
static void* descriptor188[] = {
    (void*)0x2003,
    (void*)lbl_80366FD8,
    (void*)0x2004,
    (void*)fn_800E61BC,
    (void*)0x100A,
    (void*)0x200F,
    (void*)fn_800F001C,
    (void*)0x200F,
    (void*)fn_800EE77C,
    (void*)0x200F,
    (void*)fn_800E6334,
    (void*)0x200F,
    (void*)fn_800E5F60,
    (void*)0x200F,
    (void*)fn_800E63E8,
    (void*)0xA2016,
    (void*)fn_801774DC,
    (void*)0x1110,
    (void*)0x200F,
    (void*)fn_800E6594,
    (void*)0x200F,
    (void*)fn_800E5FE0,
    (void*)0x201A,
    (void*)fn_800E607C,
    (void*)0x200F,
    (void*)fn_800E7440,
    (void*)0x200F,
    (void*)fn_800E6198,
    (void*)0x2014,
    (void*)fn_800EFFE8,
    (void*)0x1E2016,
    (void*)fn_801774DC,
    (void*)0x200F,
    (void*)fn_800EFBCC,
    (void*)0x2014,
    (void*)fn_800EFC04,
    (void*)0x200F,
    (void*)fn_80194524,
    (void*)0x2014,
    (void*)fn_80104F18,
    (void*)0x631001,
    (void*)0x0
};
// Original address: 0x80384530.
static void* descriptor230[] = {
    (void*)0x2003,
    (void*)lbl_80366FE8,
    (void*)0x2004,
    (void*)fn_800E61BC,
    (void*)0x100A,
    (void*)0x200F,
    (void*)fn_800F001C,
    (void*)0x200F,
    (void*)fn_800EE77C,
    (void*)0x200F,
    (void*)fn_800E6334,
    (void*)0x200F,
    (void*)fn_800E5F60,
    (void*)0x200F,
    (void*)fn_800E63E8,
    (void*)0xA2016,
    (void*)fn_801774DC,
    (void*)0x1110,
    (void*)0x200F,
    (void*)fn_800E5FE0,
    (void*)0x201A,
    (void*)fn_800E607C,
    (void*)0x200F,
    (void*)fn_800E7558,
    (void*)0x200F,
    (void*)fn_800E6198,
    (void*)0x200F,
    (void*)fn_80194524,
    (void*)0x2014,
    (void*)fn_80104F18,
    (void*)0x631001,
    (void*)0x0
};
// Original address: 0x803845B0.
static void* descriptor2B0[] = {
    (void*)0x2003,
    (void*)lbl_80366FF8,
    (void*)0x2004,
    (void*)fn_800E61BC,
    (void*)0x100A,
    (void*)0x200F,
    (void*)fn_800E6334,
    (void*)0x200F,
    (void*)fn_800E5F60,
    (void*)0x1110,
    (void*)0xA2016,
    (void*)fn_801774DC,
    (void*)0x200F,
    (void*)fn_800E5FE0,
    (void*)0x201A,
    (void*)fn_800E607C,
    (void*)0x200F,
    (void*)fn_800E7790,
    (void*)0x200F,
    (void*)fn_800E6198,
    (void*)0x200F,
    (void*)fn_80194524,
    (void*)0x2014,
    (void*)fn_80104F18,
    (void*)0x631001,
    (void*)0x0,
    (void*)0x2003,
    (void*)lbl_80367004,
    (void*)0x2004,
    (void*)fn_800E61BC,
    (void*)0x100A,
    (void*)0x200F,
    (void*)fn_800F001C,
    (void*)0x200F,
    (void*)fn_800EE77C,
    (void*)0x200F,
    (void*)fn_800E6334,
    (void*)0x200F,
    (void*)fn_800E5F60,
    (void*)0x200F,
    (void*)fn_800E63E8,
    (void*)0xA2016,
    (void*)fn_801774DC,
    (void*)0x1110,
    (void*)0x200F,
    (void*)fn_800E7AD8,
    (void*)0x200F,
    (void*)fn_800E5FE0,
    (void*)0x201A,
    (void*)fn_800E7BD0,
    (void*)0x200F,
    (void*)fn_800E7CC4,
    (void*)0x200F,
    (void*)fn_800E6198,
    (void*)0x2014,
    (void*)fn_800EFFE8,
    (void*)0x1E2016,
    (void*)fn_801774DC,
    (void*)0x200F,
    (void*)fn_800EFBCC,
    (void*)0x2014,
    (void*)fn_800EFC04,
    (void*)0x200F,
    (void*)fn_80194524,
    (void*)0x2014,
    (void*)fn_80104F18,
    (void*)0x631001,
    (void*)0x0
};
// Original address: 0x803846C0.
static void* descriptor3C0[] = {
    (void*)0x2003,
    (void*)lbl_80367014,
    (void*)0x2004,
    (void*)fn_800E61BC,
    (void*)0x200F,
    (void*)fn_800D6A44,
    (void*)0x100A,
    (void*)0x200F,
    (void*)fn_800E7E70,
    (void*)0x200F,
    (void*)fn_800E5F60,
    (void*)0x1110,
    (void*)0xA2016,
    (void*)fn_801774DC,
    (void*)0x200F,
    (void*)fn_800E5FE0,
    (void*)0x201A,
    (void*)fn_800E607C,
    (void*)0x200F,
    (void*)fn_800E7FC0,
    (void*)0x200F,
    (void*)fn_800E6198,
    (void*)0x200F,
    (void*)fn_800E801C,
    (void*)0x200F,
    (void*)fn_80194524,
    (void*)0x2014,
    (void*)fn_80104F18,
    (void*)0x631001,
    (void*)0x200F,
    (void*)fn_800D6A64,
    (void*)0x0,
    (void*)0x2003,
    (void*)lbl_80367020,
    (void*)0x2004,
    (void*)fn_800E61BC,
    (void*)0x100A,
    (void*)0x200F,
    (void*)fn_800E6334,
    (void*)0x1110,
    (void*)0x200F,
    (void*)fn_800E8304,
    (void*)0x200F,
    (void*)fn_800E83BC,
    (void*)0x0,
    (void*)0x0
};
// Original address: 0x80384778.
static void* descriptor478[] = {
    (void*)0x2003,
    (void*)lbl_80367030,
    (void*)0x2004,
    (void*)fn_800E61BC,
    (void*)0x100A,
    (void*)0x200F,
    (void*)fn_800E5F60,
    (void*)0x200F,
    (void*)fn_800E63E8,
    (void*)0x1110,
    (void*)0x200F,
    (void*)fn_800E5FE0,
    (void*)0x201A,
    (void*)fn_800E607C,
    (void*)0x200F,
    (void*)fn_800E8658,
    (void*)0x200F,
    (void*)fn_800E6198,
    (void*)0x2014,
    (void*)fn_80104F18,
    (void*)0x631001,
    (void*)0x0
};
// Original address: 0x803847D0.
static void* descriptor4D0[] = {
    (void*)0x2003,
    (void*)lbl_8036703C,
    (void*)0x2004,
    (void*)fn_800E61BC,
    (void*)0x100A,
    (void*)0x200F,
    (void*)fn_800A026C,
    (void*)0x200F,
    (void*)fn_800E6334,
    (void*)0x200F,
    (void*)fn_800E5F60,
    (void*)0x1110,
    (void*)0x200F,
    (void*)fn_800D6C28,
    (void*)0x200F,
    (void*)fn_800D6A44,
    (void*)0x200F,
    (void*)fn_800E5FE0,
    (void*)0x201A,
    (void*)fn_800E607C,
    (void*)0x200F,
    (void*)fn_800E871C,
    (void*)0x200F,
    (void*)fn_800E6198,
    (void*)0x2014,
    (void*)fn_80104F18,
    (void*)0x200F,
    (void*)fn_800E8834,
    (void*)0x200F,
    (void*)fn_800D6A64,
    (void*)0x200F,
    (void*)fn_800D6C38,
    (void*)0x0,
    (void*)0x2003,
    (void*)lbl_8036704C,
    (void*)0x2004,
    (void*)fn_800E61BC,
    (void*)0x100A,
    (void*)0x200F,
    (void*)fn_800E6334,
    (void*)0x200F,
    (void*)fn_800E64D0,
    (void*)0x1110,
    (void*)0x200F,
    (void*)fn_800E89F0,
    (void*)0x200F,
    (void*)fn_80194524,
    (void*)0x2014,
    (void*)fn_80104F18,
    (void*)0x0
};
// Original address: 0x80384898.
static void* descriptor598[] = {
    (void*)0x2003,
    (void*)lbl_80367058,
    (void*)0x2004,
    (void*)fn_800E61BC,
    (void*)0x100A,
    (void*)0x200F,
    (void*)fn_800E63E8,
    (void*)0x200F,
    (void*)fn_800E5F60,
    (void*)0xA2016,
    (void*)fn_801774DC,
    (void*)0x1110,
    (void*)0x200F,
    (void*)fn_800E5FE0,
    (void*)0x201A,
    (void*)fn_800E607C,
    (void*)0x200F,
    (void*)fn_800E8B70,
    (void*)0x200F,
    (void*)fn_800E6198,
    (void*)0x200F,
    (void*)fn_80194524,
    (void*)0x2014,
    (void*)fn_80104F18,
    (void*)0x631001,
    (void*)0x0,
    (void*)0x2003,
    (void*)lbl_80366FE8,
    (void*)0x2004,
    (void*)fn_800E61BC,
    (void*)0x100A,
    (void*)0x200F,
    (void*)fn_800F001C,
    (void*)0x200F,
    (void*)fn_800EE77C,
    (void*)0x200F,
    (void*)fn_800E6334,
    (void*)0x200F,
    (void*)fn_800E5F60,
    (void*)0x200F,
    (void*)fn_800E63E8,
    (void*)0xA2016,
    (void*)fn_801774DC,
    (void*)0x1110,
    (void*)0x200F,
    (void*)fn_800E5FE0,
    (void*)0x201A,
    (void*)fn_800E607C,
    (void*)0x200F,
    (void*)fn_800E8D84,
    (void*)0x200F,
    (void*)fn_800E6198,
    (void*)0x200F,
    (void*)fn_80194524,
    (void*)0x2014,
    (void*)fn_80104F18,
    (void*)0x631001,
    (void*)0x0
};
// Original address: 0x80384980.
static void* descriptor680[] = {
    (void*)0x2003,
    (void*)lbl_80367064,
    (void*)0x2004,
    (void*)fn_800E61BC,
    (void*)0x100A,
    (void*)0x200F,
    (void*)fn_800F001C,
    (void*)0x200F,
    (void*)fn_800EE77C,
    (void*)0x200F,
    (void*)fn_800E6334,
    (void*)0x1110,
    (void*)0x1206,
    (void*)0x200F,
    (void*)fn_800E6594,
    (void*)0x200F,
    (void*)fn_800E92C8,
    (void*)0x2014,
    (void*)fn_800EFFE8,
    (void*)0x1E2016,
    (void*)fn_801774DC,
    (void*)0x200F,
    (void*)fn_800EFBCC,
    (void*)0x2014,
    (void*)fn_800EFC04,
    (void*)0x2014,
    (void*)fn_80104F18,
    (void*)0x200F,
    (void*)fn_8009F3F0,
    (void*)0x200F,
    (void*)fn_800E628C,
    (void*)0x631001,
    (void*)0x0
};
// Original address: 0x80384A04.
static void* descriptor704[] = {
    (void*)0x2003,
    (void*)lbl_80367070,
    (void*)0x2004,
    (void*)fn_800E61BC,
    (void*)0x100A,
    (void*)0x200F,
    (void*)fn_800E99AC,
    (void*)0x200F,
    (void*)fn_800F001C,
    (void*)0x200F,
    (void*)fn_800EE77C,
    (void*)0x1110,
    (void*)0x1206,
    (void*)0x200F,
    (void*)fn_800D6A44,
    (void*)0x200F,
    (void*)fn_800E6594,
    (void*)0x200F,
    (void*)fn_800E9B28,
    (void*)0x1E100A,
    (void*)0x200F,
    (void*)fn_800E9CAC,
    (void*)0x201A,
    (void*)fn_800E9D38,
    (void*)0x200F,
    (void*)fn_800EA224,
    (void*)0x201A,
    (void*)fn_800EA3DC,
    (void*)0x200F,
    (void*)fn_800EA408,
    (void*)0x1E2016,
    (void*)fn_801774DC,
    (void*)0x2014,
    (void*)fn_800EFFE8,
    (void*)0x1206,
    (void*)0x200F,
    (void*)fn_800EA3F8,
    (void*)0x200F,
    (void*)fn_800EFBCC,
    (void*)0x2014,
    (void*)fn_800EFC04,
    (void*)0x631001,
    (void*)0x200F,
    (void*)fn_800D6A64,
    (void*)0x0
};
// Original address: 0x80384AB8.
static void* descriptor7B8[] = {
    (void*)0x2003,
    (void*)lbl_804CD990,
    (void*)0x2004,
    (void*)fn_800E61BC,
    (void*)0x100A,
    (void*)0x200F,
    (void*)fn_800EAD10,
    (void*)0x1110,
    (void*)0x1206,
    (void*)0x200F,
    (void*)fn_800D6A44,
    (void*)0x200F,
    (void*)fn_800EAEA4,
    (void*)0x1E100A,
    (void*)0x200F,
    (void*)fn_800EAF9C,
    (void*)0x201A,
    (void*)fn_800EAFDC,
    (void*)0x200F,
    (void*)fn_800EB048,
    (void*)0x201A,
    (void*)fn_800EB274,
    (void*)0x200F,
    (void*)fn_800EB3C8,
    (void*)0x1E2016,
    (void*)fn_801774DC,
    (void*)0x1206,
    (void*)0x631001,
    (void*)0x200F,
    (void*)fn_800D6A64,
    (void*)0x0,
    (void*)0x0
};
void fn_800EB410() {
    fn_800846BC(descriptor000);
    fn_800846BC(descriptor030);
    fn_800846BC(descriptor0F8);
    fn_800846BC(descriptor128);
    fn_800846BC(descriptor188);
    fn_800846BC(descriptor230);
    fn_800846BC(descriptor2B0);
    fn_800846BC(descriptor3C0);
    fn_800846BC(descriptor478);
    fn_800846BC(descriptor4D0);
    fn_800846BC(descriptor598);
    fn_800846BC(descriptor680);
    fn_800846BC(descriptor704);
    fn_800846BC(descriptor7B8);
}
}
