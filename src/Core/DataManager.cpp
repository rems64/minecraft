#include <MC/Core/DataManager.hpp>
#include <MC/Core/Scene.hpp>

MC::DataManager::DataManager()
{
}

MC::DataManager::~DataManager()
{
}

MC::VertexArray* MC::DataManager::getCubeVertexArray()
{
	return &m_cubeVertexArray;
}

MC::IndexBuffer* MC::DataManager::getCubeIndexBuffer()
{
	return &m_cubeIndexBuffer;
}

bool MC::DataManager::generateCubeVertexBuffer()
{
	float locs[40] = {
	-1., -1., -1., 0., 0.,// 0
	1.,  -1., -1., 1., 0.,// 1
	-1.,  1., -1., 0., 1.,// 2
	1.,   1., -1., 1., 1.,// 3
	-1., -1.,  1., 0., 1.,// 4
	1.,  -1.,  1., 0., 0.,// 5
	-1.,  1.,  1., 1., 1.,// 6
	1.,   1.,  1., 1., 1.// 7
	};

	unsigned int indexes[] = {
	0, 1, 2,
	1, 2, 3,
	0, 1, 4,
	1, 4, 5,
	0, 2, 4,
	2, 4, 6,
	1, 3, 5,
	3, 5, 7,
	4, 5, 7,
	4, 7, 6,
	2, 3, 6,
	3, 6, 7
	};
	/*
	unsigned int indexes[] = {
		0, 1, 2,
		1, 2, 3
	};
	*/


	m_cubeVertexBuffer.setBuffer(locs, sizeof(locs));

	m_cubeIndexBuffer.setBuffer(indexes, sizeof(indexes) / sizeof(indexes[0]));

	m_cubeVertexBufferLayout.Push<float>(3);
	m_cubeVertexBufferLayout.Push<float>(2);

	m_cubeVertexArray.bind();
	m_cubeVertexArray.addBuffer(m_cubeVertexBuffer, m_cubeVertexBufferLayout);
	m_cubeVertexArray.unbind();

	return true;
}

bool MC::DataManager::loadBlocsList()
{
	std::cout << "[ERROR] An error occured, please report error in load block list" << std::endl;
	return true;
}

