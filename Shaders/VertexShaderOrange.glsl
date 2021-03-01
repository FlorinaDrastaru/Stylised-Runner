#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_textcoord;
layout(location = 3) in vec3 v_color;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float Time;

out vec3 frag_color;
out vec3 frag_normal;

void main()
{
	frag_normal = v_normal;
	frag_color = v_color;
	frag_color = vec3(1, 0.5, 0);
	gl_Position = Projection * View * Model * vec4(v_position, 1.0);
}
