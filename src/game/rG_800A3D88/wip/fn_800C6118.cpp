// original keeps a frame (r31) and shuffles args through r9..r12; ours tail-less but no r31. All-register miss.
static inline int FreeSlot() {
    if (lbl_803E50D0[0] == NULL) {
        return 0;
    }
    if (lbl_803E50D0[1] == NULL) {
        return 1;
    }
    if (lbl_803E50D0[2] == NULL) {
        return 2;
    }
    if (lbl_803E50D0[3] == NULL) {
        return 3;
    }
    if (lbl_803E50D0[4] == NULL) {
        return 4;
    }
    if (lbl_803E50D0[5] == NULL) {
        return 5;
    }
    if (lbl_803E50D0[6] == NULL) {
        return 6;
    }
    if (lbl_803E50D0[7] == NULL) {
        return 7;
    }
    return -1;
}

void fn_800C6118(void* a, void* b, void* c, void* d, void* e) {
    fn_800C5EA4(FreeSlot(), a, b, c, d, 0);
}

