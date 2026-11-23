/* fn_8001ECE4: near miss, 2 of 69 words differ. Depends on types and helpers from ../fn_80016368.c; goes there in address order. */
f32 fn_8001ECE4(f32 a, f32 b, f32 x, f32 y, int n) {
    f32 d = b - a;
    f32 q = y;
    f32 p;
    int i = 1;
    p = x;
    for (; i < n; i++) {
        q *= y;
        p *= x;
    }
    return a + d * q / p;
}
