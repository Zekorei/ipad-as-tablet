#include "types/screen_point.h"

namespace Output {

    ScreenPoint::ScreenPoint(LONG x, LONG y) : x_(x), y_(y) {}

    ScreenPoint ScreenPoint::create(LONG x, LONG y) {
        if (x < win_abs_mouse_min || x > win_abs_mouse_max || y < win_abs_mouse_min || y > win_abs_mouse_max) {
            throw std::out_of_range("ScreenPoint: values must be in [0, 65535]");
        }
        return { x, y };
    }

    ScreenPoint ScreenPoint::fromNormalized(const Input::Pipeline::NormalizedPoint& normed) {
        return ScreenPoint::create(
            (LONG)(normed.x() * win_abs_mouse_max), 
            (LONG)(normed.y() * win_abs_mouse_max)
        );
    }

    LONG ScreenPoint::x() const { return x_; }

    LONG ScreenPoint::y() const { return y_; }

    void ScreenPoint::x(LONG v) {
        if (v < win_abs_mouse_min || v > win_abs_mouse_max) {
            throw std::out_of_range("ScreenPoint: values must be in [0, 65535]");
        }
        x_ = v;
    }

    void ScreenPoint::y(LONG v) {
        if (v < win_abs_mouse_min || v > win_abs_mouse_max) {
            throw std::out_of_range("ScreenPoint: values must be in [0, 65535]");
        }
        y_ = v;
    }
}
