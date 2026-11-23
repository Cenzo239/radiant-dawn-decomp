#include "game/rF_8017F400/types.h"
#pragma auto_inline off
extern "C" {
/* std::advance on a list iterator */
struct LNode { LNode* prev; LNode* next; void* val; };
void fn_801B46B4(LNode** it, int n) {
    if (n >= 0) {
        for (int k = n; k > 0; k--) *it = (*it)->next;
    } else {
        for (int k = n; k < 0; k++) *it = (*it)->prev;
    }
}
}
