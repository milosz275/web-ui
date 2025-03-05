#include "text.h"

#include <emscripten.h>
#include <emscripten/html5.h>

namespace web_ui
{
    // javascript macro to setup canvas using emscripten
    EM_JS(void, em_setup_canvas, (), {
        var glCanvas = document.getElementById('webglCanvas');
        var textCanvas = document.getElementById('textCanvas');
        
        if (!glCanvas || !textCanvas) {
            console.error("Canvas elements not found!");
            return;
        }
    
        glCanvas.width = textCanvas.width = window.innerWidth;
        glCanvas.height = textCanvas.height = window.innerHeight;
    
        Module.textCanvas = textCanvas;
    });
    
    // javascript macro to render text using emscripten
    EM_JS(void, em_render_text, (float x, float y, const char* text, const char* font, const char* fill_style), {
        var textCanvas = Module.textCanvas;
        if (!textCanvas) {
            console.error("Text canvas is not initialized.");
            return;
        }
        
        var ctx = textCanvas.getContext('2d');
        if (!ctx) {
            console.error("2D context is not available.");
            return;
        }

        ctx.font = UTF8ToString(font);
        ctx.fillStyle = UTF8ToString(fill_style);
        ctx.fillText(UTF8ToString(text), x, y);
    });

    // javascript macro to clear text canvas using emscripten
    EM_JS(void, em_clear_text_canvas, (), {
        var textCanvas = Module.textCanvas;
        if (!textCanvas) {
            console.error("Text canvas is not initialized.");
            return;
        }
        
        var ctx = textCanvas.getContext('2d');
        if (!ctx) {
            console.error("2D context is not available.");
            return;
        }
    
        ctx.clearRect(0, 0, textCanvas.width, textCanvas.height);
    });

    void text::setup_canvas()
    {
        em_setup_canvas();
    }

    void text::draw_text(float x, float y, std::string text, std::string font, std::string fill_style)
    {
        int canvas_width = EM_ASM_INT({ return getCanvasSize().width; }, 0);
        int canvas_height = EM_ASM_INT({ return getCanvasSize().height; }, 0);
        float pixel_x = (x + 1.0f) * 0.5f * canvas_width;
        float pixel_y = (1.0f - y) * 0.5f * canvas_height;
        em_render_text(pixel_x, pixel_y, text.c_str(), font.c_str(), fill_style.c_str());
    }

    void text::clear_text_canvas()
    {
        em_clear_text_canvas();
    }
}
