#version 330
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texcoord;
layout(location = 2) in vec3 normal;

uniform mat4 model;
uniform mat4 vp;
uniform vec3 light_pos;
uniform vec3 eye_pos;
uniform int bling_phong;

out vec3 v_position;
out vec2 v_uv;
out vec3 v_normal;
out float v_cosine;
out float v_spec;

void main()
{
    v_position = (model*vec4(position, 1.0)).xyz;
    v_uv = texcoord;
    v_normal = (model*vec4(normal, 0.0)).xyz;
    gl_Position = vp*model*vec4(position, 1.0);

    vec3 L = normalize(light_pos - v_position);
    vec3 n = normalize(v_normal);
    float cosine = max(dot(L, n), 0);
    vec3 e = normalize(eye_pos - v_position);
	if(bling_phong == 1)
	{
		vec3 h = normalize(L + e);
		v_spec = cosine * pow(dot(n, h), 30);
	}
	else
	{
		vec3 r = reflect(L, n);
		v_spec = cosine * pow(dot(r, e), 30);
	}

	v_cosine = cosine;
}