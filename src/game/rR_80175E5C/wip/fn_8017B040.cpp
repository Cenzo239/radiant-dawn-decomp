/* fn_8017B040: 12 of 72 words differ, all volatile register numbers around the wait countdown and the fn_8001EBC8 arguments. Uses the declarations of fn_8017B160.cpp. */
struct FadeIn {
    u8 pad0[0x30];
    Filter* f;
    u8 pad34[0x34 - 0x34];
    u16 t;
    u16 dur;
    u16 from;
    u16 to;
    u8 pad3C[2];
    s16 wait;
};

void fn_8017B040(FadeIn* o) {
    fn_80010788(3, 0x9C, fn_8017B638, o->f);
    if (o->wait > 0) {
        s16 w = o->wait - 1;
        o->wait = w;
        if (w == 0) {
            o->t = 0;
            o->dur = o->dur * 2;
            o->from = 0xFF;
            o->to = 0;
        }
    }
    if (o->t < o->dur) {
        u16 nt = o->t + 1;
        o->t = nt;
        o->f->a2 = fn_8001EBC8(o->from, o->to, o->dur, nt, 2);
    } else {
        o->f->a2 = o->to;
        if (o->to == 0) fn_80083B78(o);
    }
}
