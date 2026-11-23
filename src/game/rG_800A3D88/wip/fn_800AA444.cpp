// 15/31 words: only r4/r5 swapped between constants 0 and 1. Same Ev struct as fn_800AA848.cpp.
void fn_800AA444(Ev* e) {
    FVec v;
    *(u32*)&v.x = 0;
    *(u32*)&v.y = 0;
    *(u32*)&v.z = 0;
    e->m50 = NULL;
    e->m30 = 1;
    e->m58 = NULL;
    e->m54 = NULL;
    e->m33 = 0x32;
    e->m34 = 0x32;
    e->m32 = 0;
    e->m38 = v;
    e->m4d = 0;
    e->m4e = 0;
    e->m4c = 0;
    e->m44 = lbl_804CD330;
    e->m48 = lbl_804CD334;
    e->m31 = 1;
    e->m50 = NULL;
}

