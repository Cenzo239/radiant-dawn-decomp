#include <nw4r/snd.h>

// FE10 only keeps these two out-of-line PlayerHeap members (0x802A7E30).

namespace nw4r {
namespace snd {
namespace detail {

void PlayerHeap::AttachSound(BasicSound* pSound) {
    mSound = pSound;
}

void PlayerHeap::DetachSound(BasicSound* pSound) {
#pragma unused(pSound)
    mSound = NULL;
}

} // namespace detail
} // namespace snd
} // namespace nw4r
