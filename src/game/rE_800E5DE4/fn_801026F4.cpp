/* Delete the process once its incremented timer exceeds the limit. */
struct Timer { unsigned char pad[0x34]; int elapsed; int pad38; int limit; };
extern "C" {
void fn_80083B78(void*);
void fn_801026F4(Timer* t) {
    if (++t->elapsed > t->limit) fn_80083B78(t);
}
}
