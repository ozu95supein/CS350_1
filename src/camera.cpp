#include "camera.hpp"

camera::camera()
{
	mViewMatrix = mat4(1.0f);
	mProjectionMatrix = mat4(1.0f);
}
camera::~camera()
{

}
void camera::update()
{

}
void camera::set_projection(float fov_deg, glm::ivec2 const& window_size, float near, float far)
{
	float a = window_size.x / window_size.y;
	mProjectionMatrix = glm::perspective(glm::radians(fov_deg), a, near, far);
}
void camera::set_position(vec3 const& v)
{
	//LIGHT_translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(light_x, light_y, light_z));
	mViewMatrix = glm::translate(mViewMatrix, v);
}
void camera::set_target(vec3 const& v)
{
	vec3 campos;
	campos.x = mViewMatrix[3].x;
	campos.y = mViewMatrix[3].y;
	campos.z = mViewMatrix[3].z;
	mViewMatrix = glm::lookAt(campos, v, glm::vec3(0.0f, 1.0f, 0.0f));
}
mat4 camera::GetViewMatrix()
{
	return mViewMatrix;
}
mat4 camera::GetProjectionMatrix()
{
	return mProjectionMatrix;
}