#include "input/pipeline/stages/aspect.h"
#include "math/vec2.h"

namespace Input::Pipeline::Stages {

    Math::Vec2 Aspect::operator()(const Math::Vec2& point) {
        float aspectRatio;
        auto corrected = point;

        if ((aspectRatio = screenInfo.aspectRatio()) > 1.0f) {
            // Wide screen - compress x-axis
            corrected.x = (corrected.x - 0.5f) / aspectRatio + 0.5f;
        } else {
            // Tall screen - compress y-axis
            corrected.y = (corrected.y - 0.5f) * aspectRatio + 0.5f;
        }

        return corrected;
    }
}
