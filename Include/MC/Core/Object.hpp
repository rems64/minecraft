#pragma once

#include <iostream>

#include <MC/Graphics/VertexBuffer.hpp>
#include <MC/Graphics/IndexBuffer.hpp>
#include <MC/Graphics/VertexBufferLayout.hpp>
#include <MC/Graphics/VertexArray.hpp>
#include <MC/Graphics/Texture.hpp>
#include <MC/Graphics/Shader.hpp>

#include <MC/Debug.hpp>
#include <GL/glew.h>


namespace MC
{
	class DataManager;
	class Object
	{
	public:
		Object();
		Object(MC::DataManager* datamanager);
		~Object();

		void render(glm::mat4* transMat, std::vector<MC::Texture*> textures);

		MC::VertexBuffer* getVertexBuffer();
		MC::VertexArray* getVertexArray();
		MC::VertexBufferLayout* getVertexBufferLayout();
		MC::IndexBuffer* getIndexBuffer();
		std::vector<glm::vec3>* getVertices();

	private:
		MC::DataManager* m_dataManager;
		MC::VertexArray m_vertexArray;
		MC::VertexBuffer m_vertexBuffer;
		MC::VertexBufferLayout m_vertexBufferLayout;
		MC::IndexBuffer m_indexBuffer;
		MC::Shader m_shader;

		std::vector<glm::vec3> m_vertices;
		std::vector<glm::vec3> m_uvs;
		std::vector<glm::vec3> m_normals;
	};
}