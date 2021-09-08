#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include "math.hpp"

class camera
{
  private:
      mat4 mViewMatrix;
      mat4 mProjectionMatrix;
  public:
    //GIVEN
    void update();
    void set_projection(float fov_deg, glm::ivec2 const& window_size, float near, float far);
    void set_position(vec3 const&);
    void set_target(vec3 const&);
    //STUDENT
    camera();   
    ~camera();
    mat4 GetViewMatrix();
    mat4 GetProjectionMatrix();
};

#endif // __CAMERA_HPP__
