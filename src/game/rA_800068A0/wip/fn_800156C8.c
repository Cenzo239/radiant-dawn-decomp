/* fn_800156C8: near miss, 47 of 141 words differ. Depends on types and helpers from ../fn_80016368.c; goes there in address order. */
void fn_800156C8(PActor* a) {
    PState* st = a->s;
    f32 frame = fn_800081B4(a);
    PInfo* info = st->info;
    int i = 0;
    PBuf* b = st->buf;
    PSeg* s = info->segs;
    for (; i < info->n; i++, s++, b++) {
        if (s->flags & 0x10) {
            b->delta = a->x5C;
            b->cur += b->delta;
            {
                f32 hi = b->hi;
                f32 len = b->hi - b->lo;
                if (b->cur > hi) {
                    b->cur = b->cur - len;
                }
            }
        } else {
            f32 d = frame - b->cur;
            b->delta = d;
            b->cur = frame;
            if (d < 0.0f) {
                PKey* k = s->keys;
                Part* p = b->parts;
                int j;
                b->cur = a->x58;
                b->delta = 0.0f;
                b->lo = 0;
                b->hi = 0;
                for (j = 0; j < *(u16*)((u8*)s + 0x1E); j++, k = (PKey*)((u8*)k + 0xC), p++) {
                    p->p.x = 0.015625f * k->x;
                    p->p.y = 0.015625f * k->y;
                    p->p.z = 0.015625f * k->z;
                    p->v.x = 0.0f;
                    p->v.y = 0.0f;
                    p->v.z = 0.0f;
                    p->age = -1.0f;
                    p->x1C = 0.0f;
                    p->size = 1.0f;
                    *(f32*)((u8*)p + 0x24) = 1.0f;
                    p->r = 0xFF;
                    p->g = 0xFF;
                    p->b = 0xFF;
                    p->a = 0;
                    ((u8*)p)[0x48] = 0;
                    ((u8*)p)[0x49] = 0;
                }
                if (s->flags & 0x10) {
                    k = s->keys;
                    b->lo = 0x2710;
                    b->hi = -0x2710;
                    for (j = 0; j < *(u16*)((u8*)s + 0x1E); j++, k = (PKey*)((u8*)k + 0xC)) {
                        if (b->lo > k->y0) {
                            b->lo = k->y0;
                        }
                        if (b->hi < k->y0 + 1) {
                            b->hi = k->y0 + 1;
                        }
                    }
                }
            }
        }
    }
}
