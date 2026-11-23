/* fn_8001EBC8: near miss, 14 of 71 words differ. Depends on types and helpers from ../fn_80016368.c; goes there in address order. */
f32 fn_8001EBC8(f32 a, f32 b, f32 x, f32 y, int n) {
    f32 d = x - y;
    f32 p;
    f32 q;
    int i;
    b = b - a;
    p = x;
    q = d;
    for (i = 1; i < n; i++) {
        q *= d;
        p *= x;
    }
    return a + (b - b * q / p);
}
