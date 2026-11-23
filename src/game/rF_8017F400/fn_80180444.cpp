#include "game/rF_8017F400/types.h"

extern "C" {

/* bubble sort keys/vals by key */
void fn_80180444(Track* p)
{
    int i, j;
    s32 tk;

    for (i = 0; i < p->count; i++) {
        for (j = 0; j < p->count - i - 1; j++) {
            if (p->keys[j] > p->keys[j + 1]) {
                tk = p->keys[j];
                p->keys[j] = p->keys[j + 1];
                p->keys[j + 1] = tk;
                Vec tv = p->vals[j];
                p->vals[j] = p->vals[j + 1];
                p->vals[j + 1] = tv;
            }
        }
    }
}

void fn_801804F8(Track* p, s32 key, const Vec& val)
{
    p->vals[p->count] = val;
    p->keys[p->count] = key;
    p->count++;
    fn_80180444(p);
    p->unk18 = p->keys[p->count - 1];
}

void fn_80180598(Track* p, s32 x)
{
    p->unk14 = p->unk10;
    p->unk18 = x;
    p->unk1C = 0.0f;
}

void fn_801805D4(Track* p)
{
    p->unk6 = 1;
}

} /* extern "C" */
