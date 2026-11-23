/* fn_80280CB4: li r3,0x24 should come before addi r4,r31,0x72 */
void fn_80280CB4(u8* p) {
    lbl_804CC0AC = p;
    *(void**)(lbl_804CC0AC + 0x30) = fn_80078CCC(0x24, lbl_803738BC + 0x72, 0);
    lbl_804CC0A8 = *(Bars**)(lbl_804CC0AC + 0x30);
    memset(lbl_804CC0A8, 0, 0x24);
    lbl_804CC0A8->mC = 0x22C;
    lbl_804CC0A8->m8 = 0x22C;
    lbl_804CC0A8->m4 = 0x22C;
    lbl_804CC0A8->mE = 0x3F;
    lbl_804CC0A8->mA = 0x3F;
    lbl_804CC0A8->m6 = 0x3F;
    lbl_804CC0A8->m10 = 0;
    lbl_804CC0A8->m12 = 0;
    lbl_804CC0A8->m14 = 0;
    lbl_804CC0A8->m16 = 0;
    lbl_804CC0A8->m2 = -1;
    lbl_804CC0A8->m0 = -1;
    lbl_804CC0A8->m18 = 0;
    lbl_804CC0A8->m1A = 0;
    lbl_804CC0A8->m1C = 0;
    fn_8023F1A0(lbl_803738BC, 0);
}

