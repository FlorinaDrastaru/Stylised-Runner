#version 330

// TODO: get values from fragment shader
in vec3 frag_normal;
in vec3 frag_color;
uniform sampler2D texture_1;
uniform bool mix_textures;
in vec2 texcoord;
layout(location = 0) out vec4 out_color;

void main()
{
vec4 colour1 = texture2D(texture_1, texcoord);
	// TODO: write pixel out color
	//out_color = vec4(frag_color, 1.0);
	
		out_color = colour1;
	
	
	if (out_color.a < .5f)
	{
		discard;
	}
}