/* fn_80009A2C (GActor_UpdateTrail): near miss, 36 of 103 words differ, all
 * volatile-register numbering inside the inlined fn_8000987C (theirs uses
 * one register more: list in r5, i in r3). Same issue as wip/fn_80009454.c.
 * Needs ../fn_80006CF8.c. */
/* GActor_UpdateTrail */
void fn_80009A2C(GActor* a) {
    GChildList* list;
    s32 i;
    if (a == NULL || (list = a->children) == NULL) {
        return;
    }
    for (i = list->count - 1; i >= 0; i--) {
        fn_80009334(i == 0 ? a : list->items[i - 1], list->items[i]);
    }
    {
        GColor col = list->color;
        fn_8000987C(a, &col);
    }
    if (list->x2 < list->count) {
        list->x2++;
    }
}
