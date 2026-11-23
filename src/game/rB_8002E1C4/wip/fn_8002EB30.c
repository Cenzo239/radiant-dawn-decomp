/* fn_8002EB30: 4 of 48 words differ (register swap r0/r3 vs r4/r0 for the
 * final two byte stores before fn_8002EBF0). Best version:
 *   if (fn_80128EDC(p, x) != 0) {
 *       if (item_min_range(&p->item2, p) > x || item_max_range(&p->item2, p) < x) return;
 *       if (x == 1) { copy item2->item; x483 = 1; x47c = item.uses; fn_8002EBF0(p); }
 *   }
 */
