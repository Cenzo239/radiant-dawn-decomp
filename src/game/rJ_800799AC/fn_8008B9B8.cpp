/* MSL-style red-black tree: rebalance after inserting x (the colour is bit 0 of the parent word, 1 = red).
 * Names follow the usual __tree_balance_after_insert shape; guessed. */
#include "game/rJ_800799AC/types.h"
struct Node {
    Node* left;
    Node* right;
    u32 pc;       /* parent pointer | colour */
    u16 key;
    Node* parent() const { return (Node*)(pc & ~1); }
    void setParent(Node* p) { pc = (u32)p | (pc & 1); }
    BOOL isRed() const { return (pc & 1) == 1; }
    void setRed() { pc |= 1; }
    void setBlack() { pc &= ~1; }
};
static inline void rotateLeft(Node* x, Node*& root) {
    Node* y = x->right;
    if (root == x) root = y;
    x->right = y->left;
    if (y->left) y->left->setParent(x);
    y->setParent(x->parent());
    if (x == x->parent()->left) x->parent()->left = y;
    else x->parent()->right = y;
    y->left = x;
    x->setParent(y);
}
static inline void rotateRight(Node* x, Node*& root) {
    Node* y = x->left;
    if (root == x) root = y;
    x->left = y->right;
    if (y->right) y->right->setParent(x);
    y->setParent(x->parent());
    if (x == x->parent()->left) x->parent()->left = y;
    else x->parent()->right = y;
    y->right = x;
    x->setParent(y);
}
extern "C" {
void fn_8008B9B8(Node* x, Node* root) {
    x->setRed();
    while (x != root && x->parent()->isRed()) {
        Node* g = x->parent()->parent();
        Node* l = g->left;
        if (x->parent() == l) {
            Node* y = g->right;
            if (y != 0 && y->isRed()) {
                x->parent()->setBlack();
                y->setBlack();
                x = x->parent()->parent();
                x->setRed();
            } else {
                if (x == x->parent()->right) {
                    x = x->parent();
                    rotateLeft(x, root);
                }
                x->parent()->setBlack();
                x->parent()->parent()->setRed();
                rotateRight(x->parent()->parent(), root);
            }
        } else {
            Node* y = l;
            if (y != 0 && y->isRed()) {
                x->parent()->setBlack();
                y->setBlack();
                x = x->parent()->parent();
                x->setRed();
            } else {
                if (x == x->parent()->left) {
                    x = x->parent();
                    rotateRight(x, root);
                }
                x->parent()->setBlack();
                x->parent()->parent()->setRed();
                rotateLeft(x->parent()->parent(), root);
            }
        }
    }
    root->setBlack();
}
}
