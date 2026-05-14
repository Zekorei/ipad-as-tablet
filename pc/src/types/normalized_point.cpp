#include "types/normalized_point.h"
#include "math/vec2.h"

namespace Input::Pipeline {
    NormalizedPoint::NormalizedPoint(float x, float y) : x_(x), y_(y) {}

    NormalizedPoint NormalizedPoint::create(float x, float y) {
        if (x < norm_min || x > norm_max || y < norm_min || y > norm_max) {
            throw std::out_of_range("NormalizedPoint: values must be in [0, 1]");
        }
        return { x, y };
    }

    NormalizedPoint NormalizedPoint::create(float v) {
        return create(v, v);
    }

    NormalizedPoint NormalizedPoint::fromVec2(const Math::Vec2& p) {
        return create(p.x, p.y);
    }

    Math::Vec2 NormalizedPoint::toVec2() const {
        return { x_, y_ };
    }

    void NormalizedPoint::x(float v) {
        if (v < norm_min || v > norm_max) {
            throw std::out_of_range("NormalizedPoint: value must be in [0, 1]");
        }
        x_ = v;
    }

    void NormalizedPoint::y(float v) {
        if (v < norm_min || v > norm_max) {
            throw std::out_of_range("NormalizedPoint: value must be in [0, 1]");
        }
        y_ = v;
    }
}

