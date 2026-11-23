/* Near misses from fn_80077F98.cpp (fragments, need its declarations).
 * fn_800785FC: 8 of 122 words: only the 0 (should be r7) and h+0x20 (should be r6) swap.
 * Must write the first block through (u8*)h + 0x20: a member forwards the h->free read.
 * fn_800787E4: 84 of 274 with every heapIndex macro-expanded (scratch search stalled):
 * the first key should be r8 and its counter r3.
 */
int fn_800785FC(const char* name, u32 size) {
    int i;
    Heap* h;
    fn_8031DD44(lbl_803CD8A8 + 4);
    size = (size + 0x1F) & ~0x1F;
    h = lbl_804CB5A8 ? (Heap*)((u8*)lbl_804CB5A8 + lbl_804CB5A8->size) : (Heap*)lbl_804CB5A0;
    i = heapIndex(0);
    fn_802910CC(h->name, name, 0xB);
    h->name[0xB] = 0;
    h->below = 0;
    h->size = size;
    h->used = 0;
    h->free = (Block*)((u8*)h + 0x20);
    h->magic = 0x48454150;
    ((Block*)((u8*)h + 0x20))->next = 0;
    h->free->prev = 0;
    h->free->size = h->size - 0x20;
    lbl_803CD868[i] = h;
    lbl_804CB5B0 = h;
    fn_8023FBEC(i);
    h->below = lbl_804CB5A8;
    lbl_804CB5A8 = h;
    fn_8031DE20(lbl_803CD8A8 + 4);
    return i;
}

void fn_800787E4(void) {
    int i;
    int j;
    BOOL cur;
    Heap* h;
    Heap* n;
    fn_8031DD44(lbl_803CD8A8 + 4);
    i = heapIndex(lbl_804CB5A8);
    j = heapIndex(lbl_804CB5B0);
    lbl_804CB5A8 = lbl_804CB5A8->below;
    h = lbl_803CD868[i];
    cur = i == j;
    fn_800C7B14(h, h->size);
    fn_8023F7B0(heapIndex(h));
    n = lbl_804CB5A8;
    lbl_803CD868[i] = 0;
    if (n != 0) {
        j = heapIndex(n);
        if (cur) {
            lbl_804CB5B0 = lbl_803CD868[j];
            fn_8023FBEC(j);
        }
    }
    fn_8031DE20(lbl_803CD8A8 + 4);
}

