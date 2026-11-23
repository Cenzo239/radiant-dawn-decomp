/* fn_801B0E88 (help window move): 124/138 words; the switch base register is r5 in the original and r7 here,
   and the case 0 x1C load then lands in r31 instead of r5. */
void fn_801B0E88(int v) {
    int x;
    int y;
    const char* s;
    LData* d = lbl_804CB9BC;
    switch (d->x28) {
    case 0:
        x = d->x1C + 0x10;
        y = d->x20 + 0xA + d->x24 * 0x1C;
        break;
    case 1:
        x = d->x1C + 0x78;
        y = d->x20 + 0x22 + (d->x2C - d->x38 / 32) * 32;
        break;
    case 2:
        x = d->x1C + 0xF5;
        y = d->x20 + 0x22 + (d->x2C - d->x38 / 32) * 32;
        break;
    }
    lbl_804CB9BC->x54 = lbl_804CB9BC->x4C;
    lbl_804CB9BC->x58 = lbl_804CB9BC->x50;
    lbl_804CB9BC->x5C = x;
    lbl_804CB9BC->x60 = y;
    lbl_804CB9BC->x48 = 4;
    lbl_804CB9BC->x44 = lbl_804CB9BC->x38;
    lbl_804CB9BC->x34 = v;
    lbl_804CB9BC->x30 = v;
    if (fn_801A2224(lbl_8041EB20) != 0) {
        switch (lbl_804CB9BC->x28) {
        case 0:
            switch (lbl_804CB9BC->x24) {
            case 0:
                s = lbl_8036DCE0 + 0x2E;
                break;
            case 1:
                s = lbl_8036DCE0 + 0x41;
                break;
            case 2:
                s = lbl_8036DCE0 + 0x55;
                break;
            }
            break;
        case 1:
            s = lbl_8036DCE0 + 0x68;
            break;
        case 2:
            s = lbl_8036DCE0 + 0x73;
            break;
        }
        fn_801A1DCC(lbl_8041EB20, fn_800D0864(s), x, y);
    }
}

