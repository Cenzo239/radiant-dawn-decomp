/* fn_80024EFC: near miss, 39 of 109 words differ. Depends on types and helpers from ../fn_800235B8.cpp; goes there in address order. */
void fn_80024EFC(Str* s, u32 n) {
    u32 lng, size, cap, newcap, keep;
    char* dst;
    char* old;
    if (n > 0x7FFFFFFE) {
        const char* m = lbl_80361118;
        fn_80290B48(__files + 0xA0, m + 0xEF);
        fn_80291BD0();
    }
    lng = s->l.lng;
    if (!lng) {
        cap = 0xB;
        size = s->s.len;
    } else {
        size = s->l.len;
        cap = s->l.cap;
    }
    if (n < size) {
        n = size;
    }
    newcap = 0xB;
    if (n + 1 > 0xB) {
        newcap = (n + 0x10) & ~0xF;
    }
    if (newcap == cap) {
        return;
    }
    if (newcap == 0xB) {
        old = s->l.ptr;
        dst = (char*)s + 1;
        keep = 0;
    } else {
        if (newcap > cap) {
            dst = (char*)fn_80079150(newcap);
            if (dst == 0) {
                fn_80290B48(__files + 0xA0, lbl_80378DB4);
                fn_80291BD0();
            }
        } else {
            dst = (char*)fn_80079150(newcap);
            if (dst == 0) {
                fn_80290B48(__files + 0xA0, lbl_80378DB4);
                fn_80291BD0();
            }
            if (dst == 0) {
                return;
            }
        }
        keep = 1;
        old = lng ? s->l.ptr : (char*)s + 1;
    }
    memmove(dst, old, size);
    dst[size] = 0;
    if (lng) {
        fn_80079210(old);
    }
    s->l.lng = keep;
    if (!keep) {
        s->s.len = size;
    } else {
        s->l.ptr = dst;
        s->l.len = size;
        s->l.cap = newcap;
    }
}
