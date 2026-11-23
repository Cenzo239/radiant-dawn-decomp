/* fn_801D65EC: 14 of 190 words differ */
void fn_801D65EC(int x, int y, int fl, Rect* src, const Color* g, int flip) {
    fn_8007E154();
    fn_8007E174(0, fl | 2);
    fn_8007E164();
    Color c0 = g[0];
    Color c1 = g[1];
    Color c2 = g[2];
    Color c3 = g[3];
    fn_800800D4(3);
    fn_80080388(x, y, (s16)(src->x1 - src->x0), (s16)(src->y1 - src->y0));
    if (flip & 1) {
        fn_80080494();
        Swap(c0, c1);
    }
    if (flip & 2) {
        fn_800804B4();
        Swap(c2, c3);
    }
    fn_80080578(0);
    if (flip & 0x100) fn_80080690();
    if (flip & 0x200) fn_800806E0();
    fn_80080940(c0, c1, c2, c3);
    fn_80080308();
}

