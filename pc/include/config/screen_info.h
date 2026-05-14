#pragma once

namespace Config {

    /**
     * @brief Screen information including width and height in pixels. 
     */
    struct ScreenInfo {
        int width;  ///< Screen width in pixels
        int height; ///< Screen height in pixels

        /// @brief Default constructor that fetches screen metrics from the system.
        ScreenInfo();

        /**
         * @brief Construct screen info with specified width and height.
         */
        ScreenInfo(int width, int height);

        /// @brief Get the aspect ratio of the screen (width / height).
        float aspectRatio() const;
    };
}
