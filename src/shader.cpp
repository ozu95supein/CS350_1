#include "shader.hpp"

ShaderClass::ShaderClass(char const* v, char const* f)
{
	GLuint ID = glCreateProgram();
    if (ID == 0)
    {
        std::cout << "Unable to create shader program." << std::endl;
        exit(EXIT_FAILURE);
    }
    // vertex shader
    if (CompileAttachShader(ID, v, GL_VERTEX_SHADER) == 0)
    {
        std::cout << "Unable to create VERTEX shader program." << std::endl;
        exit(EXIT_FAILURE);
    }
    // fragment shader
    if (CompileAttachShader(ID, f, GL_FRAGMENT_SHADER) == 0)
    {
        std::cout << "Unable to create FRAG shader program." << std::endl;
        exit(EXIT_FAILURE);
    }
    //Link the programs together
    if (LinkProgram(ID) == 0)
    {
        std::cout << "Unable to LINK shader program." << std::endl;
        exit(EXIT_FAILURE);
    }
    mShaderProgramID = ID;
}
ShaderClass::~ShaderClass()
{
    glDeleteProgram(mShaderProgramID);
}
GLuint ShaderClass::CompileAttachShader(GLuint ID, const char* source, GLuint shaderType)
{
    // Create shader
    GLuint shaderhandle = 0;
    shaderhandle = glCreateShader(shaderType);
    glShaderSource(shaderhandle, 1, &source, NULL);
    // Compile the shader
    glCompileShader(shaderhandle);
    // Check for errors
    int result;
    glGetShaderiv(shaderhandle, GL_COMPILE_STATUS, &result);
    if (GL_FALSE == result)
    {
        // Compile failed, store log and return false
        int length = 0;

        glGetShaderiv(shaderhandle, GL_INFO_LOG_LENGTH, &length);
        if (length > 0)
        {
            char* c_log = new char[static_cast<size_t>(length) + 1];
            int    written = 0;
            glGetShaderInfoLog(shaderhandle, length, &written, c_log);
            std::cout << c_log << std::endl;
            delete[] c_log;
        }
        return 0;
    }
    else
    {
        // Compile succeeded, attach shader and return true
        glAttachShader(shaderhandle, shaderhandle);

        glDeleteShader(shaderhandle);
        return shaderhandle;
    }
}
GLuint ShaderClass::LinkProgram(GLuint programHandle)
{
    if (programHandle <= 0)
        return 0;

    // Link shader program
    glLinkProgram(programHandle);

    // Check for errors
    int status = 0;
    glGetProgramiv(programHandle, GL_LINK_STATUS, &status);
    if (GL_FALSE == status)
    {
        // Store log and return false
        int length = 0;

        glGetProgramiv(programHandle, GL_INFO_LOG_LENGTH, &length);
        if (length > 0)
        {
            char* c_log = new char[static_cast<size_t>(length) + 1];
            int    written = 0;
            glGetProgramInfoLog(programHandle, length, &written, c_log);
            std::cout << c_log << std::endl;
            delete[] c_log;
        }

        return 0;
    }
    return programHandle;
}
unsigned int ShaderClass::GetShaderID()
{
    return mShaderProgramID;
}