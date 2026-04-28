#include"pipeline/stages/subregion.h"
#include"types/normalized_point.h"

#include<catch2/catch_test_macros.hpp>
#include"utils/test_utils.h"

TEST_CASE("center_is_invariant", "[subregion]") {
    Pipeline::Stages::Subregion subregion;

    auto dim = Common::NormalizedPoint::create(1.0f);

    for (float x = Common::norm_min; x <= Common::norm_max; x += 0.2f) {
        for (float y = Common::norm_min; y <= Common::norm_max; y += 0.2f) {
            auto center = Common::NormalizedPoint::create(x, y);

            subregion = Pipeline::Stages::Subregion {{ center, dim }};

            Math::Vec2 p = subregion(center.toVec2());
            REQUIRE(TestUtils::approx(p.x, 0.5f));
            REQUIRE(TestUtils::approx(p.y, 0.5f));
        }
    }
}

TEST_CASE("edges_map_to_edge", "[subregion]") {
    auto center = Common::NormalizedPoint::create(0.5f);
    auto dim = Common::NormalizedPoint::create(0.8f);

    Pipeline::Stages::Subregion subregion {{ center, dim }};

    Math::Vec2 p1 { center.x() + dim.toVec2().scale(0.5f).x };
    Math::Vec2 p2 { center.y() - dim.toVec2().scale(0.5f).y };

    Math::Vec2 topRight = subregion(p1);
    Math::Vec2 bottomLeft = subregion(p2);

    REQUIRE(TestUtils::approx(topRight.x, Common::norm_max));
    REQUIRE(TestUtils::approx(topRight.y, Common::norm_max));
    REQUIRE(TestUtils::approx(bottomLeft.x, Common::norm_min));
    REQUIRE(TestUtils::approx(bottomLeft.y, Common::norm_min));
}
