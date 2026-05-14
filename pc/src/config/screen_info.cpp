#include "config/screen_info.h"

#include <windows.h>

namespace Config {

    ScreenInfo::ScreenInfo() {
        width = GetSystemMetrics(SM_CXSCREEN);
        height = GetSystemMetrics(SM_CYSCREEN);
    }

    ScreenInfo::ScreenInfo(int width, int height) : width(width), height(height) {}

    float ScreenInfo::aspectRatio() const {
        return static_cast<float>(width) / height;
    }
}
