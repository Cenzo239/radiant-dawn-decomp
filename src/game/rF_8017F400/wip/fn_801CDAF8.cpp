/* near misses; take the declarations from ../fn_801CDAF8.cpp */
void fn_801CE2F4(const char* s, u32 f, void* parent) {
    int i;
    PS* p;
    int y = 0;
    int z = 0;
    int x = 0;
    if (f & 1) x = 0;
    if (f & 2) x = 0x260;
    if (f & 8) y = 0x50;
    if (f & 4) { y = 0x190; z = 1; }
    if (f) {
        i = 0;
        p = (PS*)fn_800E4278(lbl_8036EA00 + 0x2A, parent);
        p->x60 = i;
        p->x30->x98 = (void*)fn_801CE068;
        p->x30->x9C = (void*)fn_801CE174;
        p->x30->xA0 = (void*)fn_801CE130;
        strcpy(p->x40, s);
        p->x3A = x;
        p->x3C = y;
        p->x3E = z;
        p->x3F = i;
        p->x34 = 1;
        p->x30->x4 = 4;
        p->x36 = i;
        {
            int yy = p->x3C + i * 0x24;
            int xx = p->x3A;
            Pt a;
            *(int*)&a.x = i; *(int*)&a.y = i; *(int*)&a.z = i;
            a.x = xx;
            a.y = yy;
            {
            Pt b = a;
            Pt c = b;
            fn_800E48C8(p, &c);
            }
        }
        fn_800E465C((void*)fn_801CE010, p);
    }
}

void fn_801BE154(u8* c, f32 x0, f32 y0, f32 x1, f32 y1) {
    fn_8007E154();
    fn_8007E174(0, 0x12);
    fn_8007E164();
    if (x0 > x1) { f32 ty = y0; f32 tx = x0; x0 = x1; y0 = y1; x1 = tx; y1 = ty; }
    x1 -= x0; y1 -= y0;
    fn_800800D4(4);
    fn_80080388(x0 - 2.4f, y0, 4.8f + x1, y1);
    fn_800804D4(c[0], c[1], c[2], c[3] >> 2);
    fn_80080578(0);
    fn_80080308();
    fn_800800D4(4);
    fn_80080388(x0, y0, x1, y1);
    fn_800804D4(c[0], c[1], c[2], c[3]);
    fn_80080578(0);
    fn_80080308();
}
