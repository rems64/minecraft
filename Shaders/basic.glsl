//shader vertex
#version 330 core
layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uvs_in;

uniform mat4 u_projection;
out vec3 normals;
out vec3 FragPos;
out vec2 UV;

void main()
{
    gl_Position = u_projection * vec4(vertex.x, vertex.y, vertex.z, 1.0);
    FragPos = vec3(vertex.x, vertex.y, vertex.z);
    normals = normal;
    UV = uvs_in;
};


//shader fragment
#version 330 core
out vec4 color;
in vec3 normals;
in vec3 FragPos;
in vec2 UV;

uniform sampler2D t_albedo;
uniform sampler2D t_normalmap;

void main()
{    
    vec3 norm = normalize(normals);
    vec3 lightDir = normalize(vec3(5.0, 5.0, 5.0) - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * vec3(1.0, 1.0, 1.0);


    vec3 result = (vec3(0.1, 0.1, 0.1) + diffuse) * texture(t_albedo, UV).rgb;
    color = vec4(result, 1.0);
}