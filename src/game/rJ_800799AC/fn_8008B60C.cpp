/* MSL-style red-black tree (std::set<u16> of glyph codes): insert a new node below `at`.
 * Names guessed. The string pool scaffold dumps the file's two real strings at lbl_803630C4. */
#include "game/rJ_800799AC/types.h"

struct Node {
    Node* left;   /* 0x00 */
    Node* right;  /* 0x04 */
    u32 parent;   /* 0x08 parent pointer, colour in bit 0 */
    u16 key;      /* 0x0C */
};
struct Tree {
    u32 size;
    Node* root;
    Node* first;
};
struct File { u8 pad[0x50]; };

extern "C" {
extern File __files[4];
extern char lbl_803811B0[];
int fn_80290B48(File*, const char*, ...);   /* fprintf */
void fn_80291BD0(void);                     /* abort */
void* fn_80079150(u32 size);
void fn_80079210(void* p);
void fn_8008B9B8(Node* n, Node* root);
}

struct NodeGuard {
    Node** alloc;
    Node* p;
    NodeGuard(Node** a, Node* q) : alloc(a), p(q) {}
    ~NodeGuard() { if (p) fn_80079210(p); }
};
#if TARGET_PC
/* Host: size_t is 64-bit */
inline void* operator new(__SIZE_TYPE__, void* p) { return p; }
#else
inline void* operator new(u32, void* p) { return p; }
#endif
static inline Node* allocNode() {
    Node* p = (Node*)fn_80079150(0x10);
    if (p == 0) {
        fn_80290B48(&__files[2], lbl_803811B0);
        fn_80291BD0();
    }
    return p;
}

extern "C" {

/* Scaffolding: sets the offsets of the file's string pool at lbl_803630C4. */
#pragma pool_strings on
void StringPool(const char** p) {
    p[0] = "";
    p[1] = "tree::insert length error";
}

static inline void lengthError(const char* msg) {
    fn_80290B48(&__files[2], msg);
    fn_80291BD0();
}
#pragma use_lmw_stmw on
Node* fn_8008B60C(Tree* t, Node* at, u8 left, u8 first, const u16* key) {
    if (t->size == 0xFFFFFFFF) {
        lengthError("tree::insert length error");
    }
    Node* n = allocNode();
    NodeGuard g(&t->root, n);
    new (&n->key) u16(*key);
    n->right = 0;
    g.p = 0;
    n->left = 0;
    new (&n->parent) u32((u32)at);
    if (left) at->left = n;
    else at->right = n;
    t->size++;
    fn_8008B9B8(n, t->root);
    if (first) t->first = n;
    return n;
}
#pragma use_lmw_stmw off
}
