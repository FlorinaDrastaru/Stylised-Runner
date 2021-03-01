#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;
layout(location = 3) in vec3 v_color;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float Time;

out vec3 frag_color;
out vec3 frag_normal;

uniform float time;
uniform bool is_quad;

out vec2 texcoord;



void main()
{
	//frag_normal = v_normal;
	//frag_color = v_color;
	//frag_color = vec3(0,0,1);
	//gl_Position = Projection * View * Model * vec4(v_position, 1.0);
	texcoord = v_texture_coord;

	if (time >= 0)
	{
		texcoord = vec2(texcoord.x - time / 10.f, texcoord.y);
	}

	mat4 ModelView = View * Model;
	gl_Position = Projection * ModelView * vec4(v_position, 1.f);
}
