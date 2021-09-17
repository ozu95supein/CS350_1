#include "shader.hpp"

ShaderClass::ShaderClass(char const* v, char const* f)
{
    char infoLog[512];
    int success;
    unsigned int vert_ID;
    unsigned int frag_ID;
    vert_ID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert_ID, 1, &v, NULL);
    glCompileShader(vert_ID);
    // print compile errors if any
    glGetShaderiv(vert_ID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << std::endl;
        exit(EXIT_FAILURE);
    };
    // fragment Shader
    frag_ID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag_ID, 1, &f, NULL);
    glCompileShader(frag_ID);
    // print compile errors if any
    glGetShaderiv(frag_ID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << std::endl;
        exit(EXIT_FAILURE);
    };
    // create complete shader Program
    mShaderProgramID = glCreateProgram();
    glAttachShader(mShaderProgramID, vert_ID);
    glAttachShader(mShaderProgramID, frag_ID);
    glLinkProgram(mShaderProgramID);
    // print linking errors if any
    glGetProgramiv(mShaderProgramID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(mShaderProgramID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        exit(EXIT_FAILURE);
    }
    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vert_ID);
    glDeleteShader(frag_ID);
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