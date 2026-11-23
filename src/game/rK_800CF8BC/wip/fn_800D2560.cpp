/* fn_800D306C: ['DIFF fn_800D306C: 35 of 103 words differ'] */
void fn_800D306C(RectPart* p) {
    fn_8007E154();
    fn_8007E174(0, 0x10);
    fn_8007E164();
    fn_800800D4(3);
    fn_8008031C(p->z);
    fn_800803F0(p->x0, p->y0, p->x1, p->y1);
    fn_80080578(0);
    {
        u32 c0 = p->c[0].a + (p->c[0].b << 8) + ((p->c[0].r << 24) + (p->c[0].g << 16));
        u32 c1 = p->c[1].a + (p->c[1].b << 8) + ((p->c[1].r << 24) + (p->c[1].g << 16));
        u32 c2 = p->c[2].a + (p->c[2].b << 8) + ((p->c[2].r << 24) + (p->c[2].g << 16));
        u32 c3 = p->c[3].a + (p->c[3].b << 8) + ((p->c[3].r << 24) + (p->c[3].g << 16));
        fn_80080940(*(Color*)&c0, *(Color*)&c1, *(Color*)&c2, *(Color*)&c3);
    }
    fn_80080308();
}

/* fn_800D3218: ['DIFF fn_800D3218: 1 of 97 words differ'] */
void fn_800D3218(Layout* l, f32 f) {
    u8 m = l->mode;
    if (m == 0) {
        int i;
        for (i = l->n - 1; i >= 0; i--) {
            l->parts[i]->v0C(0xFF);
        }
    } else if (m == 2) {
        int i = f;
        int next = (i + 1) % l->n;
        f32 a = 255.99f * (f - (f32)(int)f);
        if (0.0f != a) {
            l->parts[next]->v0C(256.0f + a);
        }
        l->parts[i]->v0C(0x1FF - (int)a);
    } else if (m == 1) {
        l->parts[(int)f]->v0C(0xFF);
    }
}

/* fn_800D363C: ['DIFF fn_800D363C: 28 of 187 words differ'] */
void fn_800D363C(WinProc* p) {
    f32 z = p->z + p->l->z;
    fn_8007E154();
    fn_8007E5C0(p->x, p->y, z, p->w, p->h, p->sx, p->sy, p->rot);
    switch (p->l->bF & 7) {
    case 1:
        fn_8007E84C(1);
        break;
    case 2:
        fn_8007E84C(2);
        break;
    case 4:
        fn_8007E84C(3);
        break;
    case 3:
        break;
    }
    fn_8007E7DC(p->alpha);
    fn_8007E7E8(p->b65);
    fn_8007E164();
    fn_800D3218(p->l, p->cur);
    fn_8007E154();
    fn_8007E7DC(0xFF);
    fn_8007E7E8(0x80);
    fn_8007E164();
    if (p->fence) {
        fn_8007E154();
        fn_8007E4E4(0.0f, 0.0f, 20.0f, 1.0f);
        fn_8007E7DC(p->alpha);
        fn_8007E374(p->fence, 0, 0x11);
        fn_8007E164();
        FenceDraw();
        fn_8007E154();
        fn_8007E7DC(0xFF);
        fn_8007E7E8(0x80);
        fn_8007E164();
    }
}

