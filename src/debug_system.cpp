#include "debug_system.hpp"

namespace {
    char const* c_vertex_shader = R"(
#version 440 core
layout(location = 0) in vec3 attr_position;
layout(location = 0) uniform mat4 uniform_mvp;
void main()
{
    vec4 vertex = vec4(attr_position, 1.0f);
    gl_Position = uniform_mvp * vertex;
}
)";

    char const* c_fragment_shader = R"(
#version 440 core
out vec4 out_color;
layout(location = 1) uniform vec4 uniform_color;
void main()
{
    out_color = uniform_color;
}
)";
}