/* Round 20 draft, NOT at a counted level (check_regs.py: other): fn_800C9084. Self-contained, complete source. Instruction count ours 33 orig 33. What differs: same instructions except the first proc script argument: the original has lis/addi of lbl_80382930 in r30 and addi r3,r30,0 (pooled file statics in .data: scripts at +0, +0x40, +0x58, +0x80 with a jump table between them), ours splits lis and addi. Needs the real pooled data definitions. */
#include "game/rG_800A3D88/types.h"

// Screen fade / colour fade / filter processes and their globals (lbl_804CB6D0..DC).

#pragma auto_inline off

extern "C" {

extern const f32 lbl_804CD59C;
extern const f32 lbl_804CD5A0;
extern const f32 lbl_804CD5A4;
extern const f32 lbl_804CD5A8;
extern const f32 lbl_804CD5C8;
extern const f32 lbl_804CD600;
extern u8 lbl_80382930[];
extern u8 lbl_803829C8[];
extern u8 lbl_803829D8[];
extern u32 lbl_804CB700;

struct FadeG {
    u8 pad[0x30];
    u8 m30;
    u8 m31;
    u16 m32;
    u8 m34, m35, m36, m37;
    s16 m38, m3a, m3c, m3e;
    u8 pad40[8];
    void* m48;
};

struct FadeS {
    u8 pad[0x32];
    u16 m32;
    s16 m34;
    s16 m36;
};

extern FadeG* lbl_804CB6D0;
extern FadeG* lbl_804CB6D4;
extern FadeG* lbl_804CB6D8;
extern FadeS* lbl_804CB6DC;

void fn_800C8000(FadeG*, int, int);
void fn_803047B0(int, int, int, int);
void fn_80304814(int, int, int, int);
void fn_80305020(void*, int);
void fn_80303D74();
void fn_803061BC();
void* fn_80081050(void*, int);
void fn_800846BC(void*);
void* fn_80083B84(void*);
void fn_8007E154();
void fn_8007E164();
void fn_8007E174(int, int);
void fn_8007E4E4(f32, f32, f32, f32);
void fn_800800D4(int);
void fn_80080388(f32, f32, f32, f32);
void fn_80080308();
void fn_80083E20(void (*)(void*));
int fn_800893BC(void*);
void fn_800893C4(void*);
void fn_800893D4(void*);
void fn_80079978(void*);
f32 fn_8017F68C(int, f32, f32, f32, f32);
void fn_80021F7C(int, int, int, int);
void fn_80021EF8(int, int);
void fn_80021CB4(int, int, int, int);
void fn_80021E20(int, int, int, int, int);
void fn_80021D18(int, int, int, int, int, int);
void fn_80021E8C(int, int, int, int, int);
void fn_80021D9C(int, int, int, int, int, int);
void fn_80077C08(int);
void fn_800C835C(int a, int b);

BOOL fn_800C8778();

void fn_800C8C3C(int t);

void fn_800C8C90(int t);

void fn_800C8CE4();

BOOL fn_800C8CF4();


struct Holder54 {
    u8 pad[0x54];
    FadeG* m54;
};
void fn_800C8D1C(Holder54* h);

void fn_800C900C(int a, int b);

u32 fn_800C9020();

BOOL fn_800C9030();

BOOL fn_800C9054();

u16 fn_800C9078();

void fn_800C9108();

BOOL fn_800C916C();

BOOL fn_800C919C();


struct BlurP {
    u8 pad[0x28];
    s16 m28;
    u8 pad2a[6];
    u8 m30;
    u8 pad31[3];
    s16 m34;
    u8 pad36[2];
    f32 m38, m3c;
    u8 pad40[8];
    void* m48;
};
void fn_800C9244(void* p);

void fn_800C9280(BlurP* p);

void fn_800C96A8(BlurP* p);

void fn_800C9718();

void fn_800C9770();

void fn_800C97C0();

int fn_800C9D58();

int fn_800C9D60();

void fn_800C9EB8();


} // extern "C"


#pragma use_lmw_stmw off
/* ---- from rG_800A3D88/wip/fn_800C9084.cpp ---- */
extern "C" {
// 13/33: base gets r31, z r30; want reversed.
void fn_800C9084() {
    int z;
    u8* base = lbl_80382930;
    lbl_804CB6D4 = (FadeG*)fn_80081050(base, 8);
    z = 0;
    lbl_804CB6D4->m48 = (void*)z;
    lbl_804CB6D0 = (FadeG*)fn_80081050(base + 0x80, 8);
    lbl_804CB6D8 = (FadeG*)fn_80081050(base + 0x40, 8);
    lbl_804CB6D8->m32 = z;
    lbl_804CB6DC = (FadeS*)fn_80081050(base + 0x58, 8);
    lbl_804CB6DC->m32 = z;
}
}
