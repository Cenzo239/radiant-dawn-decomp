/*
 * fn_8009999C: 5 of 61 words differ, all a swap of r4/r5 (want vtable r4, zero r5). All 120
 * store orders in MemWriterInit were tried, and no order fixes this function while keeping the
 * others. Real C++ classes were much further off. Needs MemStream helpers from
 * ../fn_80098AB8.cpp.
 */
int fn_8009999C(void)
{
    MemStream s;
    u8* buf = (u8*)fn_80079958(0x18000, 0x40);
    lbl_804CB618 = buf;
    MemWriterInit(&s, buf, 0x18000);
    fn_8024C2B4(&s);
    fn_8012D78C();
    fn_8002697C(lbl_803C8E80);
    fn_8012CBF0();
    fn_80114D00(lbl_803EC898);
    fn_80063C30(lbl_803CAB38 + 0x144);
    fn_800660C4(lbl_803CB770);
    if (fn_80060754(lbl_803CAB38) != 0) {
        fn_80105704(fn_801059B0());
    }
    fn_80114D00(lbl_803EC898);
    MemStreamDtor(&s);
    return 1;
}

/*
 * fn_80099F54: 2 of 24 words differ. Want `lbz r0; extsb r31, r0`; ours is `lbz r31; extsb
 * r31, r31`. Five spellings tried. Needs declarations from ../fn_80098AB8.cpp.
 */
int fn_80099F54(void)
{
    u8* sys = fn_8024BC94();
    int v;
    if (fn_802450BC() != 0) {
        v = *(s8*)(sys + 0x1bc9);
        fn_8024BA84(v, fn_8009E898());
    }
    setFlag1C(fn_800C3558());
    return 1;
}

/*
 * fn_8009A3D8: 1 of 15 words differs. Want `fmuls f0, f1, f0`; ours is `fmuls f0, f0, f1` with
 * either operand order, a float temp, or a static const.
 */
int fn_8009A3D8(int frames)
{
    f32 f = frames;
    return f * 16.666666f;
}

