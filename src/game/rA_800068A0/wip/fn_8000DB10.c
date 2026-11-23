/* fn_8000DB10: near miss, 7 of 127 words differ. Depends on types and helpers from ../fn_8000DA60.c; goes there in address order. */
void fn_8000DB10(void* model, AList* a, Mtx* buf, f32 frame) {
    ASet* set = findChunk(a, 0);
    int i;
    if (set != 0) {
        for (i = 0; i < set->count; i++) {
            u16 off = set->offs[i];
            AFrame* keys = off == 0xFFFF ? 0 : (AFrame*)((u8*)set + off);
            u16 n = ((u16*)keys)[0];
            u16 id = ((u16*)keys)[1];
            keys = (AFrame*)((u16*)keys + 2);
            if (n != 0) {
                s32 k = searchKey(keys, frame, n);
                s16 v = k < 0 ? keys[0].val : keys[k].val;
                if (v == 0) {
                    GNode* node = fn_8000F3D4(model, id);
                    if (!(node->flags & 0x10000000)) {
                        Mtx m;
                        fn_8031292C(m, 0.0f, 0.0f, 0.0f);
                        fn_80312378(buf[id], m, buf[id]);
                        node->flags |= 0x4000000;
                    }
                }
            }
        }
    }
}
