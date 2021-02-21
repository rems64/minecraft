//shader vertex
#version 330 core
layout (location = 0) in vec3 vertex_modelspace;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uvs_in;

uniform mat4 u_projection;
uniform mat4 model_projection;
uniform mat4 view_projection;
uniform vec3 u_lightPos;
out vec3 normals;
out vec3 FragPos;
out vec2 UV;
out vec3 lightPos;
out vec3 vertex_worldspace;
out vec3 vertex_cameraspace;

void main()
{
    gl_Position = u_projection * vec4(vertex_modelspace, 1.0);
    vertex_worldspace = (model_projection * vec4(vertex_modelspace, 1.0)).xyz;
    vertex_cameraspace = (view_projection * model_projection * vec4(vertex_modelspace, 1.0)).xyz;
    normals = (view_projection * model_projection * vec4(normal,0)).xyz;
    UV = uvs_in;
    lightPos = (view_projection * vec4(u_lightPos, 1)).xyz;
};


//shader fragment
#version 330 core
out vec4 color;
in vec3 normals;
in vec3 FragPos;
in vec2 UV;
in vec3 lightPos;
in vec3 vertex_worldspace;
in vec3 vertex_cameraspace;

uniform sampler2D t_albedo;
uniform sampler2D t_normalmap;
uniform int u_twoSided;

void main()
{    
    vec3 norm = normalize(normals);
    vec3 lightDir = normalize(lightPos - vertex_cameraspace);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * vec3(1.0, 1.0, 1.0);

    vec3 norminv = normalize(-normals);
    vec3 lightDirinv = normalize(lightPos - vertex_cameraspace);
    float diffinv = max(dot(norminv, lightDirinv), 0.0);
    vec3 diffuseinv = diffinv * vec3(1.0, 1.0, 1.0);
    vec3 result;
    if(u_twoSided==1)
    {
        result = (vec3(0.1, 0.1, 0.1) + max(diffuse, diffuseinv)) * texture(t_albedo, UV).rgb;
    }
    else
    {
        //result = (vec3(0.1, 0.1, 0.1) + diffuse) * texture(t_albedo, UV).rgb;
        result = vec3(1.0, 0.0, 0.0);
    }
    color = vec4(result, 1.0);
}