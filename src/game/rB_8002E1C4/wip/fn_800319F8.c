/* fn_800319F8: 8 of 75 words differ when key is a local (same r30/r29 swap as fn_800314CC).
 * Shares the header of fn_80031984.c.
/* "traded item" popup */
void fn_800319F8(Item* it, void* a, BUnit* u)
{
    const char* key = lbl_80361390 + 0x83;
    char buf[0x80];
    switch (fn_8024BC94()->lang) {
    case 1:
        fn_80290D04(buf, 0x80, lbl_80361390 + 0x1c, fn_801110C4(it, 0), fn_80110F08(it), (u8)item_index(it) + 0x80);
        break;
    default:
        fn_80290D04(buf, 0x80, lbl_80361390 + 0x27, (u8)item_index(it) + 0x80, fn_80110F08(it));
        break;
    }
    fn_800D0B38(0, buf);
    fn_801ABBA8(fn_800D08B4(key, fn_8011B77C(u->x12c, lbl_804CA4DC)), 0, a, 0);
}
*/
