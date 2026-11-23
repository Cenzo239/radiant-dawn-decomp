#include <nw4r/snd.h>
#include <nw4r/ut.h>

#include <climits>

// FE10 SoundPlayer: the newer NW4R version (locks the sound thread instead of
// an own mutex, sounds are allocated by SoundArchivePlayer). Reference:
// zeldaret/ss src/nw4r/snd/snd_SoundPlayer.cpp, without lpf/biquad/fx send.

namespace nw4r {
namespace snd {

SoundPlayer::SoundPlayer()
    : mOutputLineFlagEnable(false),
      mPlayableCount(1),
      mPlayableLimit(INT_MAX),
      mVolume(1.0f),
      mOutputLineFlag(OUTPUT_LINE_MAIN),
      mMainOutVolume(1.0f) {

    for (int i = 0; i < WPAD_MAX_CONTROLLERS; i++) {
        mRemoteOutVolume[i] = 1.0f;
    }
}

SoundPlayer::~SoundPlayer() {
    StopAllSound(0);
}

void SoundPlayer::Update() {
    detail::SoundThread::AutoLock lock;

    NW4R_UT_LINKLIST_FOREACH_SAFE (it, mSoundList, { it->Update(); })

    detail_SortPriorityList();
}

void SoundPlayer::StopAllSound(int frames) {
    detail::SoundThread::AutoLock lock;

    NW4R_UT_LINKLIST_FOREACH_SAFE (it, mSoundList, { it->Stop(frames); })
}

void SoundPlayer::PauseAllSound(bool flag, int frames) {
    detail::SoundThread::AutoLock lock;

    NW4R_UT_LINKLIST_FOREACH_SAFE (it, mSoundList,
                                   { it->Pause(flag, frames); })
}

void SoundPlayer::SetVolume(f32 volume) {
    mVolume = ut::Clamp(volume, 0.0f, 1.0f);
}

int SoundPlayer::detail_GetOutputLine() const {
    return mOutputLineFlag;
}

bool SoundPlayer::detail_IsEnabledOutputLine() const {
    return mOutputLineFlagEnable;
}

f32 SoundPlayer::detail_GetRemoteOutVolume(int idx) const {
    return mRemoteOutVolume[idx];
}

void SoundPlayer::detail_InsertSoundList(detail::BasicSound* pSound) {
    detail::SoundThread::AutoLock lock;

    mSoundList.PushBack(pSound);
    pSound->AttachSoundPlayer(this);
}

void SoundPlayer::RemoveSoundList(detail::BasicSound* pSound) {
    detail::SoundThread::AutoLock lock;

    mSoundList.Erase(pSound);
    pSound->DetachSoundPlayer(this);
}

void SoundPlayer::detail_InsertPriorityList(detail::BasicSound* pSound) {
    detail::SoundThread::AutoLock lock;

    detail::BasicSoundPlayerPrioList::Iterator it =
        mPriorityList.GetBeginIter();

    for (; it != mPriorityList.GetEndIter(); ++it) {
        if (pSound->CalcCurrentPlayerPriority() <
            it->CalcCurrentPlayerPriority()) {
            break;
        }
    }

    mPriorityList.Insert(it, pSound);
}

void SoundPlayer::detail_RemovePriorityList(detail::BasicSound* pSound) {
    detail::SoundThread::AutoLock lock;

    mPriorityList.Erase(pSound);
}

void SoundPlayer::detail_ChangePriority(detail::BasicSound* pSound) {
    detail_RemovePriorityList(pSound);
    detail_InsertPriorityList(pSound);
}

void SoundPlayer::detail_SortPriorityList() {
    detail::SoundThread::AutoLock lock;

    static detail::BasicSoundPlayerPrioList
        listsByPrio[detail::BasicSound::PRIORITY_MAX + 1];

    while (!mPriorityList.IsEmpty()) {
        detail::BasicSound& rSound = mPriorityList.GetFront();
        mPriorityList.PopFront();
        listsByPrio[rSound.CalcCurrentPlayerPriority()].PushBack(&rSound);
    }

    for (int i = 0; i < detail::BasicSound::PRIORITY_MAX + 1; i++) {
        while (!listsByPrio[i].IsEmpty()) {
            detail::BasicSound& rSound = listsByPrio[i].GetFront();
            listsByPrio[i].PopFront();
            mPriorityList.PushBack(&rSound);
        }
    }
}

bool SoundPlayer::detail_AppendSound(detail::BasicSound* pSound) {
    detail::SoundThread::AutoLock lock;

    int allocPriority = pSound->CalcCurrentPlayerPriority();

    if (GetPlayableSoundCount() == 0) {
        return false;
    }

    while (GetPlayingSoundCount() >= GetPlayableSoundCount()) {
        detail::BasicSound* pDropSound = detail_GetLowestPrioritySound();

        if (pDropSound == NULL) {
            return false;
        }

        if (allocPriority < pDropSound->CalcCurrentPlayerPriority()) {
            return false;
        }

        pDropSound->Shutdown();
    }

    mSoundList.PushBack(pSound);
    detail_InsertPriorityList(pSound);
    pSound->AttachSoundPlayer(this);

    return true;
}

void SoundPlayer::detail_RemoveSoundList(detail::BasicSound* pSound) {
    detail_RemovePriorityList(pSound);
    RemoveSoundList(pSound);
}

void SoundPlayer::SetPlayableSoundCount(int count) {
    detail::SoundThread::AutoLock lock;

    mPlayableCount = ut::Clamp(count, 0, mPlayableLimit);

    while (GetPlayingSoundCount() > GetPlayableSoundCount()) {
        detail::BasicSound* pDropSound = detail_GetLowestPrioritySound();
        pDropSound->Shutdown();
    }
}

void SoundPlayer::detail_SetPlayableSoundLimit(int limit) {
    mPlayableLimit = limit;
}

bool SoundPlayer::detail_CanPlaySound(int startPriority) {
    detail::SoundThread::AutoLock lock;

    if (GetPlayableSoundCount() == 0) {
        return false;
    }

    if (GetPlayingSoundCount() >= GetPlayableSoundCount()) {
        detail::BasicSound* pDropSound = detail_GetLowestPrioritySound();

        if (pDropSound == NULL) {
            return false;
        }

        if (startPriority < pDropSound->CalcCurrentPlayerPriority()) {
            return false;
        }
    }

    return true;
}

void SoundPlayer::detail_AppendPlayerHeap(detail::PlayerHeap* pHeap) {
    detail::SoundThread::AutoLock lock;

    pHeap->AttachSoundPlayer(this);
    mHeapList.PushBack(pHeap);
}

detail::PlayerHeap*
SoundPlayer::detail_AllocPlayerHeap(detail::BasicSound* pSound) {
    detail::SoundThread::AutoLock lock;

    if (mHeapList.IsEmpty()) {
        return NULL;
    }

    detail::PlayerHeap& rHeap = mHeapList.GetFront();
    mHeapList.PopFront();

    rHeap.AttachSound(pSound);
    pSound->AttachPlayerHeap(&rHeap);
    rHeap.Clear();

    return &rHeap;
}

void SoundPlayer::detail_FreePlayerHeap(detail::BasicSound* pSound) {
    detail::SoundThread::AutoLock lock;

    detail::PlayerHeap* pHeap = pSound->GetPlayerHeap();
    if (pHeap == NULL) {
        return;
    }

    pHeap->DetachSound(pSound);
    pSound->DetachPlayerHeap(pHeap);
    mHeapList.PushBack(pHeap);
}

} // namespace snd
} // namespace nw4r
