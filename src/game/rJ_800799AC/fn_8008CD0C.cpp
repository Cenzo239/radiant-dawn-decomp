/* video.cpp: screen adjust menu setup. Names guessed. */
#include "game/rJ_800799AC/types.h"

struct RenderMode {
    u8 pad0[0xA];
    s16 viXOrigin;   /* 0x0A */
    s16 viYOrigin;   /* 0x0C */
    u8 pad[0x32 - 0xE];
    u8 vfilter[7];   /* 0x32 */
};
struct AdjProc {
    u8 pad[0x30];
    void* img;      /* 0x30 */
    u8 dirty;       /* 0x34 */
    void* arrow[3]; /* 0x38 */
};
struct G1BC8 { u8 pad[0x1BC8]; s8 lang; };

extern "C" {
extern s16 lbl_804CA3D0;
extern s16 lbl_804CA3D2;
extern u8 lbl_804CA3D4;
extern const char* lbl_80381300[][2];
RenderMode* fn_802356AC(void);
int fn_801D09F0(void);
G1BC8* fn_8024BC94(void);
void fn_800068A0(void**, const char*);
void* fn_80078CCC(int, const char*, int);
void* fn_8017948C(void*, int);
void fn_801791D8(void*, int);
void fn_801791D0(void*, f32);

void fn_8008CD0C(AdjProc* p) {
    int i;
    RenderMode* rm = fn_802356AC();
    if (lbl_804CA3D0 < 0 || lbl_804CA3D2 < 0) {
        lbl_804CA3D0 = rm->viXOrigin;
        lbl_804CA3D2 = rm->viYOrigin;
        lbl_804CA3D4 = 0;
        for (i = 0; i < 7; i++) {
            lbl_804CA3D4 += rm->vfilter[i];
        }
        p->dirty = 0;
    }
    {
        int wide = fn_801D09F0();
        fn_800068A0(&p->img, lbl_80381300[fn_8024BC94()->lang][wide]);
    }
    for (i = 0; i < 3; i++) {
        void* m = fn_80078CCC(100, "", 0);
        if (m) {
            m = fn_8017948C(m, 2);
        }
        p->arrow[i] = m;
        fn_801791D8(m, 2);
        fn_801791D0(p->arrow[i], 5.0f);
    }
}
}
