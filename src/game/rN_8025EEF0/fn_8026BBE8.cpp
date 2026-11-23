/* Title intro: press-start screen setup */
#include "game/rN_8025EEF0/types.h"
#include "game/rN_8025EEF0/calls.h"

struct Wf { u8 pad0[8]; s16 m8; u8 padA[6]; u8 m10; u8 pad11[7]; u32 m18; };
struct Obj { u8 pad[0x30]; Wf* m30; };
struct TitleProc {
    u8 pad0[0x28];
    s16 m28;
    u8 pad2A[6];
    Obj* m30;
    Obj* m34;
    Obj* m38;
    Obj* m3C[4];
    void* m4C;
    int m50;
    u8 m54;
    u8 m55;
};
struct NameTbl { const char* n[4]; };
struct TexInfo { u8 obj[0x20]; u16 w; u16 h; };

extern "C" {

void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E174(void* a, int b);
void fn_8007E4E4(f32 x, f32 y, f32 z, f32 s);
void fn_800800D4(int t);
void fn_80080388(f32 x, f32 y, f32 w, f32 h);
void fn_80080308(void);
void fn_80006A64(void* a, void* b, int c);
u16 fn_80305DF8(void* t);
u16 fn_80305E0C(void* t);
int fn_8007A85C(int a);
void fn_80253EE4(const char* s, f32 v);
void fn_80250D64(int a, f32 b, f32 c);
void fn_800C835C(int a, int b);
void fn_800068A0(void* a, const char* b);
Obj* fn_800E3810(void* a, void* b);
Obj* fn_800E3C04(const char* a, void* b);
void fn_800E48AC(Obj* a, f32 x, f32 y, f32 z);
int fn_802457BC(u8* s);
int fn_80089ED0(void);
void* fn_800D4188(void* s, void* p);
s8 fn_8024F7EC(void* s);
void fn_80251838(int a, void* b, f32 c);
extern char lbl_803922C4[];
extern char lbl_803922B8[];
extern char lbl_803922AC[];
extern char lbl_803922A0[];
extern char lbl_80392288[];
extern char lbl_80392270[];
extern char lbl_80392254[];
extern char lbl_80392240[];
extern char lbl_80392228[];
extern char lbl_80392214[];
extern char lbl_80392208[];
extern char lbl_803921FC[];
extern const char* lbl_80391FA0[][2];
extern const char* lbl_80373268[4];

void fn_8026BBE8(TitleProc* p) {
    
    int zero;
    int i;
    int dur;
    const char** np;
    Obj** op;
    Obj* u;
    const char* names[4];
    
    {
        s8 lang = fn_8024BC94()[0x1BC8];
        fn_800068A0(&p->m4C, lbl_80391FA0[lang][fn_801D09F0()]);
    }
    zero = 0;
    p->m50 = zero;
    p->m54 = zero;
    p->m55 = zero;
    p->m30 = fn_800E3810(lbl_803922B8, p);
    p->m30->m30->m8 = 0x64;
    p->m30->m30->m18 |= 4;
    p->m30->m30->m18 &= ~0x8000;
    p->m34 = fn_800E3810(lbl_803922AC, p);
    p->m34->m30->m8 = 0x63;
    p->m34->m30->m18 |= 4;
    p->m34->m30->m18 &= ~0x8000;
    p->m38 = fn_800E3810(lbl_803922A0, p);
    p->m38->m30->m8 = 0x5A;
    p->m38->m30->m18 &= ~0x8000;
    *(NameTbl*)names = *(NameTbl*)lbl_80373268;
    dur = 200;
    for (i = 0; i < 4; i++) {
        u = fn_800E3C04(names[i], p);
        p->m3C[i] = u;
        fn_800E48AC(u, 304.0f, 367.0f, 0.0f);
        u->m30->m8 = dur;
        u->m30->m10 = zero;
        u->m30->m18 |= 4;
        u->m30->m18 &= ~0x8000;
    }
    {
        char* s;
        if (fn_802457BC(fn_8024BC94()) >= 1) {
            if (fn_80089ED0() & 1) {
                s = fn_801D09F0() != 0 ? lbl_80392288 : lbl_80392270;
            } else {
                s = fn_801D09F0() != 0 ? lbl_80392254 : lbl_80392240;
            }
        } else {
            s = fn_801D09F0() != 0 ? lbl_80392228 : lbl_80392214;
        }
        fn_800D4188(s, p);
    }
    if (fn_8024F7EC(lbl_80392208) < 0) {
        fn_80251838(3, lbl_803921FC, 0.0f);
    }
    p->m28 = 0x438;
    fn_800CD4A4(0x30);
}

}
