/* fn_8008A868: functionally equal (regs level per tools/check_regs.py; registers differ from the original). From wip/fn_8008A868.cpp. */
/* fn_8008A868 near miss (round 16): 5 words. Only two hoisted loop invariants are swapped in the glyph loop: the tree header address &tree.root must be r25 and the zero for the terminator bytes r26. A for(;;) { if (n == end) break; } loop gets the registers right but keeps the test at the top. Tried: iterator classes, named end/zero locals, begin()/end() members, the loop as a Tree member, helper inlines for the string. Builds the glyph cache for every character used by the game text tables. */
#include "game/rJ_800799AC/types.h"

struct Node {
    Node* left;   /* 0x00 */
    Node* right;  /* 0x04 */
    u32 parent;   /* 0x08 parent pointer, colour in bit 0 */
    u16 key;      /* 0x0C */
};

struct Glyph {
    u8 pix[0x120];
    u16 code;  /* 0x120 */
    u16 w;     /* 0x122 */
    u8 pad[0x140 - 0x124];
};

struct GlyphCache {
    Glyph* buf;
    int count;
};

struct Tree;

extern "C" {
extern const u8** lbl_80381190[];
extern const u8* lbl_803810C8[];
extern GlyphCache lbl_804CB5E8;
u16 fn_8031C044(void);
Node* fn_8008BD3C(Tree* t, const u16* key, Node** out, u8* a, u8* b);
void fn_8008B60C(Tree* t, Node* at, u8 a, u8 b, const u16* key);
void fn_8008B730(Tree* t, Node* n);
void* fn_80078D9C(int size, const char* name, int flags);
void* fn_80078D28(int heap, int size, const char* name, int flags);
void fn_80078E24(void* p);
void fn_80079210(void* p);
void fn_8031C418(void* a, void* b);
void fn_8031C7F8(const char* s, Glyph* g, int a, int b, int* w);
void* memset(void* p, int c, u32 n);
void DCFlushRange(void* p, u32 n);
}

static inline void del0(Tree* t, Node* n) {
    if (n->left) fn_8008B730(t, n->left);
    if (n->right) fn_8008B730(t, n->right);
    fn_80079210(n);
}
static inline void del1(Tree* t, Node* n) {
    if (n->left) del0(t, n->left);
    if (n->right) del0(t, n->right);
    fn_80079210(n);
}
static inline void del2(Tree* t, Node* n) {
    if (n->left) del1(t, n->left);
    if (n->right) del1(t, n->right);
    fn_80079210(n);
}
static inline void del3(Tree* t, Node* n) {
    if (n->left) del2(t, n->left);
    if (n->right) del2(t, n->right);
    fn_80079210(n);
}

struct Tree {
    int size;
    Node* root;
    Node* first;
    Tree() { size = 0; root = 0; first = (Node*)&root; }
    ~Tree() { if (root) del3(this, root); }
    void insert(const u16* key) {
        Node* out;
        u8 a, b;
        Node* at = fn_8008BD3C(this, key, &out, &a, &b);
        if (out == 0 || out->key < *key) fn_8008B60C(this, at, a, b, key);
    }
};

struct It { Node* n; void incr() {
    if (n->right) {
        Node* m = n->right;
        while (m->left) m = m->left;
        n = m;
    } else {
        Node* p;
        while (n != (p = (Node*)(n->parent & ~1))->left) n = p;
        n = p;
    }
} };

static inline BOOL isSjis(const u8* s) {
    if (((s[0] >= 0x81 && s[0] <= 0x9F) || (s[0] >= 0xE0 && s[0] <= 0xFC))
        && ((s[1] >= 0x40 && s[1] <= 0x7E) || (s[1] >= 0x80 && s[1] <= 0xFC))) {
        return 1;
    }
    return 0;
}

extern "C" {

/* Scaffolding: sets the offsets of the file's string pool at lbl_803630C4. */
#pragma pool_strings on
void StringPool(const char** p) {
    p[0] = "";
    p[1] = "tree::insert length error";
}

#pragma use_lmw_stmw on
void fn_8008A868(void) {
    Tree tree;
    const u8*** pp;
    const u8** tbl;
    const u8* s;
    void* h1;
    void* h2;
    for (pp = lbl_80381190; (tbl = *pp) != 0; pp++) {
        if (fn_8031C044() != 1 && tbl == lbl_803810C8) continue;
        for (; (s = *tbl) != 0; tbl++) {
            while ((s8)*s != 0) {
                if ((s8)*s == '\n') {
                    s++;
                } else if (fn_8031C044() != 1) {
                    u16 c = *s++;
                    tree.insert(&c);
                } else {
                    BOOL sj = 0;
                    if (fn_8031C044() == 1) sj = isSjis(s);
                    if (!sj) {
                        u16 c = *s++;
                        tree.insert(&c);
                    } else {
                        tree.insert((const u16*)s);
                        s += 2;
                    }
                }
            }
        }
    }
    if (fn_8031C044() == 1) {
        h1 = fn_80078D9C(-0x90EE4, "", 0);
        h2 = fn_80078D9C(-0x4D000, "", 0);
    } else {
        h1 = fn_80078D9C(-0x10120, "", 0);
        h2 = fn_80078D9C(-0x3000, "", 0);
    }
    fn_8031C418(h1, h2);
    GlyphCache* gc = &lbl_804CB5E8;
    lbl_804CB5E8.buf = (Glyph*)fn_80078D28(0, tree.size * 0x140, "", 0);
    memset(lbl_804CB5E8.buf, 0, tree.size * 0x140);
    lbl_804CB5E8.count = tree.size;
    {
        Node* n = tree.first;
        Glyph* g = lbl_804CB5E8.buf;
        for (; n != (Node*)&tree.root; ((It*)&n)->incr(), g++) {
            char buf[3];
            int w;
            if ((n->key & 0xFF00) == 0) {
                buf[0] = n->key;
                buf[1] = 0;
            } else {
                buf[0] = (u8)((u32)(n->key & 0xFF00) >> 8);
                buf[1] = n->key;
                buf[2] = 0;
            }
            fn_8031C7F8(buf, g, 0, 6, &w);
            g->code = n->key;
            g->w = w;
        }
    }
    DCFlushRange(gc->buf, tree.size * 0x140);
    fn_80078E24(h2);
    fn_80078E24(h1);
}
#pragma use_lmw_stmw off

}
