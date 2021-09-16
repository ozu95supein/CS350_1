#include "debug_system.hpp"
#include "opengl.hpp"
#include "shader.hpp"
#include "primitive.hpp"
#include "camera.hpp"
//like a global var for this file only
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

debug_system::debug_system(camera const* c)
{
    mCampPtr = c;
    mShader = new ShaderClass(c_vertex_shader, c_fragment_shader);
    
}
debug_system::~debug_system()
{
    delete(mShader);
    mShader = NULL;
}
void debug_system::draw_point(vec3 pt, vec4 color)
{
    //create a primitive
    primitive PrimitivePoint(E_POINT);
    PrimitivePoint.AddDebugVertex(pt, color);
    //enable backface culling
    glCullFace(GL_BACK);
    glUseProgram(mShader->GetShaderID());
    
    //create matrices
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), pt);
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0, 0.0, 1.0));
    glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    //model matrix
    glm::mat4 ModelMatrix = translationMatrix * rotationMatrix * scaleMatrix;//world space
    //Make MVP Matrix
    //mat4 MVP = u_P * u_V * u_M;
    glm::mat4 v = (mCampPtr)->GetViewMatrix();
    glm::mat4 p = (mCampPtr)->GetProjectionMatrix();
    glm::mat4 MVP = p * v * ModelMatrix;

    //pass them to program
    GLint mvp = glGetUniformLocation(mShader->GetShaderID(), "uniform_mvp");
    glUniformMatrix4fv(mvp, 1, GL_FALSE, &(MVP[0][0]));
    //bind vao
    glBindVertexArray();
}
void debug_system::draw_segment(vec3 s, vec3 e, vec4 color)
{

}
void debug_system::draw_triangle(vec3 a, vec3 b, vec3 c, vec4 color)
{

}
void debug_system::draw_aabb(vec3 c, vec3 size, vec4 color)
{

}
void debug_system::draw_plane(vec3 pt, vec3 n, float scale, vec4 color)
{

}
void debug_system::draw_sphere(vec3 c, float r, glm::vec4 color)
{

}
void debug_system::draw_frustum_lines(mat4 const& vp, vec4 color)
{

}