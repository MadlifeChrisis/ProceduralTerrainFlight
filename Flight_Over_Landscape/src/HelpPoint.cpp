#include "HelpPoint.h"

HelpPoint::HelpPoint()
{
}

HelpPoint::~HelpPoint()
{
	hPointPositions[0] = 100.0f;
	hPointPositions[1] = 100.0f;
	hPointPositions[2] = 0.0f;
}

void HelpPoint::update()
{
}

void HelpPoint::render(Renderer renderer, Shader shader)
{
	// VAO
	VertexArray va;

	//Buffer objects
	VertexBuffer vb(hPointPositions, hPointVertexCount * sizeof(float));
	VertexBufferLayout layout;
	layout.Push<float>(3);

	va.addBuffer(vb, layout);
	IndexBuffer ib(hPointIndices, hPointIndexCount);


	shader.setUniform4f("uColor", 1.0f, 0.0f, 0.0f, 1.0f);

	renderer.drawPoint(va, ib, shader);
}
