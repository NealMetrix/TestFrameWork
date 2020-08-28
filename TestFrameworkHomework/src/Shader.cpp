#include "Shader.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <sstream>

#include "render.h"

/*Constructors and Destructors*/
shaders::shaders(const std::string& Filepath)
	:m_filepath(Filepath),m_rendererID(0)
{
    shadeComponents shadeSource = parseShader(Filepath);
    m_rendererID = CreateShader(shadeSource.Vertexsource, shadeSource.Fragmentsource);
}
shaders::~shaders()
{
    GLcall(glDeleteProgram(m_rendererID));
}

/*Compile methods*/
shadeComponents shaders::parseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);

    enum class shaderType
    {
        None = -1, Vertex = 0, Fragment = 1
    };

    std::string line;
    std::stringstream shaderSequence[2];
    shaderType type = shaderType::None;

    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = shaderType::Vertex;

            else if (line.find("fragment") != std::string::npos)
                type = shaderType::Fragment;

            else { std::cout << "Warning: invalid shader specification... shader type remains unchanged" << std::endl; }
        }
        else
        {
            std::cout << line << std::endl;//This writes our shader code on the console
            if (type == shaderType::None)
                std::cout << "Error: no shaderType" << std::endl;

            shaderSequence[(int)type] << line << std::endl;
        }
    }

    return { shaderSequence[0].str(), shaderSequence[1].str() };
}
unsigned int shaders::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = &source[0];

    GLcall(glShaderSource(id, 1, &src, nullptr));
    GLcall(glCompileShader(id));

    int result;
    GLcall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE)
    {
        int length;
        GLcall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*)_malloca(length * sizeof(char));
        GLcall(glGetShaderInfoLog(id, length, &length, message));
        std::cout << "Shader Compile Failure " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
        GLcall(glDeleteShader(id));
        return 0;
    }

    return id;
}
int shaders::CreateShader(const std::string& vertexShade, const std::string& fragmentShade)
{
    GLcall(unsigned int program = glCreateProgram());
    unsigned int vtx = CompileShader(GL_VERTEX_SHADER, vertexShade);
    unsigned int frag = CompileShader(GL_FRAGMENT_SHADER, fragmentShade);

    GLcall(glAttachShader(program, vtx));
    GLcall(glAttachShader(program, frag));
    GLcall(glLinkProgram(program));
    GLcall(glValidateProgram(program));/*Question... Is it required to validate the program or is it just extremely useful
                                       for debugging*/

    GLcall(glDeleteShader(vtx));
    GLcall(glDeleteShader(frag));

    return program;
}

/*Bind Methods*/
void shaders::bind()const
{
    GLcall(glUseProgram(m_rendererID));
}
void shaders::unbind()const
{
    GLcall(glUseProgram(0));
}

/*Uniform Methods*/
void shaders::setUniform1i(const std::string& name, int value)
{
    GLcall(glUniform1i(getUniformLocation(name), value));
}
void shaders::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    GLcall(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
}
void shaders::setUniform1f(const std::string& name, float value)
{
    GLcall(glUniform1f(getUniformLocation(name), value));
}
void shaders::setUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
    GLcall(glUniformMatrix4fv(getUniformLocation(name), 1,GL_FALSE,&matrix[0][0]));
    /*So the first parameter is of course the uniform location
    Parameter 2: How many matrices we are providing. We are just giving it one matrix
    Parameter 3: Does the matrix need to be transposed or not. This would be GL_TRUE if the library stored the matrix in memory
        as rows instead of columns. But glm does it in a way that OpenGL expects
        which is that it stores the matrix data in columns and not rows
    Parameter 4: The refrence/pointer to the matrix. Usually should be the starting matrix value.*/
}

unsigned int shaders::getUniformLocation(const std::string& name)
{
    if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
        return m_uniformLocationCache[name];

    GLcall(int location = glGetUniformLocation(m_rendererID, name.c_str()));
    if (location == -1)
        std::cout << "Warning: uniform " << name << " doesn't exist!" << std::endl;

    m_uniformLocationCache[name] = location;
    return location;
}