MC::Object* MC::DataManager::loadObj(MC::Scene *scene, std::string path)
{
	std::stringstream ss;
	std::fstream fileStream(path);
	std::string line;
	std::string end;

	std::vector<float> verticesVector;
	std::vector<float> uvsTemp;
	std::vector<float> normalsTemp;
	std::vector<unsigned int> vIndicesVector;

	float* tmpFloat;
	unsigned int* tmpInt;
	//std::string* tempIndices;
	std::string currentMaterial;
	MC::Object* currentObject(nullptr);
	while (std::getline(fileStream, line))
	{
		//std::cout << "LINE";
		if (line[0] == '#')
		{
			continue;
		}
		else
		{
			if (line.substr(0, 6) == "mtllib")
			{
				currentMaterial = line.substr(7, line.size() - 7);
				std::cout << "[INFO] Current material : " << currentMaterial << std::endl;
			}
			else if (line.substr(0, 6) == "usemtl")
			{
			}
			else if((line[0]=='v') & (line[1]==' '))
			{
				if (line.size() > 2)
				{
					int size = 0;
					tmpFloat = MC::parseString<float>(line.substr(2), " ", &size);
					for (int i = 0; i < size+1; i++)
					{
						verticesVector.push_back(tmpFloat[i]);
					}
				};
			}
			else if((line[0]=='v') & (line[1]=='t'))
			{
				if (line.size() > 2)
				{
					int size = 0;
					tmpFloat = MC::parseString<float>(line.substr(3), " ", &size);
					for (int i = 0; i < size+1; i++)
					{
						uvsTemp.push_back(tmpFloat[i]);
					}
				}
			}
			else if ((line[0] == 'v') & (line[1] == 'n'))
			{
				if (line.size() > 2)
				{
					int size = 0;
					tmpFloat = MC::parseString<float>(line.substr(3), " ", &size);
					for (int i = 0; i < size + 1; i++)
					{
						normalsTemp.push_back(tmpFloat[i]);
					}
				}
			}
			if ((line[0] == 'f') & (line[1] == ' '))
			{
				int size = 0;
				std::string* tempIndices = MC::parseString<std::string>(line.substr(2), " ", &size);
				size+=1;
				if(size == 3)
					for (unsigned int i = 0; i < size; i++)
					{
						int size2 = 0;
						unsigned int* tmp = MC::parseString<unsigned int>(tempIndices[i], "/", &size2);
						vIndicesVector.push_back(tmp[0]);      // Push_back
						vIndicesVector.push_back(tmp[1]);      // Push_back
						vIndicesVector.push_back(tmp[2]);      // Push_back
					}
				else if(size == 4)
				{
					unsigned int* tmp;
					int size2 = 0;
					for (unsigned int i = 0; i < 3; i++)
					{
						tmp = MC::parseString<unsigned int>(tempIndices[i], "/", &size2);
						vIndicesVector.push_back(tmp[0]);      // Push_back
						vIndicesVector.push_back(tmp[1]);      // Push_back
						vIndicesVector.push_back(tmp[2]);      // Push_back
					}
					tmp = MC::parseString<unsigned int>(tempIndices[0], "/", &size2);
					vIndicesVector.push_back(tmp[0]);      // Push_back
					vIndicesVector.push_back(tmp[1]);      // Push_back
					vIndicesVector.push_back(tmp[2]);      // Push_back

					tmp = MC::parseString<unsigned int>(tempIndices[2], "/", &size2);
					vIndicesVector.push_back(tmp[0]);      // Push_back
					vIndicesVector.push_back(tmp[1]);      // Push_back
					vIndicesVector.push_back(tmp[2]);      // Push_back

					tmp = MC::parseString<unsigned int>(tempIndices[3], "/", &size2);
					vIndicesVector.push_back(tmp[0]);      // Push_back
					vIndicesVector.push_back(tmp[1]);      // Push_back
					vIndicesVector.push_back(tmp[2]);      // Push_back
				}
				else if (size == 5)
				{
					unsigned int* tmp;
					int size2 = 0;
					for (unsigned int i = 0; i < 3; i++)
					{
						tmp = MC::parseString<unsigned int>(tempIndices[i], "/", &size2);
						vIndicesVector.push_back(tmp[0]);      // Push_back
						vIndicesVector.push_back(tmp[1]);      // Push_back
						vIndicesVector.push_back(tmp[2]);      // Push_back
					}
					tmp = MC::parseString<unsigned int>(tempIndices[0], "/", &size2);
					vIndicesVector.push_back(tmp[0]);      // Push_back
					vIndicesVector.push_back(tmp[1]);      // Push_back
					vIndicesVector.push_back(tmp[2]);      // Push_back

					tmp = MC::parseString<unsigned int>(tempIndices[2], "/", &size2);
					vIndicesVector.push_back(tmp[0]);      // Push_back
					vIndicesVector.push_back(tmp[1]);      // Push_back
					vIndicesVector.push_back(tmp[2]);      // Push_back

					tmp = MC::parseString<unsigned int>(tempIndices[4], "/", &size2);
					vIndicesVector.push_back(tmp[0]);      // Push_back
					vIndicesVector.push_back(tmp[1]);      // Push_back
					vIndicesVector.push_back(tmp[2]);      // Push_back

					tmp = MC::parseString<unsigned int>(tempIndices[4], "/", &size2);
					vIndicesVector.push_back(tmp[0]);      // Push_back
					vIndicesVector.push_back(tmp[1]);      // Push_back
					vIndicesVector.push_back(tmp[2]);      // Push_back

					tmp = MC::parseString<unsigned int>(tempIndices[2], "/", &size2);
					vIndicesVector.push_back(tmp[0]);      // Push_back
					vIndicesVector.push_back(tmp[1]);      // Push_back
					vIndicesVector.push_back(tmp[2]);      // Push_back

					tmp = MC::parseString<unsigned int>(tempIndices[3], "/", &size2);
					vIndicesVector.push_back(tmp[0]);      // Push_back
					vIndicesVector.push_back(tmp[1]);      // Push_back
					vIndicesVector.push_back(tmp[2]);      // Push_back

				}
				else {
					std::cout << "[ERROR] Wrong number of vertices per face : " << size << std::endl;
					//return nullptr;
				}
			}
		}
	}

	std::cout << "[INFO] PARSING DONE" << std::endl;
	
	std::vector<glm::vec3> doneIndices;
	float* vertices = (float*)calloc((size_t)vIndicesVector.size() * 4, sizeof(float)); assert(vertices);
	unsigned int* indices = (unsigned int*)calloc((size_t)vIndicesVector.size() / 3, sizeof(unsigned int)); assert(indices);
	for (unsigned long i = 0; i < vIndicesVector.size() / 3; i++)
	{
		vertices[8 * i + 0] = verticesVector[(vIndicesVector[3 * i] - 1)*3+0];
		vertices[8 * i + 1] = verticesVector[(vIndicesVector[3 * i] - 1)*3+1];
		vertices[8 * i + 2] = verticesVector[(vIndicesVector[3 * i] - 1)*3+2];
		vertices[8 * i + 3] = normalsTemp[(vIndicesVector[3 * i + 2] - 1) * 3 + 0];
		vertices[8 * i + 4] = normalsTemp[(vIndicesVector[3 * i + 2] - 1) * 3 + 1];
		vertices[8 * i + 5] = normalsTemp[(vIndicesVector[3 * i + 2] - 1) * 3 + 2];
		vertices[8 * i + 6] = uvsTemp[(vIndicesVector[3 * i + 1] - 1)*2+0];
		vertices[8 * i + 7] = uvsTemp[(vIndicesVector[3* i + 1] - 1)*2+1];
		indices[i] = i;
	};


	//std::cout << vertices[0] << " | " << vertices[1] << " | " << vertices[2] << std::endl; assert(std::cout);
	//std::cout << uvs[0] << " | " << uvs[1] << " | " << uvs[2] << std::endl; assert(std::cout);
	//std::cout << vIndices[0] << " | " << vIndices[1] << " | " << vIndices[2] << " | " << vIndices[3] << " | " << vIndices[4] << std::endl; assert(std::cout);
	//std::cout << ss.str() << std::endl;


	MC::Object* object = new MC::Object(this, "../../../Shaders/basic.glsl");
	object->getVertexBuffer()->setBuffer(vertices, vIndicesVector.size() * 4 * sizeof(float));

	object->getIndexBuffer()->setBuffer(indices, vIndicesVector.size() / 3);

	object->getVertexBufferLayout()->Push<float>(3);
	object->getVertexBufferLayout()->Push<float>(3);
	object->getVertexBufferLayout()->Push<float>(2);

	object->getVertexArray()->bind();
	object->getVertexArray()->addBuffer(*(object->getVertexBuffer()), *(object->getVertexBufferLayout()));
	object->getVertexArray()->unbind();
	scene->addObjectToScene(object);

	return currentObject;
}

