//shader vertex
#version 330 core
layout (location = 0) in vec3 vertex_modelspace;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uvs_in;

uniform mat4 u_projection;
out vec3 vertex;
out vec3 normals;

void main()
{
    gl_Position = u_projection * vec4(vertex_modelspace, 1.0);
    vertex = vertex_modelspace;
    normals = normal;
};


//shader fragment
#version 330 core
out vec4 color;
in vec3 vertex;
in vec3 normals;

void main()
{    
    vec3 norm = normalize(normals);
    vec3 lightDir = normalize(vec3(-2.0, -2.0, 2.0) - vertex);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * vec3(1.0, 1.0, 1.0);

    vec3 result = (vec3(0.1, 0.1, 0.1) + diffuse);
    color = vec4(result, 1.0);
}