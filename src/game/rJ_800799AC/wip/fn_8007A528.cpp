/* Near miss (fragment, needs fn_8007A528.cpp's declarations). 9 of 100 words: the
 * base should be r28 and the induction pointer r26, made with "addi r26, r28, 0"
 * rather than "mr". fn_8007A734 is the same loop and does match. */
void fn_8007A528(void) {
    Pad* p;
    PadData* d = &lbl_803D7918;
    int i;
    fn_80323064();
    memset(d->status, 0, 0x30);
    SISetSamplingRate(1);
    fn_8032FAD0();
    fn_80335A94(fn_8007A4FC, fn_8007A504);
    fn_8030D310();
    memset(d->data, 0, 0x2100);
    for (i = 0; i < 4; i++) {
        if (d->pads[i] != 0) {
            if (d->pads[i] != 0) {
                d->pads[i]->v08(1);
            }
        }
        p = (Pad*)fn_80079940(0x5C, 0x40);
        if (p != 0) {
            *(void***)p = lbl_80380E14;
            p->f4 = 4;
            p->f8 = 4;
            p->v0C(i);
            *(void***)p = lbl_80380D28;
            p->vD0(4);
            p->vD4(p->v14());
            fn_8030D66C(i);
            fn_8030AAF4(i);
        }
        d->pads[i] = p;
    }
    if (fn_80337348() != 0) {
        lbl_804CB5BC |= 2;
    }
    lbl_804CB5BC |= 1;
    lbl_804CB5B8 = d->pads[0];
}