MC::DataManager::blockStruct MC::DataManager::getBlock(unsigned int id)
{
	std::map<unsigned int, MC::DataManager::blockStruct>::iterator it;
	unsigned int i = 0;
	for (it = m_blocksList.begin(); it != m_blocksList.end(); it++)
	{
		if (it->second.id == id)
		{
			return m_blocksList[i];
		}
		i++;
	};
	std::cout << "[ERROR] Block can't be found (id=" << id << ")" << std::endl;
	throw "[ERROR] An error occured at finding block from id";
}


template<typename T>
T* MC::parseString<T>(std::string string, std::string delimiter, int* size)
{
	unsigned int size = 0;
	std::string::size_type pos = 0;
	while ((pos = string.find(delimiter, pos)) != std::string::npos) {
		(*size)+=1;
		pos += delimiter.length();
	}

	//T* liste = (T*)calloc((size_t)(*size), sizeof(T)); assert(liste);
	T* liste = new T[(*size) + 1];

	pos = 0;
	std::string token;
	uint32_t index = 0;
	while ((pos = string.find(delimiter)) != std::string::npos) {
		token = string.substr(0, pos);
		liste[index++] = (T)token;
		string.erase(0, pos + delimiter.length());
	}
	liste[index] = (T)string;
	return liste;
}


