#pragma once

#include"types/normalized_point.h"
#include"types/screen_point.h"

namespace Pipeline::Stages {

    /**
     * @brief The display mapping stage of the pipeline. No binding.
     * 
     * Converts a normalized to absolute Windows mouse coordinates.
     */
    struct Display {

        /**
         * @brief Computes the Windows absolute mouse coordinates from a normalized screen point.
         * 
         * @param point The normalized point.
         * @return Common::ScreenPoint Returns the corresponding Windows absolute mouse coordinates.
         */
        Common::ScreenPoint operator()(Common::NormalizedPoint point);
    };
}
