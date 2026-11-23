#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
class V {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13();
};
extern "C" {
V *fn_8007B594(int);
void fn_8009AA1C(int i) {
    fn_8007B594(i)->s13();
}
}
