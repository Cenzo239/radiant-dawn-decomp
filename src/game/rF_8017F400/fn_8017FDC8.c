#include "game/rF_8017F400/types.h"

extern u8 lbl_804CA7D0, lbl_804CA7D1, lbl_804CA7D2, lbl_804CA7D3; /* default colour */


/* Track ctor */
void fn_8017FDC8(Track* p)
{
    GXColor c;
    p->count = 0;
    p->unkA = 0;
    p->unkC = 0.0f;
    p->unk10 = 0.0f;
    p->unk14 = 0.0f;
    p->unk18 = 0.0f;
    p->unk1C = 0.0f;
    p->unk4 = 0;
    p->unk6 = 0;
    c.r = lbl_804CA7D0;
    c.g = lbl_804CA7D1;
    c.b = lbl_804CA7D2;
    c.a = lbl_804CA7D3;
    p->color = c;
}
