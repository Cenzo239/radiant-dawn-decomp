// FE10: the newer NW4R StrmSound (reference zeldaret/ss, 8 tracks).
#include <nw4r/snd.h>
#include <nw4r/ut.h>

namespace nw4r {
namespace snd {
namespace detail {

NW4R_UT_RTTI_DEF_DERIVED(StrmSound, BasicSound);

StrmSound::StrmSound(SoundInstanceManager<StrmSound>* pManager, int priority,
                     int ambientPriority)
    : BasicSound(priority, ambientPriority),
      mTempSpecialHandle(NULL),
      mManager(pManager) {}

void StrmSound::InitParam() {
    BasicSound::InitParam();

    for (int i = 0; i < 8; i++) {
        mTrackVolume[i].InitValue(0.0f);
        mTrackVolume[i].SetTarget(1.0f, 1);
    }
}

StrmPlayer::SetupResult StrmSound::Setup(StrmBufferPool* pPool,
                                         int allocChannelCount,
                                         u16 allocTrackFlag) {
    InitParam();

    return mStrmPlayer.Setup(pPool, allocChannelCount, allocTrackFlag,
                             GetVoiceOutCount());
}

bool StrmSound::Prepare(StrmPlayer::StartOffsetType offsetType, s32 offset,
                        ut::FileStream* pStream) {
    bool result = mStrmPlayer.Prepare(pStream, offsetType, offset);
    if (!result) {
        mStrmPlayer.Shutdown();
        return false;
    }

    return true;
}

void StrmSound::UpdateMoveValue() {
    BasicSound::UpdateMoveValue();

    for (int i = 0; i < 8; i++) {
        if (mStrmPlayer.GetPlayerTrack(i) != NULL) {
            mTrackVolume[i].Update();
        }
    }
}

void StrmSound::UpdateParam() {
    BasicSound::UpdateParam();

    for (int i = 0; i < 8; i++) {
        if (mStrmPlayer.GetPlayerTrack(i) != NULL) {
            mStrmPlayer.SetTrackVolume(1 << i, mTrackVolume[i].GetValue());
        }
    }
}

void StrmSound::SetTrackVolume(u32 trackFlags, f32 volume, int fadeFrames) {
    ut::AutoInterruptLock lock;

    for (int i = 0; i < 8 && trackFlags != 0; i++, trackFlags >>= 1) {
        StrmPlayer::StrmTrack* pTrack = mStrmPlayer.GetPlayerTrack(i);

        if (pTrack != NULL && (trackFlags & 1)) {
            if (volume < 0.0f) {
                volume = 0.0f;
            }

            mTrackVolume[i].SetTarget(volume, fadeFrames);
        }
    }
}

void StrmSound::Shutdown() {
    BasicSound::Shutdown();
    mManager->Free(this);
}

void StrmSound::OnUpdatePlayerPriority() {
    mManager->UpdatePriority(this, CalcCurrentPlayerPriority());
}

bool StrmSound::IsAttachedTempSpecialHandle() {
    return mTempSpecialHandle != NULL;
}

void StrmSound::DetachTempSpecialHandle() {
    mTempSpecialHandle->DetachSound();
}

} // namespace detail
} // namespace snd
} // namespace nw4r
