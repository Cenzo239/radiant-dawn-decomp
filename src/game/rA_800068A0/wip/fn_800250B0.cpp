/* fn_800250B0: near miss, 108 of 178 words differ. Depends on types and helpers from ../fn_800235B8.cpp; goes there in address order. */
Str* fn_800250B0(Str* s, u32 pos, u32 n1, const char* f, const char* last, E a) {
    u32 lng, cap, size, m, n2, rest, newlen, tail;
    char* data;
    lng = s->l.lng;
    if (!lng) {
        size = s->s.len;
        data = (char*)s + 1;
        cap = 0xB;
    } else {
        data = s->l.ptr;
        cap = s->l.cap;
        size = s->l.len;
    }
    if (pos > size) {
        fn_80290B48(__files + 0xA0, lbl_80361118 + 0x112);
        fn_80291BD0();
    }
    {
        u32 t = size - pos;
        m = umin(n1, t);
    }
    n2 = dist(f, last);
    if (n2 > 0x7FFFFFFE || (rest = size - m) > 0x7FFFFFFE - n2) {
        fn_80290B48(__files + 0xA0, lbl_80361118 + 0x12D);
        fn_80291BD0();
    }
    newlen = n2 + rest;
    tail = size - (pos + m);
    if (newlen >= cap) {
        char* d;
        char* q;
        u32 c = (cap + 0xF) & ~0xF;
        while (c < newlen + 1) {
            c = (c * 2 + 0xF) & ~0xF;
        }
        d = (char*)fn_80079150(c);
        if (d == 0) {
            fn_80290B48(__files + 0xA0, lbl_80378DB4);
            fn_80291BD0();
        }
        if (pos != 0) {
            memcpy(d, data, pos);
        }
        q = d + pos;
        memmove(q, f, last - f);
        if (tail != 0) {
            memcpy(q + n2, data + pos + m, tail);
        }
        d[newlen] = lbl_804CA058[0];
        if (lng) {
            fn_80079210(data);
        } else {
            s->l.lng = 1;
        }
        s->l.ptr = d;
        s->l.len = newlen;
        s->l.cap = c;
    } else {
        Str t;
        *(u32*)&t = 0;
        t.l.len = 0;
        t.l.ptr = 0;
        if (tail != 0 && data + pos + n2 < last && last <= data + size) {
            fn_800250B0(&t, 0, !t.l.lng ? t.s.len : t.l.len, f, last, E());
            f = t.l.lng ? t.l.ptr : (char*)&t + 1;
        }
        if (tail != 0) {
            memmove(data + pos + n2, data + pos + m, tail);
        }
        memmove(data + pos, f, n2);
        data[newlen] = lbl_804CA059[0];
        if (!lng) {
            s->s.len = newlen;
        } else {
            s->l.len = newlen;
        }
        if (t.l.lng) {
            fn_80079210(t.l.ptr);
        }
    }
    return s;
}
