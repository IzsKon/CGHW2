#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in vec3 v_position[];
in vec2 v_uv[];
in vec3 v_normal[];
in float v_cosine[];
in float v_spec[];

out vec3 g_position;
out vec2 g_uv;
out vec3 g_normal;
out float g_cosine;
out float g_spec;

uniform int flat_shading;

void main() {
    //vec3 flat_normal = normalize(cross(v_position[1]-v_position[0], v_position[2]-v_position[0]));

    gl_Position = gl_in[0].gl_Position;
    g_position = v_position[0];
    g_uv = v_uv[0];
    g_normal = flat_shading==1 ? v_normal[0] : v_normal[0];
	g_cosine = v_cosine[0];
	g_spec = v_spec[0];
    EmitVertex();

    gl_Position = gl_in[1].gl_Position;
    g_position = v_position[1];
    g_uv = v_uv[1];
    g_normal = flat_shading==1 ? v_normal[0] : v_normal[1];
	g_cosine = flat_shading==1 ? v_cosine[0] : v_cosine[1];
	g_spec = flat_shading==1 ? v_spec[0] : v_spec[1];
    EmitVertex();
    
    gl_Position = gl_in[2].gl_Position;
    g_position = v_position[2];
    g_uv = v_uv[2];
    g_normal = flat_shading==1 ? v_normal[0] : v_normal[2];
	g_cosine = flat_shading==1 ? v_cosine[0] : v_cosine[2];
	g_spec = flat_shading==1 ? v_spec[0] : v_spec[2];
    EmitVertex();

    EndPrimitive();
}