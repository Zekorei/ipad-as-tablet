#include "input/pipeline/stages/aspect.h"
#include <catch2/catch_test_macros.hpp>
#include "utils/test_utils.h"

#include "config/screen_info.h"
#include "types/normalized_point.h"


using namespace Input::Pipeline::Stages;
using namespace Input::Pipeline;

TEST_CASE("center_is_invariant", "[aspect]") {
    Aspect aspect;

    float center = 0.5f;

    for (long x = 500; x <= 4000; x += 500) {
        for (long y = 500; y <= 4000; y += 500) {
            aspect = Aspect {{ x, y }};

            Math::Vec2 p = aspect({center});
            REQUIRE(TestUtils::approx(p.x, center));
            REQUIRE(TestUtils::approx(p.y, center));
        }
    }
}

TEST_CASE("horizontal_symmetry_is_preserved", "[aspect]") {
    Aspect aspect;

    for (long x = 500; x <= 4000; x += 500) {
        for (long y = 500; y <= 4000; y += 500) {
            aspect = Aspect {{ x, y }};

            Math::Vec2 p1 = aspect({ 0.2f, 0.5f });
            Math::Vec2 p2 = aspect({ 0.8f, 0.5f });
            REQUIRE(TestUtils::approx((p1.x + p2.x) / 2, 0.5f));
        }
    }
}

TEST_CASE("vertical_symmetry_is_preserved", "[aspect]") {
    Aspect aspect;

    for (long x = 500; x <= 4000; x += 500) {
        for (long y = 500; y <= 4000; y += 500) {
            aspect = Aspect {{ x, y }};

            Math::Vec2 p1 = aspect({ 0.5f, 0.2f });
            Math::Vec2 p2 = aspect({ 0.5f, 0.8f });
            REQUIRE(TestUtils::approx((p1.y + p2.y) / 2, 0.5f));
        }
    }
}

TEST_CASE("vertical_axis_isolation", "[aspect]") {
    Aspect aspect {{ 1920, 1080 }};

    for (float x = norm_min; x <= norm_max; x += 0.1f) {
        for (float y = norm_min; y <= norm_max; y += 0.1f) {
            Math::Vec2 p1 = aspect({ x, y });
            REQUIRE(p1.y == y);
        }
    }
}

TEST_CASE("horizontal_axis_isolation", "[aspect]") {
    Aspect aspect {{ 1080, 1920 }};

    for (float x = norm_min; x < norm_max; x += 0.1f) {
        for (float y = norm_min; y < norm_max; y += 0.1f) {
            Math::Vec2 p1 = aspect({ x, y });
            REQUIRE(p1.x == x);
        }
    }
}

