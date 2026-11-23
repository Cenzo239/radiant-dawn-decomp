/* Message log: load a script into the text ring, fn_8014F288. */
#include "game/rM_8014C9F8/types.h"
struct Msg {
    char names[0x10][0x20]; /* 0x0000 */
    char lines[0x100][0x40]; /* 0x0200 */
    int who;        /* 0x4200 */
    int last;       /* 0x4204 */
    char cur[0x18]; /* 0x4208 */
    u8 pad4220[0xC];
    int cnt;        /* 0x422C */
    int line;       /* 0x4230 */
    int col;        /* 0x4234 */
    u8 fresh;       /* 0x4238 */
    u8 pad4239;
    s16 h423A;      /* 0x423A */
    s16 scroll;     /* 0x423C */
    s8 dir;         /* 0x423E */
    s8 speed;       /* 0x423F */
    s16 alpha;      /* 0x4240 */
    s16 dalpha;     /* 0x4242 */
    void* obj;      /* 0x4244 */
    u8 b4248;       /* 0x4248 */
};
struct CE { const char* key; int col; };
struct CT { CE e[0x2F]; };
extern "C" {
extern u32 lbl_804CB700;
extern char lbl_80369FE8[];
extern CT lbl_80369E70;
#if TARGET_PC
FE10_PROTO u8* fn_800D0864(p32arg);
#else
u8* fn_800D0864(int);
#endif
int fn_8014FA18(Msg*, u8**);
int fn_80291188(const char*, const char*);

#define LINE(m, n) ((m)->lines[((n) + 0x100) & 0xFF])

static inline void MsgPutc(Msg* m, u8 c) {
    if (!(lbl_804CB700 & 0x800)) {
        m->fresh = 0;
        if (m->col <= 0x3E) {
            LINE(m, m->line)[m->col] = c;
            m->col++;
            LINE(m, m->line)[m->col] = 0;
        }
    }
}

static inline void PutS(Msg* m, s8 c) {
    if (!(lbl_804CB700 & 0x800)) {
        m->fresh = 0;
        if (m->col <= 0x3E) {
            LINE(m, m->line)[m->col] = c;
            m->col++;
            LINE(m, m->line)[m->col] = 0;
        }
    }
}

static inline void MsgEol(Msg* m) {
    if (m->fresh == 0) {
        LINE(m, m->line)[m->col] = 0;
        m->col = 0;
        m->line++;
        LINE(m, m->line)[0] = 0;
        m->fresh = 1;
        m->cnt++;
    }
}

static inline void MsgPuts(Msg* m, const char* s) {
    if (!(lbl_804CB700 & 0x800)) {
        while (*s != 0) {
            MsgPutc(m, *s++);
        }
    }
}

static inline BOOL IsSjis(u8* s) {
    u8 c = s[0];
    if ((c >= 0x81 && c <= 0x9F) || (c >= 0xE0 && c <= 0xFC)) {
        c = s[1];
        if ((c >= 0x40 && c <= 0x7E) || (c >= 0x80 && c <= 0xFC)) {
            return 1;
        }
    }
    return 0;
}

static inline void Pad(Msg* m) {
    int i;
    for (i = 0; i < 3 - m->cnt; i++) {
        MsgPuts(m, lbl_80369FE8 + 0xA);
        MsgEol(m);
        m->cnt--;
    }
}

#pragma use_lmw_stmw on
void fn_8014F288(
#if TARGET_PC
Msg* m, const char* key
#else
Msg* m, int key
#endif
) {
    u8* s = fn_800D0864(key);
    int i;
    int col;
    m->cnt = 2;
    m->b4248 = 1;
    for (i = 0; i < 0x10; i++) {
        m->names[i][0] = 0;
    }
    m->line = 0;
    m->col = 0;
    for (i = 0; i < 0x100; i++) {
        LINE(m, i)[0] = 0;
        LINE(m, i)[1] = 0;
    }
    m->last = -1;
    for (;;) {
        switch (fn_8014FA18(m, &s)) {
        case 0:
            goto end;
        case 1:
            continue;
        case 4:
            break;
        }
        if (m->who != m->last) {
            Pad(m);
            MsgPuts(m, lbl_80369FE8 + 6);
            MsgPuts(m, m->names[m->who]);
            {
                char* name = m->names[m->who];
                CT t = lbl_80369E70;
                col = 7;
                if (name) {
                    CE* e;
                    for (e = t.e; e->key; e++) {
                        if (fn_80291188(name, e->key) == 0) {
                            col = e->col;
                            break;
                        }
                    }
                }
            }
            MsgEol(m);
            m->cnt = 0;
            m->last = m->who;
        }
        if (m->col == 0) {
            {s8 ch = col + 0x30; PutS(m, ch);}
        }
        if (!IsSjis(s)) {
            MsgPutc(m, *s++);
        } else {
            MsgPutc(m, *s++);
            MsgPutc(m, *s++);
        }
    }
end:
    { const char* s; int c; for (i = 0; i < 3 - m->cnt; i++) { s = (char*)(lbl_80369FE8 + 0xA); if (!(lbl_804CB700 & 0x800)) { while (*s != 0) { c = *(u8*)s; s++; MsgPutc(m, c); } } MsgEol(m); m->cnt--; } }
}
}
