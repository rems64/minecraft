#pragma once

#include <vector>
#include <MC/Core/Object.hpp>
#include <MC/Graphics/Renderer.hpp>
#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>

#include <MC/Core/DataManager.hpp>

namespace MC
{
	class Scene
	{
	public:
		Scene();
		Scene(MC::DataManager* datamanager);
		~Scene();

		void addObjectToScene(MC::Object* object);
		void renderScene();

		void updateCameraPosition();
		void clearScene();
		bool getLastPushedObject(MC::Object**);

		MC::Object* getLightObject();

		void updateLightPos(glm::vec3 position); // Deprecated, will be replaced soon
	private:
		std::vector<MC::Object*> m_objects;
		MC::Renderer m_renderer;

		glm::mat4 m_PV;
		glm::mat4 m_projectionMatrix;
		glm::mat4 m_viewMatrix;

		glm::vec3 m_lightPosition;

		MC::Object m_light;
	};
}