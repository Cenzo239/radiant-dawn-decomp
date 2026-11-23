/* Near miss from fn_800CCF84.cpp, same declarations.
 * fn_800CD5F4: 10 words. Only the fn_800620A8 argument block: the lbl_803CAB38 base
 * should be r3 and 0x4330 r4, but they swap with every spelling tried. */
static inline SaveData* XY(SaveData* s) { return s; }
void fn_800CD5F4() {
    ChapReq* r = fn_8024BCA0();
    fn_8023FC0C();
    fn_80150990();
    switch (r->kind) {
    case 0:
        break;
    case 10:
        fn_80060728(&lbl_803CAB38)->kind = 1;
        fn_80061584(&lbl_803CAB38, r->chapter);
        fn_8006132C(&lbl_803CAB38);
    case 4:
    case 9:
        SetState(0xB);
        break;
    case 11:
        fn_80044654();
        fn_80061098();
        fn_8024BCAC();
        SetState(0xE);
        break;
    case 5:
    case 6:
    case 7:
        fn_80044654();
        fn_80061098();
        fn_8024BCAC();
        SetState(0x14);
        break;
    case 1:
    case 12:
        fn_80044654();
        fn_80061098();
        fn_8024BCAC();
        if (fn_801D3FFC() == 0) {
            fn_8012CC80();
            SetState(0x11);
        } else {
            fn_800620A8(lbl_803CAB38.x, lbl_803CAB38.y);
            fn_8012FF30();
            SetState(0x18);
        }
        break;
    case 2:
    case 13:
        fn_80044654();
        fn_80061098();
        fn_8024BCAC();
        SetState(0x19);
        break;
    case 3:
        r->kind = 4;
        fn_8012CBF0();
        SetState(0xB);
        break;
    case 8:
        SetState(0x15);
        break;
    }
    fn_801097FC(fn_80060728(&lbl_803CAB38));
}

