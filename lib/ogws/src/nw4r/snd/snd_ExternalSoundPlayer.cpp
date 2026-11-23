#include <nw4r/snd.h>
#include <nw4r/ut.h>

namespace nw4r {
namespace snd {
namespace detail {

ExternalSoundPlayer::ExternalSoundPlayer() : mPlayableCount(1) {}

ExternalSoundPlayer::~ExternalSoundPlayer() {
    NW4R_UT_LINKLIST_FOREACH_SAFE (it, mSoundList,
                                   { it->DetachExternalSoundPlayer(this); })
}

void ExternalSoundPlayer::DetachSoundActorAll(nw4r::snd::SoundActor* pActor) {
    NW4R_UT_LINKLIST_FOREACH_SAFE (it, mSoundList,
                                   { it->DetachSoundActor(pActor); })
}

bool ExternalSoundPlayer::AppendSound(BasicSound* pSound) {
    SoundThread::AutoLock lock;

    int startPriority = pSound->CalcCurrentPlayerPriority();

    if (GetPlayableSoundCount() == 0) {
        return false;
    }

    while (GetPlayingSoundCount() >= GetPlayableSoundCount()) {
        BasicSound* pDropSound = GetLowestPrioritySound();

        if (pDropSound == NULL) {
            return false;
        }

        if (startPriority < pDropSound->CalcCurrentPlayerPriority()) {
            return false;
        }

        pDropSound->Shutdown();
    }

    mSoundList.PushBack(pSound);
    pSound->AttachExternalSoundPlayer(this);

    return true;
}

void ExternalSoundPlayer::SetPlayableSoundCount(int count) {
    mPlayableCount = count;

    while (GetPlayingSoundCount() > GetPlayableSoundCount()) {
        GetLowestPrioritySound()->Shutdown();
    }
}

void ExternalSoundPlayer::RemoveSound(BasicSound* pSound) {
    mSoundList.Erase(pSound);
    pSound->DetachExternalSoundPlayer(this);
}

bool ExternalSoundPlayer::detail_CanPlaySound(int startPriority) {
    if (GetPlayableSoundCount() == 0) {
        return false;
    }

    if (GetPlayingSoundCount() >= GetPlayableSoundCount()) {
        BasicSound* pDropSound = GetLowestPrioritySound();

        if (pDropSound == NULL) {
            return false;
        }

        if (startPriority < pDropSound->CalcCurrentPlayerPriority()) {
            return false;
        }
    }

    return true;
}

BasicSound* ExternalSoundPlayer::GetLowestPrioritySound() {
    int lowestPrio = BasicSound::PRIORITY_MAX + 1;
    BasicSound* pLowest = NULL;

    for (BasicSoundExtPlayList::Iterator it = mSoundList.GetBeginIter();
         it != mSoundList.GetEndIter(); ++it) {

        int priority = it->CalcCurrentPlayerPriority();

        if (lowestPrio > priority) {
            pLowest = &*it;
            lowestPrio = priority;
        }
    }

    return pLowest;
}

} // namespace detail
} // namespace snd
} // namespace nw4r
