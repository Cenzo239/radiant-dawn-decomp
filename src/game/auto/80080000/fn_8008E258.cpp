/* Count linked units whose 0x8000 flag is set. */
extern "C" {
struct Unit { unsigned char pad[0xe8]; Unit* next; unsigned char pad2[0x10c-0xec]; unsigned int flags; };
struct List { unsigned char pad[0x48]; Unit* first; };
extern List* lbl_804CB814;
int fn_8008E258() { int n=0; for(Unit* u=lbl_804CB814->first;u;) { unsigned int f=u->flags; u=u->next; if(f & 0x8000ULL) ++n; }return n; }
}
