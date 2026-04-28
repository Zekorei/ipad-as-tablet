#include"pipeline/stages/display.h"
#include"types/normalized_point.h"

#include<catch2/catch_test_macros.hpp>
#include"utils/test_utils.h"

TEST_CASE("edges_map_correctly", "[display]") {
    Pipeline::Stages::Display display;

    auto n1 = Common::NormalizedPoint::create(Common::norm_min);
    auto n2 = Common::NormalizedPoint::create(Common::norm_max);

    Common::ScreenPoint p1 = display(n1);
    Common::ScreenPoint p2 = display(n2);

    REQUIRE(p1.x() == Common::win_abs_mouse_min);
    REQUIRE(p1.y() == Common::win_abs_mouse_min);
    REQUIRE(p2.x() == Common::win_abs_mouse_max);
    REQUIRE(p2.y() == Common::win_abs_mouse_max);
}

TEST_CASE("normalized_points_map_within_boundaries", "[display]") {
    Pipeline::Stages::Display display;

    for (float x = Common::norm_min; x <= Common::norm_max; x += 0.1f) {
        for (float y = Common::norm_min; y <= Common::norm_max; y += 0.1f) {
            auto n = Common::NormalizedPoint::create(x, y);
            Common::ScreenPoint p = display(n);

            REQUIRE(p.x() <= Common::win_abs_mouse_max);
            REQUIRE(p.x() >= Common::win_abs_mouse_min);
            REQUIRE(p.y() <= Common::win_abs_mouse_max);
            REQUIRE(p.y() >= Common::win_abs_mouse_min);
        }
    }
}
