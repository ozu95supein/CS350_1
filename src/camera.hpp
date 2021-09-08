#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include "math.hpp"

class camera
{
  private:
  public:
    void update();
    void set_projection(float fov_deg, glm::ivec2 const& window_size, float near, float far);
    void set_position(vec3 const&);
    void set_target(vec3 const&);
};

#endif // __CAMERA_HPP__
