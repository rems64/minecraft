#include <MC/Graphics/VertexBuffer.hpp>

MC::VertexBuffer::VertexBuffer()
{
	GLCall(glCreateBuffers(1, &m_id));
}

MC::VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	GLCall(glGenBuffers(1, &m_id));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_id));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

MC::VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_id));
}

void MC::VertexBuffer::setBuffer(const void* data, unsigned int size)
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_id));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

void MC::VertexBuffer::bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_id));
}

void MC::VertexBuffer::unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}