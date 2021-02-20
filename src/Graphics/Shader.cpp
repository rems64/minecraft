#include <MC/Graphics/Shader.hpp>

MC::Shader::Shader() : program(0), m_hasGeoShader(false)
{
}

MC::Shader::Shader(const std::string& filepath): program(0), m_hasGeoShader(false)
{
    ParseShader(filepath);
}

MC::Shader::~Shader()
{
    glDeleteProgram(program);
}


bool MC::Shader::compile()
{
    program = glCreateProgram();


    unsigned int vs = MC::Shader::CompileShader(GL_VERTEX_SHADER, vertexSource);
    GLCall(glAttachShader(program, vs));


    unsigned int gs(0);
    if (m_hasGeoShader)
    {
        gs = MC::Shader::CompileShader(GL_GEOMETRY_SHADER, geometrySource);
        GLCall(glAttachShader(program, gs));
        INFO({ "Shader's got geometry shader" });
    }

    unsigned int fs = MC::Shader::CompileShader(GL_FRAGMENT_SHADER, fragmentSource);
    GLCall(glAttachShader(program, fs));


    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLint program_comp(GL_TRUE);
    GLCall(glGetProgramiv(program, GL_LINK_STATUS, &program_comp));
    if(program_comp != GL_TRUE)
    {
        GLsizei log_length = 0;
        GLchar message[1024];
        glGetProgramInfoLog(program, 1024, &log_length, message);
        std::cout << "[ALERT] Error with shader " << program << " : " << message << std::endl;
    }
    else
    {
        INFO({ "This is fine" });
    }

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));
    if (m_hasGeoShader)
    {
        //GLCall(glDeleteShader(gs));
    }

    return true;
}

void MC::Shader::bind()
{
    GLCall(glUseProgram(program));
}

void MC::Shader::unbind()
{
    GLCall(glUseProgram(0));
}

bool MC::Shader::save()
{
    return false;
}

std::string& MC::Shader::getVertexSource()
{
    return vertexSource;
}

GLint MC::Shader::getUniform(const GLchar* location)
{
    return GLint(glGetUniformLocation(program, location));
}

void MC::Shader::setUniform1i(const GLchar* location, GLint v1)
{
    GLint concernedUniform = glGetUniformLocation(program, location);
    GLCall(glUniform1i(concernedUniform, v1));
}

void MC::Shader::setUniform1ui(const GLchar* location, GLuint v1)
{
    GLCall(glUniform1ui(glGetUniformLocation(program, location), v1));
}

void MC::Shader::setUniform1f(const GLchar* location, GLfloat v1)
{
    GLint concernedUniform = glGetUniformLocation(program, location);
    GLCall(glUniform1f(concernedUniform, v1));
}

void MC::Shader::setUniform1f(GLint target, GLfloat v1)
{
    GLCall(glUniform1f(target, v1));
}

void MC::Shader::setUniform2f(const GLchar* location, GLfloat v1, GLfloat v2)
{
    GLint concernedUniform = glGetUniformLocation(program, location);
    glUniform2f(concernedUniform, v1, v2);
}

void MC::Shader::setUniform2f(GLint target, GLfloat v1, GLfloat v2)
{
    glUniform2f(target, v1, v2);
}

void MC::Shader::setUniform3f(const char* location, GLfloat v1, GLfloat v2, GLfloat v3)
{
    glUniform3f(GetUniformLocation(location), v1, v2, v3);
}

void MC::Shader::setUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
    GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

void MC::Shader::setUniformSampler2D(const std::string& name, const unsigned int* texture)
{

}

int MC::Shader::GetUniformLocation(const std::string& name)
{
    GLCall(int location = glGetUniformLocation(program, name.c_str()));
    if (location == -1)
        std::cout << "Uniform doesn't exists" << std::endl;
    return location;
}

void MC::Shader::ParseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1, GEOMETRY = 2
    };

    std::string line;
    std::stringstream ss[3];

    ShaderType type = ShaderType::NONE;
    while (getline(stream, line))
    {
        if (line.find("//shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
            else if (line.find("geometry") != std::string::npos)
            {
                std::cout << "[INFO] Geometry shader found" << std::endl;
                type = ShaderType::GEOMETRY;
                m_hasGeoShader = true;
            }
        }
        else
        {
            ss[(int)type] << line << '\n';
        }
    };
    vertexSource = ss[0].str();
    fragmentSource = ss[1].str();
    geometrySource = ss[2].str();
}

unsigned int MC::Shader::CompileShader(unsigned int type, const std::string& source)
{
    GLCall(unsigned int id = glCreateShader(type));
    const char* src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    GLint shader_compiled;
    glGetShaderiv(id, GL_COMPILE_STATUS, &shader_compiled);
    if (shader_compiled != GL_TRUE)
    {
        GLsizei log_length = 0;
        GLchar message[1024];
        glGetShaderInfoLog(id, 1024, &log_length, message);
        std::cout << "[ALERT] Shader compilation ran in an issue (" << (GLenum)type << ") : " << std::endl << message << std::endl;
    }

    return id;
}
