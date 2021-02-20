#pragma once

#include <GL/glew.h>
#include <MC/Debug.hpp>
#include <MC/Graphics/VertexBuffer.hpp>
#include <MC/Graphics/VertexBufferLayout.hpp>

namespace MC
{
	class VertexArray
	{
	public:
		VertexArray();
		VertexArray(const VertexArray&);
		~VertexArray();

		void addBuffer(const MC::VertexBuffer& vb, const MC::VertexBufferLayout& layout);

		void bind() const;
		void unbind() const;

	private:
		unsigned int m_id;
	};
}