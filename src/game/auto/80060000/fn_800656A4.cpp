/* Forward the child-process flag update when a child exists. */
struct O { unsigned char pad[0x48]; void* child; };
extern "C" {
void fn_8017AB5C(void*, int);
void fn_800656A4(O* o) { if (o->child) fn_8017AB5C(o->child, 1); }
}
