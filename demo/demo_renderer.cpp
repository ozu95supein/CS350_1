#include "window.hpp"


int main()
{
    window window(1024,760, "cs350_framework", true);
    while (window.update()) {    
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    return 0;
}