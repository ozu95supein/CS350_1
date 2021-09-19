#include "window.hpp"
#include "debug_system.hpp"
#include "camera.hpp"
constexpr unsigned window_width = 1024;
constexpr unsigned window_height = 760;
void setup_scene(camera& c)
{
    // Setup frame
    glClearColor(0, 0, 0, 1);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, window_width, window_height);

    // Camera
    c.set_position({ 0, 0, 10 });
    c.set_target({ 0, 0, 0 });
    c.set_projection(60.0f, { window_width, window_height }, 0.01f, 1000.0f);
    c.update();
}
int main()
{
    window window(window_width, window_height, "cs350_framework", true);
    camera c;
    setup_scene(c);
    debug_system debug(&c);
    while (window.update()) {    
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwPollEvents();
        debug.draw_point({ 0, 0, 0 }, { 1, 0, 0, 1 });
        debug.draw_segment({ 0, 0, -5 }, { -5, -5, -10 }, { 1, 1, 1, 1 });
        debug.draw_triangle({ 0, 1, 0 }, { -1, -1, 0 }, { 1, -1, 0 }, { 1, 1, 1, 1 });
        debug.draw_aabb({ -4, -2.5, -4 }, { 1, 2.5, 1 }, { 1, 0, 1, 1 });
        debug.draw_plane({ 0, 0, 0 }, glm::normalize(glm::vec3({ 1, 1, 1 })), 1.0f, { 1, 1, 1, 1 });
    }
    return 0;
}