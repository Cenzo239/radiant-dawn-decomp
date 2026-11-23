/* Near misses from fn_800799AC.cpp (fragments, need its declarations).
 * fn_80079D90: only the epilogue order differs (lwz r0 before lwz r31).
 * fn_8007A1CC: base register should be r6, then reused for the 0 argument;
 * here the base goes to r8.
 */
void fn_80079D90(int) {
    lbl_803CD8E0.result = fn_802F1C8C(lbl_803CD8E0.fd);
    lbl_803CD8E0.busy = 0;
}

void fn_8007A1CC(Proc* p) {
    if (checkError(p)) {
        return;
    }
    lbl_803CD8E0.result = fn_80079BE4(lbl_803CD8E0.fd, lbl_80362390 + 8, lbl_803CD8E0.cmdBlock);
    switch (lbl_803CD8E0.result) {
    case -4:
        fn_80081A90(p);
        break;
    default:
        lbl_803CD8E0.dirOpen = 1;
        lbl_803CD8E0.busy = 1;
        lbl_803CD8E0.result = fn_802F531C(lbl_803CD8E0.cmdBlock, lbl_803CD8E0.data, 0x26000, 0, fn_80079D90);
        if (lbl_803CD8E0.result < 0) {
            fn_80083DC4(p, 0x63);
            lbl_803CD8E0.busy = 0;
        }
        break;
    }
}

