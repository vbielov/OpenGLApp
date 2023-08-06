#vertex_shader
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUv;
layout (location = 2) in vec4 aColor;

out vec2 vUv;
out vec4 vColor;

uniform mat4 u_Projection;

void main()
{
    gl_Position = u_Projection * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    vUv = aUv;
    vColor = aColor;
};

#fragment_shader
#version 330 core

out vec4 FragColor;

in vec2 vUv;
in vec4 vColor;

uniform sampler2D u_Texture;

void main()
{
    FragColor = texture(u_Texture, vUv) * vColor;
};