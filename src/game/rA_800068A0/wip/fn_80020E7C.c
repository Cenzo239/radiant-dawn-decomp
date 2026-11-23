/* fn_80020E7C: near miss, 4 of 28 words differ. Depends on types and helpers from ../fn_80017D6C.c; goes there in address order. */
void fn_80020E7C(int size) {
    int a = (size + 0x1F) & ~0x1F;
    int n = lbl_804CB0AC;
    n = n + 1;
    lbl_804CB0AC = n;
    if (a > lbl_804CB0B0) {
        if (lbl_804CB0A8 != 0) {
            fn_80079978(lbl_804CB0A8);
        }
        lbl_804CB0B0 = a;
        lbl_804CB0A8 = fn_80079940(a, 0x40);
        DCFlushRange(lbl_804CB0A8, a);
    }
}
