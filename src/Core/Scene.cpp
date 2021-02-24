#include <MC/Core/Scene.hpp>

MC::Scene::Scene()
{
}

MC::Scene::Scene(MC::DataManager* datamanager) : m_light(datamanager, "../../../Shaders/light.glsl")
{
	datamanager->loadLight(this);
}

MC::Scene::~Scene()
{
}

void MC::Scene::addObjectToScene(MC::Object* object)
{
	m_objects.push_back(object);
}

void MC::Scene::renderScene()
{
	// Display light
	/*
	m_light.updateTransform();
	m_light.bind();
	m_light.drawCall(m_PV, m_viewMatrix, m_lightPosition);
	m_light.unbind();
	*/
	m_light.updateTransform();
	m_light.renderAsLight(&m_PV);

	this->updateCameraPosition();
	std::vector<MC::Object*>::iterator it;
	for (it = m_objects.begin(); it != m_objects.end(); it++)
	{
		(**it).updateTransform();
		(**it).bind();
		(**it).drawCall(m_PV, m_viewMatrix, m_lightPosition);
		(**it).unbind();
	}
}

void MC::Scene::updateCameraPosition()
{
	m_projectionMatrix = glm::perspective(glm::radians(60.f), 1.0f, 0.1f, 100.0f);
	m_viewMatrix = glm::lookAt(glm::vec3(-4, -4, 1), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1));
	m_PV = m_projectionMatrix * m_viewMatrix;
}

void MC::Scene::clearScene()
{
	m_objects.clear();
}

bool MC::Scene::getLastPushedObject(MC::Object** object)
{
	if (m_objects.size() <= 0)
	{
		return false;
	}
	else
	{
		*object = m_objects[m_objects.size()-1];
		return true;
	}
}

MC::Object* MC::Scene::getLightObject()
{
	return &m_light;
}

void MC::Scene::updateLightPos(glm::vec3 position)
{
	m_lightPosition = position;
	m_light.setTransform(m_lightPosition, { 0., 0., 0. }, { 1., 1., 1. });
}
