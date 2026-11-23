/* fn_8002421C: near miss, 53 of 109 words differ. Depends on types and helpers from ../fn_800235B8.cpp; goes there in address order. */
void fn_8002421C(Mnu* p) {
    switch (((u8*)lbl_803CA870)[0xC]) {
    case 0x81:
        fn_80083DC4(p, 0xB);
        break;
    default:
        fn_800893AC(p->p50);
        mnuAdd(p);
        fn_800231E4();
        fn_80083B78(p);
        break;
    }
}
