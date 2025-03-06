#include <iostream>

#include <emscripten.h>
#include <emscripten/html5.h>
#include <GLES3/gl3.h>

#include "app.h"
#include "renderer.h"
#include "background.h"
#include "text.h"

using namespace std;

void render_loop()
{
    web_ui::background::draw_background();
    web_ui::renderer::draw_rectangle({-0.5f, -0.5f}, {1, 1}, {0, 1, 0});
    web_ui::renderer::draw_rectangle({0.5f, 0.5f}, {1, 1}, {0.5f, 0.5f, 1});
    web_ui::renderer::draw_line({0, 0}, {1, 1}, {1, 0, 0});
    web_ui::renderer::draw_triangle({-0.5f, 0.5f}, {0.5f, 0.5f}, {0, 1}, {0, 0, 1});
    web_ui::renderer::draw_circle({0, 0}, 0.1f, {1, 1, 0});
    web_ui::renderer::draw_circle({0.5f, 0}, 0.5f, {0, 1, 1});
    web_ui::renderer::draw_circle({-0.5f, -0.5f}, 0.25f, {1, 0, 1});
    web_ui::renderer::draw_circle({-0.75f, -0.75f}, 0.05f, {1, 0, 0}); // left
    web_ui::renderer::draw_circle({0.75f, -0.75f}, 0.05f, {1, 0, 0}); // right
    web_ui::text::clear_text_canvas();
    web_ui::text::draw_text_absolute();
    web_ui::text::draw_text({0.0f, 0.0f}, "WebGL", "20px serif", "black");
    web_ui::text::draw_text({-0.5f, 0.5f}, "1", "12px serif", "green");
    web_ui::text::draw_text({0.5f, 0.5f}, "2", "12px serif", "green");
    web_ui::text::draw_text({0.5f, -0.5f}, "3", "12px serif", "green");
    web_ui::text::draw_text({-0.5f, -0.5f}, "4", "12px serif", "green");
    web_ui::text::draw_text({-0.75f, -0.75f}, "red", "18x serif", "white"); // left
    web_ui::text::draw_text({0.75f, -0.75f}, "red", "15px serif", "white"); // right
    web_ui::text::draw_text({-0.75f, 0.75f}, "a", "12px serif", "blue");
    web_ui::text::draw_text({-0.75f, 0.70f}, "b", "12px serif", "blue");
    web_ui::text::draw_text({-0.75f, 0.65f}, "c", "12px serif", "blue");
    web_ui::text::draw_text({-0.75f, 0.60f}, "d", "12px serif", "blue");
    web_ui::text::draw_text({-0.75f, 0.55f}, "e", "12px serif", "blue");
    web_ui::text::draw_text({-0.75f, 0.50f}, "f", "12px serif", "blue");
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
