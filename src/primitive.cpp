#include "primitive.hpp"

primitive::primitive(P_TYPE p)	//constructor that will make primitives based on the type that is passed
{
	/*
	switch (p)
	{
	case E_POINT:
		mType = p;
		break;
	case E_LINE:
		mType = p;
		break;
	case E_TRIANGLE:
		mType = p;
		break;
	case E_PLANE:
		mType = p;
		break;
	case E_AABB:
		mType = p;
		break;
	case E_SPHEREDISC:
		mType = p;
		break;
	}*/
	mType = p;
	//initialize everything to 0;
	mVBO = 0;
	mVAO = 0;
	mVertexList.clear();
}
primitive::~primitive()
{
	mVBO = 0;
	mVAO = 0;
	mVertexList.clear();
}
void primitive::AddDebugVertex(glm::vec3 p, glm::vec4 c)
{
	DebugVertex v(p, c);
	mVertexList.push_back(v);
}
void primitive::GenerateVertexBuffers()
{
	switch (mType)
	{
	case E_POINT:
		GeneratePointBuffers(mVBO, mVAO);
		break;
	case E_LINE:
		break;
	case E_TRIANGLE:
		break;
	case E_PLANE:
		break;
	case E_AABB:
		break;
	case E_SPHEREDISC:
		break;
	}
}
void primitive::GeneratePointBuffers(GLuint& vbo, GLuint& vao)
{	   //keeping this for the future just in case
	// auto v = *(mVertexList.begin());
	// unsigned long stride = sizeof(v);
	unsigned long stride = sizeof(DebugVertex);

	// create buffer for VAO
	glGenVertexArrays(1, &vao);
	// create buffer for VBO
	glGenBuffers(1, &vbo);
	//bind so we are now doing stuff to the vao
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//TOOD FIX
	glBufferData(GL_ARRAY_BUFFER, (sizeof(DebugVertex)), (const void*)&(*(mVertexList.begin())), GL_STATIC_DRAW);

}
