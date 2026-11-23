#include "game/rE_800E5DE4/evproc.h"

/* Separate file: fn_800EA810 must not be visible for auto-inlining. */
void* fn_800EDB70(void* parent) {
    if (*(u32*)(lbl_803C8E80 + 0x15EC) & 0x200) {
        return fn_800EA810(parent);
    }
    return fn_80081194(lbl_80384B90, parent);
}

int fn_800EDB98(MsgProc* m, s32* v) {
    if (*v >= m->width) {
        *v = m->width - 1;
    }
    return 0;
}

void fn_800EDBB8(MsgProc* m) {
    Vec s;
    fn_80011B90(0, &m->pos, &s);
    fn_8007E154();
    fn_8007E4E4(s.x, s.y + m->offY, m->width, lbl_804CD9B8);
    fn_8007E374(m->font, 0x1C, 0x11);
    fn_8007E7DC(m->alpha);
    fn_8007E164();
    fn_800800D4(1);
    fn_80080430(lbl_804CD9BC, lbl_804CD9C0, lbl_804CD9C0, lbl_804CD9C0, lbl_804CD9C4, lbl_804CD9C8);
    fn_80080578(0);
    fn_80080308();
    fn_8007E7F4();
}

void fn_800EDC80(MsgProc* m) {
    m->timer = 0;
    m->alpha = 0xFF;
    m->font = fn_8001D3B4(lbl_80367458);
    fn_80177284(fn_800EDBB8, m);
}

void fn_800EDCD8(MsgProc* m) {
    fn_8001D424(m->font);
}

/* Bounce-in: offY follows a parabola over 8 frames. */
void fn_800EDCE0(MsgProc* m) {
    f32 k = 4.0f;
    f32 r;
    m->timer++;
    r = fn_8001EBC8(2, 0.0f, 2.0f * k, 8.0f, m->timer);
    m->offY = (r - k) * (r - k) - k * k;
    if (m->timer >= 8) {
        m->timer = 0;
        fn_80083B78(m);
    }
}

/* Fade: alpha 255 -> 0 over 12 frames. */
void fn_800EDD88(MsgProc* m) {
    m->timer++;
    m->alpha = fn_8001EF30(255.0f, 0.0f, 12.0f, m->timer);
    if (m->timer >= 0xC) {
        m->timer = 0;
        fn_80083B78(m);
    }
}

void fn_800EDE14(Vec* pos, void* parent) {
    s32 w = 500;
    s32 width;
    MsgProc* m;
    fn_800893E4(lbl_80384E00, fn_800EDB98, &w);
    width = w;
    m = fn_80081050(lbl_80384E00, parent);
    MsgProc_SetPos(m, *pos);
    m->width = width;
    m->unk58 = 0;
    m->unk60 = 0;
}

void fn_800EDEC8(
#if TARGET_PC
fe10_vec3 posv, void* parent
#else
Vec* pos, void* parent
#endif
) {
#if TARGET_PC
    Vec* pos = (Vec*)&posv;
#endif
    s32 w = 500;
    s32 width;
    MsgProc* m;
    fn_800893E4(lbl_80384E00, fn_800EDB98, &w);
    width = w;
    m = (MsgProc*)fn_80081194(lbl_80384E00, parent);
    MsgProc_SetPos(m, *pos);
    m->width = width;
    m->unk58 = 0;
    m->unk60 = 0;
}

void fn_800EDF7C(MsgProc* m) {
    Vec s;
    fn_80011B90(0, &m->pos, &s);
    fn_8007E154();
    fn_8007E4E4(s.x + m->offY, s.y, m->width, lbl_804CD9B8);
    fn_8007E374(m->font, 0x1D, 0x11);
    fn_8007E7DC(m->alpha);
    fn_8007E164();
    fn_800800D4(1);
    fn_80080430(lbl_804CD9EC, lbl_804CD9C0, lbl_804CD9C0, lbl_804CD9C0, lbl_804CD9F0, lbl_804CD9C8);
    fn_80080578(0);
    fn_80080308();
    fn_8007E7F4();
}

