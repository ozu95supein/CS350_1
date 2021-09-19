#include "window.hpp"

static void custom_error_callback(int error, const char* description)
{
	std::cout<< "Error number:  "<< error << ", "<< description <<std::endl;
	exit(EXIT_FAILURE);
}

static void custom_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		
	}
	if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{

	}
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{

	}
	if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{

	}
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{

	}
	if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_PRESS)
	{

	}
	if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS)
	{

	}
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{

	}
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{

	}
}
window::window(int w, int h, const char* window_name, bool visible)
{
	//set the error callback to the function defined above in case of error
	glfwSetErrorCallback(custom_error_callback);

	//Init the library and check if init is successful
	if (!glfwInit())
	{
		// Initialization failed
		//TODO PRINT OUT A GOOD ERROR CODE
		exit(EXIT_FAILURE);
	}
	//set hints and create the window, setting it to local var mWindow
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	mWindow = glfwCreateWindow(w, h, window_name, NULL, NULL);
	if (!mWindow)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	//sets initial visibility
	glfwWindowHint(GLFW_VISIBLE, visible);
	//sets the key callback so when we press escape key it sets the windowshould close bool to true
	glfwSetKeyCallback(mWindow, custom_key_callback);
	//This function makes the OpenGL or OpenGL ES context of the specified window
	glfwMakeContextCurrent(mWindow);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize OpenGL context" << std::endl;
		exit(EXIT_FAILURE);
	}
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glViewport(0, 0, w, h);
}
window::~window()
{
	destroy();
}
void window::destroy()
{
	glfwDestroyWindow(mWindow);
	glfwTerminate();
}
bool window::update()
{
	if (!glfwWindowShouldClose(mWindow))
	{
		//update the windo width and height, ratio if necessary
		float ratio;
		int width, height;
		glfwGetFramebufferSize(mWindow, &width, &height);
		ratio = width / (float)height;
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);
		//
		// do we need to set the program here as well as render stuff?
		//
		glfwSwapBuffers(mWindow);
		glfwPollEvents();
		return true;
	}
	else
	{
		destroy();
		return false;
	}
}