#pragma once

#include <string>

namespace web_ui
{
    class text
    {
    public:
        /**
         * @brief Setups text canvas.
         */
        static void setup_canvas();

        /**
         * @brief Draws text wrapping Emscripten.
         * @details Supply (x, y) coordinates, text style to draw it on text canvas.
         * @param x Coordinate x in (-1.0f, 1.0f) domain
         * @param y Coordinate y in (-1.0f, 1.0f) domain
         * @param text String text to be drawn
         * @param font String font style, e.g. "30px Arial"
         * @param fill_style String fill style, e.g. "white"
         */
        static void draw_text(float x = -0.9f, float y = 0.9f, std::string text = "Web UI", std::string font = "30px Arial", std::string fill_style = "white");
        
        /**
         * @brief Clears text canvas.
         * @details Prevents overlapping of printed text.
         * @attention Must be runned before any text that will be printed in each cycle.
         */
        static void clear_text_canvas();
    };
}
