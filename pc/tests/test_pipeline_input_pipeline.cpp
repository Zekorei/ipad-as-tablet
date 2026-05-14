#include "input/pipeline/input_pipeline.h"
#include <catch2/catch_test_macros.hpp>
#include "utils/test_utils.h"

#include "math/vec2.h"
#include "types/screen_point.h"
#include "config/screen_info.h"
#include "config/pipeline_config.h"


using namespace Input::Pipeline;

TEST_CASE("subregion_center_maps_to_center", "[pipeline]") {
    long screenSize = 1000L;

    Config::PipelineConfig config;
    Config::ScreenInfo screenInfo { screenSize, screenSize };

    auto dim = NormalizedPoint::create(1.0f); 

    for (float x = norm_min; x <= norm_max; x += 0.2f) {
        for (float y = norm_min; y <= norm_max; y += 0.2f) {
            auto center = NormalizedPoint::create(x, y);

            config = Config::PipelineConfig { center, dim, 1.0f, false };

            InputPipeline pipeline { config, screenInfo };

            Output::ScreenPoint p = pipeline.process(center.toVec2());
            REQUIRE(TestUtils::screenApprox(2 * p.x(), Output::win_abs_mouse_max));
            REQUIRE(TestUtils::screenApprox(2 * p.y(), Output::win_abs_mouse_max));
        }
    }
}

TEST_CASE("aspect_correction_preserves_center", "[pipeline]") {
    long screenSize = 1000L;

    Config::PipelineConfig config;
    Config::ScreenInfo screenInfo { screenSize, screenSize };

    auto dim = NormalizedPoint::create(1.0f); 

    for (float x = norm_min; x <= norm_max; x += 0.2f) {
        for (float y = norm_min; y <= norm_max; y += 0.2f) {
            auto center = NormalizedPoint::create(x, y);

            config = Config::PipelineConfig { center, dim, 1.0f, true };

            InputPipeline pipeline { config, screenInfo };

            Output::ScreenPoint p = pipeline.process(center.toVec2());
            REQUIRE(TestUtils::screenApprox(2 * p.x(), Output::win_abs_mouse_max));
            REQUIRE(TestUtils::screenApprox(2 * p.y(), Output::win_abs_mouse_max));
        }
    }
}

TEST_CASE("subregion_edges_map_to_screen_edges", "[pipeline]") {
    long screenSize = 1000L;

    Config::PipelineConfig config;
    Config::ScreenInfo screenInfo { screenSize, screenSize };

    auto dim = NormalizedPoint::create(1.0f); 

    for (float x = norm_min; x <= norm_max; x += 0.2f) {
        for (float y = norm_min; y <= norm_max; y += 0.2f) {
            auto center = NormalizedPoint::create(x, y);

            config = Config::PipelineConfig { center, dim, 1.0f, false };

            InputPipeline pipeline { config, screenInfo };

            Output::ScreenPoint bottomLeft = pipeline.process(center.toVec2() - dim.toVec2().scale(0.5f));
            Output::ScreenPoint topRight = pipeline.process(center.toVec2() + dim.toVec2().scale(0.5f));

            REQUIRE(TestUtils::screenApprox(bottomLeft.x(), Output::win_abs_mouse_min));
            REQUIRE(TestUtils::screenApprox(bottomLeft.y(), Output::win_abs_mouse_min));
            REQUIRE(TestUtils::screenApprox(topRight.x(), Output::win_abs_mouse_max));
            REQUIRE(TestUtils::screenApprox(topRight.y(), Output::win_abs_mouse_max));
        }
    }
}

TEST_CASE("symmetry", "[pipeline]") {
    auto center = NormalizedPoint::create(0.5f);
    auto dim = NormalizedPoint::create(0.8f);
    Config::PipelineConfig config { center, dim, 1.0f, true };

    Config::ScreenInfo screenInfo = { 1920, 1080 };

    InputPipeline pipeline { config, screenInfo };

    for (float x = norm_min; x <= norm_max/2; x += 0.1f) {
        Output::ScreenPoint sp1 = pipeline.process({ x });
        Output::ScreenPoint sp2 = pipeline.process({ norm_max - x });

        REQUIRE(TestUtils::screenApprox(sp1.x() + sp2.x(), Output::win_abs_mouse_max));
        REQUIRE(TestUtils::screenApprox(sp1.y() + sp2.y(), Output::win_abs_mouse_max));
    }
}

TEST_CASE("monotonicity", "[pipeline]") {
    auto center = NormalizedPoint::create(0.5f);
    auto dim = NormalizedPoint::create(0.8f);
    Config::PipelineConfig config { center, dim, 1.0f, true };

    Config::ScreenInfo screenInfo = { 1920, 1080 };

    InputPipeline pipeline { config, screenInfo };

    for (float x = norm_min; x <= norm_max; x += 0.1f) {
        Math::Vec2 p1 { x };
        Math::Vec2 p2 { x + 0.1f };

        Output::ScreenPoint sp1 = pipeline.process(p1);
        Output::ScreenPoint sp2 = pipeline.process(p2);

        REQUIRE(sp1.x() <= sp2.x());
        REQUIRE(sp1.y() <= sp2.y());
    }
}
