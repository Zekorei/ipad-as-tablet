#include"pipeline/stages/subregion.h"
#include"math/vec2.h"

namespace Pipeline::Stages {
    Math::Vec2 Subregion::operator()(const Math::Vec2& point) {
        Math::Vec2 halfSubregion = config.subregionDimensions.toVec2().scale(0.5f);
        Math::Vec2 minSubregion = config.subregionCenter.toVec2() - halfSubregion;
        Math::Vec2 maxSubregion = config.subregionCenter.toVec2() + halfSubregion;

        // Clamp points outside of the active area to the edges
        Math::Vec2 scaled = point.clamp(minSubregion, maxSubregion);

        // Remap points to the unit square
        scaled = (scaled - minSubregion) / (maxSubregion - minSubregion);

        return scaled;
    }
}
