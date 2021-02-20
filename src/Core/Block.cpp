#include <MC/Core/Block.hpp>

MC::Block::Block(): m_shader("../../../Shaders/basic.glsl")
{
}

MC::Block::Block(MC::DataManager* datamanager) : m_dataManager(datamanager), m_shader("../../../Shaders/cube.glsl")
{
	m_vertexArray = m_dataManager->getCubeVertexArray();
	m_indexBuffer = m_dataManager->getCubeIndexBuffer();
	m_shader.compile();
	INFO({ "Shader successfully compiled" });
}

MC::Block::Block(MC::DataManager* datamanager, glm::vec3 position): m_dataManager(datamanager), m_shader("../../../Shaders/cube.glsl"), m_position(position)
{
	m_vertexArray = m_dataManager->getCubeVertexArray();
	m_indexBuffer = m_dataManager->getCubeIndexBuffer();
	m_shader.compile();
	INFO({ "Shader successfully compiled" });
}

MC::Block::~Block()
{
}


void MC::Block::render(glm::mat4* transMat)
{
	//Bind
	m_vertexArray->bind();
	m_indexBuffer->bind();
	m_shader.bind();

	//Uniforms
	m_shader.setUniformMat4f("u_projection", *transMat);

	//Draw call
	GLCall(glDrawElements(GL_TRIANGLES, m_indexBuffer->getCount(), GL_UNSIGNED_INT, nullptr));

	//Unbind
	m_vertexArray->unbind();
	m_indexBuffer->unbind();
	m_shader.unbind();
}


void MC::Block::render(glm::mat4* transMat, MC::Texture* tex)
{
	//Bind
	m_vertexArray->bind();
	m_indexBuffer->bind();
	m_shader.bind();
	tex->bind(0);
	//Uniforms
	m_shader.setUniformMat4f("u_projection", *transMat);
	m_shader.setUniform1i("tex1", 0);
	//m_shader.setUniformSampler2D("tex1", tex->get());

	//Draw call
	GLCall(glDrawElements(GL_TRIANGLES, m_indexBuffer->getCount(), GL_UNSIGNED_INT, nullptr));

	//Unbind
	tex->unbind();
	m_vertexArray->unbind();
	m_indexBuffer->unbind();
	m_shader.unbind();
}