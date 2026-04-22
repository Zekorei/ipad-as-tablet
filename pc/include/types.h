#pragma once

#include<cassert>

/**
 * @brief Common types and utilities for the project.
 */
namespace Common {

    /**
     * @brief Normalized point with x and y coordinates in the range `[0.0, 1.0]`.
     */
    struct NormalizedPoint {
        float x; ///< Normalized X coordinate (0.0 to 1.0)
        float y; ///< Normalized Y coordinate (0.0 to 1.0)

        /// @brief Validate that the coordinates are within the normalized range.
        void validate() const {
            assert(x >= 0.0f && x <= 1.0f);
            assert(y >= 0.0f && y <= 1.0f);
        }
    };

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

        /// @brief Get the aspect ratio of the screen (width / height).
        inline float aspectRatio() const {
            return static_cast<float>(width) / height;
        };
    };
}