template<>
float* MC::parseString<float>(std::string string, std::string delimiter, int* size)
{
	std::string::size_type pos = 0;
	while ((pos = string.find(delimiter, pos)) != std::string::npos) {
		(*size)+=1;
		pos += delimiter.length();
	}

	//float* liste = (float*)calloc((size_t)(*size), sizeof(float)); assert(liste);
	float* liste = new float[(*size) + 1];

	pos = 0;
	std::string token;
	uint32_t index=0;
	while ((pos = string.find(delimiter)) != std::string::npos) {
		token = string.substr(0, pos);
		liste[index++] = std::stof(token);
		string.erase(0, pos + delimiter.length());
	}
	liste[index] = std::stof(string);
	return liste;
}

template<>
int* MC::parseString<int>(std::string string, std::string delimiter, int* size)
{
	std::string::size_type pos = 0;
	while ((pos = string.find(delimiter, pos)) != std::string::npos) {
		(*size)+=1;
		pos += delimiter.length();
	}

	//int* liste = (int*)calloc((size_t)(*size), sizeof(int)); assert(liste);
	int* liste = new int[(*size) + 1];

	pos = 0;
	std::string token;
	uint32_t index = 0;
	while ((pos = string.find(delimiter)) != std::string::npos) {
		token = string.substr(0, pos);
		liste[index++] = (int)std::stof(token);
		string.erase(0, pos + delimiter.length());
	}
	liste[index] = (int)std::stof(string);
	return liste;
}


template<>
unsigned int* MC::parseString<unsigned int>(std::string string, std::string delimiter, int* size)
{
	std::string::size_type pos = 0;
	while ((pos = string.find(delimiter, pos)) != std::string::npos) {
		(*size) += 1;
		pos += delimiter.length();
	}

	//unsigned int* liste = (unsigned int*)calloc((size_t)(*size), sizeof(unsigned int)); assert(liste);
	unsigned int* liste = new unsigned int[(*size)+1];

	pos = 0;
	std::string token;
	uint32_t index = 0;
	while ((pos = string.find(delimiter)) != std::string::npos) {
		token = string.substr(0, pos);
		liste[index++] = (unsigned int)std::stof(token);
		string.erase(0, pos + delimiter.length());
	}
	liste[index] = (unsigned int)std::stof(string);
	return liste;
}


template<>
std::string* MC::parseString<std::string>(std::string string, std::string delimiter, int* size)
{
	std::string::size_type pos = 0;
	while ((pos = string.find(delimiter, pos)) != std::string::npos) {
		(*size) += 1;
		pos += delimiter.length();
	}

	//std::string* liste = (std::string*) calloc((size_t)(size), sizeof(std::string)); assert(liste);
	std::string* liste = new std::string[(*size)+1];

	pos = 0;
	std::string token;
	uint32_t index = 0;
	while ((pos = string.find(delimiter)) != std::string::npos) {
		token = string.substr(0, pos);
		liste[index] = (std::string)token;
		string.erase(0, pos + delimiter.length());
		index++;
	}
	liste[index] = (std::string)string;
	return liste;
}


std::string MC::DataManager::openFile(const char* filter)
{
	OPENFILENAMEA ofn;
	CHAR szFile[260] = { 0 };
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	//ofn.hwndOwner = glfwGetWin32Window();
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = filter;
	ofn.nFilterIndex = 1;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
	if (GetOpenFileNameA(&ofn) == TRUE)
	{
		std::cout << ofn.lpstrFile << std::endl;
		return ofn.lpstrFile;
	};
	return std::string();
}

