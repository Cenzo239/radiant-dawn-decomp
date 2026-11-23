/* Title intro: press-start screen and its setup */
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

void fn_8026B96C(TitleProc* p) {
    TexInfo t;
    p->m50++;
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 200.0f, 1.0f);
    fn_8007E164();
    fn_80006A64(p->m4C, t.obj, 0);
    t.w = fn_80305DF8(t.obj);
    t.h = fn_80305E0C(t.obj);
    fn_8007E154();
    fn_8007E174(t.obj, 0x10);
    fn_8007E164();
    fn_800800D4(1);
    fn_80080388(152.0f, 394.0f, t.w, t.h);
    fn_80080308();
    if ((s8)p->m54 != 0 && (p->m50 & 4)) {
        return;
    }
    p->m3C[0]->m30->m10 = 0;
    p->m3C[1]->m30->m10 = 0;
    p->m3C[2]->m30->m10 = 0;
    p->m3C[3]->m30->m10 = 0;
    switch (lbl_804CB5B8->v18()) {
    case 0:
    case 1:
        if (fn_8007A85C(1) != 0) {
            p->m3C[1]->m30->m10 = 0xFF;
        } else {
            p->m3C[0]->m30->m10 = 0xFF;
        }
        break;
    case 3:
        p->m3C[3]->m30->m10 = 0xFF;
        break;
    case 2:
    case 4:
    case 5:
        p->m3C[2]->m30->m10 = 0xFF;
        break;
    }
    if (p->m55 == 0 && (lbl_804CB5B8->v48() & 0x4400)) {
        if (lbl_804CB5B8->v34() != lbl_804CB5B8->v20()) {
            fn_80253EE4(lbl_803922C4, 0.0f);
            fn_80250D64(6, 0.5f, 500.0f);
            p->m55 = 1;
            if (p->m28 <= 0) {
                fn_800C835C(0, 0);
            }
            fn_800CD4A4(7);
            p->m54 = 1;
            fn_80083DC4(p, 0);
        }
    }
}

}
