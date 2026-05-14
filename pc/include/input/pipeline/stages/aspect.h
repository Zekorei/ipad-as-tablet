#pragma once

#include "config/screen_info.h"
#include "math/vec2.h"

namespace Input::Pipeline::Stages {

    /**
     * @brief The aspect ratio correction stage of the pipeline. Binds screen info data to get the aspect
     * ratio.
     * 
     * Scales a point in the full normalized space according to the aspect ratio of the output screen.
     */
    struct Aspect {
        Config::ScreenInfo screenInfo;
        
        /**
         * @brief Scale a point in the full normalized space according to the aspect ratio of the screen.
         * If the screen is wider, the x-axis is compressed by a factor of the aspect ratio.
         * If the screen is taller, the y-axis is compressed by a factor of the aspect ratio.
         * 
         * @param point The input coordinates in the full normalized space.
         * @return Math::Vec2 The scaled coordinates after aspect ratio adjustment.
         */
        Math::Vec2 operator()(const Math::Vec2& point);
    };
}
