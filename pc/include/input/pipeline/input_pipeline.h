#pragma once

#include "config/pipeline_config.h"
#include "config/screen_info.h"
#include "math/vec2.h"
#include "types/normalized_point.h"
#include "types/screen_point.h"
#include "input/pipeline/stages/aspect.h"
#include "input/pipeline/stages/clamp.h"
#include "input/pipeline/stages/subregion.h"
#include "input/pipeline/stages/display.h"

namespace Input::Pipeline {
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
        explicit InputPipeline(const Config::PipelineConfig& config, const Config::ScreenInfo& screenInfo);

        Output::ScreenPoint process(const Math::Vec2& point);
    

    private:
        Config::PipelineConfig config;
        Config::ScreenInfo screenInfo;

        Stages::Subregion subregion;
        Stages::Aspect aspect;
        Stages::Clamp clamp;
        Stages::Display display;
    };
}
