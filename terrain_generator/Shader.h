#pragma once
#include <string>
#include <GL/glew.h>
#include <fstream>
#include <map>
#include <vector>

class Shader
{
public:
	// Loads shader from file and initializes it
	bool loadFromFile(std::string filename);
	// Getters
	GLuint getId();
	GLenum getType();

private:
	GLenum getShaderTypeFromFilename(std::string filename) noexcept(false);

public:
	static const char* VERTEX_SHADER_EXTENSION;
	static const char* TESS_CONTROL_SHADER_EXTENSION;
	static const char* TESS_EVALUATION_SHADER_EXTENSION;
	static const char* GEOMETRY_SHADER_EXTENSION;
	static const char* FRAGMENT_SHADER_EXTENSION;
	static const char* COMPUTE_SHADER_EXTENSION;
private:
	GLenum type;
	GLuint id;
};

