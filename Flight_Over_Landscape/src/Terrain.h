#pragma once
#include "Renderer.h"
#include "Shader.h"
#include <iostream>


class Terrain
{
private:

	
	unsigned int terrainVertexCount = 7500;
	float terrainPositions[7500];


	int rows, cols;
	unsigned int terrainIndexCount = 14406;
	unsigned int terrainIndices[14406];
	
	// (rows - 1) * (cols - 1) * 6 
	


public:

	Terrain();
	~Terrain();
	void update();
	void render(Renderer renderer, Shader shader);

};

