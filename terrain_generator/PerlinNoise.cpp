#include "PerlinNoise.h"

HeightMap PerlinNoise::generateHeightMap(
	int width, int height, float size,
	int octaves, float lacunarity, float persistance)
{
	HeightMap res(width, height);

	// Calculating factors to produce noise (for example 1 / (101 - 1) = 0.01)
	// Because of noise returns 0 when values equal to int values (for example 4.0, 5.0 etc)
	float xFactor = 1.0f / (width - 1);
	float yFactor = 1.0f / (height - 1);
	for (int row = 0; row < height; row++)
	{

		for (int col = 0; col < width; col++)
		{
			float x = col * xFactor / size;
			float y = row * yFactor / size;
			float frequency = lacunarity;
			float amplitude = persistance;
			// Noise
			float n = 0;
			for (int octave = 0; octave < octaves; octave++)
			{
				// Calculate and adjust to the range of [0, 1]
				float val = glm::perlin<float>(glm::vec2(frequency * x, frequency * y), glm::vec2(frequency)) / amplitude;
				n += (val + 1.0f) / 2.0f;
				frequency *= 2.0f;
				amplitude *= persistance;

			}
			n /= octaves;
			
			(res.data.get())[row * width + col] = (GLubyte)((n)  * 255.f);
		}

	}

	return res;

}
