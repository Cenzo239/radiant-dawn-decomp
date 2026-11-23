// Create the process with a normal call and return, as in the original.
#pragma push
#pragma optimize_tail_call off
extern "C" {
extern unsigned char lbl_80392D50[];
void* fn_80081194(void*, void*);

void fn_802889AC(void* parent) {
    fn_80081194(lbl_80392D50, parent);
}
}
#pragma pop
