#include"math/vec2.h"

namespace Math {
    Vec2::Vec2() : x(0.0f), y(0.0f) {}

    Vec2::Vec2(float x, float y) : x(x), y(y) {}

    Vec2::Vec2(float v) : x(v), y(v) {}

    Vec2 Vec2::scale(float scalar) const {
        return { x * scalar, y * scalar };
    }

    Vec2 Vec2::translate(float offset) const {
        return { x + offset, y + offset };
    }

    inline Vec2 Vec2::clamp(const Vec2& min, const Vec2& max) const {
        return {
            std::clamp(x, min.x, max.x),
            std::clamp(y, min.y, max.y)
        };
    }
}
