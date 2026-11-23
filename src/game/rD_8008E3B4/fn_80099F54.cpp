/* fn_80099F54: was a near miss. The local fixes the lbz destination register. */
#include "game/rD_8008E3B4/script.h"

extern "C" {

u8* fn_8024BC94(void);
int fn_802450BC(void* sys);
void fn_8024BA84(int v, void* p);

int fn_80099F54(void)
{
    u8* sys = fn_8024BC94();
    if (fn_802450BC(sys) != 0) {
        s8 v = sys[0x1bc9];
        fn_8024BA84(v, fn_8009E898());
    }
    setFlag1C(fn_800C3558());
    return 1;
}

}
