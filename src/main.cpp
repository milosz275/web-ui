#include <iostream>

#include <emscripten.h>
#include <emscripten/html5.h>
#include <GLES3/gl3.h>
#include <glm/glm.hpp>

#include "app.h"
#include "renderer.h"
#include "background.h"
#include "text.h"

using namespace std;

void draw_house()
{
    // sun
    web_ui::background::draw_background();
    int canvas_width = EM_ASM_INT({ return getCanvasSize().width; }, 0);
    int canvas_height = EM_ASM_INT({ return getCanvasSize().height; }, 0);

    float radius = 0.2f;
    float radius_x = radius * (static_cast<float>(canvas_height) / canvas_width);
    float radius_y = radius;
    web_ui::renderer::draw_ellipse({0.75f, 0.75f}, radius_x, radius_y, {1, 0.80f, 0});

    radius = 0.175f;
    radius_x = radius * (static_cast<float>(canvas_height) / canvas_width);
    radius_y = radius;
    web_ui::renderer::draw_ellipse({0.75f, 0.75f}, radius_x, radius_y, {1, 0.90f, 0});

    radius = 0.15f;
    radius_x = radius * (static_cast<float>(canvas_height) / canvas_width);
    radius_y = radius;
    web_ui::renderer::draw_ellipse({0.75f, 0.75f}, radius_x, radius_y, {1, 1.00f, 0});

    // house
    web_ui::renderer::draw_rectangle({-0.5f, -0.5f}, {0.5, 0.25f}, {0.8f, 0.5f, 0.2f}); // house base
    web_ui::renderer::draw_triangle({-0.75f, 0.25f}, {0.75f, 0.25f}, {0.0f, 0.75f}, {0.6f, 0.3f, 0.1f}); // roof
    web_ui::renderer::draw_rectangle({-0.1f, -0.5f}, {0.1f, 0.0f}, {0.4f, 0.2f, 0.1f}); // door
    web_ui::renderer::draw_rectangle({-0.4f, -0.2f}, {-0.2f, 0.0f}, {0.7f, 0.9f, 1.0f}); // left window
    web_ui::renderer::draw_rectangle({0.2f, -0.2f}, {0.4f, 0.0f}, {0.7f, 0.9f, 1.0f}); // right window
    web_ui::renderer::draw_line({-0.4f, -0.1f}, {-0.2f, -0.1f}, {0, 0, 0}); // left window horizontal window pane
    web_ui::renderer::draw_line({-0.3f, -0.2f}, {-0.3f, 0.0f}, {0, 0, 0}); // left window vertical window pane
    web_ui::renderer::draw_line({0.2f, -0.1f}, {0.4f, -0.1f}, {0, 0, 0}); // right window horizontal window pane
    web_ui::renderer::draw_line({0.3f, -0.2f}, {0.3f, 0.0f}, {0, 0, 0}); // right window vertical window pane
}

void draw_sierpinski_triangle(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, int depth)
{
    if (depth == 0)
        web_ui::renderer::draw_triangle(p1, p2, p3, glm::vec3(1.0f, 1.0f, 1.0f));
    else
    {
        glm::vec2 mid1 = (p1 + p2) / 2.0f;
        glm::vec2 mid2 = (p2 + p3) / 2.0f;
        glm::vec2 mid3 = (p3 + p1) / 2.0f;

        draw_sierpinski_triangle(p1, mid1, mid3, depth - 1);
        draw_sierpinski_triangle(mid1, p2, mid2, depth - 1);
        draw_sierpinski_triangle(mid3, mid2, p3, depth - 1);
    }
}

void render_loop()
{
    draw_house();

    // glm::vec2 p1 = glm::vec2(-0.5f, -0.5f);
    // glm::vec2 p2 = glm::vec2(0.5f, -0.5f);
    // glm::vec2 p3 = glm::vec2(0.0f, 0.5f);
    // draw_sierpinski_triangle(p1, p2, p3, 5);

    // text
    web_ui::text::clear_text_canvas();
    web_ui::text::draw_text_absolute();
    web_ui::text::draw_text({-0.03f, -0.75f}, "House", "20px serif", "brown");
}

int main()
{
    web_ui::text::setup_canvas();

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

    web_ui::renderer::init();
    web_ui::app::run(render_loop);

    return 0;
}
