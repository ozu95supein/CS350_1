#ifndef __WINDOW_HPP__
#define __WINDOW_HPP__

#include "opengl.hpp"
class camera;
class window
{
  private:
      GLFWwindow* mWindow;
  public:
    window(int w, int h, const char* window_name, bool visible);
    ~window();
    bool update();
    void destroy(); //unused for now
    GLFWwindow* GetWindowPointer();
};

#endif // __WINDOW_HPP__
