#pragma once
#include <GL/glew.h>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"



class Renderer {
public:
	void clear() const;
	void drawTriangle(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
	void drawPoint(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};