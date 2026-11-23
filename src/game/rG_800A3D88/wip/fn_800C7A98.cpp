// 16/30, size 0x78 vs 0x7C: ref/del base registers built per array in the original.
void fn_800C7A98(void* name) {
    FaceCache* c = &lbl_803E7200;
    void* k = fn_800C3FD0(name);
    for (int i = 0; i < 8; i++) {
        if (k == c->key[i]) {
            c->del[i] = 2;
            c->ref[i]--;
            return;
        }
    }
}
