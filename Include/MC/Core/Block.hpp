#pragma once

#include <MC/Graphics/VertexArray.hpp>

#include <glm/common.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <MC/Graphics/Texture.hpp>
#include <MC/Graphics/ProceduralTexture.hpp>
#include <MC/Graphics/IndexBuffer.hpp>
#include <MC/Graphics/VertexArray.hpp>
#include <MC/Graphics/Shader.hpp>

#include <MC/Core/DataManager.hpp>

#include <MC/Debug.hpp>
#include <GL/glew.h>

namespace MC
{
	class Block
	{
	public:
		Block();
		Block(MC::DataManager*);
		Block(MC::DataManager* , glm::vec3);
		~Block();

		void render(glm::mat4*);
		void render(glm::mat4*, MC::Texture*);

	private:
		MC::DataManager* m_dataManager;
		glm::vec3 m_position;
		MC::Texture m_texture;

		MC::IndexBuffer* m_indexBuffer;
		MC::VertexArray* m_vertexArray;

		MC::Shader m_shader;
	};
}