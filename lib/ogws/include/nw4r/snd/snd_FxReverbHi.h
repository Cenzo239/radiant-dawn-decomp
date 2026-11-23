#ifndef NW4R_SND_FX_REVERB_HI_H
#define NW4R_SND_FX_REVERB_HI_H
#include <nw4r/types_nw4r.h>

#include <nw4r/snd/snd_AxfxImpl.h>
#include <nw4r/snd/snd_FxBase.h>

#include <revolution/AXFX.h>

namespace nw4r {
namespace snd {

class FxReverbHi : public FxBase {
public:
    // FE10: AXFXReverbHiExp based
    struct ReverbHiParam {
        f32 preDelayTime;    // at 0x0
        f32 fusedTime;       // at 0x4
        f32 coloration;      // at 0x8
        f32 damping;         // at 0xC
        f32 crossTalk;       // at 0x10
        f32 outGain;         // at 0x14
        u32 earlyMode;       // at 0x18
        f32 preDelayTimeMax; // at 0x1C
        u32 fusedMode;       // at 0x20
        f32 earlyGain;       // at 0x24
        f32 fusedGain;       // at 0x28

        ReverbHiParam()
            : preDelayTime(0.02f), fusedTime(3.0f), coloration(0.6f),
              damping(0.4f), crossTalk(0.1f), outGain(1.0f), earlyMode(5),
              preDelayTimeMax(0.02f), fusedMode(0), earlyGain(0.0f),
              fusedGain(1.0f) {}
    };

public:
    FxReverbHi();

    virtual ~FxReverbHi() {
        Shutdown();
        ReleaseWorkBuffer();
    } // at 0x8

    virtual bool StartUp();  // at 0xC
    virtual void Shutdown(); // at 0x10

    virtual void UpdateBuffer(int channels, void** ppBuffer, u32 size,
                              SampleFormat format, f32 sampleRate,
                              OutputMode mode); // at 0x14

    virtual bool AssignWorkBuffer(void* pBuffer, u32 size); // at 0x18
    virtual void ReleaseWorkBuffer();                       // at 0x1C

    u32 GetRequiredMemSize();
    bool SetParam(const ReverbHiParam& rParam);

private:
    bool mIsActive;          // at 0xC (FE10)
    detail::AxfxImpl mImpl;  // at 0x10
    ReverbHiParam mParam;     // at 0x18
    AXFX_REVERBHI_EXP mAxfxParam; // at 0x44
};

} // namespace snd
} // namespace nw4r

#endif
