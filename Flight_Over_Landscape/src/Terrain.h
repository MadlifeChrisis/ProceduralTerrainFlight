#pragma once
#include "Renderer.h"
#include "Shader.h"

#include "PerlinNoise.h"
#include <iostream>


class Terrain
{
private:
	PerlinNoise* pn = new PerlinNoise(123);
	
	unsigned int terrainVertexCount = 7500;
	float terrainPositions[7500];


	int rows, cols;
	unsigned int terrainIndexCount = 14406;
	unsigned int terrainIndices[14406];
	
	// (rows - 1) * (cols - 1) * 6 
	float perlinX, perlinY;


public:

	Terrain();
	~Terrain();
	void update();
	void render(Renderer renderer, Shader shader);

};

