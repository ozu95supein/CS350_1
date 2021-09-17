#include "camera.hpp"

struct DebugVertex
{
	DebugVertex(glm::vec3 p) : position(p) {}
	glm::vec3 position;
};
//: mCamPos(glm::vec3(0.0f)), mCamTGT(glm::vec3(0.0f)), mfov_deg(0.0f), mwindow_size(glm::ivec2(0)), mnear(0.0f), mfar(0.0f), mViewMatrix
camera::camera() 
{
	mCamPos = glm::vec3(0.0f);
	mCamTGT = glm::vec3(0.0f);
	mfov_deg = 0.0f;
	mwindow_size = glm::ivec2(0);
	mnear = 0.0f;
	mfar = 0.0f;
	mViewMatrix = mat4(1.0f);
	mProjectionMatrix = mat4(1.0f);
	//compute matrices
	// set individual memeber var floats for view and prerspective to be modified, construct matrices only in update at the end of update
}
camera::~camera()
{

}
void camera::ConstructMatrices()
{
	//Creating projection matrix
	float a = mwindow_size.x / mwindow_size.y;
	mProjectionMatrix = glm::perspective(glm::radians(mfov_deg), a, mnear, mfar);
	//setting camera view position
	mViewMatrix = glm::translate(mViewMatrix, mCamPos);
	//setting camera view target
	mViewMatrix = glm::lookAt(mCamPos, mCamTGT, glm::vec3(0.0f, 1.0f, 0.0f));
}
void camera::update()
{


	//, construct matrices only in update at the end of update
	ConstructMatrices();
}
void camera::set_projection(float fov_deg, glm::ivec2 const& window_size, float near, float far)
{
	mfov_deg = fov_deg;
	mwindow_size = window_size;
	mnear = near;
	mfar = far;
}
void camera::set_position(vec3 const& v)
{
	mCamPos = v;
}
void camera::set_target(vec3 const& v)
{
	mCamTGT = v;
}
mat4 camera::GetViewMatrix() const
{
	return mViewMatrix;
}
mat4 camera::GetProjectionMatrix() const
{
	return mProjectionMatrix;
}