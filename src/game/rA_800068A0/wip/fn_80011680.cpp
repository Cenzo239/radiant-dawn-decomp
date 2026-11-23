/* fn_80011680 (GLight_InitAll): about 70 of 110 words differ. Goes in
 * fn_8000F48C.cpp after fn_80011280. fn_80010CA4 is inlined (and unrolled by
 * 2) as in the original, but the inlined stack slots come out as
 * {c, amb, p, d} instead of {amb, c, d, p}, and the set pointer / light
 * pointer registers (r29/r30) are swapped. */
/* GLight_InitAll */
void fn_80011680(void) {
    int i;
    for (i = 0; i < 8; i++) {
        fn_80010CA4(&lbl_803B6710[i]);
    }
    lbl_804CA050 = lbl_803B6710;
}
