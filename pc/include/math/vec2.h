#pragma once

#include<algorithm>

namespace Math {

    /**
     * @brief A 2D vector class with basic arithmetic operations. This is a utility type used for
     * representing an arbitrary point in 2D real euclidean space. 
     * 
     * Note that all overloaded operations are performed pairwise. For scaling or translation like behaviour
     * see `scale(float)` and `translate(float)`.
     */
    struct Vec2 {
        float x, y; // The coordinates of the vector

        /// @brief Default constructor initializes values to zero.
        Vec2();

        /// @brief Construct a new Vec2 object with the given `x` and `y` coordinates.
        Vec2(float x, float y);

        /// @brief Construct a new Vec2 object with both `x` and `y` set to the same value `c`.
        Vec2(float c);

        Vec2 operator+(const Vec2& other) const {
            return { x + other.x, y + other.y };
        }

        Vec2 operator-(const Vec2& other) const {
            return { x - other.x, y - other.y };
        }

        Vec2 operator*(const Vec2& other) const {
            return { x * other.x, y * other.y };
        }

        Vec2 operator/(const Vec2& other) const {
            return { x / other.x, y / other.y };
        }

        /**
         * @brief Scales the vector by a real scalar value. Always performs multiplication.
         * 
         * @param scalar The value to scale by. To divide, multiply by the reciprocal.
         * @return Vec2 Returns the scaled vector.
         */
        Vec2 scale(float scalar) const;

        /**
         * @brief Translates the vector by a real scalar value. Always performs addition.
         * 
         * @param offset The offset to translate by. To subtract, use the additive inverse.
         * @return Vec2 Returns the translated vector.
         */
        Vec2 translate(float offset) const;

        /**
         * @brief Clamps the values pairwise to the minimum and maximum values by the 2D points `min` and `max`. 
         * 
         * @param min The pairwise upper bound for the point.
         * @param max The pairwise lower bound for the point.
         * 
         * @return Vec2 Returns a 2D point with the components no larger than `max` and no smaller than `min` pairwise.
         */
        inline Vec2 clamp(const Vec2& min, const Vec2& max) const;
    };
}
