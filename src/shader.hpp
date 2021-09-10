#ifndef __SHADER_HPP__
#define __SHADER_HPP__
#include "opengl.hpp"

class ShaderClass
{
private:
	char const* vertShaderString = NULL;
	char const* fragShaderString = NULL;
	GLuint mShaderProgramID;
	
public:
	ShaderClass();
	~ShaderClass();
	void SetVertAndFragStrings(char const* v, char const* f);
	void CreatePrograme();
	void UseShader();

};
#endif // __SHADER_HPP__
