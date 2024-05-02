#type vertex
#version 460 core

layout(location = 0)in vec2 i_Position;

uniform mat4 u_PV;
uniform mat4 u_Model;

void main()
{
	gl_Position = u_PV * u_Model * vec4(i_Position, 0.0, 1.0);
}

#type fragment
#version 460 core

uniform vec4 u_FlatColor;

out vec4 color;

void main()
{
	color = u_FlatColor;
}