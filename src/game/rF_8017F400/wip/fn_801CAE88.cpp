/* near misses; take the declarations from ../fn_801CAE88.cpp */
void fn_801CB1A0(PZ2* p) {
    int v;
    p->x34++;
    if (p->x3C > p->x3D) {
        v = fn_8001EBC8(2, p->x3C, p->x3D, p->x38, p->x34);
    } else {
        v = fn_8001ECE4(2, p->x3C, p->x3D, p->x38, p->x34);
    }
    fn_80008F20(p->m->x14, (u8)v);
    if (p->x38 == p->x34) fn_80083B78(p);
}
