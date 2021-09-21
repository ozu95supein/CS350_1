#include "camera.hpp"
#include <iostream>

//: mCamPos(glm::vec3(0.0f)), mCamTGT(glm::vec3(0.0f)), mfov_deg(0.0f), mwindow_size(glm::ivec2(0)), mnear(0.0f), mfar(0.0f), mViewMatrix
camera::camera() 
{
	mCameraPos =  glm::vec3(0.0f, 0.0f, 0.0f);
	mCameraFront = glm::vec3(0.0f, 0.0f, 1.0f);
	mCameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

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
	mProjectionMatrix = glm::perspective(glm::radians(mfov_deg), mAspect, mnear, mfar);
	//setting camera view position
	mViewMatrix = glm::translate(mViewMatrix, mCameraPos);
	//setting camera view target
	mViewMatrix = glm::lookAt(mCameraPos, (mCameraPos + mCameraFront), glm::vec3(0.0f, 1.0f, 0.0f));
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
	mAspect = mwindow_size.x / mwindow_size.y;
}
void camera::set_position(vec3 const& v)
{
	mCameraPos = v;
}
void camera::set_target(vec3 const& t)
{
	glm::vec3 resultdir = t - mCameraPos;
	mCameraFront = glm::normalize(resultdir);
}
void camera::set_Dir(vec3 const& v)
{
	mCameraFront = v;
}
mat4 camera::GetViewMatrix() const
{
	return mViewMatrix;
}
mat4 camera::GetProjectionMatrix() const
{
	return mProjectionMatrix;
}