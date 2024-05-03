#type vertex
#version 460 core

layout(location = 0)in vec3 i_Position;

uniform mat4 u_ProjectionView;
uniform mat4 u_Transform;

void main()
{
	gl_Position = u_ProjectionView * u_Transform * vec4(i_Position, 1.0);
}

#type fragment
#version 460 core

uniform vec4 u_FlatColor;

out vec4 color;

void main()
{
	color = u_FlatColor;
}