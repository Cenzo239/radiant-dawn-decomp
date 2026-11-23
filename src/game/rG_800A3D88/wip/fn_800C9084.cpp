// 13/33: base gets r31, z r30; want reversed.
void fn_800C9084() {
    int z;
    u8* base = lbl_80382930;
    lbl_804CB6D4 = (FadeG*)fn_80081050(base, 8);
    z = 0;
    lbl_804CB6D4->m48 = (void*)z;
    lbl_804CB6D0 = (FadeG*)fn_80081050(base + 0x80, 8);
    lbl_804CB6D8 = (FadeG*)fn_80081050(base + 0x40, 8);
    lbl_804CB6D8->m32 = z;
    lbl_804CB6DC = (FadeS*)fn_80081050(base + 0x58, 8);
    lbl_804CB6DC->m32 = z;
}

