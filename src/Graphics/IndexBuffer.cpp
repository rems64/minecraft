#include <MC/Graphics/IndexBuffer.hpp>

MC::IndexBuffer::IndexBuffer() : m_count(0)
{
	GLCall(glGenBuffers(1, &m_id));
}

MC::IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) : m_count(count)
{
	GLCall(glGenBuffers(1, &m_id));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW))
}

MC::IndexBuffer::~IndexBuffer()
{
	//GLCall(glDeleteBuffers(1, &m_id));
}

void MC::IndexBuffer::setBuffer(const unsigned int* data, unsigned int count)
{
	m_count = count;
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW))
}


void MC::IndexBuffer::bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
}

void MC::IndexBuffer::unbind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void MC::IndexBuffer::debugPrint() const
{
	auto ptr = glMapBufferRange(m_id, 0, 1, GL_MAP_READ_BIT);
	std::cout << ptr << std::endl;
}