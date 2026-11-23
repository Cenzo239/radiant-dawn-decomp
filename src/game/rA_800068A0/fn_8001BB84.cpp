/* fn_8001BB84: curve resampling. The parameter copies only set register rank. */
#include "game/rA_800068A0/types.h"
extern "C" {
extern f32 fn_8001EF30(f32 a, f32 b, f32 c, f32 d);
extern void fn_8001F1D4(void* a, void* b, int n, int seg, int f);
void fn_8001BB84(void* pa, f32* psrc, u8* pal, void* pb, f32* pds, u8* pda, int pn, int pseg) {
/*P*/
    f32* w;
    void* a;
    u8* al;
    u8* da;
    f32* src;
    int n;
    f32* p;
    int i;
    int u;
    int j;
    void* b;
    f32* ds;
    int k;
    u8 a0;
    u8 a1;
    int seg;
/*E*/
    f32 s0;
    f32 s1;
    a = pa; src = psrc; al = pal; b = pb; ds = pds; da = pda; n = pn; seg = pseg;
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
        a0 = al[i];
        a1 = al[i + 1];
        for (j = 1; j < seg; j++) {
            *p = fn_8001EF30(s0, s1, (f32)seg, (f32)j);
            da[k] = (int)fn_8001EF30((f32)a0, (f32)a1, (f32)seg, (f32)j);
            p++;
            k++;
        }
        ds[k] = s1;
        da[k] = a1;
        k++;
        w++;
    }
    fn_8001F1D4(a, b, n, seg, 0);
}
}
