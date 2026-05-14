#include "input/pipeline/stages/clamp.h"
#include "types/normalized_point.h"

namespace Input::Pipeline::Stages {

    NormalizedPoint Clamp::operator()(const Math::Vec2& point) {
        Math::Vec2 normalized = point.clamp(Math::Vec2(norm_min), Math::Vec2(norm_max));

        return NormalizedPoint::fromVec2(normalized);
    }
}
