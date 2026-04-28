#include"pipeline/stages/subregion.h"
#include"math/vec2.h"

namespace Pipeline::Stages {
    Math::Vec2 Subregion::operator()(const Math::Vec2& point) {
        Math::Vec2 subregionCenter = config.subregionCenter.toVec2();
        Math::Vec2 subregionDimensions = config.subregionDimensions.toVec2();

        Math::Vec2 halfSubregion = subregionDimensions.scale(0.5f);
        Math::Vec2 minSubregion = subregionCenter - halfSubregion;
        Math::Vec2 maxSubregion = subregionCenter + halfSubregion;

        // Clamp points outside of the active area to the edges
        Math::Vec2 clamped = point.clamp(minSubregion, maxSubregion);

        // Remap points to the unit square linearly
        Math::Vec2 scaled = (clamped - subregionCenter) / subregionDimensions + Math::Vec2 { 0.5f };

        return scaled;
    }
}
