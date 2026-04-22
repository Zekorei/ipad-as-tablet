#include<algorithm>

#include"mapper.h"

Input::InputMapper::InputMapper(const InputMapConfig& config, const Common::ScreenInfo& screenInfo) {
    setConfig(config);
    setScreenMetrics(screenInfo);
}

void Input::InputMapper::setConfig(const InputMapConfig& config) {
    this->config = config;
}

void Input::InputMapper::setScreenMetrics(const Common::ScreenInfo& screenInfo) {
    this->screenInfo = screenInfo;
}

float Input::InputMapper::applyAspectRatio(float v, float center, float size) {
    if (!config.lockAspectRatio) {
        return v;
    }

    float half = size / 2.0f;
    float min = center - half;
    float max = center + half;

    v = std::clamp(v, min, max);

    return (v - min) / (max - min);
}

Common::NormalizedPoint Input::InputMapper::map(const Common::NormalizedPoint& point) {
#ifdef NDEBUG
    point.validate();
#endif

    float normX = point.x;
    float normY = point.y;

    // Apply aspect ratio adjustments
    normX = applyAspectRatio(normX, config.areaX, config.areaWidth);
    normY = applyAspectRatio(normY, config.areaY, config.areaHeight);

    // Apply sensitivity
    normX = (normX - 0.5f) * config.sensitivity + 0.5f;
    normY = (normY - 0.5f) * config.sensitivity + 0.5f;

    // Scale to screen coordinates
    LONG x = static_cast<LONG>(normX * screenInfo.width);
    LONG y = static_cast<LONG>(normY * screenInfo.height);

    Common::NormalizedPoint point{ static_cast<float>(x) / screenInfo.width, static_cast<float>(y) / screenInfo.height };

#ifdef NDEBUG
    point.validate();
#endif

    return point;
}
