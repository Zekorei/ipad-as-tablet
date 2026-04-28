#pragma once

#include"math/vec2.h"
#include"config/pipeline_config.h"
#include"types/normalized_point.h"

namespace Pipeline::Stages {
    /**
     * @brief Clamping stage of the pipeline. No bindings.
     * 
     * Normalizes a point by clamping both components.
     */
    struct Clamp {
        /**
         * @brief Clamps each component to be within the interval `[0, 1]`.
         * 
         * @param point Input point
         * @return Common::NormalizedPoint Returns a point that is normalized by clamping
         */
        Common::NormalizedPoint operator()(const Math::Vec2& point);
    };
}
