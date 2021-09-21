#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include "math.hpp"
static void camera_move_forward();

class camera
{
  private:
      glm::vec3 mCameraPos;
      glm::vec3 mCameraFront;
      glm::vec3 mCameraUp;
      float mfov_deg;
      glm::ivec2 mwindow_size;
      float mAspect;
      float mnear;
      float mfar;
      mat4 mViewMatrix;
      mat4 mProjectionMatrix;
  public:
    //GIVEN
    void update();
    void set_projection(float fov_deg, glm::ivec2 const& window_size, float near, float far);
    void set_position(vec3 const&);
    void set_Dir(vec3 const&);
    void set_Up(vec3 const&);
    void set_target(vec3 const&);

    //STUDENT
    camera();   
    ~camera();
    mat4 GetViewMatrix() const;
    mat4 GetProjectionMatrix() const;
    void ConstructMatrices();
    void InputMove_Up();
    void InputMove_Down();
    void InputMove_Left();
    void InputMove_Right();
    void InputMove_Shift();
    void InputMove_Ctrl();
    void InputMove_Space();
};

#endif // __CAMERA_HPP__
