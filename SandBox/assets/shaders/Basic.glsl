#type vertex
#version 460 core

layout(location = 0)in vec3 i_Position;
layout(location = 1)in vec2 i_TexCoord;

uniform mat4 u_ProjectionView;
uniform mat4 u_Transform;

out vec2 v_TexCoord;

void main()
{
	gl_Position = u_ProjectionView * u_Transform * vec4(i_Position, 1.0);
	v_TexCoord = i_TexCoord;
}

#type fragment
#version 460 core

in vec2 v_TexCoord;

uniform sampler2D u_Texture;

out vec4 color;

void main()
{
	color = texture(u_Texture, v_TexCoord);
}