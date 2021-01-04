#include "Shader.h"

// Static constants initialization;
const char* Shader::VERTEX_SHADER_EXTENSION = ".vert";
const char* Shader::TESS_CONTROL_SHADER_EXTENSION = ".tesc";
const char* Shader::TESS_EVALUATION_SHADER_EXTENSION = ".tese";
const char* Shader::GEOMETRY_SHADER_EXTENSION = ".geom";
const char* Shader::FRAGMENT_SHADER_EXTENSION = ".frag";
const char* Shader::COMPUTE_SHADER_EXTENSION = ".comp";

bool Shader::loadFromFile(std::string filename)
{

    // Getting a shader exception
    try
    {
        this->type = getShaderTypeFromFilename(filename);
    }
    catch (const std::invalid_argument& ex)
    {
        printf(ex.what());
        return false;
    }

    this->id = glCreateShader(this->type);
    std::ifstream file = std::ifstream(filename, std::ifstream::binary);
    std::vector<char> buf = std::vector<char>(std::istreambuf_iterator<char>(file),  std::istreambuf_iterator<char>());
    const GLchar* srcPointer = { (const GLchar*)(&(buf.front())) };
    GLint srcLength[] = { buf.size() };
    glShaderSource(this->id, 1, &srcPointer, srcLength);
    GLint isCompiled = 0;
    glCompileShader(this->id);
    glGetShaderiv(this->id, GL_COMPILE_STATUS, &isCompiled);
    // Shader was not compiled
    if (isCompiled == GL_FALSE)
    {
        // Get error string
        GLchar errBuf[256];
        GLsizei errorLogLength = 0;
        glGetShaderInfoLog(this->id, 256, &errorLogLength, errBuf);
        // Free resources
        glDeleteShader(this->id);
        return false;
    }
    return true;
}

GLuint Shader::getId()
{
    return this->id;
}

GLenum Shader::getType()
{
    return this->type;
}

GLenum Shader::getShaderTypeFromFilename(std::string filename)
{

    // Get extension from filename
    const char* delimiter = ".";
    int delimiterOffset = filename.find(delimiter);
    std::string extension = filename.substr(
        delimiterOffset,
        filename.size() - delimiterOffset
    );
    std::map<std::string, GLenum> strToShaderType = {
        {VERTEX_SHADER_EXTENSION,           GL_VERTEX_SHADER},
        {TESS_CONTROL_SHADER_EXTENSION,     GL_TESS_CONTROL_SHADER},
        {TESS_EVALUATION_SHADER_EXTENSION,  GL_TESS_EVALUATION_SHADER},
        {GEOMETRY_SHADER_EXTENSION,         GL_GEOMETRY_SHADER},
        {FRAGMENT_SHADER_EXTENSION,         GL_FRAGMENT_SHADER},
        {COMPUTE_SHADER_EXTENSION,          GL_COMPUTE_SHADER}
    };
    if (strToShaderType.find(extension) == strToShaderType.end())
    {
        char buffer[100];
        sprintf_s(buffer, 100, "Shader file extension %s doesn't supported\n", extension.c_str());
        throw std::invalid_argument(buffer);
    }

    return strToShaderType[extension];
}
