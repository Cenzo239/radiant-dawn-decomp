// Near misses, see NOTES.md. Needs declarations from ../fn_800AADBC.cpp.
void fn_800C4DDC(int a, int b, int d, FW* w) {
    fn_800C4EDC(lbl_804CD560, w, a, b, d, 0);
    if (w->m34->m20 & 2) {
        int k = (w->m48 & 0x800) ? 7 : 4;
 fn_800C57B0(lbl_804CD560, w, a, b, d, k, 0);
    }
    if (w->m34->m20 & 1) {
        fn_800C5A34(lbl_804CD560, w, a, b, d, 0, 0, 0);
        fn_800C5A34(lbl_804CD560, w, a, b, d, 1, 0, 0);
    }
}