void fn_800EE044(MsgProc* m) {
    m->timer = 0;
    m->alpha = 0xFF;
    m->font = fn_8001D3B4(lbl_80367458);
    m->offY = -32.0f; /* lbl_804CD9F4 */
    fn_80177284(fn_800EDF7C, m);
}

void fn_800EE0A4(MsgProc* m) {
    fn_8001D424(m->font);
}

void fn_800EE0AC(MsgProc* m) {
    m->timer++;
    m->offY = fn_8001EBC8(2, -32.0f, 0.0f, 8.0f, m->timer);
    if (m->timer >= 8) {
        m->timer = 0;
        fn_80083B78(m);
    }
}

void fn_800EE130(MsgProc* m) {
    m->timer++;
    m->alpha = fn_8001EF30(255.0f, 0.0f, 12.0f, m->timer);
    if (m->timer >= 0xC) {
        m->timer = 0;
        fn_80083B78(m);
    }
}

void fn_800EE1BC(
#if TARGET_PC
fe10_vec3 posv, void* parent
#else
Vec* pos, void* parent
#endif
) {
#if TARGET_PC
    Vec* pos = (Vec*)&posv;
#endif
    s32 w = 500;
    s32 width;
    MsgProc* m;
    fn_800893E4(lbl_80384E44, fn_800EDB98, &w);
    width = w;
    m = fn_80081050(lbl_80384E44, parent);
    MsgProc_SetPos(m, *pos);
    m->width = width;
    m->unk58 = 0;
    m->unk60 = 0;
}

void fn_800EE270(Vec pos, void* parent) {
    s32 w = 500;
    s32 width;
    MsgProc* m;
    fn_800893E4(lbl_80384E44, fn_800EDB98, &w);
    width = w;
    m = (MsgProc*)fn_80081194(lbl_80384E44, parent);
    MsgProc_SetPos(m, pos);
    m->width = width;
    m->unk58 = 0;
    m->unk60 = 0;
}

void fn_800EE48C(MsgProc* m) {
    m->timer = 0;
    m->offY = 0.0f;
    m->alpha = 0;
    m->font = fn_8001D3B4(lbl_80367458);
    fn_80177284(fn_800EE324, m);
}

void fn_800EE4E8(MsgProc* m) {
    fn_8001D424(m->font);
}

void fn_800EE4F0(MsgProc* m) {
    m->timer++;
    m->offY = -fn_8001EF44(0xC, m->timer, 0.0f, 20.0f);
    m->alpha = fn_8001EF30(0.0f, 255.0f, 12.0f, m->timer);
    if (m->timer >= 0xC) {
        m->timer = 0;
        fn_80083B78(m);
    }
}

void fn_800EE598(MsgProc* m) {
    m->timer++;
    m->alpha = fn_8001EF30(255.0f, 0.0f, 16.0f, m->timer);
    if (m->timer == 0x10) {
        fn_80083B78(m);
    }
}

void fn_800EE61C(
#if TARGET_PC
const Vec* posp, int n, void* parent
#else
Vec pos, int n, void* parent
#endif
) {
#if TARGET_PC
    Vec pos = *posp;
#endif
    s32 w;
    s32 width;
    MsgProc* m;
    if (n) {
        w = 500;
        fn_800893E4(lbl_80384E88, fn_800EDB98, &w);
        width = w;
        m = fn_80081050(lbl_80384E88, parent);
        MsgProc_SetPos(m, pos);
        m->width = width;
        m->unk58 = n;
        m->unk60 = 0;
    }
}

void fn_800EE6CC(Vec pos, int n, void* parent) {
    s32 w;
    s32 width;
    MsgProc* m;
    if (n) {
        w = 500;
        fn_800893E4(lbl_80384E88, fn_800EDB98, &w);
        width = w;
        m = (MsgProc*)fn_80081194(lbl_80384E88, parent);
        MsgProc_SetPos(m, pos);
        m->width = width;
        m->unk58 = n;
        m->unk60 = 0;
    }
}

void fn_800EE77C(void) {
    fn_8023F1A0(lbl_80367458, 0);
}

void fn_800EE78C(void) {
    fn_8023F880(lbl_80367458);
}
