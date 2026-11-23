/* fn_80263418: 6 words. ofs of the first two loops should be r27 (r29 here). */
static inline void dictDraw1(void) {
    int ofs;
    int i;

    i = 0;
    ofs = 0;
    for (; i < *lbl_804306E8.cnt1; ofs += 0x14, i++) {
        fn_802652DC((u8*)lbl_804306E8.t1 + ofs, lbl_804CC008->m6C[i]);
    }
}
static inline void dictDraw2(void) {
    int i;
    int ofs;

    i = 0;
    ofs = 0;
    for (; i < *lbl_804306E8.cnt2; ofs += 0x18, i++) {
        u8* e = (u8*)lbl_804306E8.t2 + ofs;
        if (lbl_804CC008->m70[i] != 0) {
            fn_80265574(e);
        }
    }
}
static inline void dictDraw3(void) {
    int ofs;
    int ofs2;
    int i;

    i = 0;
    ofs2 = 0;
    ofs = 0;
    for (; i < *lbl_804306E8.cnt3; ofs2 += 0x10, ofs += 8, i++) {
        fn_80265840((u8*)lbl_80430710.tbl3 + ofs, (u8*)lbl_804306E8.t3 + ofs2, lbl_804CC008->m74[i]);
    }
}

#pragma push
#pragma use_lmw_stmw off
void fn_80263418(void) {
    lbl_804CC008->f54 = -lbl_804CC008->m44 * lbl_804CC008->f64;
    lbl_804CC008->f58 = -lbl_804CC008->m46 * lbl_804CC008->f68;
    fn_8007E154();
    fn_8007E5C0(lbl_804CC008->f54, lbl_804CC008->f58, 50.0f, 0.0f, 0.0f, lbl_804CC008->f5C, lbl_804CC008->f60, 0.0f);
    fn_8007E7DC(0xFF);
    fn_8007E164();
    fn_80266024();
    dictDraw1();
    dictDraw2();
    dictDraw3();
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 50.0f, 1.0f);
    fn_8007E164();
    fn_8026654C();
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 18.0f, 1.0f);
    fn_8007E164();
    fn_8026697C();
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 15.0f, 1.0f);
    fn_8007E164();
    fn_802662EC();
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 10.0f, 1.0f);
    fn_8007E164();
    fn_800712E8((int)(lbl_804CC008->m2A * lbl_804CC008->f5C - lbl_804CC008->m44 * lbl_804CC008->f64),
                (int)-(8.0f * (1.0f - lbl_804CC008->f68) - (lbl_804CC008->m2C * lbl_804CC008->f60 - lbl_804CC008->m46 * lbl_804CC008->f68)),
                1);
}
#pragma pop

