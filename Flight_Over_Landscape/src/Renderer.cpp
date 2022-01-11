#include "Renderer.h"

#include <iostream>

void Renderer::clear() const{

	// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::drawTriangle(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const{
	

	shader.bind();
	va.bind();
	ib.bind();
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
	

}


void Renderer::drawPoint(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {


	shader.bind();
	va.bind();
	ib.bind();
	glPointSize(10.0);
	glDrawElements(GL_POINTS, ib.GetCount(), GL_UNSIGNED_INT, nullptr);


}

