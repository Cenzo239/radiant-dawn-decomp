#ifndef NW4R_SND_SOUND_3D_ENGINE_H
#define NW4R_SND_SOUND_3D_ENGINE_H
#include <nw4r/types_nw4r.h>

#include <nw4r/snd/snd_Sound3DCalculator.h>

namespace nw4r {
namespace snd {

class Sound3DManager;
struct Sound3DParam;
struct SoundAmbientParam;

// FE10: reference zeldaret/ss
class Sound3DEngine {
public:
    Sound3DEngine();
    virtual ~Sound3DEngine() {} // at 0x8

    virtual void UpdateAmbientParam(const Sound3DManager*, const Sound3DParam*,
                                    u32, int, SoundAmbientParam*); // at 0xC
    virtual int GetAmbientPriority(const Sound3DManager*, const Sound3DParam*,
                                   u32); // at 0x10
    virtual int GetRequiredVoiceOutCount(const Sound3DManager*,
                                         const Sound3DParam*, u32); // at 0x14
    virtual void UpdateAmbientParam(const Sound3DManager*, const Sound3DParam*,
                                    u32, u32 flags,
                                    SoundAmbientParam*); // at 0x18

private:
    Sound3DCalculator::CalcPanParam mPanParam; // at 0x04
};

} // namespace snd
} // namespace nw4r

#endif
