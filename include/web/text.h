#pragma once

#include <string>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace web_ui
{
    class text
    {
    private:
        static FT_Library ft;
        static FT_Face face;

    public:
        static void draw_text(const std::string& text, float x, float y);
    };
}
