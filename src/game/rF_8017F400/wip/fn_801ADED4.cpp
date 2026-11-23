/* near miss: fn_801AF2A8 59 words. v wants r30, then the pool base r29 and table base r28 in the first branch. Declarations in ../fn_801ADED4.cpp */
void fn_801AF2A8(TrD* d, f32 x, f32 y) {
/*P*/
    const char* s;
    int v;
/*E*/
    u32 h, m, sec;
    fn_8017FA84(d->tlo, d->thi, &h, &m, &sec);
    if (h > 0x63) { h = 0x63; m = 0x3B; sec = 0x3B; }
    fn_801BCA5C(-1.0f);
    TI0(d, x, y);
    fn_801BCA5C(-1.0f);
    fn_801BCA94();
    if (*(s8*)(fn_8024BC94() + 0x1BC8) == 0) {
        T1(1, 1.0f, 96.0f + x, 48.0f + y, fn_800D0864("MTM_TRI_RES_COMP_TURN"));
        fn_800CB3A8(1.2f, 0.0f, 216.0f + x, 44.0f + y, 6, 1, 0, "%d", *(s16*)(lbl_803CAB38 + 0x12));
        T1(1, 1.0f, 248.0f + x, 48.0f + y, fn_800D0864("MTM_TRI_RES_TURN"));
        fn_800CB3A8(1.0f, 0.0f, 94.0f + x, 80.0f + y, 1, 1, 0, "#C01%s  #C06%02d\x81""F%02d\x81""F%02d", fn_800D0864("MTM_TRI_RES_PLAYTIME"), h, m, sec);
        T1(1, 1.0f, 94.0f + x, 112.0f + y, fn_800D0864("MTM_TRI_RES_TACT_RANK"));
        fn_800CB3A8(1.2f, 0.0f, 182.0f + x, 108.0f + y, 6, 1, 0, "%c", (u8)fn_800634D8(lbl_803CAB38));
        T1(1, 1.0f, 254.0f + x, 112.0f + y, fn_800D0864("MTM_TRI_RES_ALIVE_RANK"));
        fn_800CB3A8(1.2f, 0.0f, 342.0f + x, 108.0f + y, 6, 1, 0, "%c", (u8)fn_80063568(lbl_803CAB38));
        T1(1, 1.0f, 94.0f + x, 144.0f + y, fn_800D0864("MTM_TRI_RES_BTL_RANK"));
        fn_800CB3A8(1.2f, 0.0f, 182.0f + x, 140.0f + y, 6, 1, 0, "%c", (u8)fn_80063620(lbl_803CAB38));
        T1(0x19, 1.2f, 294.0f + x, 184.0f + y, fn_800D0864("MTM_TRI_RES_TOTAL_RANK"));
        fn_800CB3A8(1.2f, 0.0f, 406.0f + x, 184.0f + y, 6, 1, 0, "%c", (u8)fn_8006376C(lbl_803CAB38));
    } else {
        T1(1, 1.0f, 96.0f + x, 48.0f + y, fn_800D0864("MTM_TRI_RES_COMP_TURN"));
        fn_800CB3A8(1.2f, 0.0f, 216.0f + x, 44.0f + y, 6, 1, 0, "%d", *(s16*)(lbl_803CAB38 + 0x12));
        fn_800CB3A8(1.0f, 0.0f, 94.0f + x, 80.0f + y, 1, 1, 0, "#C01%s   #C06%02d\x81""F%02d\x81""F%02d", fn_800D0864("MTM_TRI_RES_PLAYTIME"), h, m, sec);
        T1(1, 1.0f, 94.0f + x, 112.0f + y, fn_800D0864("MTM_TRI_RES_TACT_RANK"));
        v = (u8)fn_800634D8(lbl_803CAB38);
        Rate("MTM_TRI_RES_TACT_RANK", v, 94.0f + x, 108.0f + y);
        T1(1, 1.0f, 254.0f + x, 112.0f + y, fn_800D0864("MTM_TRI_RES_ALIVE_RANK"));
        v = (u8)fn_80063568(lbl_803CAB38);
        Rate("MTM_TRI_RES_ALIVE_RANK", v, 254.0f + x, 108.0f + y);
        T1(1, 1.0f, 94.0f + x, 144.0f + y, fn_800D0864("MTM_TRI_RES_BTL_RANK"));
        v = (u8)fn_80063620(lbl_803CAB38);
        Rate("MTM_TRI_RES_BTL_RANK", v, 94.0f + x, 140.0f + y);
        T1(0x19, 1.2f, 294.0f + x, 184.0f + y, fn_800D0864("MTM_TRI_RES_TOTAL_RANK"));
        v = (u8)fn_8006376C(lbl_803CAB38);
        Rate("MTM_TRI_RES_TOTAL_RANK", v, 294.0f + x, 184.0f + y);
    }
    fn_801BCA5C(-2.0f);
    fn_801BCA5C(-1.0f);
    fn_801BCA94();
    switch (lbl_803CAB38[0x10]) {
    case 0x5B: s = fn_800D0864("MTM_TRI_MAP1"); break;
    case 0x5C: s = fn_800D0864("MTM_TRI_MAP2"); break;
    case 0x5D: s = fn_800D0864("MTM_TRI_MAP3"); break;
    case 0x5E: s = fn_800D0864("MTM_TRI_MAP4"); break;
    case 0x5F: s = fn_800D0864("MTM_TRI_MAP5"); break;
    case 0x60: s = fn_800D0864("MTM_TRI_MAP6"); break;
    }
    fn_800CB3A8(1.0f, 0.0f, 240.0f + x - (s16)fn_800CA3DC(s, -1, 1.0f) / 2, y - 12.0f, 1, 1, 0, s);
    fn_801BCA5C(5.0f);
}
