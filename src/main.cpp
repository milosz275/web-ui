#include <iostream>

#include <emscripten.h>
#include <emscripten/html5.h>
#include <GLES3/gl3.h>

#include "app.h"
#include "text.h"
#include "renderer.h"
#include "background.h"

using namespace std;

using namespace web_ui;

void render_loop()
{
    background::draw_background();
    renderer::draw_rectangle({-0.5f, -0.5f}, {1, 1}, {0, 1, 0});
    renderer::draw_rectangle({0.5f, 0.5f}, {1, 1}, {0.5f, 0.5f, 1});
    renderer::draw_line({0, 0}, {1, 1}, {1, 0, 0});
    renderer::draw_triangle({-0.5f, 0.5f}, {0.5f, 0.5f}, {0, 1}, {0, 0, 1});
    renderer::draw_circle({0, 0}, 0.1f, {1, 1, 0});
    renderer::draw_circle({0.5f, 0}, 0.5f, {0, 1, 1});
    renderer::draw_circle({-0.5f, -0.5f}, 0.25f, {1, 0, 1});
    renderer::draw_circle({-0.75f, -0.75f}, 0.05f, {1, 0, 0}); // left
    renderer::draw_circle({0.75f, -0.75f}, 0.05f, {1, 0, 0}); // right
    text::draw_text("Hello, World!", 0, 0);
}

int main()
{
    EmscriptenWebGLContextAttributes attr;
    emscripten_webgl_init_context_attributes(&attr);
    attr.alpha = 0;
    attr.depth = 1;
    attr.stencil = 1;
    attr.antialias = 1;
    attr.majorVersion = 2;

    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE context = emscripten_webgl_create_context("#canvas", &attr);
    if (context <= 0)
    {
        cerr << "Failed to create WebGL context!" << '\n';
        return 1;
    }

    emscripten_webgl_make_context_current(context);

    renderer::init();
    app::run(render_loop);

    return 0;
}
