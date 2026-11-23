/* Refuse the command for a disabled entry, otherwise forward its value. */
extern "C" {
struct R { unsigned char pad[0x18]; void* p; };
#if TARGET_PC
FE10_PROTO R* fn_800D569C(p32arg);
#else
R* fn_800D569C(int);
#endif
void fn_801B39C4(void*);
int fn_80025EA4(void*,int id,unsigned char* entry) {
 if(entry[0x39]) return 0x10;
 fn_801B39C4(fn_800D569C(id)->p);
 return 5;
}
}
