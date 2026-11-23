#include <nw4r/ut.h>

namespace nw4r {
namespace ut {

NW4R_UT_RTTI_DEF_BASE(IOStream);

s32 IOStream::Write(const void* pSrc, u32 size) {
#pragma unused(pSrc)
#pragma unused(size)
    return 0;
}

bool IOStream::WriteAsync(const void* pSrc, u32 size, StreamCallback pCallback,
                          void* pCallbackArg) {
#pragma unused(pSrc)
#pragma unused(size)
#pragma unused(pCallback)
#pragma unused(pCallbackArg)
    return false;
}

} // namespace ut
} // namespace nw4r
