#version 330 

in vec3 in_Position;

out vec4 out_Position;

uniform mat4 mvp;

void main()
{
	out_Position =  mvp * vec4(in_Position, 1.0);
}