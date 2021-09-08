#include "window.hpp"

window::window(int w, int h, const char* window_name, bool visible)
{
	//Init the library
	if (!glfwInit())
	{
		// Initialization failed
		//TODO PRINT OUT A GOOD ERROR CODE
		exit(EXIT_FAILURE);
	}
}
window::~window()
{
	glfwTerminate();
}