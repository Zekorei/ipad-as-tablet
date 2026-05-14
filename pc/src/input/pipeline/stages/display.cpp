#include "input/pipeline/stages/display.h"

namespace Input::Pipeline::Stages {

    Output::ScreenPoint Display::operator()(NormalizedPoint point) {
        return Output::ScreenPoint::create(
            (LONG)(point.x() * (float)Output::win_abs_mouse_max),
            (LONG)(point.y() * (float)Output::win_abs_mouse_max)
        );
    }
}
