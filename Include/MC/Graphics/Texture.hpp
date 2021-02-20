#pragma once

#include <string>
#include <MC/Debug.hpp>
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#include "external/stb_image.h"


namespace MC
{
	static enum TEXTURE_TYPES {
		SPUI_TEX_BMP
	};
	class Texture
	{
	public:
		Texture();
		bool loadBMP(const char*);
		bool loadPNG(const std::string&, unsigned int, bool);
		void bind(unsigned int slot = 0);
		void unbind();
		const unsigned int get() const;
		~Texture();

	protected:
		int m_width;
		int m_height;
		int m_imageSize;
		int m_BPP;
		unsigned int m_texture;
		unsigned char* data;
	};
};