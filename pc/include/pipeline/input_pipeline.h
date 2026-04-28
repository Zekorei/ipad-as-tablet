#pragma once

#include"types/screen_info.h"
#include"types/normalized_point.h"
#include"types/screen_point.h"
#include"math/vec2.h"
#include"config/pipeline_config.h"
#include"pipeline/stages/aspect.h"
#include"pipeline/stages/clamp.h"
#include"pipeline/stages/subregion.h"
#include"pipeline/stages/display.h"

namespace Pipeline {
    /**
     * @brief Combiner class for each processing stage of the pipeline.
     */
    class InputPipeline {
    public:
        /**
         * @brief Construct a new `InputPipeline` object, and initializes each stage operation with the necessary
         * context if required.
         * 
         * @param config The config used for pipeline stages.
         * @param screenInfo The screen data used for pipeline stages.
         */
        explicit InputPipeline(const Config::PipelineConfig& config, const Common::ScreenInfo& screenInfo);

        Common::ScreenPoint process(const Math::Vec2& point);
    

    private:
        Config::PipelineConfig config;
        Common::ScreenInfo screenInfo;

        Stages::Subregion subregion;
        Stages::Aspect aspect;
        Stages::Clamp clamp;
        Stages::Display display;
    };
}
