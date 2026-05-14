#include "pipeline/stages/subregion.h"
#include <catch2/catch_test_macros.hpp>
#include "utils/test_utils.h"

#include "types/normalized_point.h"


using namespace Input::Pipeline::Stages;
using namespace Input::Pipeline;

TEST_CASE("center_is_invariant", "[subregion]") {
    Subregion subregion;

    auto dim = NormalizedPoint::create(1.0f);

    for (float x = norm_min; x <= norm_max; x += 0.2f) {
        for (float y = norm_min; y <= norm_max; y += 0.2f) {
            auto center = NormalizedPoint::create(x, y);

            subregion = Subregion {{ center, dim }};

            Math::Vec2 p = subregion(center.toVec2());
            REQUIRE(TestUtils::approx(p.x, 0.5f));
            REQUIRE(TestUtils::approx(p.y, 0.5f));
        }
    }
}

TEST_CASE("edges_map_to_edge", "[subregion]") {
    auto center = NormalizedPoint::create(0.5f);
    auto dim = NormalizedPoint::create(0.8f);

    Subregion subregion {{ center, dim }};

    Math::Vec2 p1 { center.x() + dim.toVec2().scale(0.5f).x };
    Math::Vec2 p2 { center.y() - dim.toVec2().scale(0.5f).y };

    Math::Vec2 topRight = subregion(p1);
    Math::Vec2 bottomLeft = subregion(p2);

    REQUIRE(TestUtils::approx(topRight.x, norm_max));
    REQUIRE(TestUtils::approx(topRight.y, norm_max));
    REQUIRE(TestUtils::approx(bottomLeft.x, norm_min));
    REQUIRE(TestUtils::approx(bottomLeft.y, norm_min));
}
