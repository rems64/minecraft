#include <MC/Graphics/ProceduralTexture.hpp>

MC::ProceduralTexture::ProceduralTexture() : m_perlin(12345), m_octaves(1), m_width(100), m_height(100)
{
	m_buffer = (float *)calloc((size_t)(m_width * m_height), sizeof(float)); assert(m_buffer);
}

MC::ProceduralTexture::ProceduralTexture(size_t width, size_t height, std::uint32_t seed, int octaves) : m_perlin(seed), m_octaves(octaves), m_width(width), m_height(height)
{
	m_buffer = (float *)calloc((size_t)(width * height), sizeof(float)); assert(m_buffer);
	m_perlin.reseed(seed);
}
MC::ProceduralTexture::~ProceduralTexture()
{
	std::cout << "Destructor" << std::endl;
	glDeleteTextures(1, &m_texture);
	free(m_buffer); assert(m_buffer);
	m_buffer = NULL;
}

float MC::ProceduralTexture::get2D(double x, double y)
{
	return m_perlin.accumulatedOctaveNoise2D_0_1(x, y, m_octaves);
	//return 255.f;
}

void MC::ProceduralTexture::fillArray(float *array, size_t width, size_t height, double sizeX, double sizeY)
{
	for (int i = 0; i <= (width * height) - 1; i++)
	{
		array[i]=this->get2D((double)(i%width)*sizeX, (double)std::floor(i/width)*sizeY);
	}
}

void MC::ProceduralTexture::fillBuffer(double sizeX, double sizeY)
{
	int i = 0;
	for (std::int32_t y = 0; y < m_height; y++)
	{
		for (std::int32_t x = 0; x < m_width; x++)
		{
			m_buffer[i] = this->get2D(x / (m_width / sizeX), y / (m_height / sizeY));
			i++;
		}
	}
}

void MC::ProceduralTexture::sendToGl(double sizeX, double sizeY)
{
	GLCall(glGenTextures(1, &m_texture));

	MC::Texture::bind();

	//this->fillArray(m_buffer, m_width, m_height, sizeX, sizeY);
	this->fillBuffer(sizeX, sizeY);

	/*
	for (int i = 0; i < m_width*m_height; i++)
	{
		std::cout << m_buffer[i] << std::endl;
	}
	*/

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_R8_SNORM, m_width, m_height, 0, GL_RED, GL_FLOAT, m_buffer));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));

	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void MC::ProceduralTexture::bind(unsigned int slot=0)
{
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, MC::Texture::m_texture));
}

void MC::ProceduralTexture::unbind()
{
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
