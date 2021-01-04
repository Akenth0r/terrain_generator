#pragma once
#include <vector>
#include <gtc/noise.hpp>
#include <glm.hpp>
#include <GL/glew.h>
#include <memory>

struct HeightMap
{
    int width;
    int height;
    std::shared_ptr<GLubyte> data;

    HeightMap(int width, int height)
    {
        this->width = width;
        this->height = height;
        data = std::shared_ptr<GLubyte>(new GLubyte[width * height]);
    }
};

class PerlinNoise
{
public: 
    static HeightMap generateHeightMap(
        int width, int height, float size,
        int octaves, float lacunarity, float persistance
    );
};

