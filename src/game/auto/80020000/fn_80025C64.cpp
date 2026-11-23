/* Check command availability. */
extern "C" {
extern char lbl_8037930C[];
extern unsigned int lbl_804CB700;
int fn_8004A70C(const char*);
void* fn_8024BC94();
int fn_802450BC(void*);
int fn_80025C64() {
 int r;
 if(fn_8004A70C(lbl_8037930C)) r=3;
 else if(lbl_804CB700 & 0x10) r=0;
 else { int v=fn_802450BC(fn_8024BC94()); r=2; if(v) r=0; }
 return r;
}
}
