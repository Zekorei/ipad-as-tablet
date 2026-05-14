#include "input/pipeline/input_pipeline.h"

#include "input/pipeline/stages/aspect.h"
#include "input/pipeline/stages/clamp.h"
#include "input/pipeline/stages/display.h"
#include "input/pipeline/stages/subregion.h"

namespace Input::Pipeline {

    InputPipeline::InputPipeline(const Config::PipelineConfig& config, const Config::ScreenInfo& screenInfo
        ) : config(config), screenInfo(screenInfo) {
        subregion = Stages::Subregion { config };
        aspect = Stages::Aspect { screenInfo };
        clamp = Stages::Clamp {};
        display = Stages::Display {};
    }

    Output::ScreenPoint InputPipeline::process(const Math::Vec2& point) {
       auto fullRegionPoint = subregion(point);
       auto aspectCorrected = config.lockAspect ? aspect(fullRegionPoint) : fullRegionPoint;
       auto clamped = clamp(fullRegionPoint);
       auto screenPoint = display(clamped);

       return screenPoint;
    }
}
