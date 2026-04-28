#include"config/pipeline_config.h"
#include"types/normalized_point.h"

namespace Config {

    PipelineConfig::PipelineConfig() : 
        subregionCenter(Common::NormalizedPoint::create(default_subregion_center)), 
        subregionDimensions(Common::NormalizedPoint::create(default_subregion_dimensions)),
        sensitivity(default_sensitivity),
        lockAspect(default_aspect_lock) {}

    PipelineConfig::PipelineConfig(
        Common::NormalizedPoint center, 
        Common::NormalizedPoint dimensions, 
        float sensitivity,
        bool lockAspect
    ) : subregionCenter(center), subregionDimensions(dimensions), sensitivity(sensitivity), lockAspect(lockAspect) {}
}
