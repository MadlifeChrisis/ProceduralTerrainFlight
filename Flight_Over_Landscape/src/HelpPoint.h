#pragma once
#include "Renderer.h"
#include "Shader.h"
#include <iostream>

class HelpPoint
{
private:

	unsigned int hPointVertexCount = 3;
	float hPointPositions[3];


	unsigned int hPointIndexCount = 1;
	unsigned int hPointIndices[1] = {0};




public:

	HelpPoint();
	~HelpPoint();
	void update();
	void render(Renderer renderer, Shader shader);

};

