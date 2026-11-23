// size 0x48 vs 0x4C: the original has beq-over-b for the inner null test.
static inline void Sub78_sync(Sub78* m) {
    Sub44* s = m->m44;
    if (s == NULL) {
        return;
    }
    m->m58 = s->v18;
}

void fn_800A4A98(Body* b) {
    Sub78* m = b->m78;
    if (m != NULL) {
        Sub78_sync(m);
    }
}

