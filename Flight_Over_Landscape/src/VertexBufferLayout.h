#pragma once
#include <vector>
#include <GL/glew.h>

struct vertexBufferElement {
	unsigned int type;
	unsigned int count;
	unsigned int normalized;

	static unsigned int getSizeOfType(unsigned int type) {
		switch (type)
		{
		case GL_FLOAT: return 4;
		case GL_UNSIGNED_INT: return 4;
		default:
			break;
		}
		return(0);
	}
};

class VertexBufferLayout{
private:
	std::vector<vertexBufferElement> m_Elements;
	unsigned int m_Stride;
public:
	VertexBufferLayout()
	: m_Stride(0) {}



	template<typename T>
	void Push(unsigned int count){
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count) {

		struct vertexBufferElement temp = {GL_FLOAT, count, GL_FALSE};
		
		m_Elements.push_back({temp});
		m_Stride += vertexBufferElement::getSizeOfType(GL_FLOAT) * count;
	}

	template<>
	void Push<unsigned int>(unsigned int count) {

		struct vertexBufferElement temp = { GL_UNSIGNED_INT, count, GL_FALSE };

		m_Elements.push_back({ temp });
		m_Stride += vertexBufferElement::getSizeOfType(GL_UNSIGNED_INT) * count;
	}

	inline const std::vector<vertexBufferElement> getElements() const& { return m_Elements;}
	inline unsigned int getStride() const { return m_Stride; }
};