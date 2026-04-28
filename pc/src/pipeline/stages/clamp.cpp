#include"pipeline/stages/clamp.h"
#include"types/normalized_point.h"

namespace Pipeline::Stages {
    Common::NormalizedPoint Clamp::operator()(const Math::Vec2& point) {
        Math::Vec2 normalized = point.clamp(Math::Vec2(Common::norm_min), Math::Vec2(Common::norm_max));

        return Common::NormalizedPoint::fromVec2(normalized);
    }
}
