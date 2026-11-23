/* near misses; take the declarations from ../fn_801CA4FC.cpp */
void fn_801CABAC(PY* p) {
    p->x40 = 0;
    p->x44 = 0.015625f * p->m->xA;
    p->x48 = p->x38;
    if ((f32)__fabs((f64)(p->x44 - p->x48)) > 180.0f) {
        if (p->x44 < p->x48) {
            p->x44 = p->x44 + 360.0f;
        } else if (p->x44 > p->x48) {
            p->x48 = p->x48 + 360.0f;
        }
    }
}

void fn_801CADE0(PZ* p) {
    MCol* m = p->m;
    C4 c(*(C4*)&m->r);
    p->x3C = c;
    p->x34 = 0;
}
