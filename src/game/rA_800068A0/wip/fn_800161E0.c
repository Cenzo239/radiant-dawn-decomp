/* fn_800161E0: near miss, 24 of 98 words differ. Depends on types and helpers from ../fn_800148C0.c; goes there in address order. */
void fn_800161E0(ActC* a, ActC* b) {
    StC* s = a->st;
    StC* d = b->st;
    InfoC* info;
    SegC* seg;
    int i, j;
    if (s == 0 || d == 0) {
        return;
    }
    info = s->info;
    seg = info->segs;
    for (i = 0; i < info->n; i++, seg++) {
        for (j = 0; j < seg->count; j++) {
            copyPart(&d->buf[i].parts[j], &s->buf[i].parts[j]);
        }
    }
}
