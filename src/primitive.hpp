#ifndef __PRIMITIVE_HPP__
#define __PRIMITIVE_HPP__

#include "opengl.hpp"
#include <vector>
struct DebugVertex
{
	DebugVertex(glm::vec3 p, glm::vec4 c) : position(p), color(c) {}
	glm::vec3 position;
	glm::vec4 color;
};
enum P_TYPE {E_POINT = 0, E_LINE = 1, E_TRIANGLE = 2, E_PLANE = 3, E_AABB = 4, E_SPHEREDISC = 5};
class primitive
{
private:
	std::vector <DebugVertex> mVertexList;
	P_TYPE mType;
	GLuint mVBO;
	GLuint mVAO;
public:
	primitive(P_TYPE p);	//constructor that will make primitives based on the type that is passed
	~primitive();
	
};

#endif // __PRIMITIVE_HPP__
