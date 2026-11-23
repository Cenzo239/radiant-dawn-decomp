/* Dispatch the low two state bits to the process transition. */
extern "C" {
struct State { unsigned char pad[0x34]; unsigned short flags; };
void fn_80083DC4(void*,int);
void fn_80101B50(State* p) {
 switch(p->flags & 3) {
 case 0: case 1: fn_80083DC4(p,1);break;
 case 2: fn_80083DC4(p,2);break;
 }
}
}
