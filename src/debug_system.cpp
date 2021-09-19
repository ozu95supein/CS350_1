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
    // primitives ...
     //create a point
    mPoint = new primitive(E_POINT);
    mPoint->AddDebugVertex(glm::vec3(0.0f, 0.0f, 0.0f)); // MODEL SPACE
    mPoint->GenerateVertexBuffers();
    // segment
    mSegment = new primitive(E_SEGMENT);
    mSegment->AddDebugVertex(glm::vec3(0.0f, 0.0f, 0.0f)); // MODEL SPACE
    mSegment->AddDebugVertex(glm::vec3(1.0f, 1.0f, 1.0f)); // MODEL SPACE
    mSegment->GenerateVertexBuffers();  
    // triangle
    mTriangle = new primitive(E_TRIANGLE);  //ABC
    mTriangle->AddDebugVertex(glm::vec3(-0.5f, -0.5f, 0.0f));
    mTriangle->AddDebugVertex(glm::vec3(0.5f, -0.5f, 0.0f));
    mTriangle->AddDebugVertex(glm::vec3(0.0f, 0.5f, 0.0f));
    mTriangle->GenerateVertexBuffers();
    //AABB
    //stored attributes counter clockwise
    //front face
    glm::vec3 p0 = glm::vec3(-0.5, 0.5, 0.5);
    glm::vec3 p1 = glm::vec3(-0.5, -0.5, 0.5);
    glm::vec3 p2 = glm::vec3(0.5, -0.5, 0.5);
    glm::vec3 p3 = glm::vec3(0.5, 0.5, 0.5);
    //back face
    glm::vec3 p4 = glm::vec3(-0.5, 0.5, -0.5);
    glm::vec3 p5 = glm::vec3(-0.5, -0.5, -0.5);
    glm::vec3 p6 = glm::vec3(0.5, -0.5, -0.5);
    glm::vec3 p7 = glm::vec3(0.5, 0.5, -0.5);

    mAABB = new primitive(E_AABB);
    mAABB->AddDebugVertex(p0);
    mAABB->AddDebugVertex(p1);
    mAABB->AddDebugVertex(p3);

    mAABB->AddDebugVertex(p1);
    mAABB->AddDebugVertex(p2);
    mAABB->AddDebugVertex(p3);

    mAABB->AddDebugVertex(p3);
    mAABB->AddDebugVertex(p2);
    mAABB->AddDebugVertex(p7);

    mAABB->AddDebugVertex(p2);
    mAABB->AddDebugVertex(p6);
    mAABB->AddDebugVertex(p7);

    mAABB->AddDebugVertex(p7);
    mAABB->AddDebugVertex(p6);
    mAABB->AddDebugVertex(p4);

    mAABB->AddDebugVertex(p6);
    mAABB->AddDebugVertex(p5);
    mAABB->AddDebugVertex(p4);

    mAABB->AddDebugVertex(p4);
    mAABB->AddDebugVertex(p5);
    mAABB->AddDebugVertex(p0);

    mAABB->AddDebugVertex(p5);
    mAABB->AddDebugVertex(p1);
    mAABB->AddDebugVertex(p0);

    mAABB->AddDebugVertex(p4);
    mAABB->AddDebugVertex(p0);
    mAABB->AddDebugVertex(p7);

    mAABB->AddDebugVertex(p0);
    mAABB->AddDebugVertex(p3);
    mAABB->AddDebugVertex(p7);

    mAABB->AddDebugVertex(p1);
    mAABB->AddDebugVertex(p5);
    mAABB->AddDebugVertex(p2);

    mAABB->AddDebugVertex(p5);
    mAABB->AddDebugVertex(p6);
    mAABB->AddDebugVertex(p2);
    mAABB->GenerateVertexBuffers();
    //PLANE
    mPlane = new primitive(E_PLANE);
    mPlane->AddDebugVertex(glm::vec3(-0.5, 0.5, 0));
    mPlane->AddDebugVertex(glm::vec3(-0.5, -0.5, 0));
    mPlane->AddDebugVertex(glm::vec3(0.5, -0.5, 0));
    mPlane->AddDebugVertex(glm::vec3(0.5, 0.5, 0));
    mPlane->AddDebugVertex(glm::vec3(-0.5, 0.5, 0));
    mPlane->AddDebugVertex(glm::vec3(0.5, -0.5, 0));
    mPlane->GenerateVertexBuffers();
}
debug_system::~debug_system()
{
    //DELETE ALL SHADERS
    delete(mShader);
    mShader = NULL;
    //DELETE ALL PRIMITIVES
    delete(mPoint);
    mPoint = NULL;
}
void debug_system::draw_point(vec3 pt, vec4 color)
{
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
    glUniformMatrix4fv(0, 1, GL_FALSE, &(MVP[0][0]));
    glUniform4fv(1, 1, &(color[0]));

    //bind vao
    glBindVertexArray(mPoint->GetVAO());
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawArrays(GL_POINTS, 0, 1);
}
void debug_system::draw_segment(vec3 s, vec3 e, vec4 color)
{
    //enable backface culling
    glCullFace(GL_BACK);
    glUseProgram(mShader->GetShaderID());
    //create matrices
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), s);
    //get a direction vector
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0, 0.0, 1.0));
    glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), e);
    //model matrix
    glm::mat4 ModelMatrix = translationMatrix * rotationMatrix * scaleMatrix;//world space

    //Make MVP Matrix
    //mat4 MVP = u_P * u_V * u_M;
    glm::mat4 v = (mCampPtr)->GetViewMatrix();
    glm::mat4 p = (mCampPtr)->GetProjectionMatrix();
    glm::mat4 MVP = p * v * ModelMatrix;
    //pass them to program
    glUniformMatrix4fv(0, 1, GL_FALSE, &(MVP[0][0]));
    glUniform4fv(1, 1, &(color[0]));

    //bind vao
    glBindVertexArray(mSegment->GetVAO());
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawArrays(GL_LINES, 0, 2);
}
void debug_system::draw_triangle(vec3 a, vec3 b, vec3 c, vec4 color)
{
    mTriangle->TranslateVertexByIndex(0, a);
    mTriangle->TranslateVertexByIndex(1, b);
    mTriangle->TranslateVertexByIndex(2, c);
    //enable backface culling
    glCullFace(GL_BACK);
    glUseProgram(mShader->GetShaderID());
    //create matrices
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));
    //get a direction vector
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
    glUniformMatrix4fv(0, 1, GL_FALSE, &(MVP[0][0]));
    glUniform4fv(1, 1, &(color[0]));
    //bind vao
    glBindVertexArray(mTriangle->GetVAO());
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
void debug_system::draw_aabb(vec3 c, vec3 size, vec4 color)
{
    //enable backface culling
    glCullFace(GL_BACK);
    glUseProgram(mShader->GetShaderID());
    //create matrices
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), c);
    //get a direction vector
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0, 0.0, 1.0));
    glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), size);
    //model matrix
    glm::mat4 ModelMatrix = translationMatrix * rotationMatrix * scaleMatrix;//world space

    //Make MVP Matrix
    //mat4 MVP = u_P * u_V * u_M;
    glm::mat4 v = (mCampPtr)->GetViewMatrix();
    glm::mat4 p = (mCampPtr)->GetProjectionMatrix();
    glm::mat4 MVP = p * v * ModelMatrix;
    //pass them to program
    glUniformMatrix4fv(0, 1, GL_FALSE, &(MVP[0][0]));
    glUniform4fv(1, 1, &(color[0]));
    //bind vao
    glBindVertexArray(mAABB->GetVAO());
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
void debug_system::draw_plane(vec3 pt, vec3 n, float scale, vec4 color)
{
    //enable backface culling
    glCullFace(GL_BACK);
    glUseProgram(mShader->GetShaderID());
    //create matrices
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), pt);
    //get a direction vector
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0, 0.0, 1.0));
    glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(scale, scale, scale));
    //model matrix
    glm::mat4 ModelMatrix = translationMatrix * rotationMatrix * scaleMatrix;//world space
    //Make MVP Matrix
    //mat4 MVP = u_P * u_V * u_M;
    glm::mat4 v = (mCampPtr)->GetViewMatrix();
    glm::mat4 p = (mCampPtr)->GetProjectionMatrix();
    glm::mat4 MVP = p * v * ModelMatrix;
    //pass them to program
    glUniformMatrix4fv(0, 1, GL_FALSE, &(MVP[0][0]));
    glUniform4fv(1, 1, &(color[0]));
    //bind vao
    glBindVertexArray(mPlane->GetVAO());
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawArrays(GL_TRIANGLES, 0, 6);

}
void debug_system::draw_sphere(vec3 c, float r, glm::vec4 color)
{
    
}
void debug_system::draw_frustum_lines(mat4 const& vp, vec4 color)
{

}