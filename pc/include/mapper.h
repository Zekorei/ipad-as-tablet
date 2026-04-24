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
        Common::NormalizedPoint subregionCenter{ 0.5f, 0.5f };      ///< Normalized center of the active area on the tablet [0.0, 1.0]
        Common::NormalizedPoint subregionDimensions{ 0.8f, 0.8f };  ///< Normalized width and height of the active area on the tablet [0.0, 1.0]

        float sensitivity = 1.0f;                                   ///< Sensitivity multiplier for input scaling (default 1.0)
        bool lockAspectRatio = true;                                ///< Lock the aspect ratio of the active area to match the output screen

        InputMapConfig() = default;

        /// @brief Standard constructor
        InputMapConfig(Common::NormalizedPoint center, Common::NormalizedPoint dimensions, 
            float sensitivity = 1.0f, bool lockAspectRatio = true) :
            subregionCenter(center), 
            subregionDimensions(dimensions),
            sensitivity(sensitivity),
            lockAspectRatio(lockAspectRatio) {}
    };

    /**
     * @brief Converts normalized tablet coordinates to screen coordinates with sensitivity and aspect ratio adjustments.
     */
    class InputMapper {
    public:
        InputMapper() = default;
    
        /// @brief Construct a new Input Mapper object with the given configuration and screen metrics
        InputMapper(const InputMapConfig& config, const Common::ScreenInfo& screenInfo);

        /// @brief Get the current mapping configuration
        InputMapConfig getConfig() const;

        /// @brief Set the mapping configuration parameters
        /// @param config Configuration for mapping behavior
        void setConfig(const InputMapConfig& config);

        /// @brief Get the current screen metrics used for mapping calculations
        Common::ScreenInfo getScreenInfo() const;

        /// @brief Set the screen metrics for mapping calculations
        /// @param screenInfo Screen metrics for mapping calculations
        void setScreenInfo(const Common::ScreenInfo& screenInfo);

        /**
         * @brief Map input coordinates to normalized absolute screen coordinates. Applies subregion scaling,
         * aspect ratio adjustments, and sensitivity scaling according to the given configuration `config`.
         * 
         * @param input Normalized input coordinates from the tablet (0.0 to 1.0)
         * @return Common::NormalizedPoint Normalized output coordinates for the screen (0.0 to 1.0) after mapping
         */
        Common::NormalizedPoint map(const Common::NormalizedPoint& point);

    private:
        InputMapConfig config;          ///< Configuration for mapping behavior
        Common::ScreenInfo screenInfo;  ///< Screen metrics for mapping calculations

        /**
         * @brief Scale a point within the active area described by config. Clamps points outside the
         * active area to the edges and scales points within the area to the unit interval.
         * 
         * @param point The input coordinates in the subregion.
         * @return Common::NormalizedPoint The scaled coordinates in the full normalized space.
         */
        Common::NormalizedPoint scaleSubregion(const Common::NormalizedPoint& point);

        /**
         * @brief Scale a point in the full normalized space according to the aspect ratio of the screen.
         * If the screen is wider, the x-axis is compressed by a factor of the aspect ratio.
         * If the screen is taller, the y-axis is compressed by a factor of the aspect ratio.
         * 
         * @param point The input coordinates in the full normalized space.
         * @return Common::NormalizedPoint The scaled coordinates after aspect ratio adjustment.
         */
        Common::NormalizedPoint scaleAspectRatio(const Common::NormalizedPoint& point);
    };
}
