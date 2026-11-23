/* fn_80009454 (GActor_CreateTrail): near miss, 17 of 164 words differ.
 * The colour tail is fn_8000987C inlined with a stack copy of a->color.
 * Only r6/r7 (trail list pointer vs. item offset) are swapped inside the
 * inlined loop. Paste into ../fn_80006CF8.c before fn_800096E4 to test. */
static inline void GActor_SetTrailColorP(GActor* a, const GColor* c) {
    GChildList* list;
    s32 i;
    if (a == NULL || (list = a->children) == NULL) {
        return;
    }
    list->color = *c;
    for (i = 0; i < list->count; i++) {
        s32 al = a->color.a - (a->color.a * i) / list->x2;
        al = al * c->a / 255;
        fn_80008F20(list->items[i], al);
        fn_80008F10(list->items[i], c->r, c->g, c->b);
    }
}

#pragma use_lmw_stmw on
/* GActor_CreateTrail */
void fn_80009454(GActor* a, s32 n, u8 mode) {
    GRes48* r48 = GActor_Find48(a);
    void* save48 = r48->x48;
    GRes44* save44;
    s32 i;
    GActor* c;
    if (n == 0) {
        return;
    }
    if (mode != 1) {
        s32 cnt = 0;
        s32 j;
        for (j = 0; j < r48->entryCount; j++) {
            if (r48->entries[j].flags & 0x200) {
                cnt++;
            }
        }
        if (cnt == 0) {
            return;
        }
        r48->x48 = NULL;
    }
    save44 = a->x44;
    a->children = (GChildList*)fn_80078CCC(0xC, lbl_80360AAC + 0x24, 0);
    a->children->mode = mode;
    a->children->count = n;
    a->children->x2 = 0;
    a->children->items = (GActor**)fn_80078CCC(n * 4, lbl_80360AAC + 0x24, 0);
    for (i = 0; i < n; i++) {
        c = fn_80006E1C();
        a->children->items[i] = c;
        c->parent = a;
        c->flags = a->flags;
        c->x84 = a->x84;
        c->x88 = a->x88;
        c->x82 = a->x82;
        fn_80006F20(c);
        fn_80009334(a, c);
    }
    {
        GColor col = a->color;
        GActor_SetTrailColorP(a, &col);
    }
    r48->x48 = save48;
    a->x44 = save44;
}
#pragma use_lmw_stmw off

