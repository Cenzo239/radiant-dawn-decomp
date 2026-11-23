/* fn_80008B50 (GActor_PopAnims): not matching. The original inlines
 * fn_80008A38 four levels deep (a->child .. 4th generation, then a call to
 * fn_80008A38). With plain C, fn_80008A38 being self-recursive is never
 * inlined here; declaring fn_80008A38 `inline` inlines just one level
 * (0xAC of 0x148 bytes). Needs the GActor types from ../fn_80006CF8.c. */
/* GActor_PopAnims */
BOOL fn_80008B50(GActor* a) {
    if (a == NULL) {
        fn_8001E008(lbl_80360AAC, 0x3FC, lbl_80360AAC + 0x42);
    }
    if (a->child == NULL) {
        return 0;
    }
    fn_80008A38(a->child);
    a->child = NULL;
    a->x78 = 1.0f;
    return 1;
}
