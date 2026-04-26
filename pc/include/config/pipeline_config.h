#pragma once

#include"types/normalized_point.h"

/**
 * @brief Config structs for specific settings and options.
 */
namespace Config {

    inline constexpr float default_subregion_center = 0.5f;
    inline constexpr float default_subregion_dimensions = 1.0f;
    inline constexpr float default_sensitivity = 1.0f;

    /**
     * @brief Configuration for normalized input to screen mapping. Primarily describes the active area on the tablet 
     * by the center and dimensions. Also contains the sensitivity factor for inputs
     * 
     */
    struct PipelineConfig {
        Common::NormalizedPoint subregionCenter;        ///< Normalized center of the active area on the tablet `[0.0, 1.0]`.
        Common::NormalizedPoint subregionDimensions;    ///< Normalized dimensions of the active area on the tablet.

        float sensitivity;                              ///< Sensitivity multiplier for input scaling

        /// @brief Default constructor. Assumes the subregion is the full normalized area and no sensitivity correction.
        PipelineConfig();

        /// @brief Parameterized constructor.
        PipelineConfig(Common::NormalizedPoint center, Common::NormalizedPoint dimensions, float sensitivity);
    };
}