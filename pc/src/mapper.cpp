#include<algorithm>

#include"mapper.h"

Input::InputMapper::InputMapper(const InputMapConfig& config, const Common::ScreenInfo& screenInfo) {
    setConfig(config);
    setScreenInfo(screenInfo);
}

Input::InputMapConfig Input::InputMapper::getConfig() const {
    return config;
}

void Input::InputMapper::setConfig(const InputMapConfig& newConfig) {
    config = newConfig;
}

Common::ScreenInfo Input::InputMapper::getScreenInfo() const {
    return screenInfo;
}

void Input::InputMapper::setScreenInfo(const Common::ScreenInfo& newScreenInfo) {
    screenInfo = newScreenInfo;
}

// private methods

Common::NormalizedPoint Input::InputMapper::scaleSubregion(const Common::NormalizedPoint& point) {
    auto scaled = point;

    Common::NormalizedPoint halfSubregion = config.subregionDimensions.scale(0.5f);
    Common::NormalizedPoint minSubregion = config.subregionCenter - halfSubregion;
    Common::NormalizedPoint maxSubregion = config.subregionCenter + halfSubregion;

    // Clamp points outside of the active area to the edges
    scaled.x = std::clamp(scaled.x, minSubregion.x, maxSubregion.x);
    scaled.y = std::clamp(scaled.y, minSubregion.y, maxSubregion.y);

    // Remap points to the unit square
    scaled = (scaled - minSubregion) / (maxSubregion - minSubregion);

    return scaled;
}

Common::NormalizedPoint Input::InputMapper::scaleAspectRatio(const Common::NormalizedPoint& point) {
    float aspectRatio;
    
    auto scaled = point;

    if ((aspectRatio = screenInfo.aspectRatio()) > 1.0f) {
        // Wide screen - compress x-axis
        scaled.x = (scaled.x - 0.5f) / aspectRatio + 0.5f;
    } else {
        // Tall screen - compress y-axis
        scaled.y = (scaled.y - 0.5f) * aspectRatio + 0.5f;
    }

    return scaled;
}

// public methods

Common::NormalizedPoint Input::InputMapper::map(const Common::NormalizedPoint& point) {
#ifndef NDEBUG
    point.validate();
#endif
    
    Common::NormalizedPoint scaledFullRegion = scaleSubregion(point);
    Common::NormalizedPoint scaledAspect = scaleAspectRatio(scaledFullRegion);
    Common::NormalizedPoint sensitivityCorrected = scaledAspect
                                                    .translate(-0.5f)
                                                    .scale(config.sensitivity)
                                                    .translate(0.5f);

    // Clamp points to [0, 1] after all transformations
    sensitivityCorrected.x = std::clamp(sensitivityCorrected.x, 0.0f, 1.0f);
    sensitivityCorrected.y = std::clamp(sensitivityCorrected.y, 0.0f, 1.0f);

#ifndef NDEBUG
    point.validate();
#endif

    return sensitivityCorrected;
}
