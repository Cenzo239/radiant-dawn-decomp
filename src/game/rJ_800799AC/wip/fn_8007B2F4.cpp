/* Near misses (fragments, need fn_8007B2F4.cpp's declarations). 10 of 97 words.
 * The original computes &lbl_803D7918 before the call to fn_8007A868 and then
 * "addi r30, r31, 0": an induction variable pads[i] made from a base kept in a
 * register. Indexing gets the rest right, but here the base is only materialised
 * after the call.
 */
#pragma use_lmw_stmw on
void fn_8007B2F4(void) {
    PadData* base = &lbl_803D7918;
    int i;
    Pad* p;
    fn_8007A868();
    for (i = 0; i < 4; i++) {
        p = base->pads[i];
        if (p->v14() != 4) {
            switch (p->vB4()) {
            case 0:
                switch (p->v14()) {
                case 0:
                case 1:
                case 2:
                    p->vC4(base->data[i], base->status[i]);
                    break;
                case 3:
                    p->vC4(base->data[i], base->status[i]);
                    break;
                }
                break;
            case -1:
                p->vB8();
                break;
            default:
                p->vC0();
                break;
            }
            p->vC8();
            p->vCC();
        }
    }
}

void fn_8007B458(void) {
    PadData* base = &lbl_803D7918;
    int i;
    Pad* p;
    fn_8007A868();
    for (i = 0; i < 4; i++) {
        p = base->pads[i];
        if (p->v14() != 4) {
            switch (p->vB4()) {
            case 0:
                switch (p->v14()) {
                case 0:
                case 1:
                case 2:
                    p->vC4(base->data[i], base->status[i]);
                    break;
                case 3:
                    p->vC4(base->data[i], base->status[i]);
                    break;
                }
                break;
            case -1:
                p->vB8();
                break;
            default:
                p->vC0();
                break;
            }
        }
    }
}
#pragma use_lmw_stmw off

