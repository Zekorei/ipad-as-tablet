#pragma once

#include<windows.h>

namespace Common {

    /**
     * @brief Screen information including width and height in pixels. 
     */
    struct ScreenInfo {
        int width;  ///< Screen width in pixels
        int height; ///< Screen height in pixels

        /// @brief Default constructor that fetches screen metrics from the system.
        ScreenInfo() {
            width = GetSystemMetrics(SM_CXSCREEN);
            height = GetSystemMetrics(SM_CYSCREEN);
        }

        /**
         * @brief Construct screen info with specified width and height.
         */
        ScreenInfo(int w, int h) : width(w), height(h) {}

        /// @brief Get the aspect ratio of the screen (width / height).
        inline float aspectRatio() const {
            return static_cast<float>(width) / height;
        };
    };
}