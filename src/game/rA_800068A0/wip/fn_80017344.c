/* fn_80017344: near miss, 19 of 186 words differ. Depends on types and helpers from ../fn_80016368.c; goes there in address order. */
void fn_80017344(void* a, Seg* s, Part* p) {
    void* res = fn_80007EE4(a);
    Mtx mv;
    Mtx rot;
    Vec w;
    Vec v;
    f32 k;
    int n;
    int i;
    fn_80021B68(0);
    fn_803031CC();
    fn_80302B80(9, 1);
    fn_80302B80(0xB, 1);
    fn_80303200(0, 9, 1, 4, 0);
    fn_80303200(0, 0xB, 1, 5, 0);
    fn_80021C34(0);
    fn_80021BF4(1);
    fn_80021CB4(0, 0xFF, 0xFF, 4);
    fn_80021EF8(0, 4);
    k = fx6f(*(s16*)((u8*)s + 0x14));
    n = fx6f(*(s16*)((u8*)s + 0x10));
    if (n > 0x28) {
        n = 0x28;
    }
    fn_80307E48(fn_8000FB88(), 0);
    fn_80021784(0);
    fn_80016368(s, fn_8000F3D4(res, s->node), mv, mv);
    fn_8001E6D0(mv, rot);
    fn_80304538(6.0f * n, 0);
    for (i = 0; i < s->count; i++, p++) {
        if (!(p->age < 0.0f) && p->a != 0) {
            fn_80312DB4(mv, p, &w);
            fn_80312DB4(rot, &p->v, &v);
            fn_80304314(0xA8, 0, 2);
            gxPos3(w.x, w.y, w.z);
            gxCol4(p->r, p->g, p->b, p->a);
            gxPos3(w.x - v.x * p->size, w.y - v.y * p->size, w.z - v.z * p->size);
            gxCol4(p->r, p->g, p->b, p->a * k);
        }
    }
}
