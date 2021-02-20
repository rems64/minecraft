#include <MC/Graphics/VertexArray.hpp>

MC::VertexArray::VertexArray() : m_id(0)
{
	GLCall(glCreateVertexArrays(1, &m_id));
}

MC::VertexArray::VertexArray(const VertexArray& va2) : m_id(0)
{
	m_id = va2.m_id;
}

MC::VertexArray::~VertexArray()
{
	//GLCall(glDeleteVertexArrays(1, &m_id));
}

void MC::VertexArray::addBuffer(const MC::VertexBuffer& vb, const MC::VertexBufferLayout& layout)
{
	bind();
	vb.bind();
	const auto& elements = layout.getElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*)offset));
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

void MC::VertexArray::bind() const
{
	//std::cout << "[INFO] Index" << m_id << std::endl;
	GLCall(glBindVertexArray(m_id));
}

void MC::VertexArray::unbind() const
{
	GLCall(glBindVertexArray(0));
}
