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

        inline NormalizedPoint operator+(NormalizedPoint other) const {
            return { x + other.x, y + other.y };
        }

        inline NormalizedPoint operator-(NormalizedPoint other) const {
            return { x - other.x, y - other.y };
        }

        inline NormalizedPoint operator/(NormalizedPoint other) const {
            return { x / other.x, y / other.y };
        }

        inline NormalizedPoint scale(float scalar) const {
            return { x * scalar, y * scalar };
        }

        inline NormalizedPoint translate(float offset) const {
            return { x + offset, y + offset };
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