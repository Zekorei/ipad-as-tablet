#include"pipeline/stages/display.h"

namespace Pipeline::Stages {
    Common::ScreenPoint Display::operator()(Common::NormalizedPoint point) {
        return Common::ScreenPoint::create(
            (LONG)(point.x() * (float)Common::win_abs_mouse_max),
            (LONG)(point.y() * (float)Common::win_abs_mouse_max)
        );
    }
}
