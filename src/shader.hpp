#ifndef __SHADER_HPP__
#define __SHADER_HPP__
#include "opengl.hpp"

class ShaderClass
{
private:
	char const* vertShaderString = NULL;
	char const* fragShaderString = NULL;
	GLuint mShaderProgramID;
	GLuint CompileAttachShader(GLuint ID, const char* source, GLuint shaderType);
	GLuint LinkProgram(GLuint programHandle);
public:
	ShaderClass(char const* v, char const* f);
	~ShaderClass();
	unsigned int GetShaderID();
};
#endif // __SHADER_HPP__
