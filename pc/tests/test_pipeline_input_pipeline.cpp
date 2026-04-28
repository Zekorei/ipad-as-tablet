#include"pipeline/input_pipeline.h"
#include"math/vec2.h"
#include"types/screen_point.h"
#include"types/screen_info.h"
#include"config/pipeline_config.h"

#include<catch2/catch_test_macros.hpp>
#include"utils/test_utils.h"

TEST_CASE("subregion_center_maps_to_center", "[pipeline]") {
    Config::PipelineConfig config;
    long screenSize = 1000L;
    Common::ScreenInfo screenInfo { screenSize, screenSize };

    auto dim = Common::NormalizedPoint::create(1.0f); 

    for (float x = Common::norm_min; x <= Common::norm_max; x += 0.2f) {
        for (float y = Common::norm_min; y <= Common::norm_max; y += 0.2f) {
            auto center = Common::NormalizedPoint::create(x, y);

            config = Config::PipelineConfig { center, dim, 1.0f, false };

            Pipeline::InputPipeline pipeline { config, screenInfo };

            Common::ScreenPoint p = pipeline.process(center.toVec2());
            REQUIRE(TestUtils::screenApprox(2 * p.x(), Common::win_abs_mouse_max));
            REQUIRE(TestUtils::screenApprox(2 * p.y(), Common::win_abs_mouse_max));
        }
    }
}

TEST_CASE("aspect_correction_preserves_center", "[pipeline]") {
    Config::PipelineConfig config;
    long screenSize = 1000L;
    Common::ScreenInfo screenInfo { screenSize, screenSize };

    auto dim = Common::NormalizedPoint::create(1.0f); 

    for (float x = Common::norm_min; x <= Common::norm_max; x += 0.2f) {
        for (float y = Common::norm_min; y <= Common::norm_max; y += 0.2f) {
            auto center = Common::NormalizedPoint::create(x, y);

            config = Config::PipelineConfig { center, dim, 1.0f, true };

            Pipeline::InputPipeline pipeline { config, screenInfo };

            Common::ScreenPoint p = pipeline.process(center.toVec2());
            REQUIRE(TestUtils::screenApprox(2 * p.x(), Common::win_abs_mouse_max));
            REQUIRE(TestUtils::screenApprox(2 * p.y(), Common::win_abs_mouse_max));
        }
    }
}

TEST_CASE("subregion_edges_map_to_screen_edges", "[pipeline]") {
    Config::PipelineConfig config;
    long screenSize = 1000L;
    Common::ScreenInfo screenInfo { screenSize, screenSize };

    auto dim = Common::NormalizedPoint::create(1.0f); 

    for (float x = Common::norm_min; x <= Common::norm_max; x += 0.2f) {
        for (float y = Common::norm_min; y <= Common::norm_max; y += 0.2f) {
            auto center = Common::NormalizedPoint::create(x, y);

            config = Config::PipelineConfig { center, dim, 1.0f, false };

            Pipeline::InputPipeline pipeline { config, screenInfo };

            Common::ScreenPoint bottomLeft = pipeline.process(center.toVec2() - dim.toVec2().scale(0.5f));
            Common::ScreenPoint topRight = pipeline.process(center.toVec2() + dim.toVec2().scale(0.5f));

            REQUIRE(TestUtils::screenApprox(bottomLeft.x(), Common::win_abs_mouse_min));
            REQUIRE(TestUtils::screenApprox(bottomLeft.y(), Common::win_abs_mouse_min));
            REQUIRE(TestUtils::screenApprox(topRight.x(), Common::win_abs_mouse_max));
            REQUIRE(TestUtils::screenApprox(topRight.y(), Common::win_abs_mouse_max));
        }
    }
}

TEST_CASE("symmetry", "[pipeline]") {
    auto center = Common::NormalizedPoint::create(0.5f);
    auto dim = Common::NormalizedPoint::create(0.8f);
    Config::PipelineConfig config { center, dim, 1.0f, true };

    Common::ScreenInfo screenInfo = { 1920, 1080 };

    Pipeline::InputPipeline pipeline { config, screenInfo };

    for (float x = Common::norm_min; x <= Common::norm_max/2; x += 0.1f) {
        Common::ScreenPoint sp1 = pipeline.process({ x });
        Common::ScreenPoint sp2 = pipeline.process({ Common::norm_max - x });

        REQUIRE(TestUtils::screenApprox(sp1.x() + sp2.x(), Common::win_abs_mouse_max));
        REQUIRE(TestUtils::screenApprox(sp1.y() + sp2.y(), Common::win_abs_mouse_max));
    }
}

TEST_CASE("monotonicity", "[pipeline]") {
    auto center = Common::NormalizedPoint::create(0.5f);
    auto dim = Common::NormalizedPoint::create(0.8f);
    Config::PipelineConfig config { center, dim, 1.0f, true };

    Common::ScreenInfo screenInfo = { 1920, 1080 };

    Pipeline::InputPipeline pipeline { config, screenInfo };

    for (float x = Common::norm_min; x <= Common::norm_max; x += 0.1f) {
        Math::Vec2 p1 { x };
        Math::Vec2 p2 { x + 0.1f };

        Common::ScreenPoint sp1 = pipeline.process(p1);
        Common::ScreenPoint sp2 = pipeline.process(p2);

        REQUIRE(sp1.x() <= sp2.x());
        REQUIRE(sp1.y() <= sp2.y());
    }
}
