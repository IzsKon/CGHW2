#version 330
layout(location=0) out vec4 color;

uniform sampler2D text;
uniform vec3 object_color;
uniform vec3 light_pos;
uniform vec3 eye_pos;
uniform int bling_phong;
uniform mat4 vp2;

in vec3 g_position;
in vec2 g_uv;
in vec3 g_normal;

void main()
{
	/*
	vec3 L = normalize(light_pos - g_position);
    vec3 n = normalize(g_normal);
	float cosine = max(dot(L, n), 0);
	vec3 e = normalize(eye_pos - g_position);
	float spec;
	if(bling_phong == 1)
	{
		vec3 h = normalize(L + e);
		spec = cosine * pow(dot(n, h), 30);
	}
	else
	{
		vec3 r = reflect(L, n);
		spec = cosine * pow(dot(r, e), 30);
	}
	*/

	vec3 lp = (vp2*vec4(light_pos, 1.0)).xyz;
	vec3 L = normalize(lp - g_position);
    vec3 n = normalize(g_normal);
	float cosine = max(dot(L, n), 0);
	vec3 e = normalize(-g_position);
	float spec;
	if(bling_phong == 1)
	{
		vec3 h = normalize(L + e);
		spec = cosine * pow(dot(n, h), 30);
	}
	else
	{
		vec3 r = reflect(L, n);
		spec = cosine * pow(dot(r, e), 30);
	}

	color = vec4(object_color * texture(text, g_uv).rgb * cosine + spec * vec3(1.0), 1.0);

}