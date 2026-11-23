/* fn_801AF104 (title bars and caption): 103/105 words. Only "lwz r0; extsh r3,r0" versus the original
   "lwz r3; extsh r3,r3" on the x argument differs. */
void fn_801AF104(PData* d) {
    int b = 0x4A;
    int a = 0x12;
    fn_801BCA5C(-1.0f);
    fn_8007E154();
    fn_8007E374(d->x10, 1, 0x11);
    fn_8007E164();
    fn_800800D4(1);
    fn_80080348(304.0f, a, 0.0f, 0.0f);
    fn_80080368(608.0f, b, 304.0f, 56.0f);
    fn_80080578(0);
    fn_80080308();
    fn_800800D4(1);
    fn_80080348(0.0f, a, 304.0f, 0.0f);
    fn_80080368(304.0f, b, 0.0f, 56.0f);
    fn_80080578(0);
    fn_80080308();
    fn_801BCA5C(-1.0f);
    fn_801BCA94();
    {
        const char* t = fn_800D0864(lbl_8036D68C + 0x1BD);
        f32 w = fn_800CA3DC(t, -1, 1.2f);
        s16 x = 304.0f - 0.5f * w;
        fn_800CB3A8(1.2f, 0.0f, x, 0x1E, 2, 0, 0, t);
    }
    fn_801BCA5C(2.0f);
}

