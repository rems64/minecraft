#pragma once

#include <iostream>

#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

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
	struct SubObject
	{
		unsigned int m_va;
		unsigned int m_vb;
		unsigned int m_vbl;
		unsigned int m_ib;
		MC::Texture* m_texture;
	};
	class Object
	{
	public:
		Object();
		Object(MC::DataManager* datamanager, std::string shader);
		~Object();

		void render(glm::mat4* transMat, glm::mat4* modelMat, glm::mat4* viewMat, float [], std::vector<MC::Texture*> textures);
		void render(glm::mat4* transMat, bool twoSided);
		void renderAsLight(glm::mat4* PV);

		MC::VertexBuffer* getVertexBuffer();
		MC::VertexArray* getVertexArray();
		MC::VertexBufferLayout* getVertexBufferLayout();
		MC::IndexBuffer* getIndexBuffer();
		std::vector<glm::vec3>* getVertices();

		glm::mat4 getModelTransformMatrix();

		void updateTransform();

		void bind();
		void unbind();
		void drawCall(glm::mat4 PV, glm::mat4 view, glm::vec3 lightPos);

		void setTransform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
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

		glm::vec3 m_position;
		glm::vec3 m_scale;
		glm::vec3 m_rotation;

		glm::mat4 m_modelTransformMatrix;
	};
}