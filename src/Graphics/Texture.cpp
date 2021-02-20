#include <MC/Graphics/Texture.hpp>

namespace MC
{

    Texture::Texture() : m_texture(0), m_imageSize(0), m_width(0), m_height(0), data(nullptr), m_BPP(0)
    {
    }

    Texture::~Texture()
    {
    };

    void Texture::bind(unsigned int slot)
    {
        GLCall(glActiveTexture(GL_TEXTURE0 + slot));
        GLCall(glBindTexture(GL_TEXTURE_2D, m_texture));
    }

    void Texture::unbind()
    {
        GLCall(glBindTexture(GL_TEXTURE_2D, 0));
    }

    const unsigned int Texture::get() const
    {
        return m_texture;
    }

    bool Texture::loadBMP(const char* path)
    {
        unsigned char header[54];
        unsigned int dataPos;     // Position in the file where the actual data begins
        // Actual RGB data
        FILE* file = fopen(path, "rb");
        if (!file)
        {
            printf("Image not loaded");
            return 0;
        }
        if (fread(header, 1, 54, file) != 54)
        {
            printf("Error with header");
            return 0;
        }
        if (header[0] != 'B' || header[1] != 'M')
        {
            printf("Header error");
            return 0;
        }
        dataPos = *(int*)&(header[0x0A]);
        m_imageSize = *(int*)&(header[0x22]);
        m_width = *(int*)&(header[0x12]);
        m_height = *(int*)&(header[0x16]);

        if (m_imageSize == 0)
        {
            m_imageSize = m_width * m_height * 3; // 3 : one byte for each Red, Green and Blue component
        }
        if (dataPos == 0)
        {
            dataPos = 54; // The BMP header is done that way
        }

        // Create a buffer
        data = new unsigned char[m_imageSize];

        // Read the actual data from the file into the buffer
        fread(data, 1, m_imageSize, file);

        //Everything is in memory now, the file can be closed
        fclose(file);

        GLCall(glGenTextures(1, &m_texture));

        bind();

        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_BGR, GL_UNSIGNED_BYTE, data));

        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
        return 1;
    };

    bool Texture::loadPNG(const std::string& path, unsigned int depth, bool invert)
    {
        stbi_set_flip_vertically_on_load(1);
        unsigned int colorSpace;
        if (invert)
            colorSpace = GL_BGR;
        else
            colorSpace = GL_RGB;
        data = stbi_load(path.c_str(), &m_width, &m_height, &m_BPP, STBI_rgb_alpha);

        GLCall(glGenTextures(1, &m_texture));

        bind();

        /*
        for (int i = 0; i < m_width * m_height; i++)
        {
            std::cout << data[i] << std::endl;
        }
        */

        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));

        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
        if (data)
        {
            stbi_image_free(data);
        }
        return 1;
    };
}