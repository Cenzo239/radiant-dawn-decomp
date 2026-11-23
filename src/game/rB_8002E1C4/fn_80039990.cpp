#include "game/rB_8002E1C4/types.h"

/* C++: the virtual call needs real class syntax to load the vtable into r12. */
struct Visitor {
    virtual void visit(void* item);
};
struct Holder39990 {
    u8 pad[0xf8];
    void* xf8;
};

extern "C" void fn_80039990(Visitor* v, Holder39990* h)
{
    if (h->xf8 != 0) v->visit(h->xf8);
}
