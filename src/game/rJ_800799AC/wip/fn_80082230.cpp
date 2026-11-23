/* Near misses that inline Proc_End. Fragments: these need fn_80081A90.cpp's includes.
 * Each is right except for a rotation of saved registers.
 *
 * fn_80082230, fn_800829CC: loop variable r24 should be r25, next r26 should be r24,
 *   and inlined mark locals r25 should be r26. Tried: declaration orders, for/while,
 *   parent reused as a variable, inline wrappers.
 * fn_80085FC4: p r28 should be r29, inlined prev r29 should be r28.
 * fn_80087F78: 47 words; script should be r28 (inline param gets close).
 * fn_80088948: returned process r31 should be r29.
 */
/* Proc_EndChildren */
void fn_80082230(Proc* parent) {
    Proc* n;
    Proc* q;
    if (parent == 0) {
        return;
    }
    q = parent->child;
    while (q != 0) {
        n = q->prev;
        if (q != 0 && q->script != 0 && !(q->flags & PROC_ENDED)) {
            PROC_END_BODY(q)
        }
        q = n;
    }
}

/* Script command: end this process */
int fn_80085FC4(Proc* p) {
    if (p != 0 && p->script != 0 && !(p->flags & PROC_ENDED)) {
        PROC_END_BODY_M(p)
    }
    return 0;
}

static inline void endClass(void* script) {
        int i;
    Proc* q = lbl_803D9A58;
        for (i = 0; i < 0x100; i++, q++) {
        if (q->script == script) {
            procEnd(q);
        }
    }
}

int fn_80087F78(Proc* p) {
    endClass((void*)p->cur[1]);
    p->cur += 2;
    return 1;
}

static inline Proc* findName(const char* name) {
    Proc* q = lbl_803D9A58;
    int i;
    for (i = 0; i < 0x100; i++, q++) {
        if (q->script != 0) {
            const char* s1 = q->name;
            const char* s2 = name;
            int r;
            while (*s1 | *s2) {
                if (*s1 != *s2) {
                    r = *s1 - *s2;
                    goto done;
                }
                s1++;
                s2++;
            }
            r = 0;
        done:
            if (r == 0) {
                return q;
            }
        }
    }
    return 0;
}

/* Script command: end a process by name */
int fn_80088948(Proc* p) {
    Proc* q = findName((const char*)p->cur[1]);
    if (q != 0) {
        procEnd(q);
    }
    p->cur += 2;
    return 1;
}


void fn_800829CC(Proc* parent, void* script) {
    Proc* q;
    if (parent == 0) {
        return;
    }
    q = parent->child;
    while (q != 0) {
        Proc* n = q->prev;
        if (q->script == script) {
            procEnd(q);
        }
        q = n;
    }
}
