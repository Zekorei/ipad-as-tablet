#pragma once

#include"config/pipeline_config.h"
#include"math/vec2.h"

namespace Pipeline::Stages {

    /**
     * @brief The subregion mapping stage of the pipeline. Binds config to get the subregion settings.
     * 
     * Maps the subregion linearly to the full normalized space `[0, 1]`.
     */
    struct Subregion {
        Config::PipelineConfig config;

        /**
         * @brief Scale a point within the active area described by config. Clamps points outside the
         * active area to the edges and scales points within the area to the unit interval.
         * 
         * @param point The input coordinates in the subregion.
         * @return Math::Vec2 The scaled coordinates in the full normalized space.
         */
        Math::Vec2 operator()(const Math::Vec2& point);
    };
}
