#ifndef NW4R_SND_SOUND_3D_LISTENER_H
#define NW4R_SND_SOUND_3D_LISTENER_H
#include <nw4r/types_nw4r.h>

#include <nw4r/math.h>
#include <nw4r/ut/ut_LinkList.h>

namespace nw4r {
namespace snd {

// FE10: listener of the Sound3DEngine generation (between ogws and zeldaret/ss),
// 0x58 bytes: velocity instead of position, no biquad filter values.
class Sound3DListener {
public:
    Sound3DListener();

    const math::MTX34& GetMatrix() const {
        return mMtx;
    }
    void SetMatrix(const math::MTX34& rMtx);

    const math::VEC3& GetVelocity() const {
        return mVelocity;
    }

    f32 GetInteriorSize() const {
        return mInteriorSize;
    }
    void SetInteriorSize(f32 size);

    f32 GetMaxVolumeDistance() const {
        return mMaxVolumeDistance;
    }
    void SetMaxVolumeDistance(f32 distance);

    f32 GetUnitDistance() const {
        return mUnitDistance;
    }
    void SetUnitDistance(f32 distance);

private:
    math::MTX34 mMtx;           // at 0x0
    math::VEC3 mVelocity;       // at 0x30
    f32 mInteriorSize;          // at 0x3C
    f32 mMaxVolumeDistance;     // at 0x40
    f32 mUnitDistance;          // at 0x44
    u32 mUserParam;             // at 0x48
    u8 mSkipVelocityUpdate;     // at 0x4C

public:
    ut::LinkListNode mNode;     // at 0x50
};

} // namespace snd
} // namespace nw4r

#endif
