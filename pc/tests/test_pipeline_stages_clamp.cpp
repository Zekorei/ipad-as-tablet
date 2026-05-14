#include "input/pipeline/stages/clamp.h"
#include <catch2/catch_test_macros.hpp>
#include "utils/test_utils.h"

#include "types/normalized_point.h"


using namespace Input::Pipeline::Stages;
using namespace Input::Pipeline;

TEST_CASE("bounds_are_enforced", "[clamp]") {
    Clamp clamp;

    NormalizedPoint p = clamp({ -1.0f, 2.0f });

    REQUIRE(p.x() == norm_min);
    REQUIRE(p.y() == norm_max);
}

TEST_CASE("inner_points_are_invariant", "[clamp]") {
    Clamp clamp;

    for (float x = norm_min; x <= norm_max; x += 0.1f) {
        for (float y = norm_min; y <= norm_max; y += 0.1f) {
            NormalizedPoint p = clamp({ x, y });

            REQUIRE(p.x() == x);
            REQUIRE(p.y() == y);
        }
    }
}
