#include<cmath>

#include<catch2/catch_test_macros.hpp>

#include"mapper.h"
#include"types.h"

using namespace Input;
using namespace Common;

// helper

/// @brief Approximate equality check for floating-point values, with a default tolerance of 1e-5.
/// @param a First value
/// @param b Second value
/// @param epsilon Error tolerance for comparison
/// @return True iff `a` and `b` are within the given `epsilon` tolerance of each other.
static bool approx(float a, float b, float epsilon = 1e-5f) {
    return std::fabs(a - b) < epsilon;
}

// fixture

struct MapperFixture {
    InputMapper mapper;

    MapperFixture() {
        InputMapConfig config {
            { 0.5f, 0.5f },
            { 1.0f, 1.0f },
            1.0f,
            true
        };
        ScreenInfo screenInfo(1920, 1080);
        mapper = InputMapper(config, screenInfo);
    }
};

// tests
// TODO: rewrite tests later

TEST_CASE_METHOD(MapperFixture, "Center remains invariant with full subregion", "[mapper]") {
    NormalizedPoint p{ 0.5f, 0.5f };
    auto out = mapper.map(p);

    REQUIRE(approx(out.x, 0.5f));
    REQUIRE(approx(out.y, 0.5f));
}

TEST_CASE_METHOD(MapperFixture, "Center remains invariant with proper subregion", "[mapper]") {
    InputMapConfig config = {
        { 0.5f, 0.5f },
        { 0.8f, 0.8f },
        1.0f,
        true
    };

    mapper.setConfig(config);
    NormalizedPoint p{ 0.5f, 0.5f };

    auto out = mapper.map(p);

    REQUIRE(approx(out.x, 0.5f));
    REQUIRE(approx(out.y, 0.5f));
}

TEST_CASE_METHOD(MapperFixture, "Output is clamped to [0, 1] with full subregion", "[mapper]") {
    for (float x = -0.5f; x <= 1.5f; x += 0.2f) {
        for (float y = -0.5f; y <= 1.5f; y += 0.2f) {
            auto out = mapper.map({x, y});
            REQUIRE(out.x >= 0.0f);
            REQUIRE(out.x <= 1.0f);
            REQUIRE(out.y >= 0.0f);
            REQUIRE(out.y <= 1.0f);
        }
    }
}

TEST_CASE_METHOD(MapperFixture, "Output is clamped to [0, 1] with proper subregion", "[mapper]") {
    InputMapConfig config = {
        { 0.5f, 0.5f },
        { 0.8f, 0.8f },
        1.0f,
        true
    };

    mapper.setConfig(config);

    for (float x = -0.5f; x <= 1.5f; x += 0.2f) {
        for (float y = -0.5f; y <= 1.5f; y += 0.2f) {
            auto out = mapper.map({x, y});
            REQUIRE(out.x >= 0.0f);
            REQUIRE(out.x <= 1.0f);
            REQUIRE(out.y >= 0.0f);
            REQUIRE(out.y <= 1.0f);
        }
    }
}

TEST_CASE_METHOD(MapperFixture, "Edge of subregion maps to edge of output", "[mapper]") {
    InputMapConfig config = {
        { 0.5f, 0.5f },
        { 0.8f, 0.8f },
        1.0f,
        true
    };

    mapper.setConfig(config);
    mapper.setScreenInfo({ 1000, 1000 }); // no aspect ratio adjustment

    NormalizedPoint p1 = config.subregionCenter + config.subregionDimensions.scale(0.5f);
    NormalizedPoint p2 = config.subregionCenter - config.subregionDimensions.scale(0.5f);

    auto topRight = mapper.map(p1);
    auto bottomLeft = mapper.map(p2);

    REQUIRE(approx(topRight.x, 1.0f));
    REQUIRE(approx(topRight.y, 1.0f));
    REQUIRE(approx(bottomLeft.x, 0.0f));
    REQUIRE(approx(bottomLeft.y, 0.0f));
}

TEST_CASE_METHOD(MapperFixture, "Wide screen compresses x-axis", "[mapper]") {
    mapper.setScreenInfo({ 1920, 1080 });

    float offset = 0.2f;

    NormalizedPoint p1 { 0.5f + offset, 0.5f };
    NormalizedPoint p2 { 0.5f - offset, 0.5f };

    auto out1 = mapper.map(p1);
    auto out2 = mapper.map(p2);

    REQUIRE((p1 - p2).x > (out1 - out2).x);
    REQUIRE(approx(out1.y, 0.5f));
    REQUIRE(approx(out2.y, 0.5f));
}

TEST_CASE_METHOD(MapperFixture, "Tall screen compresses y-axis", "[mapper]") {
    mapper.setScreenInfo({ 1080, 1920 });

    float offset = 0.2f;

    NormalizedPoint p1 { 0.5f, 0.5f + offset };
    NormalizedPoint p2 { 0.5f, 0.5f - offset };

    auto out1 = mapper.map(p1);
    auto out2 = mapper.map(p2);

    REQUIRE((p1 - p2).y > (out1 - out2).y);
    REQUIRE(approx(out1.x, 0.5f));
    REQUIRE(approx(out2.x, 0.5f));
}

TEST_CASE_METHOD(MapperFixture, "Mapping is symmetric about center", "[mapper]") {
    float d = 0.2f;

    NormalizedPoint p1 { 0.5f - d, 0.5f };
    NormalizedPoint p2 { 0.5f + d, 0.5f };

    auto left  = mapper.map(p1);
    auto right = mapper.map(p2);

    REQUIRE(approx((left.x + right.x) * 0.5f, 0.5f));
}
