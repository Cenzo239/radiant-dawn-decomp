#include "game/rF_8017F400/types.h"

#pragma auto_inline off

extern "C" {

extern void fn_80185A10(void* p, int mode);
extern void fn_80251838(f32 vol, int ch, const char* name); /* play BGM */
extern const char lbl_8036BCAC[]; /* "BGM_EVT_CLASS_CH..." */
extern const f32 lbl_804CE768;    /* 0.0f */
extern void fn_8023FC00(void);

/* sound-channel object (C++ class, vtable at +0) */
class SoundChan {
public:
    virtual void v08();
    virtual void v0C();
    virtual BOOL isPlaying();        /* vtable +0x10 */
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void fadeOut(int ms);    /* vtable +0x24 */
};
extern SoundChan* fn_8024F3FC(int ch);

void fn_80185C7C(void* p)
{
    fn_80185A10(p, 0);
}

void fn_80185C84(void* p)
{
    fn_80185A10(p, 1);
}

void fn_80185C8C(void)
{
    fn_80251838(lbl_804CE768, 3, lbl_8036BCAC);
}

/* fade out BGM channel 3 over 1s */
void fn_80185CA0(void)
{
    SoundChan* c = fn_8024F3FC(3);
    if (c != NULL && c->isPlaying()) {
        c->fadeOut(1000);
    }
}

void fn_80185D08(void)
{
    fn_8023FC00();
}

}
