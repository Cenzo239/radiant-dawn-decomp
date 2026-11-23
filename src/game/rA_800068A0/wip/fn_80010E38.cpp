/* fn_80010E38 (GLightSet_Alloc): 13 of 87 words differ. It goes at the end of
 * fn_8000F48C.cpp after fn_80010DA4. The original inlines its own recursion two
 * levels deep, but CW only auto-inlines functions without loops, so the levels
 * are spelled out. With the outer level written directly the callee registers
 * come out rotated (22 words); with the outer level also an inline (below) the
 * registers match but the outer return goes through the "converging mr r3"
 * pattern instead of returning directly. */
GLight* fn_80010E38(GLightSet* s, int type);

/* The original inlines its own recursion two levels deep; a function with a
 * loop is only inlined when declared inline, so the levels are spelled out. */
#define GLIGHTSET_ALLOC_BODY(NEXT)                      \
    int i;                                              \
    GLight* l;                                          \
    if (s == NULL) {                                    \
        s = lbl_804CA050;                               \
    }                                                   \
    l = s->body.lights;                                 \
    for (i = 0; i < 8; i++) {                           \
        if (l->type == 0) {                             \
            l->type = type;                             \
            switch (type) {                             \
            case 1:                                     \
            case 2: {                                   \
                GLight* l2 = NEXT(s, type + 2);         \
                if (l2 != NULL) {                       \
                    l2->link = l->id;                   \
                }                                       \
                break;                                  \
            }                                           \
            }                                           \
            return l;                                   \
        }                                               \
        l++;                                            \
    }                                                   \
    return NULL;

static inline GLight* GLightSet_Alloc2(GLightSet* s, int type) {
    GLIGHTSET_ALLOC_BODY(fn_80010E38)
}

static inline GLight* GLightSet_Alloc1(GLightSet* s, int type) {
    GLIGHTSET_ALLOC_BODY(GLightSet_Alloc2)
}

static inline GLight* GLightSet_Alloc0(GLightSet* s, int type) {
    GLIGHTSET_ALLOC_BODY(GLightSet_Alloc1)
}

#pragma auto_inline off
/* GLightSet_Alloc: types 1 and 2 also allocate a companion of type + 2 */
GLight* fn_80010E38(GLightSet* s, int type) {
    return GLightSet_Alloc0(s, type);
}
#pragma auto_inline reset
