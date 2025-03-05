#include <iostream>

#include <emscripten.h>
#include <emscripten/html5.h>
#include <GLES3/gl3.h>

#include "app.h"
#include "renderer.h"
#include "background.h"
#include "text.h"

using namespace std;

using namespace web_ui;

void render_loop()
{
    background::draw_background();
    renderer::update_scale();
    renderer::draw_rectangle({-0.5f, -0.5f}, {1, 1}, {0, 1, 0});
    renderer::draw_rectangle({0.5f, 0.5f}, {1, 1}, {0.5f, 0.5f, 1});
    renderer::draw_line({0, 0}, {1, 1}, {1, 0, 0});
    renderer::draw_triangle({-0.5f, 0.5f}, {0.5f, 0.5f}, {0, 1}, {0, 0, 1});
    renderer::draw_circle({0, 0}, 0.1f, {1, 1, 0});
    renderer::draw_circle({0.5f, 0}, 0.5f, {0, 1, 1});
    renderer::draw_circle({-0.5f, -0.5f}, 0.25f, {1, 0, 1});
    renderer::draw_circle({-0.75f, -0.75f}, 0.05f, {1, 0, 0}); // left
    renderer::draw_circle({0.75f, -0.75f}, 0.05f, {1, 0, 0}); // right
    text::clear_text_canvas();
    text::draw_text();
    text::draw_text(0.0f, 0.0f, "WebGL", "20px Arial", "black");
    text::draw_text(-0.5f, 0.5f, "1", "12px Arial", "blue");
    text::draw_text(0.5f, 0.5f, "2", "12px Arial", "blue");
    text::draw_text(0.5f, -0.5f, "3", "12px Arial", "blue");
    text::draw_text(-0.5f, -0.5f, "4", "12px Arial", "blue");
}

void deinit()
{
    
}

int main()
{
    text::setup_canvas();

    EmscriptenWebGLContextAttributes attr;
    emscripten_webgl_init_context_attributes(&attr);
    attr.alpha = 0;
    attr.depth = 1;
    attr.stencil = 1;
    attr.antialias = 1;
    attr.majorVersion = 2;

    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE context = emscripten_webgl_create_context("#webglCanvas", &attr);
    if (context <= 0)
    {
        cerr << "Failed to create WebGL context!" << '\n';
        return 1;
    }

    emscripten_webgl_make_context_current(context);

    renderer::init();
    app::run(render_loop);
    app::cleanup(deinit);

    return 0;
}
