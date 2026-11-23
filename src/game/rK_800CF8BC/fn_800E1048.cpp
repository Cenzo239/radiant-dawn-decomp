#include "game/rK_800CF8BC/types.h"

/* The script command registrar. Generated from commands.txt; see NOTES.md. */
extern char lbl_80366654[];
extern u8 lbl_80384030[];
extern u8 lbl_804CB878[8];

extern "C" {
void fn_800C3C3C(const char*, void*, int);
void fn_8009E694(int);
void fn_8013E710();
void fn_800846BC(u8*);
void fn_800EB410();
void fn_8018569C();
void fn_800E4548();
void fn_8014D310(u8*);
void fn_800D7DB0(int a);
void fn_800D7F14(int a);
void fn_800D7F98(int a);
void fn_800D805C();
void fn_800D8124();
void fn_800D81EC(int a);
void fn_800D82D0(int a);
void fn_800D83B4(int a);
#if TARGET_PC
FE10_PROTO void fn_800D8498(p32arg);
#else
void fn_800D8498(int a);
#endif
void fn_800D85C8(int a);
void fn_800D86C8(int a);
void fn_800D87C8(int a);
void fn_800D88AC(int a);
void fn_800D8990(int a);
void fn_800D8A68();
void fn_800D8B34();
void fn_800D8C00();
void fn_800D8CC8(int a);
void fn_800D8D8C(int a, int b);
void fn_800D8E00(int a, int b);
void fn_800D8E74(int a);
#if TARGET_PC
FE10_PROTO void fn_800D8F88(p32arg);
#else
void fn_800D8F88(int a);
#endif
void fn_800D90B8(int a);
void fn_800D918C(int a);
void fn_800D9258(int a);
void fn_800D9324(int a);
void fn_800D93F0(int a);
void fn_800D94BC(int a);
void fn_800D9588(int a, int b);
void fn_800D9610(int a, int b);
void fn_800D9638(int a);
void fn_800D967C(int a);
#if TARGET_PC
FE10_PROTO void fn_800D9764(int a, p32arg, p32arg);
FE10_PROTO void fn_800D97C0(int);
FE10_PROTO void fn_800D9800(int);
#else
void fn_800D9764(int a, int b, int c);
void fn_800D97C0();
void fn_800D9800();
#endif
void fn_800D9834(int a);
#if TARGET_PC
FE10_PROTO void fn_800D987C(int a, p32arg);
#else
void fn_800D987C(int a, int b);
#endif
void fn_800D9AC8(int a, int b, int c);
#if TARGET_PC
FE10_PROTO void fn_800D9CE8(int a, p32arg);
#else
void fn_800D9CE8(int a, int b);
#endif
void fn_800D9EB8(int a, int b, int c);
void fn_800D9FA8(int a, int b, int c);
void fn_800DA1FC(int a, int b, int c, int d);
void fn_800DA430(int a, int b, int c);
void fn_800DA61C(int a, int b);
void fn_800DA74C(int a, int b, int c, int d, int e);
#if TARGET_PC
FE10_PROTO void fn_800DA898(int a, p32arg);
FE10_PROTO void fn_800DA9F4(int a, p32arg);
#else
void fn_800DA898(int a, int b);
void fn_800DA9F4(int a, int b);
#endif
void fn_800DAB6C(int a, int b, int c, int d);
#if TARGET_PC
FE10_PROTO void fn_800DACF8(int a, p32arg);
#else
void fn_800DACF8(int a, int b);
#endif
void fn_800DADA0(int a, int b, int c, int d, int e);
void fn_800DAF74(int a, int b);
void fn_800DAF84(int a);
void fn_800DB0B0(int a);
void fn_800DB138(int a);
void fn_800DB214(int a);
void fn_800DB2FC(int a);
void fn_800DB3E4(int a, int b, int c);
void fn_800DB56C(int a, int b, int c);
void fn_800DB6E4(int a, int b);
void fn_800DB7B0(int a, int b);
void fn_800DB98C(int a);
void fn_800DBA10(int a);
void fn_800DBAB4(int a);
void fn_800DBB58(int a, int b);
void fn_800DBD48(int a);
void fn_800DBE1C(int a);
void fn_800DBE58();
void fn_800DBE98(void* a);
void fn_800DBEBC(void* a);
void fn_800DBEE0();
void fn_800DBF74(int a);
void fn_800DC0A8(int a);
void fn_800DC114(int a, int b, int c, int d, int e, int f);
void fn_800DC1B0(int a);
void fn_800DC204();
void fn_800DC20C(int a, int b, int c, int d);
void fn_800DC2CC(int a, int b, int c, int d);
void fn_800DC38C(int a, int b, int c);
void fn_800DC424(int a, int b, int c);
void fn_800DC5A8(int a, int b, int c);
void fn_800DC680(int a, int b, int c);
void fn_800DC770();
void fn_800DC824();
void fn_800DC9D4();
void fn_800DCAD4(int a);
void fn_800DCB34();
void fn_800DCB5C(int a, int b, int c, int d);
void fn_800DCC38(int a, int b, int c, int d);
void fn_800DCD14(int a, int b, int c, int d);
void fn_800DCDF0(int a, int b);
#if TARGET_PC
FE10_PROTO void fn_800DCEAC(int a, p32arg);
#else
void fn_800DCEAC(int a, int b);
#endif
void fn_800DCEEC(int a);
void fn_800DCF10();
void fn_800DCF34();
void fn_800DCF58();
#if TARGET_PC
FE10_PROTO void fn_800DD0F0(p32arg, int b, int c, int d);
#else
void fn_800DD0F0(int a, int b, int c, int d);
#endif
void fn_800DD1B8();
void fn_800DD20C();
void fn_800DD214(int a, int b, int c);
void fn_800DD3E4(int a, int b);
void fn_800DD4A0(int a, int b);
void fn_800DD560(int a, int b, int c);
#if TARGET_PC
FE10_PROTO void fn_800DD680(p32arg, int b);
#else
void fn_800DD680(int a, int b);
#endif
void fn_800DD7C4(int a, int b);
void fn_800DD940(int a, int b);
void fn_800DDAB8(int a, int b);
void fn_800DDC7C(int a, int b);
void fn_800DDDAC(int a, int b);
void fn_800DDE60(int a, int b);
void fn_800DDF54(int a, int b);
void fn_800DE044(int a, int b);
void fn_800DE1B8(int a, int b);
void fn_800DE324(int a, int b, int c, int d);
void fn_800DE3C0(int a, int b, int c);
void fn_800DE45C(int a, int b);
void fn_800DE4C8(int a, int b);
void fn_800DE534(int a);
void fn_800DE5FC();
void fn_800DE604(int a, int b, int c);
void fn_800DE6D8(int a, int b, int c);
void fn_800DE794(int a, int b);
#if TARGET_PC
FE10_PROTO void fn_800DE854(int a, int b, p32arg);
FE10_PROTO void fn_800DE8EC(int a, int b, p32arg);
FE10_PROTO void fn_800DE9A8(p32arg, p32arg);
#else
void fn_800DE854(int a, int b, int c);
void fn_800DE8EC(int a, int b, int c);
void fn_800DE9A8(int a, int b);
#endif
void fn_800DE9FC();
#if TARGET_PC
FE10_PROTO void fn_800DEAE8(p32arg);
FE10_PROTO void fn_800DEB88(p32arg);
#else
void fn_800DEAE8(int a);
void fn_800DEB88(int a);
#endif
void fn_800DEC18(int a, int b, int c);
void fn_800DED44(int a, int b, int c, int d);
void fn_800DEE80(int a, int b, int c, int d);
#if TARGET_PC
FE10_PROTO void fn_800DF0B8(int a, int b, int c, p32arg);
#else
void fn_800DF0B8(int a, int b, int c, int d);
#endif
void fn_800DF2C8(int a, int b);
void fn_800DF368(int a, int b);
void fn_800DF438(int a, int b);
void fn_800DF4DC(int a, int b);
void fn_800DF56C(int a, int b);
void fn_800DF5DC(int a, int b);
void fn_800DF64C(int a, int b);
void fn_800DF6C8(int a);
void fn_800DF738(int a, int b);
#if TARGET_PC
FE10_PROTO void fn_800DF7D4(p32arg);
#else
void fn_800DF7D4(int a);
#endif
void fn_800DF80C(int a);
void fn_800DF894(int a, int b, int c);
void fn_800DF940();
void fn_800DF964(int a);
void fn_800DF984(int a);
void fn_800DF9A4(int a);
void fn_800DF9C4(int a);
void fn_800DF9E4(int a, int b);
void fn_800DFA60(int a, int b);
void fn_800DFB28(int a, int b);
void fn_800DFC78(int a);
void fn_800DFCC4();
void fn_800DFD00();
void fn_800E0284(int a, int b, int c, int d, int e);
void fn_800E0394(int a, int b);
void fn_800E0468(int a);
void fn_800E052C(int a);
void fn_800E0604(int a, int b);
void fn_800E07B0(int a, int b);
void fn_800E0A40(int a, int b);
void fn_800E0C14(int a, int b, int c, int d);
void fn_800E0CDC(int a, int b, int c, int d);
void fn_800E0D78(int a, int b);
void fn_800E0E10(int a, int b);
void fn_800E0E60(int a, int b);
void fn_800E0EB0(int a);
void fn_800E0F9C(int a, int b);

void fn_800E1048() {
    fn_800C3C3C(lbl_80366654 + 0x1B, (void*)fn_800D805C, 0);
    fn_800C3C3C(lbl_80366654 + 0x28, (void*)fn_800D8124, 0);
    fn_800C3C3C(lbl_80366654 + 0x34, (void*)fn_800D8A68, 0);
    fn_800C3C3C(lbl_80366654 + 0x3F, (void*)fn_800D8B34, 0);
    fn_800C3C3C(lbl_80366654 + 0x4B, (void*)fn_800D8C00, 0);
    fn_800C3C3C(lbl_80366654 + 0x57, (void*)fn_800D8E74, 1);
    fn_800C3C3C(lbl_80366654 + 0x63, (void*)fn_800D987C, 2);
    fn_800C3C3C(lbl_80366654 + 0x6F, (void*)fn_800D9AC8, 3);
    fn_800C3C3C(lbl_80366654 + 0x7B, (void*)fn_800D9CE8, 2);
    fn_800C3C3C(lbl_80366654 + 0x89, (void*)fn_800D9EB8, 3);
    fn_800C3C3C(lbl_80366654 + 0x94, (void*)fn_800D9FA8, 3);
    fn_800C3C3C(lbl_80366654 + 0x9F, (void*)fn_800DA1FC, 4);
    fn_800C3C3C(lbl_80366654 + 0xAD, (void*)fn_800DA430, 3);
    fn_800C3C3C(lbl_80366654 + 0xBD, (void*)fn_800D7F98, 1);
    fn_800C3C3C(lbl_80366654 + 0xC8, (void*)fn_800D7F14, 1);
    fn_800C3C3C(lbl_80366654 + 0xD7, (void*)fn_800DACF8, 2);
    fn_800C3C3C(lbl_80366654 + 0xE7, (void*)fn_800DAF74, 2);
    fn_800C3C3C(lbl_80366654 + 0xF0, (void*)fn_800DADA0, 5);
    fn_800C3C3C(lbl_80366654 + 0xFB, (void*)fn_800DAF84, 1);
    fn_800C3C3C(lbl_80366654 + 0x104, (void*)fn_800DB0B0, 1);
    fn_800C3C3C(lbl_80366654 + 0x10D, (void*)fn_800DB138, 1);
    fn_800C3C3C(lbl_80366654 + 0x116, (void*)fn_800DB214, 1);
    fn_800C3C3C(lbl_80366654 + 0x122, (void*)fn_800DB2FC, 1);
    fn_800C3C3C(lbl_80366654 + 0x12E, (void*)fn_800DB3E4, 3);
    fn_800C3C3C(lbl_80366654 + 0x139, (void*)fn_800DB56C, 3);
    fn_800C3C3C(lbl_80366654 + 0x142, (void*)fn_800DB7B0, 2);
    fn_800C3C3C(lbl_80366654 + 0x150, (void*)fn_800DB6E4, 2);
    fn_800C3C3C(lbl_80366654 + 0x165, (void*)fn_800D9588, 2);
    fn_800C3C3C(lbl_80366654 + 0x16D, (void*)fn_800D9610, 2);
    fn_800C3C3C(lbl_80366654 + 0x176, (void*)fn_800D97C0, 0);
    fn_800C3C3C(lbl_80366654 + 0x17F, (void*)fn_800D9800, 0);
    fn_800C3C3C(lbl_80366654 + 0x18E, (void*)fn_800D9834, 1);
    fn_800C3C3C(lbl_80366654 + 0x19C, (void*)fn_800D9638, 1);
    fn_800C3C3C(lbl_80366654 + 0x1AF, (void*)fn_800D9764, 3);
    fn_800C3C3C(lbl_80366654 + 0x1C4, (void*)fn_800D967C, 1);
    fn_800C3C3C(lbl_80366654 + 0x1D4, (void*)fn_800DBE1C, 1);
    fn_800C3C3C(lbl_80366654 + 0x1DC, (void*)fn_800DBE58, 0);
    fn_800C3C3C(lbl_80366654 + 0x1E4, (void*)fn_800DBEE0, 0);
    fn_800C3C3C(lbl_80366654 + 0x1EE, (void*)fn_800DBE98, 1);
    fn_800C3C3C(lbl_80366654 + 0x1F9, (void*)fn_800DBEBC, 1);
    fn_800C3C3C(lbl_80366654 + 0x204, (void*)fn_800DD7C4, 2);
    fn_800C3C3C(lbl_80366654 + 0x214, (void*)fn_800DD940, 2);
    fn_800C3C3C(lbl_80366654 + 0x225, (void*)fn_800DDAB8, 2);
    fn_800C3C3C(lbl_80366654 + 0x22E, (void*)fn_800DDC7C, 2);
    fn_800C3C3C(lbl_80366654 + 0x238, (void*)fn_800DDE60, 2);
    fn_800C3C3C(lbl_80366654 + 0x248, (void*)fn_800DDF54, 2);
    fn_800C3C3C(lbl_80366654 + 0x259, (void*)fn_800DE044, 2);
    fn_800C3C3C(lbl_80366654 + 0x262, (void*)fn_800DE1B8, 2);
    fn_800C3C3C(lbl_80366654 + 0x26C, (void*)fn_800DDDAC, 2);
    fn_800C3C3C(lbl_80366654 + 0x275, (void*)fn_800DE5FC, 3);
    fn_800C3C3C(lbl_80366654 + 0x27D, (void*)fn_800DE604, 3);
    fn_800C3C3C(lbl_80366654 + 0x286, (void*)fn_800DE794, 2);
    fn_800C3C3C(lbl_80366654 + 0x297, (void*)fn_800DE854, 3);
    fn_800C3C3C(lbl_80366654 + 0x2A3, (void*)fn_800DE8EC, 3);
    fn_800C3C3C(lbl_80366654 + 0x2AF, (void*)fn_800DBF74, 1);
    fn_800C3C3C(lbl_80366654 + 0x2BA, (void*)fn_800DC0A8, 1);
    fn_800C3C3C(lbl_80366654 + 0x2C3, (void*)fn_800DC1B0, 1);
    fn_800C3C3C(lbl_80366654 + 0x2CE, (void*)fn_800DC204, 0);
    fn_800C3C3C(lbl_80366654 + 0x2D9, (void*)fn_800DC38C, 3);
    fn_800C3C3C(lbl_80366654 + 0x2E9, (void*)fn_800DC20C, 4);
    fn_800C3C3C(lbl_80366654 + 0x2F4, (void*)fn_800DC2CC, 4);
    fn_800C3C3C(lbl_80366654 + 0x2FF, (void*)fn_800DC114, 6);
    fn_800C3C3C(lbl_80366654 + 0x306, (void*)fn_800D90B8, 1);
    fn_800C3C3C(lbl_80366654 + 0x30E, (void*)fn_800D918C, 1);
    fn_800C3C3C(lbl_80366654 + 0x318, (void*)fn_800D9258, 1);
    fn_800C3C3C(lbl_80366654 + 0x324, (void*)fn_800D9324, 1);
    fn_800C3C3C(lbl_80366654 + 0x331, (void*)fn_800D93F0, 1);
    fn_800C3C3C(lbl_80366654 + 0x33D, (void*)fn_800D94BC, 1);
    fn_800C3C3C(lbl_80366654 + 0x34B, (void*)fn_800D7DB0, 1);
    fn_800C3C3C(lbl_80366654 + 0x35A, (void*)fn_800DC424, 3);
    fn_800C3C3C(lbl_80366654 + 0x364, (void*)fn_800DC5A8, 3);
    fn_800C3C3C(lbl_80366654 + 0x371, (void*)fn_800DC680, 3);
    fn_800C3C3C(lbl_80366654 + 0x385, (void*)fn_800DC770, 0);
    fn_800C3C3C(lbl_80366654 + 0x393, (void*)fn_800DC824, 0);
    fn_800C3C3C(lbl_80366654 + 0x3A1, (void*)fn_800DC9D4, 0);
    fn_800C3C3C(lbl_80366654 + 0x3B6, (void*)fn_800DCAD4, 1);
    fn_800C3C3C(lbl_80366654 + 0x3C9, (void*)fn_800DCB34, 0);
    fn_800C3C3C(lbl_80366654 + 0x3DB, (void*)fn_800DCB5C, 4);
    fn_800C3C3C(lbl_80366654 + 0x3EC, (void*)fn_800DCC38, 4);
    fn_800C3C3C(lbl_80366654 + 0x3FE, (void*)fn_800DCD14, 4);
    fn_800C3C3C(lbl_80366654 + 0x410, (void*)fn_800DCDF0, 2);
    fn_800C3C3C(lbl_80366654 + 0x423, (void*)fn_800DCEAC, 2);
    fn_800C3C3C(lbl_80366654 + 0x437, (void*)fn_800DCEEC, 1);
    fn_800C3C3C(lbl_80366654 + 0x448, (void*)fn_800DCF10, 0);
    fn_800C3C3C(lbl_80366654 + 0x459, (void*)fn_800DCF34, 0);
    fn_800C3C3C(lbl_80366654 + 0x46B, (void*)fn_800DCF58, 0);
    fn_800C3C3C(lbl_80366654 + 0x479, (void*)fn_800D8CC8, 1);
    fn_800C3C3C(lbl_80366654 + 0x48C, (void*)fn_800DE9A8, 2);
    fn_800C3C3C(lbl_80366654 + 0x49A, (void*)fn_800DE9FC, 0);
    fn_800C3C3C(lbl_80366654 + 0x4A8, (void*)fn_800DEAE8, 1);
    fn_800C3C3C(lbl_80366654 + 0x4B3, (void*)fn_800DEB88, 1);
    fn_800C3C3C(lbl_80366654 + 0x4C0, (void*)fn_800DEC18, 3);
    fn_800C3C3C(lbl_80366654 + 0x4CA, (void*)fn_800DED44, 4);
    fn_800C3C3C(lbl_80366654 + 0x4D4, (void*)fn_800DEE80, 4);
    fn_800C3C3C(lbl_80366654 + 0x4E1, (void*)fn_800DF0B8, 4);
    fn_800C3C3C(lbl_80366654 + 0x4EC, (void*)fn_800DF2C8, 2);
    fn_800C3C3C(lbl_80366654 + 0x4F9, (void*)fn_800DF4DC, 2);
    fn_800C3C3C(lbl_80366654 + 0x505, (void*)fn_800DF56C, 2);
    fn_800C3C3C(lbl_80366654 + 0x511, (void*)fn_800DF5DC, 2);
    fn_800C3C3C(lbl_80366654 + 0x51D, (void*)fn_800DF64C, 2);
    fn_800C3C3C(lbl_80366654 + 0x52C, (void*)fn_800DF368, 2);
    fn_800C3C3C(lbl_80366654 + 0x537, (void*)fn_800DF438, 2);
    fn_800C3C3C(lbl_80366654 + 0x543, (void*)fn_800DF6C8, 1);
    fn_800C3C3C(lbl_80366654 + 0x550, (void*)fn_800DF738, 2);
    fn_800C3C3C(lbl_80366654 + 0x55E, (void*)fn_800DF7D4, 1);
    fn_800C3C3C(lbl_80366654 + 0x56C, (void*)fn_800DF80C, 1);
    fn_800C3C3C(lbl_80366654 + 0x575, (void*)fn_800DD0F0, 4);
    fn_800C3C3C(lbl_80366654 + 0x584, (void*)fn_800DD1B8, 0);
    fn_800C3C3C(lbl_80366654 + 0x591, (void*)fn_800DD20C, 1);
    fn_800C3C3C(lbl_80366654 + 0x59F, (void*)fn_800E0468, 1);
    fn_800C3C3C(lbl_80366654 + 0x5A7, (void*)fn_800E052C, 1);
    fn_800C3C3C(lbl_80366654 + 0x5AF, (void*)fn_800DF894, 3);
    fn_800C3C3C(lbl_80366654 + 0x5BA, (void*)fn_800DF940, 0);
    fn_800C3C3C(lbl_80366654 + 0x5C9, (void*)fn_800DD3E4, 2);
    fn_800C3C3C(lbl_80366654 + 0x5D7, (void*)fn_800DD4A0, 2);
    fn_800C3C3C(lbl_80366654 + 0x5E5, (void*)fn_800DD560, 3);
    fn_800C3C3C(lbl_80366654 + 0x5F5, (void*)fn_800DD680, 2);
    fn_800C3C3C(lbl_80366654 + 0x60B, (void*)fn_800DD214, 3);
    fn_800C3C3C(lbl_80366654 + 0x619, (void*)fn_800DE6D8, 3);
    fn_800C3C3C(lbl_80366654 + 0x627, (void*)fn_800DE324, 4);
    fn_800C3C3C(lbl_80366654 + 0x636, (void*)fn_800DE3C0, 3);
    fn_800C3C3C(lbl_80366654 + 0x64A, (void*)fn_800DE45C, 2);
    fn_800C3C3C(lbl_80366654 + 0x658, (void*)fn_800DE4C8, 2);
    fn_800C3C3C(lbl_80366654 + 0x666, (void*)fn_800DE534, 1);
    fn_800C3C3C(lbl_80366654 + 0x671, (void*)fn_800D8D8C, 2);
    fn_800C3C3C(lbl_80366654 + 0x682, (void*)fn_800D8E00, 2);
    fn_800C3C3C(lbl_80366654 + 0x68F, (void*)fn_800DF964, 1);
    fn_800C3C3C(lbl_80366654 + 0x69D, (void*)fn_800DF984, 1);
    fn_800C3C3C(lbl_80366654 + 0x6AB, (void*)fn_800DF9A4, 1);
    fn_800C3C3C(lbl_80366654 + 0x6B6, (void*)fn_800DF9C4, 1);
    fn_800C3C3C(lbl_80366654 + 0x6C3, (void*)fn_800DF9E4, 2);
    fn_800C3C3C(lbl_80366654 + 0x6D0, (void*)fn_800DA61C, 2);
    fn_800C3C3C(lbl_80366654 + 0x6DD, (void*)fn_800DA74C, 5);
    fn_800C3C3C(lbl_80366654 + 0x6EA, (void*)fn_800DA898, 2);
    fn_800C3C3C(lbl_80366654 + 0x6F6, (void*)fn_800DA9F4, 2);
    fn_800C3C3C(lbl_80366654 + 0x701, (void*)fn_800DAB6C, 4);
    fn_800C3C3C(lbl_80366654 + 0x70F, (void*)fn_800D82D0, 1);
    fn_800C3C3C(lbl_80366654 + 0x71C, (void*)fn_800D81EC, 1);
    fn_800C3C3C(lbl_80366654 + 0x729, (void*)fn_800D83B4, 1);
    fn_800C3C3C(lbl_80366654 + 0x739, (void*)fn_800D8498, 1);
    fn_800C3C3C(lbl_80366654 + 0x746, (void*)fn_800D85C8, 1);
    fn_800C3C3C(lbl_80366654 + 0x753, (void*)fn_800D86C8, 1);
    fn_800C3C3C(lbl_80366654 + 0x761, (void*)fn_800D8F88, 1);
    fn_800C3C3C(lbl_80366654 + 0x76E, (void*)fn_800D87C8, 1);
    fn_800C3C3C(lbl_80366654 + 0x77D, (void*)fn_800D88AC, 1);
    fn_800C3C3C(lbl_80366654 + 0x78C, (void*)fn_800D8990, 1);
    fn_800C3C3C(lbl_80366654 + 0x79B, (void*)fn_800DBD48, 1);
    fn_800C3C3C(lbl_80366654 + 0x7AB, (void*)fn_800DFA60, 2);
    fn_800C3C3C(lbl_80366654 + 0x7BB, (void*)fn_800DFB28, 2);
    fn_800C3C3C(lbl_80366654 + 0x7C7, (void*)fn_800DFC78, 1);
    fn_800C3C3C(lbl_80366654 + 0x7D2, (void*)fn_800DFCC4, 0);
    fn_800C3C3C(lbl_80366654 + 0x7DE, (void*)fn_800DFD00, 0);
    fn_800C3C3C(lbl_80366654 + 0x7EA, (void*)fn_800E0284, 5);
    fn_800C3C3C(lbl_80366654 + 0x7F4, (void*)fn_800E0394, 2);
    fn_800C3C3C(lbl_80366654 + 0x7FE, (void*)fn_800E0604, 2);
    fn_800C3C3C(lbl_80366654 + 0x809, (void*)fn_800E07B0, 2);
    fn_800C3C3C(lbl_80366654 + 0x815, (void*)fn_800E0A40, 2);
    fn_800C3C3C(lbl_80366654 + 0x823, (void*)fn_800DB98C, 1);
    fn_800C3C3C(lbl_80366654 + 0x82E, (void*)fn_800DBB58, 2);
    fn_800C3C3C(lbl_80366654 + 0x83A, (void*)fn_800DBA10, 1);
    fn_800C3C3C(lbl_80366654 + 0x848, (void*)fn_800DBAB4, 1);
    fn_800C3C3C(lbl_80366654 + 0x856, (void*)fn_800E0C14, 4);
    fn_800C3C3C(lbl_80366654 + 0x866, (void*)fn_800E0CDC, 4);
    fn_800C3C3C(lbl_80366654 + 0x876, (void*)fn_800E0D78, 2);
    fn_800C3C3C(lbl_80366654 + 0x885, (void*)fn_800E0E10, 2);
    fn_800C3C3C(lbl_80366654 + 0x892, (void*)fn_800E0E60, 2);
    fn_800C3C3C(lbl_80366654 + 0x8A2, (void*)fn_800E0EB0, 1);
    fn_800C3C3C(lbl_80366654 + 0x8AF, (void*)fn_800E0F9C, 2);
}

void fn_800E1D94() {
    fn_8009E694(0);
    fn_8013E710();
    fn_800846BC(lbl_80384030);
    fn_800EB410();
    fn_8018569C();
    fn_800E4548();
    fn_8014D310(lbl_804CB878);
}
}
