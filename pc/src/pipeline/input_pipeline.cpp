#include"pipeline/input_pipeline.h"

#include"pipeline/stages/aspect.h"
#include"pipeline/stages/clamp.h"
#include"pipeline/stages/display.h"
#include"pipeline/stages/subregion.h"

namespace Pipeline {

    InputPipeline::InputPipeline(const Config::PipelineConfig& config, const Common::ScreenInfo& screenInfo
        ) : config(config), screenInfo(screenInfo) {
        subregion = Stages::Subregion { config };
        aspect = Stages::Aspect { screenInfo };
        clamp = Stages::Clamp {};
        display = Stages::Display {};
    }

    Common::ScreenPoint InputPipeline::process(const Math::Vec2& point) {
       Math::Vec2 fullRegionPoint = subregion(point);
       Math::Vec2 aspectCorrected = aspect(fullRegionPoint);
       Common::NormalizedPoint clamped = clamp(aspectCorrected);
       Common::ScreenPoint screenPoint = display(clamped);

       return screenPoint;
    }
}
