#include <MC/Core/Object.hpp>

MC::Object::Object() : m_shader("../../../Shaders/basic.glsl"), m_dataManager(nullptr)
{
	m_shader.compile();
}

MC::Object::Object(MC::DataManager* datamanager) : m_shader("../../../Shaders/basic.glsl"), m_dataManager(datamanager)
{
	m_shader.compile();
	INFO({ "Shader successfully compiled" });
}

MC::Object::~Object()
{
}

MC::VertexBuffer* MC::Object::getVertexBuffer()
{
	return &m_vertexBuffer;
}

MC::VertexArray* MC::Object::getVertexArray()
{
    return &m_vertexArray;
}

MC::VertexBufferLayout* MC::Object::getVertexBufferLayout()
{
    return &m_vertexBufferLayout;
}

MC::IndexBuffer* MC::Object::getIndexBuffer()
{
	return &m_indexBuffer;
}

std::vector<glm::vec3>* MC::Object::getVertices()
{
    return &m_vertices;
}

void MC::Object::render(glm::mat4* transMat, std::vector<MC::Texture*> textures)
{
	//Bind
	m_vertexArray.bind();
	m_indexBuffer.bind();
	m_shader.bind();
	for (int i = 0; i < textures.size(); i++)
	{
		textures[i]->bind(i);
	}
	//Uniforms
	m_shader.setUniformMat4f("u_projection", *transMat);

	
	m_shader.setUniform1i("t_albedo", 0);
	m_shader.setUniform1i("t_normalmap", 1);
	//m_shader.setUniformSampler2D("tex1", tex->get());

	//Draw call
	GLCall(glDrawElements(GL_TRIANGLES, m_indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr));

	//Unbind
	for (int i = 0; i < textures.size(); i++)
	{
		textures[i]->unbind();
	}
	m_vertexArray.unbind();
	m_indexBuffer.unbind();
	m_shader.unbind();
}