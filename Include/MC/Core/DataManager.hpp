#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

#include <glm/common.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include <MC/Graphics/VertexBuffer.hpp>
#include <MC/Graphics/IndexBuffer.hpp>
#include <MC/Graphics/VertexBufferLayout.hpp>
#include <MC/Graphics/VertexArray.hpp>
#include <MC/Graphics/Texture.hpp>


#include <Windows.h>
#include <MC/Core/Object.hpp>
//#define GLFW_EXPOSE_NATIVE_WIN32
//#include <GLFW/glfw3native.h>

typedef enum class blocktype : int{
	NONE = -1,
	SOLID = 0,
	MC_TRANSPARENT = 1,
	DYNAMIC = 2
} BLOCKTYPE;

namespace MC
{
	class Scene;
	class DataManager
	{
	struct blockStruct
	{
		unsigned int id;
		std::string name;
		std::string displayName;
		BLOCKTYPE type;
		MC::Texture textures[6];
	};

	public:
		DataManager();
		~DataManager();

		MC::VertexArray* getCubeVertexArray();
		MC::IndexBuffer* getCubeIndexBuffer();
		bool generateCubeVertexBuffer();

		bool loadBlocsList();
		bool storeBlocsList();

		MC::Object* loadObj(MC::Scene* scene, std::string path);
		void loadLight(MC::Scene* scene);
		bool parseObj(MC::Object* object, const char* path);

		MC::DataManager::blockStruct getBlock(unsigned int);

		std::string openFile(const char* filter);
	private:
		MC::VertexBuffer m_cubeVertexBuffer;
		MC::IndexBuffer m_cubeIndexBuffer;
		MC::VertexBufferLayout m_cubeVertexBufferLayout;
		MC::VertexArray m_cubeVertexArray;

		std::ifstream m_blocksListFile;
		std::map<unsigned int, MC::DataManager::blockStruct> m_blocksList;
	};

	template<typename T>
	T* parseString(std::string string, std::string delimiter, int* size);

	template<>
	float* parseString<float>(std::string string, std::string delimiter, int* size);

	template<>
	int* parseString<int>(std::string string, std::string delimiter, int* size);

	template<>
	unsigned int* parseString<unsigned int>(std::string string, std::string delimiter, int* size);

	template<>
	std::string* parseString<std::string>(std::string string, std::string delimiter, int* size);
}