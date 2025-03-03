#include "text.h"

#include <iostream>

#include <GLES3/gl3.h>

#include "DejaVuSans.h"

#define DejaVuSans_ttf _usr_share_fonts_truetype_dejavu_DejaVuSans_ttf
#define DejaVuSans_ttf_len _usr_share_fonts_truetype_dejavu_DejaVuSans_ttf_len

using namespace std;

namespace web_ui
{
    FT_Library text::ft;
    FT_Face text::face;

    void text::draw_text(const std::string& text, float x, float y)
    {
        if (!ft)
        {
            if (FT_Init_FreeType(&ft))
            {
                cerr << "Failed to initialize FreeType library!" << '\n';
                return;
            }

            // Use the embedded font data
            if (FT_New_Memory_Face(ft, DejaVuSans_ttf, DejaVuSans_ttf_len, 0, &face))
            {
                cerr << "Failed to load embedded font!" << '\n';
                return;
            }

            FT_Set_Pixel_Sizes(face, 0, 48);
        }

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        for (auto c : text)
        {
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                cerr << "Failed to load glyph for character: " << c << '\n';
                continue;
            }

            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_LUMINANCE,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_LUMINANCE,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
            );

            float xpos = x + face->glyph->bitmap_left;
            float ypos = y - face->glyph->bitmap_top;

            float w = face->glyph->bitmap.width;
            float h = face->glyph->bitmap.rows;

            float vertices[] = {
                xpos, ypos + h,
                xpos, ypos,
                xpos + w, ypos,
                xpos, ypos + h,
                xpos + w, ypos,
                xpos + w, ypos + h
            };

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, vertices);

            glDrawArrays(GL_TRIANGLES, 0, 6);

            glDisableVertexAttribArray(0);

            x += (face->glyph->advance.x >> 6);
            y += (face->glyph->advance.y >> 6);
        }

        glDeleteTextures(1, &texture);
    }
}
