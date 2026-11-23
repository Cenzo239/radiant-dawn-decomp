/* fn_8001BB84: near miss, 22 of 108 words differ, registers only: the alpha walker q must take r16 so the parameters stay at r17..r23. A dead (f32)seg conversion before the loop is needed for the temp slots. */
#include "game/rA_800068A0/types.h"
extern "C" {
extern f32 fn_8001EF30(f32 a, f32 b, f32 c, f32 d);
extern void fn_8001F1D4(void* a, void* b, int n, int seg, int f);
void fn_8001BB84(void* a, f32* src, u8* al, void* b, f32* ds, u8* da, int n, int seg) {

    f32* w;
    f32* p;
    int i;
    int j;
    int u;
    int k;
    u8 a0;
    u8 a1;
    f32 s0;
    f32 s1;

    w = src;
    ds[0] = w[0];
    da[0] = al[0];
    i = 0;
    k = 1;
    u = (f32)seg;
    for (; i < n - 1; i++) {
        s0 = w[0];
        s1 = w[1];
        p = ds + k;
        u8* q = da + k;
        a0 = al[i];
        a1 = al[i + 1];
        for (j = 1; j < seg; j++) {
            *p = fn_8001EF30(s0, s1, (f32)seg, (f32)j);
            *q = (int)fn_8001EF30((f32)a0, (f32)a1, (f32)seg, (f32)j);
            p++;
            k++;
            q++;
        }
        w++;
        ds[k] = s1;
        da[k] = a1;
        k++;
    }
    fn_8001F1D4(a, b, n, seg, 0);
}
}
