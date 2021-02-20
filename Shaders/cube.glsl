//shader vertex
#version 330 core
layout (location = 0) in vec3 vertex;
layout (location = 1) in vec2 normal;
layout (location = 2) in vec2 uvs_in;

uniform mat4 u_projection;

out vec2 UV;

void main()
{
    gl_Position = u_projection * vec4(vertex.x, vertex.y, vertex.z, 1.0);
    UV = uvs_in;
};


//shader fragment
#version 330 core
out vec4 color;
in vec2 UV;

uniform sampler2D tex1;

void main()
{    
    vec3 col = vec3(texture(tex1, UV).r*0.5+0.5);
    color = vec4(col, 1.0);
    //color = vec4(1.0, 1.0, 1.0, 1.0);
}