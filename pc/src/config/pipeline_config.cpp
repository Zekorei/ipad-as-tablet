#include "config/pipeline_config.h"
#include "types/normalized_point.h"

namespace Config {
    
    using namespace Input::Pipeline;

    PipelineConfig::PipelineConfig() : 
        subregionCenter(NormalizedPoint::create(default_subregion_center)), 
        subregionDimensions(NormalizedPoint::create(default_subregion_dimensions)),
        sensitivity(default_sensitivity),
        lockAspect(default_aspect_lock) {}

    PipelineConfig::PipelineConfig(
        NormalizedPoint center, 
        NormalizedPoint dimensions, 
        float sensitivity,
        bool lockAspect
    ) : subregionCenter(center), subregionDimensions(dimensions), sensitivity(sensitivity), lockAspect(lockAspect) {}
}
