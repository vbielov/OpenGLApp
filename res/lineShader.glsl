#vertex_shader
#version 330 core

layout (location = 0) in vec2 a_Pos;
layout (location = 1) in vec3 a_Color;

out vec3 v_Color;

uniform mat4 u_Projection;

void main()
{
    gl_Position = u_Projection * vec4(a_Pos.x, a_Pos.y, 0.0, 1.0);
    v_Color = a_Color;
};

#fragment_shader
#version 330 core

out vec4 FragColor;

in vec3 v_Color;

uniform sampler2D u_Texture;

void main()
{
    FragColor = vec4(v_Color.x, v_Color.y, v_Color.z, 1.0);
};