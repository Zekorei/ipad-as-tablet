#pragma once

#include<cmath>

namespace TestUtils {

    /**
     * @brief Approximate equality check for floating-point values, with a default tolerance of 1e-5.
     * 
     * @param a First value
     * @param b Second value
     * @param epsilon Error tolerance for comparison
     * @return true if and only if `a` and `b` are within the given `epsilon` tolerance of each other. \\
     * @return false otherwise.
     */
    inline bool approx(float a, float b, float epsilon = 1e-5f) {
        return std::fabs(a - b) < epsilon;
    }

    /**
     * @brief Approximate equality check for `long` values representing an absolute Windows mouse coordinate.
     * Default tolerance is one unit.
     * 
     * @param a First value
     * @param b Second value
     * @param epsilon Error tolerance for comparison
     * @return true if and only if `a` and `b` are within the given `epsilon` tolerance of each other. \\
     * @return false otherwise.
     */
    inline bool screenApprox(long a, long b, float epsilon = 1) {
        return std::labs(a - b) <= epsilon;
    }
}