void MC::DataManager::loadLight(MC::Scene* scene)
{
	std::stringstream ss;
	std::fstream fileStream("../../../ressources/3dmodels/light.obj");
	std::string line;
	std::string end;

	std::vector<float> verticesVector;
	std::vector<float> uvsTemp;
	std::vector<float> normalsTemp;
	std::vector<unsigned int> vIndicesVector;

	float* tmpFloat;
	unsigned int* tmpInt;
	//std::string* tempIndices;
	while (std::getline(fileStream, line))
	{
		//std::cout << "LINE";

		if (line[0] == '#')
		{
			continue;
		}
		else
		{
			if ((line[0] == 'v') & (line[1] == ' '))
			{
				if (line.size() > 2)
				{
					int size = 0;
					tmpFloat = MC::parseString<float>(line.substr(2), " ", &size);
					for (int i = 0; i < size + 1; i++)
					{
						verticesVector.push_back(tmpFloat[i]);
					}
				};
			}
			else if ((line[0] == 'v') & (line[1] == 't'))
			{
				if (line.size() > 2)
				{
					int size = 0;
					tmpFloat = MC::parseString<float>(line.substr(3), " ", &size);
					for (int i = 0; i < size + 1; i++)
					{
						uvsTemp.push_back(tmpFloat[i]);
					}
				}
			}
			else if ((line[0] == 'v') & (line[1] == 'n'))
			{
				if (line.size() > 2)
				{
					int size = 0;
					tmpFloat = MC::parseString<float>(line.substr(3), " ", &size);
					for (int i = 0; i < size + 1; i++)
					{
						normalsTemp.push_back(tmpFloat[i]);
					}
				}
			}
			if ((line[0] == 'f') & (line[1] == ' '))
			{
				int size = 0;
				std::string* tempIndices = MC::parseString<std::string>(line.substr(2), " ", &size);
				for (unsigned int i = 0; i < size + 1; i++)
				{
					int size2 = 0;
					unsigned int* tmp = MC::parseString<unsigned int>(tempIndices[i], "/", &size2);
					vIndicesVector.push_back(tmp[0]);      // Push_back
					vIndicesVector.push_back(tmp[1]);      // Push_back
					vIndicesVector.push_back(tmp[2]);      // Push_back
				}
			}
		}
	}

	std::cout << "[INFO] PARSING DONE" << std::endl;
	std::vector<glm::vec3> doneIndices;
	float* vertices = (float*)calloc((size_t)vIndicesVector.size() * 4, sizeof(float)); assert(vertices);
	unsigned int* indices = (unsigned int*)calloc((size_t)vIndicesVector.size() / 3, sizeof(unsigned int)); assert(indices);
	for (unsigned long i = 0; i < vIndicesVector.size() / 3; i++)
	{
		vertices[8 * i + 0] = verticesVector[(vIndicesVector[3 * i] - 1) * 3 + 0];
		vertices[8 * i + 1] = verticesVector[(vIndicesVector[3 * i] - 1) * 3 + 1];
		vertices[8 * i + 2] = verticesVector[(vIndicesVector[3 * i] - 1) * 3 + 2];
		vertices[8 * i + 3] = normalsTemp[(vIndicesVector[3 * i + 2] - 1) * 3 + 0];
		vertices[8 * i + 4] = normalsTemp[(vIndicesVector[3 * i + 2] - 1) * 3 + 1];
		vertices[8 * i + 5] = normalsTemp[(vIndicesVector[3 * i + 2] - 1) * 3 + 2];
		vertices[8 * i + 6] = uvsTemp[(vIndicesVector[3 * i + 1] - 1) * 2 + 0];
		vertices[8 * i + 7] = uvsTemp[(vIndicesVector[3 * i + 1] - 1) * 2 + 1];
		indices[i] = i;
	};
	//std::cout << vertices[0] << " | " << vertices[1] << " | " << vertices[2] << std::endl; assert(std::cout);
	//std::cout << uvs[0] << " | " << uvs[1] << " | " << uvs[2] << std::endl; assert(std::cout);
	//std::cout << vIndices[0] << " | " << vIndices[1] << " | " << vIndices[2] << " | " << vIndices[3] << " | " << vIndices[4] << std::endl; assert(std::cout);
	//std::cout << ss.str() << std::endl;
	//MC::Object* object = new MC::Object(this, "../../../Shaders/basic.glsl");
	scene->getLightObject()->getVertexBuffer()->setBuffer(vertices, vIndicesVector.size() * 4 * sizeof(float));

	scene->getLightObject()->getIndexBuffer()->setBuffer(indices, vIndicesVector.size() / 3);

	scene->getLightObject()->getVertexBufferLayout()->Push<float>(3);
	scene->getLightObject()->getVertexBufferLayout()->Push<float>(3);
	scene->getLightObject()->getVertexBufferLayout()->Push<float>(2);

	scene->getLightObject()->getVertexArray()->bind();
	scene->getLightObject()->getVertexArray()->addBuffer(*(scene->getLightObject()->getVertexBuffer()), *(scene->getLightObject()->getVertexBufferLayout()));
	scene->getLightObject()->getVertexArray()->unbind();
}