extern "C" {
extern void* lbl_8038C294[13];
void fn_80079210(void*);

// Only the virtual slots used to reproduce the dispatch layout are named here.
// CodeWarrior reserves the first two vtable entries before these methods.
struct Object {
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
};

// Restore this class's vtable, dispatch cleanup, then optionally free storage.
Object* fn_8008D6E8(Object* object, int deleting) {
    if (object) {
        *(void***)object = lbl_8038C294;
        object->slot2();
        if (deleting > 0) {
            fn_80079210(object);
        }
    }
    return object;
}
}
