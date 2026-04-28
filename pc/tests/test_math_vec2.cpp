#include"math/vec2.h"

#include<catch2/catch_test_macros.hpp>
#include"utils/test_utils.h"

using namespace Math;

TEST_CASE("default_constructor", "[vec2]") {
    Vec2 p;

    REQUIRE(p.x == 0.0f);
    REQUIRE(p.y == 0.0f);
}

TEST_CASE("two_argument_constructor", "[vec2]") {
    Vec2 p;

    for (float x = -2.5f; x <= 2.5f; x += 1.0f) {
        for (float y = 3.0f; y >= -2.0f; y -= 1.0f) {
            p = { x, y };
            REQUIRE(p.x == x);
            REQUIRE(p.y == y);
        }
    }
}

TEST_CASE("once_argument_constructor", "[vec2]") {
    Vec2 p;

    for (float v = -2.5f; v <= 2.5f; v += 1.0f) {
        p = { v };
        REQUIRE(p.x == v);
        REQUIRE(p.y == v);
    }
}

TEST_CASE("addition_overload", "[vec2]") {
    Vec2 p;

    for (float x = -2.5f; x <= 2.5f; x += 1.0f) {
        for (float y = 3.0f; y >= -2.0f; y -= 1.0f) {
            p = Vec2(x, y) + Vec2(y, x);
            REQUIRE(TestUtils::approx(p.x, x + y));
            REQUIRE(TestUtils::approx(p.y, x + y));
        }
    }
}

TEST_CASE("subtraction_overload", "[vec2]") {
    Vec2 p;

    for (float x = -2.5f; x <= 2.5f; x += 1.0f) {
        for (float y = 3.0f; y >= -2.0f; y -= 1.0f) {
            p = Vec2(x, y) - Vec2(y, x);
            REQUIRE(TestUtils::approx(p.x, x - y));
            REQUIRE(TestUtils::approx(p.y, y - x));
        }
    }
}

TEST_CASE("multiplication_overload", "[vec2]") {
    Vec2 p;

    for (float x = -2.5f; x <= 2.5f; x += 1.0f) {
        for (float y = 3.0f; y >= -2.0f; y -= 1.0f) {
            p = Vec2(x, y) * Vec2(y, x);
            REQUIRE(TestUtils::approx(p.x, x * y));
            REQUIRE(TestUtils::approx(p.y, x * y));
        }
    }
}

TEST_CASE("division_overload", "[vec2]") {
    Vec2 p;

    for (float x = -2.5f; x <= 2.5f; x += 1.0f) {
        for (float y = 3.1f; y >= -2.1f; y -= 1.0f) {
            p = Vec2(x, y) / Vec2(y, x);
            REQUIRE(TestUtils::approx(p.x, x / y));
            REQUIRE(TestUtils::approx(p.y, y / x));
        }
    }
}

TEST_CASE("vector_scaling", "[vec2]") {
    float offset = 0.7f;
    float factor = 2.0f;
    Vec2 p;

    for (float x = -2.4f; x <= 2.4f; x += 1.0f) {
        p = { x, x + offset };
        p = p.scale(factor);
        REQUIRE(TestUtils::approx(p.x, x * factor));
        REQUIRE(TestUtils::approx(p.y, (x + offset) * factor));
        p = p.scale(1/factor);
        REQUIRE(TestUtils::approx(p.x, x));
        REQUIRE(TestUtils::approx(p.y, x + offset));
    }
}

TEST_CASE("vector_translation", "[vec2]") {
    float offset = 0.7f;
    float trans = 2.0f;
    Vec2 p;

    for (float x = -2.5f; x <= 2.5f; x += 1.0f) {
        p = { x, x + offset };
        p = p.translate(trans);
        REQUIRE(TestUtils::approx(p.x, x + trans));
        REQUIRE(TestUtils::approx(p.y, x + offset + trans));
        p = p.translate(-trans);
        REQUIRE(TestUtils::approx(p.x, x));
        REQUIRE(TestUtils::approx(p.y, x + offset));
    }
}

TEST_CASE("clamp_out_of_bounds", "[vec2]") {
    float bound = 1.0f;
    Vec2 min = { -bound };
    Vec2 max = { bound };
    Vec2 p;

    for (float x = -10.0f; x < -1.0f; x += 1.3f) {
        p = Vec2(x).clamp(min, max);
        REQUIRE(p.x == -bound);
        REQUIRE(p.y == -bound);
    }

    for (float x = 10.0f; x > 1.0f; x -= 1.3f) {
        p = Vec2(x).clamp(min, max);
        REQUIRE(p.x == bound);
        REQUIRE(p.y == bound);
    }
}

TEST_CASE("clamp_in_bounds", "[vec2]") {
    float bound = 1.0f;
    Vec2 min = { -bound };
    Vec2 max = { bound };
    Vec2 p;

    for (float x = 1.0; x < 10.0f; x += 1.3f) {
        p = Vec2(1/x).clamp(min, max);
        REQUIRE(p.x == 1/x);
        REQUIRE(p.y == 1/x);
    }
}
