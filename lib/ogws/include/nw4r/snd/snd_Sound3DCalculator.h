#ifndef NW4R_SND_SOUND_3D_CALCULATOR_H
#define NW4R_SND_SOUND_3D_CALCULATOR_H
#include <nw4r/types_nw4r.h>

#include <nw4r/math.h>

namespace nw4r {
namespace snd {

class Sound3DManager;
class Sound3DListener;
struct Sound3DParam;

// FE10: reference zeldaret/ss (no biquad filter yet)
class Sound3DCalculator {
public:
    struct CalcPanParam {
        f32 speakerAngleStereo;    // at 0x00
        f32 frontSpeakerAngleDpl2; // at 0x04
        f32 rearSpeakerAngleDpl2;  // at 0x08
        f32 initPan;               // at 0x0C

        CalcPanParam()
            : speakerAngleStereo(NW4R_MATH_PI / 4),
              frontSpeakerAngleDpl2(NW4R_MATH_PI / 6),
              rearSpeakerAngleDpl2(2 * NW4R_MATH_PI / 3),
              initPan(0.0f) {}
    };

    static void CalcVolumeAndPriority(const Sound3DManager&,
                                      const Sound3DListener&,
                                      const Sound3DParam&, f32*, int*);
    static void CalcPan(const Sound3DManager&, const Sound3DListener&,
                        const Sound3DParam&, const CalcPanParam&, f32* pPan,
                        f32* pSurroundPan);
    static void CalcPitch(const Sound3DManager&, const Sound3DListener&,
                          const Sound3DParam&, f32*);
    static void CalcPanDpl2(const math::VEC3&, f32, f32, f32, f32, f32, f32,
                            f32*, f32*);
    static void CalcPanStereo(const math::VEC3&, f32, f32, f32, f32, f32*,
                              f32*);
    static void CalcAngleAndDistance(const math::VEC3&, f32, f32, f32*, f32*);
};

} // namespace snd
} // namespace nw4r

#endif
