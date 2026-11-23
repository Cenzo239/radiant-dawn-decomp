// 12/53: f gets r30 and i r31, want reversed (same family as fn_800AE500, fn_800BE2BC).
BOOL fn_800C3974() {
    lbl_804CB6B8 = 0;
    CmbFile* f = lbl_804CB6A0;
    CmbFile* n;
    while ((n = f->next) != NULL) {
        f = n;
    }
    if (f == NULL) {
        lbl_804CB6B8 = 1;
        return 0;
    }
    lbl_804CB6A6 -= f->m22;
    UnregCmds(f);
    CmbFile* h = lbl_804CB6A0;
    if (h != f) {
        CmbFile* m;
        while ((m = h->next) != f) {
            h = m;
        }
        h->next = NULL;
    }
    fn_8023F1A8(f);
    return 1;
}

