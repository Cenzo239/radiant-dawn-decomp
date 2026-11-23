// FE10: the Sound3DEngine generation of Sound3DListener (see zeldaret/ss).
#include <nw4r/snd.h>
#include <nw4r/snd/snd_Sound3DListener.h>

namespace nw4r {
namespace snd {

Sound3DListener::Sound3DListener()
    : mVelocity(0.0f, 0.0f, 0.0f),
      mInteriorSize(1.0f),
      mMaxVolumeDistance(1.0f),
      mUnitDistance(1.0f),
      mUserParam(0),
      mSkipVelocityUpdate(true) {
    math::MTX34Zero(&mMtx);
}

void Sound3DListener::SetMatrix(const math::MTX34& rMtx) {
    static math::VEC3 zero(0.0f, 0.0f, 0.0f);

    if (mSkipVelocityUpdate) {
        mMtx = rMtx;
        mSkipVelocityUpdate = false;
    } else {
        math::VEC3 prevPos, curPos;
        math::VEC3Transform(&prevPos, &mMtx, &zero);
        mMtx = rMtx;
        math::VEC3Transform(&curPos, &rMtx, &zero);
        math::VEC3Sub(&mVelocity, &curPos, &prevPos);
        mVelocity = -mVelocity;
    }
}

void Sound3DListener::SetInteriorSize(f32 size) {
    mInteriorSize = size;
}

void Sound3DListener::SetMaxVolumeDistance(f32 distance) {
    mMaxVolumeDistance = distance;
}

void Sound3DListener::SetUnitDistance(f32 distance) {
    mUnitDistance = distance;
}

} // namespace snd
} // namespace nw4r
