#include <nw4r/lyt/bounding.h>
#include <nw4r/lyt/common.h>
#include <nw4r/lyt/drawInfo.h>

namespace nw4r {
    namespace lyt {
        NW4R_UT_GET_DERIVED_RUNTIME_TYPEINFO(Bounding, Pane);

        Bounding::Bounding(const res::Bounding* pBlock, const ResBlockSet&) : Pane(pBlock) {
        }

        Bounding::~Bounding() {
        }

        void Bounding::DrawSelf(const DrawInfo& drawInfo) {
            // FE10 nw4hbm keeps the debug frame
            if (drawInfo.IsDebugDrawMode()) {
                LoadMtx(drawInfo);
                detail::DrawLine(GetVtxPos(), mSize, ut::Color(0x00FF00FF));
            }
        }
    }  // namespace lyt
}  // namespace nw4r
