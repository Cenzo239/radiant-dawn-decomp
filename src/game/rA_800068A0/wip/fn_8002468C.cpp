/* fn_8002468C: near miss, 4 of 82 words differ. Depends on types and helpers from ../fn_8002468C.cpp; goes there in address order. */
void fn_8002468C(VP0* self, WinA* a, WinB* b) {
    s32 tw;
    s32 w;
    s32 h;
    w = a->p3C->v50();
    h = (0x1F - fn_800CB0FC(-1, 1.0f)) >> 1;
    tw = fn_800CA3DC(b->p34->v18(b), -1, 1.0f);
    fn_8006F1B4(0, b->s32, b->b38);
    self->v50(a);
    fn_800800D4(5);
    fn_80080330(((s16)w - tw) >> 1, h + b->s32);
    self->v54(b);
    fn_80080ABC(1, 2.0f);
    fn_80080C24(b->p34->v18(b));
    fn_80080308();
}
