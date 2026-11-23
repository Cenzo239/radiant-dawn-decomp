/* String command wrappers and log-entry replacement. */
extern "C" {
struct Result { unsigned char pad[0x18]; void* value; };
#if TARGET_PC
FE10_PROTO Result* fn_800D569C(p32arg);
#else
Result* fn_800D569C(int);
#endif
void fn_801911D4(void*);
void fn_801BA1C8(int,void*);
extern unsigned char lbl_803CAB38[];
int fn_80025C20(void*,int id) { fn_801911D4(fn_800D569C(id)->value); return 5; }
int fn_80025F34(void*,int id) { Result* r=fn_800D569C(id); fn_801BA1C8(lbl_803CAB38[0x11],r->value); return 5; }
struct Entry { unsigned char code, pad; short value; };
struct Log { int unk; Entry entries[1]; };
int fn_80026324(Log* log, unsigned int code, int replacement, int value) {
 Entry* p=log->entries; int result=-1; int i=0;
 for (;;p++,i++) { if (!p->code) return result; if(code==p->code) {p->code=replacement;result=i;p->value=value;} }
 return result;
}
}
