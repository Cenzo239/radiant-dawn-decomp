/* MSL-style red-black tree: free a subtree (plain recursion, inlined into itself three levels). */
#include "game/rJ_800799AC/types.h"
struct Node {
    Node* left;
    Node* right;
    u32 parent;
    u16 key;
};
struct Tree;
extern "C" {
void fn_80079210(void* p);
#pragma use_lmw_stmw on
#pragma inline_depth(3)
void fn_8008B730(Tree* t, Node* n) {
    if (n->left) fn_8008B730(t, n->left);
    if (n->right) fn_8008B730(t, n->right);
    fn_80079210(n);
}
#pragma use_lmw_stmw off
}
