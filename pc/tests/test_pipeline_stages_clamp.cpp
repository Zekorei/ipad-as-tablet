#include"pipeline/stages/clamp.h"
#include"types/normalized_point.h"

#include<catch2/catch_test_macros.hpp>
#include"utils/test_utils.h"

TEST_CASE("bounds_are_enforced", "[clamp]") {
    Pipeline::Stages::Clamp clamp;

    Common::NormalizedPoint p = clamp({ -1.0f, 2.0f });

    REQUIRE(p.x() == Common::norm_min);
    REQUIRE(p.y() == Common::norm_max);
}

TEST_CASE("inner_points_are_invariant", "[clamp]") {
    Pipeline::Stages::Clamp clamp;

    for (float x = Common::norm_min; x <= Common::norm_max; x += 0.1f) {
        for (float y = Common::norm_min; y <= Common::norm_max; y += 0.1f) {
            Common::NormalizedPoint p = clamp({ x, y });

            REQUIRE(p.x() == x);
            REQUIRE(p.y() == y);
        }
    }
}
