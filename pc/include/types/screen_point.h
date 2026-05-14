#pragma once

#include<windows.h>

#include"normalized_point.h"

namespace Output {

    inline constexpr LONG win_abs_mouse_max = 65535L;   // max size of Windows absolute mouse coordinates
    inline constexpr LONG win_abs_mouse_min = 0L;       // min size of Windows absolute mouse coordinates

    /**
     * @brief A point representing a position on the screen by Windows absolute mouse coordinates
     */
    struct ScreenPoint {
    private:
        LONG x_; ///< Windows convention X coordinate
        LONG y_; ///< Windows convention Y coordinate

        ScreenPoint(LONG x, LONG y);

    public:

        /**
         * @brief Constructs a `ScreenPoint` with bounds checking. Values are in the range `[0, 65535]`.
         * 
         * @param x X coordinates of the point. Expected to be in the valid range.
         * @param y Y coordinates of the point. Expected to be in the valid range.
         * @throws out_of_bounds Throws out of bounds if either `x` or `y` are invalid.
         * @return ScreenPoint Returns the normalized point.
         */
        static ScreenPoint create(LONG x, LONG y);

        /**
         * @brief Constructs a `ScreenPoint` from a normalized point. Delegates responsibility to `create`.
         * 
         * @param normed Normalized point to conver.
         * @return ScreenPoint Returns the equivalent converted point.
         */
        static ScreenPoint fromNormalized(const Input::Pipeline::NormalizedPoint& normed);

        LONG x() const;
        LONG y() const;

        void x(LONG v);
        void y(LONG v);
    };
}
