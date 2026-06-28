#version 410 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in vec3 texCoord[];
out vec3 texCoord_frag;

void main()
{

//	gl_Position = gl_in[0].gl_Position + vec4(0.05f, 0.0f, 0.0f, 0.0f);
//	texCoord_frag = texCoord[0];
//	EmitVertex();
//	gl_Position = gl_in[1].gl_Position;
//	texCoord_frag = texCoord[1];
//	EmitVertex();
//	gl_Position = gl_in[2].gl_Position + vec4(-0.1f, 0.0f, 0.0f, 0.0f);
//	texCoord_frag = texCoord[2];
//	EmitVertex();
//    EmitVertex();
for (int i = 0; i < 3; ++i)
{
    gl_Position = gl_in[i].gl_Position;
    texCoord_frag = texCoord[i];
    EmitVertex();
}

	EndPrimitive();
}