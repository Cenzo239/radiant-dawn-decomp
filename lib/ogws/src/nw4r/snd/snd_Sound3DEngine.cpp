// FE10: reference zeldaret/ss (no pitch/biquad flags from the sound yet).
#include <nw4r/snd.h>
#include <nw4r/snd/snd_Sound3DCalculator.h>
#include <nw4r/snd/snd_Sound3DEngine.h>
#include <nw4r/snd/snd_Sound3DListener.h>
#include <nw4r/snd/snd_Sound3DManager.h>

namespace nw4r {
namespace snd {

Sound3DEngine::Sound3DEngine() {}

void Sound3DEngine::UpdateAmbientParam(const Sound3DManager* pMgr,
                                       const Sound3DParam* pParam, u32 id,
                                       u32 flags,
                                       SoundAmbientParam* pAmbientParam) {
#pragma unused(id)

    if (flags & 1) {
        pAmbientParam->volume = 0.0f;
    }

    if (flags & 8) {
        pAmbientParam->priority = -pMgr->GetMaxPriorityReduction();
    }

    if (pMgr->GetListenerList().GetSize() != 1) {
        flags &= ~0x16;
    }

    NW4R_UT_LINKLIST_FOREACH(it, pMgr->GetListenerList(), {
        const Sound3DListener& rListener = *it;

        if (flags & 9) {
            f32 volume;
            int priority;
            Sound3DCalculator::CalcVolumeAndPriority(*pMgr, rListener, *pParam,
                                                     &volume, &priority);
            if (flags & 1) {
                pAmbientParam->volume =
                    ut::Max(volume, pAmbientParam->volume);
            }

            if (flags & 8) {
                pAmbientParam->priority =
                    ut::Max(priority, pAmbientParam->priority);
            }
        }

        if (flags & 6) {
            f32 pan, surroundPan;
            Sound3DCalculator::CalcPan(*pMgr, rListener, *pParam, mPanParam,
                                       &pan, &surroundPan);
            if (flags & 2) {
                pAmbientParam->pan = pan;
            }
            if (flags & 4) {
                pAmbientParam->surroundPan = surroundPan;
            }
        }

        if (flags & 0x10) {
            f32 pitch;
            Sound3DCalculator::CalcPitch(*pMgr, rListener, *pParam, &pitch);
            pAmbientParam->pitch = pitch;
        }
    })
}

void Sound3DEngine::UpdateAmbientParam(const Sound3DManager* pMgr,
                                       const Sound3DParam* pParam, u32 id,
                                       int voiceOutCount,
                                       SoundAmbientParam* pAmbientParam) {
#pragma unused(voiceOutCount)

    u32 flags = 0x1F;
    if (pParam->flags & 1) {
        flags &= ~1;
    }
    if (pParam->flags & 2) {
        flags &= ~2;
    }
    if (pParam->flags & 4) {
        flags &= ~4;
    }
    if (pParam->flags & 8) {
        flags &= ~8;
    }
    if (!pParam->field_0x1E) {
        flags &= ~0x10;
    }

    UpdateAmbientParam(pMgr, pParam, id, flags, pAmbientParam);
}

int Sound3DEngine::GetAmbientPriority(const Sound3DManager* pMgr,
                                      const Sound3DParam* pParam, u32 id) {
    u32 flags = 0x1000008;
    if (pParam->flags & 8) {
        flags &= ~8;
    }

    SoundAmbientParam ambientParam;
    UpdateAmbientParam(pMgr, pParam, id, flags, &ambientParam);
    return ambientParam.priority;
}

int Sound3DEngine::GetRequiredVoiceOutCount(const Sound3DManager* pMgr,
                                            const Sound3DParam* pParam,
                                            u32 id) {
#pragma unused(pMgr)
#pragma unused(pParam)
#pragma unused(id)

    return 1;
}

} // namespace snd
} // namespace nw4r
