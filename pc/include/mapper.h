#pragma once

#include<windows.h>

#include<types.h>

/**
 * @brief Input handling for mouse control.
 */
namespace Input {

    /**
     * @brief Configuration for tablet mapping, including screen metrics and coordinate transformations.
     */
    struct InputMapConfig {
        float areaX = 0.5f;             ///< Normalized X coordinate of the center of the active area on the tablet (0.0 to 1.0)
        float areaY = 0.5f;             ///< Normalized Y coordinate of the center of the active area on the tablet (0.0 to 1.0)
        float areaWidth = 0.6f;         ///< Width of normalized area on the tablet (0.0 to 1.0)
        float areaHeight = 0.6f;        ///< Height of normalized area on the tablet (0.0 to 1.0)

        float sensitivity = 1.0f;       ///< Sensitivity multiplier for input scaling (default 1.0)

        bool lockAspectRatio = true;   ///< Lock the aspect ratio of the active area to match the output screen
    };

    /**
     * @brief Converts normalized tablet coordinates to screen coordinates with sensitivity and aspect ratio adjustments.
     */
    class InputMapper {
    public:
        /// @brief Construct a new Input Mapper object with the given configuration and screen metrics
        InputMapper(const InputMapConfig& config, const Common::ScreenInfo& screenInfo);

        /// @brief Set the mapping configuration parameters
        /// @param config Configuration for mapping behavior
        void setConfig(const InputMapConfig& config);

        /// @brief Set the screen metrics for mapping calculations
        /// @param screenInfo Screen metrics for mapping calculations
        void setScreenMetrics(const Common::ScreenInfo& screenInfo);

        /**
         * @brief Map normalized input coordinates to absolute screen coordinates and apply sensitivity and 
         * aspect ratio adjustments.
         * 
         * @param input Normalized input coordinates from the tablet (0.0 to 1.0)
         * @return Common::NormalizedPoint Normalized output coordinates for the screen (0.0 to 1.0) after mapping
         */
        Common::NormalizedPoint map(const Common::NormalizedPoint& point);

    private:
        InputMapConfig config;          ///< Configuration for mapping behavior
        Common::ScreenInfo screenInfo;  ///< Screen metrics for mapping calculations

        float applyAspectRatio(float v, float center, float size);
    };
}
