#pragma once

#include<cassert>
#include<stdexcept>

#include"math/vec2.h"

namespace Common {

    inline constexpr float norm_min = 0.0f; // max value for a normalized value
    inline constexpr float norm_max = 1.0f; // min value for a normalized value

    /**
     * @brief Normalized point with x and y coordinates in the range `[0.0, 1.0]`.
     */
    struct NormalizedPoint {
    private:
        float x_; ///< Normalized X coordinate
        float y_; ///< Normalized Y coordinate

        NormalizedPoint(float x, float y);

    public:
        /**
         * @brief Constructs a `NormalizedPoint` with bounds checking. Values are in the range `[0.0. 1.0]`.
         * 
         * @param x X coordinates of the point. Expected to be in the valid range.
         * @param y Y coordinates of the point. Expected to be in the valid range.
         * @throws out_of_bounds Throws out of bounds if either `x` or `y` are invalid.
         * @return NormalizedPoint Returns the normalized point.
         */
        static NormalizedPoint create(float x, float y);

        /**
         * @brief Construcs a `NormalizedPoint` with both values initialized to the same. Delegates
         * responsibility to the more general constructor `create(float, float)`.
         * 
         * @param v Both coordinates of the point.
         * @return NormalizedPoint Returns the normalized point.
         */
        static NormalizedPoint create(float v);

        /**
         * @brief Constructs a `NormalizedPoint` from a `Vec2` object. Delegates responsibility to `create()`.
         */
        static NormalizedPoint fromVec2(const Math::Vec2& p);

        /**
         * @brief Converts the `NormalizedPoint` to a `Vec2` representation.
         */
        Math::Vec2 toVec2() const;

        float x() const { return x_; }
        float y() const { return y_; }

        void x(float v);
        void y(float v);
    };
}
