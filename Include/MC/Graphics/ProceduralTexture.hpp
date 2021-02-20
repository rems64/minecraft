#pragma once

#include <GL/glew.h>
#include <MC/Debug.hpp>
#include <external/perlin.hpp>
#include <MC/Graphics/Texture.hpp>

namespace MC
{
	class ProceduralTexture : public MC::Texture
	{
	public:
		ProceduralTexture();
		ProceduralTexture(size_t width, size_t height, std::uint32_t seed, int octaves);
		~ProceduralTexture();

		void bind(unsigned int);
		void unbind();

		float get2D(double, double);
		void fillArray(float*, size_t, size_t, double, double);
		void fillBuffer(double, double);

		void sendToGl(double, double);

	private:
		siv::PerlinNoise m_perlin;
		int32_t m_octaves;
		float *m_buffer;
		size_t m_width;
		size_t m_height;
	};
}