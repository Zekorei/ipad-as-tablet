#include "pipeline/stages/display.h"
#include <catch2/catch_test_macros.hpp>
#include "utils/test_utils.h"

#include "types/normalized_point.h"


using namespace Input::Pipeline::Stages;
using namespace Input::Pipeline;

TEST_CASE("edges_map_correctly", "[display]") {
    Display display;

    auto n1 = NormalizedPoint::create(norm_min);
    auto n2 = NormalizedPoint::create(norm_max);

    Output::ScreenPoint p1 = display(n1);
    Output::ScreenPoint p2 = display(n2);

    REQUIRE(p1.x() == Output::win_abs_mouse_min);
    REQUIRE(p1.y() == Output::win_abs_mouse_min);
    REQUIRE(p2.x() == Output::win_abs_mouse_max);
    REQUIRE(p2.y() == Output::win_abs_mouse_max);
}

TEST_CASE("normalized_points_map_within_boundaries", "[display]") {
    Display display;

    for (float x = norm_min; x <= norm_max; x += 0.1f) {
        for (float y = norm_min; y <= norm_max; y += 0.1f) {
            auto n = NormalizedPoint::create(x, y);
            Output::ScreenPoint p = display(n);

            REQUIRE(p.x() >= Output::win_abs_mouse_min);
            REQUIRE(p.x() <= Output::win_abs_mouse_max);
            REQUIRE(p.y() <= Output::win_abs_mouse_max);
            REQUIRE(p.y() >= Output::win_abs_mouse_min);
        }
    }
}
