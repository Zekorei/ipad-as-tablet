#include"config/pipeline_config.h"
#include"types/normalized_point.h"

namespace Config {

    PipelineConfig::PipelineConfig() : 
        subregionCenter(Common::NormalizedPoint::create(default_subregion_center)), 
        subregionDimensions(Common::NormalizedPoint::create(default_subregion_dimensions)),
        sensitivity(default_sensitivity) {}

    PipelineConfig::PipelineConfig(
        Common::NormalizedPoint center, 
        Common::NormalizedPoint dimensions, 
        float sensitivity
    ) : subregionCenter(center), subregionDimensions(dimensions), sensitivity(sensitivity) {}
}
