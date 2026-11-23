/* fn_8025F068: 4 words, lfd scheduled too early. fn_8025F0E8: 11 words, dur should be r4 and 0x4330 r5. */
static inline int get48(u8* p) { return *(s8*)(p + 0x48); }
f32 fn_8025F068(u8* p) { return get48(p); }
struct Fader {
    u8 pad[0x10];
    int t;     /* 0x10 */
    int dur;   /* 0x14 */
    f32 cur;   /* 0x18 */
    f32 from;  /* 0x1C */
    f32 to;    /* 0x20 */
};

f32 fn_8025F0E8(Fader* f) {
    int dur = f->dur;
    int t = f->t;
    if (t < dur) {
        f->t = t + 1;
        f->cur = (f->to - f->from) * ((f32)t / (f32)dur) + f->from;
    } else {
        f->cur = f->to;
    }
    return f->cur;
}

