#include <nw4r/snd.h>

namespace nw4r {
namespace snd {
namespace detail {

inline void BasicPlayer::InitParamSet() {
    mVolume = 1.0f;
    mPitch = 1.0f;
    mPan = 0.0f;
    mSurroundPan = 0.0f;
    mLpfFreq = 0.0f;
    mRemoteFilter = 0;
    mOutputLine = OUTPUT_LINE_MAIN;
    mMainOutVolume = 1.0f;
    mMainSend = 0.0f;
    mPanMode = PAN_MODE_DUAL;
    mPanCurve = PAN_CURVE_SQRT;

    for (int i = 0; i < AUX_BUS_NUM; i++) {
        mFxSend[i] = 0.0f;
    }

    for (int i = 0; i < WPAD_MAX_CONTROLLERS; i++) {
        mRemoteOutVolume[i] = 1.0f;
        mRemoteSend[i] = 0.0f;
        mRemoteFxSend[i] = 0.0f;
    }

    for (int i = 0; i < 4; i++) {
        mOutParam[i].volume = 1.0f;
        mOutParam[i].pitch = 1.0f;
        mOutParam[i].pan = 0.0f;
        mOutParam[i].surroundPan = 0.0f;
        mOutParam[i].fxSend = 0.0f;
        mOutParam[i].lpf = 0.0f;
    }
}

BasicPlayer::BasicPlayer() {
    // PlayerParamSet() { Init(); } of the later versions, then mId(INVALID_ID), then InitParam()
    InitParamSet();
    mId = BasicSound::INVALID_ID;
    InitParam();
}

void BasicPlayer::InitParam() {
    InitParamSet();
}

void BasicPlayer::SetFxSend(AuxBus bus, f32 send) {
    mFxSend[bus] = send;
}

f32 BasicPlayer::GetFxSend(AuxBus bus) const {
    return mFxSend[bus];
}

void BasicPlayer::SetRemoteOutVolume(int remote, f32 volume) {
    mRemoteOutVolume[remote] = volume;
}

f32 BasicPlayer::GetRemoteOutVolume(int remote) const {
    return mRemoteOutVolume[remote];
}

f32 BasicPlayer::GetRemoteSend(int remote) const {
    return mRemoteSend[remote];
}

f32 BasicPlayer::GetRemoteFxSend(int remote) const {
    return mRemoteFxSend[remote];
}

} // namespace detail
} // namespace snd
} // namespace nw4r
