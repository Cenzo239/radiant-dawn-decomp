#ifndef NW4R_SND_STRM_SOUND_H
#define NW4R_SND_STRM_SOUND_H
#include <nw4r/types_nw4r.h>

#include <nw4r/snd/snd_BasicSound.h>
#include <nw4r/snd/snd_MoveValue.h>
#include <nw4r/snd/snd_StrmPlayer.h>

#include <nw4r/ut.h>

namespace nw4r {
namespace snd {

// Forward declarations
class StrmSoundHandle;

namespace detail {
template <typename T> class SoundInstanceManager;
class StrmBufferPool;
} // namespace detail

namespace detail {

class StrmSound : public BasicSound {
    friend class nw4r::snd::StrmSoundHandle;

public:
    NW4R_UT_RTTI_DECL(StrmSound);

public:
    StrmSound(SoundInstanceManager<StrmSound>* pManager, int priority,
              int ambientPriority);

    virtual void Shutdown(); // at 0x10
    virtual bool IsPrepared() const {
        return mStrmPlayer.IsPrepared();
    } // at 0x14

    virtual bool IsAttachedTempSpecialHandle(); // at 0x18
    virtual void DetachTempSpecialHandle();     // at 0x1C

    virtual void InitParam(); // at 0x20

    virtual BasicPlayer& GetBasicPlayer() {
        return mStrmPlayer;
    } // at 0x24
    virtual const BasicPlayer& GetBasicPlayer() const {
        return mStrmPlayer;
    } // at 0x28

    virtual void OnUpdatePlayerPriority(); // at 0x2C
    virtual void UpdateMoveValue();        // at 0x30
    virtual void UpdateParam();            // at 0x34

    // FE10 (newer NW4R, see zeldaret/ss): buffers are set up before Prepare
    StrmPlayer::SetupResult Setup(StrmBufferPool* pPool, int allocChannelCount,
                                  u16 allocTrackFlag);
    bool Prepare(StrmPlayer::StartOffsetType offsetType, s32 offset,
                 ut::FileStream* pStream);

    void SetTrackVolume(u32 trackFlags, f32 volume, int fadeFrames);

    void* GetFileStreamBuffer() {
        return mFileStreamBuffer;
    }
    s32 GetFileStreamBufferSize() {
        return sizeof(mFileStreamBuffer);
    }

private:
    static const int FILE_STREAM_BUFFER_SIZE = 512;

private:
    StrmPlayer mStrmPlayer;                                     // at 0xFC
    StrmSoundHandle* mTempSpecialHandle;                        // at 0xE64
    SoundInstanceManager<StrmSound>* mManager;                  // at 0xE68
    MoveValue<f32, int> mTrackVolume[8];            // at 0xE6C
    ut::FileStream* mFileStream;                                // at 0xEEC
    char mFileStreamBuffer[FILE_STREAM_BUFFER_SIZE];            // at 0xEF0
};

} // namespace detail
} // namespace snd
} // namespace nw4r

#endif
